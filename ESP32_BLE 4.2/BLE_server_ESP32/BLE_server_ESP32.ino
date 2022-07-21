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

#define SERVICE_UUID2         "17fb90e6-08fb-11ed-861d-0242ac120002"

#define CHARACTERISTIC_UUID   "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define CHARACTERISTIC2_UUID  "c4cef5d0-083b-11ed-861d-0242ac120002" //Use a second characteristic

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  // This create a new BLE device
  BLEDevice::init("Damien Advertise"); // Name of the service that will be received by the scanner 
  BLEServer *pServer = BLEDevice::createServer(); //The BLE device is set as a server
  
  BLEService *pService = pServer->createService(SERVICE_UUID); //creation of the service pService for the server pserver

  BLEService *pService2 = pServer->createService(SERVICE_UUID2); // Try to create another service
  // Definition of the first Characteristic used to store a int value
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

   // Definition of the first Characteristic used to store a string
   BLECharacteristic *pCharacteristic2 = pService2->createCharacteristic(
                                         CHARACTERISTIC2_UUID,
                                         BLECharacteristic::PROPERTY_NOTIFY |
                                         BLECharacteristic::PROPERTY_BROADCAST |
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
  int proprio = 37;
  //pCharacteristic->setValue("Hello World says Neil");
  pCharacteristic->setValue(proprio);
  
  pCharacteristic2->setValue("Temperature");
  //string reading = ss.str();
  //String Valeur = pCharacteristic->getValue().str();

  pService->start();
  pService2->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->addServiceUUID(SERVICE_UUID2); // Allow a second service during the advertising
  pAdvertising->setScanResponse(true);
  //pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x15);
  BLEDevice::startAdvertising();
  Serial.println("2 Characteristic2 are defined! Now you can read them in your phone!");
}

void loop() {
  // put your main code here, to run repeatedly:
  //delay(2000);
}
