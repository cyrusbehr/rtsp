#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
	cv::VideoCapture cap;
    if (!cap.open("rtsp://192.168.1.56/mpeg4?source=0&overlay=off")) {
        std::cout << "Unable to open video capture\n";
        return -1;
    }

    while(true) {
		cv::Mat frame;
	    cap >> frame;
	    if (frame.empty()) {
	        break; // End of video stream
	    }

	    cv::imshow("frame", frame);

	    if (cv::waitKey(10) == 27) {
	        break; // stop capturing by pressing ESC
	    }
	}
    return 0;
}