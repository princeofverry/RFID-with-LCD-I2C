#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

#define RST_PIN 9    // Define pin RST (Reset)
#define SS_PIN 10    // Define pin SDA (Serial Data)

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);      // Initialize serial communication
  SPI.begin();              // Initialize SPI communication
  mfrc522.PCD_Init();       // Initialize MFRC522
  lcd.init();               // Initialize LCD
  lcd.backlight();          // Turn on the backlight
  lcd.setCursor(4, 1);      // Set cursor to the second row
  lcd.print("welkam!");
}

void loop() {
  // Check if a card is present
  if (mfrc522.PICC_IsNewCardPresent()) {
    lcd.clear(); // Clear the LCD display
    lcd.print("RFID cards...");
    
    // Read the card's UID
    if (mfrc522.PICC_ReadCardSerial()) {
      Serial.print("UID: ");
      
      // Clear the second line on LCD
      lcd.setCursor(0, 1);
      lcd.print("                "); // Clear the line with spaces
      
      // Print UID on LCD
      lcd.setCursor(0, 1);
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""); // Add leading 0 for single digit HEX values
        lcd.print(mfrc522.uid.uidByte[i], HEX);
        Serial.print(" ");
      }
      mfrc522.PICC_HaltA(); // Halt card
      delay(2500); // Delay to display UID
      lcd.clear(); // Clear the LCD display
      lcd.setCursor(0, 1); // Set cursor to the second row
      lcd.print("Scan lagi cok...");
    }
  }
}
