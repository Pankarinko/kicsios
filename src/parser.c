#include "kstd.h"

#define UART_BASE 0x10000000
#define LSR_OFFSET 5
#define LCR_OFFSET 3
#define FCR_OFFSET 2
#define THR_OFFSET 0
#define LCR *(volatile uint8*) (UART_BASE + LCR_OFFSET)
#define FCR *(volatile uint8*) (UART_BASE + FCR_OFFSET)
#define THR *(volatile uint8*) (UART_BASE + THR_OFFSET)
#define LSR *(volatile uint8*) (UART_BASE + LSR_OFFSET)

#define UART_LCR_8BIT 8
#define UART_FCR_FIFO_ENABLE 2
#define UART_FCR_14B 0xC0
#define UART_LSR_DATA_AVAILABLE 1
#define UART_LSR_THR_EMPTY 32


void init_UART(void) {
    LCR = UART_LCR_8BIT;
    FCR = UART_FCR_FIFO_ENABLE | UART_FCR_14B;
}

void output_UART(char c) {
    init_UART();
    THR = c;
}


void printw(char* word) {
    int char_count;
    while (*word != '\0') {
        char_count = 0;
        if (LSR != UART_LSR_THR_EMPTY)
            while (char_count < 14) {
                output_UART((uint8) *word);
                word++;
                if (*word == '\0') return;
            }
    }
}

void println(char* word) {
    printw(word);
    output_UART('\n');
}

void print_u32(uint32 num) {
    char space[11];
    space[10] = 0;
    char *word = &(space[9]);
    uint32 digit = 0;
    while (num != 0) {
      digit = num % 10;
      word--;
      *word = 48 + digit;
      num = (num - digit) / 10;
      }
    printw(word);
}

void print_u64(uint64 num) {
    char space[21];
    space[20] = 0;
    char *word = &(space[19]);
    uint32 digit = 0;
    while (num != 0) {
      digit = num % 10;
      word--;
      *word = 48 + digit;
      num = (num - digit) / 10;
      }
    printw(word);
}


