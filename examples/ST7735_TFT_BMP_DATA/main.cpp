/*!
	@file     main.cpp
	@author   Gavin Lyons
	@brief Example cpp file for ST7735_TFT_PICO library.
			bitmap tests + FPS bitmap test.
	@note  See USER OPTIONS 0-3 in SETUP function

	@test
		-# Test 400 Sprite 
		-# Test 401 "clock demo" , icons, , font 7
		-# Test 402 bi-color small image
		-# Test 403 bi-color full screen image 128x128
		-# Test 404 16 bit color image from a data array
		-# Test 405 24 bit color image data from a data array
		-# Test 701 FPS bitmap results to serial port

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
#define CLOCK_DISPLAY_TIME 20 // seconds

// Section :: Globals
ST7735_TFT myTFT;

//  Section ::  Function Headers

void Setup(void);	// setup + user options
void Test400(void); // sprite
void Test401(void); // "clock demo" , icons, , font 7
void Test402(void); // bi-color small image
void Test403(void); // bi-color full screen image 128x128
void Test404(void); // 16 bit color image from a data array
void Test405(void); // 24 bit color image data from a data array
void Test701(void); // FPS test optional , results to serial port
void EndTests(void);

//  Section ::  MAIN

int main(void)
{
	Setup();
	Test400();
	Test401();
	Test402();
	Test403();
	Test404();
	Test405();
	Test701();
	EndTests();
}
// *** End OF MAIN **

//  Section ::  Function Space

/*!
	@brief  setup + user options
*/
void Setup(void)
{
	stdio_init_all(); // Initialize chosen serial port
	TFT_MILLISEC_DELAY(TEST_DELAY1);
	printf("TFT :: Start\r\n");

	//*************** USER OPTION 0 SPI_SPEED + TYPE ***********
	bool bhardwareSPI = true; // true for hardware spi,

	if (bhardwareSPI == true)
	{								   // hw spi
		uint32_t TFT_SCLK_FREQ = 8000; // Spi freq in KiloHertz , 1000 = 1Mhz , max 62500
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
	// the chosen interface (eg Spi0 CLK=18 DIN=19)
	int8_t SDIN_TFT = 19;
	int8_t SCLK_TFT = 18;
	int8_t DC_TFT = 3;
	int8_t CS_TFT = 2;
	int8_t RST_TFT = 17;
	myTFT.TFTSetupGPIO(RST_TFT, DC_TFT, CS_TFT, SCLK_TFT, SDIN_TFT);
	//**********************************************************

	// ****** USER OPTION 2 Screen Setup ******
	uint8_t OFFSET_COL = 0;	   // 2, These offsets can be adjusted for any issues->
	uint8_t OFFSET_ROW = 0;	   // 3, with manufacture tolerance/defects
	uint16_t TFT_WIDTH = 128;  // Screen width in pixels
	uint16_t TFT_HEIGHT = 128; // Screen height in pixels
	myTFT.TFTInitScreenSize(OFFSET_COL, OFFSET_ROW, TFT_WIDTH, TFT_HEIGHT);
	// ******************************************

	// ******** USER OPTION 3 PCB_TYPE  **************************
	myTFT.TFTInitPCBType(myTFT.TFT_ST7735R_Red); // pass enum,4 choices,see README
   //**********************************************************
}

/*!
	@brief  "sprite demo" 32 x 32 with LBLUE background
*/
void Test400(void)
{
	// Test 400-A test 16-bit color Sprite 
	// Draw as sprite, without background , 32 X 32 .bakcground color = ST7375_LBLUE
	// Green bakcground screen
	myTFT.TFTfillScreen(ST7735_GREEN);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTdrawSpriteData(5, 5, (uint8_t *)pSpriteTest16, 32, 32, ST7735_LBLUE);
	TFT_MILLISEC_DELAY(TEST_DELAY5);

	// Test 400-B test 16-bit color Sprite 
	// Draw as sprite, without background , 32 X 32 .bakcground color = ST7375_LBLUE
	// Bitmap background screen
	myTFT.TFTdrawBitmap24Data(0, 0, (uint8_t *)pFruitBowlImage, 128, 128);
	TFT_MILLISEC_DELAY(TEST_DELAY5);

    myTFT.TFTdrawSpriteData(60, 10, (uint8_t *)pSpriteTest16, 32, 32, ST7735_LBLUE);
	myTFT.TFTdrawSpriteData(60, 60, (uint8_t *)pSpriteTest16, 32, 32, ST7735_LBLUE);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

/*!
	@brief  "clock demo" , icons, , font 7
*/
void Test401(void)
{
	myTFT.TFTfillScreen(ST7735_BLACK);

	// Test variables
	uint16_t count = CLOCK_DISPLAY_TIME;
	char strCount[6];
	char strTime[12];
	char strName[8] = "G Lyons";
	uint8_t Hour = 10;
	uint8_t Min = 59;
	uint8_t Sec = 45;
	unsigned long previousMillis = 0; // will store last time display was updated
	const long interval = 1000;		  //   interval at which to update display (milliseconds)

	// All icons data vertically addressed
	// power icon, 12x8
	const unsigned char powerIcon[12] = {0xff, 0xe7, 0xc3, 0x99, 0xa5, 0xad, 0xad, 0xa5, 0x99, 0xc3, 0xe7, 0xff};
	// lighting symbol, 12x8
	const unsigned char speedIcon[12] = {0xff, 0xff, 0xf7, 0xb3, 0xd1, 0xc0, 0xe0, 0xf4, 0xf6, 0xfe, 0xff, 0xff};
	// Mobile icon  16x8px
	const unsigned char SignalIcon[16] = {0x03, 0x05, 0x09, 0xff, 0x09, 0x05, 0xf3, 0x00, 0xf8, 0x00, 0xfc, 0x00, 0xfe, 0x00, 0xff, 0x00};
	// Message icon  16x8px
	const unsigned char MsgIcon[16] = {0x00, 0x00, 0x00, 0xff, 0x85, 0x89, 0x91, 0x91, 0x91, 0x91, 0x89, 0x85, 0xff, 0x00, 0x00, 0x00};
	// Alarm icon  8x8px
	const unsigned char AlarmIcon[8] = {0x83, 0xbd, 0x42, 0x4a, 0x52, 0x52, 0xbd, 0x83};
	// Battery Icon  16x8px
	const unsigned char BatIcon[16] = {0x00, 0x00, 0x7e, 0x42, 0x81, 0xbd, 0xbd, 0x81, 0xbd, 0xbd, 0x81, 0xbd, 0xbd, 0x81, 0xff, 0x00};

	// TOP icons box
	myTFT.TFTdrawIcon(2, 2, 16, ST7735_BLACK, ST7735_WHITE, SignalIcon);
	myTFT.TFTdrawIcon(20, 2, 16, ST7735_BLACK, ST7735_WHITE, MsgIcon);
	myTFT.TFTdrawIcon(40, 2, 8, ST7735_BLACK, ST7735_WHITE, AlarmIcon);
	myTFT.TFTdrawIcon(102, 2, 16, ST7735_BLACK, ST7735_WHITE, BatIcon);
	// second box
	myTFT.TFTdrawIcon(5, 20, 12, ST7735_GREEN, ST7735_BLACK, powerIcon);
	myTFT.TFTdrawIcon(20, 20, 12, ST7735_RED, ST7735_YELLOW, speedIcon);
	myTFT.TFTdrawText(80, 20, strName, ST7735_BLUE, ST7735_BLACK, 1);

	// RED section lines
	myTFT.TFTdrawFastHLine(0, 17, 127, ST7735_RED);
	myTFT.TFTdrawFastHLine(0, 32, 127, ST7735_RED);
	myTFT.TFTdrawFastHLine(0, 80, 127, ST7735_RED);
	myTFT.TFTdrawFastHLine(0, 118, 127, ST7735_RED);

	myTFT.TFTFontNum(myTFT.TFTFont_Bignum);
	while (1)
	{
		unsigned long currentMillis = to_ms_since_boot(get_absolute_time());

		if (currentMillis - previousMillis >= interval)
		{
			previousMillis = currentMillis;
			Sec++;
			if (Sec == 60)
			{
				Min++;
				Sec = 0;
				if (Min == 60)
				{
					Hour++;
					Min = 0;
					if (Hour == 24)
					{
						Hour = 0;
					}
				}
			}
			// display Clock
			myTFT.TFTFontNum(myTFT.TFTFont_Bignum);
			snprintf(strTime, sizeof(strTime), "%02u:%02u:%02u", Hour, Min, Sec);
			myTFT.TFTdrawText(0, 45, strTime, ST7735_GREEN, ST7735_BLACK);
			// display counter
			myTFT.TFTFontNum(myTFT.TFTFont_Mednum);
			snprintf(strCount, sizeof(strCount), "%03d", count);
			myTFT.TFTdrawText(0, 85, strCount, ST7735_YELLOW, ST7735_RED);
			count--;
			// Display the Libary version number
			myTFT.TFTsetCursor(60, 85);
			myTFT.print(myTFT.TFTLibVerNumGet());
		} // if every second

		if (count == 1)
			break;
	} // end of while

	TFT_MILLISEC_DELAY(TEST_DELAY2);
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTFontNum(myTFT.TFTFont_Default);
} // end of test 401

/*!
	@brief  test 402 bi-color small image 20x24
*/
void Test402(void)
{

	myTFT.TFTfillScreen(ST7735_BLACK);
	char teststr1[] = "Test 402";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	myTFT.TFTdrawBitmap(80, 20, 40, 16, ST7735_CYAN, ST7735_BLACK, (uint8_t *)pSunTextImage,80);
	myTFT.TFTdrawBitmap(20, 40, 40, 16, ST7735_RED, ST7735_BLACK, (uint8_t *)pSunTextImage,80);
	myTFT.TFTdrawBitmap(30, 70, 40, 16, ST7735_YELLOW, ST7735_RED, (uint8_t *)pSunTextImage, 80);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

/*!
	@brief  Test403 bi-color full screen image 128x128
*/
void Test403(void)
{
	char teststr1[] = "Test 403";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY2);

	myTFT.TFTdrawBitmap(0, 0, 128, 128, ST7735_WHITE, ST7735_GREEN, (uint8_t *)pArrowImage, 2048);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

/*!
	@brief  Test404 16 bit color image from a data array
*/
void Test404(void)
{
	char teststr1[] = "Test 404";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY5);

	myTFT.TFTdrawBitmap16Data(0, 0, (uint8_t *)pMotorImage, 128, 128);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

/*!
	@brief  Test405 24 bit color image data from a data array
*/
void Test405(void)
{
	char teststr1[] = "Test 405";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY5);

	myTFT.TFTdrawBitmap24Data(0, 0, (uint8_t *)pFruitBowlImage, 128, 128);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

/*!
	@brief  Test701 frame rate per second FPS ,results to serial port
*/
void Test701(void)
{
	// Values to count frame rate per second
	long previousMillis = 0;
	long lastFramerate = 0;
	long currentFramerate = 0;

	uint16_t count = 0;
	uint16_t seconds = 0;
	uint16_t fps = 0;

	char teststr1[] = "Test 701 FPS, Output Results to USB Serial port";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.setTextColor(ST7735_YELLOW, ST7735_RED);

	while (1)
	{
		unsigned long currentMillis = to_ms_since_boot(get_absolute_time());

		if (currentMillis - previousMillis >= 1000) // every second
		{
			fps = currentFramerate - lastFramerate;
			lastFramerate = currentFramerate;
			previousMillis = currentMillis;
			seconds++;
			if (seconds == 20)
				break;
		}
		currentFramerate++;
		count++;

		//  ** Code to test **
		myTFT.TFTdrawBitmap16Data(0, 0, (uint8_t *)pMotorImage, 128, 128);
		myTFT.TFTsetCursor(5, 5); 
		myTFT.print(fps);
		//   **
	} // end of while
	
	// Report results to usb
	printf("Seconds :: %u \n", seconds);
	printf("Count :: %u \n", count);
	printf("FPS :: %u \n", fps);
	// Print to screen
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTsetCursor(0, 0); 
	myTFT.print("Seconds : ");
	myTFT.println(seconds);
	myTFT.print("Count : ");
	myTFT.println(count);
	myTFT.print("FPS : ");
	myTFT.print(fps);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
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
	printf("TFT :: Tests Over\r\n");
}
// *************** EOF ****************
