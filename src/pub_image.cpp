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
    while (1)
    {
        auto ret = cap.read(image);
        if (!ret)
        {
            continue;
        }
        cv::imencode(".jpg", image, buf);
        publisher.put(buf);
    }
    return 0;
}