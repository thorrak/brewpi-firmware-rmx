/* Copyright (C) 2019 Lee C. Bussy (@LBussy)

This file is part of LBussy's BrewPi Firmware Remix (BrewPi-Firmware-RMX).

BrewPi Firmware RMX is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

BrewPi Firmware RMX is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with BrewPi Firmware RMX. If not, see <https://www.gnu.org/licenses/>.

These scripts were originally a part of firmware, a part of
the BrewPi project. Legacy support (for the very popular Arduino
controller) seems to have been discontinued in favor of new hardware.

All credit for the original firmware goes to @elcojacobs,
@m-mcgowan, @elnicoCZ, @ntfreak, @Gargy007 and I'm sure many more
contributors around the world. My apologies if I have missed anyone;
those were the names listed as contributors on the Legacy branch.

See: 'original-license.md' for notes about the original project's
license and credits. */

#include "TwiLcdDriver.h"
#include <Brewpi.h>
#include <Pins.h>

#if BREWPI_LCD_TYPE == BREWPI_DISPLAY_TWI_LCD

#include "SoftI2CMaster.h"

TwiLcdDriver::TwiLcdDriver(){
	_Addr = TWI_ADDRESS;
	_cols = 20;
	_rows = 4;
	_backlightval = LCD_NOBACKLIGHT;
}

void TwiLcdDriver::init(){
	init_priv();
	_backlightTime = 0;
}

void TwiLcdDriver::init_priv()
{
	i2c_init();
	i2c_start((_Addr << 1) | I2C_WRITE);
	_displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
	begin(_cols, _rows);
}

void TwiLcdDriver::begin(uint8_t cols, uint8_t lines, uint8_t dotsize) {
	if (lines > 1) {
		_displayfunction |= LCD_2LINE;
	}

	_numlines = lines;
	_currline = 0;
	_currpos = 0;


	delay(50);

	// Now we pull both RS and R/W low to begin commands
	expanderWrite(_backlightval);	// reset expanderand turn backlight off (Bit 8 =1)
	delay(1000);

	// this is according to the hitachi HD44780 datasheet
	// we start in 8bit mode, try to set 4 bit mode
	write4bits(0x03 << 4); // set to 8-bit
	delayMicroseconds(4500); // wait min 4.1ms
	write4bits(0x03 << 4); // set to 8-bit
	delayMicroseconds(4500); // wait min 4.1ms
	write4bits(0x03 << 4);
	delayMicroseconds(150);
	write4bits(0x02 << 4);


	// set # lines, font size, etc.
	command(LCD_FUNCTIONSET | _displayfunction);

	// turn the display on with no cursor or blinking default
	_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	display();

	// clear it off
	clear();

	// Initialize to default text direction (for roman languages)
	_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;

	// set the entry mode
	command(LCD_ENTRYMODESET | _displaymode);

	home();

}

/********** high level commands, for the user! */
void TwiLcdDriver::clear(){
	command(LCD_CLEARDISPLAY);// clear display, set cursor position to zero

	for(uint8_t i = 0; i < _rows; i++){
		for(uint8_t j = 0; j < _cols; j++){
			content[i][j]=' '; // initialize on all spaces
		}
		content[i][_cols]='\0'; // NULL terminate string
	}

	delayMicroseconds(2000);  // this command takes a long time!
}

void TwiLcdDriver::home(){
	command(LCD_RETURNHOME);  // set cursor position to zero
	delayMicroseconds(2000);  // this command takes a long time!
}

void TwiLcdDriver::setCursor(uint8_t col, uint8_t row){
	int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	if ( row > _numlines ) {
		row = _numlines-1;    // we count rows starting w/0
	}

	_currline = row;
	_currpos = col;
	command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// Turn the display on/off (quickly)
void TwiLcdDriver::noDisplay() {
	_displaycontrol &= ~LCD_DISPLAYON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void TwiLcdDriver::display() {
	_displaycontrol |= LCD_DISPLAYON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void TwiLcdDriver::noCursor() {
	_displaycontrol &= ~LCD_CURSORON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void TwiLcdDriver::cursor() {
	_displaycontrol |= LCD_CURSORON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
void TwiLcdDriver::noBlink() {
	_displaycontrol &= ~LCD_BLINKON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void TwiLcdDriver::blink() {
	_displaycontrol |= LCD_BLINKON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void TwiLcdDriver::scrollDisplayLeft(void) {
	command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void TwiLcdDriver::scrollDisplayRight(void) {
	command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void TwiLcdDriver::leftToRight(void) {
	_displaymode |= LCD_ENTRYLEFT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void TwiLcdDriver::rightToLeft(void) {
	_displaymode &= ~LCD_ENTRYLEFT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
void TwiLcdDriver::autoscroll(void) {
	_displaymode |= LCD_ENTRYSHIFTINCREMENT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void TwiLcdDriver::noAutoscroll(void) {
	_displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void TwiLcdDriver::createChar(uint8_t location, uint8_t charmap[]) {
	location &= 0x7; // we only have 8 locations 0-7
	command(LCD_SETCGRAMADDR | (location << 3));
	for (int i=0; i<8; i++) {
		write(charmap[i]);
	}
}

// Turn the (optional) backlight off/on
void TwiLcdDriver::noBacklight(void) {
	_backlightval=LCD_NOBACKLIGHT;
	expanderWrite(0);
}

void TwiLcdDriver::backlight(void) {
	_backlightval=LCD_BACKLIGHT;
	expanderWrite(0);
}

/*********** mid level commands, for sending data/cmds */

inline void TwiLcdDriver::command(uint8_t value) {
	send(value, 0);
}

inline size_t TwiLcdDriver::write(uint8_t value) {
	content[_currline][_currpos] = value;
	_currpos++;
	if (!_bufferOnly) {
		send(value, Rs);
	}
	return 0;
}

/************ low level data pushing commands **********/

// write either command or data
void TwiLcdDriver::send(uint8_t value, uint8_t mode) {
	uint8_t highnib=value&0xf0;
	uint8_t lownib=(value<<4)&0xf0;
	write4bits((highnib)|mode);
	write4bits((lownib)|mode);
}

void TwiLcdDriver::write4bits(uint8_t value) {
	expanderWrite(value);
	pulseEnable(value);
}

void TwiLcdDriver::expanderWrite(uint8_t _data) {
	uint8_t data = ((uint8_t)(_data) | _backlightval);
	i2c_start_wait((_Addr << 1) | I2C_WRITE);
	i2c_write(data);
	i2c_stop();
}

void TwiLcdDriver::pulseEnable(uint8_t _data){
	expanderWrite(_data | En);	// En high
	delayMicroseconds(1);		// enable pulse must be >450ns

	expanderWrite(_data & ~En);	// En low
	delayMicroseconds(50);		// commands need > 37us to settle
}

void TwiLcdDriver::resetBacklightTimer(void) {
	_backlightTime = ticks.seconds();
}

void TwiLcdDriver::updateBacklight(void) {
	// True = OFF, False = ON
	bool backLightOutput = BREWPI_SIMULATE || (BACKLIGHT_AUTO_OFF_PERIOD != 0 && ticks.timeSince(_backlightTime) > BACKLIGHT_AUTO_OFF_PERIOD);
	if(backLightOutput) {
		noBacklight();
		} else {
		backlight();
	}
}

// Puts the content of one LCD line into the provided buffer.
void TwiLcdDriver::getLine(uint8_t lineNumber, char * buffer){
	const char* src = content[lineNumber];
	for(uint8_t i = 0; i < _cols;i++){
		char c = src[i];
		buffer[i] = (c == 0b11011111) ? 0xB0 : c;
	}
	buffer[_cols] = '\0'; // NULL terminate string
}

void TwiLcdDriver::printSpacesToRestOfLine(void){
	while(_currpos < _cols){
		print(' ');
	}
}

#ifndef print_P_inline
void TwiLcdDriver::print_P(const char * str){ // print a string stored in PROGMEM
	char buf[21]; // create buffer in RAM
	strcpy_P(buf, str); // copy string to RAM
	print(buf); // print from RAM
}
#endif
#endif
