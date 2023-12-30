//
// Created by zps on 23-12-22.
//

#include <thread>
#include <algorithm>
#include <cmath>

#include <rune_detector/inference.h>
#include <rune_detector/parser.h>

namespace rune_auto_aim::inference_parser {
    cv::Mat scaledResize(const cv::Mat& src, Eigen::Matrix<float, 3, 3>* transformation_matrix) {
        auto width = static_cast<float>(src.cols);
        auto height = static_cast<float>(src.rows);
        float rate = std::min(Inference::INPUT_WIDTH / width,
                              Inference::INPUT_WIDTH / height);
        int updated_w = static_cast<int>(rate * width);
        int updated_h = static_cast<int>(rate * height);
        int dw = (Inference::INPUT_WIDTH - updated_w) / 2;
        int dh = (Inference::INPUT_HEIGHT - updated_h) / 2;

        *transformation_matrix << 1.0f / rate, 0.0f,        -dw / rate,
                                  0.0f,        1.0f / rate, -dh / rate,
                                  0.0f,        0.0f,        1.0f;
        cv::Mat resized, out;
        cv::resize(src, resized, cv::Size(updated_w, updated_h));
        cv::copyMakeBorder(resized, out, dh, dh, dw, dw, cv::BORDER_CONSTANT);

        return out;
    }

    void generateGridsAndStride(const int& target_w, const int& target_h, const std::vector<int>& strides,
                            std::vector<GridAndStride>* grid_strides) {
        for (const auto& stride : strides) {
            int num_grid_w = target_w / stride;
            int num_grid_h = target_h / stride;
            for (int g1 = 0; g1 < num_grid_h; g1++) {
                for (int g0 = 0; g0 < num_grid_w ; g0++)
                    grid_strides->push_back((GridAndStride) {g0, g1, stride});
            }
        }
    }

    void generateYoloxProposals(const std::vector<GridAndStride>& grid_strides, const float* inference_result_ptr,
                                const Eigen::Matrix<float,3,3> &transform_matrix,const float& probability_confidence_threshold,
                                std::vector<InferenceResult>* inference_runes) {
        const int num_anchors = static_cast<int>(grid_strides.size());
        // Travel all the anchors
        for (int anchor_idx = 0; anchor_idx < num_anchors; anchor_idx++) {
            // 通过网格、步长、偏移获取值
            const auto grid0 = static_cast<float>(grid_strides[anchor_idx].grid0);
            const auto grid1 = static_cast<float>(grid_strides[anchor_idx].grid1);
            const auto stride = static_cast<float>(grid_strides[anchor_idx].stride);

            const int basic_pos = anchor_idx * (11 + k_NumberColor + k_NumberClassification);

            float x_1 = (inference_result_ptr[basic_pos + 0] + grid0) * stride;
            float y_1 = (inference_result_ptr[basic_pos + 1] + grid1) * stride;
            float x_2 = (inference_result_ptr[basic_pos + 2] + grid0) * stride;
            float y_2 = (inference_result_ptr[basic_pos + 3] + grid1) * stride;
            float x_3 = (inference_result_ptr[basic_pos + 4] + grid0) * stride;
            float y_3 = (inference_result_ptr[basic_pos + 5] + grid1) * stride;
            float x_4 = (inference_result_ptr[basic_pos + 6] + grid0) * stride;
            float y_4 = (inference_result_ptr[basic_pos + 7] + grid1) * stride;
            float x_5 = (inference_result_ptr[basic_pos + 8] + grid0) * stride;
            float y_5 = (inference_result_ptr[basic_pos + 9] + grid1) * stride;

            // 获取目标框概率
            auto argMax = [](const float* ptr, const int& len)->int {
                int max_arg = 0;
                for (int i = 1; i < len; i++) {
                    if (ptr[i] > ptr[max_arg])
                        max_arg = i;
                }
                return max_arg;
            };

            int box_color = argMax(inference_result_ptr + basic_pos + 11, k_NumberColor);
            int box_class = argMax(inference_result_ptr + basic_pos + 11 + k_NumberColor, k_NumberClassification);

            float box_probability = inference_result_ptr[basic_pos + 10];
            // 筛选并生成装甲板对象
            if (box_probability >= probability_confidence_threshold) {
                InferenceResult rune;
                Eigen::Matrix<float, 3, 5> tmp_apex; // 顶点
                Eigen::Matrix<float, 3, 5> rune_apex_destination; // 目标顶点

                tmp_apex << x_1, x_2, x_3, x_4, x_5,
                            y_1, y_2, y_3, y_4, y_5,
                            1,   1,   1,   1;   1;
                rune_apex_destination = transform_matrix * tmp_apex;
                for (int i = 0; i < 5; i++) {
                    rune.rune_apex[i] = cv::Point2f(rune_apex_destination(0, i), rune_apex_destination(1, i));
                    rune.points.push_back(rune.rune_apex[i]);
                }
                std::vector<cv::Point2f> tmp(rune.rune_apex, rune.rune_apex + 5);
                rune.rect = cv::boundingRect(tmp);

                rune.classification = box_class;
                rune.color = box_color;
                rune.probability = box_probability;

                inference_runes->push_back(rune);
            }
        } // point anchor loo
    }

    static void qsort_descent_inplace(std::vector<InferenceResult>& faceobjects, int left, int right) {
        int i = left;
        int j = right;
        float p = faceobjects[(left + right) / 2].probability;

        while (i <= j) {
            while (faceobjects[i].probability > p)
                i++;

            while (faceobjects[j].probability < p)
                j--;

            if (i <= j) {
                // swap
                std::swap(faceobjects[i], faceobjects[j]);

                i++;
                j--;
            }
        }

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                if (left < j) qsort_descent_inplace(faceobjects, left, j);
            }
            #pragma omp section
            {
                if (i < right) qsort_descent_inplace(faceobjects, i, right);
            }
        }
    }

    inline static void qsort_descent_inplace(std::vector<InferenceResult>& objects) {
        if (objects.empty())
            return;

        qsort_descent_inplace(objects, 0, objects.size() - 1);
    }

    static void nms_sorted_bboxes (std::vector<InferenceResult>& faceobjects, std::vector<int>& picked,
                                   float nms_threshold) {
        picked.clear();
        const int n = faceobjects.size();

        std::vector<float> areas(n);
        for (int i = 0; i < n; i++) {
            std::vector<cv::Point2f> object_apex_tmp(faceobjects[i].rune_apex, faceobjects[i].rune_apex + 5);
            areas[i] = cv::contourArea(object_apex_tmp);
        }

        for (int i = 0; i < n; i++) {
            InferenceResult& a = faceobjects[i];
            std::vector<cv::Point2f> apex_a(a.rune_apex, a.rune_apex + 5);
            int keep = 1;
            for (int j = 0; j < (int)picked.size(); j++) {
                InferenceResult& b = faceobjects[picked[j]];
                std::vector<cv::Point2f> apex_b(b.rune_apex, b.rune_apex + 5);
                std::vector<cv::Point2f> apex_inter;

                // TODO:此处耗时较长，大约1s，可以尝试使用其他方法计算IOU与多边形面积
                float inter_area = cv::intersectConvexConvex(apex_a,apex_b,apex_inter);
                float union_area = areas[i] + areas[picked[j]] - inter_area;
                float iou = inter_area / union_area;

                if (iou > nms_threshold || std::isnan(iou)) {
                    keep = 0;
                    //Stored for Merge
                    if (iou > k_UseToMeanIouThreshold && abs(a.probability - b.probability < k_MergeConfidenceError
                                                      && a.classification == b.classification && a.color == b.color)) {
                        for (int i = 0; i < 5; i++) {
                            b.points.push_back(a.rune_apex[i]);
                        }
                    }
                }
            }
            if (keep)
                picked.push_back(i);
        }
    }

    void decodeOutputs(const float* inference_result_ptr, const int& img_w, const int& img_h, const Eigen::Matrix<float, 3, 3>& transform_matrix,
                       std::vector<InferenceResult>& inference_runes) {
        if (inference_result_ptr == nullptr)
            return;

        std::vector<InferenceResult> proposals;
        std::vector<int> strides = {8, 6, 32};
        std::vector<GridAndStride> grid_strides;

        // 解析
        generateGridsAndStride(Inference::INPUT_WIDTH, Inference::INPUT_HEIGHT, strides, &grid_strides);
        generateYoloxProposals(grid_strides, inference_result_ptr, transform_matrix, k_BoundBoxConfidenceThreshold,
                               &proposals);
        qsort_descent_inplace(proposals);

        // 最多保留的推理出的能量机关的数量
        if (proposals.size() >= k_InferenceResultPollMaxVal)
            proposals.resize(k_InferenceResultPollMaxVal);
        std::vector<int> picked;
        nms_sorted_bboxes(proposals, picked, k_NmsThreshold);
        int count = picked.size();
        inference_runes.resize(count);

        for (int i = 0; i < count; i++) {
            inference_runes[i] = proposals[picked[i]];
        }
    }
} // rune_auto_aim