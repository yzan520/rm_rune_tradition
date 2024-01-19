//
// Created by zps on 24-1-6.
//

#ifndef RM_RUNE_DETECTION_BUFF_AUTO_AIM_H
#define RM_RUNE_DETECTION_BUFF_AUTO_AIM_H

#include <iostream>
#include <chrono>

#include <QThread>

#include <HikDriver/HikDriver.h>
#include <HikDriver/HikUi.h>
#include <detector_rune/detector_rune.h>

namespace buff_auto_aim {
    struct AutoAimParms {
        float exp_time;
        float gain;
        float delta_time;
    };

    class BuffAutoAim : public QThread {
        Q_OBJECT
        using ProgramClock = std::chrono::system_clock;
        using ClockUnit = std::chrono::milliseconds;
    public:
        BuffAutoAim(QObject* parent = nullptr);
        void run() override;
    private:
        AutoAimParms m_params;
        std::unique_ptr<HikDriver> m_hik_driver;
        HikFrame m_hik_frame;
        std::unique_ptr<HikUi> m_hik_ui;
        cv::Mat m_frame;

        void loadConfig();

        void initHikCamera();

    };
}



#endif //RM_RUNE_DETECTION_BUFF_AUTO_AIM_H
