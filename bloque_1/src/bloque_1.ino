// ============================================================================
// UETS SOPORTE TÉCNICO — SEMANA 02 — BLOQUE 1: ESCÁNER DE BUS I2C
// 3° Bachillerato Técnico en Informática (2026–2027)
// ============================================================================

#include <Arduino.h>
#include <Wire.h>

#define SERIAL_BAUD 115200
#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22
#define I2C_CLOCK_SPEED 400000 // 400 kHz (Modo Rápido)
#define OLED_I2C_ADDR 0x3C     // Dirección física esperada de la pantalla OLED

void setup() {
    Serial.begin(SERIAL_BAUD);
    delay(1000);
    Serial.println("\n========================================================");
    Serial.println("  [BLOQUE 1] ESCÁNER DE DIRECCIONES DE HARDWARE I2C     ");
    Serial.println("========================================================");

    Wire.begin(21,22);
    Wire.setClock(I2C_CLOCK_SPEED);
    
    Serial.println("[I2C] Bus configurado en SDA:GPIO21, SCL:GPIO22 a 400kHz.\n");
    Serial.println("--- INICIANDO BARRIDO DE DIRECCIONES (0x01 .. 0x7E) ---");

    int devicesFound = 0;

    // TODO 1.3: Recorrer las direcciones válidas de 7 bits (del 1 al 126).
    for (byte address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        byte error = Wire.endTransmission();
        
        if (error==0){
            Serial.println("[I2C] ✅ Dispositivo encontrado en la dirección 0x");
            if (address < 16) {
                Serial.print("0");
            }
            Serial.println(String(address, HEX));
            if (address == 0x3c) Serial.println("[I2C] ✅ Pantalla OLED detectada en la dirección 0x3C.");
            Serial.println();
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
