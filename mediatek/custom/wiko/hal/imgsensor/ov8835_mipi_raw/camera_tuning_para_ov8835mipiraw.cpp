/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

/********************************************************************************************
 *     LEGAL DISCLAIMER
 *
 *     (Header of MediaTek Software/Firmware Release or Documentation)
 *
 *     BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 *     THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE") RECEIVED
 *     FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON AN "AS-IS" BASIS
 *     ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED,
 *     INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR
 *     A PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY
 *     WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 *     INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK
 *     ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *     NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION
 *     OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *
 *     BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE LIABILITY WITH
 *     RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION,
TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE
 *     FEES OR SERVICE CHARGE PAID BY BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 *     THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE WITH THE LAWS
 *     OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF LAWS PRINCIPLES.
 ************************************************************************************************/
#include <utils/Log.h>
#include <fcntl.h>
#include <math.h>


#include "camera_custom_nvram.h"
#include "camera_custom_sensor.h"
#include "image_sensor.h"
#include "kd_imgsensor_define.h"
#include "camera_AE_PLineTable_ov8835mipiraw.h"
#include "camera_info_ov8835mipiraw.h"
#include "camera_custom_AEPlinetable.h"

const NVRAM_CAMERA_ISP_PARAM_STRUCT CAMERA_ISP_DEFAULT_VALUE =
{{
    //Version
    Version: NVRAM_CAMERA_PARA_FILE_VERSION,

    //SensorId
    SensorId: SENSOR_ID,
    ISPComm:{
        {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    	}
    },
    ISPPca: {
        #include INCLUDE_FILENAME_ISP_PCA_PARAM
    },
    ISPRegs:{
        #include INCLUDE_FILENAME_ISP_REGS_PARAM
    },
    ISPMfbMixer:{{
        {//00: MFB mixer for ISO 100
            0x00000000, 0x00000000
        },
        {//01: MFB mixer for ISO 200
            0x00000000, 0x00000000
        },
        {//02: MFB mixer for ISO 400
            0x00000000, 0x00000000
        },
        {//03: MFB mixer for ISO 800
            0x00000000, 0x00000000
        },
        {//04: MFB mixer for ISO 1600
            0x00000000, 0x00000000
        },
        {//05: MFB mixer for ISO 2400
            0x00000000, 0x00000000
        },
        {//06: MFB mixer for ISO 3200
            0x00000000, 0x00000000
    }
    }},
    ISPCcmPoly22:{
        79567,    // i4R_AVG
        20725,    // i4R_STD
        110867,    // i4B_AVG
        32431,    // i4B_STD
        { // i4P00[9]
            4873333, -2446667, 130000, -450000, 3306667, -293333, 60000, -2270000, 4770000
        },
        { // i4P10[9]
            1576571, -1800218, 229959, -248584, -462841, 697993, 61656, 1183283, -1244939
        },
        { // i4P01[9]
            1410483, -1515528, 116575, -406213, -430200, 827850, 16786, 356489, -373275
        },
        { // i4P20[9]
            0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        { // i4P11[9]
            0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        { // i4P02[9]
            0, 0, 0, 0, 0, 0, 0, 0, 0
        }        
    }
}};

const NVRAM_CAMERA_3A_STRUCT CAMERA_3A_NVRAM_DEFAULT_VALUE =
{
    NVRAM_CAMERA_3A_FILE_VERSION, // u4Version
    SENSOR_ID, // SensorId

    // AE NVRAM
    {
        // rDevicesInfo
        {
            1640,    // u4MinGain, 1024 base = 1x
            15872,    // u4MaxGain, 16x
            118,    // u4MiniISOGain, ISOxx  
            128,    // u4GainStepUnit, 1x/8 
            17346,    // u4PreExpUnit 
            29,    // u4PreMaxFrameRate
            13876,    // u4VideoExpUnit  
            30,    // u4VideoMaxFrameRate 
            1024,    // u4Video2PreRatio, 1024 base = 1x 
            13876,    // u4CapExpUnit 
            28,    // u4CapMaxFrameRate
            512,    // u4Cap2PreRatio, 1024 base = 1x //1024 inning sum nick
            28,    // u4LensFno, Fno = 2.8
            350    // u4FocusLength_100x
        },
        // rHistConfig
        {
            2,    // u4HistHighThres
            40,    // u4HistLowThres
            2,   // u4MostBrightRatio
            1,   // u4MostDarkRatio
            160, // u4CentralHighBound
            20,  // u4CentralLowBound
            {240, 230, 220, 210, 200}, // u4OverExpThres[AE_CCT_STRENGTH_NUM]
            {75, 108, 128, 148, 170},  // u4HistStretchThres[AE_CCT_STRENGTH_NUM]
            {18, 22, 26, 30, 34}       // u4BlackLightThres[AE_CCT_STRENGTH_NUM]
        },
        // rCCTConfig
        {
            TRUE,            // bEnableBlackLight
            TRUE,            // bEnableHistStretch
            FALSE,           // bEnableAntiOverExposure
            TRUE,            // bEnableTimeLPF
            TRUE,            // bEnableCaptureThres
            TRUE,            // bEnableVideoThres
            TRUE,            // bEnableStrobeThres
            47,                // u4AETarget
            47,                // u4StrobeAETarget

            50,                // u4InitIndex
            32,    // u4BackLightWeight
            37,    // u4HistStretchWeight
            4,                 // u4AntiOverExpWeight
            3,                 // u4BlackLightStrengthIndex
            4,    // u4HistStretchStrengthIndex
            2,                 // u4AntiOverExpStrengthIndex
            2,                 // u4TimeLPFStrengthIndex
            {1, 3, 5, 7, 8}, // u4LPFConvergeTable[AE_CCT_STRENGTH_NUM]
            90,                // u4InDoorEV = 9.0, 10 base
            -10,               // i4BVOffset delta BV = -2.3
            64,                 // u4PreviewFlareOffset
            64,                 // u4CaptureFlareOffset
            3,                 // u4CaptureFlareThres
            64,                 // u4VideoFlareOffset
            3,                 // u4VideoFlareThres
            64,                 // u4StrobeFlareOffset //12 bits
            3,                 // u4StrobeFlareThres // 0.5%
            160,                 // u4PrvMaxFlareThres //12 bit
            0,                 // u4PrvMinFlareThres
            160,                 // u4VideoMaxFlareThres // 12 bit
            0,                 // u4VideoMinFlareThres            
            18,                // u4FlatnessThres              // 10 base for flatness condition.
            75                 // u4FlatnessStrength
         }
    },

    // AWB NVRAM
    {
        // AWB calibration data
        {
            // rUnitGain (unit gain: 1.0 = 512)
            {
                0,    // i4R
                0,    // i4G
                0    // i4B
            },
            // rGoldenGain (golden sample gain: 1.0 = 512)
            {
                0,    // i4R
                0,    // i4G
                0    // i4B
            },
            // rTuningUnitGain (Tuning sample unit gain: 1.0 = 512)
            {
                0,    // i4R
                0,    // i4G
                0    // i4B
            },
            // rD65Gain (D65 WB gain: 1.0 = 512)
            {
                1037,    // i4R
                512,    // i4G
                766    // i4B
            }
        },
        // Original XY coordinate of AWB light source
        {
           // Strobe
            {
                37,    // i4X
                -461    // i4Y
            },
            // Horizon
            {
                -477,    // i4X
                -420    // i4Y
            },
            // A
            {
                -334,    // i4X
                -443    // i4Y
            },
            // TL84
            {
                -175,    // i4X
                -427    // i4Y
            },
            // CWF
            {
                -134,    // i4X
                -525    // i4Y
            },
            // DNP
            {
                -65,    // i4X
                -459    // i4Y
            },
            // D65
            {
                112,    // i4X
                -409    // i4Y
            },
            // DF
            {
                27,    // i4X
                -485    // i4Y
            }
        },
        // Rotated XY coordinate of AWB light source
        {
            // Strobe
            {
                21,    // i4X
                -462    // i4Y
            },
            // Horizon
            {
                -492,    // i4X
                -403    // i4Y
            },
            // A
            {
                -350,    // i4X
                -431    // i4Y
            },
            // TL84
            {
                -190,    // i4X
                -421    // i4Y
            },
            // CWF
            {
                -152,    // i4X
                -520    // i4Y
            },
            // DNP
            {
                -81,    // i4X
                -457    // i4Y
            },
            // D65
            {
                98,    // i4X
                -413    // i4Y
            },
            // DF
            {
                10,    // i4X
                -486    // i4Y
            }
        },
        // AWB gain of AWB light source
        {
            // Strobe 
            {
                1004,    // i4R
                512,    // i4G
                909    // i4B
            },
            // Horizon 
            {
                512,    // i4R
                553,    // i4G
                1864    // i4B
            },
            // A 
            {
                593,    // i4R
                512,    // i4G
                1465    // i4B
            },
            // TL84 
            {
                720,    // i4R
                512,    // i4G
                1156    // i4B
            },
            // CWF 
            {
                869,    // i4R
                512,    // i4G
                1250    // i4B
            },
            // DNP 
            {
                873,    // i4R
                512,    // i4G
                1040    // i4B
            },
            // D65 
            {
                1037,    // i4R
                512,    // i4G
                766    // i4B
            },
            // DF 
            {
                1024,    // i4R
                512,    // i4G
                951    // i4B
            }
        },
        // Rotation matrix parameter
        {
            2,    // i4RotationAngle
            256,    // i4Cos
            9    // i4Sin
        },
        // Daylight locus parameter
        {
            -139,    // i4SlopeNumerator
            128    // i4SlopeDenominator
        },
        // AWB light area
        {
            // Strobe:FIXME
            {
            0,    // i4RightBound
            0,    // i4LeftBound
            0,    // i4UpperBound
            0    // i4LowerBound
            },
            // Tungsten
            {
            -240,    // i4RightBound
            -890,    // i4LeftBound
            -347,    // i4UpperBound
            -500    // i4LowerBound
            },
            // Warm fluorescent
            {
            -240,    // i4RightBound
            -890,    // i4LeftBound
            -500,    // i4UpperBound
            -587    // i4LowerBound
            },
            // Fluorescent
            {
            -131,    // i4RightBound
            -240,    // i4LeftBound
            -350,    // i4UpperBound
            -470    // i4LowerBound
            },
            // CWF
            {
            -131,    // i4RightBound
            -240,    // i4LeftBound
            -470,    // i4UpperBound
            -570    // i4LowerBound
            },
            // Daylight
            {
            123,    // i4RightBound
            -131,    // i4LeftBound
            -333,    // i4UpperBound
            -493    // i4LowerBound
            },
            // Shade
            {
            483,    // i4RightBound
            123,    // i4LeftBound
            -333,    // i4UpperBound
            -493    // i4LowerBound
            },
            // Daylight Fluorescent
            {
            123,    // i4RightBound
            -131,    // i4LeftBound
            -493,    // i4UpperBound
            -613    // i4LowerBound
            }
        },
        // PWB light area
        {
            // Reference area
            {
            483,    // i4RightBound
            -890,    // i4LeftBound
            0,    // i4UpperBound
            -613    // i4LowerBound
            },
            // Daylight
            {
            148,    // i4RightBound
            -131,    // i4LeftBound
            -333,    // i4UpperBound
            -493    // i4LowerBound
            },
            // Cloudy daylight
            {
            248,    // i4RightBound
            73,    // i4LeftBound
            -333,    // i4UpperBound
            -493    // i4LowerBound
            },
            // Shade
            {
            348,    // i4RightBound
            73,    // i4LeftBound
            -333,    // i4UpperBound
            -493    // i4LowerBound
            },
            // Twilight
            {
            -131,    // i4RightBound
            -291,    // i4LeftBound
            -333,    // i4UpperBound
            -493    // i4LowerBound
            },
            // Fluorescent
            {
            148,    // i4RightBound
            -290,    // i4LeftBound
            -363,    // i4UpperBound
            -570    // i4LowerBound
            },
            // Warm fluorescent
            {
            -250,    // i4RightBound
            -450,    // i4LeftBound
            -363,    // i4UpperBound
            -570    // i4LowerBound
            },
            // Incandescent
            {
            -250,    // i4RightBound
            -450,    // i4LeftBound
            -333,    // i4UpperBound
            -493    // i4LowerBound
            },
            // Gray World
            {
            5000,    // i4RightBound
            -5000,    // i4LeftBound
            5000,    // i4UpperBound
            -5000    // i4LowerBound
            }
        },
        // PWB default gain	
        {
            // Daylight
            {
            923,    // i4R
            512,    // i4G
            867    // i4B
            },
            // Cloudy daylight
            {
            1125,    // i4R
            512,    // i4G
            701    // i4B
            },
            // Shade
            {
            1201,    // i4R
            512,    // i4G
            654    // i4B
            },
            // Twilight
            {
            693,    // i4R
            512,    // i4G
            1179    // i4B
            },
            // Fluorescent
            {
            897,    // i4R
            512,    // i4G
            1039    // i4B
            },
            // Warm fluorescent
            {
            623,    // i4R
            512,    // i4G
            1536    // i4B
            },
            // Incandescent
            {
            578,    // i4R
            512,    // i4G
            1432    // i4B
            },
            // Gray World
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            }
        },
        // AWB preference color	
        {
            // Tungsten
            {
            0,    // i4SliderValue
            7109    // i4OffsetThr
            },
            // Warm fluorescent	
            {
            0,    // i4SliderValue
            5609    // i4OffsetThr
            },
            // Shade
            {
            0,    // i4SliderValue
            1341    // i4OffsetThr
            },
            // Daylight WB gain
            {
            821,    // i4R
            512,    // i4G
            983    // i4B
            },
            // Preference gain: strobe
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: tungsten
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: warm fluorescent
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: fluorescent
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: CWF
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: daylight
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: shade
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: daylight fluorescent
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            }
        },
        {// CCT estimation
            {// CCT
                2300,    // i4CCT[0]
                2850,    // i4CCT[1]
                4100,    // i4CCT[2]
                5100,    // i4CCT[3]
                6500    // i4CCT[4]
            },
            {// Rotated X coordinate
                -590,    // i4RotatedXCoordinate[0]
                -448,    // i4RotatedXCoordinate[1]
                -288,    // i4RotatedXCoordinate[2]
                -179,    // i4RotatedXCoordinate[3]
                0    // i4RotatedXCoordinate[4]
            }
        }
    },
    {0}
};

#include INCLUDE_FILENAME_ISP_LSC_PARAM
//};  //  namespace


typedef NSFeature::RAWSensorInfo<SENSOR_ID> SensorInfoSingleton_T;


namespace NSFeature {
template <>
UINT32
SensorInfoSingleton_T::
impGetDefaultData(CAMERA_DATA_TYPE_ENUM const CameraDataType, VOID*const pDataBuf, UINT32 const size) const
{
    UINT32 dataSize[CAMERA_DATA_TYPE_NUM] = {sizeof(NVRAM_CAMERA_ISP_PARAM_STRUCT),
                                             sizeof(NVRAM_CAMERA_3A_STRUCT),
                                             sizeof(NVRAM_CAMERA_SHADING_STRUCT),
                                             sizeof(NVRAM_LENS_PARA_STRUCT),
                                             sizeof(AE_PLINETABLE_T)};

    if (CameraDataType > CAMERA_DATA_AE_PLINETABLE || NULL == pDataBuf || (size < dataSize[CameraDataType]))
    {
        return 1;
    }

    switch(CameraDataType)
    {
        case CAMERA_NVRAM_DATA_ISP:
            memcpy(pDataBuf,&CAMERA_ISP_DEFAULT_VALUE,sizeof(NVRAM_CAMERA_ISP_PARAM_STRUCT));
            break;
        case CAMERA_NVRAM_DATA_3A:
            memcpy(pDataBuf,&CAMERA_3A_NVRAM_DEFAULT_VALUE,sizeof(NVRAM_CAMERA_3A_STRUCT));
            break;
        case CAMERA_NVRAM_DATA_SHADING:
            memcpy(pDataBuf,&CAMERA_SHADING_DEFAULT_VALUE,sizeof(NVRAM_CAMERA_SHADING_STRUCT));
            break;
        case CAMERA_DATA_AE_PLINETABLE:
            memcpy(pDataBuf,&g_PlineTableMapping,sizeof(AE_PLINETABLE_T));
            break;
        default:
            break;
    }
    return 0;
}};  //  NSFeature


