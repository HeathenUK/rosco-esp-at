#ifndef ESPAT_H_
#define ESPAT_H_

#include <stdio.h>
#include <machine.h>
#include <basicio.h>
#include <printf.h>
#include <string.h>
#include <malloc.h>

typedef struct {
    uint16_t    r_ptr;
    uint16_t    w_ptr;
    uint16_t    mask;
    uint8_t     data[1024];
} RingBuffer;

// typedef enum {
//     TCP,
//     I2C
// } AT_TYPE;

typedef struct {
    char        type[6];
    uint8_t     data_len;
    uint16_t    data_ptr;
    uint8_t     data[1024];
} AT_packet;

typedef enum {
    STATE_DISCARD,
    STATE_AWAIT_PLUS,
    STATE_AWAIT_D,
    STATE_AWAIT_R,
    STATE_AWAIT_V,
    STATE_AWAIT_I,
    STATE_AWAIT_2,
    STATE_AWAIT_C,
    STATE_AWAIT_R2,
    STATE_AWAIT_D2,
    STATE_AWAIT_COLON,
    STATE_AWAIT_DATA
} STATE_ESP;

typedef struct {
    STATE_ESP       state;
    uint8_t     packet[2048];          // I don't know how big this needs to be - size of biggest packet
    uint16_t    packet_ptr;            // If packet array gets bigger, this needs more bits too...
    uint16_t    remain_len;            // Fill length remaining (only valid in STATE_FILL_DATA)
    RingBuffer  *ringBuffer;           // Ringbuffer in use 
} State_esp;

#define pgm_read_byte(addr) (*(const unsigned char *)(addr)) ///< PROGMEM workaround for non-AVR

void nop_loop(uint16_t n);

uint16_t process_incoming_esp(State_esp *state);

void i2c_read(CharDevice *uart, unsigned int i2caddr, uint8_t reg, uint8_t len);

void i2c_write(CharDevice *uart, unsigned int i2caddr, uint8_t cmd);

void i2c_write_2(CharDevice *uart, unsigned int i2caddr, uint8_t cmd2, uint8_t cmd);

void i2c_write_3(CharDevice *uart, unsigned int i2caddr, uint8_t cmd3, uint8_t cmd2, uint8_t cmd);

void i2c_write_4(CharDevice *uart, unsigned int i2caddr, uint8_t cmd4, uint8_t cmd3, uint8_t cmd2, uint8_t cmd);

void i2c_setup(CharDevice *uart, uint8_t channel, uint8_t scl, uint8_t sda, int speed);

#endif