#ifndef	__SFIFO_H__
#define __SFIFO_H__
/* Includes ------------------------------------------------------------------*/
#include  <stdlib.h>
#include  <string.h>
#include  <stdint.h>

/* Public variables ---------------------------------------------------------*/
typedef struct
{
	uint16_t	usByteDepth;		// FIFO 深度（字节大小）
	uint8_t		ucGranByte;			// FIFO 操作粒度（字节）
	
	uint8_t		*pucMem;			// FIFO 缓冲区指针
	
	uint16_t	usFree;				// 
	uint16_t	usPush;				// in 指针
	uint16_t	usPop;				// out 指针

}	STR_SFIFO_t;

/* Public function prototypes ------------------------------------------------*/
extern void vSFifoInit(STR_SFIFO_t *pxfifo, uint16_t usDepth, uint8_t ucGran, uint8_t *pucMem);
extern uint8_t ucSFifoPut(STR_SFIFO_t *pxfifo, void *pvIn);
extern uint8_t ucSFifoGet(STR_SFIFO_t *pxfifo, void *pvOut);

/******************* (C) COPYRIGHT  *****END OF FILE**************************/
#endif
