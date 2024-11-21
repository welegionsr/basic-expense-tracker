#include "ExpenseManager.hpp"
#include <stdexcept>


void ExpenseManager::AddExpense(std::unique_ptr<Expense> newExp)
{
    if (!hasCategory(newExp->getCategory()))
    {
        addCategory(newExp->getCategory());
    }
    _container[newExp->getCategory()].push_back(std::move(newExp));
}

void ExpenseManager::Reset()
{
    for(auto& list : _container)
    {
        list.second.clear();
    }
    _container.clear();

    _categories.clear(); // reset the categories vector
}

const ExpenseManager::ExpenseList& ExpenseManager::getExpensesByCategory(const std::string& category) const
{
    if (hasCategory(category))
    {
        return _container.at(category);
    }
    else
    {
        throw std::invalid_argument("The given category doesn't exist!");
    }
}

double ExpenseManager::getTotalByCategory(const std::string& category) const
{
    double total = 0;

    if(hasCategory(category))
    {
        for(auto& exp : _container.at(category))
        {
            total += exp->getAmount();
        }
    }

    return total;
}

const std::unordered_map <std::string, ExpenseManager::ExpenseList>& ExpenseManager::getAllExpenses() const
{
    return _container;
}

void ExpenseManager::addCategory(const std::string& category)
{
    _categories.push_back(category);
}

bool ExpenseManager::hasCategory(const std::string& category) const
{
    return _container.count(category);
}

const std::vector<std::string>& ExpenseManager::getCategories() const
{
    return _categories;
}