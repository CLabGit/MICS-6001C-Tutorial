/*
 * Copyright 2020 Xilinx, Inc.
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

#ifndef _XF_GRAPH_L3_OP_BFS_HPP_
#define _XF_GRAPH_L3_OP_BFS_HPP_

#include "graph.hpp"
#include "op_base.hpp"
#include "openclHandle.hpp"

namespace xf {
namespace graph {
namespace L3 {

class opBFS : public opBase {
   public:
    static uint32_t cuPerBoardBFS;

    static uint32_t dupNmBFS;

    class clHandle* handles;

    opBFS() : opBase(){};

    void setHWInfo(uint32_t numDev, uint32_t CUmax);

    void freeBFS(xrmContext* ctx);

    void createHandle(class openXRM* xrm,
                      clHandle& handle,
                      std::string kernelName,
                      std::string kernelAlias,
                      std::string xclbinFile,
                      int32_t IDDevice,
                      unsigned int requestLoad);

    void init(class openXRM* xrm,
              std::string kernelName,
              std::string kernelALias,
              std::string xclbinFile,
              uint32_t* deviceIDs,
              uint32_t* cuIDs,
              unsigned int requestLoad);

    static int compute(unsigned int deviceID,
                       unsigned int cuID,
                       unsigned int channelID,
                       xrmContext* ctx,
                       xrmCuResource* resR,
                       std::string instanceName,
                       clHandle* handles,
                       uint32_t sourceID,
                       xf::graph::Graph<uint32_t, uint32_t> g,
                       uint32_t* predecent,
                       uint32_t* distance);

    event<int> addwork(uint32_t sourceID,
                       xf::graph::Graph<uint32_t, uint32_t> g,
                       uint32_t* predecent,
                       uint32_t* distance);

   private:
    std::vector<int> deviceOffset;

    uint32_t deviceNm;

    uint32_t maxCU;

    static void bufferInit(clHandle* hds,
                           std::string instanceName0,
                           uint32_t sourceID,
                           xf::graph::Graph<uint32_t, uint32_t> g,
                           uint32_t* queue,
                           uint32_t* discovery,
                           uint32_t* finish,
                           uint32_t* predecent,
                           uint32_t* distance,
                           cl::Kernel& kernel0,
                           std::vector<cl::Memory>& ob_in,
                           std::vector<cl::Memory>& ob_out);

    static int cuExecute(
        clHandle* hds, cl::Kernel& kernel0, unsigned int num_runs, std::vector<cl::Event>* evIn, cl::Event* evOut);

    static void migrateMemObj(clHandle* hds,
                              bool type,
                              unsigned int num_runs,
                              std::vector<cl::Memory>& ob,
                              std::vector<cl::Event>* evIn,
                              cl::Event* evOut);

    static void cuRelease(xrmContext* ctx, xrmCuResource* resR);
};
} // L3
} // graph
} // xf

#endif
