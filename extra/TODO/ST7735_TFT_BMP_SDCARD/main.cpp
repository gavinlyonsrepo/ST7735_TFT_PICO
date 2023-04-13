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

// Section :: Defines   
//  Test timing related defines 
#define TEST_DELAY1 1000
#define TEST_DELAY2 2000
#define TEST_DELAY5 5000

// Section :: Globals 
ST7735_TFT myTFT;
bool bTestFPS = false; // Optional ,runs FPS test at end if true.

//  Section ::  Function Headers 

void Setup(void);  // setup + user options
void Test16(void); // 24 color bitmap
void Test17(void); // 16 color bitmap 
void TestFPS(void); // Frames per second 24 color bitmap test, optional
void EndTests(void);

//int64_t getTime(); // Utility for FPS test
//uint8_t* loadImage(char* name); // Utility for FPS test

//  Section ::  MAIN 

int main(void) 
{
	
	Setup();
	Test16();
	Test17();
	//if (bTestFPS == true) TestFPS();
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

// All files Windows BITMAPINFOHEADER offset 54
void Test16(void)
{
	myTFT.TFTfillScreen(ST7735_BLACK);
	char teststr1[] = "Bitmap 24";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 2);
	TFT_MILLISEC_DELAY(TEST_DELAY2);
	
	FILE *pFile ;
	
	size_t pixelSize = 3;
	unsigned char bmpBuffer[(128 * 128) * pixelSize ];
	
	pFile = fopen("bitmap/24pic1.bmp", "r");
	if (pFile == NULL) 
	{
		printf("Test 14A :: File does not exist\n");
		return;
	}
	fseek(pFile, 54, 0);
	fread(bmpBuffer, pixelSize, 128 * 128, pFile);
	fclose(pFile);

	myTFT.TFTdrawBitmap24(0, 0, bmpBuffer, 128, 128);

	TFT_MILLISEC_DELAY(TEST_DELAY5);
	
	pFile = fopen("bitmap/24pic2.bmp", "r");
	if (pFile == NULL) {
		printf("Test 14B :: File does not exist\n");
		return;
	}
	fseek(pFile, 54, 0);
	fread(bmpBuffer, pixelSize, 128 * 128, pFile);
	fclose(pFile);

	myTFT.TFTdrawBitmap24(0, 0, bmpBuffer, 128, 128);

	TFT_MILLISEC_DELAY(TEST_DELAY5);
	
	pFile = fopen("bitmap/24pic3.bmp", "r");
	if (pFile == NULL) {
		printf("Test 14C ::File does not exist\n");
		return;
	}
	fseek(pFile, 54, 0);
	fread(bmpBuffer, pixelSize, 128 * 128, pFile);
	fclose(pFile);

	myTFT.TFTdrawBitmap24(0, 0, bmpBuffer, 128, 128);
	
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
	
}


void Test17(void)
{
	myTFT.TFTfillScreen(ST7735_BLACK);
	char teststr1[] = "Bitmap 16";
	myTFT.TFTdrawText(5, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 2);
	TFT_MILLISEC_DELAY(TEST_DELAY2);
	
	FILE *pFile ;
	size_t pixelSize = 2;
	unsigned char bmpBuffer1[(128 * 128) * pixelSize ];
	
	// File 1  BITMAPV5HEADER offset 132
	// made in GIMP , Color space information written 
	// RGB 565 16 bit color
	pFile = fopen("bitmap/16pic1.bmp", "r");
	if (pFile == NULL) {
		printf("Test 15A ::File does not exist\n");
		return;
	}
	fseek(pFile, 132, 0);
	fread(bmpBuffer1, pixelSize, 128 * 128, pFile);
	fclose(pFile);
	myTFT.TFTdrawBitmap16(0, 0, bmpBuffer1, 128, 128);
	
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	
	// file 2 OS/2 OS22XBITMAPHEADER (BITMAPINFOHEADER2) offset 72
	// made in GIMP Color,  NO color space information written 
	// RGB 565 16 bit color
	pFile = fopen("bitmap/16pic2.bmp", "r");
	if (pFile == NULL) {
		printf("Test 15B :: File does not exist\n");
		return;
	}
	fseek(pFile, 72, 0);
	fread(bmpBuffer1, pixelSize, 128 * 128, pFile);
	fclose(pFile);
	myTFT.TFTdrawBitmap16(0, 0, bmpBuffer1, 128, 128);
	
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	
	// file 3 OS/2 OS22XBITMAPHEADER (BITMAPINFOHEADER2) offset 72
	// made in GIMP Color NO color space information written 
	// RGB 565 16 bit color
	pFile = fopen("bitmap/16pic3.bmp", "r");
	if (pFile == NULL) {
		printf("Test 15C :: File does not exist\n");
		return;
	}
	fseek(pFile, 72, 0);
	fread(bmpBuffer1, pixelSize, 128 * 128, pFile);
	fclose(pFile);
	myTFT.TFTdrawBitmap16(0, 0, bmpBuffer1, 128, 128);
	
	TFT_MILLISEC_DELAY(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
	
}

/*
void TestFPS(void) {
	// Clear The Screen
	myTFT.TFTfillRectangle(0, 0, 160, 80, ST7735_BLACK);

	// Load images into buffers
	uint8_t* img[5] = { 
		loadImage((char*)"bitmap/title.bmp"),
		loadImage((char*)"bitmap/menu.bmp"),
		loadImage((char*)"bitmap/game1.bmp"),
		loadImage((char*)"bitmap/game2.bmp"),
		loadImage((char*)"bitmap/game3.bmp")
	};

	int64_t start = getTime(), duration = 0;
	uint32_t frames = 0;
	double fps = 0;

	// Run for ~10sec
	while(duration < 10000000) {
		myTFT.TFTdrawBitmap24(0, 0, img[frames % 5], 160, 80);

		duration = getTime() - start;

		if((++frames % 50) == 0) {
			fps = (double)frames / ((double)duration / 1000000);
			printf("%.2ffps\n", fps);
		}
	}

	// Get final Stats and print
	duration = getTime() - start;
	fps = (double)frames / ((double)duration / 1000000);
	printf("%d frames, %lld sec, %.2f fps\n", frames, duration / 1000000, fps);

	// Free Up Buffers
	for(int i=0; i<5; i++) free(img[i]);
}

int64_t getTime() {
	struct timespec tms;
	if (clock_gettime(CLOCK_REALTIME,&tms)) return -1;
	int64_t micros = tms.tv_sec * 1000000;
	micros += tms.tv_nsec/1000;
	if (tms.tv_nsec % 1000 >= 500) ++micros;
	return micros;
}

uint8_t* loadImage(char* name) {
	FILE *pFile ;
	size_t pixelSize = 3;
	uint8_t* bmpBuffer1 = NULL;

	pFile = fopen(name, "r");
	if (pFile == NULL) {
		printf("TESTFPS :: File does not exist\n");
	} else {
		bmpBuffer1 = (uint8_t*)malloc((160 * 80) * pixelSize);
		fseek(pFile, 132, 0);
		fread(bmpBuffer1, pixelSize, 160 * 80, pFile);
		fclose(pFile);
	}
	
	return bmpBuffer1;
}
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
