#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9, 10, 11, 3, 5, 6);

// prototipe fungsi
float sigmoid(float x);
float bunga_mana(float panjang, float lebar);

// bobot dan bias hasil latih
float w1 = 1.9934079982481685;
float w2 = 0.5521519085296531;
float b = -6.456822842060632; 

// inisialisasi variabel
float x, z, pred;

// variabel masukan
//float pan = 4.5;
//float leb = 1;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 4);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  Serial.begin(115200);
}

void loop() {
  // variabel masukan
  float anPanjang, anLebar, pan, leb;
  anPanjang  = analogRead(A1);        // analogi sensor 1
  anLebar = analogRead(A2);   // analogi sensor 2
  pan = norm(anPanjang,0,1023,0,6);
  leb = norm(anLebar,0,1023,0,3);
  //pan = 2.0;
  //leb = 1.0;

  // kalkulasi feed forward
  pred = bunga_mana(pan,leb);

  // hitung treshold
  Serial.print(pred);
  if (pred <= 0.5){
    Serial.println(" Bunga Biru");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Neural Network");
    lcd.setCursor(0, 1);
    lcd.print("In1 =  ");
    lcd.setCursor(9, 1);
    lcd.print(pan);
    lcd.setCursor(0, 2);
    lcd.print("In2 =  ");
    lcd.setCursor(9, 2);
    lcd.print(leb);
    lcd.setCursor(0, 3);
    lcd.print("Hasil =  ");
    lcd.setCursor(9, 3);
    lcd.print("Biru");
    }
    else{
      Serial.println(" Bunga Merah");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Neural Network");
      lcd.setCursor(0, 1);
      lcd.print("In1 =  ");
      lcd.setCursor(9, 1);
      lcd.print(pan);
      lcd.setCursor(0, 2);
      lcd.print("In2 =  ");
      lcd.setCursor(9, 2);
      lcd.print(leb);
      lcd.setCursor(0, 3);
      lcd.print("Hasil =  ");
      lcd.setCursor(9, 3);
      lcd.print("Merah");
      }
  delay(1000);
}

// fungsi sigmoid
float sigmoid(float x) {
  return 1/(1+exp(-x));
  }
  
// fungsi feed forward
float bunga_mana(float panjang, float lebar){
  z = panjang*w1 + lebar*w2 + b;
  return sigmoid(z);
  }

// fungsi pemetaan
float norm(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
