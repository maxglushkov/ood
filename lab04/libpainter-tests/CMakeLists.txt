find_package(Catch2 REQUIRED)

add_executable(
	libpainter-tests
	main.cpp
	shape.cpp
	picture-draft.cpp
	painter.cpp
	ellipse.cpp
	rectangle.cpp
	regular-polygon.cpp
	triangle.cpp
	shape-factory.cpp
	designer.cpp
)
target_include_directories(libpainter-tests SYSTEM PUBLIC ../libpainter)
target_link_libraries(libpainter-tests libpainter)

include(Catch)
catch_discover_tests(libpainter-tests)
