#include <AXP192.h>
#include <Free_Fonts.h>
#include <M5Display.h>
#include <M5StickCPlus.h>
#include <RTC.h>

const int MENU_ITEMS = 4;
const char* menuOptions[MENU_ITEMS] = {"Spy-Mic", "BadBT", "Option 3", "Option 4"};
const char* randomTexts[MENU_ITEMS] = {"Random Text 1", "Random Text 2", "Random Text 3", "Random Text 4"};
int selectedOption = 0;

// Declare the function prototype for executeBluetoothKeyboard
void executeBluetoothKeyboard();

void setup() {
  M5.begin();
  M5.Lcd.setRotation(5);
  bootText();
}

void loop() {
  M5.update();
  
  if (M5.BtnA.wasPressed()) {
    executeOption();
  }
  
  if (M5.BtnB.wasPressed()) {
    nextOption();
  }
}

void bootText() {
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(TFT_GREEN); // Set initial color to green
  int cursorX = 50; // Initial x-position of the cursor
  const char* bootMessage = "Booting..."; // Boot message to display
  int textLength = strlen(bootMessage); // Length of the boot message

  // Display blinking cursor for 3 seconds
  unsigned long startTime = millis();
  while (millis() - startTime < 2000) {
    M5.Lcd.fillScreen(TFT_BLACK); // Clear the screen
    M5.Lcd.setCursor(cursorX, 50); // Set the cursor position
    if ((millis() - startTime) % 1000 < 500) {
      M5.Lcd.print("|"); // Print the cursor
    }
    delay(80); // Blinking speed (50ms on, 50ms off)
  }

  // Type out boot message slowly
  for (int i = 0; i < textLength; i++) {
    M5.Lcd.setCursor(cursorX, 50); // Set the cursor position
    M5.Lcd.print(bootMessage[i]); // Print a character of the boot message
    delay(40); // Typing speed (40ms delay between each character)
    cursorX += M5.Lcd.textWidth(String(bootMessage[i]).c_str()) + 2; // Move cursor to the right
  }
  
  delay(1500); // wait
  // Clear the screen
  M5.Lcd.fillScreen(TFT_BLACK);
  
  // Print the additional messages
  M5.Lcd.setTextSize(1);
  cursorX = 0; // Reset cursor position
  const char* bootMessage1 = "Mess with the best "; 
  const char* bootMessage2 = "Die like the rest... "; 
  const char* bootMessage3 = "      >:)"; 
  int textLength1 = strlen(bootMessage1); // Length of the message
  int textLength2 = strlen(bootMessage2); // Length of the second part of the message
  int textLength3 = strlen(bootMessage3); // Length of the third part of the message
  
  // Change text color to red
  M5.Lcd.setTextColor(TFT_RED);
  
  // Write "Mess with the best" first
  for (int i = 0; i < textLength1; i++) {
    M5.Lcd.setCursor(cursorX, 30); // Set the cursor position above the second line
    M5.Lcd.print(bootMessage1[i]); // Print a character of the message
    delay(30); // Typing speed (30ms delay between each character)
    cursorX += M5.Lcd.textWidth(String(bootMessage1[i]).c_str()) + 2; // Move cursor to the right
  }
  
  delay(1000);

  // Move cursor to the next line for the second message
  cursorX = 0; // Reset cursor position
  M5.Lcd.setCursor(cursorX, 70); // Set the cursor position for the second line
  
  // Write "die like the rest " below "Mess with the best"
  for (int i = 0; i < textLength2; i++) {
    M5.Lcd.print(bootMessage2[i]); // Print a character of the message
    delay(30); // Typing speed (30ms delay between each character)
    cursorX += M5.Lcd.textWidth(String(bootMessage2[i]).c_str()) + 2; // Move cursor to the right
    if (cursorX >= M5.Lcd.width()) {
      // Move to the next line if the message width exceeds the screen width
      cursorX = 0;
      M5.Lcd.setCursor(cursorX, 90); // Move to the next line
    }
  }
  
  
  // Move cursor to the next line for the third message
  cursorX = 0; // Reset cursor position
  M5.Lcd.setCursor(cursorX, 110); // Set the cursor position for the third line
  
  // Write ">:)" below "die like the rest"
  for (int i = 0; i < textLength3; i++) {
    M5.Lcd.print(bootMessage3[i]); // Print a character of the message
    delay(200); // Typing speed (30ms delay between each character)
    cursorX += M5.Lcd.textWidth(String(bootMessage3[i]).c_str()) + 2; // Move cursor to the right
    if (cursorX >= M5.Lcd.width()) {
      // Move to the next line if the message width exceeds the screen width
      cursorX = 0;
      M5.Lcd.setCursor(cursorX, 130); // Move to the next line
    }
  }
  
  // Wait for 2 seconds before displaying the menu
  delay(3000);
  
  // Blink all messages together really fast
  for (int j = 0; j < 30; j++) {
    M5.Lcd.fillScreen(TFT_BLACK); // Clear the screen
    delay(30); // Wait 10ms
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(TFT_RED); // Change text color to red
    M5.Lcd.setCursor(0, 30); // Set the cursor position for the first line
    M5.Lcd.print(bootMessage1); // Print "Mess with the best"
    M5.Lcd.print("\n"); // Print line break
    M5.Lcd.setCursor(0, 70); // Move cursor to the second line
    M5.Lcd.print(bootMessage2); // Print "die like the rest"
    M5.Lcd.print("\n\n"); // Print line break
    M5.Lcd.print(bootMessage3); // Print ">:)"
    delay(30); // Wait 10ms
  }
  
  M5.Lcd.setTextSize(2);
  // Clear the screen before drawing the menu
  M5.Lcd.fillScreen(TFT_BLACK);
  
  // Draw the menu
  drawMenu();
}

void drawMenu() {
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(TFT_GREEN);
  for (int i = 0; i < MENU_ITEMS; i++) {
    if (i == selectedOption) {
      M5.Lcd.fillRect(10, 10 + (i * 30), 120, 30, TFT_GREEN);
      M5.Lcd.setTextColor(TFT_BLACK);
    } else {
      M5.Lcd.fillRect(10, 10 + (i * 30), 120, 30, TFT_BLACK);
      M5.Lcd.setTextColor(TFT_GREEN);
    }
    M5.Lcd.setCursor(15, 15 + (i * 30));
    M5.Lcd.print(menuOptions[i]);
  }
}

void nextOption() {
  selectedOption = (selectedOption + 1) % MENU_ITEMS;
  drawMenu();
}

void executeOption() {
  if (selectedOption == 1) { // Check if "BadBT" option is selected
    const char* startBadBt= "Starting BadBT...";
    int textBadBtLenght = strlen(startBadBt); // Length of the message

    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.setTextColor(TFT_CYAN);

    // Type out boot message slowly
    int cursorX = 50; // Initial x-position of the cursor
    for (int i = 0; i < textBadBtLenght; i++) {
      M5.Lcd.setCursor(cursorX, 50); // Set the cursor position
      M5.Lcd.print(startBadBt[i]); // Print a character of the boot message
      delay(40); // Typing speed (40ms delay between each character)
      cursorX += M5.Lcd.textWidth(String(startBadBt[i]).c_str()) + 2; // Move cursor to the right
    }

    delay(80);

    // Execute Bluetooth keyboard code
    executeBluetoothKeyboard();
  } else {
    // Here you can define the actions to be performed for each menu option
    // For simplicity, let's just print the selected option and a random text to Serial
    Serial.print(menuOptions[selectedOption]);
    Serial.print(": ");
    Serial.println(randomTexts[selectedOption]);
  }
}
