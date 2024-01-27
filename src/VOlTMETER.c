#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define CLK 7
#define DIN 6
#define DC  5
#define CS  4
#define RST 3
#define CH_1 8
#define CH_2 9
#define CH_3 10
#define CH_4 11

Adafruit_PCD8544 display = Adafruit_PCD8544(CLK, DIN, DC, CS,RST); // Esto debe ir en orden.

// Variables LEDs alarma
const int LED_A3 = 8;
const int LED_A2 = 9;
const int LED_A1 = 10;
const int LED_A0 = 11;
 // Voltajes en DC
 float v_1=0.0;
 float v_2=0.0;
 float v_3=0.0;
 float v_4 =0.0;
 // Voltajes en AC
 float va_1=0.0;
 float va_2=0.0;
 float va_3=0.0;
 float va_4 =0.0;
 

void setup() { 
  // Canales de voltaje
  pinMode(CH_1, INPUT);
  pinMode(CH_2, INPUT);
  pinMode(CH_3, INPUT);
  pinMode(CH_4, INPUT);
  // LEDs de alarma.
  pinMode(LED_A3, OUTPUT);
  pinMode(LED_A2, OUTPUT);
  pinMode(LED_A1, OUTPUT);
  pinMode(LED_A0, OUTPUT);
  //Configuraciones de la pantalla
  display.begin();
  display.setContrast(50);  // Ajusta el contraste según sea necesario
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(5,0);
  display.println("VOLTIMETRO");
  display.display();
  delay(2000);
  display.clearDisplay(); // Clear display

}



// Funcion medir voltaje
float mide_voltaje(float mag) {
  float max_val = 0;
    for (int i = 0; i < 100; i++) {
        float val = analogRead(mag);
        if (val > max_val) {
            max_val = val;
        }
        delayMicroseconds(150);
    }
    max_val = (((511.0-max_val)* 48/1023.0)); // normalizar y escalar.
    return max_val;
}

// Loop principal donde se ejecutan las funciones del voltimetro.

void loop() {
  float volt_1 = mide_voltaje(A5);
  float volt_2 = mide_voltaje(A4);
  float volt_3 = mide_voltaje(A3);
  float volt_4 = mide_voltaje(A2);
  display.clearDisplay();

  display.setCursor(0, 0);
  display.print("V1: ");
  display.println(volt_1, 2); // Mostrar el valor con 2 decimales

  display.setCursor(0, 10);
  display.print("V2: ");
  display.println(volt_2, 2);

  display.setCursor(0, 20);
  display.print("V3: ");
  display.println(volt_3, 2);

  display.setCursor(0, 30);
  display.print("V4: ");
  display.println(volt_4, 2);

  display.display();
}