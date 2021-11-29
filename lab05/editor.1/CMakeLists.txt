cmake_minimum_required(VERSION 3.9.2)
project(editor.1 VERSION 0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

enable_testing()
add_subdirectory(tests)

add_library(
	testable OBJECT
	CDocument.cpp
	CDocumentMenu.cpp
	CImage.cpp
	CMenu.cpp
	CParagraph.cpp
)

add_executable(
	editor
	main.cpp
	$<TARGET_OBJECTS:testable>
)
