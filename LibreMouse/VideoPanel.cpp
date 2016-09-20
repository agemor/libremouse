#include "VideoPanel.h"

VideoPanel::VideoPanel(wxFrame* parent) : wxPanel(parent) {}

void VideoPanel::updateFrame(cv::Mat& frame) {
	wxBitmap image = convertToWxForm(frame);

	wxClientDC dc(this);
	dc.DrawBitmap(image, 0, 0, false);
}

wxBitmap VideoPanel::convertToWxForm(cv::Mat& bgrMat) {
	cv::Mat rgbMat;
	if (bgrMat.channels() == 3)
		cv::cvtColor(bgrMat, rgbMat, CV_BGR2RGB);

	wxImage image = wxImage(rgbMat.cols, rgbMat.rows, rgbMat.data, TRUE);
	return wxBitmap(image);
}