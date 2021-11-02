add_subdirectory(tests)

add_executable(
	painter
	main.cpp
	CSvgCanvas.cpp
)
target_include_directories(painter SYSTEM PUBLIC ../libpainter)
target_link_libraries(painter libpainter)
