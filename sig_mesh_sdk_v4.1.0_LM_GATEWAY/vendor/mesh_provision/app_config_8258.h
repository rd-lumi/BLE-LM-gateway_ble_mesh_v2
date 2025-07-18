/********************************************************************************************************
 * @file	app_config_8258.h
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

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

#include "vendor/common/version.h"    // include mesh_config.h inside.
//////////////////board sel/////////////////////////////////////
#define PCBA_8258_DONGLE_48PIN          1
#define PCBA_8258_C1T139A30_V1_0        2
#define PCBA_8258_C1T139A30_V1_2        3

#ifndef PCBA_8258_SEL // user can define in user_app_config.h
#define PCBA_8258_SEL			PCBA_8258_DONGLE_48PIN
#endif


#define _USER_CONFIG_DEFINED_	1	// must define this macro to make others known
#define	__LOG_RT_ENABLE__		0

#define GATEWAY_ENABLE			1
//#define	__DEBUG_PRINT__			0
//////////// product  Information  //////////////////////////////
#define ID_VENDOR				0x248a			// for report
#define ID_PRODUCT_BASE			0x880C
#define STRING_VENDOR			L"Telink"
#define STRING_PRODUCT			L"BLE Mesh"
#define STRING_SERIAL			L"TLSR825X"

#define DEV_NAME                "SigMesh"

#define APPLICATION_DONGLE		0					// or else APPLICATION_DEVICE
#define	USB_PRINTER				1
#define	FLOW_NO_OS				1

// LUMI
#define MODIFY_RETRY_CNT_PROV_DATA_EN     1
#define LIGHT_OPT_VENDOR_ENABLE           1
#define LIGHT_AUTO_TRANS_VENDOR_ENABLE    1
#define CHECK_NULL_MESH_KEY_ENABLE        0

#define VENDOR_NO_TID                     0
#define OP_RESPONSE_UNKNOWN               0

///////////////////// CDTP ///////////////////////////////////////
#define MESH_CDTP_ENABLE							0
#if (MESH_CDTP_ENABLE)
#define LE_AUDIO_DEMO_ENABLE                    	1
#define L2CAP_CREDIT_BASED_FLOW_CONTROL_MODE_EN     1
#define SLAVE_COC_ENABLE                            1
#define APP_LOG_EN									1

#define CDTP_SMP_LEVEL								3 // must 3 or 4 // CDTP spec require SMP >= level 3
#endif

/////////////////////HCI ACCESS OPTIONS///////////////////////////////////////
#define HCI_USE_NONE	0
#define HCI_USE_UART	1
#define HCI_USE_USB		2

#ifndef HCI_ACCESS

#if SMART_PROVISION_ENABLE
#define HCI_ACCESS		HCI_USE_UART  // for reuse hci_rx_fifo and hci_tx_fifo callback
#else
#define HCI_ACCESS		HCI_USE_UART
#endif

#if (HCI_ACCESS==HCI_USE_UART)
#if (PCBA_8258_SEL == PCBA_8258_DONGLE_48PIN)
#define UART_TX_PIN		UART_TX_PD7
#define UART_RX_PIN		UART_RX_PA0
#else
#define UART_TX_PIN		UART_TX_PB1
#define UART_RX_PIN		UART_RX_PB0
#endif
#endif
#endif

#ifndef HCI_LOG_FW_EN
#define HCI_LOG_FW_EN   (0 || DEBUG_LOG_SETTING_DEVELOP_MODE_EN)
#if HCI_LOG_FW_EN
#define DEBUG_INFO_TX_PIN           		GPIO_PB2
#define PRINT_DEBUG_INFO                    1
#endif
#endif

#define BATT_CHECK_ENABLE       			1   //must enable
#if (BATT_CHECK_ENABLE)
//telink device: you must choose one gpio with adc function to output high level(voltage will equal to vbat), then use adc to measure high level voltage
	//use PC5 output high level, then adc measure this high level voltage
	#define GPIO_VBAT_DETECT				GPIO_PC5
	#define PC5_FUNC						AS_GPIO
	#define PC5_INPUT_ENABLE				0
	#define ADC_INPUT_PCHN					C5P    //corresponding  ADC_InputPchTypeDef in adc.h
#endif

#define ADC_ENABLE		0
#if ADC_ENABLE
#define ADC_BASE_MODE	1	//GPIO voltage
#define ADC_VBAT_MODE	2	//Battery Voltage

#define ADC_MODE		ADC_VBAT_MODE
#define ADC_CHNM_ANA_INPUT 		GPIO_PB3 // one of ADC_GPIO_tab[]
#define ADC_PRESCALER	ADC_PRESCALER_1F8
#endif

#define ONLINE_STATUS_EN        0
/////////////////// mesh project config /////////////////////////////////
#ifndef TRANSITION_TIME_DEFAULT_VAL
#define TRANSITION_TIME_DEFAULT_VAL (0x00)  // 0x41: 1 second // 0x00: means no default transition time
#endif

#define PROVISIONER_GATT_ADV_EN	    (0 || MESH_CDTP_ENABLE)

#if EXTENDED_ADV_ENABLE
#define MESH_DLE_MODE               MESH_DLE_MODE_EXTEND_BEAR
#define DLE_LEN_MAX_RX              (MAX_OCTETS_DATA_LEN_EXTENSION) // must MAX_OCTETS_DATA_LEN_EXTENSION
#define DLE_LEN_MAX_TX              (40)
#endif

/////////////////// MODULE /////////////////////////////////
#define BLE_REMOTE_PM_ENABLE			0
#define PM_DEEPSLEEP_RETENTION_ENABLE   0
#define BLE_REMOTE_SECURITY_ENABLE      (0 || MESH_CDTP_ENABLE)   // 1 for smp,  0 no security
#define BLE_IR_ENABLE					0

#ifndef BLT_SOFTWARE_TIMER_ENABLE
#define BLT_SOFTWARE_TIMER_ENABLE		0
#endif

//----------------------- keyboard --------------------------------
#if SMART_PROVISION_ENABLE
#define UI_KEYBOARD_ENABLE				1
#endif

#ifndef UI_KEYBOARD_ENABLE
#define UI_KEYBOARD_ENABLE				0
#endif

#if UI_KEYBOARD_ENABLE
#define	MATRIX_ROW_PULL					PM_PIN_PULLDOWN_100K // drive pin pull
#define	MATRIX_COL_PULL					PM_PIN_PULLUP_10K    // scan pin pull
			
#define	KB_LINE_HIGH_VALID				0   // dirve pin output 0 when keyscan(no drive pin in KB_LINE_MODE=1), scanpin read 0 is valid
#define DEEPBACK_FAST_KEYSCAN_ENABLE	1   //proc fast scan when deepsleep back triggered by key press, in case key loss
#define KEYSCAN_IRQ_TRIGGER_MODE		0
#define LONG_PRESS_KEY_POWER_OPTIMIZE	1   //lower power when pressing key without release
			
#define	KB_MAP_NUM				KB_MAP_NORMAL
#define	KB_MAP_FN				KB_MAP_NORMAL
			
	#if (PCBA_8258_SEL == PCBA_8258_DONGLE_48PIN)
// key mode, KB_LINE_MODE default 0(key matrix), set to 1 in button mode.
#define KB_LINE_MODE			1 			
			
// keymap
#define KEY_SW1					1
#define KEY_SW2					2
#define KB_MAP_NORMAL			{{KEY_SW1},	{KEY_SW2}}
			
#define KB_DRIVE_PINS			{GPIO_PD6} 	// just for compile, not driver pin in KB_LINE_MODE=1.
#define KB_SCAN_PINS			{GPIO_PD6, GPIO_PD5}
			
// scan pin as gpio
#define PD5_FUNC				AS_GPIO
#define PD6_FUNC				AS_GPIO
			
//scan	pin pullup
#define PULL_WAKEUP_SRC_PD6     PM_PIN_PULLUP_1M	//btn
#define PULL_WAKEUP_SRC_PD5     PM_PIN_PULLUP_1M	//btn
			
//scan pin open input to read gpio level
#define PD6_INPUT_ENABLE		1
#define PD5_INPUT_ENABLE		1
	#elif(PCBA_8258_SEL == PCBA_8258_C1T139A30_V1_0)    // PCBA_8258_C1T139A30_V1_0
// key mode, KB_LINE_MODE default 0(key matrix), set to 1 in button mode.
#define KB_LINE_MODE			1 			
			
// keymap
#define KEY_SW1					1
#define KEY_SW2					2
#define KB_MAP_NORMAL			{{KEY_SW1},	{KEY_SW2}}
			
#define KB_DRIVE_PINS			{GPIO_PD2} 	// just for compile, not driver pin in KB_LINE_MODE=1.
#define KB_SCAN_PINS			{GPIO_PD2, GPIO_PD1}
			
// scan pin as gpio
#define PD2_FUNC				AS_GPIO
#define PD1_FUNC				AS_GPIO
			
//scan	pin pullup
#define PULL_WAKEUP_SRC_PD2     PM_PIN_PULLUP_1M	//btn
#define PULL_WAKEUP_SRC_PD1     PM_PIN_PULLUP_1M	//btn
			
//scan pin open input to read gpio level
#define PD2_INPUT_ENABLE		1
#define PD1_INPUT_ENABLE		1
	#endif
#endif

//---------------  LED / PWM
#if(PCBA_8258_SEL == PCBA_8258_DONGLE_48PIN)
#define PWM_R       GPIO_PWM1A3		//red
#define PWM_G       GPIO_PWM0A2		//green
#define PWM_B       GPIO_PWM3B0		//blue
#define PWM_W       GPIO_PWM4B1		//white
#elif(PCBA_8258_SEL == PCBA_8258_C1T139A30_V1_0)   // PCBA_8258_DEVELOPMENT_BOARD
#define PWM_R       GPIO_PWM1ND3	//red
#define PWM_G       GPIO_PWM2ND4	//green
#define PWM_B       GPIO_PD5		//blue
#define PWM_W       GPIO_PWM3D2		//white
#elif(PCBA_8258_SEL == PCBA_8258_C1T139A30_V1_2)
#define PWM_R       GPIO_PD5	//red
#define PWM_G       GPIO_PWM1ND3	//green
#define PWM_B       GPIO_PWM3D2		//blue
#define PWM_W       GPIO_PWM2ND4		//white

#endif

#define PWM_FUNC_R  AS_PWM  // AS_PWM_SECOND
#define PWM_FUNC_G  AS_PWM  // AS_PWM_SECOND
#define PWM_FUNC_B  AS_PWM  // AS_PWM_SECOND
#define PWM_FUNC_W  AS_PWM  // AS_PWM_SECOND

#define PWMID_R     (GET_PWMID(PWM_R, PWM_FUNC_R))
#define PWMID_G     (GET_PWMID(PWM_G, PWM_FUNC_G))
#define PWMID_B     (GET_PWMID(PWM_B, PWM_FUNC_B))
#define PWMID_W     (GET_PWMID(PWM_W, PWM_FUNC_W))
                    
#define PWM_INV_R   (GET_PWM_INVERT_VAL(PWM_R, PWM_FUNC_R))
#define PWM_INV_G   (GET_PWM_INVERT_VAL(PWM_G, PWM_FUNC_G))
#define PWM_INV_B   (GET_PWM_INVERT_VAL(PWM_B, PWM_FUNC_B))
#define PWM_INV_W   (GET_PWM_INVERT_VAL(PWM_W, PWM_FUNC_W))

#ifndef GPIO_LED
#define GPIO_LED	PWM_R
#endif

////////////USB DP DM///////////////////////////////////////
#define PA5_FUNC			AS_USB
#define PA5_INPUT_ENABLE	1

#define PA6_FUNC			AS_USB
#define PA6_INPUT_ENABLE	1

/////////////open SWS digital pullup to prevent MCU err, this is must ////////////
#define PA7_DATA_OUT			1


/////////////////// Clock  /////////////////////////////////
#define	USE_SYS_TICK_PER_US
#define CLOCK_SYS_TYPE  		CLOCK_TYPE_PLL	//  one of the following:  CLOCK_TYPE_PLL, CLOCK_TYPE_OSC, CLOCK_TYPE_PAD, CLOCK_TYPE_ADC
#define CLOCK_SYS_CLOCK_HZ  	48000000

//////////////////Extern Crystal Type///////////////////////
#define CRYSTAL_TYPE			XTAL_12M		//  extern 12M crystal

/////////////////// watchdog  //////////////////////////////
#define MODULE_WATCHDOG_ENABLE		1
#define WATCHDOG_INIT_TIMEOUT		5000  //ms

/////////////////// set mesh   ////////////////
#define DONGLE_PROVISION_EN			1

/////////////////// set default   ////////////////

#include "../common/default_config.h"

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif
