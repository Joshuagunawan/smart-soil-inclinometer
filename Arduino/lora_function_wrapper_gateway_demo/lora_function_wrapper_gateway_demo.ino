#include "lora_function.hpp"

char buffer[STRING_BUFFER_LENGTH] = "";

void setup()
{
  Serial.begin(SERIAL_FREQ);
  while (!Serial);

  Serial.println("Gateway controller demo");

  setupLora();
}

/*
======================================
|| MAIN FUNCTION
======================================
*/

void loop()
{
  DataMessage dataMessage;
  receiveAndParseDataMessage(&dataMessage);
  
  if (strncmp(buffer, "null", 4))
  {
    // If message received, the buffer will be updated therefore print the buffer
    Serial.print("buffer: ");
    Serial.println(buffer);
  }
  // Reset the Buffer
  sprintf(buffer, "null");

  delay(20);
}
