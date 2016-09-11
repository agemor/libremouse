#pragma once
#include <wx/wx.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "VideoPanel.h";

class LibreMouse : public wxApp
{
private:
	wxFrame *frame;
	VideoPanel *videoPanel;

public:
	virtual bool OnInit();
};

DECLARE_APP(LibreMouse);