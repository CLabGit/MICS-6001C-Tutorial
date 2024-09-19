/*
 * Copyright (C) 2019-2022, Xilinx, Inc.
 * Copyright (C) 2022-2023, Advanced Micro Devices, Inc.
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
#include <hls_stream.h>
#include <iostream>
extern "C" {

void mm2s1(float* mem, hls::stream<float>& s, int size) {
#pragma HLS INTERFACE m_axi offset = slave bundle = gmem0 port = mem latency = 125 num_read_outstanding = \
    32 max_read_burst_length = 32 num_write_outstanding = 32 max_write_burst_length = 32
#pragma HLS INTERFACE axis port = s
#pragma HLS INTERFACE s_axilite port = mem bundle = control
#pragma HLS INTERFACE s_axilite port = size bundle = control
#pragma HLS INTERFACE s_axilite port = return bundle = control

    for (unsigned int i = 0; i < size; ++i) {
#pragma HLS PIPELINE II = 1
        s.write(mem[i]);
        if (i == 131390) printf("CHECK : mem[131390] = %f\n", mem[i]);
    }
}
}
