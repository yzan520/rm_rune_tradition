/**
 * @file parser.cpp
 * @brief
 *
 * @author zps
 * @data 2023-12-22
 */

#ifndef RUNE_DETECTOR_OPENVINO_PARSER_H
#define RUNE_DETECTOR_OPENVINO_PARSER_H

#include <Eigen/Dense>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include <rune_detector/interface.h>

namespace rune_auto_aim::inference_parser {
    struct GridAndStride {
        int grid0;
        int grid1;
        int stride;
    };

    static constexpr int k_NumberClassification = 2;
    static constexpr int k_NumberColor = 2;
    static constexpr int k_InferenceResultPollMaxVal = 128;
    static constexpr float k_NmsThreshold  = 0.1f;
    static constexpr float k_BoundBoxConfidenceThreshold = 0.6f;
    static constexpr float k_MergeConfidenceError = 0.15f;
    static constexpr float k_UseToMeanIouThreshold = 0.2f;


    /**
     * @brief 调整图像并设置变换矩阵
     *
     * @param src [in]
     * @param transformation_matrix [out]
     * @return 调整大小之后的图像
     */
    cv::Mat scaledResize(const cv::Mat& src, Eigen::Matrix<float, 3, 3>* transformation_matrix);


    /**
     * @brief 生成用来解析的网格和步长
     *
     * @param target_w [in] 模型的输入宽高
     * @param target_h [in]
     * @param strides [in] 步长
     * @param grid_strides [out] 结果
     */
    void generateGridsAndStride(const int& target_w, const int& target_h, const std::vector<int>& strides,
                            std::vector<GridAndStride>* grid_strides);


    /**
     *
     * @param grid_strides
     * @param inference_result_ptr [in] 推理结果的指针
     * @param transform_matrix [in]
     * @param probability_confidence_threshold [in] 推理输出的边框的概率的阈值
     * @param inference_runes [out]
     */
    void generateYoloxProposals(const std::vector<GridAndStride>& grid_strides, const float* inference_result_ptr,
                                const Eigen::Matrix<float,3,3>& transform_matrix,const float& probability_confidence_threshold,
                                std::vector<InferenceResult>* inference_runes);


    /**
     *
     * @param faceobjects
     * @param left
     * @param right
     */
    static void qsort_descent_inplace(std::vector<InferenceResult>& faceobjects, int left, int right);

    /**
     *
     * @param faceobjects
     * @param picked
     * @param nms_threshold
     */
    static void nms_sorted_bboxes (std::vector<InferenceResult>& faceobjects, std::vector<int>& picked,
                                   float nms_threshold);


    /**
     * @brief 解析推理结果
     *
     * @param inference_result_ptr [in] 推理结果
     * @param img_w [in] 原始src的宽高
     * @param img_h [in]
     * @param transform_matrix [in] 变换矩阵
     * @param inference_armors [out] 对象
     */
    void decodeOutputs(const float* inference_result_ptr, const int& img_w, const int& img_h, const Eigen::Matrix<float, 3, 3>& transform_matrix,
                       std::vector<InferenceResult>& inference_runes);

}

#endif //RUNE_DETECTOR_OPENVINO_PARSER_H
