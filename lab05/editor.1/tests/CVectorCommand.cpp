#include <catch2/catch.hpp>
#include "../CVectorCommand.hpp"

constexpr static int VALUE = 0xc033a2d;

TEST_CASE("CVectorCommand: preparing to insert")
{
	static_assert(noexcept(std::vector<int>()));
	std::vector<int> vector;
	REQUIRE(vector.capacity() == 0);

	CVectorCommand<int> command(vector, 0, VALUE);
	REQUIRE(vector.capacity() > 0);
	REQUIRE(vector.empty());
}

TEST_CASE("CVectorCommand: inserting")
{
	std::vector<int> vector;
	CVectorCommand<int> command(vector, 0, VALUE);

	command.Do();
	REQUIRE(vector == std::vector{VALUE});
}

TEST_CASE("CVectorCommand: undoing insertion")
{
	std::vector<int> vector;
	CVectorCommand<int> command(vector, 0, VALUE);
	command.Do();

	command.Do();
	REQUIRE(vector.empty());
}

TEST_CASE("CVectorCommand: deleting")
{
	std::vector<int> vector{VALUE};
	CVectorCommand<int> command(vector, 0, std::nullopt);

	command.Do();
	REQUIRE(vector.empty());
}

TEST_CASE("CVectorCommand: undoing deletion")
{
	std::vector<int> vector{VALUE};
	CVectorCommand<int> command(vector, 0, std::nullopt);
	command.Do();

	command.Do();
	REQUIRE(vector == std::vector{VALUE});
}
