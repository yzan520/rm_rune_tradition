/**
 * @file interface.cpp
 * @brief 接口
 *
 * @author zps
 * @data 2023-12-22
 */

#ifndef RUNE_DETECTOR_OPENVINO_INTERFACE_H
#define RUNE_DETECTOR_OPENVINO_INTERFACE_H

#include <ostream>

#include <Eigen/Dense>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include <solver/solver_interface.h>

namespace rune_auto_aim {
    struct InferenceResult {
        cv::Point2f rune_apex[5];
        cv::Rect_<float> rect{};
        int classification{};
        int color{};
        float probability{};
        std::vector<cv::Point2f> points{};

        InferenceResult() = default;

        friend std::ostream& operator << (std::ostream& os, const InferenceResult& rune) {
            os << "rune_apex: ";
            for (const auto& item : rune.rune_apex)
                os << item << ";";
            os << "rect: " << rune.rect;
            os << "; classification: " << rune.classification;
            os << "; color: " << rune.color;
            os << "; probability :" << rune.probability;
            os << "; points :" << rune.points;
            return os;
        }
    };

    enum class RuneColor {BLUE, RED, UNKNOWN };

    static std::string to_string(const RuneColor& rune_color) {
        switch (rune_color) {
            case RuneColor::BLUE: return "BLUE";
            case RuneColor::RED: return "RED";
            case RuneColor::UNKNOWN: return "UNKNOWN";
        }
        return "UNKNOWN";
    }


    static std::string to_string(const std::vector<cv::Point2f>& point2f) {
        std::string result("[");
        for (int i = 0; i < point2f.size(); ++i) {
            result += fmt::format("({}, {})", point2f[i].x, point2f[i].y);
            if (i != point2f.size() - 1) result += ", ";
        }
        result += "]";
        return result;
    }
}


#endif //RUNE_DETECTOR_OPENVINO_INTERFACE_H
