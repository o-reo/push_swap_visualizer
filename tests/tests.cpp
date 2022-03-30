#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "queues.h"

TEST_CASE("Queues", "Add") {
    Queues queues;
    queues.queueA = {1, 2, 3, 4};
    queues.commands = {"sa"};
    queues.step();
    REQUIRE(queues.queueA.front() == 2);
    REQUIRE(*(++queues.queueA.begin()) == 1);
}
