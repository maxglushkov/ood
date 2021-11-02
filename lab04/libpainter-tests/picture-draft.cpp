#include <CPictureDraft.hpp>
#include <catch2/catch.hpp>
#include "shape.hpp"

TEST_CASE("Empty draft")
{
	const CPictureDraft draft;

	REQUIRE(draft.begin() == draft.end());
}

TEST_CASE("Draft with shapes")
{
	CPictureDraft draft;

	draft.AddShape(std::make_unique<Shape>(Color::Green));
	draft.AddShape(std::make_unique<Shape>(Color::Red));

	auto it = draft.begin();
	REQUIRE(it++->GetColor() == Color::Green);
	REQUIRE(it++->GetColor() == Color::Red);
	REQUIRE(it == draft.end());
}
