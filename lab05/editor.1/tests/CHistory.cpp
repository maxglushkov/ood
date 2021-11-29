#include "../CHistory.hpp"
#include "command.hpp"

TEST_CASE("CHistory: empty")
{
	CHistory history;
	REQUIRE_FALSE(history.CanUndo());
	REQUIRE_FALSE(history.CanRedo());
	REQUIRE_THROWS(history.Undo());
	REQUIRE_THROWS(history.Redo());
}

TEST_CASE("CHistory: doing command")
{
	Command::State state = Command::State::NonexistentDestroyed;
	CHistory history;

	history.Do(std::make_unique<Command>(state));
	REQUIRE(state == Command::State::Done);
	REQUIRE(history.CanUndo());
	REQUIRE_FALSE(history.CanRedo());
	REQUIRE_THROWS(history.Redo());
}

TEST_CASE("CHistory: doing 2 commands")
{
	Command::State state[] = {
		Command::State::NonexistentDestroyed,
		Command::State::NonexistentDestroyed
	};
	CHistory history;

	history.Do(std::make_unique<Command>(state[0]));
	history.Do(std::make_unique<Command>(state[1]));
	REQUIRE(state[0] == Command::State::Done);
	REQUIRE(state[1] == Command::State::Done);
	REQUIRE(history.CanUndo());
	REQUIRE_FALSE(history.CanRedo());
}

TEST_CASE("CHistory: undoing command")
{
	Command::State state = Command::State::NonexistentDestroyed;
	CHistory history;
	history.Do(std::make_unique<Command>(state));

	history.Undo();
	REQUIRE(state == Command::State::CreatedUndone);
	REQUIRE(history.CanRedo());
	REQUIRE_FALSE(history.CanUndo());
	REQUIRE_THROWS(history.Undo());
}

TEST_CASE("CHistory: redoing command")
{
	Command::State state = Command::State::NonexistentDestroyed;
	CHistory history;
	history.Do(std::make_unique<Command>(state));
	history.Undo();

	history.Redo();
	REQUIRE(state == Command::State::Done);
	REQUIRE(history.CanUndo());
	REQUIRE_FALSE(history.CanRedo());
}

TEST_CASE("CHistory: new branch")
{
	Command::State oldState = Command::State::NonexistentDestroyed;
	CHistory history;
	history.Do(std::make_unique<Command>(oldState));
	history.Undo();

	Command::State newState = Command::State::NonexistentDestroyed;
	history.Do(std::make_unique<Command>(newState));
	REQUIRE(oldState == Command::State::NonexistentDestroyed);
	REQUIRE(newState == Command::State::Done);
	REQUIRE(history.CanUndo());
	REQUIRE_FALSE(history.CanRedo());
}
