
Ekran OLED (Adafruit SSD1306) z interfejsem I2C:
   ESP32                OLED SSD1306
  (GPIO Pin)             (Pin Number)
  ----------------------------------
     3V3   -------------- VCC
     GND   -------------- GND
     22    -------------- SCL (I2C Clock)
     21    -------------- SDA (I2C Data)
Moduł GPS (NPX Neo 6M) do ESP32:
   ESP32                Neo 6M GPS Module
  (GPIO Pin)             (Pin Number)
  ------------------------------------
     3V3   -------------- VCC
     GND   -------------- GND
     17    -------------- RX (Serial RX, TX from GPS module)
     16    -------------- TX (Serial TX, RX from GPS module)

Ekran OLED (Adafruit SSD1306) z interfejsem I2C:

VCC jest podłączone do zasilania 3.3V z ESP32.
GND jest podłączone do wspólnego masy z ESP32.
SCL (I2C Clock) jest połączone z pinem GPIO 22 na ESP32, który jest liniią zegarową interfejsu I2C.
SDA (I2C Data) jest połączone z pinem GPIO 21 na ESP32, który jest linią danych interfejsu I2C.
Moduł GPS (NPX Neo 6M):

VCC jest podłączone do zasilania 3.3V z ESP32.
GND jest połączone do wspólnego masy z ESP32.
RX jest połączone z pinem 17 na ESP32 (TX do modułu GPS).
TX jest połączone z pinem 16 na ESP32 (RX z modułu GPS).
Uwagi:
3V3 vs 5V: Upewnij się, że wszystkie urządzenia działają zgodnie z poziomem logicznym 3.3V, jeśli używasz ESP32. Moduły OLED i GPS zazwyczaj operują na napięciu 3.3V, więc nie powinno być potrzeby stosowania przetworników poziomów logicznych.
Podłączenie GPIO: Numery pinów GPIO na ESP32 (22, 21, 17, 16) można dostosować do swoich potrzeb, ale upewnij się, że zmienisz je również w kodzie Arduino, aby pasowały do konkretnych pinów, które używasz.
Dzięki temu schematowi powinieneś być w stanie poprawnie połączyć ekran OLED z interfejsem I2C oraz moduł GPS z ESP32.
