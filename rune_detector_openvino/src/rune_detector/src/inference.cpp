//
// Created by zps on 23-12-22.
//

#include <opencv2/opencv.hpp>
#include <glog/logging.h>
#include <fmt/format.h>

#include <rune_detector/inference.h>
#include <rune_detector/parser.h>

namespace rune_auto_aim {
    void Inference::initModel(const std::string& model_path) {
        m_core.set_property(ov::cache_dir(m_CACHE_DIR));
        m_model = m_core.read_model(model_path);
        m_compiled_model = m_core.compile_model(m_model, m_DRIVER);
        m_infer_request = m_compiled_model.create_infer_request();
        LOG(INFO) << fmt::format("({})Model loading completed!", model_path);
    }

    bool Inference::inference(const cv::Mat &src, std::vector<InferenceResult> *inference_runes) {
        m_inference_result_ptr = nullptr;
        // 预处理 (en::pretreatment)
        cv::Mat resized_img = rune_auto_aim::inference_parser::scaledResize(src,&m_transformation_matrix);
        cv::Mat img_32f;
        cv::Mat split_img[3];
        resized_img.convertTo(img_32f, CV_32F);
        cv::split(img_32f, split_img);
        // 设置输入张量以运行推理(en: set input tensor to run inference)
        ov::Tensor input_tensor = m_infer_request.get_input_tensor();
        int offset = INPUT_WIDTH * INPUT_HEIGHT;
        for (int i = 0; i < 3; ++i)
            std::memcpy(input_tensor.data<float>() + offset * i, split_img[i].data, INPUT_WIDTH * INPUT_HEIGHT * sizeof(float));
        m_infer_request.set_input_tensor(input_tensor);
        m_infer_request.infer();
        // 解析推理结果(en: Analytic inference results)
        int src_width = src.cols;
        int src_height = src.cols;
        ov::Tensor output_tensor = m_infer_request.get_output_tensor();
        m_inference_result_ptr = output_tensor.data<float>();
        inference_parser::decodeOutputs(m_inference_result_ptr, src_width, src_height, m_transformation_matrix, inference_runes);
    }
}

