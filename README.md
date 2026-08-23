# Speedometer-esp32-200km-alarm

Prędkościomierz GPS z wbudowanym alarmem po przekroczeniu 200 km/h.

## 📦 Lista Części (BOM)
Aby złożyć to urządzenie od zera, potrzebujesz zakupić następujące elementy:
- **Mikrokontroler:** Płytka ESP32 (np. WROOM-32 DevKit V1 lub ESP32-CAM)
- **Główny osprzęt:** Moduł GPS (np. NEO-6M), Ekran SSD1306/TFT
- **Zasilanie:** 
  - Ogniwo Li-Ion 18650 (np. z odzysku ze starych baterii laptopowych)
  - Koszyk na pojedyncze ogniwo 18650 (tzw. Battery Holder 18650 x1)
  - Moduł ładowania TP4056 (najlepiej w wersji z zabezpieczeniem, z wejściem USB-C)
- **Inne:**
  - Włącznik kołyskowy KCD11 (10x15mm)
  - Przewody połączeniowe (zworki typu DuPont do testów na płytce stykowej, lub kabelki do lutowania 24AWG)

## ⚡ Schemat Zasilania (Bateria 18650)
Urządzenie jest przystosowane do pracy bezprzewodowej. Zasilanie opiera się na popularnym ogniwie 18650.
1. Pola **B+** i **B-** na module TP4056 łączymy z plusem i minusem koszyka z ogniwem 18650.
2. Pole **OUT+** z modułu TP4056 lutujemy do jednej nóżki przełącznika kołyskowego.
3. Drugą nóżkę przełącznika łączymy z pinem **5V** lub **VIN** (w zależności od nazwy pinu na Twoim ESP32).
4. Pole **OUT-** z modułu TP4056 łączymy bezpośrednio z pinem **GND** na ESP32.
5. Moduły zasilamy zazwyczaj wyprowadzając pin **3.3V** z ESP32 do odpowiedniego złącza czujnika.

*Uwaga: Ładowanie baterii odbywa się poprzez podłączenie ładowarki od telefonu do gniazda USB modułu TP4056 (a NIE do gniazda na płycie ESP32!)*

## 🚀 Jak złożyć i uruchomić?
1. **Wgraj kod:** Jeśli nie masz wiedzy programistycznej, zajrzyj do katalogu `arduino_ide` i postępuj zgodnie z instrukcjami z tamtejszego pliku. W przeciwnym razie użyj PlatformIO, otwórz główny folder i wgraj oprogramowanie kablem USB.
2. **Połącz elektronikę:** Skompletuj części z listy BOM, podłącz najpierw czujniki do ESP32 na tzw. "pająka" i przetestuj układ na biurku.
3. **Wydrukuj obudowę:** Pobierz skrypt z katalogu `hardware/enclosure.scad`, otwórz go w darmowym programie OpenSCAD, wyeksportuj do pliku `.stl` (klawisz F6, potem F7) i wrzuć do swojego slicera (np. Cura / PrusaSlicer).
4. **Montaż końcowy:** Umieść TP4056 tak, aby port USB wychodził przez dolny mały otwór. Wstaw baterię, umieść ESP32 w obudowie. Przewlecz kable włącznika przez boczny otwór, wciśnij włącznik.

## 📊 Interpretacja danych
Poczekaj na złapanie fixa (sygnału) GPS na zewnątrz (może zająć do minuty). Prędkość pokaże się na ekranie.
