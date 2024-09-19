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

#include "kernels.hpp"

namespace us {
namespace L1 {

template <typename T, const unsigned LEN, const unsigned INCREMENT, const unsigned VECDIM>
void sumMM(adf::input_buffer<T>& in1, adf::input_buffer<T>& in2, adf::output_buffer<T>& out) {
    // matrix of beamf are nx3, so we pad with 1 zero and operate row by row, count = n° rows
    T* __restrict p_in1 = in1.data();
    T* __restrict p_in2 = in2.data();
    T* __restrict p_out = out.data();

    aie::vector<float, VECDIM> op1 = aie::zeros<float, VECDIM>();
    aie::vector<float, VECDIM> op2 = aie::zeros<float, VECDIM>();
    aie::vector<float, VECDIM> res = aie::zeros<float, VECDIM>();

    for (unsigned i = 0; i < LEN; i += INCREMENT) {
        op1 = aie::load_v<VECDIM>(p_in1);
        p_in1 = byte_incr(p_in1, VECDIM * sizeof(T));

        op2 = aie::load_v<VECDIM>(p_in2);
        p_in2 = byte_incr(p_in2, VECDIM * sizeof(T));

        res = aie::add(op1, op2);
        aie::store_v(p_out, res);
        p_out = byte_incr(p_out, VECDIM * sizeof(T));
    }
};
} // namespace L1
} // namespace us
