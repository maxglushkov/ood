add_library(
	painter-src OBJECT
	main.cpp
	PainterApplication.cpp
	PainterWindow.cpp
	canvas/CairoCanvas.cpp
	canvas/CanvasPresenter.cpp
	canvas/CanvasWidget.cpp
	canvas/SelectionFrame.cpp
	model/CanonicalShape.cpp
	model/Drawing.cpp
	model/Ellipse.cpp
	model/Rectangle.cpp
	model/Triangle.cpp
)
target_include_directories(painter-src SYSTEM PRIVATE ${GTKMM_INCLUDE_DIRS})
