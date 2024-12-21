/*!
	@file     main.cpp
	@author   Gavin Lyons
	@brief Example cpp file for ST7735_TFT_PICO library.
			bitmap tests + FPS bitmap test.
	@note  See USER OPTIONS 0-3 in SETUP function

	@test
		-# Test 300 Sprite 
		-# Test 301 "clock demo" , icons, , font 7
		-# Test 302 bi-color small image
		-# Test 303 bi-color full screen image 128x128
		-# Test 304 16 bit color image from a data array
		-# Test 305 24 bit color image data from a data array
		-# Test 601 FPS bitmap results to serial port
		-# Test 802 Error checking bitmap functions, results to serial port

*/

// Section ::  libraries
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "st7735/ST7735_TFT.hpp"
#include "st7735/ST7735_TFT_Bitmap_Data.hpp"
#include <vector> // for error checking test

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
void Test300(void); // sprite
void Test301(void); // "clock demo" , icons, , font 7
void Test302(void); // bi-color small image
void Test303(void); // bi-color full screen image 128x128
void Test304(void); // 16 bit color image from a data array
void Test305(void); // 24 bit color image data from a data array
void Test601(void); // FPS test optional , results to serial port
void Test802(void); // bitmap error checking, results to serial port 
void EndTests(void);

//  Section ::  MAIN

int main(void)
{
	Setup();
	Test300();
	Test301();
	Test302();
	Test303();
	Test304();
	Test305();
	Test802();
	Test601();
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
void Test300(void)
{
	// Test 300-A test 16-bit color Sprite 
	// Draw as sprite, without background , 32 X 32 .bakcground color = ST7375_LBLUE
	// Green bakcground screen
	myTFT.TFTfillScreen(ST7735_GREEN);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTdrawSpriteData(5, 5, (uint8_t *)pSpriteTest16, 32, 32, ST7735_LBLUE);
	TFT_MILLISEC_DELAY(TEST_DELAY5);

	// Test 300-B test 16-bit color Sprite 
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
void Test301(void)
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
} // end of Test 301

/*!
	@brief  Test 302 bi-color small image 20x24
*/
void Test302(void)
{

	myTFT.TFTfillScreen(ST7735_BLACK);
	char teststr1[] = "Test 302";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	myTFT.TFTdrawBitmap(80, 20, 40, 16, ST7735_CYAN, ST7735_BLACK, (uint8_t *)pSunTextImage,80);
	myTFT.TFTdrawBitmap(20, 40, 40, 16, ST7735_RED, ST7735_BLACK, (uint8_t *)pSunTextImage,80);
	myTFT.TFTdrawBitmap(30, 70, 40, 16, ST7735_YELLOW, ST7735_RED, (uint8_t *)pSunTextImage, 80);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

/*!
	@brief  Test303 bi-color full screen image 128x128
*/
void Test303(void)
{
	char teststr1[] = "Test 303";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY2);

	myTFT.TFTdrawBitmap(0, 0, 128, 128, ST7735_WHITE, ST7735_GREEN, (uint8_t *)pArrowImage, 2048);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

/*!
	@brief  Test304 16 bit color image from a data array
*/
void Test304(void)
{
	char teststr1[] = "Test 304";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY5);

	myTFT.TFTdrawBitmap16Data(0, 0, (uint8_t *)pMotorImage, 128, 128);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

/*!
	@brief  Test305 24 bit color image data from a data array
*/
void Test305(void)
{
	char teststr1[] = "Test 305";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY5);

	myTFT.TFTdrawBitmap24Data(0, 0, (uint8_t *)pFruitBowlImage, 128, 128);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

/*!
	@brief  Test601 frame rate per second FPS ,results to serial port
*/
void Test601(void)
{
	// Values to count frame rate per second
	long previousMillis = 0;
	long lastFramerate = 0;
	long currentFramerate = 0;

	uint16_t count = 0;
	uint16_t seconds = 0;
	uint16_t fps = 0;

	char teststr1[] = "Test 601 FPS, Output Results to USB Serial port";
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
	@brief  Bitmap error checking test
*/
void Test802(void)
{
	// === Setup tests ===
	// Define the expected return values
	std::vector<uint8_t> expectedErrors = 
	{
		Display_Success, 
		Display_BitmapScreenBounds, Display_BitmapScreenBounds, Display_BitmapNullptr, Display_IconScreenWidth, //icon
		Display_BitmapScreenBounds, Display_BitmapScreenBounds, Display_BitmapNullptr, //sprite
		Display_BitmapScreenBounds, Display_BitmapScreenBounds, Display_BitmapNullptr, Display_BitmapHorizontalSize, //1-bit bitmap
		Display_BitmapScreenBounds, Display_BitmapScreenBounds, Display_BitmapNullptr, //16-bit bitmap
		Display_BitmapScreenBounds, Display_BitmapScreenBounds, Display_BitmapNullptr  //24-bit bitmap
	};
	// Vector to store return values
	std::vector<uint8_t> returnValues; 
	// test variables
	char testString5[] = "Error Check Test 802, results to usb";
	bool errorFlag = false;

	// === Tests===
	printf("=== START Error checking. Expecting errors ===\r\n");
	// Perform function calls and store return values

	// Print message + sanity check for success
	myTFT.TFTFontNum(myTFT.TFTFont_Default);
	returnValues.push_back(myTFT.TFTdrawText(5, 55, testString5, ST7735_RED, ST7735_BLACK, 2)); 
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
	//TFTdrawIcon
	returnValues.push_back(myTFT.TFTdrawIcon(180, 40, 16, ST7735_BLACK, ST7735_WHITE, SignalIcon));
	returnValues.push_back(myTFT.TFTdrawIcon(180, 180, 16, ST7735_BLACK, ST7735_WHITE, SignalIcon));
	returnValues.push_back(myTFT.TFTdrawIcon(40, 40, 16, ST7735_BLACK, ST7735_WHITE, nullptr));
	returnValues.push_back(myTFT.TFTdrawIcon(40, 40, 180, ST7735_BLACK, ST7735_WHITE, SignalIcon));
	//TFTdrawSpriteData
	returnValues.push_back(myTFT.TFTdrawSpriteData(180, 50, (uint8_t *)pSpriteTest16, 32, 32, ST7735_LBLUE));
	returnValues.push_back(myTFT.TFTdrawSpriteData(40, 180, (uint8_t *)pSpriteTest16, 32, 32, ST7735_LBLUE));
	returnValues.push_back(myTFT.TFTdrawSpriteData(40, 180, nullptr, 32, 32, ST7735_LBLUE));
	//TFTdrawBitmap
	returnValues.push_back(myTFT.TFTdrawBitmap(180, 65, 128, 128, ST7735_WHITE, ST7735_GREEN, (uint8_t *)pArrowImage, 2048));
	returnValues.push_back(myTFT.TFTdrawBitmap(50, 180, 128, 128, ST7735_WHITE, ST7735_GREEN, (uint8_t *)pArrowImage, 2048));
	returnValues.push_back(myTFT.TFTdrawBitmap(50, 65, 128, 128, ST7735_WHITE, ST7735_GREEN, nullptr, 2048));
	returnValues.push_back(myTFT.TFTdrawBitmap(20, 20, 70, 128, ST7735_WHITE, ST7735_GREEN, (uint8_t *)pArrowImage, 2048));
	//TFTdrawBitmap16Data
	returnValues.push_back(myTFT.TFTdrawBitmap16Data(180, 50, (uint8_t *)pSpriteTest16, 32, 32));
	returnValues.push_back(myTFT.TFTdrawBitmap16Data(40, 180, (uint8_t *)pSpriteTest16, 32, 32));
	returnValues.push_back(myTFT.TFTdrawBitmap16Data(40, 180, nullptr, 32, 32));
	//TFTdrawBitmap24Data
	returnValues.push_back(myTFT.TFTdrawBitmap24Data(180, 50, (uint8_t *)pSpriteTest16, 32, 32));
	returnValues.push_back(myTFT.TFTdrawBitmap24Data(40, 180, (uint8_t *)pSpriteTest16, 32, 32));
	returnValues.push_back(myTFT.TFTdrawBitmap24Data(40, 180, nullptr, 32, 32));
	
	//== SUMMARY SECTION===
	printf("\nError Checking Summary.\n");
	// Check return values against expected errors
	for (size_t i = 0; i < returnValues.size(); ++i) {
		if (i >= expectedErrors.size() || returnValues[i] != expectedErrors[i]) {
			errorFlag = true;
			printf("Unexpected error code: %d at test case %zu (expected: %d)\n", 
				returnValues[i], i + 1, (i < expectedErrors.size() ? expectedErrors[i] : -1));
		}
	}

	// Print all expectedErrors for summary
	for (uint8_t value : expectedErrors ) 
	{
		printf("%d ", value);
	}
	printf("\n");
	// Print all returnValues for summary
	for (uint8_t value : returnValues) 
	{
		printf("%d ", value);
	}
	if (errorFlag == true ){
		printf("\nError Checking has FAILED.\n");
	}else{
		printf("\nError Checking has PASSED.\n");
	}
	printf("\n=== STOP Error checking. ===\r\n");
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
