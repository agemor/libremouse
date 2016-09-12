#pragma once
#include <wx/wx.h>
#include "VideoProcessor.h"
#include "CursorUpdater.h"

class VideoPanel : public wxPanel {

private:

	VideoProcessor* video;
	CursorUpdater cursorUpdater;

	bool videoSet = false;

	wxBitmap image;
	wxTimer timer;

	wxBitmap convertToWxForm(cv::Mat& image);

	DECLARE_EVENT_TABLE()

public:
	VideoPanel(wxFrame* parent);
	
	void paint();
	void render(wxDC &dc);

	void setVideo(VideoProcessor* processor);
	VideoProcessor* getVideo();

	void onTimer(wxTimerEvent &event);

};
