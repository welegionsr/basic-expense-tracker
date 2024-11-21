#include "ExpenseManager.hpp"

ExpenseManager::ExpenseManager() : _total(0)
{
}

double ExpenseManager::getTotal() const
{
    return _total;
}

void ExpenseManager::AddExpense(std::unique_ptr<Expense> newExp)
{
    _container.push(newExp);
}

void ExpenseManager::Reset()
{
    while(!_container.empty())
    {
        _container.pop();
    }
}