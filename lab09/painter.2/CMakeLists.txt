cmake_minimum_required(VERSION 3.9.2)
project(painter.2 VERSION 0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED NO)
set(CMAKE_CXX_EXTENSIONS NO)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)

add_subdirectory(src)

add_executable(
	painter
	$<TARGET_OBJECTS:painter-src>
)
target_link_libraries(painter ${GTKMM_LIBRARIES})
