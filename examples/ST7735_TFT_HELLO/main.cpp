/*!
	@file     main.cpp
	@author   Gavin Lyons
	@brief Example cpp file for ST7735_TFT_PICO library.
			Tests  Hello World
	@note  See USER OPTIONS 0-3 in SETUP function

	@test
		-# Test0 Print out Hello world  

*/

// Section ::  libraries 
#include "pico/time.h"
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "st7735/ST7735_TFT.hpp"

// Section :: Defines   
//  Test timing related defines 
#define TEST_DELAY1 1000 // mS
#define TEST_DELAY2 2000 // mS
#define TEST_DELAY5 5000 // mS

// Section :: Globals 
ST7735_TFT myTFT;

//  Section ::  Function Headers 

void Setup(void);  // setup + user options
void Test0(void);  
void EndTests(void);

//  Section ::  MAIN loop

int main(void) 
{
	Setup();
	Test0();
	EndTests();
}
// *** End OF MAIN **

//  Section ::  Function Space 

/*!
	@brief setup the TFT :: user options 0-3
*/
void Setup(void)
{
	stdio_init_all(); // optional for error messages , Initialize chosen serial port, default 38400 baud
	TFT_MILLISEC_DELAY(TEST_DELAY1);
	printf("TFT :: Start\r\n");
	
//*************** USER OPTION 0 SPI_SPEED + TYPE ***********
	bool bhardwareSPI = true; // true for hardware spi, false for software
	
	if (bhardwareSPI == true) { // hw spi
		uint32_t TFT_SCLK_FREQ =  8000 ; // Spi freq in KiloHertz , 1000 = 1Mhz
		myTFT.TFTInitSPIType(TFT_SCLK_FREQ, spi0); 
	} else { // sw spi
		uint16_t SWSPICommDelay = 0; // optional SW SPI GPIO delay in uS
		myTFT.TFTInitSPIType(SWSPICommDelay);
	}
//*********************************************************
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
	uint8_t OFFSET_ROW = 0; // 3, with screen manufacture tolerance/defects
	uint16_t TFT_WIDTH = 128;// Screen width in pixels
	uint16_t TFT_HEIGHT = 128; // Screen height in pixels
	myTFT.TFTInitScreenSize(OFFSET_COL, OFFSET_ROW , TFT_WIDTH , TFT_HEIGHT);
// ******************************************

// ******** USER OPTION 3 PCB_TYPE  **************************
	myTFT.TFTInitPCBType(myTFT.TFT_ST7735R_Red); // pass enum,4 choices,see README
//**********************************************************
}

/*!
	@brief print out hello world on TFT
*/
void Test0(void) {

	char teststr1[] = "Hello";
	char teststr2[] = "World";
	
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTFontNum(myTFT.TFTFont_Default);
	myTFT.TFTdrawText(15, 15, teststr1, ST7735_WHITE, ST7735_BLACK, 2);
	myTFT.TFTdrawText(15, 35, teststr2, ST7735_WHITE, ST7735_BLACK, 2);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	TFT_MILLISEC_DELAY(TEST_DELAY2);
	myTFT.TFTfillScreen(ST7735_BLACK);
	TFT_MILLISEC_DELAY(TEST_DELAY1);
}

/*!
	@brief  Stop testing and shutdown the TFT
*/
void EndTests(void)
{
	myTFT.TFTPowerDown(); 
	printf("TFT :: Tests Over");
}

// *************** EOF ****************
