/*
 * $Id: uart_hw.c 3873 2009-08-05 15:41:30Z mmm $
 *  
 * Copyright (C) 2008  Pascal Brisset, Antoine Drouin
 *
 * This file is part of paparazzi.
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA. 
 *
 */

#include "uart.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <strings.h>

bool_t buf_full(struct ringbuf *buf)
{
  if (buf->head == buf->tail - 1) return TRUE;
  if (buf->head == UART_BUF_SIZE && buf->tail == 0) return TRUE;
  return FALSE;
}

bool_t buf_empty(struct ringbuf *buf)
{
  if (buf->head == buf->tail) return TRUE;
  else return FALSE;
}
bool_t buf_push(struct ringbuf *buf, uint8_t* str, int n)
{
  // this is recursive and slow
  if (buf_full(buf)) return FALSE;
  if (n == 0) return TRUE;
  
  buf->buf[buf->head] = str[0];
  buf->head += 1;
  if (buf->head >= UART_BUF_SIZE) buf->head = 0;
  
  return buf_push(buf, str + 1, n - 1);
}

uint8_t buf_shift(struct ringbuf *buf)
{
  uint8_t retval;
  if (buf_empty(buf)) return 0;  // the caller should check buf_empty before a call, but this is a guard
  retval = buf->buf[buf->tail];
  buf->tail += 1;
  if (buf->tail >= UART_BUF_SIZE) buf->tail = 0;
  return retval;
}


#ifdef USE_UART0
int fd_uart0;
struct ringbuf uart0_buf;

void uart0_init(void) 
{
  struct termios tio;
  bzero(&tio,sizeof(tio));

  fd_uart0 = open(UART0_FNAME, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (fd_uart0 < 0) { printf("%s ",UART0_FNAME); perror("uart0 open failed"); exit(-1); }
  tio.c_cflag = UART0_BAUD | CS8 | CREAD | CLOCAL ;
  tio.c_lflag = ICANON;
  tcflush(fd_uart0, TCIFLUSH);
  tcsetattr(fd_uart0,TCSANOW,&tio);

  uart0_buf.head = 0;
  uart0_buf.tail = 0;

  return; 
}

void uart0_transmit(unsigned char data ) 
{ 
  write(fd_uart0, &data, sizeof(data)); 
}
bool_t uart0_check_free_space( uint8_t len) { return TRUE; }

void uart_0_nb_read(void) 
{
  ssize_t nr;
  char read_buf[1];
  
  if (buf_full(&uart0_buf)) return;
  
  for(;;)  
  { nr = read(fd_uart0, read_buf,(ssize_t)1);
    if (nr <= 0) break;
    if (buf_push(&uart0_buf, (uint8_t *)read_buf, (int) nr) == FALSE) break;}
}

bool_t uart_0_ch_available(void)
{  
  if (buf_empty(&uart0_buf))
    return FALSE;
  else
    return TRUE;
}

uint8_t uart_0_get_ch(void) 
{
  return buf_shift(&uart0_buf);
}


#endif

#ifdef USE_UART1
int fd_uart1;
struct ringbuf uart1_buf;

void uart1_init(void) 
{
  struct termios tio;
  bzero(&tio,sizeof(tio));

  fd_uart1 = open(UART1_FNAME, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (fd_uart1 < 0) { printf("%s ",UART1_FNAME); perror("uart1 open failed"); exit(-1); }
  tio.c_cflag = UART1_BAUD | CS8 | CREAD | CLOCAL ;
  tio.c_lflag = ICANON;
  tcflush(fd_uart1, TCIFLUSH);
  tcsetattr(fd_uart1,TCSANOW,&tio);

  uart1_buf.head = 0;
  uart1_buf.tail = 0;

  return; 
}

void uart1_transmit(unsigned char data ) 
{ 
  write(fd_uart1, &data, sizeof(data)); 
}
bool_t uart1_check_free_space( uint8_t len) { return TRUE; }

void uart_1_nb_read(void) 
{
  ssize_t nr;
  char read_buf[1];
  
  if (buf_full(&uart1_buf)) return;
  
  for(;;)  
  { nr = read(fd_uart1, read_buf,(ssize_t)1);
    if (nr <= 0) break;
    if (buf_push(&uart1_buf, (uint8_t *)read_buf, (int) nr) == FALSE) break;}
}

bool_t uart_1_ch_available(void)
{  
  if (buf_empty(&uart1_buf))
    return FALSE;
  else
    return TRUE;
}

uint8_t uart_1_get_ch(void) 
{
  return buf_shift(&uart1_buf);
}


#endif


