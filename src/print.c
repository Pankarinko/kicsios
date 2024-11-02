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

#define UART_LCR_8BIT 3
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


void prints(char* word) {
  int char_count;
  while (*word != '\0') {
    char_count = 0;
    if (LSR != UART_LSR_THR_EMPTY) {
        while (char_count < 14) {
          output_UART((uint8) *word);
          word++;
          if (*word == '\0') return;
            }
        }
    }
}

void println(char* word) {
    prints(word);
    output_UART('\n');
}

void print_u32(uint32 num) {
    if (num == 0) {
        output_UART('0');
        return;
    }
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
    prints(word);
}

void print_u64(uint64 num) {
    if (num == 0) {
        output_UART('0');
        return;
    }
    char space[21];
    space[20] = 0;
    space[19] = 48;
    char *word = &(space[20]);
    uint32 digit = 0;
    while (num != 0ull) {
      digit = num % 10;
      word--;
      *word = 48 + digit;  
      num = (num - digit) / 10;
      }
    prints(word);
}

void printu(usize num) {
  PRINTU(num);
}

int clz32(uint32 v) {

  int r;      // result goes here

  static const int MultiplyDeBruijnBitPosition[32] = 
    {
    0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
    8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31
    };

    v |= v >> 1; // first round down to one less than a power of 2 
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;

    r = MultiplyDeBruijnBitPosition[(uint32)(v * 0x07C4ACDDU) >> 27];
  return 32 - r - 1;
}

int clz64(uint64 v) {
  uint32 upp = (uint32) (v >> 32);
  if (upp == 0) {
    int r = clz32((uint32) v); 
    return 32 + r;
  } else {
    return clz32(upp);
  }
}

void print_hex32(uint32 num) {
  char c = 48;
  output_UART('0');
  output_UART('x');
  if (num == 0) {
      output_UART(c);
      return;
    } 
  uint32 num2 = num;
  int shift = 4;
  uint8 lead = 0;
  for (uint8 i = 0; i < 8; i++) {
    num = num2 >> 28;
    if (num != 0) lead = 1;
    if (lead != 0) {
        if (num < 10) {
          c = 48 + num;
        } else {
          c = 65 + (num - 10);
        }
      output_UART(c);
    } 
    num2 = num2 << shift;
  }
}

void print_hex64(uint64 num) {
  char c = 48;
  output_UART('0');
  output_UART('x');
  if (num == 0) {
      output_UART(c);
      return;
    } 
  uint64 num2 = num;
  int shift = 4;
  uint8 lead = 0;
  for (uint8 i = 0; i < 16; i++) {
    num = num2 >> 60;
    if (num != 0ull) lead = 1;
    if (lead != 0) {
      if (num < 10) {
        c = 48 + num;
      } else {
        c = 65 + (num - 10);
      }
      output_UART(c);
    }
    num2 = num2 << shift;
  }
}

void print_hex(usize num) {
  PRINTHEX(num);
}
