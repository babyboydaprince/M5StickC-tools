#include <M5StickCPlus.h>
#include <BLEDevice.h>
#include <BLEHIDDevice.h>
#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

bool isConnected = false;

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    Serial.println("Device connected");
    isConnected = true;
  }

  void onDisconnect(BLEServer* pServer) {
    Serial.println("Device disconnected");
    isConnected = false;
  }
};

void btSetup() {
  M5.begin();
  Serial.begin(115200);
  
  BLEDevice::init("M5StickC Keyboard");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEHIDDevice *pHid = new BLEHIDDevice(pServer);
  BLECharacteristic *pCharacteristic = pHid->inputReport(1); // <-- input REPORTID from report map
  pCharacteristic->setAccessPermissions(ESP_GATT_PERM_READ_ENCRYPTED | ESP_GATT_PERM_WRITE_ENCRYPTED);
  pHid->manufacturer()->setValue("M5Stack");
  pHid->pnp(0x02, 0xe502, 0xa111, 0x0210);
  pHid->hidInfo(0x00, 0x02);

  // Set device name for advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->setAppearance(HID_KEYBOARD);
  pAdvertising->start();

}

void btLoop() {
  M5.update();

  if (isConnected) {
    executeBluetoothKeyboard();
  }
}

void executeBluetoothKeyboard() {
  // Example keyboard commands
  bleKeyboard.write(KEY_LEFT_ARROW);
  delay(1000);
  bleKeyboard.write(KEY_RIGHT_ARROW);
  delay(1000);
  bleKeyboard.write(KEY_HOME);
  delay(1000);
}
