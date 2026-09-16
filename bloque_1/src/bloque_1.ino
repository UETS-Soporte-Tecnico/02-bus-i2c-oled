#include <Arduino.h>
#include <Wire.h>

#define SERIAL_BAUD 115200
#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22
#define I2C_CLOCK_SPEED 400000 
#define OLED_I2C_ADDR 0x3C     

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
       
        if (error==0) {
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
}

void loop() {
    delay(1000);
}