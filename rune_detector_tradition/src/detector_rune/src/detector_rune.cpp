//
// Created by zps on 23-12-17.
//

#include <detector_rune/detector_rune.h>
#include <vector>

#include <opencv2/opencv.hpp>
#include <Eigen/Dense>
#include <fmt/color.h>

void Detector::find_R(const cv::Mat& frame_src) {
    cv::Mat test_R; // 用于寻找R标中心点的测试图像
    frame_src.copyTo(test_R);

    // Split the src into three channels
    std::vector<cv::Mat> channels;
    cv::split(frame_src, channels);

//    cv::Mat frame_diff;
//    cv::subtract(channels[0], channels[2], frame_diff);
//    cv::imshow("diff", frame_diff);

    cv::Mat frame_blue;
    // 获取蓝色通道图像(灰度图),数值为BGR->RGB前的红色通道的数值
    channels[0].copyTo(frame_blue);
    cv::imshow("blue", frame_blue);

    // Threshold the image 二值化
    cv::threshold(frame_blue, frame_R_binary, R_thresholdValue, 255, cv::THRESH_BINARY);

    // Close morphological operation 闭运算->填充小型空洞
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(frame_R_binary, frame_R_binary, cv::MORPH_CLOSE, kernel);
    cv::imshow("binary_R", frame_R_binary);


    // Find and Draw all contours
    std::vector<std::vector<cv::Point> > R_contours;
    std::vector<cv::Vec4i> R_hierarchies;
    cv::findContours(frame_R_binary, R_contours, R_hierarchies, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    cv::drawContours(test_R, R_contours, -1, cv::Scalar(0, 0, 255), 2, 8); // 画出所有轮廓--红色

    std::vector<cv::RotatedRect> R_rects;
    for (const auto& contour : R_contours) {
        // Approximate the contour
        auto rect = cv::minAreaRect(contour);
//        cv::putText(test_R, std::to_string(rect.size.area()), rect.center, cv::FONT_HERSHEY_SIMPLEX, 0.5,
//                    cv::Scalar(185, 11, 219), 2); // 显示出所有轮廓的面积--紫色
//        // Use area to check if the contour is the R_contour or not
        if (rect.size.area() < max_R_area) {
            // Use ratio to check if the contour is part of the rune
            float R_ratio = rect.size.width > rect.size.height ? rect.size.width / rect.size.height
                                                             : rect.size.height / rect.size.width;
            std::cout << R_ratio << std::endl;
//            cv::putText(test_R, std::to_string(rect.size.area()), rect.center, cv::FONT_HERSHEY_SIMPLEX, 0.5,
//                        cv::Scalar(5, 240, 240), 2); // 满足最大面积的限制条件的轮廓--黄色

            if (min_R_ratio < R_ratio && R_ratio < max_R_ratio && rect.size.area() > min_R_area) {
                cv::putText(test_R, std::to_string(rect.size.area()), rect.center, cv::FONT_HERSHEY_SIMPLEX, 0.5,
                            cv::Scalar(0, 255, 0), 2); // 满足所有限制条件的轮廓--绿色--target
                R_rects.emplace_back(rect);
                cv::minEnclosingCircle(contour, center, radius);
                // TODO 只有一个符合条件的圆才能用 会误识别到矿石点的发光处（加上距离限制）
                cv::circle(test_R, center, int(radius), cv::Scalar(0, 255, 0), 2, 8, 0);
            }
        }
    }
    cv::imshow("video_R", test_R);
}

void Detector::find_Leaf(const cv::Mat &frame_src) {
    cv::Mat test_leaf;
    frame_src.copyTo(test_leaf);
    std::vector<cv::Mat> channels;
    cv::split(frame_src, channels);

    cv::Mat frame_blue;
    cv::Mat frame_red; // 寻找关键点
    channels[0].copyTo(frame_blue);
    channels[2].copyTo(frame_red);
    cv::imshow("blue", frame_blue);
//    cv::imshow("red", frame_red);

    //----------------------------------------------Step2.寻找臂---------------------------------------------------------
    // 二值化
    cv::Mat frame_leaf_binary;
    cv::threshold(frame_blue, frame_leaf_binary,    leaf_blue_thresholdValue, 255, cv::THRESH_BINARY);

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::Mat kernel1 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
    // 闭运算，关闭小空洞或小裂缝
    cv::morphologyEx(frame_leaf_binary, frame_leaf_binary, cv::MORPH_CLOSE, kernel1);
//    cv::imshow("binary_leaf_blue", frame_leaf_binary);

    // Find and Draw all contours
    std::vector<std::vector<cv::Point> > leaf_contours;
    std::vector<cv::Vec4i> leaf_hierarchies;
    cv::findContours(frame_leaf_binary, leaf_contours, leaf_hierarchies, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    cv::drawContours(test_leaf, leaf_contours, -1, cv::Scalar(0, 0 ,255), 2, 8); // 画出所有轮廓

    std::vector<cv::RotatedRect> leaf_rects;
    for (int i = 0; i < leaf_contours.size(); i++) {
        auto const& contour = leaf_contours[i];
        // Approximate the contour
        leaf_rect = cv::minAreaRect(contour);
//        cv::putText(test_leaf, std::to_string(rect.size.area()), rect.center, cv::FONT_HERSHEY_SIMPLEX, 0.5,
//                    cv::Scalar(185, 11, 219), 2); // 显示出所有轮廓的面积--紫色
        if (leaf_rect.size.area() > leaf_minsize) {
            float leaf_ratio = leaf_rect.size.width > leaf_rect.size.height ? leaf_rect.size.width / leaf_rect.size.height
                            : leaf_rect.size.height / leaf_rect.size.width;
            std::cout << leaf_ratio << std::endl;
            cv::putText(test_leaf, std::to_string(leaf_rect.size.area()), leaf_rect.center, cv::FONT_HERSHEY_SIMPLEX, 0.5,
                        cv::Scalar(5, 240, 240), 2); // 满足最大面积的限制条件的轮廓--黄色
            if (leaf_min_ratio < leaf_ratio && leaf_ratio < leaf_max_ratio && leaf_rect.size.area() < leaf_maxsize) {
                cv::putText(test_leaf, std::to_string(leaf_rect.size.area()), leaf_rect.center, cv::FONT_HERSHEY_SIMPLEX, 0.5,
                            cv::Scalar(191, 242, 7), 2); // 满足最大面积和比例的限制条件的轮廓--青色--target
                if (leaf_hierarchies[i][3] <=0 && leaf_hierarchies[i][2] <= 0) {
                    leaf_rects.emplace_back(leaf_rect);
                    drawRotatedRect(test_leaf, leaf_rect, cv::Scalar(0, 255, 0), 1);
                    cv::putText(test_leaf, std::to_string(leaf_rect.size.area()), leaf_rect.center, cv::FONT_HERSHEY_SIMPLEX, 0.5,
                            cv::Scalar(0, 255, 0), 2); // 满足所有的限制条件的轮廓--绿色--target

                    // ----------------------------------Step3 获取roi-------------------------------------------------
                    cv::Mat test_roi; // 用来测试roi图像
                    frame_src.copyTo(test_roi);
                    cv::Point2f vertices_roi[4];
                    leaf_rect.points(vertices_roi);
                    // 防止roi图像越界
                    if (vertices_roi[0].x > 0 && vertices_roi[0].y > 0 && vertices_roi[1].x > 0 && vertices_roi[1].y > 0 &&
                        vertices_roi[2].x > 0 && vertices_roi[2].y > 0 && vertices_roi[3].x > 0 && vertices_roi[3].y > 0) {

                        cv::Point2f upper_Left = vertices_roi[0]; // 左上角
                        cv::Point2f upper_Right = vertices_roi[1]; // 右上角
                        cv::Point2f lower_Right = vertices_roi[2]; // 右下角
                        cv::Point2f lower_Left = vertices_roi[3]; // 左下角

                        cv::Rect boundingRectangle = leaf_rect.boundingRect();
                        roi = frame_red(boundingRectangle); // 灰度图的roi图像
                        roi_src = frame_src(boundingRectangle); // 原图的roi图像
                        cv::imshow("roi", roi);
                        // --------------------------------Step4 寻找关键点----------------------------------------------
                        cv::Mat roi_binary;
                        cv::threshold(roi, roi_binary, 100, 255, cv::THRESH_BINARY);
                        cv::Mat kernel2 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
                        // 膨胀使臂与inrects相连,区分大矩形和小矩形
                        cv::dilate(roi_binary, roi_binary, kernel2);
                        cv::imshow("roi_binary_", roi_binary);
                        // 开运算，消除小白点
                        cv::morphologyEx(roi_binary, roi_binary, cv::MORPH_OPEN, kernel1);
                        cv::imshow("roi_binary", roi_binary);

                        std::vector<std::vector<cv::Point> > roi_contours;
                        std::vector<cv::Vec4i> roi_hierarchies;
                        cv::findContours(roi_binary, roi_contours, roi_hierarchies, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
                        cv::drawContours(roi_src, roi_contours, -1, cv::Scalar(0, 0, 255), 2, 8);

                        std::vector<cv::RotatedRect> rrect_in;
                        std::vector<cv::RotatedRect> rrect_out;
                        for (auto& roi_contour : roi_contours) {
                            auto roi_rects = cv::minAreaRect(roi_contour);
//                            cv::putText(roi_src, std::to_string(roi_rects.size.area()), roi_rects.center, cv::FONT_HERSHEY_SIMPLEX, 0.5,
//                                    cv::Scalar(185, 11, 219), 2); // 显示出所有轮廓的面积--紫色
                            // 一共两个矩形， 一个大的一个小的
                            if (roi_rects.size.area() < small_rects_maxArea && roi_rects.size.area() > small_rects_minArea) {
                                cv::putText(roi_src, std::to_string(roi_rects.size.area()), roi_rects.center, cv::FONT_HERSHEY_SIMPLEX, 0.5,
                                            cv::Scalar(0, 0, 255), 2); // 小的--红色
                                rrect_out.emplace_back(roi_rects);
//                                cv::Point2f vertices_roi_small[4];
//                                roi_rects.points(vertices_roi_small);
//
//                                // 左上角
//                                cv::Point2f upper_left_out = vertices_roi_small[0];
//                                float x_upper_left = upper_Left.x + upper_left_out.x;
//                                float y_upper_left = upper_Left.y + upper_left_out.y;
//                                cv::Point2f vertex_upper_left(x_upper_left, y_upper_left);
//
//                                // 右上角
//                                cv::Point2f upper_right_out = vertices_roi_small[1];
//                                float x_upper_right = upper_Right.x + upper_right_out.x;
//                                float y_upper_right = upper_Right.y + upper_left_out.y;
//                                cv::Point2f vertex_upper_right(x_upper_right, y_upper_right);
//
//                                // 右下角
//                                cv::Point2f lower_right_out = vertices_roi_small[2];
//                                float x_lower_right = lower_Right.x + lower_right_out.x;
//                                float y_lower_right = lower_Right.y + lower_right_out.y;
//                                cv::Point2f vertex_lower_right(x_upper_right, y_upper_right);
//
//                                // 左下角
//                                cv::Point2f lower_left_out = vertices_roi_small[3];
//                                float x_lower_left = lower_Left.x + lower_left_out.x;
//                                float y_lower_left = lower_Left.y + lower_left_out.y;
//                                cv::Point2f vertex_lower_left(x_upper_right, y_upper_right);

//                                cv::line(test_roi, vertex_upper_left, vertex_upper_right, cv::Scalar(0, 0, 255),1);
//                                cv::line(test_roi, vertex_upper_right, vertex_lower_right, cv::Scalar(0, 0, 255),1);
//                                cv::line(test_roi, vertex_lower_right, vertex_lower_left, cv::Scalar(0, 0, 255),1);
//                                cv::line(test_roi, vertex_lower_left, vertex_upper_left, cv::Scalar(0, 0, 255),1);
                            }

                            if (roi_rects.size.area() < big_rects_maxArea && roi_rects.size.area() > big_rects_minArea) {
                                rrect_in.emplace_back(roi_rects);
                                cv::putText(roi_src, std::to_string(roi_rects.size.area()), roi_rects.center, cv::FONT_HERSHEY_SIMPLEX, 0.5,
                                            cv::Scalar(0, 255, 0), 2); // 大的--绿色
                            }
                            if (rrect_in.size() == 1 && rrect_out.size() == 1) {
                                std::cout << "aksldfhj" << std::endl;
                                cv::RotatedRect rect_in = rrect_in[0];
                                cv::RotatedRect rect_out = rrect_out[0];

                                // 找小矩形的两个关键点,将小矩形的四个点的坐标映射回原图像的坐标，再求这四个点与R标的距离，找出距离较小的两个点
                                cv::Point2f vertices_small[4];
                                rect_out.points(vertices_small);
                            }
                            cv::imshow("roi_src", roi_src);
                        }
                    }
                }
            }
        }
    }
    cv::imshow("test_leaf", test_leaf);
}


// 已弃用
/* void Detector::find_Arm(const cv::Mat& frame_src) {
    cv::Mat test_arm; // 用于寻找扇叶的测试图像
    frame_src.copyTo(test_arm);

    std::vector<cv::Mat> channels;
    cv::split(frame_src, channels);
    cv::Mat arm_red;
    channels[2].copyTo(arm_red);
    cv::imshow("red", arm_red);

    // Threshold the image 二值化
    cv::threshold(arm_red, frame_arm_binary, arm_thresholdValue, 255, cv::THRESH_BINARY);
    // 开运算，消除白点，平滑物体边界
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::Mat kernel1 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
    cv::morphologyEx(frame_arm_binary, frame_arm_binary, cv::MORPH_OPEN, kernel);
    // 膨胀->增大图像中的白色区域
    cv::dilate(frame_arm_binary,frame_arm_binary,kernel1);
    cv::imshow("binary_arm", frame_arm_binary);


    std::vector<std::vector<cv::Point>> arm_contours;
    std::vector<cv::Vec4i> arm_hierarchies;
    cv::findContours(frame_arm_binary, arm_contours, arm_hierarchies, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    cv::drawContours(test_arm, arm_contours, -1, cv::Scalar(0, 0, 255), 2, 8); // 画出所有轮廓--红色

    std::vector<cv::RotatedRect> arm_rects;
    for (int i = 0; i < arm_contours.size(); i++) {
        auto const& contour = arm_contours[i];
        // Approximate the contour
        auto arm_rect = cv::minAreaRect(contour);
        cv::putText(test_arm, std::to_string(arm_rect.size.area()), arm_rect.center, cv::FONT_HERSHEY_SIMPLEX, 0.5,
                    cv::Scalar(185, 11, 219), 2); // 找出所有轮廓--紫色
        // Use area to check if the contour is the arm_contour or not
        if (arm_rect.size.area() > min_arm_area) {
            // Use area to check if the contour is the leaf_contour or not
            float arm_ratio =arm_rect.size.width > arm_rect.size.height ? arm_rect.size.width / arm_rect.size.height
                                                                          : arm_rect.size.height / arm_rect.size.width;
            cv::putText(test_arm, std::to_string(arm_rect.size.area()), arm_rect.center, cv::FONT_HERSHEY_SIMPLEX,
                        0.5,cv::Scalar(5, 240, 240), 2); // 满足最小面积的限制条件的轮廓--黄色
            if (min_arm_ratio < arm_ratio && arm_ratio < max_arm_ratio && arm_rect.size.area() < max_arm_area) {
                cv::putText(test_arm, std::to_string(arm_rect.size.area()), arm_rect.center, cv::FONT_HERSHEY_SIMPLEX, 0.5,
                            cv::Scalar(191, 242, 7), 2); // 满足最大面积和比例的限制条件的轮廓--青色--target
                if (arm_hierarchies[i][3] <= 0 && arm_hierarchies[i][2] <= 0) { // 没有父轮廓也没有子轮廓
                    arm_rects.emplace_back(arm_rect);
                    drawRotatedRect(test_arm, arm_rect, cv::Scalar(0, 255, 0), 1);
                    cv::putText(test_arm, std::to_string(arm_rect.size.area()), arm_rect.center, cv::FONT_HERSHEY_SIMPLEX, 0.5,
                            cv::Scalar(0, 255, 0), 2); // 满足所有的限制条件的轮廓--绿色--target
                    // 计算矩
                    rect = cv::moments(contour, false);
                    // 计算中心矩
                    rectmid = cv::Point2d(rect.m10 / rect.m00 , rect.m01 / rect.m00);
                    cv::circle(test_arm, rectmid, 3, cv::Scalar(255, 0, 0), 2, 8, 0);
                }
            }
        }
    }
    cv::imshow("video_arm", test_arm);
} */


/* cv::Mat Detector::find_Target(const cv::Mat &frame) {
    cv::Mat result; // 用于寻找击打点的测试图像
    frame.copyTo(result);
    cv::Point2f target; // 目标点
    double multiple = 1.5; // 倍率，换算目标点所用

    // First quadrant
    if (rectmid.x >= center.x && rectmid.y <= center.y)
        target = cv::Point2d(center.x + (rectmid.x - center.x) * multiple, center.y - (center.y - rectmid.y) * multiple);
    // Second quadrant
    if (rectmid.x <= center.x && rectmid.y <= center.y)
		target = cv::Point2d(center.x - (center.x - rectmid.x) * multiple, center.y - (center.y - rectmid.y) * multiple);
    // Third quadrant
    if (rectmid.x <= center.x && rectmid.y >= center.y)
        target = cv::Point2d(center.x - (center.x - rectmid.x) * multiple, center.y + (rectmid.y - center.y) * multiple);
    // Fourth Quadrant
    if (rectmid.x >= center.x && rectmid.y >= center.y)
        target = cv::Point2d(center.x + (rectmid.x - center.x) * multiple, center.y + (rectmid.y - center.y) * multiple);

    fmt::print(fmt::fg(fmt::color::blue) | fmt::emphasis::bold, "预测前的击打点({},{})\n", target.x, target.y);
    cv::circle(result, target, 5, cv::Scalar(0, 0, 255 ), 2, 8, 0); //画出预测前的击打点--红色
    cv::circle(result, center, int(radius), cv::Scalar(0, 255, 0), 2, 8, 0); // 画出R标

    // 画出整个圆
    float radius_ = distance(center, target);
//    cv::circle(result, center, int(radius_), cv::Scalar(0, 255, 0), 2, 8, 0);

    // 小能量机关的简单预测
    Eigen::Vector2d tar(target.x, target.y); // 目标点
    Eigen::Vector2d R_cent(center.x, center.y); // 风车中心点
    Eigen::Vector2d vector = tar - R_cent;

    double angle = -(M_PI / 3 / 30); // 帧之间的旋转角度
    Eigen::Matrix2d rotation;
    rotation << cos(angle), -sin(angle),
                sin(angle), cos(angle);
    Eigen::Vector2d rotatedPoint = rotation * vector;
    Eigen::Vector2d prediction = R_cent + rotatedPoint;

    double x = (prediction.x());
    double y = (prediction.y());
    fmt::print(fmt::fg(fmt::color::red) | fmt::emphasis::bold,
               "预测后的击打点:({},{})\n", x, y);
    cv::Point2d pre1(x, y);
    cv::circle(result, pre1, 5, cv::Scalar(0, 255, 0), 2, 8, 0); //画出预测后的击打点--绿色

    cv::putText(result, "target_before", target, cv::FONT_HERSHEY_SIMPLEX,
                        0.5,cv::Scalar(0, 0, 255), 2);
    cv::putText(result, "target_after", pre1, cv::FONT_HERSHEY_SIMPLEX,
                        0.5,cv::Scalar(0, 255, 0), 2);
    cv::imshow("result", result);
    return result;
} */

void Detector::drawRotatedRect(cv::Mat &img, const cv::RotatedRect &rect, const cv::Scalar &color, int thickness) {
    cv::Point2f Vertex[4];
    rect.points(Vertex);
    for(int i = 0 ; i < 4 ; i++) {
        cv::line(img , Vertex[i] , Vertex[(i + 1) % 4] , color , thickness);
    }
}

float Detector::distance(cv::Point a,cv::Point b) {
    return sqrt((a.x -b.x)*(a.x -b.x) + (a.y -b.y)*(a.y -b.y));
}
