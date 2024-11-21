#ifndef __EXPENSE_HPP__
#define __EXPENSE_HPP__

#include <iostream>
#include <string>

class Expense
{
public:
    Expense(const std::string& category, double amount, const std::string& comment = "No comment.");
    ~Expense() noexcept = default;
    Expense(const Expense& other) = default;
    Expense& operator=(const Expense& other) = default;
    Expense(Expense&& other) = default;
    Expense& operator=(Expense&& other) = default;

    size_t getId() const;
    const std::string& getCategory() const;
    const std::string& getComment() const;
    double getAmount() const;

    void setCategory(const std::string& category);
    void setComment(const std::string& comment);
    void setAmount(double amount);

private:
    size_t _id = 0;
    std::string _category;
    std::string _comment;
    double _amount;

    static size_t _instances;

}; // class Expense


#endif // __EXPENSE_HPP__