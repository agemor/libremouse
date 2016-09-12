#pragma once
#include <wx/wx.h>
#include <wx/msgdlg.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "VideoPanel.h";

class LibreMouse : public wxApp
{
private:
	wxFrame *frame;
	VideoPanel *videoPanel;

	VideoProcessor *videoProcessor;

public:
	virtual bool OnInit();
	virtual int FilterEvent(wxEvent& event);
};

DECLARE_APP(LibreMouse);