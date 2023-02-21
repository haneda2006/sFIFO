#ifndef	__SFIFO_H__
#define __SFIFO_H__
/* Includes ------------------------------------------------------------------*/
#include  <stdlib.h>
#include  <string.h>
#include  <stdint.h>

/* Public variables ---------------------------------------------------------*/
typedef struct
{
	uint16_t	usByteDepth;		// FIFO ��ȣ��ֽڴ�С��
	uint8_t		ucGranByte;			// FIFO �������ȣ��ֽڣ�
	
	uint8_t		*pucMem;			// FIFO ������ָ��
	
	uint16_t	usFree;				// 
	uint16_t	usPush;				// in ָ��
	uint16_t	usPop;				// out ָ��

}	STR_SFIFO_t;

/* Public function prototypes ------------------------------------------------*/
extern void vSFifoInit(STR_SFIFO_t *pxfifo, uint16_t usDepth, uint8_t ucGran, uint8_t *pucMem);
extern uint8_t ucSFifoPut(STR_SFIFO_t *pxfifo, void *pvIn);
extern uint8_t ucSFifoGet(STR_SFIFO_t *pxfifo, void *pvOut);

/******************* (C) COPYRIGHT  *****END OF FILE**************************/
#endif
