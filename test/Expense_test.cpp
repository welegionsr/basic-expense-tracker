#include "Expense.hpp"
#include <cassert>

void BasicTest()
{
    Expense exp("Entertainment", 50.0, "Tickets to a movie");

    assert(exp.getAmount() == 50.0 && exp.getCategory() == "Entertainment" && exp.getComment() == "Tickets to a movie");

    std::cout << "Basic test successful!\n";
}


int main()
{
    std::cout << "Expense class TESTS\n\n";

    BasicTest();

    std::cout << "\n\nEnd of: Expense class TESTS\n\n";

    return 0;
}