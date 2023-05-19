# SPi Speed test results 

**November 8 2022**

1. test11B function ::  ST7735_TFT_TESTS file
2. test :: graphics + text
3. 8 MHZ HW SPI
4. 33 fps 

**November 8 2022**

1. test11B function ::  ST7735_TFT_TESTS file
2. test :: graphics + text
3. SW SPI
4. 7 fps 

**November 10 2022**

1. testFPS function ::  ST7735_TFT_BMP_DATA file
2. test :: myTFT.TFTdrawBitmap16Data(0, 0, (uint8_t*)motorImage, 128, 128);
3. 8 MHZ HW SPI
4. 22 fps 

**November 10 2022**

1. testFPS function ::  ST7735_TFT_BMP_DATA file
2. test :: myTFT.TFTdrawBitmap16Data(0, 0, (uint8_t*)motorImage, 128, 128);
3. 20 MHZ HW SPI
4. 39 fps

**November 10 2022**

1. testFPS function ::  ST7735_TFT_BMP_DATA file
2. test :: myTFT.TFTdrawBitmap16Data(0, 0, (uint8_t*)motorImage, 128, 128);
3. 60 MHZ HW SPI
4. 64 fps

**November 10 2022**

1. testFPS function ::  ST7735_TFT_BMP_DATA file
2. test :: myTFT.TFTdrawBitmap24Data(0, 0, (uint8_t*)fruitBowl, 128, 128);
3. 20 MHZ HW SPI
4. 34 fps

**November 10 2022**

1. testFPS function ::  ST7735_TFT_BMP_DATA file
2. test :: myTFT.TFTdrawBitmap(0, 0, 128 , 128, ST7735_WHITE , ST7735_GREEN, backupMenuBitmap);
3. 20 MHZ HW SPI
4. 43 FPS
