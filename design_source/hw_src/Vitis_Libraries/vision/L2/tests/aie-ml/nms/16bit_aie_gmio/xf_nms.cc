/*
 * Copyright 2021 Xilinx, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "kernels.h"
#include "imgproc/xf_nms.hpp"

void nms_aa(adf::input_buffer<int16>& _ymin,
            adf::input_buffer<int16>& _xmin,
            adf::input_buffer<int16>& _ymax,
            adf::input_buffer<int16>& _xmax,
            adf::output_buffer<int16>& _out,
            const int16_t& iou_threshold,
            const int16_t& max_detections,
            const int16_t& total_valid_boxes) {
    xf::cv::aie::nms_aa_api(_ymin, _xmin, _ymax, _xmax, _out, iou_threshold, max_detections, total_valid_boxes);
}
