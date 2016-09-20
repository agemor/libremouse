#include "LibreMouse.h"

#define TIMER_ID 100

IMPLEMENT_APP(LibreMouse)
BEGIN_EVENT_TABLE(LibreMouse, wxApp)
	EVT_TIMER(TIMER_ID, LibreMouse::onTimer)
END_EVENT_TABLE()

LibreMouse::LibreMouse() : timer(this, TIMER_ID) { }

bool LibreMouse::OnInit() {

	//AllocConsole();
	//freopen("CONOUT$", "w", stdout);

	wxInitAllImageHandlers();

	menuBar = new wxMenuBar();
	helpMenu = new wxMenu();
	helpMenu->Append(wxID_ABOUT, _T("&About"));
	menuBar->Append(helpMenu, _T("&Help"));

	frame = new wxFrame((wxFrame*)NULL, -1, _T("LibreMouse"));
	frame->CreateStatusBar();
	frame->Show(true);
	frame->SetSize(wxRect(0, 0, 640, 480), 2);
	frame->SetWindowStyle(wxDEFAULT_FRAME_STYLE ^ wxMAXIMIZE_BOX ^ wxMINIMIZE_BOX);
	frame->SetMenuBar(menuBar);

	frame->Bind(wxEVT_MENU, [](wxCommandEvent & evt)->void {
		wxMessageBox("LibreMouse\n\nCopyright (c) HyunJun Kim and contributors.\nThis is free software.\nVersion 1.0.0", "About", wxOK | wxICON_INFORMATION);
	}, wxID_ABOUT);

	SetTopWindow(frame);
	
	videoPanel = new VideoPanel(frame);

	videoProcessor.initialize();
	timer.Start(1000 / 36);
	return true;
}

void LibreMouse::onTimer(wxTimerEvent &event) {

	if (!videoProcessor.isInitialized())
		return;

	std::string statusText = "";

	if (videoProcessor.featureSelected) {
		cursorUpdater.start();
		statusText = "Tracking... Press spacebar to stop.";
	}
	else {
		cursorUpdater.stop();
		statusText = "Press spacebar to start tracking.";
	}

	if (mouseDown) {
		statusText = "Mouse down";
	}

	videoProcessor.process();

	bool mouthOpen = videoProcessor.detectMouth() > 0.2f;

	// mouse up situation
	if (mouseDown && !mouthOpen) {
		mouseDown = false;
		CursorControl::mouseUp();
	}

	// mouse down situation
	else if (!mouseDown && mouthOpen) {
		mouseDown = true;
		CursorControl::mouseDown();
	}
	
	cv::Rect2d box = videoProcessor.getBoundingBox();
	cursorUpdater.addToPath(Point2D(box.x, box.y));

	int windowWidth, windowHeight;
	frame->GetClientSize(&windowWidth, &windowHeight);
	videoPanel->updateFrame(videoProcessor.getFrame(), windowWidth, windowHeight);

	frame->SetStatusText(statusText);
}

int LibreMouse::FilterEvent(wxEvent& event) {
	if ((event.GetEventType() == wxEVT_KEY_DOWN) &&
		(((wxKeyEvent&)event).GetKeyCode() == WXK_SPACE)) {
		if (videoProcessor.featureSelected) {
			videoProcessor.dropFeature();
		}
		else {
			videoProcessor.selectFeature();
		}
		return true;
	}

	return -1;
}