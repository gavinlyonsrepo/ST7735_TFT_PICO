/*!
	@file     main.cpp
	@author   Gavin Lyons
	@brief Example cpp file for ST7735_TFT_PICO library.
			Tests 13-16. bitmap tests
	@note  See USER OPTIONS 0-3 in SETUP function

	@test

	-# Test 13 bi-color small image
	-# Test 14 bi-color full screen image 128x128
	-# Test 15 16 bit color image from a data array
	-# Test 16  24 bit color image data from a data array
	-# Test FPS FPS optional test -> set bool bTestFPS

*/
// Section ::  libraries 
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "st7735/ST7735_TFT.hpp"
#include "st7735/ST7735_TFT_Bitmap_Data.hpp"

// Section :: Defines   
//  Test timing related defines 
#define TEST_DELAY1 1000
#define TEST_DELAY2 2000
#define TEST_DELAY5 5000

// Section :: Globals 
ST7735_TFT myTFT;
bool bTestFPS  = false; /**< turn on frame rate per second test , set true for ON */

//  Section ::  Function Headers 

void Setup(void);  // setup + user options
void Test13(void); // bi-color small image
void Test14(void); // bi-color full screen image 128x128
void Test15(void); // 16 bit color image from a data array
void Test16(void); // 24 bit color image data from a data array
void TestFPS(void); // FPS test optional 
void EndTests(void);

//  Section ::  MAIN 

int main(void) 
{
	
	Setup();
	stdio_init_all(); // Initialize chosen serial port for FPS results
	Test13();
	Test14();
	Test15();
	Test16();
	if (bTestFPS == true) TestFPS();
	EndTests();

}
// *** End OF MAIN **


//  Section ::  Function Space 

/*!
	@brief  setup + user options
*/
void Setup(void)
{

	TFT_MILLISEC_DELAY(TEST_DELAY1);
	stdio_init_all(); // Initialize chosen serial port
	TFT_MILLISEC_DELAY(TEST_DELAY1);
	printf("TFT Start\r\n");
	
//*************** USER OPTION 0 SPI_SPEED + TYPE ***********
	bool bhardwareSPI = true; // true for hardware spi, 
	
	if (bhardwareSPI == true) { // hw spi
		uint32_t TFT_SCLK_FREQ = 8000 ; // Spi freq in KiloHertz , 1000 = 1Mhz , max 62500
		myTFT.TFTInitSPIType(TFT_SCLK_FREQ, spi0); 
	} else { // sw spi
		myTFT.TFTInitSPIType(); 
	}
//**********************************************************

// ******** USER OPTION 1 GPIO *********
// NOTE if using Hardware SPI clock and data pins will be tied to 
// the chosen interface (eg Spi0 CLK=18 DIN=19)
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
	myTFT.TFTInitPCBType(myTFT.TFT_ST7735R_Red); // pass enum,4 choices,see README
//**********************************************************
	
}

/*!
	@brief  test 13 bi-color small image 20x24
*/
void Test13(void)
{

	myTFT.TFTfillScreen(ST7735_BLACK);
	char teststr1[] = "Test 12";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	myTFT.TFTdrawBitmap(80, 20, 20 , 24, ST7735_CYAN , ST7735_BLACK, (uint8_t*)pSmallImage);
	myTFT.TFTdrawBitmap(20, 40, 20 , 24, ST7735_RED, ST7735_BLACK, (uint8_t*)pSmallImage);
	myTFT.TFTdrawBitmap(30, 70, 20 , 24, ST7735_YELLOW, ST7735_RED, (uint8_t*)pSmallImage);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);

}

/*!
	@brief  Test14 bi-color full screen image 128x128
*/
void Test14(void)
{
	char teststr1[] = "Test 14";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY1);
	
	myTFT.TFTdrawBitmap(0, 0, 128 , 128, ST7735_WHITE , ST7735_GREEN, (uint8_t*)pBackupMenuBitmap);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
	
}

/*!
	@brief  Test15 16 bit color image from a data array
*/
void Test15(void)
{
	char teststr1[] = "Test 15";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY1);

	myTFT.TFTdrawBitmap16Data(0, 0, (uint8_t*)pMotorImage, 128, 128);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

/*!
	@brief  Test16 24 bit color image data from a data array
*/
void Test16(void)
{
	char teststr1[] = "Test 16";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY1);

	myTFT.TFTdrawBitmap24Data(0, 0, (uint8_t*)pFruitBowlImage, 128, 128);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

/*!
	@brief  TestFPS FPS optional test -> set bool bTestFPS
*/
void TestFPS(void)
{
	// Values to count frame rate per second
	long previousMillis  = 0;
	long lastFramerate = 0;
	long currentFramerate = 0;

	uint16_t count  = 0;
	uint16_t seconds  = 0;
	uint16_t fps = 0;

	char teststr1[] = "Test FPS";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY1);

	while(1){

	unsigned long currentMillis = to_ms_since_boot(get_absolute_time());

	if (currentMillis  - previousMillis  >= 1000) // every second
	{
		fps = currentFramerate - lastFramerate;
		lastFramerate = currentFramerate ;
		previousMillis  = currentMillis;
		seconds++;
		if (seconds == 10)break;
	}
	currentFramerate++;
	count++;
	
	//  ** Code to test ** 
	//myTFT.TFTdrawBitmap(0, 0, 128 , 128, ST7735_WHITE , ST7735_GREEN, backupMenuBitmap);
	myTFT.TFTdrawBitmap16Data(0, 0, (uint8_t*)pMotorImage, 128, 128);
	//myTFT.TFTdrawBitmap24Data(0, 0, (uint8_t*)fruitBowl, 128, 128);
	//  **
	} // end of while 

	// Report results to usb
	printf("Seconds :: %u \n", seconds  );
	printf("Count :: %u \n", count  );
	printf("FPS :: %u \n", fps );
}

/*!
	@brief  Stop testing and shutdown the TFT
*/
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
