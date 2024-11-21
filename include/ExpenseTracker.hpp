#ifndef __EXPENSE_TRACKER_HPP__
#define __EXPENSE_TRACKER_HPP__

#include "ExpenseManager.hpp"


class ExpenseTracker
{
public:
    ExpenseTracker() = default;
    ~ExpenseTracker() noexcept = default;
    ExpenseTracker(const ExpenseTracker& other) = default;
    ExpenseTracker& operator=(const ExpenseTracker& other) = default;
    ExpenseTracker(ExpenseTracker&& other) = default;
    ExpenseTracker& operator=(ExpenseTracker&& other) = default;

    void start();

private:
    ExpenseManager _expenses;
    bool _isRunning = false;

    void handleAdd();
    void handleQuit();
    void handleViewCategories() const;
    void handleViewAllSorted() const;

};


#endif // __EXPENSE_TRACKER_HPP__