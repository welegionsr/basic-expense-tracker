#include "ExpenseTracker.hpp"
#include <unordered_map>
#include <functional>
#include <limits> // For std::numeric_limits

static void ShowMenu()
{
    std::cout << "\n\nChoose an option from the menu:\n";
    std::cout << "1. Add Expense\n";
    std::cout << "2. View expenses by categories\n";
    std::cout << "3. View all expenses, sorted by amount\n";
    std::cout << "4. Quit\n\n\n";
}

static void PrintExpenses(const std::list<Expense>& expenses)
{
    std::cout << "All expenses, sorted by amount:\n\n";

    for(auto& expense : expenses)
    {
        std::cout << " - $" << expense.getAmount() << ": " << expense.getComment() << " (Category: " << expense.getCategory() << ")" << std::endl;
    }

    std::cout << "-----------------------------------------------------------\n";
}

static bool CompareExpenses(const Expense& lhs, const Expense& rhs)
{
    return (lhs.getAmount() > rhs.getAmount());
}

void ExpenseTracker::handleAdd()
{
    std::cout << "You chose to add a new expense.\nLet's begin!\n";
    std::cout << "First, type the amount in USD:\n";
    
    double amount;

    while (!(std::cin >> amount))  //this will be true if an error occurs.
    {
        std::string str;
        std::cin.clear();//you need to clear the flags before input
        std::getline(std::cin, str);//read what was written. Since you probably don't need this, look into cin.ignore()
        std::cout << str << " is not a valid input for amount. Try again!\n";
    }

    if(amount <= 0)
    {
        std::cout << "amount can't be negative or zero! returning to menu...\n";
        return;
    }

    std::cout << "Now type the name of the category:\n";
    std::string category("");
    std::cin >> category;

    // check if category already exists, and if not, add it
    if(!_expenses.hasCategory(category))
    {
        std::cout << "That's a new category, adding it automatically...\n";
    }

    std::cout << "Any comment for this expense? (if not, just press Enter)\n";
    std::string comment("");
    std::cin >> comment;

    if(comment == "")
    {
        comment = "No comment.";
    }

    _expenses.AddExpense(std::make_unique<Expense>(category, amount, comment));

    std::cout << "Expense successfully added!\n";

    std::cin.clear(); // Clear error flags
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
}

void ExpenseTracker::handleQuit()
{
    std::cout << "You chose to quit. Bye!\n";
    _isRunning = false;
}

void ExpenseTracker::handleViewCategories() const
{
    auto& categories = _expenses.getCategories();

    if (!categories.empty())
    {
        for(auto& category : categories)
        {
            // get all expenses of current category
            auto& expensesByCat = _expenses.getExpensesByCategory(category);

            // for each category, print its name, the list of expenses, and the sum total
            std::cout << "Category: " << category << " | Sum Total: $" << _expenses.getTotalByCategory(category) << std::endl;

            // now print the list of expenses
            for(auto& expense : expensesByCat)
            {
                std::cout << " - $" << expense->getAmount() << ": " << expense->getComment() << std::endl;
            }

            std::cout << "-----------------------------------------------------------\n";
        }
    }
}

void ExpenseTracker::handleViewAllSorted() const
{
    auto& categories = _expenses.getCategories();

    // merge all lists into one, then sort it
    std::list<Expense> allExpenses;

    if (!categories.empty())
    {
        for (auto& category : categories)
        {
            // get all expenses of current category
            auto& expensesByCat = _expenses.getExpensesByCategory(category);

            // add them to the big list
            for(auto& expense : expensesByCat)
            {
                allExpenses.emplace_back(*expense);
            }
        }
    }

    // now sort the big boy
    allExpenses.sort(CompareExpenses);

    // and print the whole list
    PrintExpenses(allExpenses);

}

void ExpenseTracker::start()
{
    // create map of input options
    std::unordered_map<std::string, std::function<void()>> options;
    options["1"] = [this]() { handleAdd(); };
    options["2"] = [this]() { handleViewCategories(); };
    options["3"] = [this]() { handleViewAllSorted(); };
    options["4"] = [this]() { handleQuit(); };

    std::string input("");
    _isRunning = true;

    while (_isRunning)
    {
        ShowMenu();

        std::getline(std::cin, input);

        if(options.count(input))
        {
            std::cout << "\n\n" << std::endl;
            options[input]();
        }
        else
        {
            std::cout << "invalid option, please choose one from the menu!\n";
        }
    }
}