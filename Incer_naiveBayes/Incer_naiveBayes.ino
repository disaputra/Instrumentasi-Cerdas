#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9, 10, 11, 3, 5, 6);

//--------------------------------------------
float nilaiAktualSuhu;
float nilaiAktualKelembaban;
//--------------------------------------------
float meanSuhuNormal             = 22.5;
float meanSuhuPeringatan         = 22.5;
float meanSuhuBahaya             = 22.5;
float meanKelembabanNormal       = 47.5;
float meanKelembabanPeringatan   = 47.5;
float meanKelembabanBahaya       = 47.5;
//--------------------------------------------
float stdDeviasiSuhuNormal            = 2.738612788;
float stdDeviasiKelembabanNormal      = 8.21583863;
float stdDeviasiSuhuPeringatan        = 8.215838363;
float stdDeviasiKelembabanPeringatan  = 13.69306394;
float stdDeviasiSuhuBahaya            = 13.69306394;
float stdDeviasiKelembabanBahaya      = 19.17028951;
//--------------------------------------------
float probSuhuNormal;
float probSuhuPeringatan;
float probSuhuBahaya;
float probKelembabanNormal;
float probKelembabanPeringatan;
float probKelembabanBahaya;
float probTotalNormal;
float probTotalPeringatan;
float probTotalBahaya;
//--------------------------------------------
//rumus dari hasil perhitungan 
// P = (1/(sqrt(2*3.14) * standar_deviasi_kondisi_suhu))*exp(-((pow((nilaiAktualSuhu - mean_suhu), 2)))/(2*(pow((standar_deviasi_kondisi), 2))));
float probDensityFunction (float stdDeviasi, float nilaiBaru, float nilaiMean){
  return (1/(sqrt(2*3.14) * stdDeviasi))*exp(-((pow((nilaiBaru - nilaiMean), 2)))/(2*(pow((stdDeviasi), 2))));
  }
//--------------------------------------------

//--------------------------------------------
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 4);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  Serial.begin(115200);
}
void loop() {
  // variabel masukan
  float anSensorX1, anSensorX2, X1, X2;
  anSensorX1  = analogRead(A1);        // analogi sensor 1
  anSensorX2 = analogRead(A2);   // analogi sensor 2
  X1 = norm(anSensorX1,0,1023,10,50);
  X2 = norm(anSensorX2,0,1023,10,90);
  
  nilaiAktualSuhu = X1;
  nilaiAktualKelembaban = X2;
  //--------------------------------------------
  // algoritma naive bayes 
  probSuhuNormal = probDensityFunction(stdDeviasiSuhuNormal, nilaiAktualSuhu, meanSuhuNormal);
  probKelembabanNormal = probDensityFunction(stdDeviasiKelembabanNormal, nilaiAktualKelembaban, meanKelembabanNormal);
  probTotalNormal = probSuhuNormal + probKelembabanNormal;
  //  //--------------------------------------------
  probSuhuPeringatan = probDensityFunction(stdDeviasiSuhuPeringatan, nilaiAktualSuhu, meanSuhuPeringatan);
  probKelembabanPeringatan = probDensityFunction(stdDeviasiKelembabanPeringatan, nilaiAktualKelembaban, meanKelembabanPeringatan);
  probTotalPeringatan       = probSuhuPeringatan + probKelembabanPeringatan;
  //  //--------------------------------------------
  probSuhuBahaya = probDensityFunction(stdDeviasiSuhuBahaya, nilaiAktualKelembaban, meanKelembabanBahaya);
  probKelembabanBahaya = probDensityFunction(stdDeviasiKelembabanBahaya, nilaiAktualKelembaban, meanKelembabanBahaya);
  probTotalBahaya       = probSuhuBahaya + probKelembabanBahaya;
  //--------------------------------------------
  if(probTotalNormal > probTotalPeringatan && probTotalNormal > probTotalBahaya){
    Serial.println("Normal");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Naive Bayes Classifier");
    lcd.setCursor(0, 1);
    lcd.print("Sensor1 = ");
    lcd.setCursor(11, 1);
    lcd.print(X1);
    lcd.setCursor(0, 2);
    lcd.print("Sensor2 = ");
    lcd.setCursor(11, 2);
    lcd.print(X2);
    lcd.setCursor(0, 3);
    lcd.print("Out = ");
    lcd.setCursor(6, 3);
    lcd.print("Normal");
    delay(1000);
//    digitalWrite(pin_kipas, LOW);
//    digitalWrite(pin_led_kipas, LOW);
  }else if(probTotalPeringatan > probTotalNormal && probTotalPeringatan > probTotalBahaya) {
    Serial.println("Peringatan");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Naive Bayes Classifier");
    lcd.setCursor(0, 1);
    lcd.print("Sensor1 = ");
    lcd.setCursor(11, 1);
    lcd.print(X1);
    lcd.setCursor(0, 2);
    lcd.print("Sensor2 = ");
    lcd.setCursor(11, 2);
    lcd.print(X2);
    lcd.setCursor(0, 3);
    lcd.print("Out = ");
    lcd.setCursor(6, 3);
    lcd.print("Peringatan");
    delay(1000);
//    digitalWrite(pin_kipas, HIGH);
//    digitalWrite(pin_led_kipas, HIGH);
  }else if(probTotalBahaya > probTotalNormal && probTotalBahaya > probTotalPeringatan){
    Serial.println("Panas");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Naive Bayes Classifier");
    lcd.setCursor(0, 1);
    lcd.print("Sensor1 = ");
    lcd.setCursor(11, 1);
    lcd.print(X1);
    lcd.setCursor(0, 2);
    lcd.print("Sensor2 = ");
    lcd.setCursor(11, 2);
    lcd.print(X2);
    lcd.setCursor(0, 3);
    lcd.print("Out = ");
    lcd.setCursor(6, 3);
    lcd.print("Panas");
    delay(1000);
//    digitalWrite(pin_kipas, HIGH);
//    digitalWrite(pin_led_kipas, HIGH);
  }
}

// fungsi pemetaan
float norm(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
