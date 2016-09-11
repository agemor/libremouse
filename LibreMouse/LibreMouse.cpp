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