#include <string>

#include "Cache/Cache.h"
#include "Cache/Policy/FIFO.h"
#include "test_helper.hpp"

#include "catch2/catch.hpp"

TEMPLATE_TEST_CASE("Cache w/ FIFO replacement policy: FIFO behaviour", "[cache][behaviour][fifo]", (Cache<std::string, int, Policy::FIFO>),
    (Cache<std::string, void, Policy::FIFO>))
{
	constexpr size_t MAX_SIZE = 128;
	TestType cache(MAX_SIZE);

	SECTION("Replaced item is the first in (1/4)")
	{
		for(size_t i = 1; i <= MAX_SIZE; i++)
			insert_helper(cache, std::to_string(i), (int)i);

		REQUIRE(cache.size() == cache.max_size());
		REQUIRE(cache.evicted_count() == 0);

		CHECK(cache.contains("1") == true);

		insert_helper(cache, "asdf", 42);
		CHECK(cache.contains("1") == false);
		CHECK(cache.evicted_count() == 1);
	}

	SECTION("Replaced item is the first in (2/4)")
	{
		for(size_t i = 1; i <= MAX_SIZE; i++)
			insert_helper(cache, std::to_string(i), (int)i);

		REQUIRE(cache.size() == cache.max_size());
		REQUIRE(cache.evicted_count() == 0);

		CHECK(cache.contains("1") == true);

		insert_helper(cache, "asdf", 42);
		CHECK(cache.contains("1") == false);
		CHECK(cache.evicted_count() == 1);
	}

	SECTION("Replaced item is the first in (3/4)")
	{
		for(size_t i = 1; i <= MAX_SIZE; i++)
			insert_helper(cache, std::to_string(i), (int)i);

		REQUIRE(cache.size() == cache.max_size());
		REQUIRE(cache.evicted_count() == 0);

		for(size_t i = 1; i <= MAX_SIZE; i++)
			REQUIRE(cache.contains(std::to_string(i)) == true);

		CHECK(cache.contains("1") == true);

		insert_helper(cache, "asdf", 42);
		CHECK(cache.contains("1") == false);
		CHECK(cache.evicted_count() == 1);
	}

	SECTION("Replaced item is the first in (4/4)")
	{
		for(size_t i = 1; i <= MAX_SIZE; i++)
			insert_helper(cache, std::to_string(i), (int)i);

		REQUIRE(cache.size() == cache.max_size());
		REQUIRE(cache.evicted_count() == 0);

		for(size_t i = 1; i <= MAX_SIZE; i++)
			REQUIRE(cache.find(std::to_string(i)) != cache.end());

		CHECK(cache.contains("1") == true);

		insert_helper(cache, "asdf", 42);
		CHECK(cache.contains("1") == false);
		CHECK(cache.evicted_count() == 1);
	}
}
