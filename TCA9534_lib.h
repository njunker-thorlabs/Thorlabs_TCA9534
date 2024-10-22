/**************************************************************************//**
This I2C driver is used to interface the TI TCA9534 GPIO Expander chip.

   \date          29-April-2024
   \copyright     2024 Thorlabs Spectral Works
   \author       Nicholas Junker (njunker@thorlabs.com)

******************************************************************************/

#ifndef INC_TCA9534_LIB_H_
#define INC_TCA9534_LIB_H_

#include <cstdint> //for uint8_t, etc
#include <cstddef> //for size_t

#define INPUT_PORT_REGISTER 0x00
#define OUTPUT_PORT_REGISTER 0x01
#define POLARITY_INVERSION_REGISTER 0x02
#define CONFIG_REGISTER 0x03

class Thorlabs_TCA9534 {
public:
	//TODO make some nicer functions
	typedef enum {
		OUT,
		IN
	} pin_mode;

	typedef enum {
		OFF,
		ON
	} pin_level;

	typedef enum {
		ORIGINAL,
		INVERTED
	} pin_invert;

	//Initialize object with I2C instance and address.
	void begin(uint8_t addr = 0x38);

	//Set pin mode for pins 0-7. FALSE/0 is output, TRUE/1 is input.
	bool pinMode(uint8_t pin, pin_mode mode);

	//Set polarity inversion for input pins 0-7.
	bool invertPin(uint8_t pin, pin_invert inverted);

	//Set pin high or low for pins 0-7. FALSE/0 is off, TRUE/1 is on.
	bool writePin(uint8_t pin, pin_level level);

	//Read state of a single pin for pins 0-7.
	bool readPin(uint8_t pin);

	//Read state of every pin 0-7 in a single uint8_t.
	uint8_t readAll();

protected:

	uint8_t _addr;

	uint8_t Thorlabs_I2C_write(uint8_t *buf, size_t size) __attribute__((weak));

	void Thorlabs_I2C_read(uint8_t *buf, size_t size) __attribute__((weak));

	void Thorlabs_I2C_begin() __attribute__((weak));

	void Thorlabs_I2C_end() __attribute__((weak));

	void Thorlabs_I2C_setup() __attribute__((weak));

private:

	bool write_register(uint8_t reg, uint8_t data);
	uint8_t read_register(uint8_t reg);
};





#endif /* INC_TCA9534_LIB_H_ */
