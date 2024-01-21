//
// Created by zps on 23-12-17.
//

#ifndef RM_RUNE_DETECTION_DETECTOR_RUNE_H
#define RM_RUNE_DETECTION_DETECTOR_RUNE_H

#include <opencv2/opencv.hpp>
#include <Eigen/Dense>

#include <serial_port/VCOMCOMM.h>
#include <serial_port/communicate_protocol.h>


class Detector {
public:

    /**
     * @brief 找R标
     * @param frame_src [in]
     */
    void find_R(const cv::Mat & frame_src);

    /**
     * @brief 找扇叶
     * @param frame_src [in]
     */
    void find_Leaf(const cv::Mat & frame_src);

    /**
     * @brief 找小臂
     * @param frame_src
     */
    void find_Arm(const cv::Mat & frame_src); // 已弃用 -- 寻找小臂

    /**
     * @brief 找击打点
     * @param frame
     * @return
     */
    cv::Mat find_Target(const cv::Mat & frame); // 已弃用--寻找击打点与上函数配套使用


    /**
     * @brief 画出旋转矩形，注意：要画的旋转矩形必须是从传入的图像中找到的，不能画roi的旋转矩形，即使该roi图像中也包含要画的旋转矩形
     * @param img [in]
     * @param rect [in]
     * @param color [in]
     * @param thickness [in]
     */
    void drawRotatedRect(cv::Mat & img, const cv::RotatedRect & rect, const cv::Scalar & color, int thickness);

    /**
     * @brief 测两点间的距离
     * @param a 第一个点
     * @param b 第二个点
     * @return 两点间距离
     */
    float distance(cv::Point a, cv::Point b);

    void translatoin2YawPitch(const Eigen::Vector3d& translation);

private:
#ifdef DEBUG
    // FIXME R标相关变量 -- 视频
    int R_thresholdValue = 200; // R标二值化阈值
    double max_R_area = 300; // R标最大面积
    double min_R_area = 200 ; // R标最小面积
    float min_R_ratio = 0.5;
    float max_R_ratio = 1.6;
    cv::Mat frame_R_binary; // R标二值化图像
    cv::Point2f center; // R外接圆中心坐标
    float radius; // R外接圆半径
#else
    // FIXME R标相关变量 -- 投影
    int R_thresholdValue = 90; // R标二值化阈值
    double max_R_area = 200; // R标最大面积
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

#ifdef DEBUG
    // FIXME 小臂相关变量 -- 视频
    int arm_thresholdValue = 90;
    float min_arm_area = 7400;
    float max_arm_area = 9500;
    float min_arm_ratio = 0.7;
    float max_arm_ratio = 2.0;
    cv::Point2f vertex_arm[4];
    std::vector<cv::Point2f> key_points; // 小臂旋转矩形的四个顶点
    cv::Moments rect;
    cv::Point2f rectmid;
#else
    // FIXME 小臂相关变量 -- 投影
    int arm_thresholdValue = 0;
    float min_arm_area;
    float max_arm_area;
    float min_arm_ratio;
    float max_arm_ratio;
    cv::Point2f vertex_arm[4];
    std::vector<cv::Point2f> key_points; // 小臂旋转矩形的四个顶点
    cv::Moments rect;
    cv::Point2f rectmid;
#endif

    int arm_width = 0;
    int arm_height = 0;
    std::vector<cv::Point3f> objects_points; // 物体坐标
    cv::Mat rvec; // 旋转矩阵
    cv::Mat tvec; // 平移矩阵
    Eigen::Vector3d transslation_vector;

    cv::Mat cameraMatrix = (cv::Mat_<float> (3, 3) << 2665.005527408399, 0,                 696.8233,
                                                                 0,                 2673.364537791387, 500.5147099572225,
                                                                 0,                 0,                 1);

    cv::Mat distCoeffs = (cv::Mat_<float>(1, 5) << -0.303608974614145, 4.163247825941419, -0.008432853056627, -0.003830248744148, 0);

    float yaw{};
    float pitch{};


};


#endif //RM_RUNE_DETECTION_DETECTOR_RUNE_H
