#include "ESPAT.H"

static const unsigned char font[] = {
        0x00, 0x00, 0x00, 0x00, 0x00,
	0x3E, 0x5B, 0x4F, 0x5B, 0x3E,
	0x3E, 0x6B, 0x4F, 0x6B, 0x3E,
	0x1C, 0x3E, 0x7C, 0x3E, 0x1C,
	0x18, 0x3C, 0x7E, 0x3C, 0x18,
	0x1C, 0x57, 0x7D, 0x57, 0x1C,
	0x1C, 0x5E, 0x7F, 0x5E, 0x1C,
	0x00, 0x18, 0x3C, 0x18, 0x00,
	0xFF, 0xE7, 0xC3, 0xE7, 0xFF,
	0x00, 0x18, 0x24, 0x18, 0x00,
	0xFF, 0xE7, 0xDB, 0xE7, 0xFF,
	0x30, 0x48, 0x3A, 0x06, 0x0E,
	0x26, 0x29, 0x79, 0x29, 0x26,
	0x40, 0x7F, 0x05, 0x05, 0x07,
	0x40, 0x7F, 0x05, 0x25, 0x3F,
	0x5A, 0x3C, 0xE7, 0x3C, 0x5A,
	0x7F, 0x3E, 0x1C, 0x1C, 0x08,
	0x08, 0x1C, 0x1C, 0x3E, 0x7F,
	0x14, 0x22, 0x7F, 0x22, 0x14,
	0x5F, 0x5F, 0x00, 0x5F, 0x5F,
	0x06, 0x09, 0x7F, 0x01, 0x7F,
	0x00, 0x66, 0x89, 0x95, 0x6A,
	0x60, 0x60, 0x60, 0x60, 0x60,
	0x94, 0xA2, 0xFF, 0xA2, 0x94,
	0x08, 0x04, 0x7E, 0x04, 0x08,
	0x10, 0x20, 0x7E, 0x20, 0x10,
	0x08, 0x08, 0x2A, 0x1C, 0x08,
	0x08, 0x1C, 0x2A, 0x08, 0x08,
	0x1E, 0x10, 0x10, 0x10, 0x10,
	0x0C, 0x1E, 0x0C, 0x1E, 0x0C,
	0x30, 0x38, 0x3E, 0x38, 0x30,
	0x06, 0x0E, 0x3E, 0x0E, 0x06,
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x5F, 0x00, 0x00,
	0x00, 0x07, 0x00, 0x07, 0x00,
	0x14, 0x7F, 0x14, 0x7F, 0x14,
	0x24, 0x2A, 0x7F, 0x2A, 0x12,
	0x23, 0x13, 0x08, 0x64, 0x62,
	0x36, 0x49, 0x56, 0x20, 0x50,
	0x00, 0x08, 0x07, 0x03, 0x00,
	0x00, 0x1C, 0x22, 0x41, 0x00,
	0x00, 0x41, 0x22, 0x1C, 0x00,
	0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
	0x08, 0x08, 0x3E, 0x08, 0x08,
	0x00, 0x80, 0x70, 0x30, 0x00,
	0x08, 0x08, 0x08, 0x08, 0x08,
	0x00, 0x00, 0x60, 0x60, 0x00,
	0x20, 0x10, 0x08, 0x04, 0x02,
	0x3E, 0x51, 0x49, 0x45, 0x3E,
	0x00, 0x42, 0x7F, 0x40, 0x00,
	0x72, 0x49, 0x49, 0x49, 0x46,
	0x21, 0x41, 0x49, 0x4D, 0x33,
	0x18, 0x14, 0x12, 0x7F, 0x10,
	0x27, 0x45, 0x45, 0x45, 0x39,
	0x3C, 0x4A, 0x49, 0x49, 0x31,
	0x41, 0x21, 0x11, 0x09, 0x07,
	0x36, 0x49, 0x49, 0x49, 0x36,
	0x46, 0x49, 0x49, 0x29, 0x1E,
	0x00, 0x00, 0x14, 0x00, 0x00,
	0x00, 0x40, 0x34, 0x00, 0x00,
	0x00, 0x08, 0x14, 0x22, 0x41,
	0x14, 0x14, 0x14, 0x14, 0x14,
	0x00, 0x41, 0x22, 0x14, 0x08,
	0x02, 0x01, 0x59, 0x09, 0x06,
	0x3E, 0x41, 0x5D, 0x59, 0x4E,
	0x7C, 0x12, 0x11, 0x12, 0x7C,
	0x7F, 0x49, 0x49, 0x49, 0x36,
	0x3E, 0x41, 0x41, 0x41, 0x22,
	0x7F, 0x41, 0x41, 0x41, 0x3E,
	0x7F, 0x49, 0x49, 0x49, 0x41,
	0x7F, 0x09, 0x09, 0x09, 0x01,
	0x3E, 0x41, 0x41, 0x51, 0x73,
	0x7F, 0x08, 0x08, 0x08, 0x7F,
	0x00, 0x41, 0x7F, 0x41, 0x00,
	0x20, 0x40, 0x41, 0x3F, 0x01,
	0x7F, 0x08, 0x14, 0x22, 0x41,
	0x7F, 0x40, 0x40, 0x40, 0x40,
	0x7F, 0x02, 0x1C, 0x02, 0x7F,
	0x7F, 0x04, 0x08, 0x10, 0x7F,
	0x3E, 0x41, 0x41, 0x41, 0x3E,
	0x7F, 0x09, 0x09, 0x09, 0x06,
	0x3E, 0x41, 0x51, 0x21, 0x5E,
	0x7F, 0x09, 0x19, 0x29, 0x46,
	0x26, 0x49, 0x49, 0x49, 0x32,
	0x03, 0x01, 0x7F, 0x01, 0x03,
	0x3F, 0x40, 0x40, 0x40, 0x3F,
	0x1F, 0x20, 0x40, 0x20, 0x1F,
	0x3F, 0x40, 0x38, 0x40, 0x3F,
	0x63, 0x14, 0x08, 0x14, 0x63,
	0x03, 0x04, 0x78, 0x04, 0x03,
	0x61, 0x59, 0x49, 0x4D, 0x43,
	0x00, 0x7F, 0x41, 0x41, 0x41,
	0x02, 0x04, 0x08, 0x10, 0x20,
	0x00, 0x41, 0x41, 0x41, 0x7F,
	0x04, 0x02, 0x01, 0x02, 0x04,
	0x40, 0x40, 0x40, 0x40, 0x40,
	0x00, 0x03, 0x07, 0x08, 0x00,
	0x20, 0x54, 0x54, 0x78, 0x40,
	0x7F, 0x28, 0x44, 0x44, 0x38,
	0x38, 0x44, 0x44, 0x44, 0x28,
	0x38, 0x44, 0x44, 0x28, 0x7F,
	0x38, 0x54, 0x54, 0x54, 0x18,
	0x00, 0x08, 0x7E, 0x09, 0x02,
	0x18, 0xA4, 0xA4, 0x9C, 0x78,
	0x7F, 0x08, 0x04, 0x04, 0x78,
	0x00, 0x44, 0x7D, 0x40, 0x00,
	0x20, 0x40, 0x40, 0x3D, 0x00,
	0x7F, 0x10, 0x28, 0x44, 0x00,
	0x00, 0x41, 0x7F, 0x40, 0x00,
	0x7C, 0x04, 0x78, 0x04, 0x78,
	0x7C, 0x08, 0x04, 0x04, 0x78,
	0x38, 0x44, 0x44, 0x44, 0x38,
	0xFC, 0x18, 0x24, 0x24, 0x18,
	0x18, 0x24, 0x24, 0x18, 0xFC,
	0x7C, 0x08, 0x04, 0x04, 0x08,
	0x48, 0x54, 0x54, 0x54, 0x24,
	0x04, 0x04, 0x3F, 0x44, 0x24,
	0x3C, 0x40, 0x40, 0x20, 0x7C,
	0x1C, 0x20, 0x40, 0x20, 0x1C,
	0x3C, 0x40, 0x30, 0x40, 0x3C,
	0x44, 0x28, 0x10, 0x28, 0x44,
	0x4C, 0x90, 0x90, 0x90, 0x7C,
	0x44, 0x64, 0x54, 0x4C, 0x44,
	0x00, 0x08, 0x36, 0x41, 0x00,
	0x00, 0x00, 0x77, 0x00, 0x00,
	0x00, 0x41, 0x36, 0x08, 0x00,
	0x02, 0x01, 0x02, 0x04, 0x02,
	0x3C, 0x26, 0x23, 0x26, 0x3C,
	0x1E, 0xA1, 0xA1, 0x61, 0x12,
	0x3A, 0x40, 0x40, 0x20, 0x7A,
	0x38, 0x54, 0x54, 0x55, 0x59,
	0x21, 0x55, 0x55, 0x79, 0x41,
	0x21, 0x54, 0x54, 0x78, 0x41,
	0x21, 0x55, 0x54, 0x78, 0x40,
	0x20, 0x54, 0x55, 0x79, 0x40,
	0x0C, 0x1E, 0x52, 0x72, 0x12,
	0x39, 0x55, 0x55, 0x55, 0x59,
	0x39, 0x54, 0x54, 0x54, 0x59,
	0x39, 0x55, 0x54, 0x54, 0x58,
	0x00, 0x00, 0x45, 0x7C, 0x41,
	0x00, 0x02, 0x45, 0x7D, 0x42,
	0x00, 0x01, 0x45, 0x7C, 0x40,
	0xF0, 0x29, 0x24, 0x29, 0xF0,
	0xF0, 0x28, 0x25, 0x28, 0xF0,
	0x7C, 0x54, 0x55, 0x45, 0x00,
	0x20, 0x54, 0x54, 0x7C, 0x54,
	0x7C, 0x0A, 0x09, 0x7F, 0x49,
	0x32, 0x49, 0x49, 0x49, 0x32,
	0x32, 0x48, 0x48, 0x48, 0x32,
	0x32, 0x4A, 0x48, 0x48, 0x30,
	0x3A, 0x41, 0x41, 0x21, 0x7A,
	0x3A, 0x42, 0x40, 0x20, 0x78,
	0x00, 0x9D, 0xA0, 0xA0, 0x7D,
	0x39, 0x44, 0x44, 0x44, 0x39,
	0x3D, 0x40, 0x40, 0x40, 0x3D,
	0x3C, 0x24, 0xFF, 0x24, 0x24,
	0x48, 0x7E, 0x49, 0x43, 0x66,
	0x2B, 0x2F, 0xFC, 0x2F, 0x2B,
	0xFF, 0x09, 0x29, 0xF6, 0x20,
	0xC0, 0x88, 0x7E, 0x09, 0x03,
	0x20, 0x54, 0x54, 0x79, 0x41,
	0x00, 0x00, 0x44, 0x7D, 0x41,
	0x30, 0x48, 0x48, 0x4A, 0x32,
	0x38, 0x40, 0x40, 0x22, 0x7A,
	0x00, 0x7A, 0x0A, 0x0A, 0x72,
	0x7D, 0x0D, 0x19, 0x31, 0x7D,
	0x26, 0x29, 0x29, 0x2F, 0x28,
	0x26, 0x29, 0x29, 0x29, 0x26,
	0x30, 0x48, 0x4D, 0x40, 0x20,
	0x38, 0x08, 0x08, 0x08, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x38,
	0x2F, 0x10, 0xC8, 0xAC, 0xBA,
	0x2F, 0x10, 0x28, 0x34, 0xFA,
	0x00, 0x00, 0x7B, 0x00, 0x00,
	0x08, 0x14, 0x2A, 0x14, 0x22,
	0x22, 0x14, 0x2A, 0x14, 0x08,
	0xAA, 0x00, 0x55, 0x00, 0xAA,
	0xAA, 0x55, 0xAA, 0x55, 0xAA,
	0x00, 0x00, 0x00, 0xFF, 0x00,
	0x10, 0x10, 0x10, 0xFF, 0x00,
	0x14, 0x14, 0x14, 0xFF, 0x00,
	0x10, 0x10, 0xFF, 0x00, 0xFF,
	0x10, 0x10, 0xF0, 0x10, 0xF0,
	0x14, 0x14, 0x14, 0xFC, 0x00,
	0x14, 0x14, 0xF7, 0x00, 0xFF,
	0x00, 0x00, 0xFF, 0x00, 0xFF,
	0x14, 0x14, 0xF4, 0x04, 0xFC,
	0x14, 0x14, 0x17, 0x10, 0x1F,
	0x10, 0x10, 0x1F, 0x10, 0x1F,
	0x14, 0x14, 0x14, 0x1F, 0x00,
	0x10, 0x10, 0x10, 0xF0, 0x00,
	0x00, 0x00, 0x00, 0x1F, 0x10,
	0x10, 0x10, 0x10, 0x1F, 0x10,
	0x10, 0x10, 0x10, 0xF0, 0x10,
	0x00, 0x00, 0x00, 0xFF, 0x10,
	0x10, 0x10, 0x10, 0x10, 0x10,
	0x10, 0x10, 0x10, 0xFF, 0x10,
	0x00, 0x00, 0x00, 0xFF, 0x14,
	0x00, 0x00, 0xFF, 0x00, 0xFF,
	0x00, 0x00, 0x1F, 0x10, 0x17,
	0x00, 0x00, 0xFC, 0x04, 0xF4,
	0x14, 0x14, 0x17, 0x10, 0x17,
	0x14, 0x14, 0xF4, 0x04, 0xF4,
	0x00, 0x00, 0xFF, 0x00, 0xF7,
	0x14, 0x14, 0x14, 0x14, 0x14,
	0x14, 0x14, 0xF7, 0x00, 0xF7,
	0x14, 0x14, 0x14, 0x17, 0x14,
	0x10, 0x10, 0x1F, 0x10, 0x1F,
	0x14, 0x14, 0x14, 0xF4, 0x14,
	0x10, 0x10, 0xF0, 0x10, 0xF0,
	0x00, 0x00, 0x1F, 0x10, 0x1F,
	0x00, 0x00, 0x00, 0x1F, 0x14,
	0x00, 0x00, 0x00, 0xFC, 0x14,
	0x00, 0x00, 0xF0, 0x10, 0xF0,
	0x10, 0x10, 0xFF, 0x10, 0xFF,
	0x14, 0x14, 0x14, 0xFF, 0x14,
	0x10, 0x10, 0x10, 0x1F, 0x00,
	0x00, 0x00, 0x00, 0xF0, 0x10,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xFF, 0xFF, 0xFF, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xFF, 0xFF,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x38, 0x44, 0x44, 0x38, 0x44,
	0x7C, 0x2A, 0x2A, 0x3E, 0x14,
	0x7E, 0x02, 0x02, 0x06, 0x06,
	0x02, 0x7E, 0x02, 0x7E, 0x02,
	0x63, 0x55, 0x49, 0x41, 0x63,
	0x38, 0x44, 0x44, 0x3C, 0x04,
	0x40, 0x7E, 0x20, 0x1E, 0x20,
	0x06, 0x02, 0x7E, 0x02, 0x02,
	0x99, 0xA5, 0xE7, 0xA5, 0x99,
	0x1C, 0x2A, 0x49, 0x2A, 0x1C,
	0x4C, 0x72, 0x01, 0x72, 0x4C,
	0x30, 0x4A, 0x4D, 0x4D, 0x30,
	0x30, 0x48, 0x78, 0x48, 0x30,
	0xBC, 0x62, 0x5A, 0x46, 0x3D,
	0x3E, 0x49, 0x49, 0x49, 0x00,
	0x7E, 0x01, 0x01, 0x01, 0x7E,
	0x2A, 0x2A, 0x2A, 0x2A, 0x2A,
	0x44, 0x44, 0x5F, 0x44, 0x44,
	0x40, 0x51, 0x4A, 0x44, 0x40,
	0x40, 0x44, 0x4A, 0x51, 0x40,
	0x00, 0x00, 0xFF, 0x01, 0x03,
	0xE0, 0x80, 0xFF, 0x00, 0x00,
	0x08, 0x08, 0x6B, 0x6B, 0x08,
	0x36, 0x12, 0x36, 0x24, 0x36,
	0x06, 0x0F, 0x09, 0x0F, 0x06,
	0x00, 0x00, 0x18, 0x18, 0x00,
	0x00, 0x00, 0x10, 0x10, 0x00,
	0x30, 0x40, 0xFF, 0x01, 0x01,
	0x00, 0x1F, 0x01, 0x01, 0x1E,
	0x00, 0x19, 0x1D, 0x17, 0x12,
	0x00, 0x3C, 0x3C, 0x3C, 0x3C,
	0x00, 0x00, 0x00, 0x00, 0x00
};

int cursor_y = 0;
int cursor_x = 0;

#define SSD1306_128_32

#if defined SSD1306_128_64
        #define WIDTH                  128
        #define HEIGHT                 64
#endif
#if defined SSD1306_128_32
        #define WIDTH                  128
        #define HEIGHT                 32
#endif

#define BLACK 0   ///< Draw 'off' pixels
#define WHITE 1   ///< Draw 'on' pixels
#define INVERSE 2 ///< Invert pixels

#define SSD1306_MEMORYMODE 0x20          ///< See datasheet
#define SSD1306_COLUMNADDR 0x21          ///< See datasheet
#define SSD1306_PAGEADDR 0x22            ///< See datasheet
#define SSD1306_SETCONTRAST 0x81         ///< See datasheet
#define SSD1306_CHARGEPUMP 0x8D          ///< See datasheet
#define SSD1306_SEGREMAP 0xA0            ///< See datasheet
#define SSD1306_DISPLAYALLON_RESUME 0xA4 ///< See datasheet
#define SSD1306_DISPLAYALLON 0xA5        ///< Not currently used
#define SSD1306_NORMALDISPLAY 0xA6       ///< See datasheet
#define SSD1306_INVERTDISPLAY 0xA7       ///< See datasheet
#define SSD1306_SETMULTIPLEX 0xA8        ///< See datasheet
#define SSD1306_DISPLAYOFF 0xAE          ///< See datasheet
#define SSD1306_DISPLAYON 0xAF           ///< See datasheet
#define SSD1306_COMSCANINC 0xC0          ///< Not currently used
#define SSD1306_COMSCANDEC 0xC8          ///< See datasheet
#define SSD1306_SETDISPLAYOFFSET 0xD3    ///< See datasheet
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5  ///< See datasheet
#define SSD1306_SETPRECHARGE 0xD9        ///< See datasheet
#define SSD1306_SETCOMPINS 0xDA          ///< See datasheet
#define SSD1306_SETVCOMDETECT 0xDB       ///< See datasheet

#define SSD1306_SETLOWCOLUMN 0x00  ///< Not currently used
#define SSD1306_SETHIGHCOLUMN 0x10 ///< Not currently used
#define SSD1306_SETSTARTLINE 0x40  ///< See datasheet

#define SSD1306_EXTERNALVCC 0x01  ///< External display voltage source
#define SSD1306_SWITCHCAPVCC 0x02 ///< Gen. display voltage from 3.3V

#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26              ///< Init rt scroll
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27               ///< Init left scroll
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29 ///< Init diag scroll
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A  ///< Init diag scroll
#define SSD1306_DEACTIVATE_SCROLL 0x2E                    ///< Stop scroll
#define SSD1306_ACTIVATE_SCROLL 0x2F                      ///< Start scroll
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3             ///< Set scroll range

#define SSD1306_BLACK 0   ///< Draw 'off' pixels
#define SSD1306_WHITE 1   ///< Draw 'on' pixels
#define SSD1306_INVERSE 2 ///< Invert pixels

unsigned int *frame_buffer;

extern void install_interrupt(CharDevice *device, RingBuffer *uart_a, RingBuffer *uart_b);
extern void remove_interrupt();

static RingBuffer uart_a;
static RingBuffer uart_b;

#define SSD1306_128_32

void ssd1306_begin(CharDevice *uart, unsigned int i2caddr)
{
	// I2C Init

	// Init sequence
	i2c_write_2(uart, i2caddr, 0x00, SSD1306_DISPLAYOFF);	// 0xAE
	i2c_write_2(uart, i2caddr, 0x00, SSD1306_SETDISPLAYCLOCKDIV);	// 0xD5
	i2c_write_2(uart, i2caddr, 0x00, 0x80);	// the suggested ratio 0x80

	i2c_write_2(uart, i2caddr, 0x00, SSD1306_SETMULTIPLEX);	// 0xA8
	i2c_write_2(uart, i2caddr, 0x00, HEIGHT - 1);

	i2c_write_2(uart, i2caddr, 0x00, SSD1306_SETDISPLAYOFFSET);	// 0xD3
	i2c_write_2(uart, i2caddr, 0x00, 0x0);	// no offset
	i2c_write_2(uart, i2caddr, 0x00, SSD1306_SETSTARTLINE | 0x0);	// line #0
	i2c_write_2(uart, i2caddr, 0x00, SSD1306_CHARGEPUMP);	// 0x8D
	i2c_write_2(uart, i2caddr, 0x00, 0x14);

	i2c_write_2(uart, i2caddr, 0x00, SSD1306_MEMORYMODE);	// 0x20
	i2c_write_2(uart, i2caddr, 0x00, 0x00);	// 0x0 act like ks0108
	i2c_write_2(uart, i2caddr, 0x00, SSD1306_SEGREMAP | 0x1);
	i2c_write_2(uart, i2caddr, 0x00, SSD1306_COMSCANDEC);

	#if defined SSD1306_128_32
	i2c_write_2(uart, i2caddr, 0x00, SSD1306_SETCOMPINS);	// 0xDA
	i2c_write_2(uart, i2caddr, 0x00, 0x02);
	i2c_write_2(uart, i2caddr, 0x00, SSD1306_SETCONTRAST);	// 0x81
	i2c_write_2(uart, i2caddr, 0x00, 0x8F);
	#elif defined SSD1306_128_64
	i2c_write_2(uart, i2caddr, 0x00, SSD1306_SETCOMPINS);	// 0xDA
	i2c_write_2(uart, i2caddr, 0x00, 0x12);
	i2c_write_2(uart, i2caddr, 0x00, SSD1306_SETCONTRAST);	// 0x81
	if (vccstate == SSD1306_EXTERNALVCC) {
		i2c_write_2(uart, i2caddr, 0x00, 0x9F);
	} else {
		i2c_write_2(uart, i2caddr, 0x00, 0xCF);
	}	
	#endif

	i2c_write_2(uart, i2caddr, 0x00, SSD1306_SETPRECHARGE);	// 0xd9

		i2c_write_2(uart, i2caddr, 0x00, 0xF1);

	i2c_write_2(uart, i2caddr, 0x00, SSD1306_SETVCOMDETECT);	// 0xDB
	i2c_write_2(uart, i2caddr, 0x00, 0x40);
	i2c_write_2(uart, i2caddr, 0x00, SSD1306_DISPLAYALLON_RESUME);	// 0xA4
	i2c_write_2(uart, i2caddr, 0x00, SSD1306_NORMALDISPLAY);	// 0xA6

	i2c_write_2(uart, i2caddr, 0x00, SSD1306_DEACTIVATE_SCROLL);

	i2c_write_2(uart, i2caddr, 0x00, SSD1306_DISPLAYON);	// --turn on oled panel
}

void ssd1306_drawPixel(int x, int y, unsigned int color)
{
	if ((x < 0) || (x >= WIDTH) || (y < 0) || (y >= HEIGHT))
		return;

	// x is which column
	switch (color) {
	case WHITE:
		frame_buffer[x + (y / 8) * WIDTH] |= (1 << (y & 7));
		break;
	case BLACK:
		frame_buffer[x + (y / 8) * WIDTH] &= ~(1 << (y & 7));
		break;
	case INVERSE:
		frame_buffer[x + (y / 8) * WIDTH] ^= (1 << (y & 7));
		break;
	}
}


void ssd1306_clearDisplay(void)
{
	memset(frame_buffer, 0,
	       (WIDTH * HEIGHT / 8) * sizeof(int));
	cursor_y = 0;
	cursor_x = 0;
}

void ssd1306_drawFastHLineInternal(int x, int y, int w, unsigned int color)
{
	// Do bounds/limit checks
	if (y < 0 || y >= HEIGHT) {
		return;
	}
	// make sure we don't try to draw below 0
	if (x < 0) {
		w += x;
		x = 0;
	}
	// make sure we don't go off the edge of the display
	if ((x + w) > WIDTH) {
		w = (WIDTH - x);
	}
	// if our width is now negative, punt
	if (w <= 0) {
		return;
	}
	// set up the pointer for movement through the frame_buffer
	unsigned int *pBuf = frame_buffer;
	// adjust the frame_buffer pointer for the current row
	pBuf += ((y / 8) * WIDTH);
	// and offset x columns in
	pBuf += x;

	unsigned int mask = 1 << (y & 7);

	switch (color) {
	case WHITE:
		while (w--) {
			*pBuf++ |= mask;
		};
		break;
	case BLACK:
		mask = ~mask;
		while (w--) {
			*pBuf++ &= mask;
		};
		break;
	case INVERSE:
		while (w--) {
			*pBuf++ ^= mask;
		};
		break;
	}
}

void ssd1306_drawFastVLineInternal(int x, int __y, int __h, unsigned int color)
{

	// do nothing if we're off the left or right side of the screen
	if (x < 0 || x >= WIDTH) {
		return;
	}
	// make sure we don't try to draw below 0
	if (__y < 0) {
		// __y is negative, this will subtract enough from __h to account
		// for __y being 0
		__h += __y;
		__y = 0;

	}
	// make sure we don't go past the height of the display
	if ((__y + __h) > HEIGHT) {
		__h = (HEIGHT - __y);
	}
	// if our height is now negative, punt
	if (__h <= 0) {
		return;
	}
	// this display doesn't need ints for coordinates, use local byte
	// registers for faster juggling
	unsigned int y = __y;
	unsigned int h = __h;

	// set up the pointer for fast movement through the frame_buffer
	unsigned int *pBuf = frame_buffer;
	// adjust the frame_buffer pointer for the current row
	pBuf += ((y / 8) * WIDTH);
	// and offset x columns in
	pBuf += x;

	// do the first partial byte, if necessary - this requires some
	// masking
	unsigned int mod = (y & 7);
	if (mod) {
		// mask off the high n bits we want to set
		mod = 8 - mod;

		// note - lookup table results in a nearly 10% performance
		// improvement in fill* functions
		// register unsigned int mask = ~(0xFF >> (mod));
		static unsigned int premask[8] =
		    { 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE };
		unsigned int mask = premask[mod];

		// adjust the mask if we're not going to reach the end of this
		// byte
		if (h < mod) {
			mask &= (0XFF >> (mod - h));
		}

		switch (color) {
		case WHITE:
			*pBuf |= mask;
			break;
		case BLACK:
			*pBuf &= ~mask;
			break;
		case INVERSE:
			*pBuf ^= mask;
			break;
		}

		// fast exit if we're done here!
		if (h < mod) {
			return;
		}

		h -= mod;

		pBuf += WIDTH;
	}
	// write solid bytes while we can - effectively doing 8 rows at a time
	if (h >= 8) {
		if (color == INVERSE) {	// separate copy of the code so we don't
			// impact performance of the black/white
			// write version with an extra comparison
			// per loop
			do {
				*pBuf = ~(*pBuf);

				// adjust the frame_buffer forward 8 rows worth of data
				pBuf += WIDTH;

				// adjust h & y (there's got to be a faster way for me to
				// do this, but this should still help a fair bit for now)
				h -= 8;
			}
			while (h >= 8);
		} else {
			// store a local value to work with
			register unsigned int val = (color == WHITE) ? 255 : 0;

			do {
				// write our value in
				*pBuf = val;

				// adjust the frame_buffer forward 8 rows worth of data
				pBuf += WIDTH;

				// adjust h & y (there's got to be a faster way for me to
				// do this, but this should still help a fair bit for now)
				h -= 8;
			}
			while (h >= 8);
		}
	}
	// now do the final partial byte, if necessary
	if (h) {
		mod = h & 7;
		// this time we want to mask the low bits of the byte, vs the high 
		// bits we did above
		// register unsigned int mask = (1 << mod) - 1;
		// note - lookup table results in a nearly 10% performance
		// improvement in fill* functions
		static unsigned int postmask[8] =
		    { 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F };
		unsigned int mask = postmask[mod];
		switch (color) {
		case WHITE:
			*pBuf |= mask;
			break;
		case BLACK:
			*pBuf &= ~mask;
			break;
		case INVERSE:
			*pBuf ^= mask;
			break;
		}
	}
}

void ssd1306_drawFastHLine(int x, int y, int w, unsigned int color)
{

		ssd1306_drawFastHLineInternal(x, y, w, color);
}

void ssd1306_drawFastVLine(int x, int y, int h, unsigned int color)
{

		ssd1306_drawFastVLineInternal(x, y, h, color);
}

void ssd1306_fillRect(int x, int y, int w, int h, int fillcolor)
{

	// Bounds check
	if ((x >= WIDTH) || (y >= HEIGHT))
		return;

	// Y bounds check
	if (y + h > HEIGHT) {
		h = HEIGHT - y - 1;
	}
	// X bounds check
	if (x + w > WIDTH) {
		w = WIDTH - x - 1;
	}

	int i;
	for (i = 0; i < h; i++)
		ssd1306_drawFastHLine(x, y + i, w, fillcolor);
}

void ssd1306_drawChar(int x, int y, unsigned char c, int color, int size)
{

	if ((x >= WIDTH) ||	// Clip right
	    (y >= HEIGHT) ||	// Clip bottom
	    ((x + 6 * size - 1) < 0) ||	// Clip left
	    ((y + 8 * size - 1) < 0))	// Clip top
		return;
	int i;
	int j;
	for (i = 0; i < 6; i++) {
		int line;
		if (i == 5)
			line = 0x0;
		else
			line = pgm_read_byte(font + (c * 5) + i);
		for (j = 0; j < 8; j++) {
			if (line & 0x1) {
				if (size == 1)	// default size
					ssd1306_drawPixel(x + i, y + j, color);
				else {	// big size
					ssd1306_fillRect(x + (i * size),
							 y + (j * size), size,
							 size, color);
				}
			}
			line >>= 1;
		}
	}
}

//https://github.com/iliapenev/ssd1306_i2c/blob/master/ssd1306_i2c.c

int textsize = 1;
int wrap = 1;

void ssd1306_setTextSize(int s)
{
	textsize = (s > 0) ? s : 1;
}

uint16_t ssd1306_stringwidth(char *str) {

	int l = strlen(str);

	return (5 * l);

}

void ssd1306_write(int c)
{

	if (c == '\n') {
		cursor_y += textsize * 8;
		cursor_x = 0;
	} else if (c == '\r') {
		// skip em
	} else {
		ssd1306_drawChar(cursor_x, cursor_y, c, WHITE, textsize);
		cursor_x += textsize * 6;
		if (wrap && (cursor_x > (WIDTH - textsize * 6))) {
			cursor_y += textsize * 8;
			cursor_x = 0;
		}
	}
}

void ssd1306_drawString_xy(char *str, uint16_t x, uint16_t y)
{
	(void)x;
	(void)y;
	cursor_x = x;
	cursor_y = y;
	int i, end;
	end = strlen(str);
	for (i = 0; i < end; i++)
		ssd1306_write(str[i]);
}

void ssd1306_drawString_centre(char *str, uint16_t y) {

	uint16_t l = ssd1306_stringwidth(str);
	if (l > WIDTH) return;
	ssd1306_drawString_xy(str, (WIDTH - ssd1306_stringwidth(str)) / 2, y);

}

void ssd1306_drawString(char *str)
{
	int i, end;
	end = strlen(str);
	for (i = 0; i < end; i++)
		ssd1306_write(str[i]);
}

void drawIco16x16(int16_t xMove, int16_t yMove, const uint8_t *ico, bool inverse) {
  uint16_t data;

  for(int16_t y = 0; y < 16; y++) {
    data = pgm_read_byte(ico + (y << 1)) + (pgm_read_byte(ico + (y << 1) + 1) << 8);
    for(int16_t x = 0; x < 16; x++ ) {
      if ((data & 0x01) ^ inverse) {
        ssd1306_drawPixel(xMove + x, yMove + y, WHITE);
      } else {
        ssd1306_drawPixel(xMove + x, yMove + y, BLACK);
      }
      data >>= 1; // Move a bit
    }
  }
}

void drawIco8x8(int16_t xMove, int16_t yMove, const uint8_t *ico, bool inverse) {
  uint16_t data;

  for(int16_t y = 0; y < 8; y++) {
    data = pgm_read_byte(ico + (y << 1)) + (pgm_read_byte(ico + (y << 1) + 1) << 8);
    for(int16_t x = 0; x < 8; x++ ) {
      if ((data & 0x01) ^ inverse) {
        ssd1306_drawPixel(xMove + x, yMove + y, WHITE);
      } else {
        ssd1306_drawPixel(xMove + x, yMove + y, BLACK);
      }
      data >>= 1; // Move a bit
    }
  }
}

void drawIco(int16_t width, int16_t height, int16_t xMove, int16_t yMove, const uint8_t *ico, bool inverse) {
  uint16_t data;

  for(int16_t y = 0; y < height; y++) {
    data = pgm_read_byte(ico + (y << 1)) + (pgm_read_byte(ico + (y << 1) + 1) << 8);
    for(int16_t x = 0; x < width; x++ ) {
      if ((data & 0x01) ^ inverse) {
        ssd1306_drawPixel(xMove + x, yMove + y, WHITE);
      } else {
        ssd1306_drawPixel(xMove + x, yMove + y, BLACK);
      }
      data >>= 1; // Move a bit
    }
  }
}

void ssd1306_display(CharDevice *uart, uint8_t i2caddr)
{
    (void)uart;

	i2c_write_2(uart, 0x3C, 0x00, SSD1306_COLUMNADDR);
	i2c_write_2(uart, 0x3C, 0x00,  0);	// Column start address (0 = reset)
	i2c_write_2(uart, 0x3C, 0x00,  WIDTH - 1);	// Column end address (127 
	// = reset)

	i2c_write_2(uart, 0x3C, 0x00,  SSD1306_PAGEADDR);
	i2c_write_2(uart, 0x3C, 0x00,  0);	// Page start address (0 = reset)
	i2c_write_2(uart, 0x3C, 0x00,  7);	// Page end address

	for (int i = 0; i < (WIDTH * HEIGHT / 8) -1; i += 3) {

        i2c_write_4(uart, i2caddr, 0x40, frame_buffer[i], frame_buffer[i + 1], frame_buffer[i + 2]);

	}


}


void fill(uint8_t fill) {

    memset(frame_buffer, fill, WIDTH * ((HEIGHT + 7) / 8));
    
}

uint16_t gb_x = 5;
uint16_t gb_y = 5;

// static unsigned char wifi[] = {0x80, 0xA0, 0xA8, 0xAB, 0xAB, 0xA8, 0xA0, 0x80 };

// static unsigned char usb_16[] = {
//    0x40, 0x00, 0x60, 0x00, 0xe0, 0x00, 0xf0, 0x1c, 0x40, 0x1c, 0x40, 0x1c,
//    0x42, 0x0c, 0x47, 0x04, 0x47, 0x07, 0xc6, 0x03, 0x46, 0x00, 0x4c, 0x00,
//    0x7c, 0x00, 0x60, 0x00, 0x40, 0x00, 0x40, 0x00 };

//char text[] = "Hello!";

extern void install_interrupt(CharDevice *device, RingBuffer *uart_a, RingBuffer *uart_b);
extern void remove_interrupt();



static RingBuffer uart_b;

// extern AT_packet at;

int main(int argc, char **argv) {

    frame_buffer = (unsigned int *)malloc(WIDTH * ((HEIGHT + 7) / 8));

    (void)argc;
    (void)argv;

    printf("\033*");
    printf("\f");

    // set up ring buffers
    uart_a.mask = 0x3ff;
    uart_b.mask = 0x3ff;

	//static RingBuffer uart_a;

    CharDevice duart_a;
    CharDevice duart_b;
    mcGetDevice(0, &duart_a);
    mcGetDevice(1, &duart_b);
	
    install_interrupt(&duart_b, NULL, &uart_b);

    if (mcGetDevice(0, &duart_a)) fctprintf(mcSendDevice, &duart_a, "\f");
    
    if (mcGetDevice(1, &duart_b)) fctprintf(mcSendDevice, &duart_b, "\r");
    
    if (mcGetDevice(1, &duart_b)) fctprintf(mcSendDevice, &duart_b, "AT+RST\r");
    

    // State stateA;
    // stateA.state = STATE_DISCARD;
    // stateA.ringBuffer = &uart_a;

    State_esp stateB;
    stateB.state = STATE_DISCARD;
    stateB.ringBuffer = &uart_b;

	fctprintf(mcSendDevice, &duart_a, "Pre loop\n");

    while (true) {            
        
        if (mcGetDevice(0, &duart_a) && (mcCheckDevice(&duart_a))) {
            //unsigned char cmd_list[] = {0x00, 0x8D, 0x14, 0xA1, 0xC8, 0xAF};
            uint8_t c = mcReadDevice(&duart_a);
			// fctprintf(mcSendDevice, &duart_a, "I have char %c\n", c);
            switch(c) {

                 case '/':
                     fctprintf(mcSendDevice, &duart_b, "AT+RST\r");
                     break;

                case 'o':
                    i2c_setup(&duart_b, 0, 9, 2, 5000);

                //     ssd1306_begin(&duart_b, 0x3C);
                     break;
                
				case 's':
					i2c_read(&duart_b, 0x68, 0x0f, 1);
					//ssd1306_drawString_centre(at.data, (HEIGHT / 2));
					//ssd1306_display(&duart_b, 0x3C);
					break;

                // // case ']':
                // //     fill(0x00);
                // //     ssd1306_display();
                // //     break;
                
                // case '[':
                //     ssd1306_clearDisplay();
                //     ssd1306_display(&duart_b, 0x3C);
                //     break;
                
                // case '`':
                //     // draw_pixel(gb_x, gb_y, 1);
                //     // gb_x += 5; gb_y += 5;
                //     // draw(&duart_b);
                //     break;       
                
                // case 'p':
                //     drawIco16x16(0,0,usb_16,false);
				// 	ssd1306_display(&duart_b, 0x3C);
                //     break; 
                
                // case 'c':
	            //     //ssd1306_setTextSize(3);
                //     //ssd1306_drawString(text);
				// 	ssd1306_drawString_centre(text, (HEIGHT / 2));
                //     ssd1306_display(&duart_b, 0x3C);
					
                //     break;                   

                default:
                    fctprintf(mcSendDevice, &duart_b, "%c", c);
					fctprintf(mcSendDevice, &duart_a, "%c", c);
					if (c == '\r') fctprintf(mcSendDevice, &duart_a, "%c", '\n');
                    break;
                
            }
                
        }

        process_incoming_esp(&stateB);
        
    }
}
