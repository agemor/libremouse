#include <wx/wx.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "LibreMouse.h"


IMPLEMENT_APP(LibreMouse);

bool LibreMouse::OnInit() {
	wxFrame *frame = new wxFrame((wxFrame*)NULL, -1, _T("LibreMouse"));
	frame->CreateStatusBar();
	frame->SetStatusText(_T("Hello World"));
	frame->Show(true);
	SetTopWindow(frame);
	return true;
}