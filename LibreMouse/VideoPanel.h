#pragma once
#include <wx/wx.h>
#include "VideoProcessor.h"
#include "CursorUpdater.h"
#include "Point2D.h"

class VideoPanel : public wxPanel {

private:
	wxBitmap convertToWxForm(cv::Mat& image);

public:
	VideoPanel(wxFrame* parent);
	void updateFrame(cv::Mat& frame);
};
