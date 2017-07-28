/**
 * Copyright (c) 2011-2016, Jack Mo (mobangjack@foxmail.com).
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#ifndef __CTL_H__
#define __CTL_H__

/**********************************************/
/*              Logic Controller              */
/**********************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "sys.h"
#include "cci.h"
#include "dci.h"
#include "cmd.h"
#include "odo.h"
#include "pid.h"
#include "rmp.h"

typedef struct
{
	PeriphsState_t fs;
	ChassisState_t cv;
	MecanumState_t mv;
	MecanumState_t mc;
	MecanumState_t mp;
	PantiltState_t gv;
	PantiltState_t gc;
}Ctl_t;

#define CCL_NUM 4
typedef struct
{
	PID_t w[CCL_NUM];
}Ccl_t; // Chassis control loop

typedef struct
{
	PID_t p;
	PID_t t;
}Gcl_t; // Grabber control loop

typedef struct
{
	Ccl_t mp;
	Ccl_t mv;
	Gcl_t gp;
	Gcl_t gv;
}Pid_t;

void Ctl_Init(void);
void Ctl_Proc(void);

/**********************************************/
/*             Exported Variables             */
/**********************************************/

extern Ctl_t ctl;
extern Pid_t pid;
extern Rmp_t rmp;

#ifdef __cplusplus
}
#endif

#endif

