

#ifndef CONFIG_LINUXFC_H
#define CONFIG_LINUXFC_H

/* Stub from tiny_2_1_1.h created Dec09 Pat Hickey */
#define Configure_GPS_RESET_Pin() LED_INIT(GPS_RESET)
#define Set_GPS_RESET_Pin_LOW() LED_ON(GPS_RESET)
#define Open_GPS_RESET_Pin() ClearBit(LED_DIR(GPS_RESET), LED_PIN(GPS_RESET))

/* P0.5 aka MAT0.1  */
#define SERVO_CLOCK_PIN  5
#define SERVO_CLOCK_PINSEL PINSEL0
#define SERVO_CLOCK_PINSEL_VAL 0x02
#define SERVO_CLOCK_PINSEL_BIT 10
/* p1.20          */
#define SERVO_RESET_PIN 20

/* ADC */

#define ADC_0 AdcBank1(6)
#ifdef USE_ADC_0
#ifndef USE_AD1
#define USE_AD1
#endif
#define USE_AD1_6
#endif

#define ADC_1 AdcBank1(7)
#ifdef USE_ADC_1
#ifndef USE_AD1
#define USE_AD1
#endif
#define USE_AD1_7
#endif


#define ADC_2 AdcBank0(4)
#ifdef USE_ADC_2
#ifndef USE_AD0
#define USE_AD0
#endif
#define USE_AD0_4
#endif

#define ADC_3 AdcBank0(6)
#ifdef USE_ADC_3
#ifndef USE_AD0
#define USE_AD0
#endif
#define USE_AD0_6
#endif

#define ADC_4 AdcBank0(3)
#ifdef USE_ADC_4
#ifndef USE_AD0
#define USE_AD0
#endif
#define USE_AD0_3
#endif

#define ADC_5 AdcBank0(2)
#ifdef USE_ADC_5
#ifndef USE_AD0
#define USE_AD0
#endif
#define USE_AD0_2
#endif

#define ADC_6 AdcBank0(1)
#ifdef USE_ADC_6
#ifndef USE_AD0
#define USE_AD0
#endif
#define USE_AD0_1
#endif

#define ADC_7 AdcBank1(3)
#ifdef USE_ADC_7
#ifndef USE_AD1
#define USE_AD1
#endif
#define USE_AD1_3
#endif

#define ADC_CHANNEL_VSUPPLY AdcBank1(5)
#ifndef USE_AD1
#define USE_AD1
#endif
#define USE_AD1_5


#ifndef VoltageOfAdc
#define VoltageOfAdc(adc) (0.0247311828*adc)
#endif

#define SPI_SELECT_SLAVE0_PORT 0
#define SPI_SELECT_SLAVE0_PIN 20

#define SPI1_DRDY_PINSEL PINSEL1
#define SPI1_DRDY_PINSEL_BIT   0
#define SPI1_DRDY_PINSEL_VAL   1
#define SPI1_DRDY_EINT         0
#define SPI1_DRDY_VIC_IT       VIC_EINT0

#endif /* CONFIG_LINUXFC_H */
