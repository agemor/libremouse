#include "LibreMouse.h"
#include <windows.h>

IMPLEMENT_APP(LibreMouse);

bool LibreMouse::OnInit() {

	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	wxInitAllImageHandlers();

	frame = new wxFrame((wxFrame*)NULL, -1, _T("LibreMouse"));
	frame->CreateStatusBar();
	frame->SetStatusText(_T("Not tracking"));
	frame->Show(true);
	frame->SetSize(wxRect(0, 0, 640, 480), 2);
	SetTopWindow(frame);

	videoProcessor = new VideoProcessor();
	if (videoProcessor->initialize() != 0) {
		wxMessageBox(wxT("Hello World!"));

		return true;
	}

	videoPanel = new VideoPanel(frame);
	videoPanel->setVideo(videoProcessor);

	//std::cout << &(videoPanel->getVideo()).kuru << std::endl;
	//std::cout << &videoProcessor.kuru << std::endl;

	return true;
}

int LibreMouse::FilterEvent(wxEvent& event) {
	if ((event.GetEventType() == wxEVT_KEY_DOWN) &&
		(((wxKeyEvent&)event).GetKeyCode() == WXK_SPACE)) {
		
		videoProcessor->selectFeature();

		return true;
	}

	return -1;
}