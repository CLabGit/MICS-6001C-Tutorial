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
set XF_PROJ_ROOT $CUR_DIR/../../../..
set XPART xcu250-figd2104-2L-e

set PROJ "cholesky_test.prj"
set SOLN "sol1"

if {![info exists CLKP]} {
  set CLKP 300MHz
}

open_project -reset $PROJ

add_files "${XF_PROJ_ROOT}/L1/tests/cholesky/kernel/kernel_cholesky_0.cpp" -cflags "-DMATRIX_DIM=3 -DMATRIX_LOWER_TRIANGULAR=0 -DSEL_ARCH=0 -D_DATA_PATH=${XF_PROJ_ROOT}/L1/tests/cholesky/datas/ -I./ -I${XF_PROJ_ROOT}/L1/tests/cholesky/host/ -I${XF_PROJ_ROOT}/L1/tests/cholesky/kernel/ -I${XF_PROJ_ROOT}/L1/tests/cholesky/ -I${XF_PROJ_ROOT}/L1/tests/ -I${XF_PROJ_ROOT}/L1/include/ -I${XF_PROJ_ROOT}/L1/include/hw -I${XF_PROJ_ROOT}/L2/include -I${XF_PROJ_ROOT}/../utils/L1/include/"
add_files -tb "${XF_PROJ_ROOT}/L1/tests/cholesky/host/test_cholesky.cpp" -cflags "-DMATRIX_DIM=3 -DMATRIX_LOWER_TRIANGULAR=0 -DSEL_ARCH=0 -D_DATA_PATH=${XF_PROJ_ROOT}/L1/tests/cholesky/datas/ -I./ -I${XF_PROJ_ROOT}/L1/tests/cholesky/host/ -I${XF_PROJ_ROOT}/L1/tests/cholesky/kernel/ -I${XF_PROJ_ROOT}/L1/tests/cholesky/ -I${XF_PROJ_ROOT}/L1/tests/ -I${XF_PROJ_ROOT}/L1/include/ -I${XF_PROJ_ROOT}/L1/include/hw -I ./host -I${XF_PROJ_ROOT}/../utils/L1/include/"
set_top kernel_cholesky_0

open_solution -reset $SOLN



set_part $XPART
create_clock -period $CLKP

if {$CSIM == 1} {
  csim_design
}

if {$CSYNTH == 1} {
  csynth_design
}

if {$COSIM == 1} {
  cosim_design
}

if {$VIVADO_SYN == 1} {
  export_design -flow syn -rtl verilog
}

if {$VIVADO_IMPL == 1} {
  export_design -flow impl -rtl verilog
}

exit