/** @file
 * Copyright (c) 2022-2023, Arm Limited or its affiliates. All rights reserved.
 * SPDX-License-Identifier : Apache-2.0

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
**/

#include "FVP/include/platform_override_struct.h"
#include "include/pal_common_support.h"

extern PLATFORM_OVERRIDE_TIMER_INFO_TABLE platform_timer_cfg;

/**
  @brief  This API fills in the TIMER_INFO_TABLE with information about local and
          system timers in the system from baremetal platform timer configuration

  @param  TimerTable  - Address where the Timer information needs to be filled

  @return  None
**/
void
pal_timer_create_info_table(TIMER_INFO_TABLE *TimerTable)
{

  uint32_t Index;

  if (TimerTable == NULL || TimerTable->gt_info == NULL)
    return;

  TimerTable->header.num_platform_timer = 0;

  TimerTable->header.s_el1_timer_flag    = platform_timer_cfg.header.s_el1_timer_flags;
  TimerTable->header.ns_el1_timer_flag   = platform_timer_cfg.header.ns_el1_timer_flags;
  TimerTable->header.el2_timer_flag      = platform_timer_cfg.header.el2_timer_flags;
  TimerTable->header.s_el1_timer_gsiv    = platform_timer_cfg.header.s_el1_timer_gsiv;
  TimerTable->header.ns_el1_timer_gsiv   = platform_timer_cfg.header.ns_el1_timer_gsiv;
  TimerTable->header.el2_timer_gsiv      = platform_timer_cfg.header.el2_timer_gsiv;
  TimerTable->header.virtual_timer_flag  = platform_timer_cfg.header.virtual_timer_flags;
  TimerTable->header.virtual_timer_gsiv  = platform_timer_cfg.header.virtual_timer_gsiv;
  TimerTable->header.el2_virt_timer_gsiv = platform_timer_cfg.header.el2_virt_timer_gsiv;

  TimerTable->gt_info->type            = platform_timer_cfg.gt_info.type;
  TimerTable->gt_info->block_cntl_base = platform_timer_cfg.gt_info.block_cntl_base;
  TimerTable->gt_info->timer_count     = platform_timer_cfg.gt_info.timer_count;

  for (Index = 0; Index < TimerTable->gt_info->timer_count; Index++)
  {
     TimerTable->gt_info->GtCntBase[Index]    = platform_timer_cfg.gt_info.GtCntBase[Index];
     TimerTable->gt_info->GtCntEl0Base[Index] = platform_timer_cfg.gt_info.GtCntEl0Base[Index];
     TimerTable->gt_info->gsiv[Index]         = platform_timer_cfg.gt_info.gsiv[Index];
     TimerTable->gt_info->virt_gsiv[Index]    = platform_timer_cfg.gt_info.virt_gsiv[Index];
     TimerTable->gt_info->flags[Index]        = platform_timer_cfg.gt_info.flags[Index];

     TimerTable->header.num_platform_timer++;

  }
}

/**
  @brief  This API gets the counter frequency value from user

  @param  None

  @return Counter frequency value
**/
uint64_t
pal_timer_get_counter_frequency(void)
{
  return PLATFORM_OVERRIDE_TIMER_CNTFRQ;
}
