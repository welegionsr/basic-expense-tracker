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

void ExpenseTracker::start()
{
    // create map of input options
    std::unordered_map<std::string, std::function<void()>> options;
    options["1"] = [this]() { handleAdd(); };
    options["4"] = [this]() { handleQuit(); };

    std::string input("");
    _isRunning = true;

    while (_isRunning)
    {
        ShowMenu();

        // Use std::getline for robust input handling
        std::getline(std::cin, input);

        if(options.count(input))
        {
            options[input]();
        }
        else
        {
            std::cout << "invalid option, please choose one from the menu!\n";
        }
    }
}