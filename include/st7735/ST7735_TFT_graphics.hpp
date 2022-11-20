/*
 * Project Name: ST7735_TFT_PICO
 * File: ST7735_TFT_graphics.hpp
 * Description: library header file
 * Author: Gavin Lyons.
 * Description: See URL for full details.
 * URL: https://github.com/gavinlyonsrepo/ST7735_TFT_PICO
 */

#ifndef _st7735_tft_graph_h
#define _st7735_tft_graph_h

// Section: Includes 
#include <cstring> //strlen
#include <cstdio> 
#include <cstdlib>
#include "hardware/spi.h"
#include "ST7735_TFT_Print.hpp" 

// Section defines 

#define _swap_TFT(a, b) { int16_t t; t = a; a = b; b = t;}

// Section: Enums 
typedef enum 
{
	TFTFont_Default = 1,
	TFTFont_Thick = 2,
	TFTFont_Seven_Seg = 3,
	TFTFont_Wide = 4,
	TFTFont_Tiny = 5,
	TFTFont_HomeSpun = 6,
	TFTFont_Bignum = 7,
	TFTFont_Mednum = 8,
}TFT_FONT_TYPE_e; // Font type 1-8

typedef enum 
{
	TFTFont_width_3 = 3, 
	TFTFont_width_5 = 5, 
	TFTFont_width_7 = 7, 
	TFTFont_width_4 = 4, 
	TFTFont_width_8 = 8,
	TFTFont_width_16= 16
}TFT_Font_width_e; // width of the font in bytes, cols.

typedef enum 
{
	TFTFont_offset_none = 0x00, // extended ASCII
	TFTFont_offset_space = 0x20,  // Starts at Space
	TFTFont_offset_zero = 0x30,  //Starts at zero
}TFT_Font_offset_e; // font offset in the ASCII table

typedef enum 
{
	TFTFont_height_8 = 8, TFTFont_height_16 = 16, TFTFont_height_32 = 32
}TFT_Font_height_e; // height of the font in bits


// Section: Classes

// Class to handle fonts and graphics of ST7735 display
class ST7735_TFT_graphics : public Print {

 public:

	ST7735_TFT_graphics(); // Constructor
	~ST7735_TFT_graphics(){};
	
	virtual size_t write(uint8_t);
	void TFTsetAddrWindow(uint8_t, uint8_t, uint8_t, uint8_t);
	void TFTfillScreen(uint16_t color);
	void TFTsetCursor(int16_t x, int16_t y);
	
	// Shapes and lines
	void TFTdrawPixel(uint8_t, uint8_t, uint16_t);
	void TFTdrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
	void TFTdrawFastVLine(uint8_t x, uint8_t y, uint8_t h, uint16_t color);
	void TFTdrawFastHLine(uint8_t x, uint8_t y, uint8_t w, uint16_t color);

	void TFTdrawRectWH(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color);
	void TFTfillRectangle(uint8_t, uint8_t, uint8_t, uint8_t, uint16_t);
	void TFTfillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color);

	void TFTdrawRoundRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t r, uint16_t color);
	void TFTfillRoundRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t r, uint16_t color);
	
	void TFTdrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
	void TFTfillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

	void TFTdrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
	void TFTfillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

	// Text
	void TFTsetTextWrap(bool w);
	void TFTFontNum(TFT_FONT_TYPE_e FontNumber);
	void TFTdrawChar(uint8_t x, uint8_t y, uint8_t c, uint16_t color, uint16_t bg, uint8_t size);
	void TFTdrawText(uint8_t x, uint8_t y, char *_text, uint16_t color, uint16_t bg, uint8_t size);
	void TFTdrawCharNumFont(uint8_t x, uint8_t y, uint8_t c, uint16_t color ,uint16_t bg);
	void TFTdrawTextNumFont(uint8_t x, uint8_t y, char *pText, uint16_t color, uint16_t bg);
	void setTextColor(uint16_t c);
	void setTextColor(uint16_t c, uint16_t bg);
	void setTextSize(uint8_t s);
	
	// Bitmap & Icon
	void TFTdrawIcon(uint8_t x, uint8_t y, uint8_t w, uint16_t color, uint16_t bgcolor, const unsigned char character[]);
	void TFTdrawBitmap(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color, uint16_t bgcolor, uint8_t *pBmp);
	void TFTdrawBitmap24(uint8_t x, uint8_t y, uint8_t *pBmp, uint8_t w, uint8_t h);
	void TFTdrawBitmap24Data(uint8_t x, uint8_t y, uint8_t *pBmp, uint8_t w, uint8_t h);
	void TFTdrawBitmap16(uint8_t x, uint8_t y, uint8_t *pBmp, uint8_t w, uint8_t h);
	void TFTdrawBitmap16Data(uint8_t x, uint8_t y, uint8_t *pBmp, uint8_t w, uint8_t h);
	
protected:

	void pushColor(uint16_t color);
	uint16_t Color565(uint16_t ,uint16_t , uint16_t );
	void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
	void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);

	void writeCommand(uint8_t);
	void writeData(uint8_t);
	void spiWrite(uint8_t);
	void spiWriteSoftware(uint8_t spidata);
	void spiWriteDataBuffer(uint8_t* spidata, uint32_t len);
	
	
	TFT_FONT_TYPE_e FontNum;
	uint8_t _FontNumber = TFTFont_Default;
	uint8_t _CurrentFontWidth = TFTFont_width_5;
	uint8_t _CurrentFontoffset = TFTFont_offset_none;
	uint8_t _CurrentFontheight = TFTFont_height_8;
	bool _wrap = true;
	uint16_t _textcolor =0xFFFF ;
	uint16_t _textbgcolor =0x0000 ; //background color
	uint8_t _textSize = 1;
	
	uint8_t _currentMode = 0; //TFT mode 
	int16_t _cursorX = 0; 
	int16_t _cursorY = 0;
	
	uint8_t _colstart; 
	uint8_t  _rowstart;
	uint8_t _XStart; 
	uint8_t _YStart;
	
	uint16_t _widthTFT;
	uint16_t _heightTFT;
	uint16_t _widthStartTFT; //  never change after first init
	uint16_t _heightStartTFT; // never change after first init
	
	int8_t _TFT_DC;
	int8_t _TFT_RST;
	int8_t _TFT_CS;    
	int8_t _TFT_SCLK; 
	int8_t _TFT_SDATA;  

	bool _hardwareSPI;
	spi_inst_t *_pspiInterface;
	uint16_t _speedSPIKHz;

};

#endif // file header guard

// ********************** EOF *********************
