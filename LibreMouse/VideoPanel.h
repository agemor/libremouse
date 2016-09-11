#pragma once
#include <wx/wx.h>
#include "VideoProcessor.h";

class VideoPanel : public wxPanel {

private:

	VideoProcessor video;
	bool videoSet = false;

	wxBitmap image;
	wxTimer timer;

	wxBitmap convertToWxForm(Mat& image);

	DECLARE_EVENT_TABLE()

public:
	VideoPanel(wxFrame* parent);
	
	void paint();
	void render(wxDC &dc);

	void setVideo(VideoProcessor &processor);
	VideoProcessor getVideo();

	void onPaint(wxPaintEvent &event);
	void onTimer(wxTimerEvent &event);

};

