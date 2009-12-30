/*
 * Paparazzi mcu0 $Id: pprz_transport.c 929 2006-06-02 12:11:37Z poine $
 *  
 * Copyright (C) 2006  Pascal Brisset, Antoine Drouin
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

#include <inttypes.h>
#include "pprz_transport.h"
#include "uart.h"

uint8_t ck_a, ck_b;
volatile bool_t pprz_msg_received = FALSE;
uint8_t pprz_ovrn, pprz_error;
volatile uint8_t pprz_payload_len;
uint8_t pprz_payload[PPRZ_PAYLOAD_LEN];
