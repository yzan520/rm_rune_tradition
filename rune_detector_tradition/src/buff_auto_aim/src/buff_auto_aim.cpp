//
// Created by zps on 24-1-6.
//

#include <memory>

#include <buff_auto_aim/buff_auto_aim.h>
#include <google_logger/google_logger.h>


namespace buff_auto_aim {
    BuffAutoAim::BuffAutoAim(QObject *parent)
            : m_hik_driver(std::make_unique<HikDriver>(0)) {
        initHikCamera();
    }

    void BuffAutoAim::run() {
        LOG(INFO) << "buff_auto_aim_thread" << QThread::currentThreadId();
        uint64_t timestamp = ProgramClock::now().time_since_epoch().count();

        while (true) {
            m_hik_frame = m_hik_driver->getFrame();
            m_frame = *m_hik_frame.getRgbFrame();
            timestamp = m_hik_frame.getTimestamp();
//            cv::resize(m_frame, m_frame, cv::Size(640, 480));
            cv::cvtColor(m_frame, m_frame, cv::COLOR_BGR2RGB);
            cv::imshow("src", m_frame);
            Detector rune;
            rune.find_R(m_frame);
            rune.find_Arm(m_frame);
//            rune.find_Leaf(m_frame);
//            rune.find_Target(m_frame);
//            cv::waitKey(0);
            if (cv::waitKey(30) == 'q') {
                break;
            }
        }
    }

    void BuffAutoAim::initHikCamera() {
        if (m_hik_driver->isConnected()) {
            m_hik_driver->setExposureTime(8000);
            m_hik_driver->setGain(11);
            m_hik_driver->showParamInfo();
            m_hik_driver->startReadThread();
//            m_hik_ui = std::make_unique<HikUi>(*m_hik_driver);
//            m_hik_ui->show();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        } else {
            LOG(FATAL) << "Hik can't connected!";
        };
    }
}

