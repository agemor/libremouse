#include "LibreMouse.h"
#include <windows.h>

#define TIMER_ID 100

IMPLEMENT_APP(LibreMouse)
BEGIN_EVENT_TABLE(LibreMouse, wxApp)
	EVT_TIMER(TIMER_ID, LibreMouse::onTimer)
END_EVENT_TABLE()

LibreMouse::LibreMouse() : timer(this, TIMER_ID) { }

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
	
	videoPanel = new VideoPanel(frame);

	videoProcessor.initialize();
	timer.Start(1000 / 36);
	return true;
}

void LibreMouse::onTimer(wxTimerEvent &event) {

	if (!videoProcessor.isInitialized())
		return;

	if (videoProcessor.featureSelected) {
		cursorUpdater.start();
	}
	else {
		cursorUpdater.stop();
	}

	videoProcessor.process();

	if (videoProcessor.detectMouth() > 0.2f) {
		std::cout << "click" << std::endl;
	}

	cv::Rect2d box = videoProcessor.getBoundingBox();
	cursorUpdater.addToPath(Point2D(box.x, box.y));

	videoPanel->updateFrame(videoProcessor.getFrame());
}

int LibreMouse::FilterEvent(wxEvent& event) {
	if ((event.GetEventType() == wxEVT_KEY_DOWN) &&
		(((wxKeyEvent&)event).GetKeyCode() == WXK_SPACE)) {
		
		videoProcessor.selectFeature();

		return true;
	}

	return -1;
}