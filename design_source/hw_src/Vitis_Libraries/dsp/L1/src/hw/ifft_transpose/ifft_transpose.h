/*
 * Copyright (C) 2019-2022, Xilinx, Inc.
 * Copyright (C) 2022-2024, Advanced Micro Devices, Inc.
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
#pragma once

#include <complex>
#include <ap_fixed.h>
#include <hls_stream.h>

namespace ifft_transpose {
template <unsigned int TP_POINT_SIZE>
constexpr unsigned int fnPtSizeD1() {
    unsigned int sqrtVal =
        TP_POINT_SIZE == 65536
            ? 256
            : TP_POINT_SIZE == 32768
                  ? 256
                  : TP_POINT_SIZE == 16384
                        ? 128
                        : TP_POINT_SIZE == 8192
                              ? 128
                              : TP_POINT_SIZE == 4096
                                    ? 64
                                    : TP_POINT_SIZE == 2048
                                          ? 64
                                          : TP_POINT_SIZE == 1024
                                                ? 32
                                                : TP_POINT_SIZE == 512
                                                      ? 32
                                                      : TP_POINT_SIZE == 256
                                                            ? 16
                                                            : TP_POINT_SIZE == 128
                                                                  ? 16
                                                                  : TP_POINT_SIZE == 64
                                                                        ? 8
                                                                        : TP_POINT_SIZE == 32
                                                                              ? 8
                                                                              : TP_POINT_SIZE == 16 ? 4 : 0;
    return sqrtVal;
}

static constexpr unsigned NSTREAM = SSR;
static constexpr unsigned POINT_SIZE_D1 = fnPtSizeD1<POINT_SIZE>();
static constexpr unsigned NROW = (POINT_SIZE_D1 + NSTREAM - 1) / NSTREAM; // # of rows of transforms per bank
static constexpr unsigned EXTRA =
    (NROW * NSTREAM) - POINT_SIZE_D1; // # of extra zero-padded samples (to made divisible by NSTREAM)
static constexpr unsigned DEPTH = (POINT_SIZE / POINT_SIZE_D1 + EXTRA); // Depth of each bank
static constexpr unsigned NBITS = 128;                                  // Size of PLIO bus on PL side @ 312.5 MHz
typedef ap_uint<NBITS> TT_DATA;                                         // Equals two 'cint32' samples
static constexpr unsigned SAMPLE_SIZE = 64;
static constexpr unsigned SAMPLES_PER_READ = NBITS / SAMPLE_SIZE;
typedef ap_uint<SAMPLE_SIZE> TT_SAMPLE; // Samples are 'cint32'
typedef hls::stream<TT_DATA> TT_STREAM;
};

// // Run:
void ifft_transpose_wrapper(ifft_transpose::TT_STREAM sig_i[ifft_transpose::NSTREAM],
                            ifft_transpose::TT_STREAM sig_o[ifft_transpose::NSTREAM]);
