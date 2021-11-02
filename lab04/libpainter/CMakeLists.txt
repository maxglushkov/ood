add_library(
	libpainter
	Color.cpp
	CDesigner.cpp
	CEllipse.cpp
	CRectangle.cpp
	CRegularPolygon.cpp
	CShapeFactory.cpp
	CTriangle.cpp
)
set_property(TARGET libpainter PROPERTY OUTPUT_NAME painter)
