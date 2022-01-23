add_library(
	painter-src OBJECT
	main.cpp
	PainterApplication.cpp
	PainterWindow.cpp
	canvas/CairoCanvas.cpp
	canvas/CanvasPainter.cpp
	canvas-view/BoundsMovementState.cpp
	canvas-view/CanvasHitTester.cpp
	canvas-view/CanvasPresenter.cpp
	canvas-view/CanvasWidget.cpp
	canvas-view/SelectionFrame.cpp
	history/History.cpp
	drawing/Drawing.cpp
	drawing/RectangularShape.cpp
)
target_include_directories(painter-src SYSTEM PRIVATE ${GTKMM_INCLUDE_DIRS})
