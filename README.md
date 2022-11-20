[![Website](https://img.shields.io/badge/Website-Link-blue.svg)](https://gavinlyonsrepo.github.io/)  [![Rss](https://img.shields.io/badge/Subscribe-RSS-yellow.svg)](https://gavinlyonsrepo.github.io//feed.xml)  [![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/paypalme/whitelight976)

![ ig ](https://github.com/gavinlyonsrepo/pic_16F18346_projects/blob/master/images/st7735/pcb.jpg)

Table of contents
---------------------------

  * [Overview](#overview)
  * [Test](#test)
  * [Software](#software)  
  * [Hardware](#hardware)
  * [Output](#output)
  * [TODO](#todo)

Overview
--------------------------------------------
* Name: ST7735_TFT_PICO
* Description:

0. Library for a TFT SPI LCD, ST7735 Driver
1. Raspberry pi PICO RP2040 library.
2. Inverse colour, rotate, sleep, idle  & vertical scroll modes supported.
3. Eight fonts
4. Graphics + print class included.
5. bi-color, 16 bit and 24 colour Bitmaps supported.
6. Hardware and software  SPI

* Author: Gavin Lyons
* Port of my Raspberry PI library version 1.5 at [github link.](https://github.com/gavinlyonsrepo/ST7735_TFT_RPI)
* Developed on
	1. Raspberry pi PICO RP2040
	2. SDK C++, compiler G++ for arm-none-eabi
	3. CMAKE , VScode


Test
----------------------------

There are 3 example files included. User picks the one they want 
by editing the CMakeLists.txt :: add_executable(${PROJECT_NAME}  section.
There are 3 paths , comment in one path and one path only.

| Filename  | Function  | Note |
| --- | --- | --- |
| ST7735_TFT_TESTS | Text , graphics , icons tests, Test 1-11 | --- |
| ST7735_TFT_BMP_DATA | bi colour 24 & 16 bitmaps tests ,Test 12 -16 | Bitmap data is stored in arrays on PICO |
| ST7735_TFT_BMP_SDCARD|  SD card bitmaps tests | TODO, not working |


Software
----------------------

In the main.cpp example files. There are four sections in "Setup()" function 
where user can make adjustments to select for SPI type used, PCB type used and screen size.


0. USER OPTION 0 SPI_SPEED + TYPE 
1. USER OPTION 1 GPIO
2. USER OPTION 2 SCREEN SECTION 
3. USER OPTION 3 PCB_TYPE


**USER OPTION 0 SPI SPEED** 

Here the user can pass the SPI Bus freq in kiloHertz, Currently set to 8 Mhz.
Max SPI speed on the PICO is 62.5Mhz. There is a file with SPI test results for the FPS tests in
extra/doc folder. The SPI interface(spi0 spi1 etc). If users wants software SPI just call this method 
without any arguments. 

**USER OPTION 1 GPIO**

The 5 GPIO pins used, the clock and data lines must be the clock and data lines 
of spi interface chosen in option 0 if using hardware SPI.

**USER OPTION 2 Screen size  + Offsets**

In the main.cpp file, in USER OPTION 2 .
User can adjust screen pixel height, screen pixel width and x & y screen offsets.
These offsets can be used in the event of screen damage or manufacturing errors around edge 
such as cropped data or defective pixels.
The function TFTInitScreenSize sets them.

**USER OPTION 3 PCB Version**

It should work in theory on other TFT displays using the different init functions, 
but not tested. In the main.cpp in USER OPTION 3 PCB_TYPE select your PCB.
By passing an enum type to function  TFTInitPCBType.
Default is "TFT_ST7735R_Red". 

There are 4 types of the ST7735 TFT display supported.
| Number | Description | Enum label|
| ---- | ---- | --- | 
| 1 | ST7735B controller| TFT_ST7735B |
| 2 | ST7735R Green Tab | TFT_ST7735R_Green |
| 3 | ST7735R Red Tab   | TFT_ST7735R_Red |
| 4 | ST7735S Black Tab | TFT_ST7735S_Black |


**Tested** 
 
These two are only type of ST7735 library tested on, but should work on other types in theory.

1. TFT SPI LCD, ST7735 Driver, RED PCB v1.1, 1.44 , 128 x 128 pixels, "ST7735R Red Tab" 
2. TFT SPI LCD, ST7735 Driver, RED PCB v1.2, 1.8 , 128 x 160 pixels, "ST7735S Black Tab" 

The test files and full screen bitmaps are set up for number 1. 


**Fonts**

Eight fonts available : 

| # | Name | Char size WxH |  ASCII range |  Size in bytes |
| ------ | ------ | ------ | ------ |   ------ |  
| 1 | Default | 5x8 | Full Extended ASCII 0x00 - 0xFF | 1275 |
| 2 | Thick   | 7x8 | ASCII  0x20 - 0x5A  ,no lowercase letters | 406 |
| 3 | Seven segment | 4x8 | ASCII  0x20 - 0x7A |  364 |
| 4 | Wide | 8x8 | ASCII 0x20 - 0x5A , no lowercase letters | 464 | 
| 5 | Tiny | 3x8 | ASCII  0x20 - 0x7E | 285 |
| 6 | HomeSpun  | 7x8 | ASCII  0x20 - 0x7E |  658 |
| 7 | Big Nums | 16x32 | ASCII 0x2E-0x3A , Numbers + : . only | 704 |
| 8 | Med Nums | 16x16 | ASCII 0x2E-0x3A , Numbers + : . only | 352 |

The fonts 1-6 are byte high(at text size 1) scale-able fonts,
The large numerical Fonts, 7 & 8 cannot be scaled.

**Bitmap**

There are 6 functions to support drawing bitmaps, 

| Num | Function Name | Colour support | bitmap size Max |  Note |
| ------ | ------ | ------ | ------ | ------ |
| 1 | TFTdrawIcon | bi-colour | (8 x (0-Max_y)) 128 bytes max  | Data vertically addressed |
| 2 | TFTdrawBitmap | bi-colour | 2048 bytes  | Data horizontally  addressed |
| 3 | TFTdrawBitmap16Data | 16 bit color 565  | 32768  | Data from array on PICO |
| 4 | TFTdrawBitmap24Data  | 24 bit color  | 49152  | Data from Array on PICO, Converted by software to 16-bit color  |
| 5 | TFTdrawBitmap16 | 16 bit color 565 BMP files |  32768  | TODO not working , Data from SD card|
| 6 | TFTdrawBitmap24  | 24 bit color BMP files | 49152  | TODO not working ,  Data from SD card  |

1. Bitmap size in kiloBytes = (screenWidth * screenHeight * bitsPerPixel)/(1024 * 8)
2. Math in bitmap size column 2-5  assumes 128x128 pixel screen.
3. The data array for 1 and 2 is created from image files using file data conversion tool [link](https://javl.github.io/image2cpp/)
4. The data array for 3 and 4 is created from BMP files using file data conversion tool [link](https://notisrac.github.io/FileToCArray/)

Hardware
----------------------

Connections as setup in main.cpp helloworld test file.

| TFT PinNum | Pindesc |  HW SPI |
| --- | --- | --- | 
| 1 | LED | VCC |   
| 2 | SCLK | GPIO18 |
| 3 | SDA | GPIO19 |
| 4 | A0/DC |  GPIO3  |
| 5 | RESET |   GPIO17 |
| 6 | SS/CS |  GPIO2 |
| 7 | GND | GND |
| 8 | VCC |  VCC  |

1. NOTE connect LED backlight pin 1 thru a 150R/220R ohm resistor to 3.3/5V VCC.
2. This is a 3.3V logic device do NOT connect the I/O logic lines to 5V logic device.
3. You can connect VCC to 5V if there is a 3.3 volt regulator on back of TFT module.
4. SW SPI pick any GPIO you like , HW SPI SCLK and SDA will be tied to spio interface.
5. Backlight on/off control is left to user.

Output
-----------------------

Output of some of the test routine's. Left to right

1. Bitmap (bi-color) A background and a foreground, 128 X 128 pixels.
2. Different sizes of default font. Size 2 3 4 & 5 shown.
3. Different Fonts at font size 2, fonts 1-6 All these fonts are scale-able
4. Graphics.
5. Clock Demo Test 11,  showing icons, and font 7 "BigNums"
6. 24 bit RGB test image displayed from a data array  ,  128 X 128 pixels.
7. 16 bit 565 test image displayed from a data array , 128 X 128 pixels.

![ pic ](https://github.com/gavinlyonsrepo/ST7735_TFT_PICO/blob/main/extra/doc/images/row1.jpg)
![ pic1 ](https://github.com/gavinlyonsrepo/ST7735_TFT_RPI/blob/main/extra/images/4.jpg)


TODO
--------------------------

* SD card support for displaying BMP files. 
