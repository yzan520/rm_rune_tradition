//
// Created by zps on 23-12-17.
//

#include <detector_rune/detector_rune.h>
#include <opencv2/opencv.hpp>
#include <vector>

cv::Point2f Detector::find_R(const cv::Mat& frame_src) {
    cv::Mat test_R;
    frame_src.copyTo(test_R);
    // Split the src into three channels
    std::vector<cv::Mat> channels;
    cv::split(frame_src, channels);

//    cv::Mat frame_diff;
//    cv::subtract(channels[0], channels[2], frame_diff);
//    cv::imshow("diff", frame_diff);

    cv::Mat frame_blue;
    channels[0].copyTo(frame_blue);
//    cv::imshow("blue", frame_blue);

    // Threshold the image
    cv::threshold(frame_blue, frame_R_binary, R_thresholdValue, 255, cv::THRESH_BINARY);

    // Close morphological operation
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(frame_R_binary, frame_R_binary, cv::MORPH_CLOSE, kernel);
//    cv::imshow("binary", frame_R_binary);


    // Find and Draw all contours
    std::vector<std::vector<cv::Point> > R_contours;
    std::vector<cv::Vec4i> R_hierarchies;
    cv::findContours(frame_R_binary, R_contours, R_hierarchies, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    cv::drawContours(test_R, R_contours, -1, cv::Scalar(0, 0, 255), 2, 8); // 画出所有轮廓--红色

    std::vector<cv::RotatedRect> R_rect;
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
//            cv::putText(test_R, std::to_string(rect.size.area()), rect.center, cv::FONT_HERSHEY_SIMPLEX, 0.5,
//                        cv::Scalar(5, 240, 240), 2); // 满足最大面积的限制条件的轮廓--黄色
//
            if (min_R_ratio < R_ratio && R_ratio < max_R_ratio && rect.size.area() > min_R_area) {
                cv::putText(test_R, std::to_string(rect.size.area()), rect.center, cv::FONT_HERSHEY_SIMPLEX, 0.5,
                            cv::Scalar(0, 255, 0), 2); // 满足所有限制条件的轮廓--绿色--target
                R_rect.emplace_back(rect);
                cv::minEnclosingCircle(contour, center, radius);
                cv::circle(test_R, center, int(radius), cv::Scalar(0, 255, 0), 2, 8, 0);
                return center;
            }
        }
    }
//    cv::imshow("video_R", test_R);
}

cv::Point2f Detector::find_Fan(const cv::Mat& frame_src) {
    cv::Mat test_fan;
    frame_src.copyTo(test_fan);
    std::vector<cv::Mat> channels;
    cv::split(frame_src, channels);
    cv::Mat fan_red;
    channels[2].copyTo(fan_red);
    cv::imshow("red", fan_red);
    cv::threshold(fan_red, frame_fan_binary, fan_thresholdValue, 255, cv::THRESH_BINARY);
    // 开运算，消除小白点
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::Mat kernel1 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
    cv::morphologyEx(frame_fan_binary, frame_fan_binary, cv::MORPH_OPEN, kernel);
    cv::dilate(frame_fan_binary,frame_fan_binary,kernel1);
    cv::imshow("binary", frame_fan_binary);


    std::vector<std::vector<cv::Point>> fan_contours;
    std::vector<cv::Vec4i> fan_hierarchies;
    cv::findContours(frame_fan_binary, fan_contours, fan_hierarchies, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    cv::drawContours(test_fan, fan_contours, -1, cv::Scalar(0, 0, 255), 2, 8); // 画出所有轮廓--红色

    std::vector<cv::RotatedRect> fan_rect;
    for (int i = 0; i < fan_contours.size(); i++) {
        auto const& contour = fan_contours[i];
        // Approximate the contour
        auto fan_rects = cv::minAreaRect(contour);
//        cv::putText(test_fan, std::to_string(fan_rects.size.area()), fan_rects.center, cv::FONT_HERSHEY_SIMPLEX, 0.5,
//                    cv::Scalar(185, 11, 219), 2); // 找出所有轮廓--紫色
        // Use area to check if the contour is the fan_contour or not
        if (fan_rects.size.area() > min_fan_area) {
            // Use area to check if the contour is the leaf_contour or not
            float fan_ratio =fan_rects.size.width > fan_rects.size.height ? fan_rects.size.width / fan_rects.size.height
                                                                          : fan_rects.size.height / fan_rects.size.width;
//            cv::putText(test_fan, std::to_string(fan_rects.size.area()), fan_rects.center, cv::FONT_HERSHEY_SIMPLEX,
//                        0.5,cv::Scalar(5, 240, 240), 2); // 满足最小面积的限制条件的轮廓--黄色
            if (min_fan_ratio < fan_ratio && fan_ratio < max_fan_ratio && fan_rects.size.area() < max_fan_area) {
//                cv::putText(test_fan, std::to_string(fan_rects.size.area()), fan_rects.center, cv::FONT_HERSHEY_SIMPLEX, 0.5,
//                            cv::Scalar(191, 242, 7), 2); // 满足最大面积和比例的限制条件的轮廓--青色--target
                if (fan_hierarchies[i][3] <= 0 && fan_hierarchies[i][2] <= 0) { // 没有父轮廓也没有子轮廓
                    fan_rect.emplace_back(fan_rects);
                    drawRotatedRect(test_fan, fan_rects, cv::Scalar(0, 255, 0), 1);
                    cv::putText(test_fan, std::to_string(fan_rects.size.area()), fan_rects.center, cv::FONT_HERSHEY_SIMPLEX, 0.5,
                            cv::Scalar(0, 255, 0), 2); // 满足所有的限制条件的轮廓--绿色--target
                    // 计算矩
                    cv::Moments rect;
                    rect = cv::moments(contour, false);
                    // 计算中心矩
                    cv::Point2f rectmid;
                    rectmid = cv::Point2f(rect.m10 / rect.m00 , rect.m01 / rect.m00);
                    cv::circle(test_fan, rectmid, 3, cv::Scalar(255, 0, 0), 2, 8, 0);
                    cv::imshow("video_fan", test_fan);
                    return rectmid;
                }
            }
        }
    }
}

cv::Mat Detector::find_Target(const cv::Mat &frame, cv::Point2f R_center, cv::Point2f fan_center) {
    cv::Mat result;
    frame.copyTo(result);
    cv::Point2f target; // 目标点
    double multiple = 1.5; // 倍率，换算目标点所用

    // 第一象限
    if (fan_center.x >= R_center.x && fan_center.y <= R_center.y)
        target = cv::Point2f(R_center.x + (fan_center.x - R_center.x) * multiple, R_center.y - (R_center.y - fan_center.y) * multiple);
    // 第二象限
    if (fan_center.x <= R_center.x && fan_center.y <= R_center.y)
		target = cv::Point2f(R_center.x - (R_center.x - fan_center.x) * multiple, R_center.y - (R_center.y - fan_center.y) * multiple);
    // 第三象限
    if (fan_center.x <= R_center.x && fan_center.y >= R_center.y)
        target = cv::Point2f(R_center.x - (R_center.x - fan_center.x) * multiple, R_center.y + (fan_center.y - R_center.y) * multiple);
    // 第四象限
    if (fan_center.x >= R_center.x && fan_center.y >= R_center.y)
        target = cv::Point2f(R_center.x + (fan_center.x - R_center.x) * multiple, R_center.y + (fan_center.y - R_center.y) * multiple);
    cv::circle(result, target, 5, cv::Scalar(0, 0, 255 ), 2, 8, 0);
    cv::circle(result, R_center, int(radius), cv::Scalar(0, 255, 0), 2, 8, 0);
    float radius = distance(R_center, target);
    cv::circle(result, R_center, radius, cv::Scalar(0, 255, 0), 2, 8, 0);
    cv::putText(result, "target", target, cv::FONT_HERSHEY_SIMPLEX,
                        0.5,cv::Scalar(0, 255, 0), 2);
    cv::imshow("result", result);
    return result;
}

void Detector::drawRotatedRect(cv::Mat &img, const cv::RotatedRect &rect, const cv::Scalar &color, int thickness) {
    cv::Point2f Vertex[4];
    rect.points(Vertex);
    for(int i = 0 ; i < 4 ; i++) {
        cv::line(img , Vertex[i] , Vertex[(i + 1) % 4] , color , thickness);
    }
}

double Detector::distance(cv::Point a,cv::Point b) {
    return sqrt((a.x -b.x)*(a.x -b.x) + (a.y -b.y)*(a.y -b.y));
}
