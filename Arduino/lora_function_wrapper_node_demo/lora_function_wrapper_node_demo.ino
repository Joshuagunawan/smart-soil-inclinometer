#include "lora_function.hpp"

// Define the instruction code for sending messages
#define SEND 0

/*
===========================================
|| TRANSMIT AND RECEIVE DATA STRUCTURE
===========================================
*/
uint8_t msg_id = 0;
const uint8_t instruction_code = SEND;
uint8_t nodeId = 10;     // Node ID
uint8_t gatewayId = 214; // Selected gateway ID to communicate
uint8_t generalId = 0;   // Node ID for gateway to access every node
uint8_t checkSum = 200;  // Check sum code, must be same with corresponding gateway and its sensor unit group

uint8_t arrayData_1[6] = {1, 1, 2, 2, 3, 3};       // measurement data from current period
uint8_t arrayData_2[6] = {6, 6, 5, 5, 4, 4};       // measurement data from current period
uint8_t arrayData_3[6] = {9, 9, 8, 8, 7, 7};       // measurement data from current period
uint8_t arrayData_4[6] = {10, 10, 11, 11, 12, 12}; // measurement data from current period
uint8_t arrayData_5[6] = {13, 13, 14, 14, 15, 15}; // measurement data from current period
const uint8_t arrayLen_1 = sizeof(arrayData_1);    // measurement data length
const uint8_t arrayLen_2 = sizeof(arrayData_2);    // measurement data length
const uint8_t arrayLen_3 = sizeof(arrayData_3);    // measurement data length
const uint8_t arrayLen_4 = sizeof(arrayData_4);    // measurement data length
const uint8_t arrayLen_5 = sizeof(arrayData_5);    // measurement data length

uint8_t batVol = 100; // battery voltage data

uint8_t transmitData[42] = {
    msg_id, instruction_code,
    gatewayId, gatewayId,
    nodeId,
    batVol,
    checkSum,
    1,
    arrayData_1[0], arrayData_1[1],
    arrayData_1[2], arrayData_1[3],
    arrayData_1[4], arrayData_1[5],
    2,
    arrayData_2[0], arrayData_2[1],
    arrayData_2[2], arrayData_2[3],
    arrayData_2[4], arrayData_2[5],
    3,
    arrayData_3[0], arrayData_3[1],
    arrayData_3[2], arrayData_3[3],
    arrayData_3[4], arrayData_3[5],
    4,
    arrayData_4[0], arrayData_4[1],
    arrayData_4[2], arrayData_4[3],
    arrayData_4[4], arrayData_4[5],
    5,
    arrayData_5[0], arrayData_5[1],
    arrayData_5[2], arrayData_5[3],
    arrayData_5[4], arrayData_5[5]};              // Transmit data: Byte array data to send using LoRa wireless
const uint8_t transmitLen = sizeof(transmitData); // Transmit data length

void setup()
{
  Serial.begin(SERIAL_FREQ);
  while (!Serial)
    ;
  Serial.println("Node controller demo");

  setupLora();
}

/*
==============================
|| MAIN FUNCTION
==============================
*/

void loop()
{
  // transmit data
  transmitFunction(transmitData, 42);
  delay(3000);
}
