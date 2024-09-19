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

#ifndef ADF_GRAPH_H
#define ADF_GRAPH_H

#include <adf.h>
#include <array>
#include <type_traits>

#include "kernels.h"

using namespace adf;

class maskGenGraph : public adf::graph {
   private:
    kernel k;

   public:
    input_plio in1;
    output_plio out1;
    port<input> depth_min;
    port<input> depth_max;
    port<input> thres_f_new;
    port<input> thres_b_new;

    maskGenGraph() {
        k = kernel::create(maskGen_api);
        in1 = input_plio::create("DataIn0", adf::plio_128_bits, "data/input.txt");
        out1 = output_plio::create("DataOut0", adf::plio_128_bits, "data/output.txt");

        // create nets to connect kernels and IO ports
        connect<>(in1.out[0], k.in[0]);
        connect<>(k.out[0], out1.in[0]);
        connect<parameter>(depth_min, async(k.in[1]));
        connect<parameter>(depth_max, async(k.in[2]));
        connect<parameter>(thres_f_new, async(k.in[3]));
        connect<parameter>(thres_b_new, async(k.in[4]));

        adf::dimensions(k.in[0]) = {ELEM_WITH_METADATA};
        adf::dimensions(k.out[0]) = {ELEM_WITH_METADATA};
        // specify kernel sources
        source(k) = "xf_mask_gen.cc";

        runtime<ratio>(k) = 1.0;
    }
};

#endif
