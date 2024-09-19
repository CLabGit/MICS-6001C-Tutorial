# Copyright (C) 2019-2022, Xilinx, Inc.
# Copyright (C) 2022-2023, Advanced Micro Devices, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# vitis hls makefile-generator v2.0.0

set CSIM 1
set CSYNTH 1
set COSIM 1
set VIVADO_SYN 1
set VIVADO_IMPL 1
set CUR_DIR [pwd]
set XF_PROJ_ROOT $CUR_DIR/../../../../../../..
set XPART xcu280-fsvh2892-2L-e

set PROJ "laplacian_RTM_x28_y25_z20_t1_p2_test.prj"
set SOLN "sol"

if {![info exists CLKP]} {
  set CLKP 3.3333
}

open_project -reset $PROJ

add_files "${XF_PROJ_ROOT}/L1/tests/hw/rtm3d/laplacian/tests/RTM_x28_y25_z20_t1_p2/../../laplacian.cpp" -cflags "-I${XF_PROJ_ROOT}/L1/tests/hw/rtm3d/laplacian/tests/RTM_x28_y25_z20_t1_p2 -I${XF_PROJ_ROOT}/L1/include/hw -I${XF_PROJ_ROOT}/../blas/L1/include/hw"
add_files -tb "${XF_PROJ_ROOT}/L1/tests/hw/rtm3d/laplacian/tests/RTM_x28_y25_z20_t1_p2/../../main.cpp" -cflags "-std=c++14 -I${XF_PROJ_ROOT}/L1/tests/hw/rtm3d/laplacian/tests/RTM_x28_y25_z20_t1_p2 -I${XF_PROJ_ROOT}/L1/include/hw -I${XF_PROJ_ROOT}/../blas/L1/include/hw -I${XF_PROJ_ROOT}/../blas/L1/tests/sw/include"
set_top top

open_solution -reset $SOLN



set_part $XPART
create_clock -period $CLKP

if {$CSIM == 1} {
  csim_design -argv "${XF_PROJ_ROOT}/L1/tests/hw/rtm3d/laplacian/tests/RTM_x28_y25_z20_t1_p2/data/"
}

if {$CSYNTH == 1} {
  csynth_design
}

if {$COSIM == 1} {
  cosim_design -argv "${XF_PROJ_ROOT}/L1/tests/hw/rtm3d/laplacian/tests/RTM_x28_y25_z20_t1_p2/data/"
}

if {$VIVADO_SYN == 1} {
  export_design -flow syn -rtl verilog
}

if {$VIVADO_IMPL == 1} {
  export_design -flow impl -rtl verilog
}

exit