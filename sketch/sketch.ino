#include <Wire.h>

// Initialize I2C with XIAO ESP32-C6 default pins
#define SDAPIN D4 // SDA=D4/GPIO6
#define SCLPIN D5 // SCL=D5/GPIO7

void setup() {
  Serial.begin(115200);

  while (!Serial) {
    delay(10);
  }

  Serial.println("\nI2C Scanner for XIAO ESP32-C6");
  Serial.println("Default I2C pins:");
  Serial.print("SDA="); Serial.println(SDAPIN, HEX);
  Serial.print("SCL="); Serial.println(SCLPIN, HEX);

  Wire.begin(SDAPIN, SCLPIN);
}

void loop() {
  // byte error;
  // byte address;
  int deviceCount = 0;

  Serial.println("\nScanning I2C bus...");

  for (byte address = 1; address < 127; ++address) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Device found at 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.print("  →  ");
      printKnownDevice(address);
      ++deviceCount;
    } else if (error == 4) {
      Serial.print("Unknown error at 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }

  if (deviceCount == 0) {
    Serial.println("No I2C devices found.");
  }
  else {
    Serial.printf("\n%d device(s) found.\n", deviceCount);
  }

  delay(5000);  // Rescan every 5 seconds
}

void printKnownDevice(byte address) {
  switch (address) {
    case 0x20: Serial.println("PCF8574 I/O Expander"); break;
    case 0x27: Serial.println("PCF8574 LCD / I/O Expander"); break;
    case 0x3C: Serial.println("SSD1306 OLED Display"); break;
    case 0x3D: Serial.println("SSD1306 OLED Display (alt)"); break;
    case 0x40: Serial.println("PCA9685 / INA219 / HTU21D"); break;
    case 0x48: Serial.println("ADS1115 / TMP48 / PCF8591"); break;
    case 0x50: Serial.println("AT24C EEPROM"); break;
    case 0x57: Serial.println("DS3231 RTC EEPROM"); break;
    case 0x5C: Serial.println("AM2315 Humidity Sensor"); break;
    case 0x68: Serial.println("MPU6050 IMU / DS1307 RTC"); break;
    case 0x76: Serial.println("BME280 / BMP280 Sensor"); break;
    case 0x77: Serial.println("BME280 / BMP280 (alt) / MS5611"); break;
    default:   Serial.println("Unknown device"); break;
  }
}
