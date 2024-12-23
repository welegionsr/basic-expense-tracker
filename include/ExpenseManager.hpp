#ifndef __EXPENSE_MANAGER_HPP__
#define __EXPENSE_MANAGER_HPP__

#include <unordered_map> // std::unordered_map
#include <list> // std::list
#include <vector>
#include <memory> // smart ptrs
#include <algorithm>

#include "Expense.hpp" // Expense class


class ExpenseManager
{

    class ExpenseCompare
    {
    public:
        bool operator()(const Expense& lhs, const Expense& rhs) const
        {
            return (lhs.getAmount() < rhs.getAmount());
        }
    }; // Class ExpenseCompare

    using ExpenseList = std::list<std::unique_ptr<Expense>>;

public:
    ExpenseManager() = default;
    ~ExpenseManager() noexcept = default;
    ExpenseManager(const ExpenseManager& other) = default;
    ExpenseManager& operator=(const ExpenseManager& other) = default;
    ExpenseManager(ExpenseManager&& other) = default;
    ExpenseManager& operator=(ExpenseManager&& other) = default;

    void AddExpense(std::unique_ptr<Expense> newExp);
    void Reset();

    const ExpenseList& getExpensesByCategory(const std::string& category) const;
    double getTotalByCategory(const std::string& category) const;

    const std::unordered_map <std::string, ExpenseList>& getAllExpenses() const;

    void addCategory(const std::string& category);
    bool hasCategory(const std::string& category) const;
    const std::vector<std::string>& getCategories() const;

private:
    std::unordered_map <std::string, ExpenseList> _container;
    std::vector<std::string> _categories;
};


#endif // __EXPENSE_MANAGER_HPP__