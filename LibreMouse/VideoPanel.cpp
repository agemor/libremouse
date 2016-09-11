#include "VideoPanel.h"

#define TIMER_ID 1000

BEGIN_EVENT_TABLE(VideoPanel, wxPanel)
EVT_PAINT(VideoPanel::onPaint)
EVT_TIMER(TIMER_ID, VideoPanel::onTimer)
END_EVENT_TABLE()

VideoPanel::VideoPanel(wxFrame* parent) : wxPanel(parent), timer(this, TIMER_ID) {
	timer.Start(1000 / 36);
}

void VideoPanel::onTimer(wxTimerEvent &event) {

	if (!videoSet)
		return;

	if (!video.isInitialized())
		return;

	image = convertToWxForm(video.getImage());

	paint();
}

wxBitmap VideoPanel::convertToWxForm(Mat &image) {
	Mat rgbMat;
	if (image.channels() == 3)
		cv::cvtColor(image, rgbMat, CV_BGR2RGB);

	wxImage temp = wxImage(rgbMat.cols, rgbMat.rows, rgbMat.data, TRUE);
	return wxBitmap(temp);
}

void VideoPanel::onPaint(wxPaintEvent &evt) {
	wxPaintDC dc(this);
	render(dc);
}

void VideoPanel::paint() {
	wxClientDC dc(this);
	render(dc);
}

void VideoPanel::render(wxDC &dc) {
	dc.DrawBitmap(image, 0, 0, false);
}

void VideoPanel::setVideo(VideoProcessor &processor) {
	video = processor;
	videoSet = true;
}

VideoProcessor VideoPanel::getVideo() {
	return video;
}