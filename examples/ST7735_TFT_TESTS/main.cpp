/*!
	@file main.cpp
	@brief Library test file, tests text & fonts.
	@author Gavin Lyons.
	@note See USER OPTIONS 0-3 in SETUP function
	@details For this test file to work fully the optional fonts 9-12 
		must be enabled which they are by default.
		User can disable these fonts by commenting out the following defines
		-# _font.hpp file _TFT_OPTIONAL_FONT_9 for font 9
		-# _font.hpp file _TFT_OPTIONAL_FONT_10 for font 10
		-# _font.hpp file _TFT_OPTIONAL_FONT_11 for font 11
		-# _font.hpp file _TFT_OPTIONAL_FONT_12 for font 12
	@test
	-# Test 101 print out fonts 1-12
	-# Test 102 defined 16-bit Colors, text
	-# Test 103 print entire ASCII font 0 to 254, default font
	-# Test 104 font sizes + character draw using draw functions
	-# Test 105 print method all fonts
	-# Test 106 Misc print class tests (string object, println invert, wrap, base nums etc)
	-# Test 107 Misc draw functions (Invert, wrap, Error checks etc)
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

void Setup(void);
void Test101(void);
void Test102(void);
void Test103(void);
void Test104(void);
void Test105(void);
void Test106(void);
void Test107(void);
void EndTests(void);
void DisplayReset(void);

//  Section ::  MAIN loop

int main(void)
{
	Setup();
	Test101();
	Test102();
	Test103();
	Test104();
	Test105();
	Test106();
	Test107();

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
	printf("TFT Start\r\n");

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
	@brief Test 101: Print out fonts 1-12 with drawtext 
*/
void Test101(void) {

	printf("Test 101: Print out fonts 1-12 with drawtext\r\n");
	char teststr1[] = "Default 1";
	char teststr2[] = "THICK 2";
	char teststr3[] = "Seven 3";
	char teststr4[] = "WIDE 4";
	char teststr5[] = "Tiny 5";
	char teststr6[] = "Home 6";
	char teststr7[] = "1234";
	char teststr8[] = "123456";
	char teststr9[] = "Arial R 9";
	char teststr10[] = "Arial B 10";
	char teststr11[] = "Mia 11";
	char teststr12[] = "Dedica 12";

	myTFT.TFTfillScreen(ST7735_BLACK);

	myTFT.TFTFontNum(myTFT.TFTFont_Default);
	myTFT.TFTdrawText(5, 2, teststr1, ST7735_WHITE, ST7735_BLACK, 2);
	myTFT.TFTFontNum(myTFT.TFTFont_Thick);
	myTFT.TFTdrawText(5, 20, teststr2, ST7735_GREEN, ST7735_BLACK, 2);
	myTFT.TFTFontNum(myTFT.TFTFont_Seven_Seg);
	myTFT.TFTdrawText(5, 36, teststr3, ST7735_BLUE, ST7735_BLACK, 2);
	myTFT.TFTFontNum(myTFT.TFTFont_Wide);
	myTFT.TFTdrawText(5, 52, teststr4, ST7735_CYAN, ST7735_BLACK, 2);
	myTFT.TFTFontNum(myTFT.TFTFont_Tiny);
	myTFT.TFTdrawText(5, 68, teststr5, ST7735_RED, ST7735_BLACK, 2);
	myTFT.TFTFontNum(myTFT.TFTFont_HomeSpun);
	myTFT.TFTdrawText(5, 84, teststr6, ST7735_YELLOW, ST7735_BLACK, 2);
	DisplayReset();

	myTFT.TFTFontNum(myTFT.TFTFont_Bignum);
	myTFT.TFTdrawText(5, 2, teststr7, ST7735_WHITE, ST7735_BLACK);
	myTFT.TFTFontNum(myTFT.TFTFont_Mednum);
	myTFT.TFTdrawText(5, 33, teststr8, ST7735_GREEN, ST7735_BLACK);
	myTFT.TFTFontNum(myTFT.TFTFont_ArialRound);
	myTFT.TFTdrawText(5, 50, teststr9, ST7735_BLUE, ST7735_BLACK);
	myTFT.TFTFontNum(myTFT.TFTFont_ArialBold);
	myTFT.TFTdrawText(5, 74, teststr10, ST7735_CYAN, ST7735_BLACK);
	myTFT.TFTFontNum(myTFT.TFTFont_Mia);
	myTFT.TFTdrawText(5, 91, teststr11, ST7735_RED, ST7735_BLACK);
	myTFT.TFTFontNum(myTFT.TFTFont_Dedica);
	myTFT.TFTdrawText(5, 106, teststr12, ST7735_YELLOW, ST7735_BLACK);
	DisplayReset();

}

/*!
	@brief Test 102: Some of the Defined 16-bit Colors for text
*/
void Test102(void) {
	printf("Test 102: Some of the Defined 16-bit Colors for text\r\n");
	myTFT.TFTFontNum(myTFT.TFTFont_Default);
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
	char teststr11[] = "ORANGE";
	char teststr12[] = "DGREEN";

	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 15, teststr2, ST7735_BLUE, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 25, teststr3, ST7735_RED, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 35, teststr4, ST7735_GREEN, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 45, teststr5, ST7735_CYAN, ST7735_BLACK, 1);
	myTFT.TFTdrawText(5, 55, teststr6, ST7735_MAGENTA, ST7735_BLACK, 1);
	myTFT.TFTdrawText(60, 5, teststr7, ST7735_YELLOW, ST7735_BLACK, 1);
	myTFT.TFTdrawText(60, 15, teststr8, ST7735_GREY, ST7735_BLACK, 1);
	myTFT.TFTdrawText(60, 25, teststr9, ST7735_TAN, ST7735_BLACK, 1);
	myTFT.TFTdrawText(60, 35, teststr10 , ST7735_BROWN, ST7735_BLACK, 1);
	myTFT.TFTdrawText(60, 45, teststr11 , ST7735_ORANGE, ST7735_BLACK, 1);
	myTFT.TFTdrawText(60, 55, teststr12, ST7735_DGREEN, ST7735_BLACK, 1);

	DisplayReset();
}

/*!
	@brief Test 103: Print entire ASCII font 0 to 254, default font
*/
void Test103(void) {
	printf("Test 103: Print entire ASCII font 0 to 254, default font\r\n");
	uint8_t row = 5;
	uint8_t col = 5;
	for (char i = 0; i < 126; i++) {

		myTFT.TFTdrawChar(col, row, i, ST7735_GREEN, ST7735_BLACK, 1);
		col += 10;
		if (col > 115) {
			row += 10;
			col = 5;
		}
	}
	DisplayReset();

	row = 5;
	col = 5;
	for (unsigned char j = 127; j < 254; j++) {

		myTFT.TFTdrawChar(col, row, j, ST7735_GREEN, ST7735_BLACK, 1);
		col += 10;
		if (col > 115) {
			row += 10;
			col = 5;
		}
	}
	DisplayReset();
}


/*!
	@brief Test 104: font sizes (2-5) + character draw using draw functions
*/
void Test104(void) {
	printf("Test 104: font sizes (2-5) + character draw using draw functions\r\n");
	myTFT.TFTFontNum(myTFT.TFTFont_Default);
	char teststr1[] = "TEST";
	myTFT.TFTdrawText(0, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 2);
	myTFT.TFTdrawText(0, 25, teststr1, ST7735_WHITE, ST7735_BLACK, 3);
	myTFT.TFTdrawText(0, 55, teststr1, ST7735_WHITE, ST7735_BLACK, 4);
	myTFT.TFTdrawChar(0, 85, 'G', ST7735_WHITE, ST7735_BLACK, 5);
	myTFT.TFTdrawChar(45, 85, 'L', ST7735_WHITE, ST7735_BLACK, 5);

	DisplayReset();
}

/*!
	@brief Test 105: Print class methods
*/
void Test105(void)
{
	printf("Test 105: Print class methods\r\n");

	// Test Fonts 1-6

	myTFT.setTextSize(1);
	myTFT.setTextColor(ST7735_WHITE, ST7735_BLACK);

	myTFT.TFTsetCursor(5,5);
	myTFT.TFTFontNum(myTFT.TFTFont_Default);
	myTFT.print("Default ");
	myTFT.print(-43);

	myTFT.TFTsetCursor(5,15);
	myTFT.TFTFontNum(myTFT.TFTFont_Thick);
	myTFT.print("THICK ");
	myTFT.print(123.284,1); // print 123.2

	myTFT.TFTsetCursor(5,25);
	myTFT.TFTFontNum(myTFT.TFTFont_Seven_Seg);
	myTFT.print("7 SEG ");
	myTFT.print(747);

	myTFT.TFTsetCursor(5,35);
	myTFT.TFTFontNum(myTFT.TFTFont_Wide);
	myTFT.print("WIDE ");
	myTFT.print(456);

	myTFT.TFTsetCursor(5,45);
	myTFT.TFTFontNum(myTFT.TFTFont_Tiny);
	myTFT.print("Tiny!  ");
	myTFT.print(-3.14);

	myTFT.TFTsetCursor(5,55);
	myTFT.TFTFontNum(myTFT.TFTFont_HomeSpun);
	myTFT.print("HomeSpun ");
	myTFT.print(6.019,2 );// print 6.02

	DisplayReset();

	// Test Font 7-12

	myTFT.TFTFontNum(myTFT.TFTFont_Bignum); // Test bignum font 7
	myTFT.TFTsetCursor(5,5);
	myTFT.println(-7.16);
	myTFT.print("10:05");

	myTFT.TFTsetCursor(5,70); // Test mednum font 8
	myTFT.TFTFontNum(myTFT.TFTFont_Mednum);
	myTFT.println(-8.16);
	myTFT.print("12:45");

	DisplayReset();

	myTFT.TFTsetCursor(5,5); // Test Arial round font 9
	myTFT.TFTFontNum(myTFT.TFTFont_ArialRound);
	myTFT.println("A rnd");
	myTFT.print(96.78);

	myTFT.TFTsetCursor(5,70); // Test Arial bold font 10
	myTFT.TFTFontNum(myTFT.TFTFont_ArialBold);
	myTFT.println("A bold");
	myTFT.print(12.08);

	DisplayReset();

	myTFT.TFTsetCursor(5,5); // Test 11 Mia
	myTFT.TFTFontNum(myTFT.TFTFont_Mia);
	myTFT.println("Mia Font");
	myTFT.print(1141.23);

	myTFT.TFTsetCursor(10,50); // Test 12 Dedica
	myTFT.TFTFontNum(myTFT.TFTFont_Dedica);
	myTFT.println("Dedica Font");
	myTFT.print(1241.23);

	DisplayReset();

}

/*!
	@brief Test 106: Misc print class(string object, println invert, wrap, base nums
*/
void Test106(void)
{
	printf("Test 106: Misc print class(string object, println invert, wrap, base nums etc)\r\n");
	//Inverted print fonts 1-6
	myTFT.setTextColor(ST7735_RED, ST7735_YELLOW);

	//size 1
	myTFT.setTextSize(1);
	myTFT.TFTsetCursor(5,5);
	myTFT.print("ABCD");

	//size 2
	myTFT.setTextSize(2);
	myTFT.TFTsetCursor(5,15);
	myTFT.TFTFontNum(myTFT.TFTFont_Seven_Seg);
	myTFT.print(-49);
	myTFT.TFTsetCursor(5,35);
	myTFT.TFTFontNum(myTFT.TFTFont_Default);
	myTFT.print(112.09);
	myTFT.TFTsetCursor(5,55);
	myTFT.print("ABCD");

	//size 3
	myTFT.setTextSize(3);
	myTFT.TFTsetCursor(5,85);
	myTFT.TFTFontNum(myTFT.TFTFont_Thick);
	myTFT.print("ER");
	DisplayReset();

	// Inverted print fonts 7-12
	myTFT.setTextColor(ST7735_YELLOW, ST7735_RED);
	myTFT.TFTsetCursor(5,5);
	myTFT.TFTFontNum(myTFT.TFTFont_ArialBold);
	myTFT.print("INVERT");
	myTFT.TFTsetCursor(5,25);
	myTFT.TFTFontNum(myTFT.TFTFont_Mednum);
	myTFT.print(-994.982, 2);
	myTFT.TFTsetCursor(5,45);
	myTFT.TFTFontNum(myTFT.TFTFont_Mia);
	myTFT.print("INVERT");
	myTFT.TFTsetCursor(5,85);
	myTFT.TFTFontNum(myTFT.TFTFont_Dedica);
	myTFT.print(12345678);
	DisplayReset();


	// Test print with DEC BIN OCT HEX
	myTFT.setTextColor(ST7735_WHITE, ST7735_BLACK);
	uint8_t numPos = 47;
	myTFT.TFTFontNum(myTFT.TFTFont_HomeSpun);
	myTFT.setTextSize(2);
	myTFT.TFTsetCursor(5,5);
	myTFT.print(numPos , DEC); // 47
	myTFT.TFTsetCursor(5,25);
	myTFT.print(numPos , BIN); // 10111
	myTFT.TFTsetCursor(5,45);
	myTFT.print(numPos , OCT); // 57
	myTFT.TFTsetCursor(5,65);
	myTFT.print(numPos , HEX); // 2F

	DisplayReset();

	// Test print a string object with print
	myTFT.TFTFontNum(myTFT.TFTFont_Dedica);
	std::string timeInfo = "12:45";
	std::string newLine = "new l";
	myTFT.TFTsetCursor(5, 5);
	myTFT.print(timeInfo);
	// print a new line with println
	myTFT.TFTsetCursor(5,40);
	myTFT.println(newLine); // print a new line feed with println
	myTFT.print(newLine);

	//text wrap with print
	myTFT.TFTsetCursor(5,70);
	myTFT.print("12345678901234567890ABCDEFGHIJ");
	DisplayReset();
}

/*!
	@brief Test 107: Misc draw functions tests invert, wrap, Error checks
*/
void Test107(void)
{
	printf("Test 107: Misc draw functions tests invert, wrap, Error checks etc\r\n");

	//wrap
	char teststr0[] = "123456789";

	myTFT.TFTFontNum(myTFT.TFTFont_Wide);
	myTFT.TFTdrawText(105, 5, teststr0, ST7735_WHITE, ST7735_BLACK, 2);
	myTFT.TFTdrawText(105, 75, teststr0, ST7735_WHITE, ST7735_BLACK, 1);
	DisplayReset();

	myTFT.TFTFontNum(myTFT.TFTFont_Bignum);
	myTFT.TFTdrawText(80, 10, teststr0, ST7735_WHITE, ST7735_BLACK);
	DisplayReset();

	// Error checking
	printf("=== START Error checking. ===\r\n");
	//wrong font
	myTFT.TFTdrawText(105, 5, teststr0, ST7735_WHITE, ST7735_BLACK, 1); //throw error
	myTFT.TFTFontNum(myTFT.TFTFont_Wide);
	myTFT.TFTdrawText(80, 5, teststr0, ST7735_WHITE, ST7735_BLACK);  //throw error

	DisplayReset();

	// character out of font bounds
	// wide & thick lower case + ]
	char testlowercase[] = "ABC]ab";
	char testNonNumExtend[] = "-./12:;,A";
	myTFT.TFTdrawText(5,  5, testlowercase, ST7735_WHITE, ST7735_BLACK, 2); //throw wide font error
	myTFT.TFTFontNum(myTFT.TFTFont_Thick);
	myTFT.TFTdrawText(5, 25, testlowercase, ST7735_WHITE, ST7735_BLACK, 2); //throw thick font error

	// Numeric extened bounds ; , A errors
	myTFT.TFTFontNum(myTFT.TFTFont_Bignum);
	myTFT.TFTdrawText(5, 45, testNonNumExtend, ST7735_WHITE, ST7735_BLACK); //throw bignum font error
	myTFT.TFTFontNum(myTFT.TFTFont_Mednum);
	myTFT.TFTdrawText(5, 75, testNonNumExtend, ST7735_WHITE, ST7735_BLACK); //throw mednum font error
	DisplayReset();

	// screen out of bounds
	myTFT.TFTFontNum(myTFT.TFTFont_Default);
	myTFT.TFTdrawChar(0, 130, 'e', ST7735_WHITE, ST7735_BLACK, 1); //throw error
	myTFT.TFTdrawChar(130, 0, 'f', ST7735_WHITE, ST7735_BLACK, 1); //throw error
	DisplayReset();

	myTFT.TFTFontNum(myTFT.TFTFont_ArialBold);
	myTFT.TFTdrawChar(0, 130, 'A', ST7735_WHITE, ST7735_BLACK); //throw error
	myTFT.TFTdrawChar(130, 0, 'B', ST7735_WHITE, ST7735_BLACK); //throw error
	DisplayReset();
	printf("=== STOP Error checking. ===\r\n");

	//invert + Numeric fonts 1-6 sprintf
	int myInt=931;
	char myStr[5];
	myTFT.TFTFontNum(myTFT.TFTFont_Seven_Seg);
	sprintf(myStr, "%d", myInt);
	myTFT.TFTdrawText(5, 5, myStr, ST7735_BLUE, ST7735_BLACK, 3);

	myTFT.TFTFontNum(myTFT.TFTFont_HomeSpun);
	float  myPI = 3.171592;
	char myStr2[8];
	sprintf(myStr2, "%0.3f", myPI); // 3.172
	myTFT.TFTdrawText(5, 65, myStr2, ST7735_RED, ST7735_BLACK, 3);

	DisplayReset();

	//invert + Numeric fonts 7-12 sprintf
	// Note fonts 7 and 8 are extended numeric only
	// Note Fonts 9 and 10 are Alphanumeric
	char teststr1[] = "12:81";
	char teststr2[] = "72:83";
	char teststr3[] = "9 rnd";
	char teststr4[] = "10 bold";

	myTFT.TFTFontNum(myTFT.TFTFont_Bignum);
	myTFT.TFTdrawChar(2, 2, '7',  ST7735_RED, ST7735_BLACK);
	myTFT.TFTdrawText(2, 40, teststr1, ST7735_YELLOW, ST7735_RED);

	myTFT.TFTFontNum(myTFT.TFTFont_Mednum);
	myTFT.TFTdrawChar(2, 75, '8',  ST7735_WHITE, ST7735_BLACK);
	myTFT.TFTdrawText(2, 100, teststr2, ST7735_GREEN, ST7735_RED);

	DisplayReset();

	myTFT.TFTFontNum(myTFT.TFTFont_ArialRound);
	myTFT.TFTdrawChar(2, 2, '9',  ST7735_RED, ST7735_BLACK);
	myTFT.TFTdrawText(2, 26, teststr3, ST7735_YELLOW, ST7735_RED);

	myTFT.TFTFontNum(myTFT.TFTFont_ArialBold);
	myTFT.TFTdrawChar(2, 56, 'A',  ST7735_WHITE, ST7735_BLACK);
	myTFT.TFTdrawText(2, 90, teststr4, ST7735_GREEN, ST7735_RED);

	DisplayReset();
}

void DisplayReset(void)
{
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
}


/*!
	@brief  Stop testing and shutdown the TFT
*/
void EndTests(void)
{
	char teststr1[] = "Tests over";
	myTFT.TFTFontNum(myTFT.TFTFont_Default);
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTdrawText(5, 50, teststr1, ST7735_GREEN, ST7735_BLACK, 2);
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTPowerDown();
	printf("TFT :: Tests Over");
}

// *************** EOF ****************
