#include "LibreMouse.h"


IMPLEMENT_APP(LibreMouse);

bool LibreMouse::OnInit() {

	wxInitAllImageHandlers();

	wxFrame *frame = new wxFrame((wxFrame*)NULL, -1, _T("LibreMouse"));
	frame->CreateStatusBar();
	frame->SetStatusText(_T("Not tracking"));
	frame->Show(true);
	frame->SetSize(wxRect(0, 0, 640, 480), 2);
	SetTopWindow(frame);

	VideoProcessor proc = VideoProcessor();
	if (proc.initialize() != 0) {
		wxMessageBox(wxT("Hello World!"));

		return true;
	}

	videoPanel = new VideoPanel(frame);
	videoPanel->setVideo(proc);

	return true;
}