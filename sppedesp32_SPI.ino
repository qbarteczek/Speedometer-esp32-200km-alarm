#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TinyGPS++.h>

// Definicje dla wyświetlacza OLED SPI
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    16
#define OLED_DC       17
#define OLED_CS       4
#define OLED_CLK      18
#define OLED_MOSI     23
#define OLED_MISO     19 // W przypadku SSD1306 może nie być używany

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);

// Obiekt dla TinyGPS++
TinyGPSPlus gps;

// Ustawienia dla GPS
#define RXPin 25 // Zmieniony pin RX
#define TXPin 26 // Zmieniony pin TX
#define GPSBaud 9600

// Utworzenie obiektu dla serialu GPS
HardwareSerial SerialGPS(1);

// Zmienne do śledzenia dziennego przebiegu
double dailyDistance = 0.0;
double lastLat = 0.0;
double lastLng = 0.0;
bool alarmActive = false;

void setup() {
  // Inicjalizacja serial monitor
  Serial.begin(115200);

  // Inicjalizacja serial dla GPS
  SerialGPS.begin(GPSBaud, SERIAL_8N1, RXPin, TXPin);

  // Inicjalizacja wyświetlacza OLED SPI
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
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

void loop() {
  // Odczyt danych z GPS
  while (SerialGPS.available() > 0) {
    gps.encode(SerialGPS.read());
  }

  // Aktualizacja przebiegu dziennego
  if (gps.location.isValid() && gps.location.isUpdated()) {
    if (lastLat != 0.0 && lastLng != 0.0) {
      double distance = TinyGPSPlus::distanceBetween(
        lastLat, lastLng,
        gps.location.lat(), gps.location.lng()
      );
      dailyDistance += distance / 1000.0; // Przeliczenie na kilometry
    }
    lastLat = gps.location.lat();
    lastLng = gps.location.lng();
  }

  // Sprawdzanie, czy alarm powinien być aktywowany
  if (dailyDistance >= 200.0 && gps.speed.kmph() > 0) {
    alarmActive = true;
  }

  // Wyłączanie alarmu po zatrzymaniu
  if (gps.speed.kmph() == 0) {
    alarmActive = false;
  }

  // Wyświetlanie informacji na OLED
  display.clearDisplay();

  // Wyświetlanie liczby widocznych satelitów w lewym górnym rogu
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  if (gps.satellites.isValid()) {
    display.print("Sat: ");
    display.print(gps.satellites.value());
  } else {
    display.print("Sat: N/A");
  }

  // Wyświetlanie wysokości nad poziomem morza w prawym górnym rogu
  display.setCursor(SCREEN_WIDTH - 64, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  if (gps.altitude.isValid()) {
    display.print("Alt: ");
    display.print(gps.altitude.meters());
    display.print(" m");
  } else {
    display.print("Alt: N/A");
  }

  // Wyświetlanie czasu z korekcją dla Polski (UTC+2) w lewym dolnym rogu
  display.setCursor(0, SCREEN_HEIGHT - 8);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
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
    display.print("Time: N/A");
  }

  // Wyświetlanie dziennego licznika kilometrów w prawym dolnym rogu
  display.setCursor(SCREEN_WIDTH - 64, SCREEN_HEIGHT - 8);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("KM: ");
  display.print(dailyDistance, 1);

  // Wyświetlanie prędkości w centralnym miejscu wyświetlacza
  display.setCursor((SCREEN_WIDTH / 2) - 20, (SCREEN_HEIGHT / 2) - 8);
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  if (gps.speed.isValid()) {
    display.print(gps.speed.kmph());
  } else {
    display.print("N/A");
  }
  display.setTextSize(1);
  display.setCursor((SCREEN_WIDTH / 2) + 20, (SCREEN_HEIGHT / 2) - 8);
  display.print(" km/h");

  // Alarmowanie o konieczności odpoczynku
  if (alarmActive) {
    display.setCursor(0, SCREEN_HEIGHT / 2 + 16);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.print("Odpocznij!");
  }

  display.display();
}
