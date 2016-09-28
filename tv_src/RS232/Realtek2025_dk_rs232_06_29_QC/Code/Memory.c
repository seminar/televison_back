//----------------------------------------------------------------------------------------------------
// ID Code      : RTD2528R_Memory.c No.0000
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#define __RTD2547D_MEMORY__

#include "Header\Include.h"

#if(_SCALER_TYPE == _RTD2547D)


#if((_OD_SUPPORT == _ON) || (_FRC_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Reset SDRAM
// Input Value  : NONE
// Output Value : NONE
//--------------------------------------------------
void CMemorySDRAMReset(void)
{
    CScalerPageSelect(_PAGE4);
    CScalerSetBit(_P4_SDR_PRCG_A4, ~_BIT4, _BIT4);
    CTimerDelayXms(5);
    CScalerSetBit(_P4_SDR_PRCG_A4, ~_BIT4, 0x00);
}

//--------------------------------------------------
// Description  : Calculate the number and remain 
// Input Value  : ucTotalSize --> Image total size / ucLength --> Length of SDRAM access 
// Output Value : number and remain
//--------------------------------------------------
DWORD CMemoryCalculateNumberAndRemain(DWORD ucTotalSize, BYTE ucLength, bit bDummy)
{
    BYTE remain = 0;
    WORD number = 0;

    if(bDummy)
    {
    	if (ucTotalSize & 0x03)
        	(ucTotalSize += 4 - (ucTotalSize & 0x03));
    }

    if((ucTotalSize % ucLength) != 0)
    {
        number = ucTotalSize / ucLength;
        remain = ucTotalSize % ucLength;
    }
    else
    {
        ucTotalSize = ucTotalSize - ucLength;
        number = ucTotalSize / ucLength;
        remain = ucLength;
    }

    return (((DWORD)remain << 16) | number);

}
#endif

#if(_OD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Load OD Table to LUT
// Input Value  : ucColor   --> LUT Channel Select
// Output Value : NONE
//--------------------------------------------------
void CMemoryLoadODLUT(BYTE ucColor)
{
    BYTE repeat;

    CScalerPageSelect(_PAGE3);
    CScalerSetBit(_P3_LS_LUT_ROW_ADDR_AE, ~_BIT7, _BIT7);

    if((ucColor == _OD_TABLE_COMMON))
    {
        CScalerSetBit(_P3_LS_LUT_COL_ADDR_AF, ~(_BIT7 | _BIT6), _OD_TABLE_COMMON << 6);
        CMemoryLoadODTable(tOD_TABLE[_OD_TABLE_MIDDLE]);
    }
    else
    {
        for(repeat=0 ; repeat<3 ; repeat++)
        {
            CScalerSetBit(_P3_LS_LUT_COL_ADDR_AF, ~(_BIT7 | _BIT6), repeat << 6);            
            CMemoryLoadODTable(tOD_TABLE[repeat]);
        }
    }
    CScalerSetBit(_P3_LS_LUT_ROW_ADDR_AE, ~_BIT7, 0x00);
    CScalerSetBit(_P3_LS_CTRL0_A1, ~(_BIT6|_BIT5), (_BIT6|_BIT5));
    CTimerDelayXms(50);
    CScalerSetBit(_P3_LS_CTRL0_A1, ~_BIT7, _BIT7);
}

//--------------------------------------------------
// Description  : Load OD Table to LUT
// Input Value  : pChannelArray    --> OD Table Start Address
// Output Value : NONE
//--------------------------------------------------
void CMemoryLoadODTable(BYTE *pChannelArray)
{
    CScalerWrite(_P3_LS_LUT_DATA_B0, 1088, pChannelArray, _NON_AUTOINC);
}

//--------------------------------------------------
// Description  : OD On/Off Select
// Input Value  : ucSelect    --> On or Off
// Output Value : NONE
//--------------------------------------------------
void CMemorySetODOnOff(BYTE ucSelect)
{
    CScalerPageSelect(_PAGE3);

    CScalerSetBit(_P3_LS_CTRL0_A1, ~(_BIT6 | _BIT5 | _BIT3), (_BIT6 | _BIT5 | _BIT3));

    CScalerSetByte(_P3_LS_CTRL1_A2, ((BYTE)_OD_LBNRT_ENABLE<<4 | _OD_LBNRT_MODE<<3 | _OD_LBNRT_LEVEL) | _BIT7 | _BIT6);

    CScalerSetByte(_P3_LS_STATUS0_B6, 0x01);
    
    CAdjustODeltaGain(stSystemData.ODTable);

    if(ucSelect == _ON)
        CScalerSetBit(_P3_LS_CTRL0_A1, ~_BIT7, _BIT7);
    else
        CScalerSetBit(_P3_LS_CTRL0_A1, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : OD Compress
// Input Value  : NONE
// Output Value : NONE
//--------------------------------------------------
void CMemorySetODCompress(void)
{
    BYTE compress = 0, resolution = 0; 
    WORD efficiency = 0, target = 0; 

    CScalerPageSelect(_PAGE3);
#if (_OD_BIT_RESOLUTION == _OD_RES_5BIT)
    CScalerSetBit(_P3_LS_CTRL0_A1, ~(_BIT2 | _BIT1 | _BIT0),(((Panel[ucPanelSelect].PanelConfig & 0x80) << 2) | 0x01));
#else
    CScalerSetBit(_P3_LS_CTRL0_A1, ~(_BIT2 | _BIT1 | _BIT0),(((Panel[ucPanelSelect].PanelConfig & 0x80) << 2) | 0x00));
#endif

    // Calculate and set display clock frequency
    ((DWORD *)pData)[0] = (DWORD)(stDisplayInfo.DHTotal) * (DWORD)stModeInfo.IHFreq * (DWORD)(stDisplayInfo.DVHeight) / stModeInfo.IVHeight / 10;

//    efficiency = (((DWORD)(Panel[ucPanelSelect].DHWidth * ((DWORD *)pData)[0] * 6 * 3 * 2)) * 1000) / 
//                 ((DWORD)(Panel[ucPanelSelect].DHTotal * (_MEMORY_SPEED * 1000) * _MEMORY_BUS_WIDTH));                

    efficiency = (DWORD)Panel[ucPanelSelect].DHWidth * ((DWORD *)pData)[0] / _MEMORY_SPEED * _OD_BIT_RESOLUTION * 3 * 2 / Panel[ucPanelSelect].DHTotal / _MEMORY_BUS_WIDTH;

    //if(efficiency >= 900)
    //    compress = 1;
    //else
        compress = 0;

    compress = (compress | _OD_COMPRESSION);

    CScalerSetBit(_P3_LS_CTRL0_A1, ~_BIT4, (compress << 4));

    if(compress == _TRUE)
    {
        efficiency = (efficiency * 5) / 6;//Rounding to 5bit/4bit
    
        if(efficiency >= 800)
        {
            CScalerSetBit(_P3_LS_CPRS_CTRL_A4, ~(_BIT6 | _BIT5), 0x00);
            resolution = 4;
        }
        else
        {
            CScalerSetBit(_P3_LS_CPRS_CTRL_A4, ~(_BIT6 | _BIT5), _BIT5);
            resolution = 5;
        }
    }
    else
        resolution = _OD_BIT_RESOLUTION;

    pData[0] = (HIBYTE(_COMPRESS_GROUP_NUMBER) & 0x03);
    pData[1] = (LOBYTE(_COMPRESS_GROUP_NUMBER));
    CScalerWrite(_P3_LS_GRP_NUM_H_A7, 2, pData, _AUTOINC);

    target = (WORD)resolution * _COMPRESS_GROUP_NUMBER * 3 / 64;

    pData[0] = (HIBYTE(target) & 0x01);
    pData[1] = (LOBYTE(target));
    CScalerWrite(_P3_LS_TG_SIZE_H_A5, 2, pData, _AUTOINC);    
}

//--------------------------------------------------
// Description  : Set OD FIFO
// Input Value  : NONE
// Output Value : NONE
//--------------------------------------------------
void CMemorySetODFIFO(void)
{
    BYTE resolution = 6, length = 176;//128;
    DWORD value = 0;

    CScalerRead(_P3_LS_CTRL0_A1, 1, pData, _NON_AUTOINC);

    if((pData[0] & 0x10) == 0x10)
    {
        CScalerRead(_P3_LS_CPRS_CTRL_A4, 1, pData, _NON_AUTOINC);    

        if((pData[0] & 0x20) == 0x20)
            resolution = 5;
        else
            resolution = 4;
    }
    else
    {
        resolution = _OD_BIT_RESOLUTION;    // Issac
    }

    ((DWORD *)pData)[0] = (((DWORD)Panel[ucPanelSelect].DHWidth * Panel[ucPanelSelect].DVHeight) * 3 * resolution % 64) ? 
                          ((((DWORD)Panel[ucPanelSelect].DHWidth * Panel[ucPanelSelect].DVHeight) * 3 * resolution / 64) + 1) : 
                          (((DWORD)Panel[ucPanelSelect].DHWidth * Panel[ucPanelSelect].DVHeight) * 3 * resolution / 64);// One frame total pixel for SDRAM (unit : 64 bits)

    value = CMemoryCalculateNumberAndRemain(((DWORD *)pData)[0], length);

    CScalerPageSelect(_PAGE3);
    CScalerSetByte(_P3_LS_WTLVL_W_C0, (length / 2));
    CScalerSetByte(_P3_LS_WTLVL_R_C1, (length / 2));

    pData[0] = (HIBYTE(value));
    pData[1] = (LOBYTE(value));
    CScalerWrite(_P3_LS_MEM_FIFO_RW_NUM_H_C2, 2, pData, _AUTOINC);

    CScalerSetByte(_P3_LS_MEM_FIFO_RW_LEN_C4, length);
    CScalerSetByte(_P3_LS_MEM_FIFO_RW_REMAIN_C5, ((value >> 16) & 0xff));

    pData[0] = ((_OD_START_ADDRESS >> 16) & 0x3f);
    pData[1] = ((_OD_START_ADDRESS >> 8) & 0xff);
    pData[2] = (_OD_START_ADDRESS & 0xff);
    CScalerWrite(_P3_LS_MEM_START_ADDR_H_C6, 3, pData, _AUTOINC);    
}
#endif //End of #if(_OD_SUPPORT == _ON)


#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : IN1&MAIN FIFO Setting for FRC Mode
// Input Value  : ucHorSize --> Horizontal size / ucVerSize --> Vertical Size
// Output Value : None
//--------------------------------------------------
void CMemoryControlForFRC(WORD ucHorSize, WORD ucVerSize)
{
    CMemoryCtrlForFRCInput(ucHorSize, ucVerSize);
    CMemoryCtrlForFRCDisplay(ucHorSize, ucVerSize);
}

//--------------------------------------------------
// Description  : IN1 FIFO Setting for FRC Mode
// Input Value  : ucHorSize --> Horizontal size / ucVerSize --> Vertical Size
// Output Value : None
//--------------------------------------------------
void CMemoryCtrlForFRCInput(WORD ucHorSize, WORD ucVerSize)
{
    BYTE length = 64;
    DWORD value = 0, step = 0;

    ((DWORD *)pData)[0] = ((DWORD)ucHorSize * 3 * 8 % 64) ? 
                          (((DWORD)ucHorSize * 3 * 8 / 64) + 1) : 
                          ((DWORD)ucHorSize * 3 * 8 / 64);// One line total pixel for SDRAM (unit : 64 bits)

    value = CMemoryCalculateNumberAndRemain(((DWORD *)pData)[0], length, 1);
    step = CMemoryCalculateLineStepAndBlockStep(ucHorSize, ucVerSize);

    pData[0] = length;
    pData[1] = HIBYTE(value);
    pData[2] = LOBYTE(value);
    pData[3] = length;
    pData[4] = (value >> 16) & 0xff;
    pData[5] = (BYTE)(_FRC_1ST_BLOCK_STA_ADDR >> 16);
    pData[6] = (BYTE)(_FRC_1ST_BLOCK_STA_ADDR >> 8);
    pData[7] = (BYTE)(_FRC_1ST_BLOCK_STA_ADDR >> 0);
    pData[8] = (BYTE)(step >> 24);//LINE_STEP
    pData[9] = (BYTE)(step >> 16);//LINE_STEP

#if(_FIELD_MERGE_SUPPORT == _ON)
    if(GET_FIELDMERGE_MODE())
    {
//        pData[10] = HIBYTE(step);//BLOCK_STEP
//        pData[11] = LOBYTE(step);//BLOCK_STEP
        pData[10] = (BYTE)(_FRC_2ND_BLOCK_STA_ADDR >> 20);//BLOCK_STEP
        pData[11] = (BYTE)(_FRC_2ND_BLOCK_STA_ADDR >> 12);//BLOCK_STEP
    }
    else
    {
        pData[10] = 0x00;//BLOCK_STEP
        pData[11] = 0x00;//BLOCK_STEP
    }
#else
    pData[10] = 0x00;//BLOCK_STEP
    pData[11] = 0x00;//BLOCK_STEP
#endif

//        step = (step & 0xffff) << 12;
//        pData[12] = (BYTE)(step >> 16);
//        pData[13] = (BYTE)(step >> 8);
//        pData[14] = (BYTE)(step >> 0);

    pData[12] = (BYTE)(_FRC_2ND_BLOCK_STA_ADDR >> 16);
    pData[13] = (BYTE)(_FRC_2ND_BLOCK_STA_ADDR >> 8);
    pData[14] = (BYTE)(_FRC_2ND_BLOCK_STA_ADDR >> 0);

    CScalerPageSelect(_PAGE5);
    CScalerWrite(_P5_SDRF_IN1_WATER_LEVEL_A8, 15, pData, _AUTOINC);

    pData[0] = (((ucVerSize >> 8) & 0x0f) | 0x00);
    pData[1] = LOBYTE(ucVerSize);

#if(_FIELD_MERGE_SUPPORT == _ON)
    if(GET_FIELDMERGE_MODE())
        pData[2] = 0xe2;
    else
        pData[2] = 0xa2;
#else
    pData[2] = 0xa2;
#endif

    CScalerWrite(_P5_SDRF_IN1_LINE_NUM_H_B7, 3, pData, _AUTOINC);
}

//--------------------------------------------------
// Description  : MAIN FIFO Setting for FRC Mode
// Input Value  : ucHorSize --> Horizontal size / ucVerSize --> Vertical Size
// Output Value : None
//--------------------------------------------------
void CMemoryCtrlForFRCDisplay(WORD ucHorSize, WORD ucVerSize)
{
    BYTE length = 64;
    DWORD value = 0, step = 0;

    ((DWORD *)pData)[0] = ((DWORD)ucHorSize * 3 * 8 % 64) ? 
                          (((DWORD)ucHorSize * 3 * 8 / 64) + 1) : 
                          ((DWORD)ucHorSize * 3 * 8 / 64);// One line total pixel for SDRAM (unit : 64 bits)

    value = CMemoryCalculateNumberAndRemain(((DWORD *)pData)[0], length, 0);
    step = CMemoryCalculateLineStepAndBlockStep(ucHorSize, ucVerSize);

    pData[0] = HIBYTE(stDisplayInfo.DVStartPos - 3) ;
    pData[1] = LOBYTE(stDisplayInfo.DVStartPos - 3);
	pData[2] = (HIBYTE(ucHorSize) & 0x07);
	pData[3] = LOBYTE(ucHorSize);
    pData[4] = length;//WTLVL
    pData[5] = 0x00;//Reserved
    pData[6] = HIBYTE(value);
    pData[7] = LOBYTE(value);
    pData[8] = length;
    pData[9] = (BYTE)(value >> 16);
    pData[10] = (BYTE)(_FRC_1ST_BLOCK_STA_ADDR >> 16);
    pData[11] = (BYTE)(_FRC_1ST_BLOCK_STA_ADDR >> 8); 
    pData[12] = (BYTE)(_FRC_1ST_BLOCK_STA_ADDR >> 0); 
    pData[13] = (BYTE)(step >> 24);//LINE_STEP
    pData[14] = (BYTE)(step >> 16);//LINE_STEP

    CScalerPageSelect(_PAGE5);
    CScalerWrite(_P5_SDRF_MN_PRERD_VST_H_BC, 15, pData, _AUTOINC);

#if(_FIELD_MERGE_SUPPORT == _ON)
    if(GET_FIELDMERGE_MODE())
    {
//        pData[0] = HIBYTE(step);
//        pData[1] = LOBYTE(step);
        pData[0] = (BYTE)(_FRC_2ND_BLOCK_STA_ADDR >> 20);//BLOCK_STEP
        pData[1] = (BYTE)(_FRC_2ND_BLOCK_STA_ADDR >> 12);//BLOCK_STEP
    }
    else
    {
        pData[0] = (BYTE)(_FRC_1ST_BLOCK_STA_ADDR >> 19);//BLOCK_STEP
        pData[1] = (BYTE)(_FRC_1ST_BLOCK_STA_ADDR >> 11);//BLOCK_STEP
    }
#else
    pData[0] = (BYTE)(_FRC_1ST_BLOCK_STA_ADDR >> 19);//BLOCK_STEP
    pData[1] = (BYTE)(_FRC_1ST_BLOCK_STA_ADDR >> 11);//BLOCK_STEP
#endif

    pData[2] = ((ucVerSize >> 8) & 0x0f);//LINE_NUM
    pData[3] = LOBYTE(ucVerSize);//LINE_NUM

#if(_FIELD_MERGE_SUPPORT == _ON)
    if(GET_FIELDMERGE_MODE())
        pData[4] = 0x69;//DISP_CTRL
    else
        pData[4] = 0x49;//DISP_CTRL
#else
    pData[4] = 0x49;//DISP_CTRL
#endif

    pData[5] = 0x10;

    CScalerWrite(_P5_SDRF_MN_BLOCK_STEP_H_CB, 6, pData, _AUTOINC);
}

//--------------------------------------------------
// Description  : Transfer the Memory Size to Address
// Input Value  : ucTotalSize --> Total Memory size
// Output Value : Line Step Address or Block Step Address
//--------------------------------------------------
DWORD CMemoryAddressConversion(DWORD ucTotalSize)
{
    DWORD size = 0;

#if(_MEMORY_CONFIG >= _2M_32BIT_1PCE)
    size = ((ucTotalSize & 0xffff00) << 1) | LOBYTE(ucTotalSize);
#else
    size = ((ucTotalSize & 0x000100) << 1) | ((ucTotalSize & 0xfffe00) << 2) | LOBYTE(ucTotalSize);
#endif

    return size;    
}

//--------------------------------------------------
// Description  : Calculate the Line Step and Block Step
// Input Value  : ucHorSize --> Horizontal size / ucVerSize --> Vertical size
// Output Value : Line Step and Block Step
//--------------------------------------------------
DWORD CMemoryCalculateLineStepAndBlockStep(WORD ucHorSize, WORD ucVerSize)
{
    WORD line = 0;
    DWORD block = 0;

    line = ucHorSize * 24 / 64;
   	if (line & 0x03)
       	(line += 4 - (line & 0x03));

    line = line * 64 / _MEMORY_BUS_WIDTH ;
    block = (DWORD)ucVerSize * line;
    line = CMemoryAddressConversion(line);
    block = (CMemoryAddressConversion(block) >> 11);

    return (((DWORD)line << 16) | (block & 0xffff));
}

#endif //End of #if(_FRC_SUPPORT == _ON)


#endif  // End of #if(_SCALER_TYPE == _RTD2547D)

