#include "Model/Person/Player.hpp"
#include <gtest/gtest.h>
#include <iostream>

TEST(PlayerTest, InitTest)
{
    Player player;
    EXPECT_EQ(player.Get_Number_Cards(), 0);
}
