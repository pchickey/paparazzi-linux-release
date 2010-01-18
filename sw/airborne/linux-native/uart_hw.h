/*
 * $Id: uart_hw.h 3726 2009-07-18 18:22:45Z poine $
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

#ifndef UART_HW_H
#define UART_HW_H

#include "std.h"
#include <inttypes.h>

#define UART_BUF_SIZE 1024

struct ringbuf
{
  uint8_t buf[UART_BUF_SIZE];
  int head;
  int tail;
};
bool_t buf_full(struct ringbuf *);
bool_t buf_empty(struct ringbuf *);
bool_t buf_push(struct ringbuf *, uint8_t*, int);
uint8_t buf_shift(struct ringbuf *);

#define Uart0ChAvailable uart_0_ch_available
#define Uart0Getch uart_0_get_ch
bool_t uart_0_ch_available(void);
uint8_t uart_0_get_ch(void);
void uart_0_nb_read(void);

#define Uart1ChAvailable uart_1_ch_available
#define Uart1Getch uart_1_get_ch
bool_t uart_1_ch_available(void);
uint8_t uart_1_get_ch(void);
void uart_1_nb_read(void);

#endif /* UART_HW_H */
