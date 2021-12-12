find_package(Catch2 REQUIRED)

add_executable(
	tests
	main.cpp
	CHasQuarterState.cpp
	CNoQuarterState.cpp
	CSoldOutState.cpp
	CSoldState.cpp
	GumBallMachineWithDynamicallyCreatedState.cpp
	GumBallMachineWithState.cpp
	NaiveGumBallMachine.cpp
	State.cpp
)

include(Catch)
catch_discover_tests(tests)
