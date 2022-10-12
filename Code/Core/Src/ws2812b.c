/*
 * ws2812b.c
 *
 *  Created on: 27.04.2020
 *      Author: Thomas
 */
#include <stdio.h>
#include <spi.h>
#include <stdint.h>
#include <stdbool.h>

#include "ws2812b.h"
#include "main.h"

#define LED_NO  10
#define LED_BUFFER_LENGTH (LED_NO*16)

#define std_r 100
#define std_g 50
#define std_b 50

uint8_t ws_buffer[LED_BUFFER_LENGTH];
uint8_t update = 0;


/** Basic Functions **/
void encode_byte( uint8_t data, int16_t buffer_index )
{
   uint8_t encode1;
   uint8_t encode2;
   uint8_t encode3;
   uint8_t encode4;
   uint8_t help;
   encode1 = 0x00;
   encode2 = 0x00;
   encode3 = 0x00;
   encode4 = 0x00;
   //1100 for 1
   //100 for 0
   //encode first bit
   help = data>>7;
   encode1 |= 0x08;
   encode1 |= help <<2;
   encode1 = encode1<<4;
   //encode second bit
   help = data>>6;
   help &= 0x01;
   encode1 |= 0x08;
   encode1 |= help <<2;
   //encode third bit
   help = data>>5;
   help &= 0x01;
   encode2 |= 0x08;
   encode2 |= help <<2;
   encode2 = encode2 <<4;
   //encode fourth bit
   help = data>>4;
   help &= 0x01;
   encode2 |= 0x08;
   encode2 |= help <<2;
   //encode fifth bit
   help = data>>3;
   help &= 0x01;
   encode3 |= 0x08;
   encode3 |= help <<2;
   encode3 = encode3 <<4;
   //encode sixth bit
   help = data>>2;
   help &= 0x01;
   encode3 |= 0x08;
   encode3 |= help <<2;
   //encode seventh bit
   help = data>>1;
   help &= 0x01;
   encode4 |= 0x08;
   encode4 |= help <<2;
   encode4 = encode4 <<4;
   //encode eight bit
   help = data;
   help &= 0x01;
   encode4 |= 0x08;
   encode4 |= help <<2;

   ws_buffer[buffer_index++ ] = encode1;
   ws_buffer[buffer_index++ ] = encode2;
   ws_buffer[buffer_index++ ] = encode3;
   ws_buffer[buffer_index++ ] = encode4;

}
void generate_ws_buffer( uint8_t RData,uint8_t GData,uint8_t BData, int16_t led_no )
{
	//ws2812b
//G--R--B
//MSB first
   int offset = led_no * 12;
   encode_byte( GData, offset);
   encode_byte( RData, offset+4);
   encode_byte( BData, offset+8);
}
void send_ws2812b(void)
 {
	//if (1){
    HAL_SPI_Transmit_DMA( &hspi1, ws_buffer, LED_BUFFER_LENGTH );
    // wait until finished
    while(__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_BSY ));
	//}//else{
    //HAL_SPI_Transmit( &hspi1, ws_buffer, LED_BUFFER_LENGTH, 300 );
	//}
 }

void setAllPixelColor(uint8_t r, uint8_t g, uint8_t b)
{
   int i;
   for(i=0;i< LED_NO;i++) {
      generate_ws_buffer( r, g, b, i );
   }
   send_ws2812b();
   update = 1;
   //Send_SPI();
}
 void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b)
 {
   generate_ws_buffer( r, g, b, n );
   send_ws2812b();
   update = 1;
   //Send_SPI();
}
/**
 * initialize MOSI pin to LOW.  Without this, first time transmit for first LED might be wrong.
 *
 */
void ws2812_init(void)
{
	//HAL_TIM_Base_Start_IT(&htim16);
   uint8_t buffer0[2] = { 0, 0 };
   HAL_SPI_Transmit(&hspi1, buffer0, 1, 1000);
   /* Clear all LEDs */
   setAllPixelColor(0,0,0);
}


void clear_LED()
{
	setAllPixelColor(0,0,0);
}

