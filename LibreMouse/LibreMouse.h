#pragma once
#include <wx/wx.h>
#include <wx/msgdlg.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "VideoPanel.h";

class LibreMouse : public wxApp {
private:
	wxFrame* frame;
	VideoPanel* videoPanel;
	wxTimer timer;

	VideoProcessor videoProcessor;
	CursorUpdater cursorUpdater;
	MouthMonitor mouthMonitor;

	DECLARE_EVENT_TABLE()

public:
	LibreMouse();
	virtual bool OnInit();
	virtual int FilterEvent(wxEvent& event);

	void onTimer(wxTimerEvent &event);

};

DECLARE_APP(LibreMouse);