// ============================================================================
// UETS SOPORTE TÉCNICO — SEMANA 02 — BLOQUE 1: ESCÁNER DE BUS I2C
// 3° Bachillerato Técnico en Informática (2026–2027)
// ============================================================================

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display (SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
void ojosA(){
    display.clearDisplay();
    
    display.fillRect(20,15,35,35, WHITE);
    display.fillRect(73,15,35,35, WHITE);

    display.fillRect(32,27,10,10, BLACK);
    display.fillRect(85,27,10,10, BLACK);

    display.display();
}

void ojosC(){
    display.clearDisplay();

    display.fillRect(20,31,35,5, WHITE);
    display.fillRect(73,31,35,5, WHITE);

    display.display();
}

void setup(){
    Wire.begin(SDA, SCL);

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextColor(WHITE);
} 

void loop(){
    ojosA();
    delay(2000);

    ojosC();
    delay(200);

    ojosA();
    delay(2000);
}