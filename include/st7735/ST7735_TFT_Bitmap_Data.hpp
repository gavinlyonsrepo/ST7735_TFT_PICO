/*!
	@file     ST7735_TFT_Bitmap_Data.hpp
	@author   Gavin Lyons
	@brief    Library header file for ST7735_TFT_PICO bitmap data
              Data file to hold bitmap data. Test 12 , test 14. 15 16	
    @note    Not part of core library only used for holding test data, should be omitted
    in project use or port.

     4 bitmaps in file 
    -#  backupmenuBitmap : bi-colour 2048 bytes  (128x128)
    -#  smallImage : bi-colour (20x20)  
    -#  motorImage : 16 bit color 565,  32768 bytes (128x128)
    -#  fruitbowl  : 24 bit color, 49152 bytes (128x128) 

*/

#pragma once

#include "pico/stdlib.h"

extern const uint8_t * pBackupMenuBitmap;  /**< Pointer to bitmap data which is in cpp file */
extern const uint8_t * pSunTextImage;       /**< Pointer to bitmap data which is in cpp file */
extern const uint8_t * pMotorImage;       /**< Pointer to bitmap data which is in cpp file */
extern const uint8_t * pFruitBowlImage;   /**< Pointer to bitmap data which is in cpp file */

