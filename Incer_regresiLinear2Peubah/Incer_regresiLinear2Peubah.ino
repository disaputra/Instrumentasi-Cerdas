#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9, 10, 11, 3, 5, 6);

// koefisien regresi hasil latih dengan dua peubah
float b1 = 0.519598;
float b2 = 0.05193;
float b0 = 28.32138;
float y;

float X1 = 11;
float X2 = 130;

// koefisien regresi hasil latih dengan satu peubah
//float a0 = 35.64;
//float a1 = 0.74;

// inisialisasi variabel
int  pred;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 4);
//  pinMode(A1,INPUT);
//  pinMode(A2,INPUT);
  Serial.begin(115200);
  
  y = b0 + b1*X1 + b2*X2;
}

void loop() {
  // variabel masukan
//  float anSensorX1, anSensorX2, X1, X2;
//  anSensorX1  = analogRead(A1);        // analogi sensor 1
//  anSensorX2 = analogRead(A2);          // analogi sensor 2
//  X1 = map(anSensorX1,0,1023,1,683);
//  X2 = map(anSensorX2,0,1023,23,32);

  // hasil prediksi 1 peubah
  //pred = hasilPrediksi(X1);
//  float y = b0 + b1*X1 + b2*X2;

  // hasil preodiksi 2 peubah
//  pred = hasilPrediksi(X1,X2);

  // menampilkan hasil prediksi
  Serial.println(y);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Regresi Linear 2 peubah");
  lcd.setCursor(0, 1);
  lcd.print("Sensor1 = ");
  lcd.setCursor(11, 1);
  lcd.print(X1);
  lcd.setCursor(0, 2);
  lcd.print("Sensor2 = ");
  lcd.setCursor(11, 2);
  lcd.print(X2);
  lcd.setCursor(0, 3);
  lcd.print("Hasil   = ");
  lcd.setCursor(11, 3);
  lcd.print(pred);

  delay(1000);
}

// fungsi regresi 1 peubah
//float hasilPrediksi(float sensorX1){
//  return a0 + a1*sensorX1; 
//  }

  // fungsi regresi 2 peubah
//float hasilPrediksi(float sensorX1, float sensorX2){
//  return b0 + b1*sensorX1 + b2*sensorX2; // rumus regresi 2 peubah
//  }
