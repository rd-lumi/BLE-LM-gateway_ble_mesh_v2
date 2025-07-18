/********************************************************************************************************
 * @file	mesh_node.h
 *
 * @brief	for TLSR chips
 *
 * @author	telink
 * @date	Sep. 30, 2010
 *
 * @par     Copyright (c) 2017, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *
 *******************************************************************************************************/
#pragma once
#include "tl_common.h"
#if NL_API_ENABLE
#include "nl_api/nl_model_schedules.h"
#endif

#if WIN32
#pragma pack(1)
#endif

typedef struct{
	u16 md_id; 
}model_sig_id_t;

typedef struct{
	u16 cid;
	u16 md_id; 
}model_vendor_id_t;

typedef struct{
	u32 id;
	u8 sig_model; // bool
}mesh_model_id_t;

#if 0	// can not use in VC
typedef struct{
	union{
		struct{
			u16 k1	:12;
			u16 k2	:12;
		};
		struct{
			u16 net	:12;
			u16 app	:12;
		};
	};
}key_idx_enc_t;
#else
#define GET_KEY_INDEX_LEN(cnt)		        ((cnt/2) * 3 + (cnt&1) * 2)
#define GET_PAR_LEN_FROM_RSP(len, size_op)  (len - 4 - size_op)
#define GET_RSP_LEN_FROM_PAR(len, size_op)  (len + 4 + size_op)

static inline u16 GET_KEY_INDEX_L(u8 *p){
	return (p[0]+((p[1]&0x0f)<<8));
}
static inline u16 GET_KEY_INDEX_H(u8 *p){
	return ((p[1]+(p[2]<<8))>>4);
}
static inline u16 GET_NETKEY_INDEX(u8 *p){
	return GET_KEY_INDEX_L(p);
}
static inline u16 GET_APPKEY_INDEX(u8 *p){
	return GET_KEY_INDEX_H(p);
}

static inline void SET_KEY_INDEX_L(u8 *p, u16 key_idx){
	p[0] = key_idx & 0xff;
	p[1] &= 0xf0; 
	p[1] |= (key_idx >> 8) & 0x0f;
}
static inline void SET_KEY_INDEX_H(u8 *p, u16 key_idx){
	p[1] &= 0x0f; 
	p[1] |= (key_idx & 0x0f) << 4;
	p[2] = (key_idx >> 4) & 0xff;
}
static inline void SET_KEY_INDEX(u8 *p, u16 key_idx_L, u16 key_idx_H){
	SET_KEY_INDEX_L(p, key_idx_L);
	SET_KEY_INDEX_H(p, key_idx_H);
}

static inline int is_array_mask_en(u8 *mask, u32 mask_num)
{
    return (mask[mask_num / 8] & BIT(mask_num % 8));
}

static inline void set_array_mask_en(u8 *mask, u32 mask_num)
{
    mask[mask_num / 8] |= BIT(mask_num % 8);
}
#endif
//----------------------------------- key
#define NET_KEY_PRIMARY     (0)

#if 0 // (GATEWAY_ENABLE || (__LIB_EN__ && __PROJECT_MESH_PRO__))
#define NET_KEY_MAX         (3)		// count in node
#else
#define NET_KEY_MAX         (2)		// count in node
#endif
#define APP_KEY_MAX         (2)		// count in node

#define NET_KEY_LIST_MAX_PROV	(1)		// count in provisioner
#define APP_KEY_LIST_MAX_PROV	(5)		// count in provisioner

//#define NET_KEY_SEL_DEF		(0)
//#define APP_KEY_SEL_DEF		(0)

enum{
	NET0 = NET_KEY_PRIMARY,
};

enum{
	NET0_APP0 = 0x88,	// must not 0, because PTS use 0 as default.
	NET0_APP1 = 1,
	NET0_APP2 = 2,
	NET0_APP3 = 3,
};

#define IV_UPDATE_START_SNO             (0xC00000)  // margin should be enough, because sometimes can't keep 96 hour powered. so, should be enough margin to restart iv update flow next power up. 
#if IV_UPDATE_TEST_EN
#define IV_UPDATE_KEEP_TMIE_MIN_S       (3*60)// 3 minutes
#define IV_UPDATE_KEEP_TMIE_MIN_RX_S    (3*60)// 3 minutes
#else
#define IV_UPDATE_KEEP_TMIE_MIN_S       (96*3600)//(96*3600)       // 96 hour
#define IV_UPDATE_KEEP_TMIE_MIN_RX_S    (96*3600)//(96*3600)       // 96 hour
#endif

#define	IV_IDX_CUR		0x00000000	// don't change, because of compatibility in factory mode.

#define DEVKEY_DEF 		{0x9d,0x6d,0xd0,0xe9,0x6e,0xb2,0x5d,0xc1, 0x9a,0x40,0xed,0x99,0x14,0xf8,0xf0,0x3f}

#define NETKEY_A 		{0x7d,0xd7,0x36,0x4c,0xd8,0x42,0xad,0x18, 0xc1,0x7c,0x74,0x65,0x6c,0x69,0x6e,0x6b}
#define APPKEY_A		{0x63,0x96,0x47,0x71,0x73,0x4f,0xbd,0x76, 0xe3,0xb4,0x74,0x65,0x6c,0x69,0x6e,0x6b}
#define APPKEY_B		{0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7, 0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf}
#define APPKEY_C		{0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7, 0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf}
#define APPKEY_D		{0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7, 0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf}

#define APPKEY_E		{0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7, 0xe8,0xe9,0xea,0xeb,0xec,0xed,0xee,0xef}
#define APPKEY_F		{0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7, 0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff}

typedef struct{
	u8 valid;
	u16 appkey_idx;
	u8 rsv[13];
	u8 appkey[16];
}VC_appkey_idx_list_t;

typedef struct{
	u8 valid;
	u16 netkey_idx;
	u8 rsv[13];
	u8 netkey[16];
	VC_appkey_idx_list_t appkey[APP_KEY_LIST_MAX_PROV];
}VC_key_idx_list_t;

extern _align_4_ VC_key_idx_list_t VC_key_idx_list[NET_KEY_LIST_MAX_PROV];

enum{
	BIND_NONE	= 0,
	BIND_OK 	= 1,
};

enum{
	KEY_INDEX_NOT_EXIST = 0,
	KEY_INDEX_EXIST_AND_KEY_SAME,
	KEY_INDEX_EXIST_AND_KEY_DIFF,
};

#define SIZEOF_TWO_INDEX				(3)	// NOTE: C++: sizeof(key_idx_enc_t) == 4

#define STATUS_NONE                     (0xffffffff)
#define STATUS_NONE_VENDOR_OP_VC        (0x00)  // must 0
#define TID_NONE_VENDOR_OP_VC           (0x00)  // must 0

// SIG model
#define SIG_MD_CFG_SERVER               0x0000  // for test high byte
#define SIG_MD_CFG_CLIENT               0x0001
#define SIG_MD_HEALTH_SERVER            0x0002
#define SIG_MD_HEALTH_CLIENT            0x0003
#if !DRAFT_FEAT_VD_MD_EN
#define SIG_MD_REMOTE_PROV_SERVER       0x0004
#define SIG_MD_REMOTE_PROV_CLIENT       0x0005
#endif
#define SIG_MD_DF_CFG_S					0x0006
#define SIG_MD_DF_CFG_C					0x0007
#define SIG_MD_BRIDGE_CFG_SERVER		0x0008
#define SIG_MD_BRIDGE_CFG_CLIENT		0x0009
#define SIG_MD_PRIVATE_BEACON_SERVER 	0x000a
#define SIG_MD_PRIVATE_BEACON_CLIENT	0x000b

#define SIG_MD_ON_DEMAND_PROXY_S		0x000C
#define SIG_MD_ON_DEMAND_PROXY_C		0x000D
#define SIG_MD_SAR_CFG_S				0x000E
#define SIG_MD_SAR_CFG_C				0x000F
#define SIG_MD_OP_AGG_S					0x0010
#define SIG_MD_OP_AGG_C					0x0011
#define SIG_MD_LARGE_CPS_S				0x0012
#define SIG_MD_LARGE_CPS_C				0x0013
#define SIG_MD_SOLI_PDU_RPL_CFG_S		0x0014
#define SIG_MD_SOLI_PDU_RPL_CFG_C		0x0015


#define SIG_MD_G_ONOFF_S                0x1000
#define SIG_MD_G_ONOFF_C                0x1001
#define SIG_MD_G_LEVEL_S                0x1002
#define SIG_MD_G_LEVEL_C                0x1003
#define SIG_MD_G_DEF_TRANSIT_TIME_S     0x1004
#define SIG_MD_G_DEF_TRANSIT_TIME_C     0x1005
#define SIG_MD_G_POWER_ONOFF_S          0x1006
#define SIG_MD_G_POWER_ONOFF_SETUP_S    0x1007
#define SIG_MD_G_POWER_ONOFF_C          0x1008
#define SIG_MD_G_POWER_LEVEL_S          0x1009
#define SIG_MD_G_POWER_LEVEL_SETUP_S    0x100A
#define SIG_MD_G_POWER_LEVEL_C          0x100B
#define SIG_MD_G_BAT_S          		0x100C
#define SIG_MD_G_BAT_C          		0x100D
#define SIG_MD_G_LOCATION_S          	0x100E
#define SIG_MD_G_LOCATION_SETUP_S       0x100F
#define SIG_MD_G_LOCATION_C          	0x1010
#define SIG_MD_G_ADMIN_PROP_S          	0x1011
#define SIG_MD_G_MFG_PROP_S          	0x1012
#define SIG_MD_G_USER_PROP_S          	0x1013
#define SIG_MD_G_CLIENT_PROP_S          0x1014
#define SIG_MD_G_PROP_C          		0x1015
// --------
#define SIG_MD_SENSOR_S              	0x1100
#define SIG_MD_SENSOR_SETUP_S        	0x1101
#define SIG_MD_SENSOR_C              	0x1102
// --------
#define SIG_MD_TIME_S              		0x1200
#define SIG_MD_TIME_SETUP_S        		0x1201
#define SIG_MD_TIME_C              		0x1202
#define SIG_MD_SCENE_S              	0x1203
#define SIG_MD_SCENE_SETUP_S        	0x1204
#define SIG_MD_SCENE_C              	0x1205
#define SIG_MD_SCHED_S              	0x1206
#define SIG_MD_SCHED_SETUP_S        	0x1207
#define SIG_MD_SCHED_C              	0x1208
// --------
#define SIG_MD_LIGHTNESS_S              0x1300
#define SIG_MD_LIGHTNESS_SETUP_S        0x1301
#define SIG_MD_LIGHTNESS_C              0x1302
#define SIG_MD_LIGHT_CTL_S              0x1303
#define SIG_MD_LIGHT_CTL_SETUP_S        0x1304
#define SIG_MD_LIGHT_CTL_C              0x1305
#define SIG_MD_LIGHT_CTL_TEMP_S         0x1306
#define SIG_MD_LIGHT_HSL_S              0x1307
#define SIG_MD_LIGHT_HSL_SETUP_S        0x1308
#define SIG_MD_LIGHT_HSL_C              0x1309
#define SIG_MD_LIGHT_HSL_HUE_S          0x130A
#define SIG_MD_LIGHT_HSL_SAT_S          0x130B
#define SIG_MD_LIGHT_XYL_S              0x130C
#define SIG_MD_LIGHT_XYL_SETUP_S        0x130D
#define SIG_MD_LIGHT_XYL_C              0x130E
#define SIG_MD_LIGHT_LC_S              	0x130F
#define SIG_MD_LIGHT_LC_SETUP_S        	0x1310
#define SIG_MD_LIGHT_LC_C              	0x1311
// --------

//--------------------------------------- NLC profile ID
#define NLC_PROFILE_ID_ALSMP			0x1600
#define NLC_PROFILE_ID_BLCMP			0x1601
#define NLC_PROFILE_ID_BSSMP			0x1602
#define NLC_PROFILE_ID_DICMP			0x1603
#define NLC_PROFILE_ID_ENMMP			0x1604
#define NLC_PROFILE_ID_OCSMP			0x1605

//--------------------------------------- config model
#define NO_TX_RSP2SELF_EN               (!MD_CLIENT_EN)   // to save 

#if(0 == TESTCASE_FLAG_ENABLE)
	#if (GATEWAY_ENABLE&&__PROJECT_MESH_PRO__)
#define SUB_LIST_MAX                    (2)
	#else
#define SUB_LIST_MAX                    (8) 
	#endif
#else	
#define SUB_LIST_MAX                    (8)
#endif
#define VIRTUAL_ADDR_ENABLE				(SUB_LIST_MAX<=8)// disable virtual address to save ram
#define FIX_SIZE(sig_model)             (sig_model?2:0)

// net key
typedef struct{
	u16 idx;
	u8 key[16];
}mesh_netkey_set_t;

typedef struct{
	u8 st;
	u16 idx;
}mesh_netkey_status_t;

typedef struct{
	u8 key_idx_enc[(NET_KEY_MAX+1)/2][3];
}mesh_netkey_list_t;


// app key
typedef struct{
	u8 net_app_idx[3];		// can not set 24bit var IN vc
	u8 appkey[16];
}mesh_appkey_set_t;

typedef struct{
	u8 st;
	u8 net_app_idx[3];
}mesh_appkey_status_t;

#define AK_IDX_ENC_MAX		((APP_KEY_MAX+1)/2)

typedef struct{
	u16 netkey_idx;
}mesh_appkey_get_t;

typedef struct{
	u8 st;
	u16 netkey_idx;
	u8 appkey_idx_enc[AK_IDX_ENC_MAX][3];
}mesh_appkey_list_t;

typedef struct{
	u16 ele_adr;
	u32 model_id;
}mesh_md_app_get_t;

typedef struct{
	u8 st;
	u16 ele_adr;
	u32 model_id;
	u8 appkey_idx_enc[AK_IDX_ENC_MAX][3];
}mesh_sig_md_app_list_t;

typedef struct{
	u16 ele_adr;
	u16 index;
	u32 model_id;
}mesh_app_bind_t;

typedef struct{
	u8 st;
	mesh_app_bind_t bind;
}mesh_app_bind_status_t;

// key refresh
enum{
	KEY_REFRESH_NORMAL		= 0,
	KEY_REFRESH_PHASE1		= 1,
	KEY_REFRESH_PHASE2		= 2,
	KEY_REFRESH_PHASE3		= 3,
	KEY_REFRESH_TRANS2		= KEY_REFRESH_PHASE2,
	KEY_REFRESH_TRANS3		= KEY_REFRESH_PHASE3,
	KEY_REFRESH_STATE_MAX	= KEY_REFRESH_PHASE2,
};

typedef struct{
	u16 nk_idx;
}mesh_key_refresh_phase_get_t;

typedef struct{
	u16 nk_idx;
	u8 transition;
}mesh_key_refresh_phase_set_t;

typedef struct{
	u8 st;
	u16 nk_idx;
	u8 phase;
}mesh_key_refresh_phase_status_t;

typedef struct{
	u16 nk_idx;
}mesh_node_identity_get_t;

typedef struct{
	u16 nk_idx;
	u8 identity;
}mesh_node_identity_set_t;

typedef struct{
	u8 st;
	u16 nk_idx;
	u8 identity;
}mesh_node_identity_status_t;

typedef struct{
	u16 lpn_adr;
	u32 timeout; // only use 24-bit
}mesh_lpn_poll_timeout_status_t;

// publication
#define TRANSITION_STEP_RES_100MS   (0)
#define TRANSITION_STEP_RES_1S      (1)
#define TRANSITION_STEP_RES_10S     (2)
#define TRANSITION_STEP_RES_10MIN   (3)

#define GET_TRANSITION_TIME_WITH_STEP(val, step)    ((val & 0x3F) | ((step << 6) & 0xC0))

enum{				// unit 100ms
    RES_100MS 	= 1,
    RES_1S		= 1*10,
    RES_10S		= 10*10,
    RES_10MIN	= 600*10,
};

typedef struct{
	u8 steps    :6;
	u8 res      :2;	
}mesh_pub_period_t;

typedef struct{
    union{
        u8 val;
        struct{
			u8 steps    :6;
			u8 res      :2;	
		};
	};
}trans_time_t;

typedef struct{
    union{
        u8 val;
        struct{
			u8 count      :3;
			u8 invl_steps :5;
		};
	};
}mesh_transmit_t;

typedef struct{
	u8 sar_seg_invl_step:4;
	u8 sar_uni_retrans_cnt:4;
	u8 sar_uni_retrans_cnt_no_ack:4;
	u8 sar_uni_retrans_invl_step:4;
	u8 sar_uni_retrans_invl_incre:4;
	u8 sar_multi_retrans_cnt:4;
	u8 sar_multi_retrans_invl:4;
	u8 rfu:4;
}sar_transmitter_t;

typedef struct{
	u8 sar_seg_thres:5;
	u8 sar_ack_delay_inc:3;	
#if 0 // pts revert the para
	u8 sar_rcv_seg_invl_step:4;
	u8 sar_discard_timeout:4;
#else
	u8 sar_discard_timeout:4;
	u8 sar_rcv_seg_invl_step:4;	
#endif
	u8 sar_ack_retrans_cnt:2;
	u8 rfu:6;
}sar_receiver_t;

typedef struct{
	u8 par_type;
	struct{
		u8 step:1;  // unit: 0:10ms 1:100ms
		u8 count:7;
	};
	u16 start_tick;
}bear_delay_t;

typedef struct{
	u8 relay;
	mesh_transmit_t transmit;
}mesh_cfg_model_relay_set_t;

typedef struct{
	u16 appkey_idx      :12;
	u16 credential_flag :1;
	u16 rfu             :3;
	u8 ttl;
	mesh_pub_period_t period;
	mesh_transmit_t transmit;
}mesh_model_pub_par_t;

typedef struct{
	u16 ele_adr;
	u16 pub_adr;
	mesh_model_pub_par_t pub_par;
	u32 model_id;
}mesh_cfg_model_pub_set_t;

typedef struct{
	u16 ele_adr;
	u32 model_id;
}mesh_cfg_model_pub_get_t;

typedef struct{
	u8 status;
	mesh_cfg_model_pub_set_t set;
}mesh_cfg_model_pub_st_t;

typedef struct{
	u16 ele_adr;
	u8 pub_uuid[16];             // lab UUID(virtual addr)
	mesh_model_pub_par_t pub_par;
	u32 model_id;
}mesh_cfg_model_pub_virtual_set_t;

// subscription
typedef struct{
	u16 ele_adr;
	u16 sub_adr;    // only group adr (not include 0xffff, virtual adr)
	u32 model_id;
}mesh_cfg_model_sub_set_t;  // add, del, over write

typedef struct{
	u16 ele_adr;
	u8 sub_uuid[16];             // lab UUID(virtual addr)
	u32 model_id;
}mesh_cfg_model_sub_virtual_set_t;  // add, del, over write

typedef struct{
	u16 ele_adr;
	u32 model_id;
}mesh_cfg_model_sub_del_all_t;

typedef struct{
	u8 status;
	mesh_cfg_model_sub_set_t set;
}mesh_cfg_model_sub_status_t;

typedef struct{
	u16 ele_adr;
	u16 model_id;
}mesh_cfg_model_sub_get_sig_t;

typedef struct{
	u16 ele_adr;
	u32 model_id;
}mesh_cfg_model_sub_get_vendor_t;

typedef struct{
	u8 status;
	u16 ele_adr;
	u16 model_id;
	u16 sub_adr[SUB_LIST_MAX];
}mesh_cfg_model_sub_list_sig_t;

typedef struct{
	u8 status;
	u16 ele_adr;
	u32 model_id;
	u16 sub_adr[SUB_LIST_MAX];
}mesh_cfg_model_sub_list_vendor_t;

//--------------------------------------- generic model
enum{
    PAR_TYPE_PUB_ADR = 0,
    PAR_TYPE_ONLINE_ALL = 1,
    PAR_TYPE_SET_MAC = 2,
    //= 3,  // wait for reuse
    PAR_TYPE_SET_NODE_ADR = 4,
};

enum{
    PAR2USB_MONITOR_MODE 				= 0,
    PAR2USB_MONITOR_FILTER_SNO 			= 1,
    PAR2USB_MONITOR_SELECT_CHN			= 2,
    PAR2USB_MONITOR_UNPROVISION_BEACON 	= 3,
    PAR2USB_MONITOR_SECURE_NW_BEACON 	= 4,
};

enum{
    CMD_NO_ACK 	= 0,
    CMD_ACK 	= 1,
};

enum{
    G_OFF = 0,
    G_ON  = 1,
    G_ONOFF_RSV = 2,
};

enum{
    TRANSITION_STEP_MAX = 0x3E,
};

enum{
	ST_G_LEVEL_SET_PUB_NONE = 0,
	ST_G_LEVEL_SET_PUB_NOW = 1,     // right now
	ST_G_LEVEL_SET_PUB_TRANS = 2,
};

typedef struct{
	union{
		u8 transit_t;
		struct{
			u8 steps	:6;
			u8 res		:2; 
		};
	};
	u8 delay;
}transition_par_t;

#define GET_TRANSITION_STEP(val)	(val & 0x3f)
static inline int is_transition_need(u8 transit_t, u8 delay)
{
    return (GET_TRANSITION_STEP(transit_t) || delay);
}

// --------------------------- dim2dark_delay_ms:
//            _______ (target)
//	 	     /
//          /
//	  _____/ (min) dim2dark_delay_ms: time of "OFF -> min".
//   |
// __| (off)
// --------------------------- dim2dark_delay_ms end
typedef struct{
	u32 dim2dark_delay_ms;
	s16 target_val;		// include onoff and level
	s16 present_val;
	s16 level_move;     //
	u8 transit_t;
	u8 delay;
	u16 op;
}mesh_set_trans_t;

typedef struct{
	u8 onoff;
	u8 tid;
	u8 transit_t;
	u8 delay;		// unit 5ms
}mesh_cmd_g_onoff_set_t;

typedef struct{
	u8 present_onoff;
	u8 target_onoff;
	u8 remain_t;
#if MESH_RX_TEST
	u8 data[20];
#endif
}mesh_cmd_g_onoff_st_t;

typedef struct{
	s16 level;
	u8 tid;
	u8 transit_t;
	u8 delay;		// unit 5ms
}mesh_cmd_g_level_set_t;

typedef struct{
	s32 level;
	u8 tid;
	u8 transit_t;
	u8 delay;		// unit 5ms
}mesh_cmd_g_level_delta_t;

typedef struct{
	s16 level;
	u8 tid;
	u8 transit_t;
	u8 delay;		// unit 5ms
}mesh_cmd_g_level_move_t; // be same as mesh_cmd_g_level_set_t.

typedef struct{
	s16 present_level;
	s16 target_level;
	u8 remain_t;
}mesh_cmd_g_level_st_t;

enum{
    G_ON_POWERUP_OFF = 0,
    G_ON_POWERUP_ON,
    G_ON_POWERUP_SAVE,
    G_ON_POWERUP_MAX,
};

typedef struct{
	u16 power;
	u8 tid;
	u8 transit_t;
	u8 delay;
}mesh_cmd_g_power_set_t;

typedef struct{
	u16 present_power;
	u16 target_power;
	u8 remain_t;
}mesh_cmd_g_power_st_t;

typedef struct{
	u16 power;
}mesh_cmd_g_power_def_set_t;

enum{
    RANGE_SET_SUCCESS,
    RANGE_CANNOT_SET_MIN,
    RANGE_CANNOT_SET_MAX,
};

typedef struct{
	u16 min;
	u16 max;
}mesh_cmd_g_power_range_set_t;

typedef struct{
    u8 status;
	u16 min;
	u16 max;
}mesh_cmd_g_power_range_st_t;

#if 0
typedef struct{
	s16 val;
}mesh_model_g_level_t;

typedef struct{
	u16 linear;
	u16 current;
	u16 last;
	u16 def;
	u16 min;
	u16 max;
}mesh_model_g_lightness_t;
#endif


//--------------------------------------- node composition data
#ifndef LIGHT_CNT
#if (LIGHT_TYPE_SEL == LIGHT_TYPE_PANEL)
	#if __PROJECT_MESH_SWITCH__
		#if UI_BUTTON_MODE_ENABLE
#define LIGHT_CNT                       (1)     // means instance count
		#else
#define LIGHT_CNT						(4) 	// means instance count
		#endif
	#else
#define LIGHT_CNT                       (3)     // means instance count
	#endif
#elif (LIGHT_TYPE_SEL == LIGHT_TYPE_NLC_CTRL_CLIENT)
#define LIGHT_CNT                       (4)     // means instance count
#else
#define LIGHT_CNT                       (1)     // means instance count
#endif
#endif
#define ELE_CNT                         (LIGHT_CNT * ELE_CNT_EVERY_LIGHT)

//--------------------------------node extended and corresponding models start--------------
#if COMPOSITION_DATA_PAGE1_PRESENT_EN
#define MAX_EXTEND_MD_NUM							2

#define EXTEND_MD_ID_ARRAY_LIGHTNESS_SETUP_S		{SIG_MD_LIGHTNESS_S, SIG_MD_G_POWER_ONOFF_SETUP_S}
#define EXTEND_MD_ID_ARRAY_LIGHTNESS_S				{SIG_MD_G_LEVEL_S, SIG_MD_G_POWER_ONOFF_S}

#define EXTEND_MD_ID_ARRAY_POWER_ONOFF_SETUP_S		{SIG_MD_G_POWER_ONOFF_S, SIG_MD_G_DEF_TRANSIT_TIME_S}
#define EXTEND_MD_ID_ARRAY_POWER_ONOFF_S			{SIG_MD_G_ONOFF_S}

#define EXTEND_MD_ID_ARRAY_POWER_LEVEL_S			{SIG_MD_G_POWER_ONOFF_S, SIG_MD_G_LEVEL_S}
#define EXTEND_MD_ID_ARRAY_POWER_LEVEL_SETUP_S		{SIG_MD_G_POWER_LEVEL_S, SIG_MD_G_POWER_ONOFF_SETUP_S}		

#define EXTEND_MD_ID_ARRAY_LOCATION_SETUP_S			{SIG_MD_G_LOCATION_S}

#define EXTEND_MD_ID_ARRAY_ADMIN_PROP_S				{SIG_MD_G_USER_PROP_S}
#define EXTEND_MD_ID_ARRAY_MANU_PROP_S				{SIG_MD_G_USER_PROP_S}

#define EXTEND_MD_ID_ARRAY_SCENE_SETUP_S			{SIG_MD_SCENE_S, SIG_MD_G_DEF_TRANSIT_TIME_S}

#define EXTEND_MD_ID_ARRAY_LIGHT_CTL_SETUP_S		{SIG_MD_LIGHT_CTL_S, SIG_MD_LIGHTNESS_SETUP_S}			
#define EXTEND_MD_ID_ARRAY_LIGHT_CTL_S				{SIG_MD_LIGHTNESS_S}
#define EXTEND_MD_ID_ARRAY_LIGHT_CTL_TEMP_S			{SIG_MD_G_LEVEL_S}

#define EXTEND_MD_ID_ARRAY_LIGHT_LC_SETUP_S			{SIG_MD_LIGHT_LC_S}
#define EXTEND_MD_ID_ARRAY_LIGHT_LC_S				{SIG_MD_LIGHTNESS_S, SIG_MD_G_ONOFF_S}

#define EXTEND_MD_ID_ARRAY_LIGHT_HSL_S				{SIG_MD_LIGHTNESS_S}
#define EXTEND_MD_ID_ARRAY_LIGHT_HSL_HUE_S			{SIG_MD_G_LEVEL_S}
#define EXTEND_MD_ID_ARRAY_LIGHT_HSL_SAT_S			{SIG_MD_G_LEVEL_S}
#define EXTEND_MD_ID_ARRAY_LIGHT_HSL_SETUP_S		{SIG_MD_LIGHT_HSL_S, SIG_MD_LIGHTNESS_SETUP_S}

#define EXTEND_MD_ID_ARRAY_LIGHT_XYL_S				{SIG_MD_LIGHTNESS_S}
#define EXTEND_MD_ID_ARRAY_LIGHT_XYL_SETUP_S		{SIG_MD_LIGHT_XYL_S, SIG_MD_LIGHTNESS_SETUP_S}

//#define EXTEND_MD_ID_ARRAY_VENDOR_SETUP_S
enum{
	EXTEND_MD_SHORT_FORMAT = 0,
	EXTEND_MD_LONG_FORMAT = 1,
};

typedef struct{
	u8 nums;
	u8 numv;
}cps_page1_ele_head_t;

typedef struct{
	u8 group_id_present:1;
	u8 format:1;
	u8 extend_cnt:6;
	u8 group_id;
}cps_page1_md_item_t;

typedef struct{
	s8 ele_offset;
	u8 md_idx;
}cps_page1_extend_md_item_t;

typedef struct{
	u16 main_md;
	u16 extend_md[MAX_EXTEND_MD_NUM]; // u16, only sig models have extended model now.
}extend_model_map_t;

typedef struct{
	u16 md_id1;
	u16 md_id2;
}corresponding_model_map_t;

typedef struct{
	u16 md_id;
	u8  group_id;
}corresponding_model_t;
#endif
//--------------------------------node extended and corresponding models end--------------

enum{
    RELAY_SUPPORT_DISABLE = 0,  // supported
    RELAY_SUPPORT_ENABLE,
    RELAY_NOT_SUPPORT,
    RELAY_ST_MAX,
};

enum{
    NW_BEACON_NOT_BROADCASTING = 0,
    NW_BEACON_BROADCASTING,
    NW_BEACON_ST_MAX,
};

enum{
    GATT_PROXY_SUPPORT_DISABLE = 0,
    GATT_PROXY_SUPPORT_ENABLE,
    GATT_PROXY_NOT_SUPPORT,
    GATT_PROXY_ST_MAX,
};


enum{
	NODE_IDENTITY_SUB_NET_STOP =0,
	NODE_IDENTITY_SUB_NET_RUN ,
	NODE_IDENTITY_SUB_NET_NOT_SUPPORT,
	NODE_IDENTITY_SUB_NET_PROHIT,
};


enum{
    FRIEND_SUPPORT_DISABLE = 0,
    FRIEND_SUPPORT_ENABLE,
    FRIEND_NOT_SUPPORT,
    FRIEND_ST_MAX,
};

enum{
    LPN_SUPPORT_DISABLE = 0,
    LPN_SUPPORT_ENABLE,
    LPN_NOT_SUPPORT,
    LPN_ST_MAX,
};

typedef struct{
	u16 relay       :1;
	u16 proxy       :1;
	u16 frid      	:1;
	u16 low_power   :1;
	u16 rfu         :12;
}mesh_page_feature_t;

typedef struct{
	u16 cid;
	u16 pid;
	u16 vid;
	u16 crpl;
	mesh_page_feature_t feature;
}mesh_page0_head_t;

typedef struct{
	u16 loc;
	u8 nums;
	u8 numv;
	u16 md_sig[1];      // just pointer
	//u32 md_vendor[];
}mesh_element_head_t;

typedef struct{
	mesh_page0_head_t head;
	mesh_element_head_t ele;
	// other ele
}mesh_page0_t;

#define RX_TID_CNT      6
typedef struct{
    u32 tick_100ms;
    u16 adr;
    u8 tid;
    u8 rsv;
}mesh_tid_rx_t;

typedef struct{
    mesh_tid_rx_t rx[RX_TID_CNT];
    u8 tx[ELE_CNT];
}mesh_tid_t;

#if (WIN32 || (NET_KEY_MAX > 2 || APP_KEY_MAX > 2)) // (TLV_ENABLE) // can not change BIND_KEY_MAX, due to "model_common_t *" in library.
#define BIND_KEY_MAX		(APP_KEY_MAX * NET_KEY_MAX)
#else
#define BIND_KEY_MAX		(APP_KEY_MAX)   // confirm later, because of compatibility of flash save
#endif

typedef struct{
    u16 idx		:12;
    u16 rsv		:3;
    u16 bind_ok	:1;
}bind_key_t;

typedef int (*cb_pub_st_t) (u8 model_idx);

typedef struct{
    u16 ele_adr;    // use as primary address for model_sig_cfg_s_t
    u8 no_pub   :1;	// means not support publish function
    u8 no_sub   :1; // means not support subscription function; must before pub and sub par
    u8 pub_trans_flag :1; // transition process was ongoing flag.
    u8 pub_2nd_state  :1; // eg: lightness and lightness linear.
    u8 rsv2;
    bind_key_t bind_key[BIND_KEY_MAX];
	u8 pub_uuid[16];
	cb_pub_st_t cb_pub_st;	// no need to save, fix later
	u32 cb_tick_ms;		    // no need to save, fix later
	u16 pub_adr;    // pub_adr and pub_par must existed if sub_list existed //  offset:32
	mesh_model_pub_par_t pub_par;
	u8 directed_pub_policy;
	u16 sub_list[SUB_LIST_MAX];     // pub_adr, pub_par, sub_list must follow com if existed
#if VIRTUAL_ADDR_ENABLE
	u8 sub_uuid[SUB_LIST_MAX][16];
#endif
}model_common_t;

typedef struct{
    model_common_t com;             // must first
}model_client_common_t;



#define HEALTH_TEST_LEN		0x08

typedef struct{
	u8 test_id;
	u16 company_id;
	u8 fault_array[HEALTH_TEST_LEN];
	u8 cur_fault_idx;
}mesh_health_current_sts_t;

typedef struct{
	u8 test_id;
	u16 company_id;
	u8 fault_array[HEALTH_TEST_LEN];
	u8 cur_fault_idx;
}mesh_health_fault_sts_t;


typedef struct{
	u8 fast_period_log;
}mesh_health_period_status_t;

typedef struct{
	mesh_health_current_sts_t cur_sts;
	mesh_health_fault_sts_t   fault_sts;
	mesh_health_period_status_t period_sts;
	u8 test_id_list[HEALTH_TEST_LEN];
	u8 attention_timer;
	u16 dst_adr;
}mesh_health_mag_sts_t;

typedef struct{
	model_common_t com;
	mesh_health_mag_sts_t health_mag;
}model_health_common_t;

//--------------------SIG SERVER MODEL
typedef struct{
	u16 dst_adr;
	u16 cnt_val;
	u8 	cnt_log;
	u8  per_log;
	u8  ttl;
	u16 feature;
	u16 netkeyidx;
}mesh_heartbeat_pub_str;

typedef struct{
	u16 adr;
	u16 dst;
	u8 	per_log;
	u8  cnt_log;
	u8  min_hops;
	u8 	max_hops;
	u16 per_val;
	u16 cnt_val;
	u8  state;
	u32 tick;
}mesh_heartbeat_sub_str;

//--------------------SIG SERVER MODEL
typedef struct{
    model_common_t com;             // must first
    u8 rfu1[8];
	u8 sec_nw_beacon;
	u8 ttl_def;
	u8 gatt_proxy;
	u8 frid;
	u8 relay;
	mesh_transmit_t relay_retransmit;	// must after relay
	mesh_transmit_t nw_transmit;
	u8 net_key_list;	// wait for define struct
	u8 app_key_list;	// wait for define struct
	u8 md2app_key_list;	// wait for define struct
	u8 rfu2[2];
	mesh_heartbeat_pub_str hb_pub;
	mesh_heartbeat_sub_str hb_sub;
}model_sig_cfg_s_t;

typedef struct{
    model_common_t com;             // must first
}model_g_light_s_t;

typedef struct{
#if MD_SERVER_EN
	model_g_light_s_t srv[LIGHT_CNT];			// server
    #if MD_VENDOR_2ND_EN
    model_g_light_s_t srv2[LIGHT_CNT];           // server
    #endif
#endif
#if MD_CLIENT_VENDOR_EN
	model_client_common_t clnt[1];		        // client // if want to change clnt[1] to clnt[LIGHT_CNT], need to add ARRAY_SIZE(md_id_vendor_second) to CPS_DATA_ELE_SECOND.
#endif
}model_vd_light_t;

typedef struct{
#if MD_SERVER_EN
	model_g_light_s_t onoff_srv[LIGHT_CNT];			// server
    #if MD_LEVEL_EN
	model_g_light_s_t level_srv[LIGHT_CNT * ELE_CNT_EVERY_LIGHT];   // server, same with ELE CNT, the sequence refer to ST_TRANS_LIGHTNESS -- ST_TRANS_MAX 
    #endif
#endif
#if MD_CLIENT_EN
	model_client_common_t onoff_clnt[LIGHT_CNT];	        // client
	#if MD_LEVEL_EN
	model_client_common_t level_clnt[LIGHT_CNT];	        // client
	#endif
#endif
}model_g_onoff_level_t;

typedef struct{
	u64 valid_flag_or_idx	: 4;	// flag: when save;  index: in message
	u64 year		: 7;
	u64 month		: 12;
	u64 day			: 5;
	u64 hour		: 5;
	u64 minute		: 6;
	u64 second		: 6;
	u64 week        : 7;    // bit0 means monday,
	u64 action		: 4;
	u64 trans_t	    : 8;    // transition time
	u16 scene_id;
	u8 rand_hour;
	u8 rand_min;
	u8 rand_sec;
	u8 rsv;
}scheduler_t;

#define SIZE_SCHEDULER  (OFFSETOF(scheduler_t,rand_hour))

typedef struct{
#if MD_SERVER_EN
    #if MD_TIME_EN
	model_g_light_s_t time_srv[1];			        // server
	model_g_light_s_t time_setup[1];		        // server
    #endif
    #if MD_SCHEDULE_EN
	model_g_light_s_t sch_srv[LIGHT_CNT];			// server
	model_g_light_s_t sch_setup[LIGHT_CNT];			// server
    #endif
#endif
#if MD_CLIENT_EN
    #if MD_TIME_EN
    model_client_common_t time_clnt[1];             // client // only one time model is enough.
    #endif
    #if MD_SCHEDULE_EN
    model_client_common_t sch_clnt[1];              // client
    #endif
#endif
#if (MD_SCHEDULE_EN && MD_SERVER_EN)
    scheduler_t	schd_list[LIGHT_CNT][16];
#endif
}model_time_schedule_t;

#define g_schd_list     (model_sig_time_schedule.schd_list)

typedef struct{
#if MD_LIGHTNESS_EN
    #if MD_SERVER_EN
	model_g_light_s_t srv[LIGHT_CNT];			// server
	model_g_light_s_t setup[LIGHT_CNT];			// server
	#endif
    #if MD_CLIENT_EN
	model_client_common_t clnt[LIGHT_CNT];		        // client
    #endif
#endif
}model_lightness_t;

typedef struct{
#if MD_SERVER_EN
	model_g_light_s_t srv[LIGHT_CNT];			// server
	model_g_light_s_t setup[LIGHT_CNT];			// server
	model_g_light_s_t temp[LIGHT_CNT];			// server
#endif
#if MD_CLIENT_EN
	model_client_common_t clnt[LIGHT_CNT];		        // client
#endif
}model_light_ctl_t;

typedef struct{
#if MD_SERVER_EN
	model_g_light_s_t srv[LIGHT_CNT];			// server
	model_g_light_s_t setup[LIGHT_CNT];			// server
	model_g_light_s_t hue[LIGHT_CNT];			// server
	model_g_light_s_t sat[LIGHT_CNT];			// server
#endif
#if MD_CLIENT_EN
	model_client_common_t clnt[LIGHT_CNT];		        // client
#endif
}model_light_hsl_t;

typedef struct{
#if MD_SERVER_EN
	model_g_light_s_t srv[LIGHT_CNT];			// server
	model_g_light_s_t setup[LIGHT_CNT];			// server
#endif
#if MD_CLIENT_EN
	model_client_common_t clnt[LIGHT_CNT];		        // client
#endif
}model_light_xyl_t;

typedef struct{
	u16 len;        // exclude len
	u16 id;
	u8 val[4];      // max 3
}lc_prop_head_t;

typedef struct{
	u16 len;        // exclude len
	u16 id;
	void *p_val;
	u16 len_p_val;
	u16 type/*lc_prop_type_t*/;     // 4byte align
	u32 val_init;   // max 3 byte
}lc_prop_info_t;

typedef struct{
	u32 val     :24;    // unit: ms
}lc_prop_u24_t;     // property time            // Note: sizeof(bit-field 24) is 7 for eclipse, but 8 for VC.
#define LEN_LC_PROP_TIME            (3+2)   // sizeof(bit-field) error // sizeof(id + val)
#define LEN_LC_PROP_LIGHTNESS       (2+2)   // sizeof(id + val)

typedef struct{
	u32 val     :24;    
}lc_prop_luxlevel_t;
#define LEN_LC_PROP_LUXLEVEL        (3+2)   // sizeof(24bit) error for VC
#define LEN_LC_PROP_REGULATOR       (4+2)
#define LEN_LC_PROP_ACCURACY        (1+2)

#define LEN_LC_PROP_MAX		(sizeof(lc_prop_head_t)-OFFSETOF(lc_prop_head_t,id))

typedef struct{
	lc_prop_luxlevel_t LuxLevelOn;       // confirm 2 or 3 byte later
	lc_prop_luxlevel_t LuxLevelProlong;
	lc_prop_luxlevel_t LuxLevelStandby;
	u16 LightnessOn;
	u16 LightnessProlong;
	u16 LightnessStandby;
	u8  RegAccuracy;
	float RegKid;
	float RegKiu;
	float RegKpd;
	float RegKpu;
	lc_prop_u24_t TimeOccupancyDelay;
	lc_prop_u24_t TimeFadeOn;
	lc_prop_u24_t TimeRun;
	lc_prop_u24_t TimeFade;
	lc_prop_u24_t TimeProlong;
	lc_prop_u24_t TimeStandbyAuto;
	lc_prop_u24_t TimeStandbyManual;
}light_lc_property_t;

typedef struct{
#if MD_SERVER_EN
	model_g_light_s_t srv[LIGHT_CNT];			// server
	model_g_light_s_t setup[LIGHT_CNT];			// server
#endif
#if MD_CLIENT_EN
	model_client_common_t clnt[LIGHT_CNT];		        // client
#endif
#if MD_SERVER_EN
	light_lc_property_t propty[LIGHT_CNT];
	u8 mode[LIGHT_CNT];
	u8 om[LIGHT_CNT]; // Occupancy Mode
	u8 lc_onoff_target[LIGHT_CNT];
	u8 rsv[LIGHT_CNT][4];
#endif
}model_light_lc_t;

typedef struct{
#if MD_SERVER_EN
    #if MD_POWER_ONOFF_EN
	model_g_light_s_t pw_onoff_srv[LIGHT_CNT];			// server
	model_g_light_s_t pw_onoff_setup[LIGHT_CNT];			// server
    #endif
    #if MD_DEF_TRANSIT_TIME_EN
	model_g_light_s_t def_trans_time_srv[LIGHT_CNT];			// server
    #endif
#endif
#if MD_CLIENT_EN
    #if MD_POWER_ONOFF_EN
	model_client_common_t pw_onoff_clnt[1];		                // client
    #endif
    #if MD_DEF_TRANSIT_TIME_EN
	model_client_common_t def_trans_time_clnt[1];		        // client
    #endif
#endif
#if MD_SERVER_EN
	u8 on_powerup[LIGHT_CNT];               // can't delete
	trans_time_t trans_time[LIGHT_CNT];     // can't delete
#endif
}model_g_power_onoff_trans_time_t;

#define g_def_trans_time_val(idx)	(model_sig_g_power_onoff.trans_time[idx].val)

typedef struct{
#if MD_SERVER_EN
	model_g_light_s_t srv[LIGHT_CNT];			// server
	model_g_light_s_t setup[LIGHT_CNT];			// server
#endif
#if MD_CLIENT_EN
	model_client_common_t clnt[LIGHT_CNT];		        // client
#endif
}model_g_power_level_t;

#define SCENE_CNT_MAX			(16)

typedef struct{
	u16 id;
	s16 lightness_s16;
#if LIGHT_TYPE_CT_EN
	s16 temp_s16;
	s16 delta_uv_s16;
#endif
#if LIGHT_TYPE_HSL_EN
	s16 hue_s16;
	s16 sat_s16;
#endif
#if (LIGHT_TYPE_SEL == LIGHT_TYPE_XYL)
    s16 x_s16;
    s16 y_s16;
#endif
#if MD_LIGHT_CONTROL_EN //
    u8 lc_mode;
    u8 lc_onoff;
    u8 lc_om; // Occupancy Mode
	light_lc_property_t lc_propty; // MMDL/SR/LLCS/BV-02-C
#endif
#if LIGHT_TYPE_CT_EN
    u8 ct_flag;
    u8 rsv[3];
#else
	u8 rsv[4];
#endif
#if NL_API_ENABLE
	u8 nl_data[NL_VENDOR_SCENE_DATA_LENGTH];
#endif
}scene_data_t;

typedef struct{
#if MD_SERVER_EN
	model_g_light_s_t srv[LIGHT_CNT];			// server
	model_g_light_s_t setup[LIGHT_CNT];			// server
#endif
#if MD_CLIENT_EN
	model_client_common_t clnt[LIGHT_CNT];		        // client
#endif
#if MD_SERVER_EN
	scene_data_t data[LIGHT_CNT][SCENE_CNT_MAX];
#endif
}model_scene_t;



typedef struct{
	u32 battery_level:8;
	u32 discharge_time:24;
	u32 charge_time:24;
	u32 battery_flag:8;
}mesh_cmd_battery_st_t;

typedef struct{
	u32 global_latitude;
	u32 global_longitude;
	u16 global_altitude;
}mesh_cmd_location_global_st_t;

typedef struct{
	u16 local_north;
	u16 local_east;
	u16 local_altitude;
	u8 	floor_number;
	u16	uncertainty;
}mesh_cmd_location_local_st_t; 

typedef struct{
	mesh_cmd_location_global_st_t location_global;
	mesh_cmd_location_local_st_t  location_local;
}mesh_generic_location_t;

typedef struct{
#if 1 // MD_SERVER_EN, gateway also need ota.
	model_g_light_s_t fw_update_srv;		// server
	model_g_light_s_t blob_trans_srv;		// server
#endif
#if DISTRIBUTOR_UPDATE_CLIENT_EN
	model_client_common_t fw_distr_clnt;	// client
#endif
#if DISTRIBUTOR_UPDATE_SERVER_EN
    model_g_light_s_t fw_distr_srv;         // server
	model_client_common_t fw_update_clnt;	// client   // may use
	model_client_common_t blob_trans_clnt;	// client   // may use
#endif
#if MD_SERVER_EN
    // u32 rsv;    // remove later
#endif
}model_mesh_ota_t;

#define MESH_PROPERTY_STR_SIZE_MAX      (8)
#define MESH_PROPERTY_CNT_MAX           (1)

typedef struct{
    u8 len_val;
    u16 id;
    u8 access;
    u8 val[MESH_PROPERTY_STR_SIZE_MAX];
}mesh_property_t;

typedef struct{
#if MD_SERVER_EN
	model_g_light_s_t admin_srv[LIGHT_CNT];	    // serve
	model_g_light_s_t mfg_srv[LIGHT_CNT];	    // serve
	model_g_light_s_t user_srv[LIGHT_CNT];	    // serve
	model_g_light_s_t client_srv[LIGHT_CNT];    // serve
#endif
#if MD_CLIENT_EN
	model_client_common_t clnt[1];		        // client
#endif
#if MD_SERVER_EN
    mesh_property_t user_prop[MESH_PROPERTY_CNT_MAX];
    mesh_property_t client_prop[MESH_PROPERTY_CNT_MAX];
#endif
}model_property_t;

typedef struct{
	model_health_common_t srv;
	model_client_common_t clnt;
}model_health_t;
//--------------------VENDOR SERVER MODEL

//----------------------------------- key
typedef struct{
    u8 ek_f[16];    // friend
    u8 pk_f[16];
    u8 nid_f;		// friend
}friend_key_t;

typedef struct{
    u8 key[16]; // must at first, because mesh_tx_access_key_get()
    u8 aid;
    u16 index;
    u8 valid;
}mesh_app_key_t;

typedef struct{
    u8 ek_d[16];    // directed
    u8 pk_d[16];
    u8 nid_d;		// directed
}directed_key_t;

typedef struct{
    u8 key[16];		// network key
    u8 ek_m[16];    // master: encryption key
    u8 pk_m[16];	//             Privacy Key
    u8 ek_d[16];    // directed: encryption key
    u8 pk_d[16];	//             Privacy Key
    u8 idk[16];		// identity key
    u8 bk[16];		// beacon key
    u8 prik[16];    // privacy beacon key 
	u8 ident_hash[8];// identity hash 
	u8 priv_net_hash[8];
	u8 priv_ident_hash[8];
    u8 nw_id[8];    // network_id,    store in big endianness
    u8 nid_m;		// master: map to encryption key
    u8 nid_d;		// directed: map to encryption key
    u16 index;		// network key index
    u8 valid;
    u8 key_phase;
    u8 node_identity;
    u8 priv_identity;
	mesh_app_key_t app_key[APP_KEY_MAX];
	u32 start_identity_s;
	u32 priv_identity_s;
    u8 rfu3[8];		// for 16 align
}mesh_net_key_t;

#define DEC_BOTH_TWO_DEV_KEY        (2)    

typedef struct{
	u8 dev_key[16];	// device key, use as app key
	mesh_net_key_t net_key[NET_KEY_MAX][2];	// one is normal, another is key refresh
	u8 netkey_sel_dec;	// slecte network key index in array. valid netkey_idx in mesh_sec_msg_dec_apl() 
	u8 sec_type_sel;// security material: MASTER DIRECTED or DRIENDSHIP
	u8 appkey_sel_dec;	// slecte app key index in array.
	u8 devkey_self_dec;	// 0: use device key of TX node, 1: use device key of self (RX node).
	u8 new_netkey_dec;
}mesh_key_t;

typedef struct{
    u8 valid;
    u16 index;
    u8 node_identity;
	u8 priv_identity;
    u8 rfu[11];		// for 16 align
	u8 key[16];
	mesh_app_key_t app_key[APP_KEY_MAX];
}mesh_net_key_save_t;

#if WIN32
#define KEY_SAVE_ENCODE_ENABLE  0
#else
#define KEY_SAVE_ENCODE_ENABLE  1
#endif

#define KEY_SAVE_ENCODE_FLAG    (0x3A)

typedef struct{
	u8 dev_key[16];	// device key, use as app key
	mesh_net_key_save_t net_key[NET_KEY_MAX];
	u8 rfu0[14];
	u8 mic_val;
	u8 encode_flag;
}mesh_key_save_t;

// misc: sno
typedef struct{
    u32 sno;
    u8 ct_flag;
    u8 rfu1[2];
    u8 iv_update_trigger_flag;     // trigger by self or other
    u8 iv_index[4];	// big endianness
	#if VC_APP_ENABLE
	u16 unicast;
	u8 rfu2[6];
	#else
    u8 rfu2[8];
	#endif
	u8 user[8];
}misc_save_t;

typedef struct{
    u8 iv_index[4];	// big endianness
    u8 iv_update_trigger_flag;     // trigger by self or other
    u32 sno;
}misc_save_gw2vc_t;

enum{
    KEY_INVALID     = 0,        // must 0
    KEY_VALID       = 1,
};

enum{
    IV_UPDATE_NORMAL= 0,
    IV_UPDATE_STEP1 = 1,		// trigger
    IV_UPDATE_STEP2 = 2,		// change to normal from update status // also need to keep 96 hours
};

typedef struct{
	// iv index: if use "u32" means little endianness; "u8 [4]" means big endianness;
    u32 iv_cur;	// current iv index,  // little endianness in RAM. but big endianness when save to flash to keep compatibility.
    u32 iv_tx;	// little endianness
    u32 iv_rx;	// little endianness  // debug Note: it will be fresh by the beacon from other network.
    u32 keep_time_s;
    u8 searching_flag;
    u8 rx_update;   // receive iv index update flag
    u8 update_trigger_by_save;
    u8 update_proc_flag;
#if FEATURE_LOWPOWER_EN
    u8 rx_beacon_ok_after_searching; // have received beacon after entering recovery mode.
#endif
}mesh_iv_idx_st_t;

extern _align_4_ mesh_key_t mesh_key;
extern _align_4_ mesh_iv_idx_st_t iv_idx_st;

// provision par
typedef struct{
	u8 nk[16];
	u16 node_adr;
}mesh_prov_par_t;


#define MESH_MODEL_MISC_SAVE_EN		(MD_PRIVACY_BEA||MD_SAR_EN||MD_ON_DEMAND_PROXY_EN)
#if MESH_MODEL_MISC_SAVE_EN
// model with device key
// privacy_beacon
typedef struct{
	u8 beacon_sts;
	u8 random_inv_step;
	u8 proxy_sts;
	u8 identity_sts;	// not applicable now, instead by priv_identity
}mesh_privacy_beacon_save_t;

typedef struct{
#if 1 // MD_PRIVACY_BEA
	mesh_privacy_beacon_save_t privacy_bc;
#endif
#if 1 // MD_SAR_EN
	sar_transmitter_t sar_transmitter;
	sar_receiver_t sar_receiver;
#endif
#if 1 // MD_ON_DEMAND_PROXY_EN
	u8 on_demand_proxy;	// enable or disable "on demand proxy" function
#endif

	//reserve;
	u8 rfu[32];
}mesh_model_misc_save_t;

extern mesh_model_misc_save_t g_mesh_model_misc_save;
void mesh_model_misc_save();

static inline void mesh_privacy_beacon_save()
{
	mesh_model_misc_save();
}

static inline void mesh_model_sar_save()
{
	mesh_model_misc_save();
}

static inline void mesh_model_on_demand_save()
{
	mesh_model_misc_save();
}
#endif

// common save
#define FLASH_CHECK_SIZE_MAX	(64)
#define SIZE_SAVE_FLAG		(4)

typedef struct{
	u8 flag;
	u8 crc_en:1;
	u16 crc;
}mesh_save_head_t;

typedef struct{
    u32 adr_base;
    u8 *p_save_par;
    u32 *p_adr;
    u32 size_save_par;		// exclude save flag
}mesh_save_map_t;

#define MODEL_MAX_ONE_SECTOR	(6)

typedef struct{
    bool4 sig_model;
    u32 md_id[MODEL_MAX_ONE_SECTOR];
    u32 adr_base;
}mesh_md_adr_map_t;

extern const u32 mesh_save_map_array;
extern const mesh_save_map_t mesh_save_map[];

// ---------------
static inline u32 GET_LEVEL_PAR_LEN(int trans_flag){
	return (trans_flag ? sizeof(mesh_cmd_g_level_set_t) : 2);
}

static inline u32 GET_PAR_LEN_BY_TRANS(int len, int trans_flag){
	return (trans_flag ? len : len - 2);
}

extern u32 del_node_tick;
//--------------- declaration
int mesh_is_proxy_ready();
int app_event_handler_adv(u8 *p_payload, int src_type, u8 need_proxy_and_trans_par_val);
void mesh_gatt_bear_handle(u8 *bear);
void mesh_nw_pdu_from_gatt_handle(u8 *p_bear);
int mesh_adv_cmd_set(u8 *p_adv, u8 *p_bear);
void sleep_us_clear_dog(u32 us);
void mesh_loop_proc_prior();
void mesh_node_init();
int mesh_nid_check(u8 nid);
void mesh_friend_key_refresh(mesh_net_key_t *new_key);
void mesh_friend_key_RevokingOld(mesh_net_key_t *new_key);
void mesh_friend_key_update_all_nk(u8 lpn_idx, u8 nk_arr_idx);
void mesh_set_iv_idx_rx(u8 ivi);
void mesh_iv_idx_init_cb(int rst_sno);
void mesh_set_ele_adr(u16 adr);
void mesh_set_ele_adr_ll(u16 adr, int save, int reset_pub_flag);
int is_own_ele(u16 adr);
int is_ele_in_node(u16 ele_adr, u16 node_adr, u32 cnt);
int is_retransaction(u16 adr, u8 tid);

mesh_net_key_t * mesh_get_netkey_by_idx(u16 key_idx);
mesh_net_key_t * is_mesh_net_key_exist(u16 key_idx);
int is_netkey_index_prohibited(u16 key_idx);
int get_mesh_net_key_offset(u16 key_idx);
int is_net_key_save();
void model_pub_st_cb_re_init_lc_srv(cb_pub_st_t cb);
void model_pub_st_cb_re_init_sensor_setup(cb_pub_st_t cb);
u8 get_ele_cnt_by_traversal_cps(mesh_page0_t * p_page0, u32 len_page0);
u8 get_ele_offset_by_model(mesh_page0_t * p_page0, u32 len_page0, u16 node_adr, u16 obj_adr, u32 model_id, bool4 sig_model);
u16 get_primary_adr(u16 ele_adr);
u16 get_primary_adr_with_check(u16 node_adr, u16 ele_adr);
u8 * get_virtual_adr_uuid(u16 pub_adr, model_common_t *p_com_md);
int is_sno_exhausted();
int is_iv_update_keep_enough_time_ll();
int is_iv_update_keep_enough_time_rx();
void iv_index_read_print_test();
void iv_index_set_keep_time_test();
void iv_index_set_sno_test();
void iv_index_test_button_firmware();
void mesh_receive_ivi_plus_one_in_normal_cb();
void mesh_tx_reliable_start(u8 retry_cnt);
void mesh_tx_reliable_tick_refresh();

//--------------- save
void mesh_flash_save_check();
void mesh_flash_retrieve();
int mesh_key_retrieve();

void mesh_par_store(const u8 *in, u32 *p_adr, u32 adr_base, u32 size);
int mesh_par_retrieve(u8 *out, u32 *p_adr, u32 adr_base, u32 size);
int mesh_common_retrieve(u32 adr_base);
int mesh_common_store(u32 adr_base);
int mesh_model_retrieve(bool4 sig_model, u32 md_id);
void mesh_common_save_all_md();
int mesh_model_store(bool4 sig_model, u32 md_id);
void mesh_common_retrieve_cb(int err, u32 adr_base);
void mesh_common_reset_all();
void factory_test_key_bind(int bind_flag);
u32 mesh_net_key_find(u16 key_index);
u8 mesh_net_key_set(u16 op, const u8 *nk, u16 key_idx, int save);
u32 mesh_net_key_get(u8 *list);
void mesh_net_key_add_by_provision(u8 *nk, u16 key_index, u8 key_fresh_flag);
u8 mesh_app_key_set_and_bind(u16 netkey_idx, u8 *ak, u16 ak_idx, int save);
void mesh_app_key_set_default(u16 netkey_idx, int save);
u8 mesh_app_key_set(u16 op, const u8 *ak, u16 app_key_idx, u16 net_key_idx, int save);
u32 mesh_app_key_get(u8 *list);
void set_dev_key(u8 *dev_key);
int is_exist_valid_network_key();
void mesh_key_save();
void appkey_bind_all(int bind_flag, u16 ak_idx, int fac_filter_en);
void mesh_key_flash_sector_init();
u32 get_all_appkey_cnt();
int get_mesh_adv_interval();
int get_mesh_tx_delay_ms(bear_delay_t *p_bear);
void set_mesh_bear_tx_delay(u8 *p, int delay_ms);

void VC_node_info_retrieve();
u8 * VC_master_get_other_node_dev_key(u16 adr);
u8 VC_node_cps_save(mesh_page0_t * p_page0,u16 unicast, u32 len_cps);
u8 VC_search_and_bind_model();

u8 * mesh_cfg_cmd_dev_key_get(const u16 adr);
mesh_app_key_t * mesh_app_key_search_by_index(u16 netkey_idx, u16 appkey_idx);
u8 get_nk_arr_idx(u16 netkey_idx);
u8 get_ak_arr_idx(u8 nk_array_idx, u16 appkey_idx);
u8 get_ak_arr_idx_first_valid(u8 nk_array_idx);
u8 get_nk_arr_idx_first_valid();
mesh_net_key_t *get_nk_first_valid();
mesh_net_key_t *get_nk_primary();

u8 GetNKArrayIdxByPointer(mesh_net_key_t *key);

mesh_app_key_t *mesh_tx_access_key_get(u8 *mat, u8 akf);
void mesh_misc_store();
void mesh_factory_test_mode_en(u8 en);
void mesh_adv_txrx_to_self_en(u8 en);
int is_valid_cfg_op_when_factory_test(u16 op);
int is_activated_factory_test_mode();
void APP_set_vd_id_mesh_save_map(u16 vd_id);
int is_mesh_latency_window();
void proc_node_reset();
u32 node_reset_start(u16 adr_src);
void client_node_reset_cb(u16 adr_dst);
int is_support_model_dst(u16 dst_adr, u32 model_id, bool4 sig_model);
int is_support_op_dst(u16 op, u16 adr_dst);     // provisioner check dst unicast when tx command.
int is_support_op_dst_VC_APP(u16 op, u16 adr_dst);
u32 get_random_delay_pub_tick_ms(u32 interval_ms);
void mesh_pub_period_proc();
int is_tx_status_cmd2self(u16 op, u16 adr_dst);
u8 mesh_sub_search_ele_and_set(u16 op, u16 ele_adr, u16 sub_adr, u8 *uuid, u32 model_id, bool4 sig_model);
void mesh_service_change_report();
#define MESH_PARA_RETRIEVE_VAL      1
#define MESH_PARA_STORE_VAL         0
int mesh_par_retrieve_store_win32(u8 *in_out, u32 *p_adr, u32 adr_base, u32 size,u8 flag);
void mesh_seg_rx_init();
void mesh_seg_ack_poll_rx();
int is_retrans_segment_done();
void mesh_seg_ack_poll_tx();
void blc_pm_select_none();

void mesh_key_node_identity_init(); // after power on ,we need to detect the flag ,and set timer part 
void mesh_key_node_identity_set_prov_set();
void mesh_switch_identity_proc();// run in loop
int is_pkt_notify_only(u16 dst_adr, int relay_flag);
u32 get_reliable_interval_ms_min();
void prov_random_proc(u8 *p_random);
void mesh_node_refresh_binding_tick();
u64 mul32x32_64(u32 a, u32 b);
void mesh_private_identity_change_by_proxy_service(mesh_net_key_t *p_netkey);
int rf_link_get_op_para(u8 *ac,  int len_ac, u16 *op, u8 **params, int *par_len);
int rf_link_get_vendor_op_para_extend(u8 *ac,  int len_ac, u16 *op, u8 **params, int *par_len);
u32 is_op_need_extend_and_fill_op_par(u16 op, u8 *ac_sig_out, u8 *par, u32 par_len);
u32 is_op_need_extend_and_remove_op_par(u8 *rc_rsp_data, u8 *ac, int len_ac);
int is_client_tx_extend_model(u16 model);
u16 get_vendor2sig_op(u16 op, u8 *p_sig_op);
int is_rx_need_extend_invalid_model(u16 model, int get_op_st);
u32 get_cps_vendor_op_extend(u8 *cps_out);
bind_key_t * is_exist_bind_key_extend_op(u16 appkey_idx);
int is_mesh_adv_cmd_fifo_empty();
u8 * mesh_cfg_cmd_dev_key_candi_get(const u16 adr);
void mesh_tx_en_devkey_candi(u8 en);
u8 mesh_cps_data_page0_page128_is_same();
u8 mesh_cps_data_update_page0_from_page128();
u32 get_crc32_16bytes(unsigned long crc_init, unsigned char* data);
u32 get_blk_crc_tlk_type2(u32 crc_init, u8 *data, u32 len);
int is_valid_tlk_fw_buf(u8 *p_flag);
void power_on_io_proc(u8 i);
unsigned char ble_module_id_is_kmadongle();
void mesh_blc_ll_initExtendedAdv();
u8 mesh_blc_ll_setExtAdvParamAndEnable();
void mesh_blc_ll_setExtAdvData(u8 adv_pdu_len, u8 *data);
void mesh_ivi_event_cb(u8 search_flag);
void mesh_netkey_cb(u8 idx,u16 op);
void send_and_wait_completed_reset_node_status();
void mesh_node_identity_refresh();
int is_rx_seg_reject_before(u16 src_addr, u32 seqAuth);
void add2rx_seg_reject_cache(u16 src_addr, u32 seqAuth);
#if (!WIN32 && (MCU_CORE_TYPE >= MCU_CORE_8258))
void sys_clock_init(SYS_CLK_TypeDef SYS_CLK);
#endif
int gateway_upload_ividx(misc_save_gw2vc_t *p_misc);
u32 mesh_sno_get_save_delta();

extern u16 ele_adr_primary;
extern u8 g_ele_cnt;
extern u8 g_bind_key_max;
extern u8 key_bind_all_ele_en;
extern u16 connect_addr_gatt;
extern u32 prov_app_key_setup_tick;

//#define node_unprovision_flag   (!is_provision_success())
extern u8 node_need_store_misc;
extern u32 node_binding_tick;
extern u8 factory_test_mode_en;
extern u8 factory_test_cache_not_equal_mode_en;
extern u8 mesh_adv_txrx_self_en;
extern _align_4_ mesh_tid_t mesh_tid;
extern u8 my_rf_power_index;
extern u8 tx_bear_extend_en;
extern u8 proxy_message_between_gatt_and_adv_en;
//------------model
extern /*const */mesh_page0_t * const gp_page0;
#define cps_cid                (gp_page0->head.cid)
extern const u32                SIZE_OF_PAGE0_LOCAL;
extern _align_4_ model_sig_cfg_s_t 		model_sig_cfg_s;
extern _align_4_ model_client_common_t 	model_sig_cfg_c;

extern _align_4_ model_health_t 			model_sig_health;

extern _align_4_ model_g_onoff_level_t    model_sig_g_onoff_level;
extern _align_4_ model_lightness_t       	model_sig_lightness;
extern _align_4_ model_light_ctl_t       	model_sig_light_ctl;
extern _align_4_ model_light_hsl_t       	model_sig_light_hsl;
extern _align_4_ model_light_xyl_t       	model_sig_light_xyl;
extern _align_4_ model_light_lc_t       	model_sig_light_lc;
extern _align_4_ model_scene_t			model_sig_scene;
extern _align_4_ model_time_schedule_t	model_sig_time_schedule;
extern _align_4_ model_g_power_onoff_trans_time_t    model_sig_g_power_onoff;
extern _align_4_ model_mesh_ota_t        	model_mesh_ota;
// extern model_g_power_level_t    model_sig_g_power_level; // share with model_sig_lightness

extern _align_4_ model_vd_light_t       	model_vd_light;
extern _align_4_ mesh_key_t mesh_key; 
extern _align_4_ friend_key_t mesh_fri_key_lpn[NET_KEY_MAX][2];
extern _align_4_ friend_key_t mesh_fri_key_fn[MAX_LPN_NUM][2];
extern _align_4_ directed_key_t directed_key[NET_KEY_MAX][2];
extern s8 rssi_pkt; // have been -110

extern u8 pts_test_en;
extern const u16 my_fwRevisionUUID;
extern u8 my_fwRevisionCharacter;
#define FW_REVISION_VALUE_LEN       (16)
extern const u8  my_fwRevision_value [FW_REVISION_VALUE_LEN];
extern u8 g_gw_extend_adv_option;

typedef struct{
	u16 major 			:4;
	u16 spec 			:4;
	u16 second_minor	:4;
	u16 minor 			:4;
}sw_version_big_endian_t;

#define TEST_CNT 100
typedef struct{
	u8 rcv_cnt;
	u8 ack_par_len;
	u8 send_index;
	u16 max_time;
	u16 min_time;
	u16 avr_time;
	u16 rcv_time[TEST_CNT];
	u32 send_tick;
} mesh_rcv_t;

#define EXTEND_PROVISION_FLAG_OP		(0xFFFF)	// use a special op to represent provision data, no valid op is equal to this.
#define PUBLISH_CHECK_INIT_DELAY		(40*1000) // period pub need delay

enum{
    EXTEND_ADV_OPTION_NONE      = 0,    // not support extend adv
    EXTEND_ADV_OPTION_OTA_ONLY  = 1,    // only mesh OTA command use extend adv
    EXTEND_ADV_OPTION_ALL       = 2,    // all command use extend adv
    EXTEND_ADV_OPTION_MAX,
};

enum{
	CPU_POWER_RESET,
	CPU_WATCHDOG_RESET,
	CPU_PAD_WAKEUP,
	CPU_TIMER_WAKEUP,
};

int get_cpu_wakeup_source();
void set_mesh_ota_distribute_100_flag();
void clr_mesh_ota_distribute_100_flag();
int is_mesh_ota_distribute_100_flag();

#define set_ota_gatt_connected_flag_lpn		set_mesh_ota_distribute_100_flag
#define clr_ota_gatt_connected_flag_lpn		clr_mesh_ota_distribute_100_flag
#define is_ota_gatt_connected_flag_lpn		is_mesh_ota_distribute_100_flag

extern u8 update_key_by_bridge_flag;
