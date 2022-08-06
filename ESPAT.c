#include <stdio.h>
#include <machine.h>
#include <basicio.h>
#include <printf.h>
#include <string.h>
#include <malloc.h>
#include "ESPAT.h"

#define STANDARD_NOP 1000

void nop_loop(uint16_t n) {

    while (n--) {
        __asm__ __volatile__("nop");
    }

}

bool queryraised;
AT_packet at;

extern uint16_t unbuffer(RingBuffer *rb, unsigned char *buffer);

static uint8_t last_c = 0x00;

uint16_t process_incoming_esp(State_esp *state) {
    
    static uint8_t buffer[1024];
	uint16_t count = unbuffer(state->ringBuffer, buffer);      //Pull the ring buffer

        if (count == 0) return 0;
	
    	CharDevice duart_a;
        mcGetDevice(0, &duart_a);
		if (mcGetDevice(0, &duart_a)) fctprintf(mcSendDevice, &duart_a, "Pulled the ringbuffer, got %d chars.\r\n", count);

		#ifdef DEBUG_PACKETS
			for (int i = 0; i < count; i++) {
				fctprintf(mcSendDevice, &duart_a, "0x%02x ", buffer[i]);
			}
			fctprintf(mcSendDevice, &duart_a, "\r\n\r\n");
		#endif

        for (int i = 0; i < count; i++) {
            
            if (queryraised == true) {
                fctprintf(mcSendDevice, &duart_a, "Processing following a query being raised, prior c was %c (0X%02x)\r\n", last_c, last_c);

                switch(state->state) {
                    
                    case STATE_DISCARD:
                        if (buffer[i] == '+' && last_c != 'T') {
                            state->state = STATE_AWAIT_D;
                            fctprintf(mcSendDevice, &duart_a, "Non-AT + received\r\n");
                        } else {
                            state->state = STATE_DISCARD;
                            printf("%c", buffer[i]);
                        }
                        break;
                    
                    case STATE_AWAIT_D:
                        if (buffer[i] == 'D') {
                                state->state = STATE_AWAIT_R;
                                fctprintf(mcSendDevice, &duart_a, "Got a D!\r\n");
                        } else {
                            state->state = STATE_DISCARD;
                            printf("%c", buffer[i]);
                        }
                        break;
                            
                    case STATE_AWAIT_R:
                        if (buffer[i] == 'R') {
                                state->state = STATE_AWAIT_V;
                                fctprintf(mcSendDevice, &duart_a, "Got an R!\r\n");
                                printf("%c", buffer[i]);
                        } else {
                            state->state = STATE_DISCARD;
                            printf("%c", buffer[i]);
                        }
                        break;

                    case STATE_AWAIT_V:
                        if (buffer[i] == 'V') {
                                state->state = STATE_AWAIT_I;
                                fctprintf(mcSendDevice, &duart_a, "Got a V!\r\n");
                        } else {
                            state->state = STATE_DISCARD;
                            printf("%c", buffer[i]);
                        }
                        break;

                    case STATE_AWAIT_I:
                        if (buffer[i] == 'I') {
                                state->state = STATE_AWAIT_2;
                                fctprintf(mcSendDevice, &duart_a, "Got an I!\r\n");
                        } else {
                            state->state = STATE_DISCARD;
                            printf("%c", buffer[i]);
                        }
                        break;

                    case STATE_AWAIT_2:
                        if (buffer[i] == '2') {
                                state->state = STATE_AWAIT_C;
                                fctprintf(mcSendDevice, &duart_a, "Got a 2!\r\n");
                        } else {
                            state->state = STATE_DISCARD;
                            printf("%c", buffer[i]);
                        }
                        break;

                    case STATE_AWAIT_C:
                        if (buffer[i] == 'C') {
                                state->state = STATE_AWAIT_R2;
                                fctprintf(mcSendDevice, &duart_a, "Got a C!\r\n");
                        } else {
                            state->state = STATE_DISCARD;
                            printf("%c", buffer[i]);
                        }
                        break;

                    case STATE_AWAIT_R2:
                        if (buffer[i] == 'R') {
                                state->state = STATE_AWAIT_D2;
                                fctprintf(mcSendDevice, &duart_a, "Got an R!\r\n");
                        } else {
                            state->state = STATE_DISCARD;
                            printf("%c", buffer[i]);
                        }
                        break;

                    case STATE_AWAIT_D2:
                        if (buffer[i] == 'D') {
                                state->state = STATE_AWAIT_COLON;
                                fctprintf(mcSendDevice, &duart_a, "Got a D!\r\n");
                        } else {
                            state->state = STATE_DISCARD;
                            printf("%c", buffer[i]);
                        }
                        break;

                    case STATE_AWAIT_COLON:
                        if (buffer[i] == ':') {
                                at.data_ptr = 0;
                                state->state = STATE_AWAIT_DATA;
                                fctprintf(mcSendDevice, &duart_a, "Got a colon!\r\n");
                        } else {
                            state->state = STATE_DISCARD;
                            printf("%c", buffer[i]);
                        }
                        break;

                    case STATE_AWAIT_DATA:
                        at.data[at.data_ptr++] = buffer[i];
                        if (at.data_ptr == at.data_len) {
                            queryraised = false;
                            state->state = STATE_DISCARD;
                            fctprintf(mcSendDevice, &duart_a, "Completed a query with value 0x%02x!\r\n", *at.data);
                        }
                        break;

                }
            }

            else printf("%c", buffer[i]);
        
        last_c = buffer[i];
        }

        return count;
}

void i2c_read(CharDevice *uart, unsigned int i2caddr, uint8_t reg, uint8_t len) {
    
    i2c_write(uart, i2caddr, reg);
    //fctprintf(mcSendDevice, uart, "AT+DRVI2CWRBYTES=0,0x%02x,1,0x%02x\r", i2caddr, reg);
    nop_loop(STANDARD_NOP);
    //if (mcGetDevice(0, &duart_a)) fctprintf(mcSendDevice, &duart_a, "AT+DRVI2CWRBYTES=0,0x%02X,2,0x%02X40\r\n", i2caddr, cmd);
    at.data_len = len;
    nop_loop(STANDARD_NOP);
    fctprintf(mcSendDevice, uart, "AT+DRVI2CRD=0,0x%02x,%d\r", i2caddr, len);
    printf("\n");
    queryraised = true;
    nop_loop(STANDARD_NOP);

}

void i2c_write(CharDevice *uart, unsigned int i2caddr, uint8_t cmd) {
    
    fctprintf(mcSendDevice, uart, "AT+DRVI2CWRBYTES=0,0x%02x,1,0x%02X\r", i2caddr, cmd);
    printf("\n");
    //if (mcGetDevice(0, &duart_a)) fctprintf(mcSendDevice, &duart_a, "AT+DRVI2CWRBYTES=0,0x%02X,2,0x%02X40\r\n", i2caddr, cmd);
    nop_loop(STANDARD_NOP);

}


void i2c_write_2(CharDevice *uart, unsigned int i2caddr, uint8_t cmd2, uint8_t cmd) {
    fctprintf(mcSendDevice, uart, "AT+DRVI2CWRBYTES=0,0x%02x,2,0x%02X%02X\r", i2caddr, cmd, cmd2);
    printf("\n");
    //if (mcGetDevice(0, &duart_a)) fctprintf(mcSendDevice, &duart_a, "AT+DRVI2CWRBYTES=0,0x%02X,2,0x%02X40\r\n", i2caddr, cmd);
    nop_loop(STANDARD_NOP);

}

void i2c_write_3(CharDevice *uart, unsigned int i2caddr, uint8_t cmd3, uint8_t cmd2, uint8_t cmd) {
    fctprintf(mcSendDevice, uart, "AT+DRVI2CWRBYTES=0,0x%02x,3,0x%02X%02X%02X\r", i2caddr, cmd, cmd2, cmd3);
    printf("\n");
    //if (mcGetDevice(0, &duart_a)) fctprintf(mcSendDevice, &duart_a, "AT+DRVI2CWRBYTES=0,0x%02X,3,0x%02X%02XC0\r\n", i2caddr, cmd, cmd2);
    nop_loop(STANDARD_NOP);

}

void i2c_write_4(CharDevice *uart, unsigned int i2caddr, uint8_t cmd4, uint8_t cmd3, uint8_t cmd2, uint8_t cmd) {
    fctprintf(mcSendDevice, uart, "AT+DRVI2CWRBYTES=0,0x%02x,4,0x%02X%02X%02X%02X\r", i2caddr, cmd, cmd2, cmd3, cmd4);
    printf("\n");
    // if (mcGetDevice(0, &duart_a)) fctprintf(mcSendDevice, &duart_a, "AT+DRVI2CWRBYTES=0,0x%02X,4,0x%02X%02X%02X40\r\n", i2caddr, cmd, cmd2, cmd3);
    nop_loop(STANDARD_NOP);

}

void i2c_setup(CharDevice *uart, uint8_t channel, uint8_t scl, uint8_t sda, int speed) {

    fctprintf(mcSendDevice, uart, "AT+DRVI2CINIT=%u,%u,%u,%d\r", channel, scl, sda, speed);
    printf("\n");

}
