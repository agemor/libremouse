#include "VideoPanel.h"

VideoPanel::VideoPanel(wxFrame* parent) : wxPanel(parent) {}

void VideoPanel::updateFrame(cv::Mat& frame, int width, int height) {

	wxBitmap image;

	if (frame.cols != width || frame.rows != height) {
		cv::Mat resized;
		cv::resize(frame, resized, cv::Size(width, height));
		image = convertToWxForm(resized);
	}
	else {
		image = convertToWxForm(frame);
	}

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