#include "Model/Person/Bank.hpp"
#include <gtest/gtest.h>
#include <iostream>

TEST(BankTest, InitTest)
{
    Bank bank;
    EXPECT_EQ(bank.Get_Number_Cards(), 0);
}
