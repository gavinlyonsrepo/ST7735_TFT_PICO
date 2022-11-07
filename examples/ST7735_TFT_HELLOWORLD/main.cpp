/*
 * Project Name: ST7735_TFT_PICO  
 * File: main.cpp
 * Description: library test file  for hello world
 * Author: Gavin Lyons.
 * Description: See URL for full details.
 * NOTE :: USER OPTIONS 0-3 in SETUP function
 * URL: https://github.com/gavinlyonsrepo/ST7735_TFT_PICO
 */

// Section ::  libraries 
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "st7735/ST7735_TFT.hpp"

// Section :: Defines   
//  Test timing related defines 
#define TEST_DELAY1 1000
#define TEST_DELAY2 2000
#define TEST_DELAY5 5000

// Section :: Globals 
ST7735_TFT myTFT;

//  Section ::  Function Headers 
void Setup(void);  // setup + user options
void Test0(void);  // Hello world
void EndTests(void);

//  Section ::  MAIN 

int main(void) 
{
	Setup();
	Test0();
	EndTests();
	return 0;
}
// *** End OF MAIN **

//  Section ::  Function Space 

void Setup(void)
{
	TFT_MILLISEC_DELAY(TEST_DELAY1);
	
//*************** USER OPTION 0 SPI_SPEED + TYPE ***********
	bool bhardwareSPI = true; // true for hardware spi
	
	if (bhardwareSPI == true) { // hw spi
		uint16_t TFT_SCLK_FREQ =  8000 ; // Spi freq in KiloHertz , 1000 = 1Mhz
		myTFT.TFTInitSPIType(TFT_SCLK_FREQ, spi0); 
	} else {
		myTFT.TFTInitSPIType(); // sw spi
	}
//**********************************************************

// ******** USER OPTION 1 GPIO *********
// NOTE if using Hardware SPI clock and data pins will be tied to 
// the chosen interface eg Spi0 CLK=18 DIN=19)
	int8_t SDIN_TFT = 19; 
	int8_t SCLK_TFT = 18; 
	int8_t DC_TFT = 3;
	int8_t CS_TFT = 2 ;  
	int8_t RST_TFT = 17;
	myTFT.TFTSetupGPIO(RST_TFT, DC_TFT, CS_TFT, SCLK_TFT, SDIN_TFT);
//**********************************************************

// ****** USER OPTION 2 Screen Setup ****** 
	uint8_t OFFSET_COL = 0;  // 2, These offsets can be adjusted for any issues->
	uint8_t OFFSET_ROW = 0; // 3, with manufacture tolerance/defects
	uint16_t TFT_WIDTH = 128;// Screen width in pixels
	uint16_t TFT_HEIGHT = 128; // Screen height in pixels
	myTFT.TFTInitScreenSize(OFFSET_COL, OFFSET_ROW , TFT_WIDTH , TFT_HEIGHT);
// ******************************************

// ******** USER OPTION 3 PCB_TYPE  **************************
	myTFT.TFTInitPCBType(TFT_ST7735R_Red); // pass enum,4 choices,see README
//**********************************************************

}

void Test0(void) {

	char teststr1[] = "Hello World";
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTFontNum(TFTFont_Default);
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void EndTests(void)
{
	char teststr1[] = "Test over";
	myTFT.TFTdrawText(5, 50, teststr1, ST7735_GREEN, ST7735_BLACK, 2);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTPowerDown(); 
}

// *************** EOF ****************
