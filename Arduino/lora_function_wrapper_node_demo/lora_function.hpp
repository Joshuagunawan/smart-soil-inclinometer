#ifndef LORA_FUNCTION_H
#define LORA_FUNCTION_H

#include <stdint.h>
#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

/*
=============================
|| CONSTANT DEFINITION
=============================
*/
#define SERIAL_FREQ 9600
#define STRING_BUFFER_LENGTH 256
#define RECEIVE_LEN 42 // Estimated of Received LENGTH
#define INSTRUCTION_DATA_LEN 24

/*
=============================
|| WIRELESS SETUP
=============================
*/
#define LORA_OPERATING_FREQUENCY 915E6 // LoRa wireless communication frequency
#define CS_PIN 10                      // LoRa radio chip select
#define RESET_PIN 9                    // LoRa radio reset
#define IRQ_PIN 2                      // change for your board; must be a hardware interrupt pin
#define RX_PIN 7                       // setup only for e-byte E-19 LoRa module. Must set to LOW when transmit and HIGH when receive
#define TX_PIN 8                       // setup only for e-byte E-19 LoRa module. Must set to HIGH when transmit and LOW when receive

/*
============================
|| MESSAGE STRUCTURE
============================
*/
#define MSG_ID_IDX 0
#define INSTRUCTION_CODE_IDX 1
#define GATE_ID_HB_IDX 2
#define GATE_ID_LB_IDX 3
#define NODE_ID_IDX 4
#define BATT_IDX 5
#define CHECKSUM_IDX 6
#define SID_1_IDX 7
#define ACC_X_1_HB_IDX 8
#define ACC_X_1_LB_IDX 9
#define ACC_Y_1_HB_IDX 10
#define ACC_Y_1_LB_IDX 11
#define ACC_Z_1_HB_IDX 12
#define ACC_Z_1_LB_IDX 13
#define SID_2_IDX 14
#define ACC_X_2_HB_IDX 15
#define ACC_X_2_LB_IDX 16
#define ACC_Y_2_HB_IDX 17
#define ACC_Y_2_LB_IDX 18
#define ACC_Z_2_HB_IDX 19
#define ACC_Z_2_LB_IDX 20
#define SID_3_IDX 21
#define ACC_X_3_HB_IDX 22
#define ACC_X_3_LB_IDX 23
#define ACC_Y_3_HB_IDX 24
#define ACC_Y_3_LB_IDX 25
#define ACC_Z_3_HB_IDX 26
#define ACC_Z_3_LB_IDX 27
#define SID_4_IDX 28
#define ACC_X_4_HB_IDX 29
#define ACC_X_4_LB_IDX 30
#define ACC_Y_4_HB_IDX 31
#define ACC_Y_4_LB_IDX 32
#define ACC_Z_4_HB_IDX 33
#define ACC_Z_4_LB_IDX 34
#define SID_5_IDX 35
#define ACC_X_5_HB_IDX 36
#define ACC_X_5_LB_IDX 37
#define ACC_Y_5_HB_IDX 38
#define ACC_Y_5_LB_IDX 39
#define ACC_Z_5_HB_IDX 40
#define ACC_Z_5_LB_IDX 41
#define MESSAGE_LENGTH 42

typedef struct
{
  uint8_t id;
  uint16_t accelerometer_x;
  uint16_t accelerometer_y;
  uint16_t accelerometer_z;
} SensorData;

typedef struct
{
  uint8_t message_id;
  uint8_t instruction_code;
  uint16_t gateway_id;
  uint8_t node_id;
  uint8_t battery_voltage;
  uint8_t checksum;
  SensorData sensor[5];
} DataMessage;

typedef struct
{
  uint8_t instruction_id;
  uint16_t gateway_id;
  uint8_t node_id;
  uint8_t sensor_id;
  uint8_t instruction_code;
  uint8_t instruction_data;
  uint8_t checksum;
} InstructionMessage;

// Function Prototype
void setupLora();
void receiveAndParseDataMessage(DataMessage *dataMessage);
void convertDataMessageToHTMLData(DataMessage *dataMessage, char output[]);

// Debug Function
void convertDataMessageToDebugString(DataMessage *dataMessage, char output[]);

// Direct Receive/Transmit
bool receiveFunction(uint8_t data[], uint8_t dataLen);
bool transmitFunction(uint8_t data[], uint8_t dataLen);

#endif
