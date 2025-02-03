#include <iostream>
#include <opencv2/opencv.hpp>
#include "zenoh.hxx"
using namespace zenoh;

void listener(const Sample &sample)
{
    cv::Mat image;
    std::vector<uint8_t> buffer = sample.get_payload().as_vector();
    cv::imdecode(buffer, cv::IMREAD_COLOR, &image);
    cv::imshow("image", image);
    auto key = cv::waitKey(1);
    if (key == 'q')
    {
        exit(0);
    }
}

int main(int argc, char **argv)
{
    Config config = Config::create_default();
    auto session = Session::open(std::move(config));
    std::string key = "image";
    auto subscriber = session.declare_subscriber(KeyExpr(key.c_str()), &listener, closures::none);
    while (1)
    {
        continue;
    }
    return 0;
}
