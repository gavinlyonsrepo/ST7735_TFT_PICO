/*!
	@file     ST7735_TFT_Font.hpp
	@author   Gavin Lyons
	@brief    Library header file for ST7735_TFT_PICO font data
              This file contains the font definitions and data.	
              10 fonts see main readme file for details.
			  font data is in cpp file.
			  Fonts 9 & 10 optional , comment in define _TFT_OPTIONAL_FONTS to enable 
*/

#pragma once

#include "pico/stdlib.h"


//#define _TFT_OPTIONAL_FONTS /**< Comment in to enable optional fonts 9 & 10  */

extern const unsigned char * pFontDefaultptr; /**< Pointer to default font data  */
extern const unsigned char * pFontThickptr; /**< Pointer to thick font data  */
extern const unsigned char * pFontSevenSegptr; /**< Pointer to seven segment font data  */
extern const unsigned char * pFontWideptr; /**< Pointer to wide font data  */
extern const unsigned char * pFontTinyptr; /**< Pointer to tiny font data  */
extern const unsigned char * pFontHomeSpunptr; /**< Pointer to homespun font data  */
extern const uint8_t (* pFontBigNumptr)[64]; /**< Pointer to big numbers font data  */
extern const uint8_t (* pFontMedNumptr)[32]; /**< Pointer to medium numbers font data  */
#ifdef _TFT_OPTIONAL_FONTS
extern const uint8_t (* pFontArial16x24ptr)[48]; /**< Pointer to Arial Round font data */
extern const uint8_t (* pFontArial16x16ptr)[32]; /**< Pointer to Arial bold font data */
#endif