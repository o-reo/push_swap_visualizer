#include <catch2/catch.hpp>
#include "pushswap.h"

TEST_CASE("run", "[PushSwap]") {
    PushSwap ps;
    ps.path = "../push_swap";
    ps.run("2 1 3");
    REQUIRE_FALSE(ps.commands.empty());
    REQUIRE(ps.commands.front() == "sa");
}
