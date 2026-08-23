// Parametryczna Obudowa 3D
// Miejsce na ESP32, ogniwo 18650 i moduł TP4056

wall = 2;
x_width = 50;
y_length = 90;
z_height = 30;

module case_body() {
    difference() {
        // Główna bryła
        cube([x_width, y_length, z_height]);
        
        // Wnętrze (wydrążenie)
        translate([wall, wall, wall])
            cube([x_width - 2*wall, y_length - 2*wall, z_height]);
            
        // Otwór na przełącznik (10x15mm kołyskowy) na bocznej ściance
        translate([-1, 20, 10])
            cube([5, 10, 15]);
            
        // Otwór na port USB z TP4056
        translate([x_width/2 - 5, -1, 3])
            cube([10, 5, 5]);
            
        // Otwór na ekran SSD1306/TFT
translate([10, 10, z_height-2]) cube([27, 27, 5]);
    }
}

case_body();
