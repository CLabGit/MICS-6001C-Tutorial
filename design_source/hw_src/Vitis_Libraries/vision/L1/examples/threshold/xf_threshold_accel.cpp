/*
 * Copyright 2022 Xilinx, Inc.
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

#include "xf_threshold_accel_config.h"

static constexpr int __XF_DEPTH = (HEIGHT * WIDTH * (XF_PIXELWIDTH(IN_TYPE, NPPCX)) / 8) / (INPUT_PTR_WIDTH / 8);

void threshold_accel(ap_uint<INPUT_PTR_WIDTH>* img_inp,
                     ap_uint<OUTPUT_PTR_WIDTH>* img_out,
                     unsigned char thresh,
                     unsigned char maxval,
                     int rows,
                     int cols) {
// clang-format off
    #pragma HLS INTERFACE m_axi     port=img_inp  offset=slave bundle=gmem1 depth=__XF_DEPTH
    #pragma HLS INTERFACE m_axi     port=img_out  offset=slave bundle=gmem2 depth=__XF_DEPTH

    #pragma HLS INTERFACE s_axilite port=thresh     bundle=control
    #pragma HLS INTERFACE s_axilite port=maxval     bundle=control
    #pragma HLS INTERFACE s_axilite port=rows     bundle=control
    #pragma HLS INTERFACE s_axilite port=cols     bundle=control
    #pragma HLS INTERFACE s_axilite port=return   bundle=control
    // clang-format on

    const int pROWS = HEIGHT;
    const int pCOLS = WIDTH;
    const int pNPC1 = NPPCX;

    xf::cv::Mat<IN_TYPE, HEIGHT, WIDTH, NPPCX, XF_CV_DEPTH_IN> in_mat(rows, cols);
    // clang-format off
    // clang-format on

    xf::cv::Mat<OUT_TYPE, HEIGHT, WIDTH, NPPCX, XF_CV_DEPTH_OUT> out_mat(rows, cols);
// clang-format off
// clang-format on

// clang-format off
    #pragma HLS DATAFLOW
    // clang-format on

    xf::cv::Array2xfMat<INPUT_PTR_WIDTH, IN_TYPE, HEIGHT, WIDTH, NPPCX, XF_CV_DEPTH_IN>(img_inp, in_mat);

    xf::cv::Threshold<THRESH_TYPE, IN_TYPE, HEIGHT, WIDTH, NPPCX, XF_CV_DEPTH_IN, XF_CV_DEPTH_OUT>(in_mat, out_mat,
                                                                                                   thresh, maxval);

    xf::cv::xfMat2Array<OUTPUT_PTR_WIDTH, OUT_TYPE, HEIGHT, WIDTH, NPPCX, XF_CV_DEPTH_OUT>(out_mat, img_out);
}
