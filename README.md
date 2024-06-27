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
