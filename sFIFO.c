/****************************************Copyright (c)****************************************************
**
**
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               sFIFO.c
** Descriptions:			��FIFOʵ��
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
* ���ƣ�vSFifoInit
* ���ܣ�FIFO��ʼ��
* ˵����
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
* ���ƣ�ucSFifoPut
* ���ܣ�FIFO�������ݣ������ȳ�
* ˵��������ֵ 1 ʧ�ܣ������������� 0 �ɹ�
****************************************************************************/
uint8_t ucSFifoPut(STR_SFIFO_t *pxfifo, void *pvIn)
{
	uint8_t flag = 0;
	
	if ((pxfifo == NULL) || (pxfifo->usByteDepth == 0))
		return EXIT_FAILURE;

	if ((pxfifo->usFree == 0) || (pxfifo->usFree < pxfifo->ucGranByte)) {
		flag = EXIT_FAILURE;					// ����������
	} else {
		// ��������
		memcpy((uint8_t *)&pxfifo->pucMem[pxfifo->usPush], (uint8_t *)pvIn, pxfifo->ucGranByte);
		
		pxfifo->usPush += pxfifo->ucGranByte;		// ������Ϊѭ��
		if(pxfifo->usPush >= pxfifo->usByteDepth) pxfifo->usPush = 0;
		
		pxfifo->usFree -= pxfifo->ucGranByte;
		
		flag = EXIT_SUCCESS;
	}

	return flag;
}

/****************************************************************************
* ���ƣ�ucSFifoGet
* ���ܣ�FIFOȡ�����ݣ������ȳ�
* ˵��������ֵ 1 �� 0 ��
****************************************************************************/
uint8_t ucSFifoGet(STR_SFIFO_t *pxfifo, void *pvOut)
{
	uint8_t flag;
	
	if ((pxfifo == NULL) || (pxfifo->usByteDepth == 0))
		return EXIT_FAILURE;

	if (pxfifo->usFree >= pxfifo->usByteDepth) {
		memset((uint8_t *)pvOut, 0, pxfifo->ucGranByte);
		
		flag = EXIT_FAILURE;	// ������Ϊ��
	} else {
		// ȡ������
		memcpy((uint8_t *)pvOut, (uint8_t *)&pxfifo->pucMem[pxfifo->usPop], pxfifo->ucGranByte);
		
		pxfifo->usPop += pxfifo->ucGranByte;								// ������Ϊѭ��
		if(pxfifo->usPop >= pxfifo->usByteDepth) pxfifo->usPop = 0;
		
		pxfifo->usFree += pxfifo->ucGranByte;
		
		flag = EXIT_SUCCESS;
	}

	return flag;
}

/******************* (C) COPYRIGHT  *****END OF FILE**************************/
