 #include <stdint.h>
 
 typedef struct{
	uint32_t uiUartRxD; //0
	uint32_t uiRecv1[15];
	uint32_t uiUartTxD; //40
	uint32_t uiRecv2[15];
	uint32_t uiCr1;//80
	uint32_t uiCr2;//84
	uint32_t uiCr3;//88
	uint32_t uiCr4;//8c
	uint32_t uiFcr; //0x90
	uint32_t uiSr1;//94
	uint32_t uiSr2;//98
	uint32_t uiEsc;//9c
	uint32_t uiTim;//a0
	uint32_t uiBir;//a4
	uint32_t uiBmr;//a8
	uint32_t uiBrc;//ac
	uint32_t uiOnems;//b0
	uint32_t uiUts;//b4
	uint32_t uiMcr;//b8
} T_UART_REG;

void uart_init(void);
void uart_putc(uint8_t ucVal);