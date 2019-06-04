#include "lora_function.hpp"

/*
=====================================
|| BASIC LORA FUNCTION
=====================================
*/

bool receiveFunction(uint8_t data[], uint8_t dataLen)
{
    // setup only for e-byte E-19 LoRa module
    digitalWrite(RX_PIN, HIGH);
    digitalWrite(TX_PIN, LOW);

    // try to parse packet
    int packetSize = LoRa.parsePacket();
    if (packetSize)
    {

        // read packet from LoRa
        uint8_t idx = 0;
        while (LoRa.available())
        {
            if (idx < dataLen)
            {
                // store data per-byte to receiveData
                data[idx] = LoRa.read();
                idx++;
            }
            else
            {
                // clear the data in case any signal contain longer byte than receiveLen
                LoRa.read();
            }
        }

        return true;
    }

    return false;
}

bool transmitFunction(uint8_t data[], uint8_t dataLen)
{
    // setup only for e-byte E-19 LoRa module
    digitalWrite(RX_PIN, LOW);
    digitalWrite(TX_PIN, HIGH);

    //  Serial.println("Data to Send:");
    //  for (int i = 0; i < dataLen; i++)
    //  {
    //    Serial.print(data[i]);
    //    Serial.print(", ");
    //  }
    //  Serial.println("");

    //  Serial.println("Begin Transmission");

    // send packet via LoRa
    LoRa.beginPacket();
    LoRa.write(data, dataLen);
    LoRa.endPacket();
    return true;
    //  Serial.println("End of Transmission.");
}

/*
=====================
|| Converter Function
=====================
*/

/**   Data Message    **/
static void convertDataMessageToArray(DataMessage *dataMessage, uint8_t data[])
{
    data[MSG_ID_IDX] = dataMessage->message_id;
    data[INSTRUCTION_CODE_IDX] = dataMessage->instruction_code;
    data[GATE_ID_HB_IDX] = (uint8_t)(dataMessage->gateway_id >> 8);
    data[GATE_ID_LB_IDX] = (uint8_t)(dataMessage->gateway_id % 256);
    data[NODE_ID_IDX] = dataMessage->node_id;
    data[BATT_IDX] = dataMessage->battery_voltage;
    data[CHECKSUM_IDX] = dataMessage->checksum;

    data[SID_1_IDX] = dataMessage->sensor[0].id;
    data[ACC_X_1_HB_IDX] = (uint8_t)(dataMessage->sensor[0].accelerometer_x >> 8);
    data[ACC_X_1_LB_IDX] = (uint8_t)(dataMessage->sensor[0].accelerometer_x % 256);
    data[ACC_Y_1_HB_IDX] = (uint8_t)(dataMessage->sensor[0].accelerometer_y >> 8);
    data[ACC_Y_1_LB_IDX] = (uint8_t)(dataMessage->sensor[0].accelerometer_y % 256);
    data[ACC_Z_1_HB_IDX] = (uint8_t)(dataMessage->sensor[0].accelerometer_z >> 8);
    data[ACC_Z_1_LB_IDX] = (uint8_t)(dataMessage->sensor[0].accelerometer_z % 256);

    data[SID_2_IDX] = dataMessage->sensor[1].id;
    data[ACC_X_2_HB_IDX] = (uint8_t)(dataMessage->sensor[1].accelerometer_x >> 8);
    data[ACC_X_2_LB_IDX] = (uint8_t)(dataMessage->sensor[1].accelerometer_x % 256);
    data[ACC_Y_2_HB_IDX] = (uint8_t)(dataMessage->sensor[1].accelerometer_y >> 8);
    data[ACC_Y_2_LB_IDX] = (uint8_t)(dataMessage->sensor[1].accelerometer_y % 256);
    data[ACC_Z_2_HB_IDX] = (uint8_t)(dataMessage->sensor[1].accelerometer_z >> 8);
    data[ACC_Z_2_LB_IDX] = (uint8_t)(dataMessage->sensor[1].accelerometer_z % 256);

    data[SID_3_IDX] = dataMessage->sensor[2].id;
    data[ACC_X_3_HB_IDX] = (uint8_t)(dataMessage->sensor[2].accelerometer_x >> 8);
    data[ACC_X_3_LB_IDX] = (uint8_t)(dataMessage->sensor[2].accelerometer_x % 256);
    data[ACC_Y_3_HB_IDX] = (uint8_t)(dataMessage->sensor[2].accelerometer_y >> 8);
    data[ACC_Y_3_LB_IDX] = (uint8_t)(dataMessage->sensor[2].accelerometer_y % 256);
    data[ACC_Z_3_HB_IDX] = (uint8_t)(dataMessage->sensor[2].accelerometer_z >> 8);
    data[ACC_Z_3_LB_IDX] = (uint8_t)(dataMessage->sensor[2].accelerometer_z % 256);

    data[SID_4_IDX] = dataMessage->sensor[3].id;
    data[ACC_X_4_HB_IDX] = (uint8_t)(dataMessage->sensor[3].accelerometer_x >> 8);
    data[ACC_X_4_LB_IDX] = (uint8_t)(dataMessage->sensor[3].accelerometer_x % 256);
    data[ACC_Y_4_HB_IDX] = (uint8_t)(dataMessage->sensor[3].accelerometer_y >> 8);
    data[ACC_Y_4_LB_IDX] = (uint8_t)(dataMessage->sensor[3].accelerometer_y % 256);
    data[ACC_Z_4_HB_IDX] = (uint8_t)(dataMessage->sensor[3].accelerometer_z >> 8);
    data[ACC_Z_4_LB_IDX] = (uint8_t)(dataMessage->sensor[3].accelerometer_z % 256);

    data[SID_5_IDX] = dataMessage->sensor[4].id;
    data[ACC_X_5_HB_IDX] = (uint8_t)(dataMessage->sensor[4].accelerometer_x >> 8);
    data[ACC_X_5_LB_IDX] = (uint8_t)(dataMessage->sensor[4].accelerometer_x % 256);
    data[ACC_Y_5_HB_IDX] = (uint8_t)(dataMessage->sensor[4].accelerometer_y >> 8);
    data[ACC_Y_5_LB_IDX] = (uint8_t)(dataMessage->sensor[4].accelerometer_y % 256);
    data[ACC_Z_5_HB_IDX] = (uint8_t)(dataMessage->sensor[4].accelerometer_z >> 8);
    data[ACC_Z_5_LB_IDX] = (uint8_t)(dataMessage->sensor[4].accelerometer_z % 256);
}

static void convertArrayToDataMessage(uint8_t data[], DataMessage *dataMessage)
{
    dataMessage->message_id = data[MSG_ID_IDX];
    dataMessage->instruction_code = data[INSTRUCTION_CODE_IDX];
    dataMessage->gateway_id = (data[GATE_ID_HB_IDX] << 8) + data[GATE_ID_LB_IDX];
    dataMessage->node_id = data[NODE_ID_IDX];
    dataMessage->battery_voltage = data[BATT_IDX];
    dataMessage->checksum = data[CHECKSUM_IDX];

    dataMessage->sensor[0].id = data[SID_1_IDX];
    dataMessage->sensor[0].accelerometer_x = (data[ACC_X_1_HB_IDX] << 8) + data[ACC_X_1_LB_IDX];
    dataMessage->sensor[0].accelerometer_y = (data[ACC_Y_1_HB_IDX] << 8) + data[ACC_Y_1_LB_IDX];
    dataMessage->sensor[0].accelerometer_z = (data[ACC_Z_1_HB_IDX] << 8) + data[ACC_Z_1_LB_IDX];

    dataMessage->sensor[1].id = data[SID_2_IDX];
    dataMessage->sensor[1].accelerometer_x = (data[ACC_X_2_HB_IDX] << 8) + data[ACC_X_2_LB_IDX];
    dataMessage->sensor[1].accelerometer_y = (data[ACC_Y_2_HB_IDX] << 8) + data[ACC_Y_2_LB_IDX];
    dataMessage->sensor[1].accelerometer_z = (data[ACC_Z_2_HB_IDX] << 8) + data[ACC_Z_2_LB_IDX];

    dataMessage->sensor[2].id = data[SID_3_IDX];
    dataMessage->sensor[2].accelerometer_x = (data[ACC_X_3_HB_IDX] << 8) + data[ACC_X_3_LB_IDX];
    dataMessage->sensor[2].accelerometer_y = (data[ACC_Y_3_HB_IDX] << 8) + data[ACC_Y_3_LB_IDX];
    dataMessage->sensor[2].accelerometer_z = (data[ACC_Z_3_HB_IDX] << 8) + data[ACC_Z_3_LB_IDX];

    dataMessage->sensor[3].id = data[SID_4_IDX];
    dataMessage->sensor[3].accelerometer_x = (data[ACC_X_4_HB_IDX] << 8) + data[ACC_X_4_LB_IDX];
    dataMessage->sensor[3].accelerometer_y = (data[ACC_Y_4_HB_IDX] << 8) + data[ACC_Y_4_LB_IDX];
    dataMessage->sensor[3].accelerometer_z = (data[ACC_Z_4_HB_IDX] << 8) + data[ACC_Z_4_LB_IDX];

    dataMessage->sensor[4].id = data[SID_5_IDX];
    dataMessage->sensor[4].accelerometer_x = (data[ACC_X_5_HB_IDX] << 8) + data[ACC_X_5_LB_IDX];
    dataMessage->sensor[4].accelerometer_y = (data[ACC_Y_5_HB_IDX] << 8) + data[ACC_Y_5_LB_IDX];
    dataMessage->sensor[4].accelerometer_z = (data[ACC_Z_5_HB_IDX] << 8) + data[ACC_Z_5_LB_IDX];
}

void convertDataMessageToHTMLData(DataMessage *dataMessage, char output[])
{
    sprintf(output, "gid=%u&nid=%u&batt=%u&checksum=%u&date=2019-05-09&time=10%%3A00%%3A03&sid0=%d&data00=%d&data01=%d&data02=%d&sid1=%d&data10=%d&data11=%d&data12=%d&sid2=%d&data20=%d&data21=%d&data22=%d&sid3=%d&data30=%d&data31=%d&data32=%d&sid4=%d&data40=%d&data41=%d&data42=%d",
            dataMessage->gateway_id, dataMessage->node_id,
            dataMessage->battery_voltage, dataMessage->checksum,
            dataMessage->sensor[0].id, dataMessage->sensor[0].accelerometer_x, dataMessage->sensor[0].accelerometer_y, dataMessage->sensor[0].accelerometer_z,
            dataMessage->sensor[1].id, dataMessage->sensor[1].accelerometer_x, dataMessage->sensor[1].accelerometer_y, dataMessage->sensor[1].accelerometer_z,
            dataMessage->sensor[2].id, dataMessage->sensor[2].accelerometer_x, dataMessage->sensor[2].accelerometer_y, dataMessage->sensor[2].accelerometer_z,
            dataMessage->sensor[3].id, dataMessage->sensor[3].accelerometer_x, dataMessage->sensor[3].accelerometer_y, dataMessage->sensor[3].accelerometer_z,
            dataMessage->sensor[4].id, dataMessage->sensor[4].accelerometer_x, dataMessage->sensor[4].accelerometer_y, dataMessage->sensor[4].accelerometer_z);
}

// Debug Function
void convertDataMessageToDebugString(DataMessage *dataMessage, char output[])
{
    sprintf(output, "msg_id: %hhu, instruction code: %hhu |gid=%u&nid=%u&batt=%u&checksum=%u&date=2019-05-09&time=10%%3A00%%3A03&sid0=%d&data00=%d&data01=%d&data02=%d&sid1=%d&data10=%d&data11=%d&data12=%d&sid2=%d&data20=%d&data21=%d&data22=%d&sid3=%d&data30=%d&data31=%d&data32=%d&sid4=%d&data40=%d&data41=%d&data42=%d",
            dataMessage->message_id, dataMessage->instruction_code,
            dataMessage->gateway_id, dataMessage->node_id,
            dataMessage->battery_voltage, dataMessage->checksum,
            dataMessage->sensor[0].id, dataMessage->sensor[0].accelerometer_x, dataMessage->sensor[0].accelerometer_y, dataMessage->sensor[0].accelerometer_z,
            dataMessage->sensor[1].id, dataMessage->sensor[1].accelerometer_x, dataMessage->sensor[1].accelerometer_y, dataMessage->sensor[1].accelerometer_z,
            dataMessage->sensor[2].id, dataMessage->sensor[2].accelerometer_x, dataMessage->sensor[2].accelerometer_y, dataMessage->sensor[2].accelerometer_z,
            dataMessage->sensor[3].id, dataMessage->sensor[3].accelerometer_x, dataMessage->sensor[3].accelerometer_y, dataMessage->sensor[3].accelerometer_z,
            dataMessage->sensor[4].id, dataMessage->sensor[4].accelerometer_x, dataMessage->sensor[4].accelerometer_y, dataMessage->sensor[4].accelerometer_z);
}
/*
=====================================
|| FUNCTION DEFINITION
=====================================
*/

void setupLora()
{
    // override the default CS, reset, and IRQ pins (optional)
    LoRa.setPins(CS_PIN, RESET_PIN, IRQ_PIN); // set CS, reset, IRQ pin

    if (!LoRa.begin(LORA_OPERATING_FREQUENCY))
    {
        Serial.println("Starting LoRa failed!");
        while (1)
            ;
    }

    // setup only for e-byte E-19 LoRa module
    pinMode(RX_PIN, OUTPUT);
    pinMode(TX_PIN, OUTPUT);
}

void receiveAndParseDataMessage(DataMessage *dataMessage)
{
    uint8_t receiveData[MESSAGE_LENGTH];
    const uint8_t receiveLen = sizeof(receiveData);

    // check for incoming a LoRa wireless signal from nodes and store the data to receive data
    if (receiveFunction(receiveData, receiveLen))
    {
        convertArrayToDataMessage(receiveData, dataMessage);
    }
}

void parseAndTransmitDataMessage(DataMessage *dataMessage)
{
    uint8_t transmitData[MESSAGE_LENGTH];
    const uint8_t transmitLen = sizeof(transmitData);

    // check for incoming a LoRa wireless signal from nodes and store the data to receive data
    convertDataMessageToArray(dataMessage, transmitData);
    transmitFunction(transmitData, transmitLen);
}

void receiveAndParseInstructionMessageFromString(char htmlData[], InstructionMessage *instructionMessage)
{
    sscanf(htmlData, "%hu,%hhu,%hhu,%hhu,%hhu,%hhu",
           &(instructionMessage->gateway_id),
           &(instructionMessage->node_id),
           &(instructionMessage->sensor_id),
           &(instructionMessage->instruction_id),
           &(instructionMessage->instruction_code),
           &(instructionMessage->instruction_data));
}
