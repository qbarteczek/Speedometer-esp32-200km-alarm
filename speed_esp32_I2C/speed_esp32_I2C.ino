#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TinyGPS++.h>

// Definicje dla wyświetlacza OLED I2C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Obiekt dla TinyGPS++
TinyGPSPlus gps;

// Ustawienia dla GPS
#define RXPin 16
#define TXPin 17
#define GPSBaud 9600

// Utworzenie obiektu dla portu szeregowego GPS
HardwareSerial SerialGPS(1);

// Zmienne do śledzenia dziennego przebiegu
double dailyDistance = 0.0;
double lastLat = 0.0;
double lastLng = 0.0;
bool alarmActive = false;

void setup() {
  // Inicjalizacja monitora portu szeregowego
  Serial.begin(115200);

  // Inicjalizacja portu szeregowego dla GPS
  SerialGPS.begin(GPSBaud, SERIAL_8N1, RXPin, TXPin);

  // Inicjalizacja wyświetlacza OLED I2C
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();

  // Inicjalizacja ostatniej pozycji
  lastLat = gps.location.lat();
  lastLng = gps.location.lng();
}

// Zmienna do płynnego odświeżania ekranu (bez migotania)
unsigned long lastDisplayUpdate = 0;
const unsigned long DISPLAY_INTERVAL = 500; // 2 klatki na sekundę

void loop() {
  // 1. Asynchroniczny odczyt danych z GPS
  while (SerialGPS.available() > 0) {
    gps.encode(SerialGPS.read());
  }

  // 2. Aktualizacja przebiegu dziennego (z filtrem anty-driftowym)
  if (gps.location.isValid() && gps.location.isUpdated()) {
    if (lastLat != 0.0 && lastLng != 0.0) {
      // Zabezpieczenie przed naliczaniem "przebiegu widmo" na postoju
      if (gps.speed.isValid() && gps.speed.kmph() > 3.0) {
        double distance = TinyGPSPlus::distanceBetween(
          lastLat, lastLng,
          gps.location.lat(), gps.location.lng()
        );
        dailyDistance += distance / 1000.0; // Przeliczenie na kilometry
      }
    }
    lastLat = gps.location.lat();
    lastLng = gps.location.lng();
  }

  // 3. Sprawdzanie, czy alarm powinien być aktywowany
  if (dailyDistance >= 200.0 && gps.speed.isValid() && gps.speed.kmph() > 0) {
    alarmActive = true;
  }
  // Wyłączanie alarmu po zatrzymaniu
  if (gps.speed.isValid() && gps.speed.kmph() < 1.0) {
    alarmActive = false;
  }

  // 4. Płynne odświeżanie OLED (co 500 ms)
  if (millis() - lastDisplayUpdate >= DISPLAY_INTERVAL) {
    lastDisplayUpdate = millis();

    display.clearDisplay();

    // Wyświetlanie liczby widocznych satelitów w lewym górnym rogu
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    if (gps.satellites.isValid()) {
      display.print("Sat: ");
      display.print(gps.satellites.value());
    } else {
      display.print("Sat: ---");
    }

    // Wyświetlanie wysokości nad poziomem morza w prawym górnym rogu
    display.setCursor(SCREEN_WIDTH - 64, 0);
    if (gps.altitude.isValid()) {
      display.print("Alt: ");
      display.print(gps.altitude.meters(), 0);
      display.print("m");
    } else {
      display.print("Alt: ---");
    }

    // Wyświetlanie czasu z korekcją dla Polski (UTC+2) w lewym dolnym rogu
    display.setCursor(0, SCREEN_HEIGHT - 8);
    if (gps.time.isValid()) {
      int hour = (gps.time.hour() + 2) % 24;
      if (hour < 10) display.print('0');
      display.print(hour);
      display.print(":");
      if (gps.time.minute() < 10) display.print('0');
      display.print(gps.time.minute());
      display.print(":");
      if (gps.time.second() < 10) display.print('0');
      display.print(gps.time.second());
    } else {
      display.print("Time: --:--");
    }

    // Wyświetlanie dziennego licznika kilometrów w prawym dolnym rogu
    display.setCursor(SCREEN_WIDTH - 64, SCREEN_HEIGHT - 8);
    display.print("KM: ");
    display.print(dailyDistance, 1);

    // Wyświetlanie prędkości w centralnym miejscu wyświetlacza
    display.setCursor((SCREEN_WIDTH / 2) - 20, (SCREEN_HEIGHT / 2) - 8);
    display.setTextSize(2);
    if (gps.speed.isValid()) {
      display.print(gps.speed.kmph(), 0);
    } else {
      display.print("---");
    }
    display.setTextSize(1);
    display.setCursor((SCREEN_WIDTH / 2) + 20, (SCREEN_HEIGHT / 2) - 8);
    display.print(" km/h");

    // Alarmowanie o konieczności odpoczynku
    if (alarmActive) {
      display.setCursor(0, SCREEN_HEIGHT / 2 + 16);
      display.print("Odpocznij!");
    }

    display.display();
  }
}
