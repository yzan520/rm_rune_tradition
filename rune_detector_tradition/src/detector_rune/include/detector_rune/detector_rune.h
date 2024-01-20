//
// Created by zps on 23-12-17.
//

#ifndef RM_RUNE_DETECTION_DETECTOR_RUNE_H
#define RM_RUNE_DETECTION_DETECTOR_RUNE_H


#include <opencv2/opencv.hpp>

class Detector {
public:

    void find_R(const cv::Mat & frame_src);

    // 已弃用
    void find_Arm(const cv::Mat & frame_src);

    void find_Leaf(const cv::Mat & frame_src);

    cv::Mat find_Target(const cv::Mat & frame);

    void drawRotatedRect(cv::Mat & img, const cv::RotatedRect & rect, const cv::Scalar & color, int thickness);

    void drawRotatedRect(cv::Mat & img, const cv::RotatedRect & roi, const cv::RotatedRect & rect,  cv::Scalar & color, int thickness);

    float distance(cv::Point a, cv::Point b);

private:
#ifdef DEBUG
    // FIXME R标相关变量 -- 视频
    double max_R_area = 300; // R标最大面积
    double min_R_area = 200 ; // R标最小面积
    float min_R_ratio = 0.5;
    float max_R_ratio = 1.6;
    int R_thresholdValue = 200; // R标二值化阈值
    cv::Mat frame_R_binary; // R标二值化图像
    cv::Point2f center; // R外接圆中心坐标
    float radius; // R外接圆半径
#else
    // FIXME R标相关变量 -- 投影
    double max_R_area = 200; // R标最大面积
    int R_thresholdValue = 90; // R标二值化阈值
    double min_R_area = 70; // R标最小面积
    float min_R_ratio = 0.5;
    float max_R_ratio = 1.6;
    cv::Mat frame_R_binary; // R标二值化图像
    cv::Point2f center; // R外接圆中心坐标
    float radius; // R外接圆半径
#endif

#ifdef DEBUG
    // FIXME 扇叶相关变量 -- 视频
    int leaf_blue_thresholdValue = 140;
    float leaf_minsize = 10000;
    float leaf_maxsize = 17000;
    float leaf_min_ratio = 1.4;
    float leaf_max_ratio = 2.7;
    cv::RotatedRect leaf_rect;
    cv::Mat roi;
    cv::Mat roi_src;
    std::vector<cv::Point2f> k_points; // 存储关键点
    int small_rects_minArea = 1500, small_rects_maxArea = 2500;
    int big_rects_minArea = 6500, big_rects_maxArea = 8000;

#else
    // FIXME 扇叶相关变量 -- 投影
    int leaf_blue_thresholdValue = 140;
    float leaf_minsize = 10000;
    float leaf_maxsize = 17000;
    float leaf_min_ratio = 1.4;
    float leaf_max_ratio = 2.7;
    cv::RotatedRect leaf_rect;
    cv::Mat roi;
    cv::Mat roi_src;
    std::vector<cv::Point2f> k_points; // 存储关键点
    int small_rects_minArea = 1500, small_rects_maxArea = 2500;
    int big_rects_minArea = 6500, big_rects_maxArea = 8000;
#endif
};


#endif //RM_RUNE_DETECTION_DETECTOR_RUNE_H
