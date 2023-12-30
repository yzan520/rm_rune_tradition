//
// Created by zps on 23-12-17.
//

#ifndef RM_RUNE_DETECTION_DETECTOR_RUNE_H
#define RM_RUNE_DETECTION_DETECTOR_RUNE_H

#include <opencv2/opencv.hpp>

class Detector {
public:

    cv::Point2f find_R(const cv::Mat & frame_src);

    cv::Point2f find_Fan(const cv::Mat & frame_src);

    cv::Mat find_Target(const cv::Mat & frame, cv::Point2f R_center, cv::Point2f fan_center);

    void drawRotatedRect(cv::Mat & img, const cv::RotatedRect & rect, const cv::Scalar & color, int thickness);

    double distance(cv::Point a, cv::Point b);

private:
    // R标相关变量
    double max_R_area = 300; // R标最大面积
    double min_R_area = 200 ; // R标最小面积
    float min_R_ratio = 0.5;
    float max_R_ratio = 1.6;
    int R_thresholdValue = 200; // R标二值化阈值
    cv::Mat frame_R_binary; // R标二值化图像
    cv::Point2f center; // R外接圆中心坐标
    float radius; // R外接圆半径

    // 扇叶相关变量
    double min_fan_area = 7500; // 扇叶最小面积
    double max_fan_area = 9000; // 扇叶最大面积
    float min_fan_ratio = 0.5;
    float max_fan_ratio = 2.0;
    int fan_thresholdValue = 89; // 扇叶二值化阈值
    cv::Mat frame_fan_binary; // 扇叶二值化图像
    cv::Mat frame_fan_erode; // 扇叶腐蚀图像

};


#endif //RM_RUNE_DETECTION_DETECTOR_RUNE_H
