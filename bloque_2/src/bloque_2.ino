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

// Instanciación del objeto display
// (Ancho, Alto, Puntero al Bus Wire, Pin de Reset)
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

    // Inicializamos el bus I2C
    // SDA = GPIO21
    // SCL = GPIO22
    Wire.begin(21, 22);

    // Inicializamos la pantalla OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR)) {
        Serial.println("[OLED] ERROR: Pantalla no detectada en 0x3C.");
        while (true);
    }

    Serial.println("[OLED] Pantalla SSD1306 inicializada [OK]");

    // Limpiar el buffer de la pantalla
    display.clearDisplay();

    // Configurar texto
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);

    // Posicionar el cursor
    display.setCursor(8, 0);

    // Escribir el título
    display.println(">> ESP32 SISTEMA <<");

    // Dibujar línea horizontal
    display.drawLine(0, 10, 128, 10, SSD1306_WHITE);

    // Enviar el contenido del buffer a la pantalla
    display.display();

    Serial.println("[OLED] Cabecera visual renderizada exitosamente.");
}

void loop() {
    // La pantalla se mantiene mostrando la información.
    delay(1000);
}