#ifndef __WS2812_H
#define __WS2812_H

#include <stdint.h>
#include <stdbool.h>

void encode_byte( uint8_t data, int16_t buffer_index );
void generate_ws_buffer( uint8_t RData,uint8_t GData,uint8_t BData, int16_t led_no );
void send_ws2812b(void);
void setAllPixelColor(uint8_t r, uint8_t g, uint8_t b);
void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
void ws2812_init(void);
void update_lauflicht(void);
void setLedbar(uint8_t barNo, uint8_t lvl, uint8_t r, uint8_t g, uint8_t b);
void lauflicht_init();
void conf_lauflicht(uint8_t speed, uint8_t r, uint8_t g, uint8_t b, bool inv);
void start_lauflicht();
void stop_lauflicht();
void clear_LED();
void setLeaderLED(uint8_t r, uint8_t g, uint8_t b);
void setAssistLED(uint8_t r, uint8_t g, uint8_t b);
void setCoAssistLED(uint8_t r, uint8_t g, uint8_t b);
void setNormalLED(uint8_t r, uint8_t g, uint8_t b);
void clearLeaderLED();
void clearAssistLED();
void clearCoAssistLED();
void clearNormalLED();

#endif
