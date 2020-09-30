#include <opencv2/opencv.hpp>
#include <iostream>
#include <unistd.h>
#include <mutex>
#include <thread>
#include <atomic>
#include <csignal>

// Globals
std::atomic<bool> g_run;

void sigstop(int a) {
    std::cout << "Interrupt signal received" << std::endl;
    g_run = false;
}

void threadFunc(cv::Mat& frame, std::mutex& lock) {
    cv::VideoCapture cap;
    // Open the default camera, use something different from 0 otherwise
    if (!cap.open("rtsp://root:admin@192.168.0.12/stream6")) {
        std::cout << "Unable to open video capture\n";
        return;
    }

    while(g_run) {
        cv::Mat f;
        cap >> f;
        if (f.empty()) {
            break; // End of video stream
        }

        lock.lock();
          frame = f;
        lock.unlock();
    }
}

int main() {
    std::mutex lock;
    cv::Mat frame;

    g_run = true;
    signal(SIGINT, 	sigstop);
    signal(SIGQUIT,	sigstop);
    signal(SIGTERM,	sigstop);

    std::thread t1(threadFunc, std::reference_wrapper<cv::Mat>(frame), std::reference_wrapper<std::mutex>(lock));

    while(g_run) {
        // Simulate heavy processing
        usleep(100000);

        lock.lock();
        cv::Mat localFrame = frame;
        lock.unlock();

        if (localFrame.empty()) {
            std::cout << "Frame is empty" << std::endl;
            continue;
        }

        cv::imshow("frame", localFrame);

        if (cv::waitKey(10) == 27) {
            break; // stop capturing by pressing ESC
        }

    }

    t1.join();
    return 0;
}