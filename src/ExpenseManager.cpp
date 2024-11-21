#include "ExpenseManager.hpp"
#include <stdexcept>


void ExpenseManager::AddExpense(std::unique_ptr<Expense> newExp)
{
    _container[newExp->getCategory()].push_back(std::move(newExp));
}

void ExpenseManager::Reset()
{
    for(auto& list : _container)
    {
        list.second.clear();
    }
    _container.clear();
}

const ExpenseManager::ExpenseList& ExpenseManager::getExpensesByCategory(std::string category) const
{
    if(_container.count(category))
    {
        return _container.at(category);
    }
    else
    {
        throw std::invalid_argument("The given category doesn't exist!");
    }
}

double ExpenseManager::getTotalByCategory(std::string category) const
{
    double total = 0;

    if(_container.count(category))
    {
        for(auto& exp : _container.at(category))
        {
            total += exp->getAmount();
        }
    }

    return total;
}