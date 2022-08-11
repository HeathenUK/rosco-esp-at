#include <stdio.h>
#include <machine.h>
#include <basicio.h>
#include <printf.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "ESPAT.h"

//#define DEBUG_A

#ifdef DEBUG_A
//#define DEBUGF(...) do { printf(__VA_ARGS__); } while (0)
#define DEBUGF(...) do { CharDevice duart_a; if (mcGetDevice(0, &duart_a)) { fctprintf(mcSendDevice, &duart_a, __VA_ARGS__); }} while (0)
#else
#define DEBUGF(...)
#endif

#define STANDARD_NOP 500

void nop_loop(uint16_t n) {

    while (n--) {
        __asm__ __volatile__("nop");
    }

}

extern uint16_t unbuffer(RingBuffer *rb, unsigned char *buffer);

static uint8_t last_c = 0x00;

ESP_Query I2C;
ESP_Query_Comma HTTPGET;

uint16_t process_incoming_esp(State_esp *state) {
    
    static uint8_t buffer[1024];
	uint16_t count = unbuffer(state->ringBuffer, buffer);      //Pull the ring buffer

        if (count == 0) return 0;
	
    	CharDevice duart_a;
        mcGetDevice(0, &duart_a);
		DEBUGF("Pulled the ringbuffer, got %d chars.\r\n", count);

		#ifdef DEBUG_PACKETS
			for (int i = 0; i < count; i++) {
				fctprintf(mcSendDevice, &duart_a, "0x%02x ", buffer[i]);
			}
			fctprintf(mcSendDevice, &duart_a, "\r\n\r\n");
		#endif

        // char strcat_char[2];
        // strcat_char[1] = '\0';

        // static char preamble[10];
        uint8_t preamble_ptr = 0;
        uint8_t data_len_str_ptr = 0;
        static uint16_t data_ptr = 1;
        
        HTTPGET.data_ptr = 0;
        // static char preamble_check[10];
        //uint8_t preamble_check_ptr = 0;


        for (int i = 0; i < count; i++) {
            
            if (I2C.status == QUERY_RAISED) {
                //fctprintf(mcSendDevice, &duart_a,"[0X%02x]\r\n", last_c);
                DEBUGF("Processing following a query being raised, prior c was %c (0X%02x)\r\n", last_c, last_c);

                switch(I2C.state) {
                    
                    case STATE_DISCARD:
                        if (buffer[i] == '+' && last_c != 'T') {
                            I2C.state = STATE_AWAIT_D;
                            DEBUGF("Non-AT + received\r\n");
                        } else {
                            I2C.state = STATE_DISCARD;
                            if (state->echo) printf("%c", buffer[i]);
                        }
                        break;
                    
                    case STATE_AWAIT_D:
                        if (buffer[i] == 'D') {
                                I2C.state = STATE_AWAIT_R;
                                DEBUGF("Got a D!\r\n");
                        } else {
                            I2C.state = STATE_DISCARD;
                            if (state->echo) printf("%c", buffer[i]);
                        }
                        break;
                            
                    case STATE_AWAIT_R:
                        if (buffer[i] == 'R') {
                                I2C.state = STATE_AWAIT_V;
                                DEBUGF("Got an R!\r\n");
                                if (state->echo) printf("%c", buffer[i]);
                        } else {
                            I2C.state = STATE_DISCARD;
                            if (state->echo) printf("%c", buffer[i]);
                        }
                        break;

                    case STATE_AWAIT_V:
                        if (buffer[i] == 'V') {
                                I2C.state = STATE_AWAIT_I;
                                DEBUGF("Got a V!\r\n");
                        } else {
                            I2C.state = STATE_DISCARD;
                            if (state->echo) printf("%c", buffer[i]);
                        }
                        break;

                    case STATE_AWAIT_I:
                        if (buffer[i] == 'I') {
                                I2C.state = STATE_AWAIT_2;
                                DEBUGF("Got an I!\r\n");
                        } else {
                            I2C.state = STATE_DISCARD;
                            if (state->echo) printf("%c", buffer[i]);
                        }
                        break;

                    case STATE_AWAIT_2:
                        if (buffer[i] == '2') {
                                I2C.state = STATE_AWAIT_C;
                                DEBUGF("Got a 2!\r\n");
                        } else {
                            I2C.state = STATE_DISCARD;
                            if (state->echo) printf("%c", buffer[i]);
                        }
                        break;

                    case STATE_AWAIT_C:
                        if (buffer[i] == 'C') {
                                I2C.state = STATE_AWAIT_R2;
                                DEBUGF("Got a C!\r\n");
                        } else {
                            I2C.state = STATE_DISCARD;
                            if (state->echo) printf("%c", buffer[i]);
                        }
                        break;

                    case STATE_AWAIT_R2:
                        if (buffer[i] == 'R') {
                                I2C.state = STATE_AWAIT_D2;
                                DEBUGF("Got an R!\r\n");
                        } else {
                            I2C.state = STATE_DISCARD;
                            if (state->echo) printf("%c", buffer[i]);
                        }
                        break;

                    case STATE_AWAIT_D2:
                        if (buffer[i] == 'D') {
                                I2C.state = STATE_AWAIT_COLON;
                                DEBUGF("Got a D!\r\n");
                        } else {
                            I2C.state = STATE_DISCARD;
                            if (state->echo) printf("%c", buffer[i]);
                        }
                        break;

                    case STATE_AWAIT_COLON:
                        if (buffer[i] == ':') {
                                I2C.data_ptr = 0;
                                I2C.state = STATE_AWAIT_DATA;
                                DEBUGF("Got a colon!\r\n");
                        } else {
                            I2C.state = STATE_DISCARD;
                            if (state->echo) printf("%c", buffer[i]);
                        }
                        break;

                    case STATE_AWAIT_DATA:
                        I2C.query_data[I2C.data_ptr++] = buffer[i];
                        fctprintf(mcSendDevice, &duart_a,"[0X%02x]\r\n", buffer[i]);
                        if (I2C.data_ptr == I2C.data_len) {
                            //queryraised = false;
                            I2C.state = STATE_DISCARD;
                            I2C.status = QUERY_READY;
                            // printf("Completed a query with values:\r\n\n");
                            // for (int j = 0; j < I2C.data_len; j++) {
                        
                            //     printf("Byte %d: 0x%02x\r\n", j, I2C.query_data[j]);

                            // }
                            
                            
                        }
                        break;

                }
            }

            else if (HTTPGET.status == QUERY_RAISED) {
                //printf("\n[H]");
                switch(HTTPGET.state) {
                    
                    case STATE_EMPTY:
                        if (buffer[i] == '+' && last_c != 'T') {
                            HTTPGET.state = STATE_AWAIT_COLON_C;
                            DEBUGF("Non-AT + received\r\n");
                        } else {
                            HTTPGET.state = STATE_EMPTY;
                            if (state->echo) printf("%c", buffer[i]);
                        }
                        break;
                        
                    case STATE_AWAIT_COLON_C:
                        if (buffer[i] == ':') {
                                HTTPGET.state = STATE_AWAIT_COMMA_C;
                                DEBUGF("Got a colon!\r\n");
                        } else {

                            HTTPGET.preamble[preamble_ptr++] = buffer[i];

                        }
                        break;

                    case STATE_AWAIT_COMMA_C:
                        if (buffer[i] == ',') {
                                HTTPGET.state = STATE_AWAIT_DATA_C;
                                data_ptr = 0;
                                DEBUGF("Got a comma!\r\n");
                                CharDevice duart_a;if (mcGetDevice(0, &duart_a)) { fctprintf(mcSendDevice, &duart_a, "Preamble: %s, Length: %s\r\n",HTTPGET.preamble, HTTPGET.data_len_str); };
                                printf("\r\f");
                        } else {

                            HTTPGET.data_len_str[data_len_str_ptr++] = buffer[i];

                        }
                        break;                    

                    case STATE_AWAIT_DATA_C:

                        if (data_ptr == atoi(HTTPGET.data_len_str) - 1)
                        {
                            HTTPGET.query_data[data_ptr++] = buffer[i];
                            //CharDevice duart_a;if (mcGetDevice(0, &duart_a)) { fctprintf(mcSendDevice, &duart_a, "%d out of %d\r\n", data_ptr - 1, atoi(HTTPGET.data_len_str) - 1); };
                            CharDevice duart_a;if (mcGetDevice(0, &duart_a)) { fctprintf(mcSendDevice, &duart_a, "0X%02X", buffer[i]); };
                            printf("%03d:%02X ", (data_ptr - 1), buffer[i]);
                            if(data_ptr % 14 == 0 && data_ptr != 0 ) printf("\n");

                            HTTPGET.state = STATE_EMPTY;
                            HTTPGET.status = QUERY_READY;
                            preamble_ptr = 0;
                            data_len_str_ptr = 0;

                            memset(HTTPGET.preamble, '\0', strlen(HTTPGET.preamble));
                            memset(HTTPGET.data_len_str, '\0', strlen(HTTPGET.data_len_str));

                        } else {
                            
                            HTTPGET.query_data[data_ptr++] = buffer[i];
                            //CharDevice duart_a;if (mcGetDevice(0, &duart_a)) { fctprintf(mcSendDevice, &duart_a, "%d out of %d\r\n", data_ptr - 1, atoi(HTTPGET.data_len_str) - 1); };
                            CharDevice duart_a;if (mcGetDevice(0, &duart_a)) { fctprintf(mcSendDevice, &duart_a, "0X%02X, ", buffer[i]); };
                            printf("%03d:%02X ", (data_ptr - 1), buffer[i]);
                            if(data_ptr % 14 == 0 && data_ptr != 0 ) printf("\n");

                        }
                        break;

                }

            }

            //else if (state->echo) printf("[0x%02x]", buffer[i]);
            else if ((buffer[i] != '\f') && ((state->echo))) printf("%c", buffer[i]);
        
        last_c = buffer[i];
        }

        return count;
}

ESP_Query_Comma http_get(State_esp *state, CharDevice *uart) {

    //fctprintf(mcSendDevice, uart, "\rAT+HTTPCGET=\"https://people.math.sc.edu/Burkardt/data/bmp/all_gray.bmp\"\r");
    fctprintf(mcSendDevice, uart, "\rAT+HTTPCGET=\"https://www.w3.org/People/mimasa/test/imgformat/img/w3c_home_2.bmp\"\r");
    nop_loop(STANDARD_NOP);
    HTTPGET.status = QUERY_RAISED;
    while (HTTPGET.status != QUERY_READY) {
        nop_loop(STANDARD_NOP);
        process_incoming_esp(state);
    }
    return HTTPGET;
}

ESP_Query_Comma http_get2(State_esp *state, CharDevice *uart) {

    //fctprintf(mcSendDevice, uart, "\rAT+HTTPCGET=\"https://people.math.sc.edu/Burkardt/data/bmp/all_gray.bmp\"\r");
    fctprintf(mcSendDevice, uart, "AT+HTTPCLIENT=2,0,\"https://www.w3.org/People/mimasa/test/imgformat/img/w3c_home_2.bmp\",\"www.w3.org\",\"/People/mimasa/test/imgformat/img/w3c_home_2.bmp\",2\r");
    
//    https://www.w3.org/People/mimasa/test/imgformat/img/w3c_home_2.bmp
    
    nop_loop(STANDARD_NOP);
    HTTPGET.status = QUERY_RAISED;
    while (HTTPGET.status != QUERY_READY) {
        process_incoming_esp(state);
    }
    return HTTPGET;
}

ESP_Query i2c_read(State_esp *state, CharDevice *uart, unsigned int i2caddr, uint8_t reg, uint8_t len) {
    
    i2c_write(uart, i2caddr, reg);
    //fctprintf(mcSendDevice, uart, "AT+DRVI2CWRBYTES=0,0x%02x,1,0x%02x\r", i2caddr, reg);
    nop_loop(STANDARD_NOP);
    //if (mcGetDevice(0, &duart_a)) fctprintf(mcSendDevice, &duart_a, "AT+DRVI2CWRBYTES=0,0x%02X,2,0x%02X40\r\n", i2caddr, cmd);
    I2C.data_len = len;
    nop_loop(STANDARD_NOP);
    fctprintf(mcSendDevice, uart, "AT+DRVI2CRD=0,0x%02x,%d\r", i2caddr, len);
    //queryraised = true;
    I2C.status = QUERY_RAISED;
    while (I2C.status != QUERY_READY) {
        process_incoming_esp(state);
    }
    return I2C;

}

void i2c_write(CharDevice *uart, unsigned int i2caddr, uint8_t cmd) {
    
    fctprintf(mcSendDevice, uart, "\rAT+DRVI2CWRBYTES=0,0x%02x,1,0x%02X\r", i2caddr, cmd);
    //if (mcGetDevice(0, &duart_a)) fctprintf(mcSendDevice, &duart_a, "AT+DRVI2CWRBYTES=0,0x%02X,2,0x%02X40\r\n", i2caddr, cmd);
    nop_loop(STANDARD_NOP);

}


void i2c_write_2(CharDevice *uart, unsigned int i2caddr, uint8_t cmd2, uint8_t cmd) {
    fctprintf(mcSendDevice, uart, "\rAT+DRVI2CWRBYTES=0,0x%02x,2,0x%02X%02X\r", i2caddr, cmd, cmd2);
    //if (mcGetDevice(0, &duart_a)) fctprintf(mcSendDevice, &duart_a, "AT+DRVI2CWRBYTES=0,0x%02X,2,0x%02X40\r\n", i2caddr, cmd);
    nop_loop(STANDARD_NOP);

}

void i2c_write_3(CharDevice *uart, unsigned int i2caddr, uint8_t cmd3, uint8_t cmd2, uint8_t cmd) {
    fctprintf(mcSendDevice, uart, "\rAT+DRVI2CWRBYTES=0,0x%02x,3,0x%02X%02X%02X\r", i2caddr, cmd, cmd2, cmd3);
    //if (mcGetDevice(0, &duart_a)) fctprintf(mcSendDevice, &duart_a, "AT+DRVI2CWRBYTES=0,0x%02X,3,0x%02X%02XC0\r\n", i2caddr, cmd, cmd2);
    nop_loop(STANDARD_NOP);

}

void i2c_write_4(CharDevice *uart, unsigned int i2caddr, uint8_t cmd4, uint8_t cmd3, uint8_t cmd2, uint8_t cmd) {
    fctprintf(mcSendDevice, uart, "\rAT+DRVI2CWRBYTES=0,0x%02x,4,0x%02X%02X%02X%02X\r", i2caddr, cmd, cmd2, cmd3, cmd4);
    // if (mcGetDevice(0, &duart_a)) fctprintf(mcSendDevice, &duart_a, "AT+DRVI2CWRBYTES=0,0x%02X,4,0x%02X%02X%02X40\r\n", i2caddr, cmd, cmd2, cmd3);
    nop_loop(STANDARD_NOP);

}

void i2c_setup(CharDevice *uart, uint8_t channel, uint8_t scl, uint8_t sda, int speed) {

    fctprintf(mcSendDevice, uart, "\rAT+DRVI2CINIT=%u,%u,%u,%d\r", channel, scl, sda, speed);


}