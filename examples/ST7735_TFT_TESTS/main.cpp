/*
 * Project Name: ST7735_TFT_PICO
 * File: main.cpp
 * Description: library test file for test 0-12, text, graphics, bi-color bitmap.
 * Author: Gavin Lyons.
 * Created: November 2022
 * Description: See URL for full details.
 * NOTE: USER OPTIONS 0-3 in SETUP function
 * URL: https://github.com/gavinlyonsrepo/ST7735_TFT_PICO
 */

// Section ::  libraries 
#include "pico/time.h"
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "st7735/ST7735_TFT.hpp"

// Section :: Defines   
//  Test timing related defines 
#define TEST_DELAY1 1000
#define TEST_DELAY2 2000
#define TEST_DELAY5 5000
#define CLOCK_DISPLAY_TIME 20

// Section :: Globals 
ST7735_TFT myTFT;
bool bTestFPS = false;

//  Section ::  Function Headers 

void Setup(void);  // setup + user options
void Test1(void);  // Print out  fonts 1-6
void Test1A(void); // defined 16-bit Colors, text
void Test1B(void); // print entire ASCII font 0 to 254, default font
void Test1C(void); // print numbers int and float using draw functions
void Test1D(void); // PRINT function
void Test1E(void); // Print out font 7 & 8 using draw functions
void Test2(void);  // font sizes (2-5) + character draw using draw functions
void Test3(void);  // pixels and lines
void Test4(void);  // rectangles 
void Test5(void);  // Circle
void Test6(void);  // Triangles 
void Test7(void);  // scroll
void Test8(void);  // More shapes, media buttons graphic.
void Test9(void);  // Rotate
void Test10(void); // change modes test -> Invert, display on/off and Sleep.
void Test11(void); // "clock demo" , icons, , font 7
void Test11B(void); // FPS
void EndTests(void);

//  Section ::  MAIN loop

int main(void) 
{
	Setup();
	Test1();
	Test1A();
	Test1B();
	Test1C();
	Test1D();
	Test1E();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();
	Test8();
	Test9();
	Test10();
	Test11();
	if (bTestFPS == true)  Test11B();
	EndTests();
	return 0;
}
// *** End OF MAIN **

//  Section ::  Function Space 

void Setup(void)
{

	TFT_MILLISEC_DELAY(TEST_DELAY1);
	
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
	uint8_t OFFSET_ROW = 0; // 3, with screen manufacture tolerance/defects
	uint16_t TFT_WIDTH = 128;// Screen width in pixels
	uint16_t TFT_HEIGHT = 128; // Screen height in pixels
	myTFT.TFTInitScreenSize(OFFSET_COL, OFFSET_ROW , TFT_WIDTH , TFT_HEIGHT);
// ******************************************

// ******** USER OPTION 3 PCB_TYPE  **************************
	myTFT.TFTInitPCBType(TFT_ST7735R_Red); // pass enum,4 choices,see README
//**********************************************************
}

void Test1(void) {

	char teststr1[] = "Default 1";
	char teststr2[] = "THICK 2";
	char teststr3[] = "Seven 3";
	char teststr4[] = "WIDE 4";
	char teststr5[] = "Tiny 5";
	char teststr6[] = "Home 6";
	
	myTFT.TFTfillScreen(ST7735_BLACK);
	
	myTFT.TFTFontNum(TFTFont_Default);
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 2);
	myTFT.TFTFontNum(TFTFont_Thick);
	myTFT.TFTdrawText(5, 25, teststr2, ST7735_GREEN, ST7735_BLACK, 2);
	myTFT.TFTFontNum(TFTFont_Seven_Seg);
	myTFT.TFTdrawText(5, 45, teststr3, ST7735_BLUE, ST7735_BLACK, 2);
	myTFT.TFTFontNum(TFTFont_Wide);
	myTFT.TFTdrawText(5, 65, teststr4, ST7735_CYAN, ST7735_BLACK, 2);
	myTFT.TFTFontNum(TFTFont_Tiny);
	myTFT.TFTdrawText(5, 85, teststr5, ST7735_RED, ST7735_BLACK, 2);
	myTFT.TFTFontNum(TFTFont_HomeSpun);
	myTFT.TFTdrawText(5, 105, teststr6, ST7735_YELLOW, ST7735_BLACK, 2);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTFontNum(TFTFont_Default);
}

void Test1A(void) {
	char teststr1[] = "WHITE";
	char teststr2[] = "BLUE";
	char teststr3[] = "RED";
	char teststr4[] = "GREEN";
	char teststr5[] = "CYAN";
	char teststr6[] = "MAGENTA";
	char teststr7[] = "YELLOW";
	char teststr8[] = "GREY";
	char teststr9[] = "TAN";
	char teststr10[] = "BROWN";
	char teststr11[] = "PINK";
	char teststr12[] = "ORANGE";
	myTFT.TFTdrawText(5, 10, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 25, teststr2, ST7735_BLUE, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 40, teststr3, ST7735_RED, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 55, teststr4, ST7735_GREEN, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 70, teststr5, ST7735_CYAN, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 85, teststr6, ST7735_MAGENTA, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTdrawText(5, 10, teststr7, ST7735_YELLOW, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 25, teststr8, ST7735_GREY, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 40, teststr9, ST7735_TAN, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 55, teststr10 , ST7735_BROWN, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 70, teststr11, ST7735_PINK, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 85, teststr12 , ST7735_ORANGE, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void Test1B(void) {
	uint8_t row = 5;
	uint8_t col = 5;
	for (char i = 0; i < 126; i++) {
		
		myTFT.TFTdrawChar(col, row, i, ST7735_GREEN, ST7735_BLACK, 1);
		col += 10;
		if (col > 100) {
			row += 10;
			col = 0;
		}
	}

	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
	row = 5;
	col = 5;
	for (unsigned char j = 127; j < 254; j++) {
		
		myTFT.TFTdrawChar(col, row, j, ST7735_GREEN, ST7735_BLACK, 1);
		col += 10;
		if (col > 100) {
			row += 10;
			col = 0;
		}
	}
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}


void Test1C(void)
{
	int myInt=931;
	char myStr[5];
	myTFT.TFTFontNum(TFTFont_Seven_Seg);
	sprintf(myStr, "%d", myInt);
	myTFT.TFTdrawText(5, 5, myStr, ST7735_BLUE, ST7735_BLACK, 3);

	float  myPI = 3.141592;
	char myStr2[8];
	sprintf(myStr2, "%0.3f", myPI);
	myTFT.TFTdrawText(5, 65, myStr2, ST7735_RED, ST7735_BLACK, 3);
	
	TFT_MILLISEC_DELAY(TEST_DELAY2);
	myTFT.TFTfillScreen(ST7735_BLACK);
		
}


void Test1D(void){

	uint8_t numPos = 47;

	myTFT.setTextSize(1);  // Test a string with print 
	myTFT.TFTsetCursor(10,10);
	myTFT.TFTFontNum(TFTFont_Default);
	myTFT.print("Hello ");
	
	myTFT.TFTFontNum(TFTFont_Thick);
	myTFT.TFTsetCursor(50,10); // Test a int with print 
	myTFT.print(1243);
	
	// Test a int with print inverted size 2
	myTFT.setTextSize(2);
	myTFT.setTextColor(ST7735_RED, ST7735_YELLOW);
	myTFT.TFTfillRectangle(5, 25, 120, 20, ST7735_YELLOW);
	myTFT.TFTsetCursor(5,25);
	myTFT.TFTFontNum(TFTFont_Seven_Seg);
	myTFT.print(-492);
	
	myTFT.TFTsetCursor(65,25); // Test a float 
	myTFT.TFTFontNum(TFTFont_Wide);
	myTFT.print(3.1745 , 1); // print 3.2
	
	myTFT.TFTsetCursor(10,55); // Test float bignum font
	myTFT.TFTFontNum(TFTFont_Bignum);
	myTFT.print(5.16);
	
	myTFT.TFTsetCursor(10,95); // Test float  mednum font
	myTFT.setTextColor(ST7735_WHITE, ST7735_BLACK);
	myTFT.TFTFontNum(TFTFont_Mednum);
	myTFT.print(76.88);
	
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);

	// Test print with DEC BIN OCT HEX 
	myTFT.TFTFontNum(TFTFont_HomeSpun);
	myTFT.TFTsetCursor(5,5); 
	myTFT.print(numPos , DEC); // 47
	myTFT.TFTsetCursor(5,25); 
	myTFT.print(numPos , BIN); // 10111
	myTFT.TFTsetCursor(5,45); 
	myTFT.print(numPos , OCT); // 57
	myTFT.TFTsetCursor(5,65); 
	myTFT.print(numPos , HEX); // 2F

	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void Test1E(void)
{
	// Note fonts 7 and 8 are numbers only + : 
	char teststr1[] = "12:81";
	char teststr2[] = "72:83";
	
	myTFT.TFTFontNum(TFTFont_Bignum);
	myTFT.TFTdrawCharNumFont(0, 0, '6',  ST7735_RED, ST7735_BLACK);
	myTFT.TFTdrawTextNumFont(0, 40, teststr1, ST7735_YELLOW, ST7735_RED);
	
	myTFT.TFTFontNum(TFTFont_Mednum);
	myTFT.TFTdrawCharNumFont(0, 75, '7',  ST7735_WHITE, ST7735_BLACK);
	myTFT.TFTdrawTextNumFont(0, 100, teststr2, ST7735_GREEN, ST7735_RED);
	
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void Test2(void) {
	myTFT.TFTFontNum(TFTFont_Default);
	char teststr1[] = "Size2";
	myTFT.TFTdrawText(0, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 2);
	myTFT.TFTdrawChar(0, 25, '3', ST7735_WHITE, ST7735_BLACK, 3);
	myTFT.TFTdrawChar(0, 55, '4', ST7735_WHITE, ST7735_BLACK, 4);
	myTFT.TFTdrawChar(0, 85, '5', ST7735_WHITE, ST7735_BLACK, 5);

	TFT_MILLISEC_DELAY(TEST_DELAY2);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void Test3(void)  
{
	myTFT.TFTdrawPixel(85, 5, ST7735_WHITE);
	myTFT.TFTdrawPixel(87, 7, ST7735_WHITE);
	myTFT.TFTdrawPixel(89, 9, ST7735_WHITE);
	myTFT.TFTdrawLine(10, 10, 30, 30, ST7735_RED);
	myTFT.TFTdrawFastVLine(40, 40, 40, ST7735_GREEN);
	myTFT.TFTdrawFastHLine(60, 60, 40, ST7735_YELLOW);

	TFT_MILLISEC_DELAY(TEST_DELAY2);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void Test4(void) {
	myTFT.TFTdrawRectWH(5, 5, 20, 20, ST7735_RED);
	myTFT.TFTfillRectangle(45, 5, 20, 20, ST7735_YELLOW);
	myTFT.TFTfillRect(85, 5, 20, 20, ST7735_GREEN);
	myTFT.TFTdrawRoundRect(15, 60, 50, 50, 5, ST7735_CYAN);
	myTFT.TFTfillRoundRect(70, 60, 50, 50, 10, ST7735_WHITE);

	TFT_MILLISEC_DELAY(TEST_DELAY2);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void Test5(void) {
	myTFT.TFTdrawCircle(40, 20, 15, ST7735_GREEN);
	myTFT.TFTfillCircle(80, 20, 15, ST7735_YELLOW);
}

void Test6(void) {
	myTFT.TFTdrawTriangle(5, 80, 50, 40, 95, 80, ST7735_CYAN);
	myTFT.TFTfillTriangle(55, 120, 100, 90, 127, 120, ST7735_RED);

	TFT_MILLISEC_DELAY(TEST_DELAY2);
	myTFT.TFTfillScreen(ST7735_BLACK);
}


void Test7(void) 
{
	const uint8_t LINES = 10, LINE_SIZE = 10, LINE_OFFSET = 3, TOP_FIXED = 0, BOTTOM_FIXED = 0;
	char teststr1[] = "Scroll test";
	
	for (uint8_t i = 0; i < LINES; i++)
	{
	myTFT.TFTdrawText(0, LINE_OFFSET+i*LINE_SIZE,teststr1 , ST7735_WHITE, ST7735_BLACK, 1);
	}
	myTFT.TFTsetScrollDefinition(TOP_FIXED,BOTTOM_FIXED,1);  // bottom-to-top
	uint8_t pos = LINE_OFFSET;
	for (uint8_t i = 0; i < LINES; i++) 
	{
	for (uint8_t j = 0; j < LINE_SIZE; j++) 
	{
		myTFT.TFTVerticalScroll(pos + TOP_FIXED);
		pos++;
		// check pos if necessary: must be < tftTFT_HEIGHT - TOP_FIXED - BOTTOM_FIXED
		TFT_MILLISEC_DELAY(15);  
	}
	TFT_MILLISEC_DELAY(TEST_DELAY1);
	}
	myTFT.TFTchangeMode(TFT_Normal_mode); 
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void Test8() 
{
	char teststr1[] = "Press Play";
	//Draw play button 
	myTFT.TFTfillRoundRect(25, 10, 78, 60, 8, ST7735_WHITE);
	myTFT.TFTfillTriangle(42, 20, 42, 60, 90, 40, ST7735_RED);
	myTFT.TFTdrawText(5, 80, teststr1, ST7735_GREEN, ST7735_BLACK, 2);
	TFT_MILLISEC_DELAY(TEST_DELAY1);
	
	// change play color
	myTFT.TFTfillTriangle(42, 20, 42, 60, 90, 40, ST7735_BLUE);
	TFT_MILLISEC_DELAY(TEST_DELAY1);
	// change play color
	myTFT.TFTfillTriangle(42, 20, 42, 60, 90, 40, ST7735_GREEN);
	TFT_MILLISEC_DELAY(TEST_DELAY1);
}

void Test9()
{
	char teststr0[] = "Rotate 0"; //normal
	char teststr1[] = "Rotate 90"; // 90
	char teststr2[] = "Rotate 180"; // 180
	char teststr3[] = "Rotate 270"; // 270
	
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTsetRotation(TFT_Degrees_0);
	myTFT.TFTdrawText(20, 20, teststr0, ST7735_GREEN, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY2);
	
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTsetRotation(TFT_Degrees_90);
	myTFT.TFTdrawText(20, 20, teststr1, ST7735_GREEN, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY2);
	
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTsetRotation(TFT_Degrees_180);
	myTFT.TFTdrawText(20, 20, teststr2, ST7735_GREEN, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY2);
	
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTsetRotation(TFT_Degrees_270);
	myTFT.TFTdrawText(20, 20, teststr3, ST7735_GREEN, ST7735_BLACK, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY2);
	
	myTFT.TFTsetRotation(TFT_Degrees_0);
	myTFT.TFTchangeMode(TFT_Normal_mode);
	myTFT.TFTfillScreen(ST7735_BLACK);
}

void Test10()
{
	char teststr1[] = "Mode test";
	myTFT.TFTfillRoundRect(25, 10, 78, 60, 8, ST7735_YELLOW);
	myTFT.TFTdrawText(30, 80, teststr1, ST7735_WHITE, ST7735_RED, 1);
	TFT_MILLISEC_DELAY(TEST_DELAY2);
	myTFT.TFTchangeMode(TFT_Normal_mode);
	 TFT_MILLISEC_DELAY(TEST_DELAY2);
	 myTFT.TFTchangeMode(TFT_Invert_mode);
	 TFT_MILLISEC_DELAY(TEST_DELAY2);
	 myTFT.TFTchangeMode(TFT_Normal_mode);
	 TFT_MILLISEC_DELAY(TEST_DELAY2);
	 myTFT.TFTchangeMode(TFT_Display_off_mode);
	 TFT_MILLISEC_DELAY(TEST_DELAY2);
	 myTFT.TFTchangeMode(TFT_Display_on_mode);
	 TFT_MILLISEC_DELAY(TEST_DELAY2);
	 myTFT.TFTchangeMode(TFT_Sleep_mode);
	 TFT_MILLISEC_DELAY(TEST_DELAY2);
	 myTFT.TFTchangeMode(TFT_Normal_mode);
}

void Test11(void)
{
	myTFT.TFTfillScreen(ST7735_BLACK);

	// Tets variables 
	uint16_t count=CLOCK_DISPLAY_TIME;
	char strCount[5];
	char strTime[9];
	char strName[8] = "G Lyons";
	uint8_t Hour = 10;
	uint8_t Min = 05;
	uint8_t Sec = 30;
	unsigned long previousMillis = 0;  // will store last time display was updated
	const long interval = 1000;  //   interval at which to update display (milliseconds)

	// All icons data vertically addressed 
	//power icon, 12x8
	const unsigned char powerIcon[12] = {0xff, 0xe7, 0xc3, 0x99, 0xa5, 0xad, 0xad, 0xa5, 0x99, 0xc3, 0xe7, 0xff};
	//lighting symbol, 12x8
	const unsigned char speedIcon[12] = {0xff, 0xff, 0xf7, 0xb3, 0xd1, 0xc0, 0xe0, 0xf4, 0xf6, 0xfe, 0xff, 0xff}; 
	// Mobile icon  16x8px
	const unsigned char SignalIcon[16] = {0x03, 0x05, 0x09, 0xff, 0x09, 0x05, 0xf3, 0x00, 0xf8, 0x00, 0xfc, 0x00, 0xfe, 0x00, 0xff, 0x00};
	// Message icon  16x8px
	const unsigned char MsgIcon[16] = {0x00, 0x00, 0x00, 0xff, 0x85, 0x89, 0x91, 0x91, 0x91, 0x91, 0x89, 0x85, 0xff, 0x00, 0x00, 0x00};
	// Alarm icon  8x8px 
	const unsigned char AlarmIcon[8] ={0x83, 0xbd, 0x42, 0x4a, 0x52, 0x52, 0xbd, 0x83};
	// Battery Icon  16x8px 
	const unsigned char BatIcon[16] = {0x00, 0x00, 0x7e, 0x42, 0x81, 0xbd, 0xbd, 0x81, 0xbd, 0xbd, 0x81, 0xbd, 0xbd, 0x81, 0xff, 0x00};

	// TOP icons box
	myTFT.TFTdrawIcon(2, 2, 16, ST7735_BLACK, ST7735_WHITE, SignalIcon);
	myTFT.TFTdrawIcon(20, 2, 16, ST7735_BLACK, ST7735_WHITE, MsgIcon);
	myTFT.TFTdrawIcon(40, 2, 8, ST7735_BLACK, ST7735_WHITE, AlarmIcon);
	myTFT.TFTdrawIcon(102, 2, 16, ST7735_BLACK, ST7735_WHITE, BatIcon);
	// second box 
	myTFT.TFTdrawIcon(5, 20, 12, ST7735_GREEN , ST7735_BLACK,powerIcon);
	myTFT.TFTdrawIcon(20, 20, 12, ST7735_RED, ST7735_YELLOW, speedIcon);
	myTFT.TFTdrawText(80, 20, strName, ST7735_BLUE, ST7735_BLACK, 1);
	
	// RED section lines
	myTFT.TFTdrawFastHLine(0, 17, 120, ST7735_RED);
	myTFT.TFTdrawFastHLine(0, 32, 120, ST7735_RED);
	myTFT.TFTdrawFastHLine(0, 80, 120, ST7735_RED);
	myTFT.TFTdrawFastHLine(0, 118, 120, ST7735_RED);
	
	myTFT.TFTFontNum(TFTFont_Bignum);
	while(1)
	{
		unsigned long currentMillis = to_ms_since_boot(get_absolute_time());

		if (currentMillis - previousMillis >= interval)
		{
			previousMillis  = currentMillis;
			Sec++;
			if (Sec == 60)
			{
				Min++;
				Sec = 0;
				if (Min == 60)
				{
					Hour++;
					Min = 0;
					if (Hour == 24)Hour, Min , Sec = 0;
				}
			}
			// display Clock
			sprintf(strTime, "%02u:%02u:%02u", Hour , Min ,Sec);
			myTFT.TFTdrawTextNumFont(0, 45, strTime, ST7735_GREEN, ST7735_BLACK);
			// display counter
			sprintf(strCount, "%03d", count);
			myTFT.TFTdrawTextNumFont(0, 85, strCount, ST7735_YELLOW, ST7735_RED);
			count--;
		} // if every second

			
		if(count==1)break;
	} // end of while
		
	TFT_MILLISEC_DELAY(TEST_DELAY2);
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTFontNum(TFTFont_Default);
} //end of test 11


void Test11B(void)
{
	// Values to count frame rate per second
	long previousMillis  = 0;
	long lastFramerate = 0;
	long currentFramerate = 0;
	uint16_t count  = 0;
	uint16_t seconds  = 0;
	uint16_t fps = 0;
	uint16_t shapeColor = 0x2222;
	myTFT.setTextSize(1);

	while(1){

	unsigned long currentMillis = to_ms_since_boot(get_absolute_time());

	if (currentMillis  - previousMillis  >= 1000) // every second
	{
		fps = currentFramerate - lastFramerate;
		lastFramerate = currentFramerate ;
		previousMillis  = currentMillis;
		seconds++;
		shapeColor = rand() % 60000;
		if (count == 5000)return; // end if count gets to 5000
	}
	currentFramerate++;
	count++;
	
	//  ** Code to test ** 
	// print seconds
	myTFT.TFTsetCursor(5,15);
	myTFT.print("Secs :");
	myTFT.TFTsetCursor(50 ,15);
	myTFT.print(seconds);
	// print fps
	myTFT.TFTsetCursor(5,25);
	myTFT.print("FPS :");
	myTFT.TFTsetCursor(50,25);
	myTFT.print(fps);
	//print count
	myTFT.TFTsetCursor(5,35);
	myTFT.print("Count :");
	myTFT.TFTsetCursor(50,35);
	myTFT.print(count);
	// print some graphics
	myTFT.TFTdrawCircle(90, 90, 10, shapeColor);
	myTFT.TFTdrawRectWH(40, 80,20, 20,  shapeColor << 1);
	myTFT.TFTdrawRoundRect(5, 80, 20, 20, 2 , shapeColor >> 1);
	//  **** 
	}
}

void EndTests(void)
{
	char teststr1[] = "Tests over";
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTdrawText(5, 50, teststr1, ST7735_GREEN, ST7735_BLACK, 2);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTPowerDown(); 
}

// *************** EOF ****************
