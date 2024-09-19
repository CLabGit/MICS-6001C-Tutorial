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

void s2mm3(float* mem, hls::stream<float>& s, int size) {
#pragma HLS INTERFACE m_axi offset = slave bundle = gmem3 port = mem latency = 125 num_read_outstanding = \
    32 max_read_burst_length = 32 num_write_outstanding = 32 max_write_burst_length = 32

#pragma HLS INTERFACE axis port = s

#pragma HLS INTERFACE s_axilite port = mem bundle = control
#pragma HLS INTERFACE s_axilite port = size bundle = control
#pragma HLS INTERFACE s_axilite port = return bundle = control

    for (int i = 0; i < size; ++i) {
        // if(i%(example_1_num_sample)==0)std::cout << "mult out-3 in line = " << i/example_1_num_sample << std::endl;
        mem[i] = s.read();
    }
}
}
