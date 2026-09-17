// ============================================================================
// UETS SOPORTE TÉCNICO — SEMANA 02 — BLOQUE 1: ESCÁNER DE BUS I2C Y OJOS OLED
// 3° Bachillerato Técnico en Informática (2026–2027)
// ============================================================================

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SERIAL_BAUD 115200
#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22
#define I2C_CLOCK_SPEED 400000 // 400 kHz (Modo Rápido)

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET_PIN -1
#define OLED_I2C_ADDR 0x3C     // Dirección física esperada de la pantalla OLED

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);

// ============================================================================
// FUNCIONES DE ANIMACIÓN DE OJOS (Círculo Blanco + Círculo Negro)
// ============================================================================

// Dibujar ojos abiertos (Ojo blanco + Pupila negra)
void dibujarOjosAbiertos() {
    display.clearDisplay();

    // --- OJO IZQUIERDO ---
    // Círculo exterior (Blanco) - Centro X=38, Y=32, Radio=14
    display.fillCircle(38, 32, 14, SSD1306_WHITE);
    // Pupila interior (Negra) - Centro X=38, Y=32, Radio=6
    display.fillCircle(38, 32, 6, SSD1306_BLACK);

    // --- OJO DERECHO ---
    // Círculo exterior (Blanco) - Centro X=90, Y=32, Radio=14
    display.fillCircle(90, 32, 14, SSD1306_WHITE);
    // Pupila interior (Negra) - Centro X=90, Y=32, Radio=6
    display.fillCircle(90, 32, 6, SSD1306_BLACK);

    display.display();
}

// Dibujar ojos cerrados usando drawLine
void dibujarOjosCerrados() {
    display.clearDisplay();
    // Línea Ojo Izquierdo
    display.drawLine(24, 32, 52, 32, SSD1306_WHITE); 
    // Línea Ojo Derecho
    display.drawLine(76, 32, 104, 32, SSD1306_WHITE); 
    display.display();
}

// ============================================================================
// TELEMETRÍA DE ARRANQUE
// ============================================================================

void logBoot(const char* moduleName, bool isOk) {
    display.print(moduleName);

    // Alinear el estado a la derecha en la columna X=95
    display.setCursor(95, display.getCursorY());

    if (isOk) {
        display.println("[OK]");
    } else {
        display.println("[ERR]");
    }

    display.display();
    delay(200);
}

// ============================================================================
// CONFIGURACIÓN INICIAL (SETUP)
// ============================================================================

void setup() {
    Serial.begin(SERIAL_BAUD);
    delay(1000);
    
    Serial.println("\n========================================================");
    Serial.println("  [BLOQUE 1] INICIALIZACIÓN I2C Y PANTALLA OLED         ");
    Serial.println("========================================================");

    // Inicialización del bus I2C
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    Wire.setClock(I2C_CLOCK_SPEED);

    // Inicialización de la pantalla OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR)) {
        Serial.println("[OLED] ERROR: Pantalla no detectada.");
        while (true);
    }

    // Configuración inicial de texto en OLED
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    
    // Cabecera de Telemetría
    display.setCursor(8, 0);
    display.println(">> ESP32 SISTEMA <<");
    display.drawLine(0, 10, 128, 10, SSD1306_WHITE);
    display.setCursor(0, 14); 
    display.display();

    // Prueba de telemetría logBoot()
    logBoot("ESP32 Core", true);
    logBoot("Sensor I2C", true);

    delay(1500); // Pausa para visualizar la pantalla de arranque
}

// ============================================================================
// BUCLE PRINCIPAL (LOOP)
// ============================================================================

void loop() {
    // 1. Mostrar Ojos Abiertos (con pupila)
    dibujarOjosAbiertos();
    delay(2500); // Mantiene los ojos abiertos 2.5 segundos

    // 2. Mostrar Ojos Cerrados (Parpadeo)
    dibujarOjosCerrados();
    delay(150);  // Parpadeo rápido de 150 ms
}