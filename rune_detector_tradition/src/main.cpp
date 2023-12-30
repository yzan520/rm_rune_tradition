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

#include <detector_rune/detector_rune.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <glog/logging.h>

std::string filename = "/home/zps/Videos/rune.avi";
cv::Mat frame_src;

int main() {
    cv::VideoCapture video(filename);
	int frame_width = video.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = video.get(cv::CAP_PROP_FRAME_HEIGHT);
    double fps = video.get(cv::CAP_PROP_FPS);
    cv::VideoWriter writer("/home/zps/Videos/result.avi", video.get(cv::CAP_PROP_FOURCC), fps, cv::Size(frame_width, frame_height), true);
    while (video.read(frame_src)) {
        if (frame_src.empty() || frame_src.channels() != 3) {
            std::cout << "视频播放结束" << std::endl;
            break;
        }
        cv::resize(frame_src, frame_src, cv::Size(640, 480));
        cv::cvtColor(frame_src, frame_src, cv::COLOR_BGR2RGB);
        cv::imshow("src", frame_src);

        Detector rune;
        cv::Point2f R_center = rune.find_R(frame_src);
        cv::Point2f fan_center = rune.find_Fan(frame_src);
        cv::Mat result = rune.find_Target(frame_src, R_center, fan_center);
//        cv::imshow("result1", result);
//        writer.write(result);

        cv::waitKey(0);
//        if (cv::waitKey(30) == 'q') {
//            break;
//        }
    }
    video.release();
    writer.release();
    cv::destroyAllWindows();
    return 0;
}
