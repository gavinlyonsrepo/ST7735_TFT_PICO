/*!
	@file     ST7735_TFT.cpp
	@author   Gavin Lyons
	@brief    Source file for ST7735_TFT_PICO library. 
			Contains driver methods for ST7735_TFT display 
	@note  See URL for full details.https://github.com/gavinlyonsrepo/ST7735_TFT_PICO
		
*/

#include "../../include/st7735/ST7735_TFT.hpp"
 
/*!
	@brief Constructor for class ST7735_TFT
*/
ST7735_TFT :: ST7735_TFT(){}

/*!
	@brief : Init Hardware SPI
*/
void ST7735_TFT::TFTSPIInitialize(void)
{
	spi_init(_pspiInterface, _speedSPIKHz * 1000); // Initialize SPI port 
	// Initialize SPI pins : clock and data
	TFT_SDATA_SPI_FUNC;
	TFT_SCLK_SPI_FUNC;

    // Set SPI format
    spi_set_format( _pspiInterface,   // SPI instance
                    8,      // Number of bits per transfer
                    SPI_CPOL_0,      // Polarity (CPOL)
                    SPI_CPHA_0,      // Phase (CPHA)
                    SPI_MSB_FIRST);

}

/*!
	@brief: Call when powering down TFT
	@note  Will switch off SPI 
*/
void ST7735_TFT ::TFTPowerDown(void)
{
	TFTchangeMode(TFT_Display_off_mode);
	TFT_DC_SetLow;
	TFT_RST_SetLow;
	TFT_SCLK_SetLow;
	TFT_SDATA_SetLow;
	TFT_CS_SetLow;
	if (_hardwareSPI == true) 
		spi_deinit(_pspiInterface);
}

/*!
	@brief: Method for Hardware Reset pin control
*/
void ST7735_TFT ::TFTResetPIN() {
	TFT_RST_SetDigitalOutput;
	TFT_RST_SetHigh;
	TFT_MILLISEC_DELAY(10);
	TFT_RST_SetLow;
	TFT_MILLISEC_DELAY(10);
	TFT_RST_SetHigh;
	TFT_MILLISEC_DELAY(10);
}

/*!
	@brief  sets up TFT GPIO
	@param rst reset GPIO 
	@param dc data or command GPIO.
	@param cs chip select GPIO 
	@param sclk Data clock GPIO  
	@param din Data to TFT GPIO 
*/
void ST7735_TFT ::TFTSetupGPIO(int8_t rst, int8_t dc, int8_t cs, int8_t sclk, int8_t din)
{
	_TFT_SDATA = din;
	_TFT_SCLK = sclk;
	_TFT_RST= rst;
	_TFT_DC = dc;
	_TFT_CS = cs;

	TFT_SDATA_INIT; 
	TFT_SCLK_INIT; 
	TFT_RST_INIT;
	TFT_DC_INIT; 
	TFT_CS_INIT; 
}

/*!
	@brief: init sub-routine ST7735R Green Tab
*/
void ST7735_TFT ::TFTGreenTabInitialize() {
	TFTResetPIN();
	TFT_DC_SetLow;
	TFT_DC_SetDigitalOutput;
	TFT_CS_SetHigh;
	TFT_CS_SetDigitalOutput;
if (_hardwareSPI == false){
	TFT_SCLK_SetLow;
	TFT_SDATA_SetLow;
	TFT_SCLK_SetDigitalOutput;
	TFT_SDATA_SetDigitalOutput;
}else{
	TFTSPIInitialize();
}
	Rcmd1();
	Rcmd2green();
	Rcmd3();
	TFT_PCBtype = TFT_ST7735R_Green;
}

/*!
	@brief: init sub-routine ST7735R Green Tab
*/
void ST7735_TFT ::Rcmd2green() {
	writeCommand(ST7735_CASET);
	writeData(0x00);
	writeData(0x02);
	writeData(0x00);
	writeData(0x7F + 0x02);
	writeCommand(ST7735_RASET);
	writeData(0x00);
	writeData(0x01);
	writeData(0x00);
	writeData(0x9F + 0x01);
}

/*!
	@brief: ST7735R Red Tab Init Red PCB version
*/
void ST7735_TFT ::TFTRedTabInitialize() {
	TFTResetPIN();
	TFT_DC_SetLow;
	TFT_DC_SetDigitalOutput;
	TFT_CS_SetHigh;
	TFT_CS_SetDigitalOutput;
if (_hardwareSPI == false)
{
	TFT_SCLK_SetLow;
	TFT_SDATA_SetLow;
	TFT_SCLK_SetDigitalOutput;
	TFT_SDATA_SetDigitalOutput;
}else{
	TFTSPIInitialize();
}
	Rcmd1();
	Rcmd2red();
	Rcmd3();
	TFT_PCBtype = TFT_ST7735R_Red;

}

/*!
	@brief: Init Routine ST7735R Black Tab (ST7735S)
*/
void ST7735_TFT ::TFTBlackTabInitialize() {
	TFTResetPIN();
	TFT_DC_SetLow;
	TFT_DC_SetDigitalOutput;
	TFT_CS_SetHigh;
	TFT_CS_SetDigitalOutput;
if (_hardwareSPI == false)
{
	TFT_SCLK_SetLow;
	TFT_SDATA_SetLow;
	TFT_SCLK_SetDigitalOutput;
	TFT_SDATA_SetDigitalOutput;
}else{
	TFTSPIInitialize();
}
	Rcmd1();
	Rcmd2red();
	Rcmd3();
	writeCommand(ST7735_MADCTL);
	writeData(0xC0);
	TFT_PCBtype = TFT_ST7735S_Black ;
}

/*!
	@brief: init routine for ST7735B controller
*/
void ST7735_TFT ::TFTST7735BInitialize() {
	TFTResetPIN();
	TFT_DC_SetLow;
	TFT_DC_SetDigitalOutput;
	TFT_CS_SetHigh;
	TFT_CS_SetDigitalOutput;
if (_hardwareSPI == false)
{
	TFT_SCLK_SetLow;
	TFT_SDATA_SetLow;
	TFT_SCLK_SetDigitalOutput;
	TFT_SDATA_SetDigitalOutput;
}else{
	TFTSPIInitialize();
}
	Bcmd();
	TFT_PCBtype = TFT_ST7735B ;
}

/*!
	@brief: init routine for ST7735B controller
*/
void ST7735_TFT ::Bcmd() {
	uint8_t seq6[] {0x09, 0x16, 0x09, 0x20, 0x21, 0x1B, 0x13, 0x19, 0x17, 0x15, 0x1E, 0x2B, 0x04, 0x05, 0x02, 0x0E}; 
	uint8_t seq7[] {0x0B, 0x14, 0x08, 0x1E, 0x22, 0x1D, 0x18, 0x1E, 0x1B, 0x1A, 0x24, 0x2B, 0x06, 0x06, 0x02, 0x0F}; 
	uint8_t seq8[] { 0x00, 0x02, 0x08, 0x81};
	uint8_t seq9[] { 0x00, 0x01, 0x08, 0xA0};
	writeCommand(ST7735_SWRESET);
	TFT_MILLISEC_DELAY(50);
	writeCommand(ST7735_SLPOUT);
	TFT_MILLISEC_DELAY(500);
	writeCommand(ST7735_COLMOD);
	writeData(0x05);
	TFT_MILLISEC_DELAY(10);
	writeCommand(ST7735_FRMCTR1);
	writeData(0x00);
	writeData(0x06);
	writeData(0x03);
	TFT_MILLISEC_DELAY(10);
	writeCommand(ST7735_MADCTL);
	writeData(0x08);
	writeCommand(ST7735_DISSET5);
	writeData(0x15);
	writeData(0x02);
	writeCommand(ST7735_INVCTR);
	writeData(0x00);
	writeCommand(ST7735_PWCTR1);
	writeData(0x02);
	writeData(0x70);
	TFT_MILLISEC_DELAY(10);
	writeCommand(ST7735_PWCTR2);
	writeData(0x05);
	writeCommand(ST7735_PWCTR3);
	writeData(0x01);
	writeData(0x02);
	writeCommand(ST7735_VMCTR1);
	writeData(0x3C);
	writeData(0x38);
	TFT_MILLISEC_DELAY(10);
	writeCommand(ST7735_PWCTR6);
	writeData(0x11);
	writeData(0x15);
	writeCommand(ST7735_GMCTRP1);
	spiWriteDataBuffer(seq6, sizeof(seq6));
	writeCommand(ST7735_GMCTRN1);
	spiWriteDataBuffer(seq7, sizeof(seq7));
	TFT_MILLISEC_DELAY(10);
	writeCommand(ST7735_CASET);
	spiWriteDataBuffer(seq8, sizeof(seq8));
	writeCommand(ST7735_RASET);
	spiWriteDataBuffer(seq9, sizeof(seq9));
	writeCommand(ST7735_NORON);
	TFT_MILLISEC_DELAY(10);
	writeCommand(ST7735_DISPON);
	TFT_MILLISEC_DELAY(500);
}

/*!
	@brief: init sub-routine
*/
void ST7735_TFT ::Rcmd1() {
	uint8_t seq1[] { 0x01, 0x2C, 0x2D };
	uint8_t seq2[] { 0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D };
	uint8_t seq3[] { 0xA2, 0x02, 0x84 }; 
	writeCommand(ST7735_SWRESET);
	TFT_MILLISEC_DELAY(150);
	writeCommand(ST7735_SLPOUT);
	TFT_MILLISEC_DELAY(500);
	writeCommand(ST7735_FRMCTR1);
	spiWriteDataBuffer(seq1, sizeof(seq1));
	writeCommand(ST7735_FRMCTR2);
	spiWriteDataBuffer(seq1, sizeof(seq1));
	writeCommand(ST7735_FRMCTR3);
	spiWriteDataBuffer(seq2, sizeof(seq2));
	writeCommand(ST7735_INVCTR);
	writeData(0x07);
	writeCommand(ST7735_PWCTR1);
	spiWriteDataBuffer(seq3, sizeof(seq3));
	writeCommand(ST7735_PWCTR2);
	writeData(0xC5);
	writeCommand(ST7735_PWCTR3);
	writeData(0x0A);
	writeData(0x00);
	writeCommand(ST7735_PWCTR4);
	writeData(0x8A);
	writeData(0x2A);
	writeCommand(ST7735_PWCTR5);
	writeData(0x8A);
	writeData(0xEE);
	writeCommand(ST7735_VMCTR1);
	writeData(0x0E);
	writeCommand(ST7735_INVOFF);
	writeCommand(ST7735_MADCTL);
	writeData(0xC8);
	writeCommand(ST7735_COLMOD);
	writeData(0x05);
}
/*!
	@brief: init sub-routine
*/
void ST7735_TFT ::Rcmd2red() {
	uint8_t seq1[] { 0x00, 0x00, 0x00, 0x7F};
	uint8_t seq2[] { 0x00, 0x00, 0x00, 0x9F};
	writeCommand(ST7735_CASET);
	spiWriteDataBuffer(seq1, sizeof(seq1));
	writeCommand(ST7735_RASET);
	spiWriteDataBuffer(seq2, sizeof(seq2));
}

/*!
	@brief: init sub-routine
*/
void ST7735_TFT ::Rcmd3() {
	uint8_t seq4[] {0x02, 0x1C, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2D, 0x29, 0x25, 0x2B, 0x39, 0x00, 0x01, 0x03, 0x10}; 
	uint8_t seq5[] {0x03, 0x1D, 0x07, 0x06, 0x2E, 0x2C, 0x29, 0x2D, 0x2E, 0x2E, 0x37, 0x3F, 0x00, 0x00, 0x02, 0x10}; 
	writeCommand(ST7735_GMCTRP1);
	spiWriteDataBuffer(seq4, sizeof(seq4));
	writeCommand(ST7735_GMCTRN1);
	spiWriteDataBuffer(seq5, sizeof(seq5));
	writeCommand(ST7735_NORON);
	TFT_MILLISEC_DELAY(10);
	writeCommand(ST7735_DISPON);
	TFT_MILLISEC_DELAY(100);
}

/*!
	@brief This method defines the Vertical Scrolling Area of the display where:
	@param top_fix_heightTFT describes the Top Fixed Area,
	@param bottom_fix_heightTFT describes the Bottom Fixed Area and
	@param _scroll_direction is scroll direction (0 for top to bottom and 1 for bottom to top).
*/
void ST7735_TFT ::TFTsetScrollDefinition(uint8_t top_fix_heightTFT, uint8_t bottom_fix_heightTFT, bool _scroll_direction) {
	uint8_t scroll_heightTFT;
	scroll_heightTFT = _heightTFT - top_fix_heightTFT - bottom_fix_heightTFT;
	writeCommand(ST7735_VSCRDEF);
	writeData(0x00);
	writeData(top_fix_heightTFT);
	writeData(0x00);
	writeData(scroll_heightTFT);
	writeData(0x00);
	writeData(bottom_fix_heightTFT);
	writeCommand(ST7735_MADCTL);
	if (_scroll_direction) {
		if ((TFT_PCBtype == TFT_ST7735R_Red)  || (TFT_PCBtype == TFT_ST7735R_Green)) {
			writeData(0xD8);
		}
		if (TFT_PCBtype == TFT_ST7735S_Black) {
			writeData(0xD0);
		}
		if (TFT_PCBtype == TFT_ST7735B ) {
			writeData(0x18);
		}
	} else {
		if (((TFT_PCBtype == TFT_ST7735R_Red)  || (TFT_PCBtype == TFT_ST7735R_Green))) {
			writeData(0xC8);
		}
		if (TFT_PCBtype == TFT_ST7735S_Black) {
			writeData(0xC0);
		}
		if (TFT_PCBtype == TFT_ST7735B ) {
			writeData(0x08);
		}
	}
}

/*!
	@brief: This method is used together with the TFTsetScrollDefinition.
*/
void ST7735_TFT ::TFTVerticalScroll(uint8_t _vsp) {
	writeCommand(ST7735_VSCRSADD);
	writeData(0x00);
	writeData(_vsp);
}

/*!
	@brief Toggle the invert mode
	@param invertModeOn true invert on false invert off
*/
void ST7735_TFT ::TFTchangeInvertMode(bool invertModeOn) {
	if(invertModeOn) {
		writeCommand(ST7735_INVON);
	} else {
		writeCommand(ST7735_INVOFF);
	}
}

/*!
	@brief This changes the mode of the display as:
	@param mode enum TFT_mode value
		-# TFT_Normal_mode: Normal mode.
		-# TFT_Partial_mode: Enable partial mode to work in portions of display 
		-# TFT_Idle_mode: Idle_mode consume less current and shows less color
		-# TFT_Sleep_mode: Put display driver section in sleep but rest of the logic works.
		-# TFT_Invert_mode: invert the display
		-# TFT_Display_on_mode: Turn on display
		-# TFT_Display_off_mode: Turn off display
 */
void ST7735_TFT ::TFTchangeMode(TFT_modes_e mode) {
	switch (mode) {
		case TFT_Normal_mode:
			if (_currentMode ==  TFT_Display_off_mode) {//was in off display?
				writeCommand(ST7735_DISPON);
			}
			if (_currentMode == TFT_Idle_mode) {//was in idle?
				writeCommand(ST7735_TFT_Idle_modeOF);
			}
			if (_currentMode == TFT_Sleep_mode) {//was in sleep?
				writeCommand(ST7735_SLPOUT);
				TFT_MILLISEC_DELAY(120);
			}
			if (_currentMode == TFT_Invert_mode) {//was inverted?
				_currentMode = TFT_Normal_mode;
				writeCommand(ST7735_INVOFF);
			}
			writeCommand(ST7735_NORON);
			_currentMode = TFT_Normal_mode;
			break;
		case TFT_Partial_mode:
			writeCommand(ST7735_PTLON);
			_currentMode = TFT_Partial_mode;
			break;
		case TFT_Idle_mode:
			writeCommand(ST7735_TFT_Idle_modeON);
			_currentMode = TFT_Idle_mode;
			break;
		case TFT_Sleep_mode:
			writeCommand(ST7735_SLPIN);
			_currentMode = TFT_Sleep_mode;
			TFT_MILLISEC_DELAY(5);
			return;
		case TFT_Invert_mode:
			writeCommand(ST7735_INVON);
			_currentMode = TFT_Invert_mode;
			break;
		case TFT_Display_on_mode:
			writeCommand(ST7735_DISPON);
			_currentMode = TFT_Display_on_mode;
			break;
		case TFT_Display_off_mode:
			writeCommand(ST7735_DISPOFF);
			_currentMode =  TFT_Display_off_mode;
			break;
	}//switch end
}

/*!
	@brief: change rotation of display.
	@param mode TFT_rotate_e enum
	0 = Normal
	1=  90 rotate
	2 = 180 rotate
	3 =  270 rotate
	@note if on your display colors are wrong after rotate change
	you may have chosen wrong display pcb type.
*/
void ST7735_TFT ::TFTsetRotation(TFT_rotate_e mode) {
	uint8_t madctl = 0;
	uint8_t rotation;
	rotation = mode % 4;
	switch (rotation) {
		case TFT_Degrees_0 :
			if (TFT_PCBtype == TFT_ST7735S_Black ){
				madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MY | ST7735_MADCTL_RGB;
			}else{
				madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MY | ST7735_MADCTL_BGR;
			}
			_widthTFT =_widthStartTFT;
			_heightTFT = _heightStartTFT;
			_XStart = _colstart;
			_YStart = _rowstart;
			break;
		case TFT_Degrees_90:
			if (TFT_PCBtype == TFT_ST7735S_Black )
			{
				madctl = ST7735_MADCTL_MY | ST7735_MADCTL_MV | ST7735_MADCTL_RGB;
			}else{
				madctl = ST7735_MADCTL_MY | ST7735_MADCTL_MV | ST7735_MADCTL_BGR;
			}
			_YStart = _colstart;
			_XStart = _rowstart;
			_widthTFT  =_heightStartTFT;
			_heightTFT = _widthStartTFT;
			break;
		case TFT_Degrees_180:
			if (TFT_PCBtype == TFT_ST7735S_Black)
			{
				madctl = ST7735_MADCTL_RGB;
			}else{
				madctl = ST7735_MADCTL_BGR;
			}
			_XStart = _colstart;
			_YStart = _rowstart;
			_widthTFT =_widthStartTFT;
			_heightTFT = _heightStartTFT;
			break;
		case TFT_Degrees_270:
			if (TFT_PCBtype == TFT_ST7735S_Black){
				madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MV | ST7735_MADCTL_RGB;
			}else{
				madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MV | ST7735_MADCTL_BGR;
			}
			_YStart = _colstart;
			_XStart = _rowstart;
			_widthTFT =_heightStartTFT;
			_heightTFT = _widthStartTFT;
			break;
	}
	writeCommand(ST7735_MADCTL);
	writeData(madctl);
}

/*!
	@brief initialise the variables that define the size of the screen
	@param colOffset Column offset
	@param rowOffset row offset
	@param width_TFT width in pixels
	@param height_TFT height in pixels
	@note  The offsets can be adjusted for any issues with manufacture tolerance/defects
*/
void ST7735_TFT  :: TFTInitScreenSize(uint8_t colOffset, uint8_t rowOffset, uint16_t width_TFT, uint16_t height_TFT)
{
	_colstart = colOffset; 
	_rowstart = rowOffset;
	_XStart = colOffset; 
	_YStart = rowOffset;
	
	_widthTFT = width_TFT;
	_heightTFT = height_TFT;
	_widthStartTFT = width_TFT;
	_heightStartTFT = height_TFT;
}

/*!
	@brief intialise PCBtype
	@param pcbType Enum TFT_PCBtype_e , 4 choices 
*/
void ST7735_TFT  ::TFTInitPCBType(TFT_PCBtype_e pcbType)
{
	uint8_t choice = pcbType;
	switch(choice)
	{
		case TFT_ST7735R_Red : TFTRedTabInitialize(); break;
		case TFT_ST7735R_Green: TFTGreenTabInitialize(); break;
		case TFT_ST7735S_Black: TFTBlackTabInitialize(); break;
		case TFT_ST7735B : TFTST7735BInitialize(); break;
	}
}

/*!
	@brief intialise HW SPI setup
	@param speed_Khz SPI baudrate in Khz , 1000 = 1 Mhz
	@param spi_interface Spi interface, spi0 spi1 etc
	@note method overload used , method 1 hardware SPI 
*/
void ST7735_TFT  :: TFTInitSPIType(uint32_t speed_Khz,  spi_inst_t* spi_interface) 
{
	 _pspiInterface = spi_interface;
	_speedSPIKHz = speed_Khz;
	_hardwareSPI = true;
}

/*!
	@brief intialise SW SPI set
	@param CommDelay SW SPI GPIO delay
	@note method overload used , method 2 software SPI 
*/
void ST7735_TFT ::TFTInitSPIType(uint16_t CommDelay) 
{
	TFTSwSpiGpioDelaySet(CommDelay);
	_hardwareSPI = false;
}

/*!
	@brief Library version number getter
	@return The lib version number eg 171 = 1.7.1
*/
uint16_t ST7735_TFT::TFTLibVerNumGet(void) {return _LibVersionNum;}

/*!
	@brief Freq delay used in SW SPI getter, uS delay used in SW SPI method
	@return The  GPIO communications delay in uS
*/
uint16_t ST7735_TFT::TFTSwSpiGpioDelayGet(void){return _SWSPIGPIODelay;}

/*!
	@brief Freq delay used in SW SPI setter, uS delay used in SW SPI method
	@param CommDelay The GPIO communications delay in uS
*/
void  ST7735_TFT::TFTSwSpiGpioDelaySet(uint16_t CommDelay){_SWSPIGPIODelay = CommDelay;}
//**************** EOF *****************
