#ifndef __EXPENSE_MANAGER_HPP__
#define __EXPENSE_MANAGER_HPP__

#include <unordered_map> // std::unordered_map
#include <queue> // std::priority_queue
#include <memory> // smart ptrs

#include "Expense.hpp" // Expense class


class ExpenseManager
{
public:
    ExpenseManager();
    ~ExpenseManager() noexcept = default;
    ExpenseManager(const ExpenseManager& other) = default;
    ExpenseManager& operator=(const ExpenseManager& other) = default;
    ExpenseManager(ExpenseManager&& other) = default;
    ExpenseManager& operator=(ExpenseManager&& other) = default;

    void AddExpense(std::unique_ptr<Expense> newExp);
    void Reset();
    double getTotal() const;

private:

    class ExpenseCompare
    {
    public:
        bool operator()(const Expense& lhs, const Expense& rhs) const
        {
            return (lhs.getAmount() < rhs.getAmount());
        }
    }; // Class ExpenseCompare

    std::priority_queue<std::unique_ptr<Expense>, std::vector<std::unique_ptr<Expense>>, ExpenseCompare> _container;
    double _total;
};


#endif // __EXPENSE_MANAGER_HPP__