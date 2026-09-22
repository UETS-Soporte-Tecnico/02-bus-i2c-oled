
// ============================================================================
// UETS SOPORTE TÉCNICO — SEMANA 02 — BLOQUE 2: INICIALIZACIÓN OLED & CABECERA
// 3° Bachillerato Técnico en Informática (2026–2027)
// ============================================================================

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET_PIN -1
#define OLED_I2C_ADDR 0x3C
#define SERIAL_BAUD 115200

Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    OLED_RESET_PIN
);

void setup() {
    Serial.begin(SERIAL_BAUD);
    delay(1000);

    Serial.println("\n[BLOQUE 2] Inicializando Pantalla OLED SSD1306...");

    // Inicialización del bus I2C
    Wire.begin(21, 22);
    Wire.setClock(400000);

    // Inicialización de la pantalla OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR)) {
        Serial.println("[OLED] ERROR: Pantalla no detectada.");
        while (true) {
            delay(1000);
        }
    }

    Serial.println("[OLED] Pantalla SSD1306 inicializada [OK]");

    // Construir la cabecera visual en el buffer RAM
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);

    display.setCursor(8, 0);
    display.println(">> ESP32 SISTEMA <<");

    display.drawLine(0, 10, 128, 10, SSD1306_WHITE);

    display.setCursor(0, 14);
    display.println("Sistema iniciado");

    // Enviar el buffer a la pantalla
    display.display();

    Serial.println("[OLED] Cabecera visual renderizada exitosamente.");
}

void loop() {
    delay(1000);
}


