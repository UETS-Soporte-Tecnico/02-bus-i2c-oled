#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SERIAL_BAUD 115200
#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22
#define I2C_CLOCK_SPEED 400000 

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET_PIN -1
#define OLED_I2C_ADDR 0x3C

Adafruit_SSD1306 display(
    SCREEN_WIDTH, 
    SCREEN_HEIGHT, 
    &Wire, 
    OLED_RESET_PIN
);

void dibujarOjos(bool parpadeando) {
    display.clearDisplay();

    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(8,0);
    display.println(">> ESP32 SISTEMA <<");
    display.drawLine(0, 10, 128, 10, SSD1306_WHITE);

    if (!parpadeando) {
        display.fillCircle(40, 38, 14, SSD1306_WHITE);
        display.fillCircle(40, 38, 5, SSD1306_BLACK);

        display.fillCircle(88, 38, 14, SSD1306_WHITE);
        display.fillCircle(88, 38, 5, SSD1306_BLACK);
    } else {
        for (int i = 0; i < 3; i++) {
            display.drawLine(26, 38 + i, 54, 38 + i, SSD1306_WHITE);
            display.drawLine(74, 38 + i, 102, 38 + i, SSD1306_WHITE);
        }
    }
    
    display.display();
}

void setup() {
    Serial.begin(SERIAL_BAUD);
    delay(1000);
    Serial.println("\n========================================================");
    Serial.println("  [BLOQUE 1] ESCÁNER DE DIRECCIONES DE HARDWARE I2C     ");
    Serial.println("========================================================");

    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    Wire.setClock(I2C_CLOCK_SPEED);

    Serial.println("[I2C] Bus configurado en SDA:GPIO21, SCL:GPIO22 a 400kHz.\n");
    Serial.println("--- INICIANDO BARRIDO DE DIRECCIONES (0x01 .. 0x7E) ---");

    int devicesFound = 0;

    for (byte address = 1; address < 127; address++) {

        Wire.beginTransmission(address);
        byte error = Wire.endTransmission();
        
        if (error == 0) {
          Serial.printf("[I2C] Dispositivo detectado en: 0x%02X ", address);
          if (address == OLED_I2C_ADDR) {
           Serial.println("➔ [Display OLED SSD1306] [OK]");
           } else {
            Serial.println("➔ [Periférico Desconocido]");
           }
            devicesFound++;
         }
    }

    if (devicesFound == 0) {
        Serial.println("[I2C] ❌ No se detectaron dispositivos en el bus.");
        Serial.println("[DIAGNÓSTICO] Revisa que SDA esté en GPIO21, SCL en GPIO22, 3V3 y GND.");
    } else {
        Serial.printf("\n--- BARRIDO FINALIZADO: %d dispositivo(s) encontrado(s) ---\n", devicesFound);
    }

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR)) {
        Serial.println("[OLED] ERROR: Pantalla no detectada.");
        while (true);
    }

    dibujarOjos(false);
}

void loop() {
    delay(3000);

    dibujarOjos(true);
    delay(150);

    dibujarOjos(false);
}