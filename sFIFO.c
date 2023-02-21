/****************************************Copyright (c)****************************************************
**
**
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               sFIFO.c
** Descriptions:			简单FIFO实现
**
**--------------------------------------------------------------------------------------------------------
** Created by:              Haneda
** Created date:            2022-3-6
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "sFIFO.h"

/* Private variables ---------------------------------------------------------*/
/****************************************************************************
* 名称：vSFifoInit
* 功能：FIFO初始化
* 说明：
****************************************************************************/
void vSFifoInit(STR_SFIFO_t *pxfifo, uint16_t usDepth, uint8_t ucGran, uint8_t *pucMem)
{
	if (pxfifo == NULL)
		return;

	memset((uint8_t *)pxfifo, 0, sizeof(STR_SFIFO_t));
	
	pxfifo->usByteDepth = usDepth;
	pxfifo->usFree = usDepth;
	pxfifo->ucGranByte = ucGran;
	pxfifo->pucMem = pucMem;
}

/****************************************************************************
* 名称：ucSFifoPut
* 功能：FIFO放入数据，先入先出
* 说明：返回值 1 失败（缓存器已满） 0 成功
****************************************************************************/
uint8_t ucSFifoPut(STR_SFIFO_t *pxfifo, void *pvIn)
{
	uint8_t flag = 0;
	
	if ((pxfifo == NULL) || (pxfifo->usByteDepth == 0))
		return EXIT_FAILURE;

	if ((pxfifo->usFree == 0) || (pxfifo->usFree < pxfifo->ucGranByte)) {
		flag = EXIT_FAILURE;					// 缓存器已满
	} else {
		// 放入数据
		memcpy((uint8_t *)&pxfifo->pucMem[pxfifo->usPush], (uint8_t *)pvIn, pxfifo->ucGranByte);
		
		pxfifo->usPush += pxfifo->ucGranByte;		// 缓存器为循环
		if(pxfifo->usPush >= pxfifo->usByteDepth) pxfifo->usPush = 0;
		
		pxfifo->usFree -= pxfifo->ucGranByte;
		
		flag = EXIT_SUCCESS;
	}

	return flag;
}

/****************************************************************************
* 名称：ucSFifoGet
* 功能：FIFO取出数据，先入先出
* 说明：返回值 1 无 0 有
****************************************************************************/
uint8_t ucSFifoGet(STR_SFIFO_t *pxfifo, void *pvOut)
{
	uint8_t flag;
	
	if ((pxfifo == NULL) || (pxfifo->usByteDepth == 0))
		return EXIT_FAILURE;

	if (pxfifo->usFree >= pxfifo->usByteDepth) {
		memset((uint8_t *)pvOut, 0, pxfifo->ucGranByte);
		
		flag = EXIT_FAILURE;	// 缓存器为空
	} else {
		// 取出数据
		memcpy((uint8_t *)pvOut, (uint8_t *)&pxfifo->pucMem[pxfifo->usPop], pxfifo->ucGranByte);
		
		pxfifo->usPop += pxfifo->ucGranByte;								// 缓存器为循环
		if(pxfifo->usPop >= pxfifo->usByteDepth) pxfifo->usPop = 0;
		
		pxfifo->usFree += pxfifo->ucGranByte;
		
		flag = EXIT_SUCCESS;
	}

	return flag;
}

/******************* (C) COPYRIGHT  *****END OF FILE**************************/
