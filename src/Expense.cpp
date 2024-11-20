#include "Expense.hpp" // Expense class

size_t Expense::_instances = 0; // initialize static instances counter

Expense::Expense(const std::string& category, double amount, const std::string& comment) : _id(_instances + 1), _category(category), _comment(comment), _amount(amount)
{
    ++_instances;
}

size_t Expense::getId() const
{
    return _id;
}

const std::string& Expense::getCategory() const
{
    return _category;
}

const std::string& Expense::getComment() const
{
    return _comment;
}

double Expense::getAmount() const
{
    return _amount;
}

