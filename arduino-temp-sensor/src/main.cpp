#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
String cpu;
String gpu;
String cpu_clck;
String gpu_clck;

float cpu_hot = 85.0;
float gpu_hot = 75.0;

byte termo[] =
    {
        B00100,
        B01010,
        B01010,
        B01010,
        B01110,
        B11111,
        B11111,
        B01110};
byte lightning[] = {
    0b00100, //   *
    0b01100, //  **
    0b00110, //   **
    0b00011, //    **
    0b00101, //   * *
    0b01001, //  *  *
    0b00010, //    *
    0b00000  // (empty bottom)
};

void setup()
{
  lcd.begin();
  lcd.createChar(1, termo);
  lcd.createChar(2, lightning);
  lcd.backlight();
  lcd.home();
  lcd.setCursor(0, 0);
  Serial.begin(9600);
  lcd.print("Initializing");
  while (!Serial)
    ;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CPU: ");
  lcd.setCursor(0, 1);
  lcd.print("GPU: ");
}

void loop()
{
  if (cpu == "" || gpu == "")
  {
    lcd.setCursor(5, 0);
    lcd.print("N/A");
    lcd.setCursor(5, 1);
    lcd.print("N/A");
    while (!Serial.available())
      ;
  }
  if (Serial.available() > 0)
  {
    String myshit = Serial.readString();
    {
      cpu = myshit.substring(5, 9);
      gpu = myshit.substring(15, 19);

      cpu_clck = myshit.substring(28, 33);
      gpu_clck = myshit.substring(43, 47);
      float cpuClck = cpu_clck.toFloat();
      float gpuClck = gpu_clck.toFloat();

      if (cpuClck >= 1000)
      {
        cpu_clck = String(cpuClck / 1000).substring(0, 3) + "GHz";
      }
      else
      {
        cpu_clck = String(cpuClck).substring(0, 3) + "MHz";
      }

      if (gpuClck >= 1000)
      {
        gpu_clck = String(gpuClck / 1000).substring(0, 3) + "GHz";
      }
      else
      {
        gpu_clck = String(gpuClck).substring(0, 3) + "MHz";
      }

      float cpuTemp = cpu.toFloat();
      float gpuTemp = gpu.toFloat();
      lcd.setCursor(4, 0);
      lcd.write(1);
      lcd.print(cpu);

      if (cpuTemp >= cpu_hot)
      {
        lcd.setCursor(9, 0);
        lcd.print(" HOT          ");
      }
      else
      {
        lcd.setCursor(9, 0);
        lcd.write(2);
        lcd.print(cpu_clck + "MHz");
      }
      lcd.setCursor(4, 1);
      lcd.write(1);
      lcd.print(gpu);
      if (gpuTemp >= gpu_hot)
      {
        lcd.setCursor(9, 1);
        lcd.print(" HOT         ");
      }
      else if (gpuTemp < gpu_hot)
      {
        lcd.setCursor(9, 1);
        lcd.write(2);
        lcd.print(gpu_clck + "MHz");
      }
      while (!Serial.available())
        ;
    }
  }
}
