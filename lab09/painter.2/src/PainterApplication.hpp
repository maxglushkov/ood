#pragma once
#include "PainterWindow.hpp"

class PainterApplication: public Gtk::Application
{
protected:
	void on_startup()override;

	void on_activate()override;

private:
	Drawing m_drawing{640, 480};
	PainterWindow m_mainWindow{m_drawing};

	void SetupMenu();
};
