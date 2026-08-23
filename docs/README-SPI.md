DLa SPI
   ESP32                OLED SSD1306
  (GPIO Pin)             (Pin Number)
  ----------------------------------
     3V3   -------------- VCC
     GND   -------------- GND
     5V    -------------- N/C (Not connected, if using 3.3V)
     14    -------------- CLK (SCK, SPI clock)
     13    -------------- MOSI (SDA, SPI data)
      5    -------------- D/C (Data/Command)
      6    -------------- CS (Chip Select)
     N/C   -------------- RES (Reset, connected to OLED_RESET if available)
   ESP32                Neo 6M GPS Module
  (GPIO Pin)             (Pin Number)
  ------------------------------------
     3V3   -------------- VCC
     GND   -------------- GND
     17    -------------- RX (Serial RX, TX from GPS module)
     16    -------------- TX (Serial TX, RX from GPS module)
Objaśnienie połączeń:
Ekran OLED (Adafruit SSD1306) z interfejsem SPI:

VCC jest podłączone do zasilania 3.3V z ESP32.
GND jest podłączone do wspólnego masy z ESP32.
CLK (SCK) jest połączone z pinem GPIO 14 na ESP32, który jest zegarem SPI.
MOSI (SDA) jest połączone z pinem GPIO 13 na ESP32, który jest linią danych SPI.
D/C (Data/Command) jest połączone z pinem GPIO 5 na ESP32, służy do sterowania czy wysyłamy dane czy komendy do wyświetlacza.
CS (Chip Select) jest połączone z pinem GPIO 6 na ESP32, używane do wybierania urządzenia SPI.
RES (Reset) jest opcjonalne. Jeśli jest dostępne (OLED_RESET), powinno być połączone z pinem RESET na ESP32.
Moduł GPS (NPX Neo 6M):

VCC jest podłączone do zasilania 3.3V z ESP32.
GND jest połączone do wspólnego masy z ESP32.
RX jest połączone z pinem 17 na ESP32 (TX do modułu GPS).
TX jest połączone z pinem 16 na ESP32 (RX z modułu GPS).
Uwagi:
3V3 vs 5V: Upewnij się, że wszystkie urządzenia działają zgodnie z poziomem logicznym 3.3V, jeśli używasz ESP32. Jeśli masz ekran OLED, który pracuje na 5V, mogą być potrzebne dodatkowe przetwornice poziomów logicznych.
Podłączenie GPIO: Numery pinów GPIO na ESP32 (14, 13, 5, 6, 17, 16) można dostosować do swoich potrzeb, ale upewnij się, że zmienisz je również w kodzie Arduino, aby pasowały do konkretnych pinów, które używasz.
Dzięki temu schematowi powinieneś być w stanie poprawnie połączyć ekran OLED z interfejsem SPI oraz moduł GPS z ESP32.
