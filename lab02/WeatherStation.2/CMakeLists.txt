cmake_minimum_required(VERSION 3.9.2)
project(WeatherStation.2 VERSION 0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED NO)
set(CMAKE_CXX_EXTENSIONS NO)

find_package(Catch2 REQUIRED)

add_executable(
	WeatherStation
	main.cpp
)

add_executable(
	tests
	tests.cpp
)

include(Catch)
enable_testing()
catch_discover_tests(tests)
