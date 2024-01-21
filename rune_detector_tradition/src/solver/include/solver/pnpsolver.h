//
// Created by zps on 24-1-21.
//

#ifndef RM_RUNE_DETECTION_PNPSOLVER_H
#define RM_RUNE_DETECTION_PNPSOLVER_H

#include <opencv2/opencv.hpp>

#include <solver/solver_interface.h>

namespace armor_auto_aim {
class PnPSolver {
public:
    PnPSolver(const std::array<double, 9>& intrinsic_matrix,
              const std::vector<double>& distortion_vector);

private:
    // Unit: mm
    static constexpr float SMALL_ARMOR_WIDTH = 135;
    static constexpr float SMALL_ARMOR_HEIGHT = 55;
    static constexpr float LARGE_ARMOR_WIDTH = 225;
    static constexpr float LARGE_ARMOR_HEIGHT = 55;

    cv::Mat m_intrinsic_matrix;
    cv::Mat m_distortion_vector;
    std::vector<cv::Point3f> m_small_armor_point3d;
    std::vector<cv::Point3f> m_large_armor_point3d;

    inline double adjust(double angle) { return (angle < 0) ? (angle + 2 * M_PI) : angle; }
};
} // armor_auto_aim


#endif //RM_RUNE_DETECTION_PNPSOLVER_H
