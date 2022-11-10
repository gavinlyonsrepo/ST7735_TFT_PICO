/*
 * Project Name: ST7735_TFT_PICO
 * Description: library source file
 * Author: Gavin Lyons.
 * Description: See URL for full details.
 * URL: https://github.com/gavinlyonsrepo/ST7735_TFT_PICO
 */

#include "../include/st7735/ST7735_TFT_graphics.hpp"
#include "../include/st7735/ST7735_TFT.hpp"
#include "../include/st7735/ST7735_TFT_Font.hpp"   

ST7735_TFT_graphics::ST7735_TFT_graphics()
{
}

//Desc: Draw a pixel to screen
//Param1: X co-ord
//Param2 Y  co-ord
//Param3 color 565 16-bit

void ST7735_TFT_graphics ::TFTdrawPixel(uint8_t x, uint8_t y, uint16_t color) {
	if ((x >= _widthTFT) || (y >= _heightTFT))
		return;
	TFTsetAddrWindow(x, y, x + 1, y + 1);
	writeData(color >> 8);
	writeData(color & 0xFF);
}

/*
  Desc SPI displays set an address window rectangle for blitting pixels
  Param1:  Top left corner x coordinate
  Param2:  y  Top left corner x coordinate
  Param3:  w  Width of window
  Param4:  h  Height of window
 https://en.wikipedia.org/wiki/Bit_blit
 */
void ST7735_TFT_graphics ::TFTsetAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	writeCommand(ST7735_CASET);
	writeData(0);
	writeData(x0 + _XStart);
	writeData(0);
	writeData(x1 + _XStart);
	writeCommand(ST7735_RASET);
	writeData(0);
	writeData(y0 +_YStart);
	writeData(0);
	writeData(y1 +_YStart);
	writeCommand(ST7735_RAMWR); // Write to RAM
}

// Desc: fills a rectangle starting from coordinates (x,y) with width of w and height of h.
// Note :: uses spiWriteBuffer method
void ST7735_TFT_graphics ::TFTfillRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color) {
	uint8_t hi, lo;

	// Check bounds
	if ((x >= _widthTFT) || (y >= _heightTFT)) return;
	if ((x + w - 1) >= _widthTFT) w = _widthTFT - x;
	if ((y + h - 1) >= _heightTFT) h = _heightTFT - y;
	
	// Colour to bytes
	hi = color >> 8;
	lo = color;

	// Create bitmap buffer
	uint8_t* buffer = (uint8_t*)malloc(w*h*sizeof(uint16_t));
	for(uint32_t i = 0; i<w*h*sizeof(uint16_t);) {
		buffer[i++] = hi;
		buffer[i++] = lo;
	}

	// Set window and write buffer
	TFTsetAddrWindow(x, y, x + w - 1, y + h - 1);
	TFT_DC_SetHigh;
	TFT_CS_SetLow;
	spiWriteBuffer(buffer, h*w*sizeof(uint16_t));
	TFT_CS_SetHigh;

	free(buffer);
}

// Desc: Fills the whole screen with a given color.

void ST7735_TFT_graphics ::TFTfillScreen(uint16_t color) {
	TFTfillRectangle(0, 0, _widthTFT, _heightTFT, color);
}

// Desc: Draws a vertical line starting at (x,y) with height h.

void ST7735_TFT_graphics ::TFTdrawFastVLine(uint8_t x, uint8_t y, uint8_t h, uint16_t color) {
	uint8_t hi, lo;
	if ((x >= _widthTFT) || (y >= _heightTFT))
		return;
	if ((y + h - 1) >= _heightTFT)
		h = _heightTFT - y;
	hi = color >> 8;
	lo = color;
	TFTsetAddrWindow(x, y, x, y + h - 1);
	TFT_DC_SetHigh;

	TFT_CS_SetLow;
	while (h--) {
		spiWrite(hi);
		spiWrite(lo);
	}
	TFT_CS_SetHigh;
}

// Desc: Draws a horizontal line starting at (x,y) with width w.

void ST7735_TFT_graphics ::TFTdrawFastHLine(uint8_t x, uint8_t y, uint8_t w, uint16_t color) {
	uint8_t hi, lo;
	if ((x >= _widthTFT) || (y >= _heightTFT))
		return;
	if ((x + w - 1) >= _widthTFT)
		w = _widthTFT - x;
	hi = color >> 8;
	lo = color;
	TFTsetAddrWindow(x, y, x + w - 1, y);
	TFT_DC_SetHigh;
	TFT_CS_SetLow;
	while (w--) {
		spiWrite(hi);
		spiWrite(lo);
	}
	TFT_CS_SetHigh;
}

// Desc: draws a circle where (x0,y0) are center coordinates an r is circle radius.

void ST7735_TFT_graphics ::TFTdrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
	int16_t f, ddF_x, ddF_y, x, y;
	f = 1 - r, ddF_x = 1, ddF_y = -2 * r, x = 0, y = r;
	TFTdrawPixel(x0, y0 + r, color);
	TFTdrawPixel(x0, y0 - r, color);
	TFTdrawPixel(x0 + r, y0, color);
	TFTdrawPixel(x0 - r, y0, color);
	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		TFTdrawPixel(x0 + x, y0 + y, color);
		TFTdrawPixel(x0 - x, y0 + y, color);
		TFTdrawPixel(x0 + x, y0 - y, color);
		TFTdrawPixel(x0 - x, y0 - y, color);
		TFTdrawPixel(x0 + y, y0 + x, color);
		TFTdrawPixel(x0 - y, y0 + x, color);
		TFTdrawPixel(x0 + y, y0 - x, color);
		TFTdrawPixel(x0 - y, y0 - x, color);
	}
}

// Desc : used internally by TFTdrawRoundRect

void ST7735_TFT_graphics ::drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color) {
	int16_t f, ddF_x, ddF_y, x, y;
	f = 1 - r, ddF_x = 1, ddF_y = -2 * r, x = 0, y = r;
	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		if (cornername & 0x4) {
			TFTdrawPixel(x0 + x, y0 + y, color);
			TFTdrawPixel(x0 + y, y0 + x, color);
		}
		if (cornername & 0x2) {
			TFTdrawPixel(x0 + x, y0 - y, color);
			TFTdrawPixel(x0 + y, y0 - x, color);
		}
		if (cornername & 0x8) {
			TFTdrawPixel(x0 - y, y0 + x, color);
			TFTdrawPixel(x0 - x, y0 + y, color);
		}
		if (cornername & 0x1) {
			TFTdrawPixel(x0 - y, y0 - x, color);
			TFTdrawPixel(x0 - x, y0 - y, color);
		}
	}
}

// Desc : used internally by fill circle TFTfillRoundRect and fillcircle

void ST7735_TFT_graphics ::fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color) {
	int16_t f, ddF_x, ddF_y, x, y;
	f = 1 - r, ddF_x = 1, ddF_y = -2 * r, x = 0, y = r;
	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		if (cornername & 0x1) {
			TFTdrawFastVLine(x0 + x, y0 - y, 2 * y + 1 + delta, color);
			TFTdrawFastVLine(x0 + y, y0 - x, 2 * x + 1 + delta, color);
		}
		if (cornername & 0x2) {
			TFTdrawFastVLine(x0 - x, y0 - y, 2 * y + 1 + delta, color);
			TFTdrawFastVLine(x0 - y, y0 - x, 2 * x + 1 + delta, color);
		}
	}
}

// Desc: fills a circle where (x0,y0) are center coordinates an r is circle radius.

void ST7735_TFT_graphics ::TFTfillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
	TFTdrawFastVLine(x0, y0 - r, 2 * r + 1, color);
	fillCircleHelper(x0, y0, r, 3, 0, color);
}

// Desc: draws rectangle at (x,y) where h is height and w is width of the rectangle.

void ST7735_TFT_graphics ::TFTdrawRectWH(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color) {
	TFTdrawFastHLine(x, y, w, color);
	TFTdrawFastHLine(x, y + h - 1, w, color);
	TFTdrawFastVLine(x, y, h, color);
	TFTdrawFastVLine(x + w - 1, y, h, color);
}

// Desc : draws a line from (x0,y0) to (x1,y1).

void ST7735_TFT_graphics ::TFTdrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
	int16_t steep, dx, dy, err, ystep;
	steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		_swap_TFT(x0, y0);
		_swap_TFT(x1, y1);
	}
	if (x0 > x1) {
		_swap_TFT(x0, x1);
		_swap_TFT(y0, y1);
	}
	dx = x1 - x0;
	dy = abs(y1 - y0);

	err = dx / 2;
	if (y0 < y1) {
		ystep = 1;
	} else {
		ystep = -1;
	}

	for (; x0 <= x1; x0++) {
		if (steep) {
			TFTdrawPixel(y0, x0, color);
		} else {
			TFTdrawPixel(x0, y0, color);
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
}

// Desc : fills a rectangle starting from coordinates (x,y) with width of w and height of h.

void ST7735_TFT_graphics ::TFTfillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color) {
	int16_t i;
	for (i = x; i < x + w; i++) {
		TFTdrawFastVLine(i, y, h, color);
	}
}

// Desc: draws a rectangle with rounded edges. h: height, w:width, r: radius of the rounded edges.

void ST7735_TFT_graphics ::TFTdrawRoundRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t r, uint16_t color) {
	TFTdrawFastHLine(x + r, y, w - 2 * r, color);
	TFTdrawFastHLine(x + r, y + h - 1, w - 2 * r, color);
	TFTdrawFastVLine(x, y + r, h - 2 * r, color);
	TFTdrawFastVLine(x + w - 1, y + r, h - 2 * r, color);
	drawCircleHelper(x + r, y + r, r, 1, color);
	drawCircleHelper(x + w - r - 1, y + r, r, 2, color);
	drawCircleHelper(x + w - r - 1, y + h - r - 1, r, 4, color);
	drawCircleHelper(x + r, y + h - r - 1, r, 8, color);
}

// Desc: draws a filled rectangle with rounded edges. h: height, w:width, r: radius of the rounded edges.

void ST7735_TFT_graphics ::TFTfillRoundRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t r, uint16_t color) {
	TFTfillRect(x + r, y, w - 2 * r, h, color);
	fillCircleHelper(x + w - r - 1, y + r, r, 1, h - 2 * r - 1, color);
	fillCircleHelper(x + r, y + r, r, 2, h - 2 * r - 1, color);
}


// Desc: draws a triangle of coordinates (x0,y0), (x1,y1) and (x2,y2).

void ST7735_TFT_graphics ::TFTdrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
	TFTdrawLine(x0, y0, x1, y1, color);
	TFTdrawLine(x1, y1, x2, y2, color);
	TFTdrawLine(x2, y2, x0, y0, color);
}

// Desc: draws a filled triangle of coordinates (x0,y0), (x1,y1) and (x2,y2).

void ST7735_TFT_graphics ::TFTfillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
	int16_t a, b, y, last, dx01, dy01, dx02, dy02, dx12, dy12, sa, sb;
	// Sort coordinates by Y order (y2 >= y1 >= y0)
	if (y0 > y1) {
		_swap_TFT(y0, y1);
		_swap_TFT(x0, x1);
	}
	if (y1 > y2) {
		_swap_TFT(y2, y1);
		_swap_TFT(x2, x1);
	}
	if (y0 > y1) {
		_swap_TFT(y0, y1);
		_swap_TFT(x0, x1);
	}
	if (y0 == y2) {
		a = b = x0;
		if (x1 < a) a = x1;
		else if (x1 > b) b = x1;
		if (x2 < a) a = x2;
		else if (x2 > b) b = x2;
		TFTdrawFastHLine(a, y0, b - a + 1, color);
		return;
	}
	dx01 = x1 - x0;
	dy01 = y1 - y0;
	dx02 = x2 - x0;
	dy02 = y2 - y0;
	dx12 = x2 - x1;
	dy12 = y2 - y1;
	sa = 0;
	sb = 0;
	if (y1 == y2) last = y1;
	else last = y1 - 1;
	for (y = y0; y <= last; y++) {
		a = x0 + sa / dy01;
		b = x0 + sb / dy02;
		sa += dx01;
		sb += dx02;
		if (a > b) _swap_TFT(a, b);
		TFTdrawFastHLine(a, y, b - a + 1, color);
	}

	sa = dx12 * (y - y1);
	sb = dx02 * (y - y0);
	for (; y <= y2; y++) {
		a = x1 + sa / dy12;
		b = x0 + sb / dy02;
		sa += dx12;
		sb += dx02;
		if (a > b) _swap_TFT(a, b);
		TFTdrawFastHLine(a, y, b - a + 1, color);
	}
}

// Desc: writes a char (c) on the TFT
// Param 1 , 2 : coordinates (x, y).
// Param 3: The ASCII character
// Param 4: color 565 16-bit
// Param 5: background color
// Param 6: size. 1-x
// Notes for font #1-6

void ST7735_TFT_graphics ::TFTdrawChar(uint8_t x, uint8_t y, uint8_t c, uint16_t color, uint16_t bg, uint8_t size) {

	int8_t i, j;

	if ((x >= _widthTFT) || (y >= _heightTFT))
		return;
	if (size < 1) size = 1;

	for (i = 0; i < _CurrentFontWidth; i++) {
		uint8_t line =0;
		switch (_FontNumber)
		{
			case TFTFont_Default:
				 line = Font_One[(c - _CurrentFontoffset ) * _CurrentFontWidth + i];
			break;
			case TFTFont_Thick:
				line = Font_Two[(c - _CurrentFontoffset ) * _CurrentFontWidth + i];
			break;
			case TFTFont_Seven_Seg:
				 line = Font_Three[(c - _CurrentFontoffset ) * _CurrentFontWidth + i];
			break;
			case TFTFont_Wide:
				 line = Font_Four[(c - _CurrentFontoffset ) * _CurrentFontWidth + i];
			break;
			case TFTFont_Tiny:
				 line = Font_Five[(c - _CurrentFontoffset ) * _CurrentFontWidth + i];
			break;
			case TFTFont_HomeSpun:
				 line = Font_Six[(c - _CurrentFontoffset ) * _CurrentFontWidth + i];
			break;
		}
		for (j = 0; j < 7; j++, line >>= 1) {
			if (line & 0x01) {
				if (size == 1) TFTdrawPixel(x + i, y + j, color);
				else TFTfillRect(x + (i * size), y + (j * size), size, size, color);
			} else if (bg != color) {
				if (size == 1) TFTdrawPixel(x + i, y + j, bg);
				else TFTfillRect(x + i*size, y + j*size, size, size, bg);
			}
		}
	}
}

//Desc:turn on or off screen wrap of the text (fonts 1-5)
//Param1: TRUE or FALSE

void ST7735_TFT_graphics ::TFTsetTextWrap(bool w) {
	_wrap = w;
}

// Desc: Writes text string (*ptext) on the TFT
// Param 1 , 2 : coordinates (x, y).
// Param 3: pointer to string
// Param 4: color 565 16-bit
// Param 5: background color
// Param 6: size 1-x
// Notes for font #1-6

void ST7735_TFT_graphics ::TFTdrawText(uint8_t x, uint8_t y, char *ptext, uint16_t color, uint16_t bg, uint8_t size) {
	uint8_t _cursorX, _cursorY;
	uint16_t _textSize, i;
	_cursorX = x, _cursorY = y;
	_textSize = strlen(ptext);
	for (i = 0; i < _textSize; i++) {
		if (_wrap && ((_cursorX + size * _CurrentFontWidth) > _widthTFT)) {
			_cursorX = 0;
			_cursorY = _cursorY + size * 7 + 3;
			if (_cursorY > _heightTFT) _cursorY = _heightTFT;
			if (ptext[i] == _CurrentFontoffset ) goto _skip;
		}
		TFTdrawChar(_cursorX, _cursorY, ptext[i], color, bg, size);
		_cursorX = _cursorX + size * (_CurrentFontWidth + 1);
		if (_cursorX > _widthTFT) _cursorX = _widthTFT;
_skip:
		;
	}
}


// Func Desc : called by the print class after it converts the data to a
// character
size_t ST7735_TFT_graphics ::write(uint8_t c)
{
	if (_FontNumber < TFTFont_Bignum)
	{
		if (c == '\n') {
		_cursorY += _textSize*_CurrentFontheight;
		_cursorX  = 0;
		} else if (c == '\r') {
		// skip
		} else {
		TFTdrawChar(_cursorX, _cursorY, c, _textcolor, _textbgcolor, _textSize);
		_cursorX += _textSize*(_CurrentFontWidth+1);
			if (_wrap && (_cursorX > (_widthTFT - _textSize*(_CurrentFontWidth+1)))) {
			  _cursorY += _textSize*_CurrentFontheight;
			  _cursorX = 0;
			}
		}
	}else if (_FontNumber == TFTFont_Bignum || _FontNumber == TFTFont_Mednum)
	{
		uint8_t radius = 3;
		if (_FontNumber == TFTFont_Mednum) radius = 2;

		if (c == '\n')
		{
			_cursorY += _CurrentFontheight;
			_cursorX  = 0;
		} else if (c == '\r')
		{
			// Skip
		} else if (c == '.')
		{
			// draw a circle for decimal & point skip a space.
			TFTfillRect(_cursorX, _cursorY , _CurrentFontWidth, _CurrentFontheight, _textbgcolor);
			TFTfillCircle(_cursorX+(_CurrentFontWidth/2), _cursorY + (_CurrentFontheight-6), radius, _textcolor);
			_cursorX += (_CurrentFontWidth);
			if (_wrap && (_cursorX  > (_widthTFT - (_CurrentFontWidth))))
			{
				_cursorY += _CurrentFontheight;
				_cursorX = 0;
			}
		}else
		{
			TFTdrawCharNumFont(_cursorX, _cursorY, c, _textcolor, _textbgcolor);
			_cursorX += (_CurrentFontWidth);
			if (_wrap && (_cursorX > (_widthTFT - (_CurrentFontWidth))))
			{
				_cursorY += _CurrentFontheight;
				_cursorX = 0;
			}
		}

	}
  return 1;
}


// Desc :  Set the font number
// Param1: Param1: fontnumber 1-8 enum OLED_FONT_TYPE_e
// 1=default 2=thick 3=seven segment 4=wide 5=tiny 6=homespun 7=bignums 8=mednums

void ST7735_TFT_graphics ::TFTFontNum(TFT_FONT_TYPE_e FontNumber) {

	_FontNumber = FontNumber;

	TFT_Font_width_e setfontwidth;
	TFT_Font_offset_e setoffset;
	TFT_Font_height_e setfontheight;

	switch (_FontNumber)
	{
		case TFTFont_Default:  // Norm default 5 by 8
			_CurrentFontWidth = TFTFont_width_5;
			_CurrentFontoffset =  TFTFont_offset_none;
			_CurrentFontheight = TFTFont_height_8;
		break;
		case TFTFont_Thick: // Thick 7 by 8 (NO LOWERCASE LETTERS)
			_CurrentFontWidth = TFTFont_width_7;
			_CurrentFontoffset =  TFTFont_offset_space;
			_CurrentFontheight = TFTFont_height_8;
		break;
		case TFTFont_Seven_Seg:  // Seven segment 4 by 8
			_CurrentFontWidth = TFTFont_width_4;
			_CurrentFontoffset =  TFTFont_offset_space;
			_CurrentFontheight = TFTFont_height_8;
		break;
		case TFTFont_Wide: // Wide  8 by 8 (NO LOWERCASE LETTERS)
			_CurrentFontWidth = TFTFont_width_8;
			_CurrentFontoffset =   TFTFont_offset_space;
			_CurrentFontheight = TFTFont_height_8;
		break;
		case TFTFont_Tiny:  // tiny 3 by 8
			_CurrentFontWidth = TFTFont_width_3;
			_CurrentFontoffset =  TFTFont_offset_space;
			_CurrentFontheight = TFTFont_height_8;
		break;
		case TFTFont_HomeSpun: // homespun 7 by 8 
			_CurrentFontWidth = TFTFont_width_7;
			_CurrentFontoffset =  TFTFont_offset_space;
			_CurrentFontheight = TFTFont_height_8;
		break;
		case TFTFont_Bignum: // big nums 16 by 32 (NUMBERS + : only)
			_CurrentFontWidth = TFTFont_width_16;
			_CurrentFontoffset =   TFTFont_offset_zero;
			_CurrentFontheight = TFTFont_height_32;
		break;
		case TFTFont_Mednum: // med nums 16 by 16 (NUMBERS + : only)
			_CurrentFontWidth = TFTFont_width_16;
			_CurrentFontoffset =  TFTFont_offset_zero;
			_CurrentFontheight = TFTFont_height_16;
		break;
		default:
			_CurrentFontWidth = (setfontwidth = TFTFont_width_5);
			_CurrentFontoffset =  (setoffset = TFTFont_offset_none);
			_CurrentFontheight = (setfontheight=TFTFont_height_8);
			_FontNumber = TFTFont_Default;
		break;
	}
}

// Desc: Draws an custom Icon of X by 8 size to screen , where X = 0 to 127
// Param 1,2  X,Y screen co-ord
// Param 3 0-MAX_Y possible values width of icon in pixels , height is fixed at 8 pixels
// Param 4,5 icon colors ,is bi-color
// Param 6: an array of unsigned chars containing icon data vertically addressed.

void ST7735_TFT_graphics ::TFTdrawIcon(uint8_t x, uint8_t y, uint8_t w, uint16_t color, uint16_t backcolor, const unsigned char character[]) {
	if ((x >= _widthTFT) || (y >= _heightTFT))
		return;
	uint8_t value;
	for (uint8_t byte = 0; byte < w; byte++)
	{
		for (uint8_t mybit = 0; mybit < 8; mybit++)
		{
			value = !!(character[byte]& (1 << mybit));
			if (value)
			{
				TFTdrawPixel(x + byte, y + mybit, backcolor);
			} else
			{
				TFTdrawPixel(x + byte, y + mybit, color);
			}
			value = 0;
		}
	}
}

// Desc: Draws an bi-color bitmap to screen
// Param 1,2  X,Y screen co-ord
// Param 3,4 0-127 possible values width and height of bitmap in pixels
// Param 4,5 bitmap colors ,bitmap is bi-color
// Param 6: an array of unsigned chars containing bitmap data horizontally addressed.
// Note  uses spiWriteBuffer method
void ST7735_TFT_graphics ::TFTdrawBitmap(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color, uint16_t bgcolor, uint8_t *pBmp) {
	int16_t byteWidth = (w + 7) / 8;
	uint8_t byte = 0;
	uint16_t mycolor = 0;
	uint32_t ptr;
	
	// Check bounds
	if ((x >= _widthTFT) || (y >= _heightTFT)) return;
	if ((x + w - 1) >= _widthTFT) w = _widthTFT - x;
	if ((y + h - 1) >= _heightTFT) h = _heightTFT - y;
	
	// Create bitmap buffer
	uint8_t* buffer = (uint8_t*)malloc(w * h * 2);
	ptr = 0;
	
	for (int16_t j = 0; j < h; j++)
	{
		for (int16_t i = 0; i < w; i++)
		{
			if (i & 7)
				byte <<= 1;
			else
				byte = (pBmp[j * byteWidth + i / 8]);
			mycolor = (byte & 0x80) ? color : bgcolor;
			buffer[ptr++] = mycolor >> 8;
			buffer[ptr++] = mycolor;
		}
	}
	// Set window and write buffer
	
	TFTsetAddrWindow(x, y, x + w - 1, y + h - 1);
	TFT_DC_SetHigh;
	TFT_CS_SetLow;
	spiWriteBuffer(buffer, h*w*sizeof(uint16_t));
	TFT_CS_SetHigh;

	free(buffer);
}

// Desc: Draws an 24 bit color bitmap to screen from a bitmap file
// Param 1,2  X,Y screen co-ord
// Param 3 A pointer to the databuffer containing Bitmap data
// Param 4,5: width and height of bitmap in pixels
// Note 24 bit color converted to 16 bit color bv color 565 function.
// Note uses spiWriteBuffer method
void ST7735_TFT_graphics ::TFTdrawBitmap24(uint8_t x, uint8_t y, uint8_t *pBmp, uint8_t  w, uint8_t  h)
{
	uint8_t i, j;
	uint16_t color;
	uint32_t rgb, ptr;

	// Check bounds
	if ((x >= _widthTFT) || (y >= _heightTFT)) return;
	if ((x + w - 1) >= _widthTFT) w = _widthTFT - x;
	if ((y + h - 1) >= _heightTFT) h = _heightTFT - y;
	
	// Create bitmap buffer
	uint8_t* buffer = (uint8_t*)malloc(w * h * 2);

	ptr = 0;
	for(j = 0; j < h; j++)
	{
		for(i = 0; i < w ; i ++)
		{
			// Translate RBG24 to RGB565 bitmap 
			rgb = *(unsigned int*)(pBmp + i * 3 + (h-1-j) * 3 * w);
			color = Color565(((rgb >> 16) & 0xFF), ((rgb >> 8) & 0xFF), (rgb & 0xFF));
			buffer[ptr++] = color >> 8;
			buffer[ptr++] = color;
		}
	}

	// Set window and write buffer
	TFTsetAddrWindow(x, y, x + w - 1, y + h - 1);
	TFT_DC_SetHigh;
	TFT_CS_SetLow;
	spiWriteBuffer(buffer, h*w*sizeof(uint16_t));
	TFT_CS_SetHigh;

	free(buffer);
}

// Desc: Draws an 24 bit color bitmap to screen from a data array
// Param 1,2  X,Y screen co-ord
// Param 3 A pointer to the databuffer containing data array
// Param 4,5: width and height of bitmap in pixels
// Note 24 bit color converted to 16 bit color 
// Note uses spiWriteBuffer method
void ST7735_TFT_graphics ::TFTdrawBitmap24Data(uint8_t x, uint8_t y, uint8_t *pBmp, uint8_t  w, uint8_t  h)
{
	uint8_t i, j;
	uint32_t ptr;
	uint16_t color, red , green ,blue = 0; 
	// Check bounds
	if ((x >= _widthTFT) || (y >= _heightTFT)) return;
	if ((x + w - 1) >= _widthTFT) w = _widthTFT - x;
	if ((y + h - 1) >= _heightTFT) h = _heightTFT - y;
	
	// Create bitmap buffer
	uint8_t* buffer = (uint8_t*)malloc(w * h * 2);

	ptr = 0;
	for(j = 0; j < h; j++)
	{
		for(i = 0; i < w ; i ++)
		{
			// RRRR RRRR GGGG GGGG BBBB BBBB => 565 => RRRRR GGGGGG BBBBB
			red = *pBmp++;
			green = *pBmp++;
			blue = *pBmp++;
			//color = Color565(red , green, blue);
			color = ((red & 0xF8) << 8) | ((green & 0xFC) << 3) | (blue >> 3);
			buffer[ptr++] = color >> 8; // upper byte
			buffer[ptr++] = color & 0x00FF; // lower byte
		}
	}

	// Set window and write buffer
	TFTsetAddrWindow(x, y, x + w - 1, y + h - 1);
	TFT_DC_SetHigh;
	TFT_CS_SetLow;
	spiWriteBuffer(buffer, h*w*sizeof(uint16_t));
	TFT_CS_SetHigh;

	free(buffer);
}


// Desc: Draws an 16 bit color bitmap to screen from a bitmap file
// Param 1,2  X,Y screen co-ord
// Param 3 A pointer to the data array containing Bitmap data
// Param 4,5: width  and height of bitmap in pixels
void ST7735_TFT_graphics ::TFTdrawBitmap16(uint8_t x, uint8_t y, uint8_t *pBmp, uint8_t w, uint8_t h) {
	uint8_t i, j;
	uint16_t color;
	uint32_t ptr;
	
	// Check bounds
	if ((x >= _widthTFT) || (y >= _heightTFT)) return;
	if ((x + w - 1) >= _widthTFT) w = _widthTFT - x;
	if ((y + h - 1) >= _heightTFT) h = _heightTFT - y;
	
	// Create bitmap buffer
	uint8_t* buffer = (uint8_t*)malloc(w * h * 2);
	ptr = 0;
	
	for(j = 0; j < h; j++)
	{
		for(i = 0; i < w; i ++)
		{
			color = *(unsigned int*)(pBmp + i * 2 + (h-1-j) * 2 * w);
			buffer[ptr++] = color >> 8;
			buffer[ptr++] = color & 0x00FF;
		}
	}
	
	// Set window and write buffer
	TFTsetAddrWindow(x, y, x + w - 1, y + h - 1);
	TFT_DC_SetHigh;
	TFT_CS_SetLow;
	spiWriteBuffer(buffer, h*w*sizeof(uint16_t));
	TFT_CS_SetHigh;

	free(buffer);
}

// Desc: Draws an 16 bit color bitmap to screen from a data Array
// Param 1,2  X,Y screen co-ord
// Param 3 A pointer to the databuffer containing data
// Param 4,5: width and height  of bitmap in pixels
void ST7735_TFT_graphics ::TFTdrawBitmap16Data(uint8_t x, uint8_t y, uint8_t *pBmp, uint8_t w, uint8_t h) {
	uint8_t i, j;
	uint32_t ptr;
	
	// Check bounds
	if ((x >= _widthTFT) || (y >= _heightTFT)) return;
	if ((x + w - 1) >= _widthTFT) w = _widthTFT - x;
	if ((y + h - 1) >= _heightTFT) h = _heightTFT - y;
	
	// Create bitmap buffer
	uint8_t* buffer = (uint8_t*)malloc(w * h * 2);
	ptr = 0;
	
	for(j = 0; j < h; j++)
	{
		for(i = 0; i < w; i ++)
		{
			buffer[ptr++] = (*pBmp++);
			buffer[ptr++] = (*pBmp++);
		}
	}
	// Set window and write buffer
	TFTsetAddrWindow(x, y, x + w - 1, y + h - 1);
	TFT_DC_SetHigh;
	TFT_CS_SetLow;
	spiWriteBuffer(buffer, h*w*sizeof(uint16_t));
	TFT_CS_SetHigh;

	free(buffer);
}

// Desc: writes a char (c) on the TFT
// Param 1 , 2 : coordinates (x, y).
// Param 3: The ASCII character
// Param 4: color 565 16-bit
// Param 5: background color
// Notes for font 7,8 only

void ST7735_TFT_graphics ::TFTdrawCharNumFont(uint8_t x, uint8_t y, uint8_t c, uint16_t color , uint16_t bg)
{
	if (_FontNumber < TFTFont_Bignum) {return ;} // Notes for font 7,6 only

	uint8_t i, j;
	uint8_t ctemp = 0, y0 = y;

	for (i = 0; i < _CurrentFontheight*2; i++)
	{
		if (_FontNumber == TFTFont_Bignum){
			ctemp = Font_Seven[c - _CurrentFontoffset][i];
		}
		else if (_FontNumber == TFTFont_Mednum){
			ctemp = Font_Eight[c - _CurrentFontoffset][i];
		}

		for (j = 0; j < 8; j++)
		{
			if (ctemp & 0x80)
			{
				TFTdrawPixel(x, y, color);
			} else
			{
				TFTdrawPixel(x, y, bg);
			}

			ctemp <<= 1;
			y++;
			if ((y - y0) == _CurrentFontheight)
			{
				y = y0;
				x++;
				break;
			}
		}
	}
}

// Desc: Writes text string (*ptext) on the TFT
// Param 1 , 2 : coordinates (x, y).
// Param 3: pointer to string
// Param 4: color 565 16-bit
// Param 5: background color
// Notes for font 7 8 only

void ST7735_TFT_graphics ::TFTdrawTextNumFont(uint8_t x, uint8_t y, char *pText, uint16_t color, uint16_t bg)
{
	if (_FontNumber < TFTFont_Bignum){return ;} // for font 7,6 only

	while (*pText != '\0')
	{
		if (x > (_widthTFT - _CurrentFontWidth ))
		{
			x = 0;
			y += _CurrentFontheight;
			if (y > (_heightTFT - _CurrentFontheight ))
			{
				y = x = 0;
			}
		}
		TFTdrawCharNumFont(x, y, *pText, color, bg);
		x += _CurrentFontWidth ;
		pText++;
	}
}

// Desc: Convert: 24-bit color to 565 16-bit color
// 3 byte to 2 byte,  Red Green Blue.
// RRRR RRRR GGGG GGGG BBBB BBBB => 565 => RRRRR GGGGGG BBBBB
uint16_t ST7735_TFT_graphics::Color565(uint16_t r, uint16_t g, uint16_t b) {
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void ST7735_TFT_graphics ::pushColor(uint16_t color) {
	uint8_t hi, lo;
	hi = color >> 8;
	lo = color;
	TFT_DC_SetHigh;
	TFT_CS_SetLow;
	spiWrite(hi);
	spiWrite(lo);
	TFT_CS_SetHigh;
}

// Desc: Write an SPI command
// Param1: command byte to send

void ST7735_TFT_graphics::writeCommand(uint8_t cmd_) {
	TFT_DC_SetLow;
	TFT_CS_SetLow;
	spiWrite(cmd_);
	TFT_CS_SetHigh;
}

// Desc: Write SPI data
// Param1: data byte to send

void ST7735_TFT_graphics ::writeData(uint8_t data_) {
	TFT_DC_SetHigh;
	TFT_CS_SetLow;
	spiWrite(data_);
	TFT_CS_SetHigh;
}

// Desc: Write SPI databuffer
// Param1: data array to send
// Param2: length of buffer
void ST7735_TFT_graphics ::writeDataBuffer(uint8_t* data_, uint32_t len) {
	TFT_DC_SetHigh;
	TFT_CS_SetLow;
	spiWriteBuffer(data_, len);
	TFT_CS_SetHigh;
}

// Desc: Write to SPI
// Param1: byte to send

void ST7735_TFT_graphics::spiWrite(uint8_t spidata) {
	if (_hardwareSPI == false)
	{
		spiWriteSoftware(spidata);
	} else {
		spi_write_blocking(_pspiInterface, &spidata, 1);
	}
}

// Desc: Write a byte to SPI using software SPI
// Param1: byte to send

void ST7735_TFT_graphics::spiWriteSoftware(uint8_t spidata) {
	uint8_t i;
	for (i = 0; i < 8; i++) {
		TFT_SDATA_SetLow;
		if (spidata & 0x80)TFT_SDATA_SetHigh;
		TFT_SCLK_SetHigh;
		if(TFT_HIGHFREQ_DELAY > 0)TFT_MICROSEC_DELAY(TFT_HIGHFREQ_DELAY);
		spidata <<= 1;
		TFT_SCLK_SetLow;
		if(TFT_HIGHFREQ_DELAY > 0) TFT_MICROSEC_DELAY(TFT_HIGHFREQ_DELAY);
	}
}

// Desc: Write a buffer to SPI, both Software and hardware SPI supported
// Param1: bytes to send
// Param2: length of buffer

void ST7735_TFT_graphics::spiWriteBuffer(uint8_t* spidata, uint32_t len) {
	if(_hardwareSPI == false) {
		for(uint32_t i=0; i<len; i++) {
			spiWriteSoftware(spidata[i]);
		}
	} else {
		spi_write_blocking(_pspiInterface, spidata, len);
	}
}

void ST7735_TFT_graphics::TFTsetCursor(int16_t x, int16_t y) {
  _cursorX = x;
  _cursorY = y;
}

void ST7735_TFT_graphics::setTextSize(uint8_t s) {
  _textSize = (s > 0) ? s : 1;
}

void ST7735_TFT_graphics::setTextColor(uint16_t c) {
  _textcolor = _textbgcolor = c;
}

void ST7735_TFT_graphics::setTextColor(uint16_t c, uint16_t b) {
  _textcolor   = c;
  _textbgcolor = b;
}

//**************** EOF *****************
