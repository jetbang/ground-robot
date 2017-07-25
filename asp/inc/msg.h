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
 
#ifndef __MSG_H__
#define __MSG_H__

/********************************************************/
/*                 KylinBot Msg Type                    */
/*     Basic frame structure:                           */
/*       ________________________________________       */
/*      |id:8|length:8|token:16|data~|checksum:16|      */
/*      |______________________|_____|___________|      */
/*      |         head         |body~|    crc    |      */
/*      |________________________________________|      */
/*                         Msg                          */
/********************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "cbus.h"
#include "dbus.h"
#include "fifo.h"
#include "calib.h"
#include "crc16.h"
	
/* Message length minimum/maximum limit */
#define MSG_LEN_MIN 6u
#define MSG_LEN_MAX 256u
#define MSG_LEN_EXT 6u

#pragma pack(1)

/* Message head union typedef */
typedef union MsgHead_t
{
	uint32_t value; // Message head value in 32bit
	struct
	{
		uint8_t id : 8; // Message ID
		uint8_t length : 8; // Message length (unit: byte)
		uint16_t token : 16; // Message CRC token
	}attr; // Message head attributes
}MsgHead_t; // Message head union typedef

#define IMU_MSG_VALUE_SCALE 1.0f
typedef struct
{
	uint32_t frame_id;
	int16_t ax;
	int16_t ay;
	int16_t az;
	int16_t gx;
	int16_t gy;
	int16_t gz;
}ImuMsg_t;

#define MAG_MSG_VALUE_SCALE 1.0f
typedef struct
{
	uint32_t frame_id;
	int16_t mx;
	int16_t my;
	int16_t mz;
}MagMsg_t;

typedef struct
{
	uint32_t frame_id;
	uint8_t  flag; //0:invalid 1:valid
	uint32_t x;
	uint32_t y;
	uint32_t z;
	uint32_t w;
}UwbMsg_t;

#define ODO_MSG_VALUE_SCALE 1e3f
typedef struct
{
	uint32_t frame_id;
	uint32_t fs; // Functional state
	ChassisState_p cp;
	ChassisState_v cv;
	PantiltState_c gp;
	PantiltState_c gv;
}OdoMsg_t;

#define PTZ_MSG_VALUE_SCALE 1e3f
typedef struct
{
	uint32_t frame_id;
	int16_t p; // pan
	int16_t t; // tilt
	int16_t z; // zoom
}PTZMsg_t;

typedef struct
{
	uint32_t frame_id;
	uint8_t data[RCP_FRAME_LEN];
}VRCMsg_t;

typedef struct
{
	uint32_t frame_id;
	uint8_t data[HCP_FRAME_LEN];
}VHCMsg_t;

#define AHRS_MSG_VALUE_SCALE 1.0f
typedef struct
{
	uint32_t frame_id;
	float q[4];
}AHRSMsg_t;

typedef struct
{
	uint32_t frame_id;
	CBus_t cbus;
}CBusMsg_t;

typedef struct
{
	uint32_t frame_id;
	uint8_t data[DBUS_FRAME_LEN];
}VDBusMsg_t;

#define ZGYRO_ANGLE_RECIP 1e-2f // To scale zgyro angle to deg
#define ZGYRO_RATE_RECIP 1e-5f // To scale zgyro rate to deg/s
typedef struct
{
	uint32_t frame_id;
	int32_t angle; // = (deg*100)
	int16_t rate; // = delta(angle)/1ms
}ZGyroMsg_t;

#define MOTOR1_ID 0
#define MOTOR2_ID 1
#define MOTOR3_ID 2
#define MOTOR4_ID 3
#define MOTOR5_ID 4
#define MOTOR6_ID 5
#define MOTOR_ECD_ANGLE_MAX 8191
typedef struct
{
	uint8_t id; // 0~5
	uint32_t frame_id;
	uint16_t ecd_angle; // Encoder angle, range from 0~8191
	int32_t round;
	int32_t angle; // Continuous angle, infinite
	int16_t rate; // Rate in ecd_diff/1ms
}MotorMsg_t;

typedef struct
{
	uint32_t frame_id;
	uint32_t wdg; // Watchdog
	uint32_t ini; // Initialization status
}StatuMsg_t;

typedef struct
{
	uint32_t frame_id;
	uint32_t msg_type;
}SubscMsg_t;

#define CALIB_FLAG_BIT_IMU (1u<<0)
#define CALIB_FLAG_BIT_MAG (1u<<1)
#define CALIB_FLAG_BIT_POS (1u<<2)
typedef struct
{
	uint32_t frame_id;
	uint32_t auto_cali_flag; // Auto calibration control bits
}CalibMsg_t;

typedef struct
{
	uint32_t frame_id;
	PIDCalib_t data;
}PIDCalibMsg_t;

typedef struct
{
	uint32_t frame_id;
	IMUCalib_t data;
}IMUCalibMsg_t;

typedef struct
{
	uint32_t frame_id;
	MagCalib_t data;
}MagCalibMsg_t;

typedef struct
{
	uint32_t frame_id;
	VelCalib_t data;
}VelCalibMsg_t;

typedef struct
{
	uint32_t frame_id;
	MecCalib_t data;
}MecCalibMsg_t;

typedef struct
{
	uint32_t frame_id;
	PosCalib_t data;
}PosCalibMsg_t;

#define WRAP_U8(V) ((uint8_t)V)
#define WRAP_U16(V) ((uint16_t)V)
#define WRAP_U32(V) ((uint32_t)V)

#define MSG_ID_IMU WRAP_U8(0x01)
#define MSG_ID_MAG WRAP_U8(0x02)
#define MSG_ID_UWB WRAP_U8(0x03)
#define MSG_ID_ODO WRAP_U8(0x04)
#define MSG_ID_PTZ WRAP_U8(0x05)
#define MSG_ID_VRC WRAP_U8(0x06)
#define MSG_ID_VHC WRAP_U8(0x07)
#define MSG_ID_AHRS WRAP_U8(0x08)
#define MSG_ID_CBUS WRAP_U8(0x09)
#define MSG_ID_VDBUS WRAP_U8(0x0a)
#define MSG_ID_ZGYRO WRAP_U8(0x0b)
#define MSG_ID_MOTOR WRAP_U8(0x0c)
#define MSG_ID_STATU WRAP_U8(0x0d)
#define MSG_ID_SUBSC WRAP_U8(0x0e)
#define MSG_ID_CALIB WRAP_U8(0x0f)
#define MSG_ID_PID_CALIB WRAP_U8(0x10)
#define MSG_ID_IMU_CALIB WRAP_U8(0x11)
#define MSG_ID_MAG_CALIB WRAP_U8(0x12)
#define MSG_ID_VEL_CALIB WRAP_U8(0x13)
#define MSG_ID_MEC_CALIB WRAP_U8(0x14)
#define MSG_ID_POS_CALIB WRAP_U8(0x15)

#define MSG_LEN_IMU sizeof(ImuMsg_t)
#define MSG_LEN_MAG sizeof(MagMsg_t)
#define MSG_LEN_UWB sizeof(UwbMsg_t)
#define MSG_LEN_ODO sizeof(OdoMsg_t)
#define MSG_LEN_PTZ sizeof(PTZMsg_t)
#define MSG_LEN_VRC sizeof(VRCMsg_t)
#define MSG_LEN_VHC sizeof(VHCMsg_t)
#define MSG_LEN_AHRS sizeof(AHRSMsg_t)
#define MSG_LEN_CBUS sizeof(CBusMsg_t)
#define MSG_LEN_VDBUS sizeof(VDBusMsg_t)
#define MSG_LEN_ZGYRO sizeof(ZGyroMsg_t)
#define MSG_LEN_MOTOR sizeof(MotorMsg_t)
#define MSG_LEN_STATU sizeof(StatuMsg_t)
#define MSG_LEN_SUBSC sizeof(SubscMsg_t)
#define MSG_LEN_CALIB sizeof(CalibMsg_t)
#define MSG_LEN_PID_CALIB sizeof(PIDCalibMsg_t)
#define MSG_LEN_IMU_CALIB sizeof(IMUCalibMsg_t)
#define MSG_LEN_MAG_CALIB sizeof(MagCalibMsg_t)
#define MSG_LEN_VEL_CALIB sizeof(VelCalibMsg_t)
#define MSG_LEN_MEC_CALIB sizeof(MecCalibMsg_t)
#define MSG_LEN_POS_CALIB sizeof(PosCalibMsg_t)

#define MSG_TOKEN_IMU WRAP_U16(0xff11)
#define MSG_TOKEN_MAG WRAP_U16(0xff12)
#define MSG_TOKEN_UWB WRAP_U16(0xff13)
#define MSG_TOKEN_ODO WRAP_U16(0xff14)
#define MSG_TOKEN_PTZ WRAP_U16(0xff15)
#define MSG_TOKEN_VRC WRAP_U16(0xff16)
#define MSG_TOKEN_VHC WRAP_U16(0xff17)
#define MSG_TOKEN_AHRS WRAP_U16(0xff18)
#define MSG_TOKEN_CBUS WRAP_U16(0xff19)
#define MSG_TOKEN_VDBUS WRAP_U16(0xff1a)
#define MSG_TOKEN_ZGYRO WRAP_U16(0xff1b)
#define MSG_TOKEN_MOTOR WRAP_U16(0xff1c)
#define MSG_TOKEN_STATU WRAP_U16(0xff1d)
#define MSG_TOKEN_SUBSC WRAP_U16(0xff1e)
#define MSG_TOKEN_CALIB WRAP_U16(0xff1f)
#define MSG_TOKEN_PID_CALIB WRAP_U16(0xff21)
#define MSG_TOKEN_IMU_CALIB WRAP_U16(0xff22)
#define MSG_TOKEN_MAG_CALIB WRAP_U16(0xff23)
#define MSG_TOKEN_VEL_CALIB WRAP_U16(0xff24)
#define MSG_TOKEN_MEC_CALIB WRAP_U16(0xff25)
#define MSG_TOKEN_POS_CALIB WRAP_U16(0xff26)

#define MSG_HEAD_VALUE(ID,LEN,TOKEN) ((WRAP_U32(TOKEN)<<16) | (WRAP_U32(LEN)<<8) | WRAP_U32(ID))
#define MSG_HEAD_VALUE_OF(NAME) MSG_HEAD_VALUE(MSG_ID_##NAME,MSG_LEN_##NAME,MSG_TOKEN_##NAME)

#define MSG_HEAD_VALUE_IMU MSG_HEAD_VALUE_OF(IMU)
#define MSG_HEAD_VALUE_MAG MSG_HEAD_VALUE_OF(MAG)
#define MSG_HEAD_VALUE_UWB MSG_HEAD_VALUE_OF(UWB)
#define MSG_HEAD_VALUE_ODO MSG_HEAD_VALUE_OF(ODO)
#define MSG_HEAD_VALUE_PTZ MSG_HEAD_VALUE_OF(PTZ)
#define MSG_HEAD_VALUE_VRC MSG_HEAD_VALUE_OF(VRC)
#define MSG_HEAD_VALUE_VHC MSG_HEAD_VALUE_OF(VHC)
#define MSG_HEAD_VALUE_AHRS MSG_HEAD_VALUE_OF(AHRS)
#define MSG_HEAD_VALUE_CBUS MSG_HEAD_VALUE_OF(CBUS)
#define MSG_HEAD_VALUE_VDBUS MSG_HEAD_VALUE_OF(VDBUS)
#define MSG_HEAD_VALUE_ZGYRO MSG_HEAD_VALUE_OF(ZGYRO)
#define MSG_HEAD_VALUE_MOTOR MSG_HEAD_VALUE_OF(MOTOR)
#define MSG_HEAD_VALUE_STATU MSG_HEAD_VALUE_OF(STATU)
#define MSG_HEAD_VALUE_SUBSC MSG_HEAD_VALUE_OF(SUBSC)
#define MSG_HEAD_VALUE_CALIB MSG_HEAD_VALUE_OF(CALIB)
#define MSG_HEAD_VALUE_PID_CALIB MSG_HEAD_VALUE_OF(PID_CALIB)
#define MSG_HEAD_VALUE_IMU_CALIB MSG_HEAD_VALUE_OF(IMU_CALIB)
#define MSG_HEAD_VALUE_MAG_CALIB MSG_HEAD_VALUE_OF(MAG_CALIB)
#define MSG_HEAD_VALUE_VEL_CALIB MSG_HEAD_VALUE_OF(VEL_CALIB)
#define MSG_HEAD_VALUE_MEC_CALIB MSG_HEAD_VALUE_OF(MEC_CALIB)
#define MSG_HEAD_VALUE_POS_CALIB MSG_HEAD_VALUE_OF(POS_CALIB)

#define MSG_HEAD_IMU { MSG_HEAD_VALUE_VRC }
#define MSG_HEAD_MAG { MSG_HEAD_VALUE_MAG }
#define MSG_HEAD_UWB { MSG_HEAD_VALUE_UWB }
#define MSG_HEAD_ODO { MSG_HEAD_VALUE_ODO }
#define MSG_HEAD_PTZ { MSG_HEAD_VALUE_PTZ }
#define MSG_HEAD_VRC { MSG_HEAD_VALUE_VRC }
#define MSG_HEAD_VHC { MSG_HEAD_VALUE_VHC }
#define MSG_HEAD_AHRS { MSG_HEAD_VALUE_AHRS }
#define MSG_HEAD_CBUS { MSG_HEAD_VALUE_CBUS }
#define MSG_HEAD_VDBUS { MSG_HEAD_VALUE_VDBUS }
#define MSG_HEAD_ZGYRO { MSG_HEAD_VALUE_ZGYRO }
#define MSG_HEAD_MOTOR { MSG_HEAD_VALUE_MOTOR }
#define MSG_HEAD_STATU { MSG_HEAD_VALUE_STATU }
#define MSG_HEAD_SUBSC { MSG_HEAD_VALUE_SUBSC }
#define MSG_HEAD_CALIB { MSG_HEAD_VALUE_CALIB }
#define MSG_HEAD_PID_CALIB { MSG_HEAD_VALUE_PID_CALIB }
#define MSG_HEAD_IMU_CALIB { MSG_HEAD_VALUE_IMU_CALIB }
#define MSG_HEAD_MAG_CALIB { MSG_HEAD_VALUE_MAG_CALIB }
#define MSG_HEAD_VEL_CALIB { MSG_HEAD_VALUE_VEL_CALIB }
#define MSG_HEAD_MEC_CALIB { MSG_HEAD_VALUE_MEC_CALIB }
#define MSG_HEAD_POS_CALIB { MSG_HEAD_VALUE_POS_CALIB }

#define MSG_TYPE_IDX_IMU 0u
#define MSG_TYPE_IDX_MAG 1u
#define MSG_TYPE_IDX_UWB 2u
#define MSG_TYPE_IDX_ODO 3u
#define MSG_TYPE_IDX_PTZ 4u
#define MSG_TYPE_IDX_VRC 5u
#define MSG_TYPE_IDX_VHC 5u
#define MSG_TYPE_IDX_AHRS 6u
#define MSG_TYPE_IDX_CBUS 7u
#define MSG_TYPE_IDX_VDBUS 8u
#define MSG_TYPE_IDX_ZGYRO 9u
#define MSG_TYPE_IDX_MOTOR 10u
#define MSG_TYPE_IDX_STATU 11u
#define MSG_TYPE_IDX_SUBSC 12u
#define MSG_TYPE_IDX_CALIB 13u
#define MSG_TYPE_IDX_PID_CALIB 14u
#define MSG_TYPE_IDX_IMU_CALIB 15u
#define MSG_TYPE_IDX_MAG_CALIB 16u
#define MSG_TYPE_IDX_VEL_CALIB 17u
#define MSG_TYPE_IDX_MEC_CALIB 18u
#define MSG_TYPE_IDX_POS_CALIB 19u

typedef enum
{
	MSG_TYPE_IMU = 1u << MSG_TYPE_IDX_IMU,
	MSG_TYPE_MAG = 1u << MSG_TYPE_IDX_MAG,
	MSG_TYPE_UWB = 1u << MSG_TYPE_IDX_UWB,
	MSG_TYPE_ODO = 1u << MSG_TYPE_IDX_ODO,
	MSG_TYPE_PTZ = 1u << MSG_TYPE_IDX_PTZ,
	MSG_TYPE_VRC = 1u << MSG_TYPE_IDX_VRC,
	MSG_TYPE_VHC = 1u << MSG_TYPE_IDX_VHC,
	MSG_TYPE_AHRS = 1u << MSG_TYPE_IDX_AHRS,
	MSG_TYPE_CBUS = 1u << MSG_TYPE_IDX_CBUS,
	MSG_TYPE_VDBUS = 1u << MSG_TYPE_IDX_VDBUS,
	MSG_TYPE_ZGYRO = 1u << MSG_TYPE_IDX_ZGYRO,
	MSG_TYPE_MOTOR = 1u << MSG_TYPE_IDX_MOTOR,
	MSG_TYPE_STATU = 1u << MSG_TYPE_IDX_STATU,
	MSG_TYPE_SUBSC = 1u << MSG_TYPE_IDX_SUBSC,
	MSG_TYPE_CALIB = 1u << MSG_TYPE_IDX_CALIB,
	MSG_TYPE_PID_CALIB = 1u << MSG_TYPE_IDX_PID_CALIB,
	MSG_TYPE_IMU_CALIB = 1u << MSG_TYPE_IDX_IMU_CALIB,
	MSG_TYPE_MAG_CALIB = 1u << MSG_TYPE_IDX_MAG_CALIB,
	MSG_TYPE_VEL_CALIB = 1u << MSG_TYPE_IDX_VEL_CALIB,
	MSG_TYPE_MEC_CALIB = 1u << MSG_TYPE_IDX_MEC_CALIB,
	MSG_TYPE_POS_CALIB = 1u << MSG_TYPE_IDX_POS_CALIB,
}MsgType_t;

#pragma pack()

void* Msg_GetData(const void* buf, const void* head);

/**
 * @brief: Push a single message to message fifo. 
 * @param fifo Message fifo
 * @param buf Message buffer
 * @param head Message head
 * @param body Message body
 * @return Message length (num of bytes)
 */
uint32_t Msg_Push(FIFO_t* fifo, void* buf, const void* head, const void* body);

/**
 * @brief Pop a single message from message fifo. 
 * @param fifo Message fifo
 * @param buf Message buffer
 * @param head Message head
 * @param body Message body
 * @return Message length (num of bytes)
 */
uint32_t Msg_Pop(FIFO_t* fifo, void* buf, const void* head, void* body);

extern const MsgHead_t msg_head_imu;
extern const MsgHead_t msg_head_mag;
extern const MsgHead_t msg_head_uwb;
extern const MsgHead_t msg_head_odo;
extern const MsgHead_t msg_head_ptz;
extern const MsgHead_t msg_head_vrc;
extern const MsgHead_t msg_head_vhc;
extern const MsgHead_t msg_head_ahrs;
extern const MsgHead_t msg_head_cbus;
extern const MsgHead_t msg_head_vdbus;
extern const MsgHead_t msg_head_zgyro;
extern const MsgHead_t msg_head_motor;
extern const MsgHead_t msg_head_statu;
extern const MsgHead_t msg_head_subsc;
extern const MsgHead_t msg_head_calib;
extern const MsgHead_t msg_head_pid_calib;
extern const MsgHead_t msg_head_imu_calib;
extern const MsgHead_t msg_head_mag_calib;
extern const MsgHead_t msg_head_vel_calib;
extern const MsgHead_t msg_head_mec_calib;
extern const MsgHead_t msg_head_pos_calib;


#ifdef __cplusplus
}
#endif

#endif


