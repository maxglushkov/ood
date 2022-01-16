add_library(
	painter-src OBJECT
	main.cpp
	PainterApplication.cpp
	PainterWindow.cpp
	canvas/CairoCanvas.cpp
	canvas/CanonicalShape.cpp
	canvas/CanvasPresenter.cpp
	canvas/CanvasWidget.cpp
	canvas/Ellipse.cpp
	canvas/ICanvasPresenterItem.cpp
	canvas/Rectangle.cpp
	canvas/SelectionFrame.cpp
	canvas/Triangle.cpp
	model/Drawing.cpp
	model/RectangularShape.cpp
)
target_include_directories(painter-src SYSTEM PRIVATE ${GTKMM_INCLUDE_DIRS})
