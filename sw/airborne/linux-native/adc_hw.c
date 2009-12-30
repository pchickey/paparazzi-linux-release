/*
 * $Id: adc_hw.c 3726 2009-07-18 18:22:45Z poine $
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

#include "adc.h"

/** First NB_ADC for bank 0, others for bank 2 */
static struct adc_buf* buffers[NB_ADC*2];

volatile uint16_t adc0_val[NB_ADC] = {1,  2,  3,  4,  5,  6,  7,  8};
volatile uint16_t adc1_val[NB_ADC] = {9, 10, 11, 12, 13, 14, 15, 16};

void adcISR0 ( void );
void adcISR1 ( void );

void adc_buf_channel(uint8_t adc_channel, struct adc_buf* s, uint8_t av_nb_sample) {
  buffers[adc_channel] = s;
  s->av_nb_sample = av_nb_sample;
}
void adc_init (void) { return; }
void adcISR0 (void) { return; }
void adcISR1 (void) { return; }

/*
void adcISR0 ( void ) {
  ISR_ENTRY();
  uint32_t tmp = AD0GDR;
  uint8_t  channel = (uint8_t)(tmp >> 24) & 0x07;
  uint16_t value = (uint16_t)(tmp >> 6) & 0x03FF;
  adc0_val[channel] = value;

  struct adc_buf* buf = buffers[channel];
  if (buf) {
    uint8_t new_head = buf->head + 1;
    if (new_head >= buf->av_nb_sample) new_head = 0;
    buf->sum -= buf->values[new_head];
    buf->values[new_head] = value;
    buf->sum += value;
    buf->head = new_head;   
  }
  
  VICVectAddr = 0x00000000;                 // clear this interrupt from the VIC
  ISR_EXIT();                               // recover registers and return
}
*/


