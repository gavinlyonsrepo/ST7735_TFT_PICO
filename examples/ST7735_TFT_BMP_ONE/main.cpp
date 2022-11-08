/*
 * Project Name: ST7735_TFT_PICO
 * File: main.cpp
 * Description: library test file  test 14 and 15 24 and 16 bit bitmap
 * Author: Gavin Lyons.
 * Description: See URL for full details.
 * NOTE :: USER OPTIONS 0-3 in SETUP function
 * NOTE :: NOT WORKING YET . TODO.  
 * URL: https://github.com/gavinlyonsrepo/ST7735_TFT_PICO
 */

// Section ::  libraries 
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "st7735/ST7735_TFT.hpp"
#include "st7735/ST7735_Bitmap_Data.hpp"

// Section :: Defines   
//  Test timing related defines 
#define TEST_DELAY1 1000
#define TEST_DELAY2 2000
#define TEST_DELAY5 5000

// Section :: Globals 
ST7735_TFT myTFT;
bool bTestFPS  = false;

//  Section ::  Function Headers 

void Setup(void);  // setup + user options
void Test12(void); // bi-color image
void Test14(void); // 16 bit color image 
void EndTests(void);

//  Section ::  MAIN 

int main(void) 
{
	
	Setup();
	Test12();
	Test14();
	EndTests();

}
// *** End OF MAIN **


//  Section ::  Function Space 

void Setup(void)
{

	TFT_MILLISEC_DELAY(TEST_DELAY1);
	stdio_init_all(); // Initialize chosen serial port
	TFT_MILLISEC_DELAY(TEST_DELAY1);
	printf("TFT Start\r\n");
	
//*************** USER OPTION 0 SPI_SPEED + TYPE ***********
	bool bhardwareSPI = true; // true for hardware spi, 
	
	if (bhardwareSPI == true) { // hw spi
		uint32_t TFT_SCLK_FREQ =  8000 ; // Spi freq in KiloHertz , 1000 = 1Mhz
		myTFT.TFTInitSPIType(TFT_SCLK_FREQ, spi0); 
	} else { // sw spi
		myTFT.TFTInitSPIType(); 
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

// bi-color bitmap small size 
void Test12(void)
{

	myTFT.TFTfillScreen(ST7735_BLACK);
	char teststr1[] = "Test 12";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	// smallImage is cast as it is defined as const.
	myTFT.TFTdrawBitmap(80, 20, 20 , 20, ST7735_CYAN , ST7735_BLACK, (uint8_t*)smallImage);
	myTFT.TFTdrawBitmap(20, 40, 20 , 20, ST7735_RED, ST7735_BLACK, (uint8_t*)smallImage);

	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);

}


void Test14(void)
{
	myTFT.TFTfillScreen(ST7735_BLACK);
	char teststr1[] = "Test 14";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY2);
	myTFT.TFTdrawBitmap(0, 0, 128 , 128, ST7735_WHITE , ST7735_GREEN, backupMenuBitmap);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
	
}


void EndTests(void)
{
	char teststr1[] = "Tests over";
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTdrawText(5, 50, teststr1, ST7735_GREEN, ST7735_BLACK, 2);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTPowerDown(); 
	printf("TFT End\r\n");
}
// *************** EOF ****************
