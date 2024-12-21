/*!
	@file     main.cpp
	@author   Gavin Lyons
	@brief Example cpp file for ST7735_TFT_PICO library.
			 Graphics methods testing
	@note  See USER OPTIONS 0-3 in SETUP function

	@test
		-# Test901  pixels and lines
		-# Test902  rectangles
		-# Test903  Circle
		-# Test904  Triangles
		-# Test905  More shapes, media buttons graphic.
*/

// Section ::  libraries
#include "pico/time.h"
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "st7735/ST7735_TFT.hpp"

// Section :: Defines
//  Test timing related defines
#define TEST_DELAY1 1000	  // mS
#define TEST_DELAY2 2000	  // mS
#define TEST_DELAY5 5000	  // mS

// Section :: Globals
ST7735_TFT myTFT;

//  Section ::  Function Headers

void Setup(void);	// setup + user options
void Test901(void);	// pixels and lines
void Test902(void);	// rectangles
void Test903(void);	// Circle
void Test904(void);	// Triangles
void Test905(void);	// More shapes, media buttons graphic.
void EndTests(void);

//  Section ::  MAIN loop

int main(void)
{
	Setup();
	Test901();
	Test902();
	Test903();
	Test904();
	Test905();
	EndTests();
	return 0;
}
// *** End OF MAIN **

//  Section ::  Function Space

/*!
	@brief setup + user options
*/
void Setup(void)
{
	stdio_init_all(); // optional for error messages , Initialize chosen serial port, default 38400 baud
	TFT_MILLISEC_DELAY(TEST_DELAY1);
	printf("TFT :: Start\r\n");

	//*************** USER OPTION 0 SPI_SPEED + TYPE ***********
	bool bhardwareSPI = true; // true for hardware spi,

	if (bhardwareSPI == true)
	{								// hw spi
		uint32_t TFT_SCLK_FREQ = 8000; // Spi freq in KiloHertz , 1000 = 1Mhz
		myTFT.TFTInitSPIType(TFT_SCLK_FREQ, spi0);
	}
	else
	{								 // sw spi
		uint16_t SWSPICommDelay = 0; // optional SW SPI GPIO delay in uS
		myTFT.TFTInitSPIType(SWSPICommDelay);
	}
	//**********************************************************

	// ******** USER OPTION 1 GPIO *********
	// NOTE if using Hardware SPI clock and data pins will be tied to
	// the chosen interface eg Spi0 CLK=18 DIN=19)
	int8_t SDIN_TFT = 19;
	int8_t SCLK_TFT = 18;
	int8_t DC_TFT = 3;
	int8_t CS_TFT = 2;
	int8_t RST_TFT = 17;
	myTFT.TFTSetupGPIO(RST_TFT, DC_TFT, CS_TFT, SCLK_TFT, SDIN_TFT);
	//**********************************************************

	// ****** USER OPTION 2 Screen Setup ******
	uint8_t OFFSET_COL = 0;	   // 2, These offsets can be adjusted for any issues->
	uint8_t OFFSET_ROW = 0;	   // 3, with screen manufacture tolerance/defects
	uint16_t TFT_WIDTH = 128;  // Screen width in pixels
	uint16_t TFT_HEIGHT = 128; // Screen height in pixels
	myTFT.TFTInitScreenSize(OFFSET_COL, OFFSET_ROW, TFT_WIDTH, TFT_HEIGHT);
	// ******************************************

	// ******** USER OPTION 3 PCB_TYPE  **************************
	myTFT.TFTInitPCBType(myTFT.TFT_ST7735R_Red); // pass enum,4 choices,see README
	//**********************************************************
}


/*!
	@brief   pixels and lines
*/
void Test901(void)
{
	TFT_MILLISEC_DELAY(TEST_DELAY1);
	myTFT.TFTfillScreen(ST7735_BLACK);

	myTFT.TFTdrawPixel(85, 5, ST7735_WHITE);
	myTFT.TFTdrawPixel(87, 7, ST7735_WHITE);
	myTFT.TFTdrawPixel(89, 9, ST7735_WHITE);
	myTFT.TFTdrawLine(10, 10, 30, 30, ST7735_RED);
	myTFT.TFTdrawFastVLine(40, 40, 40, ST7735_GREEN);
	myTFT.TFTdrawFastHLine(60, 60, 40, ST7735_YELLOW);

	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

/*!
	@brief  rectangles
*/
void Test902(void)
{
	myTFT.TFTdrawRectWH(5, 5, 20, 20, ST7735_RED);
	if(myTFT.TFTfillRectBuffer(45, 5, 20, 20, ST7735_YELLOW) != 0) //uses spiwrite
	{
		printf("Error Test902 1: Error in the TFTfillRectangle function\r\n");
	}
	myTFT.TFTfillRect(85, 5, 20, 20, ST7735_GREEN);
	myTFT.TFTdrawRoundRect(15, 60, 50, 50, 5, ST7735_CYAN);
	myTFT.TFTfillRoundRect(70, 60, 50, 50, 10, ST7735_WHITE);

	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

/*!
	@brief  circles
*/
void Test903(void)
{
	myTFT.TFTdrawCircle(40, 20, 15, ST7735_GREEN);
	myTFT.TFTfillCircle(80, 20, 15, ST7735_YELLOW);
}

/*!
	@brief  triangles
*/
void Test904(void)
{
	myTFT.TFTdrawTriangle(5, 80, 50, 40, 95, 80, ST7735_CYAN);
	myTFT.TFTfillTriangle(55, 120, 100, 90, 127, 120, ST7735_RED);

	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

/*!
	@brief  More shapes, media buttons graphic.
*/
void Test905()
{
	char teststr1[] = "Press Play";
	// Draw play button
	myTFT.TFTfillRoundRect(25, 10, 78, 60, 8, ST7735_WHITE);
	myTFT.TFTfillTriangle(42, 20, 42, 60, 90, 40, ST7735_RED);
	myTFT.TFTdrawText(5, 80, teststr1, ST7735_GREEN, ST7735_BLACK, 2);
	TFT_MILLISEC_DELAY(TEST_DELAY2);

	// change play color
	myTFT.TFTfillTriangle(42, 20, 42, 60, 90, 40, ST7735_BLUE);
	TFT_MILLISEC_DELAY(TEST_DELAY2);
	// change play color
	myTFT.TFTfillTriangle(42, 20, 42, 60, 90, 40, ST7735_GREEN);
	TFT_MILLISEC_DELAY(TEST_DELAY2);
}

/*!
	@brief  Stop testing and shutdown the TFT
*/
void EndTests(void)
{
	myTFT.TFTPowerDown(); 
	printf("TFT :: Tests Over");
}