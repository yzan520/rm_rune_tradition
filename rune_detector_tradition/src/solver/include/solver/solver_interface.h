//
// Created by zps on 24-1-21.
//

#ifndef RM_RUNE_DETECTION_SOLVER_INTERFACE_H
#define RM_RUNE_DETECTION_SOLVER_INTERFACE_H

#include <ostream>

#include <fmt/format.h>

namespace rune_auto_aim::solver {
    struct Pose {
        float pitch;
        float yaw;
        float roll;
        float x, y, z;

        Pose() = default;

        Pose(float p, float yaw, float r, float x, float y, float z)
            : pitch(p), yaw(yaw), roll(r), x(x), y(y), z(z)
        {}

        std::string to_string() const {
            return fmt::format("x :{}; y: {}; z: {}; yaw: {}; pitch: {}; roll: {};",
                               x, y, z, yaw, pitch, roll);
        };

        friend std::ostream& operator<<(std::ostream& os, const Pose& pose) {
            os << pose.to_string();
            return os;
        }
    };
}


#endif //RM_RUNE_DETECTION_SOLVER_INTERFACE_H
