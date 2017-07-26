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
 
#include "bsp.h"

void Bsp_Config(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	Beep_Config();
	Btm_Config();
	Btn_Config();
	Dbi_Config();
	Key_Config();
	Led_Config();
	Pwm_Config();
	Rcv_Config();
	Tim_Config();
	Tty_Config();
	Can1_Config();
	Can2_Config();
	//SR04_Config(); // Not used
	Spi5_Config();
	Laser_Config();
	MPU6500_Config();
	//IST8310_Config();
	LED_GREEN_ON();
}

