#pragma once
#include <wx/wx.h>

class VideoPanel : public wxPanel {

public:
	VideoPanel(wxFrame* parent);
	
	void paintEvent(wxPaintEvent &event);
	void paint();
	void render(wxDC &dc);
	void OnTimer(wxTimerEvent &event);

};