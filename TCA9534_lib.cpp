/*
 * TCA9534_lib.c
 *
 *  Created on: Apr 29, 2024
 *      Author: NJunker
 *      WIP Library for the TCA9534 GPIO Expander Chip
 */

#include "TCA9534_lib.h"

void Thorlabs_TCA9534::begin(uint8_t addr)
{
	_addr = addr;

	Thorlabs_I2C_setup();
}


bool Thorlabs_TCA9534::write_register(uint8_t reg, uint8_t data)
{
	uint8_t cmd[2];
	int ret;
	//build command word
	cmd[0] = reg;
	cmd[1] = data;
	
	Thorlabs_I2C_begin();
	ret = Thorlabs_I2C_write(cmd, sizeof(cmd));
	Thorlabs_I2C_end();

	if (ret == sizeof(cmd)) {
		return true;
	} else {
		return false;
	}
}

uint8_t Thorlabs_TCA9534::read_register(uint8_t reg)
{
	uint8_t cmd[1];
	uint8_t _read_buf[1];
	//build command word
	cmd[0] = reg;
	
	Thorlabs_I2C_begin();
	Thorlabs_I2C_write(cmd, sizeof(cmd));
	Thorlabs_I2C_end();
	
	Thorlabs_I2C_read(_read_buf, sizeof(_read_buf));
	return _read_buf[0];
}

bool Thorlabs_TCA9534::pinMode(uint8_t pin, pin_mode mode)
{
	uint8_t currentConfig;
	uint8_t newConfig;
	uint8_t pinMask;

	currentConfig = read_register(CONFIG_REGISTER);

	pinMask = ~(1 << pin);
	newConfig = currentConfig & pinMask;
	newConfig |= (mode << pin);
	return write_register(CONFIG_REGISTER, newConfig);
}

bool Thorlabs_TCA9534::invertPin(uint8_t pin, pin_invert inverted)
{
		uint8_t currentConfig;
		uint8_t newConfig;
		uint8_t pinMask;

		currentConfig = read_register(POLARITY_INVERSION_REGISTER);

		pinMask = ~(1 << pin);
		newConfig = currentConfig & pinMask;
		newConfig |= (inverted << pin);
		return write_register(POLARITY_INVERSION_REGISTER, newConfig);
}

bool Thorlabs_TCA9534::writePin(uint8_t pin, pin_level level)
{
	uint8_t currentConfig;
	uint8_t newConfig;
	uint8_t pinMask;

	currentConfig = read_register(OUTPUT_PORT_REGISTER);

	pinMask = ~(1 << pin);
	newConfig = currentConfig & pinMask;
	newConfig |= (level << pin);
	return write_register(OUTPUT_PORT_REGISTER, newConfig);
}

bool Thorlabs_TCA9534::readPin(uint8_t pin)
{
	bool pinStatus;

	uint8_t regStatus = read_register(INPUT_PORT_REGISTER);
	pinStatus = (regStatus >> pin) & 1;

	return pinStatus;
}

uint8_t Thorlabs_TCA9534::readAll()
{
	return read_register(INPUT_PORT_REGISTER);
}

//-----------------------------------------------------------------------
//------------------- To be implemented by user -------------------------
//-----------------------(Platform Specific)-----------------------------
//-----------------------------------------------------------------------

uint8_t Thorlabs_TCA9534::Thorlabs_I2C_write(uint8_t *buf, size_t size) {
	//Implement this in a parent class or modify for your platform

	//Take in an array of single bytes (buf) and length
	//Return length of bytes successfully transmitted
}

void Thorlabs_TCA9534::Thorlabs_I2C_read(uint8_t *buf, size_t size) {
	//Implement this in a parent class or modify for your platform

	//Takes in a pointer to a buffer to place data in, and size of said buffer
}

void Thorlabs_TCA9534::Thorlabs_I2C_begin() {
	//Implement this in a parent class or modify for your platform

	//Used if your platform has an I2C transaction begin function (i.e. Arduino)
}

void Thorlabs_TCA9534::Thorlabs_I2C_end() {
	//Implement this in a parent class or modify for your platform
	
	//Used if your platform has an I2C transaction end function (i.e. Arduino)
}

void Thorlabs_TCA9534::Thorlabs_I2C_setup() {
	//Implement this in a parent class or modify for your platform

	//Platform specific startup code, i.e. setting pins, clock speed, etc
}