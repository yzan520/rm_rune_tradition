/*
 *                        _oo0oo_
 *                       o8888888o
 *                       88" . "88
 *                       (| -_- |)
 *                       0\  =  /0
 *                     ___/`---'\___
 *                   .' \\|     |// '.
 *                  / \\|||  :  |||// \
 *                 / _||||| -:- |||||- \
 *                |   | \\\  - /// |   |
 *                | \_|  ''\---/''  |_/ |
 *                \  .-\__  '-'  ___/-. /
 *              ___'. .'  /--.--\  `. .'___
 *           ."" '<  `.___\_<|>_/___.' >' "".
 *          | | :  `- \`.;`\ _ /`;.`/ - ` : | |
 *          \  \ `_.   \_ __\ /__ _/   .-` /  /
 *      =====`-.____`.___ \_____/___.-`___.-'=====
 *                        `=---='
 *
 *
 *      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *            佛祖保佑       永不宕机     永无BUG
 */

#include <QApplication>
#include <QThread>

#include <google_logger/google_logger.h>
#include <buff_auto_aim/buff_auto_aim.h>

//int main(int argc, char* argv[]) {
//    armor_auto_aim::google_log::initGoogleLogger(argc, argv);
//    QApplication app(argc, argv);
//    buff_auto_aim::BuffAutoAim auto_aim_thread;
//    auto_aim_thread.start();
//    LOG(INFO) << fmt::format("main_thread: {};", QThread::currentThreadId());
//    return QApplication::exec();
//}

#include <detector_rune/detector_rune.h>

#include <iostream>
#include <opencv2/opencv.hpp>
#include <fmt/color.h>

std::string filename = "/home/zps/Videos/rune.avi";
cv::Mat frame_src;

int main() {
    cv::VideoCapture video(filename);
    int frame_width = video.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = video.get(cv::CAP_PROP_FRAME_HEIGHT);
    double fps = video.get(cv::CAP_PROP_FPS);
    fmt::print(fmt::fg(fmt::color::crimson) | fmt::emphasis::bold,
               "The frame size:({} ,{})\n", frame_width, frame_height);
    fmt::print(fmt::fg(fmt::color::crimson) | fmt::emphasis::bold,
               "The fps:{}\n", fps);
    while (video.read(frame_src)) {
        if (frame_src.empty() || frame_src.channels() != 3) {
            std::cout << "视频播放结束" << std::endl;
            break;
        }
        cv::resize(frame_src, frame_src, cv::Size(640, 480));
        // 从BGR->RGB,红色通道和蓝色通道的数值互换
        cv::cvtColor(frame_src, frame_src, cv::COLOR_BGR2RGB);
        cv::imshow("src", frame_src);

        Detector rune;
//        rune.find_R(frame_src);
        rune.find_Leaf(frame_src);
//        rune.find_Arm(frame_src);
//        cv::Mat result = rune.fin d_Target(frame_src);

        cv::waitKey(0);
//        if (cv::waitKey(30) == 'q') {
//            break;
//        }
    }
    video.release();
//    writer.release();
    cv::destroyAllWindows();
    return 0;
}
