#include <Wire.h>
#include <Adafruit_MS8607.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_MS8607 ms8607;

void setup() {
  Serial.begin(115200);

  while (!Serial);

  Serial.println("Adafruit MS8607 and SSD1306 test!");

  if (!ms8607.begin()) {
    Serial.println("Failed to find MS8607 chip");
    while (1) {
      delay(10);
    }
  }

  Serial.println("MS8607 Found!");

  ms8607.setHumidityResolution(MS8607_HUMIDITY_RESOLUTION_OSR_8b);
  ms8607.setPressureResolution(MS8607_PRESSURE_RESOLUTION_OSR_8192);

  Serial.println("Resolution settings configured");

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  sensors_event_t temp, pressure, humidity;
  ms8607.getEvent(&pressure, &temp, &humidity);
  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degrees C");

  Serial.print("Pressure: ");
  Serial.print(pressure.pressure);
  Serial.println(" hPa");

  Serial.print("Humidity: ");
  Serial.print(humidity.relative_humidity);
  Serial.println(" %rH");

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Temperature: ");
  display.print(temp.temperature);
  display.println(" degrees C");

  display.setCursor(0, 10);
  display.print("Pressure: ");
  display.print(pressure.pressure);
  display.println(" hPa");

  display.setCursor(0, 20);
  display.print("Humidity: ");


  

  