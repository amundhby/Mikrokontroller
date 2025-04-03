#include "uart.h"
#include "gpio.h"

#define UART ((NRF_UART_REG*)0x40002000)

typedef struct {
    uint32_t TASKS_STARTRX;
    uint32_t TASKS_STOPRX;
    uint32_t TASKS_STARTTX;
    uint32_t TASKS_STOPTX;
    uint32_t RESERVED0[3];
    uint32_t TASKS_SUSPEND;
    uint32_t RESERVED1[56];
    uint32_t EVENTS_CTS;
    uint32_t EVENTS_NCTS;
    uint32_t EVENTS_RXDRDY;
    uint32_t RESERVED2[4];
    uint32_t EVENTS_TXDRDY;
    uint32_t RESERVED3[1];
    uint32_t EVENTS_ERROR;
    uint32_t RESERVED4[7];
    uint32_t EVENTS_RXTO;
    uint32_t RESERVED5[46];
    uint32_t SHORTS;
    uint32_t RESERVED7[64];
    uint32_t INTSENSET;
    uint32_t INTENCLR;
    uint32_t RESERVED8[93];
    uint32_t ERRORSRC;
    uint32_t RESERVED9[31];
    uint32_t ENABLE;
    uint32_t RESERVED10[1];
    uint32_t PSELRTS;
    uint32_t PSELTXD;
    uint32_t PSELCTS;
    uint32_t PSELRXD;
    uint32_t RXD;
    uint32_t TXD;
    uint32_t RESERVED11[1];
    uint32_t BAUDRATE;
    uint32_t RESERVED12[17];
    uint32_t CONFIG;
} NRF_UART_REG;

void uart_init() {
    GPIO->PIN_CNF[6] = 0;
	GPIO->PIN_CNF[8] = 1;

    UART->PSELTXD = 6;
    UART->PSELRXD = 8;

    UART->BAUDRATE = 0x00275000;
    UART->PSELRTS = 0xFFFFFFFF;
    UART->PSELCTS = 0xFFFFFFFF;

    UART->ENABLE = 4;
    UART->TASKS_STARTRX = 1;
}

void uart_send(char letter) {
    UART->TASKS_STARTTX = 1;
    UART->TXD = letter;
    while(!(UART->EVENTS_TXDRDY));
    UART->EVENTS_TXDRDY = 0;
    UART->TASKS_STOPTX = 1;
}

char uart_read() {
    if (UART->EVENTS_RXDRDY) {
        UART->EVENTS_RXDRDY = 0;
        return UART->RXD;
    } return '\0';
}