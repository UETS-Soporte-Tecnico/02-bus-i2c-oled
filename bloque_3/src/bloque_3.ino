#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET_PIN -1
#define OLED_I2C_ADDR 0x3C
#define SERIAL_BAUD 115200

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);

void logBoot(const char* moduleName, bool isOk) {

    display.print(moduleName);

    display.setCursor(95, display.getCursorY());

    if (isOk) {
        display.println("[OK]");
    } else {
        display.println("[ERR]");
    }

    display.display();
    delay(200);
}

void setup() {
    Serial.begin(SERIAL_BAUD);
    delay(1000);
    Serial.println("\n[BLOQUE 3] Demostración de Telemetría logBoot()...");

    Wire.begin(21, 22);

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR)) {
        Serial.println("[OLED] ERROR: Pantalla no detectada.");
        while (true);
    }

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    

    display.setCursor(8, 0);
    display.println(">> ESP32 SISTEMA <<");
    display.drawLine(0, 10, 128, 10, SSD1306_WHITE);
    display.setCursor(0, 14);
    display.display();

    logBoot("ESP32 Core", true);
    logBoot("Sensor I2C", true);
    Serial.println("[BLOQUE 3] Telemetría renderizada correctamente.");
}

void loop() {
    delay(1000);
}
