find_package(Catch2 REQUIRED)

add_executable(
	painter-tests
	main.cpp
	client.cpp
)
target_include_directories(painter-tests SYSTEM PUBLIC ../../libpainter)

include(Catch)
catch_discover_tests(painter-tests)
