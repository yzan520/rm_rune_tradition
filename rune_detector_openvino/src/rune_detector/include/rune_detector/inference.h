/**
 * @file inference.cpp
 * @brief 推理
 *
 * @author zps
 * @data 2023-12-25
 */

#ifndef RUNE_DETECTOR_OPENVINO_INFERENCE_H
#define RUNE_DETECTOR_OPENVINO_INFERENCE_H

#include <string>

#include <Eigen/Dense>
#include <openvino/openvino.hpp>

#include <rune_detector/interface.h>

namespace rune_auto_aim {
    class Inference {
    public:
        Inference() = default;

        explicit Inference(const std::string& model_path) : m_inference_result_ptr(new float) {initModel(model_path);}

        void initModel(const std::string& model_path);

        bool inference(const cv::Mat& src, std::vector<InferenceResult>* inference_runes);

        static constexpr int INPUT_WIDTH = 416;
        static constexpr int INPUT_HEIGHT = 416;

    private:
        ov::Core m_core;
        std::shared_ptr<ov::Model> m_model;
        ov::CompiledModel m_compiled_model;
        float* m_inference_result_ptr{};
        ov::InferRequest m_infer_request;
        Eigen::Matrix<float, 3, 3> m_transformation_matrix;

        const std::string m_MODEL_PATH = "../../model/buff.xml";
        const std::string m_DRIVER = "CPU"; // FIXME: driver To GPU
        const std::string m_CACHE_DIR = "../.cache";
};
} // rune_auto_aim

#endif //RUNE_DETECTOR_OPENVINO_INFERENCE_H
