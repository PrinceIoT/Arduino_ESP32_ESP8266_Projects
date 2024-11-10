// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h>

void setup() {
  Serial.begin(921600);
  while (!Serial);

  Serial.println("CAN Receiver and Transmitter");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

void loop() {
  receiveCANPacket();
  transmitCANPacket();
}

void receiveCANPacket() {
  // try to parse packet
  int packetSize = CAN.parsePacket();

  if (packetSize) {
    // Print the packet ID in HEX
    Serial.print(CAN.packetId(), HEX);
    Serial.print(";");

    // Print the RTR flag (0 for data frame, 1 for remote request frame)
    Serial.print(CAN.packetRtr() ? "1" : "0");
    Serial.print(";");

    // Print the IDE flag (0 for standard frame, 1 for extended frame)
    Serial.print(CAN.packetExtended() ? "1" : "0");
    Serial.print(";");

    // Print the packet size (DLC)
    Serial.print(CAN.packetDlc());
    Serial.print(";");

    // Only print packet data for non-RTR packets
    if (!CAN.packetRtr()) {
      while (CAN.available()) {
        Serial.print(CAN.read(), HEX);
      }
    }

    // End the packet with a newline character
    Serial.println();
  }
}

void transmitCANPacket() {
  // Example of sending a CAN frame
  // Prepare CAN packet
  CAN.beginPacket(0x123); // Arbitration ID
  CAN.write('H');          // Data byte 0
  CAN.write('i');          // Data byte 1
  CAN.write('!');          // Data byte 2
  CAN.endPacket();         // Send the packet
  delay(1000);             // Adjust as needed depending on your application requirements
}
