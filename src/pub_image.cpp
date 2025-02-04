#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>
#include "zenoh.hxx"

using namespace zenoh;
int main()
{
    Config config = Config::create_default();
    auto session = Session::open(std::move(config));
    std::string key = "image";
    auto publisher = session.declare_publisher(KeyExpr(key.c_str()));
    cv::Mat image;
    std::vector<uint8_t> buf;
    cv::VideoCapture cap(0);

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(cv::CAP_PROP_FPS, 15);

    while (true)
    {
        if (!cap.read(image))
        {
            continue;
        }

        cv::imencode(".jpg", image, buf);
        publisher.put(std::move(buf));
        buf.clear();
    }
    return 0;
}
