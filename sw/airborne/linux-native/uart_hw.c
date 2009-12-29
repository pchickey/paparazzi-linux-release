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

#include "uart_hw.h"

#ifdef USE_UART0
void uart0_ISR(void) { return; }
void uart0_init(void) { return; }  
void uart0_transmit(unsigned char data ) { return; }
bool_t uart0_check_free_space( uint8_t len) { return 1; }

bool_t uart_0_ch_available(void) { return 0; }
uint8_t uart_0_get_ch(void) { return 'g'; }
#endif

#ifdef USE_UART1
void uart1_ISR(void) { return; }
void uart1_init(void) { return; }  
void uart1_transmit(unsigned char data ) { return; }
bool_t uart1_check_free_space( uint8_t len) { return 1; }

bool_t uart_1_ch_available(void) { return 0; }
uint8_t uart_1_get_ch(void) { return 'g'; }
#endif


