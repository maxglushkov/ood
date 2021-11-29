find_package(Catch2 REQUIRED)

add_executable(
	tests
	main.cpp
	CArguments.cpp
	CConstDocumentItem.cpp
	CDocument.cpp
	CDocumentItem.cpp
	CDocumentMenu.cpp
	CHistory.cpp
	CMenu.cpp
	CParagraph.cpp
	CSetCommand.cpp
	CSize.cpp
	CVectorCommand.cpp
	$<TARGET_OBJECTS:testable>
)

include(Catch)
catch_discover_tests(tests)
