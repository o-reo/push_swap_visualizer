#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "queues.h"

TEST_CASE("normalize", "[Queues]") {
    Queues queues;
    queues.start({2, 10, 4});
    auto it = queues.queueA.begin();
    REQUIRE(*it == 0);
    REQUIRE(*(++it) == 2);
    REQUIRE(*(++it) == 1);
}

TEST_CASE("sa", "[Queues]") {
    Queues queues;
    queues.queueA = {1, 2, 3, 4};
    queues.commands = {"sa"};
    queues.step();
    REQUIRE(queues.queueA.front() == 2);
    REQUIRE(*(++queues.queueA.begin()) == 1);
}

TEST_CASE("sb", "[Queues]") {
    Queues queues;
    queues.queueB = {1, 2, 3, 4};
    queues.commands = {"sb"};
    queues.step();
    REQUIRE(queues.queueB.front() == 2);
    REQUIRE(*(++queues.queueB.begin()) == 1);
}

TEST_CASE("pa", "[Queues]") {
    Queues queues;
    queues.queueB = {1, 2, 3, 4};
    queues.commands = {"pa"};
    queues.step();
    REQUIRE(queues.queueB.front() == 2);
    REQUIRE(queues.queueA.front() == 1);
}

TEST_CASE("pb", "[Queues]") {
    Queues queues;
    queues.queueA = {1, 2, 3, 4};
    queues.commands = {"pb"};
    queues.step();
    REQUIRE(queues.queueA.front() == 2);
    REQUIRE(queues.queueB.front() == 1);
}

TEST_CASE("ra", "[Queues]") {
    Queues queues;
    queues.queueA = {1, 2, 3, 4};
    queues.commands = {"ra"};
    queues.step();
    REQUIRE(queues.queueA.front() == 2);
    REQUIRE(queues.queueA.back() == 1);
}

TEST_CASE("rb", "[Queues]") {
    Queues queues;
    queues.queueB = {1, 2, 3, 4};
    queues.commands = {"rb"};
    queues.step();
    REQUIRE(queues.queueB.front() == 2);
    REQUIRE(queues.queueB.back() == 1);
}

TEST_CASE("rra", "[Queues]") {
    Queues queues;
    queues.queueA = {1, 2, 3, 4};
    queues.commands = {"rra"};
    queues.step();
    REQUIRE(queues.queueA.front() == 4);
    REQUIRE(queues.queueA.back() == 3);
}

TEST_CASE("rrb", "[Queues]") {
    Queues queues;
    queues.queueB = {1, 2, 3, 4};
    queues.commands = {"rrb"};
    queues.step();
    REQUIRE(queues.queueB.front() == 4);
    REQUIRE(queues.queueB.back() == 3);
}
