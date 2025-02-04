#include <opencv2/opencv.hpp>
#include <iostream>

#include <chrono>
#include "zenoh.hxx"

using namespace zenoh;
using namespace std::chrono_literals;
int main()
{
    Config config = Config::create_default();
    zenoh::PosixShmProvider provider(MemoryLayout(92160, AllocAlignment({2})));
    auto session_shm = Session::open(std::move(config));

    std::string key = "image_shm";
    auto publisher_shm = session_shm.declare_publisher(KeyExpr(key.c_str()));
    cv::Mat image;
    std::vector<uint8_t> buf;
    cv::VideoCapture cap(0);

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(cv::CAP_PROP_FPS, 15);

    while (1)
    {
        if (!cap.read(image))
        {
            continue;
        }
        cv::imencode(".jpg", image, buf);
        const auto len = buf.size() + 1;
        auto alloc_result = provider.alloc_gc_defrag_blocking(len, AllocAlignment({0}));
        ZShmMut &&bufshm = std::get<ZShmMut>(std::move(alloc_result));
        std::memcpy(bufshm.data(), buf.data(), len);
        publisher_shm.put(std::move(buf));
    }
    return 0;
}
