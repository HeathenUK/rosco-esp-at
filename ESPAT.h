#ifndef ESPAT_H_
#define ESPAT_H_

#include <stdio.h>
#include <machine.h>
#include <basicio.h>
#include <printf.h>
#include <string.h>
#include <malloc.h>
#include "ESPAT.h"

typedef struct {
    uint16_t    r_ptr;
    uint16_t    w_ptr;
    uint16_t    mask;
    uint8_t     data[1024];
} RingBuffer;

typedef enum {
    I2C_READ,
    TCP_RECEIVE
} ESP_QUERY_TYPE;

typedef enum {
    NO_QUERY,
    QUERY_RAISED,
    QUERY_READY
} ESP_QUERY_STATE;

typedef enum {
    STATE_DISCARD,
    STATE_AWAIT_D,
    STATE_AWAIT_R,
    STATE_AWAIT_V,
    STATE_AWAIT_I,
    STATE_AWAIT_2,
    STATE_AWAIT_C,
    STATE_AWAIT_R2,
    STATE_AWAIT_COLON,
    STATE_AWAIT_D2,
    STATE_AWAIT_DATA
} STATE_ESP;

typedef enum {
    STATE_EMPTY,
    STATE_AWAIT_COLON_C,
    STATE_AWAIT_COMMA_C,
    STATE_AWAIT_DATA_C
} STATE_ESP_COMMA;

typedef struct {
    ESP_QUERY_TYPE      type;
    ESP_QUERY_STATE     status;
    STATE_ESP           state;
    long                data_len;
    uint16_t            data_ptr;
    char                preamble[20];
    uint8_t             query_data[4096];
    bool                plus;
    bool                colon;
    bool                comma;
    char                data_len_str[7];
} ESP_Query;

typedef struct {
    ESP_QUERY_TYPE      type;
    ESP_QUERY_STATE     status;
    STATE_ESP_COMMA     state;
    long                data_len;
    uint16_t            data_ptr;
    char                preamble[20];
    uint8_t             query_data[4096];
    bool                plus;
    bool                colon;
    bool                comma;
    char                data_len_str[7];
} ESP_Query_Comma;

extern ESP_Query I2C;
extern ESP_Query_Comma HTTPGET;

typedef struct {
    STATE_ESP      state;
    bool           echo;
    // uint8_t     packet[2048];          // I don't know how big this needs to be - size of biggest packet
    // uint16_t    packet_ptr;            // If packet array gets bigger, this needs more bits too...
    // uint16_t    remain_len;            // Fill length remaining (only valid in STATE_FILL_DATA)
    RingBuffer  *ringBuffer;           // Ringbuffer in use 
} State_esp;

#define pgm_read_byte(addr) (*(const unsigned char *)(addr)) ///< PROGMEM workaround for non-AVR

void nop_loop(uint16_t n);

uint16_t process_incoming_esp(State_esp *state);

ESP_Query_Comma http_get(State_esp *state, CharDevice *uart);

ESP_Query i2c_read(State_esp *state, CharDevice *uart, unsigned int i2caddr, uint8_t reg, uint8_t len);

void i2c_write(CharDevice *uart, unsigned int i2caddr, uint8_t cmd);

void i2c_write_2(CharDevice *uart, unsigned int i2caddr, uint8_t cmd2, uint8_t cmd);

void i2c_write_3(CharDevice *uart, unsigned int i2caddr, uint8_t cmd3, uint8_t cmd2, uint8_t cmd);

void i2c_write_4(CharDevice *uart, unsigned int i2caddr, uint8_t cmd4, uint8_t cmd3, uint8_t cmd2, uint8_t cmd);

void i2c_setup(CharDevice *uart, uint8_t channel, uint8_t scl, uint8_t sda, int speed);

#endif