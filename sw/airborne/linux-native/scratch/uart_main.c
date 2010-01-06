// test the uart implementation

#include "uart.h"
#include <stdio.h>

int main (void)
{
/* // used as verification code with UART_BUF_SIZE = 10 
  struct ringbuf testbuf;
  testbuf.head = 0;
  testbuf.tail = 0;
  printf("ringbuf state\nhead: %x at %d, tail: %x at %d\n", testbuf.buf[testbuf.head] , testbuf.head,
    testbuf.buf[testbuf.tail] , testbuf.tail);

  buf_push(&testbuf, "abcd", 4);
  printf("push abcd\n");

  printf("head: %x at %d, tail: %x at %d\n", testbuf.buf[testbuf.head] , testbuf.head,
    testbuf.buf[testbuf.tail] , testbuf.tail);

  printf("two shifts: %x %x\n", buf_shift(&testbuf), buf_shift(&testbuf));

  printf("head: %x at %d, tail: %x at %d\n", testbuf.buf[testbuf.head] , testbuf.head,
   testbuf.buf[testbuf.tail] , testbuf.tail);
  
  buf_push(&testbuf, "12345", 5);

  printf("head: %x at %d, tail: %x at %d\n", testbuf.buf[testbuf.head] , testbuf.head,
   testbuf.buf[testbuf.tail] , testbuf.tail);

  buf_push(&testbuf, "67", 2);

  printf("head: %x at %d, tail: %x at %d\n", testbuf.buf[testbuf.head] , testbuf.head,
   testbuf.buf[testbuf.tail] , testbuf.tail);

  buf_push(&testbuf, "89", 2);


  printf("head: %x at %d, tail: %x at %d\n", testbuf.buf[testbuf.head] , testbuf.head,
   testbuf.buf[testbuf.tail] , testbuf.tail);

  int ii;
  printf("11 shifts:\n");
  for( ii = 0; ii < 11; ii++ )
    printf("%x ", buf_shift(&testbuf));
  printf("\n");
  
  buf_push(&testbuf, "1234", 4);
  
  for( ii = 0; ii < 11; ii++ )
    printf("%x ", buf_shift(&testbuf));
*/
  uart0_init();
  uint8_t c = 'a';
  while(1)
  {
    uart_0_nb_read();
    while (uart_0_ch_available())
    {        
      c = uart_0_get_ch();
      printf("%x ",c);
    }
  }
  return 0;
}
