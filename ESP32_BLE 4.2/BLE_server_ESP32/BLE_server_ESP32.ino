/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp
    Ported to Arduino ESP32 by Evandro Copercini
    updates by Damien Sambo
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID          "4fafc201-1fb5-459e-8fcc-c5c9c331914b"

#define CHARACTERISTIC_UUID   "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define CHARACTERISTIC2_UUID  "c4cef5d0-083b-11ed-861d-0242ac120002" //Use a second characteristic

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  BLEDevice::init("Damien Advertise"); // Name of the service that will be received by the scanner
  BLEServer *pServer = BLEDevice::createServer();
  
  BLEService *pService = pServer->createService(SERVICE_UUID); //creation of the service pService
  
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_NOTIFY |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

   BLECharacteristic *pCharacteristic2 = pService->createCharacteristic(
                                         CHARACTERISTIC2_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
  int proprio = 37;
  //pCharacteristic->setValue("Hello World says Neil");
  pCharacteristic->setValue(proprio);
  pCharacteristic2->setValue("Temperature");
  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  //pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("2 Characteristic2 are defined! Now you can read them in your phone!");
}

void loop() {
  // put your main code here, to run repeatedly:
  //delay(2000);
}
