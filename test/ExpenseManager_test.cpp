#include "ExpenseManager.hpp"
#include <cassert>


void BasicTest()
{
    ExpenseManager expMan;

    expMan.AddExpense(std::make_unique<Expense>("Utilities", 200, "Water bill"));
    expMan.AddExpense(std::make_unique<Expense>("Utilities", 100, "Other bill"));

    auto& list = expMan.getExpensesByCategory("Utilities");
    double total = expMan.getTotalByCategory("Utilities");

    assert(total == 300);
    assert(list.front()->getComment() == "Water bill");

    std::cout << "Basic Test: PASSED!\n";
}


int main()
{
    std::cout << "ExpenseManager TESTS:\n\n";
    BasicTest();

    std::cout << "\n\nEnd of ExpenseManager TESTS.\n\n";

    return 0;
}