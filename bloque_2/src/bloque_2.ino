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

// Instanciación del objeto display con sus 4 parámetros:
// (Ancho, Alto, Puntero al Bus Wire, Pin de Reset)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);

void setup()
{
    Serial.begin(SERIAL_BAUD);
    delay(1000);
    Serial.println("\n[BLOQUE 2] Inicializando Pantalla OLED SSD1306...");

    // Inicializamos el bus I2C en los pines por defecto del ESP32 (SDA=21, SCL=22)
    Wire.begin(21, 22);

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR))
    {
        Serial.println("[OLED] ❌ ERROR: Pantalla no detectada en 0x3C.");
        while (true)
            ; // Detiene la ejecución si hay falla física
    }

    Serial.println("[OLED] Pantalla SSD1306 inicializada [OK]");

    display.clearDisplay();                          // 2. Borra el cuaderno borrador en RAM
    display.setTextSize(1);                          // 3. Tamaño de fuente (6x8 px por letra)
    display.setTextColor(SSD1306_WHITE);             // 4. Color blanco activo
    display.setCursor(8 , 0);                         // 5. Ubicar el cursor en (X=0, Y=0)
    display.println(">> ESP32 SISTEMA <<");          // 6. Escribir en el borrador
    display.drawLine(0, 10, 128, 10, SSD1306_WHITE); // Línea horizontal

    display.display();

    Serial.println("[OLED] Cabecera visual renderizada exitosamente.");
}

void loop()
{
    delay(1000);
}
