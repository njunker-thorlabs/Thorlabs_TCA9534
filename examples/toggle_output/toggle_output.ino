//This example will toggle a single GPIO pin at around 100Hz.

#include <TCA9534_lib.h>

Thorlabs_TCA9534 gpio;

void setup() {
  
  Serial.begin(115200);
  Serial.println("Thorlabs TCA9534 - GPIO Toggle Test");

  gpio.begin(); //Initialize GPIO Expander
  gpio.pinMode(0, gpio.OUT); //Configure GPIO pin 0 as an output

}

void loop() {
  
  gpio.writePin(0, gpio.ON); //Turn on GPIO pin 0
  delay(5);
  gpio.writePin(0, gpio.OFF); //Turn off GPIO pin 0
  delay(5);

}
