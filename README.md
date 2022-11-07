[![Website](https://img.shields.io/badge/Website-Link-blue.svg)](https://gavinlyonsrepo.github.io/)  [![Rss](https://img.shields.io/badge/Subscribe-RSS-yellow.svg)](https://gavinlyonsrepo.github.io//feed.xml)  [![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/paypalme/whitelight976)

![ ig ](https://github.com/gavinlyonsrepo/pic_16F18346_projects/blob/master/images/st7735/pcb.jpg)

Table of contents
---------------------------

  * [Overview](#overview)
  * [TODO](#todo)
  * [Test](#test)
  * [Software](#software)  
  * [Hardware](#hardware)
  * [Output](#output)

Overview
--------------------------------------------
* Name: ST7735_TFT_PICO
* Description:

0. Library for a TFT SPI LCD, ST7735 Driver
1. Raspberry pi PICO RP2040 library.
2. Inverse colour, rotate, sleep, idle  & verticaly scroll modes supported.
3. Seven fonts
4. Graphics + print class included.
5. bi-color Bitmaps supported.
6. Hardware SPI

* Author: Gavin Lyons
* Port of my Raspberry PI library version 1.5 at [github link.](https://github.com/gavinlyonsrepo/ST7735_TFT_RPI)
* Developed on
	1. Raspberry pi PICO RP2040
	2. SDK C++, compiler G++ for arm-none-eabi
	3. CMAKE , VScode

TODO
---------------------------

1. 16 and 24 color bitmap support
2. Software SPI support is included but currently very slow.


Test
----------------------------

There are 3 example files included , you pick the one you want 
by editing the CMakeLists.txt :: add_executable(${PROJECT_NAME}  section.
There are 3 paths , comment in one path and one path only.

| Filename  | Function  | Note |
| --- | --- | --- |
| ST7735_TFT_HELLOWORLD | Basic use case  | --- |
| ST7735_TFT_TESTS | Text , graphics and bi-color bitmaps tests | --- |
| ST7735_TFT_BMP | 24 and 16 bit color bitmaps tests | Not working,  TODO |


Software
----------------------

In the main.cpp files. There are four sections in "Setup()" function 
where user can make adjustments to select for SPI type used, PCB type used and screen size.


0. USER OPTION 0 SPI_SPEED + TYPE 
1. USER OPTION 1 GPIO
2. USER OPTION 2 SCREEN SECTION 
3. USER OPTION 3 PCB_TYPE


**USER OPTION 0 SPI SPEED** 

Here the user can pass the SPI Bus freq in kiloHertz,
The SPI interface(spi0 spi1 etc) and whether they want software SPI or hardware SPI


**USER OPTION 1 GPIO**

The 5 GPIO pins used, the clodk and data lines must be the clock and data lines 
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

The test files and full screen bitmaps are set up for number 1.  so user will have to modify 
"USER OPTIONS" in main.cpp and provide own (128X160)bitmap to fully test number 2.
No built-in SD card support at present and backlight control is left to user.


**Fonts**

Seven fonts available : 

| Font num | Font name | Font size xbyy |  Note |
| ------ | ------ | ------ | ------ |  
| 1 | Default | 5x8 | Full Extended ASCII 0x00 - 0xFF |
| 2 | Thick   | 7x8 | ASCII  0x20 - 0x5A  ,no lowercase letters |
| 3 | Seven segment | 4x8 | ASCII  0x20 - 0x7A |
| 4 | Wide | 8x8 | ASCII 0x20 - 0x5A , no lowercase letters |
| 5 | Tiny | 3x8 | ASCII  0x20 - 0x7A |
| 6 | Big Nums | 16x32 | ASCII 0x2E-0x3A , Numbers + : . only |
| 7 | Med Nums | 16x16 | ASCII 0x2E-0x3A , Numbers + : . only |

The fonts 1-5 are byte high(at text size 1) scale-able fonts,
The large numerical Fonts, 6 & 7 cannot be scaled.

**Bitmap**

There are four functions to support drawing bitmaps

| Function Name | Colour support | Pixel size |  Note |
| ------ | ------ | ------ | ------ |
| TFTdrawIcon | bi-colour | 8 x(0-127) , 128 bytes max  | Data vertically addressed |
| TFTdrawBitmap | bi-colour | 128 by 128 , 2048 bytes max | Data horizontally  addressed |
| TFTdrawBitmap16 | 16 bit color 565 BMP files | 128 by 128 = 32K max | TODO |
| TFTdrawBitmap24  | 24 bit color BMP files | 128 by 128 = 48K max | TODO , Converted by software to 16-bit color  |

Bitmap size in kiloBytes = (screenWidth * screenHeight * bitsPerPixel)/(1024 * 8)

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

Output
-----------------------

Output of some of the test routine's. Left to right, top to bottom.

1. Different defined colors at default font size 1. Full 16 bit colour 565 available
2. Different sizes of default font. Size 2 3 4 & 5 shown.
3. Different Fonts at font size 2, fonts 1-5. Are these fonts are scale-able
4. Shapes
5. More Shapes
6. Bitmap (bi-color) A background and a foreground.
7. Clock Demo showing icons, small bitmaps and font 6 "BigNums"
8. 24-bit color bitmap test image , test14 , not working TODO
9. 16-bit color bitmap test image, test15 , not working TODO

![ pic ](https://github.com/gavinlyonsrepo/pic_16F18346_projects/blob/master/images/st7735/9.jpg)
![ pic1 ](https://github.com/gavinlyonsrepo/ST7735_TFT_RPI/blob/main/extra/images/4.jpg)
