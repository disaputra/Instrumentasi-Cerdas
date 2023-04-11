#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9, 10, 11, 3, 5, 6);

int rules1=0,rules2=0,rules3=0,rules4=0;
float weight1=0, weight2=0, weight3=0, weight4=0;

/** PART 1: Definisi Type Bentukan **/
typedef struct suhu{
  float sejuk;          /* membership sejuk */
  float hangat;         /* membership kotor */
};

typedef struct kelembaban{
  float rendah;   /* membership rendah */
  float tinggi;   /* membership tinggi */
};

/** PART 2: Main function **/
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 4);
//  pinMode(A1,INPUT);
//  pinMode(A2,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float  suhu_z, kelembaban_z, blower_z;
  float anSuhuFloat, anKelembabanFloat;

//  anSuhuFloat  = analogRead(A1);        // analogi sensor 1
//  anKelembabanFloat = analogRead(A2);   // analogi sensor 2
//  suhu_z = map(anSuhuFloat,0,1023,20,40);      
//  kelembaban_z = map(anKelembabanFloat,0,1023,0,100);
  suhu_z = 36; // input suhu manual
  kelembaban_z = 76; // input kelembaban manual 
  
  suhu Suhu;
  kelembaban Kelembaban;
  
  /* menghitung membership grade dari suhu */
  Suhu.sejuk = trap_mf(20,20,25,35,suhu_z);
  Suhu.hangat = trap_mf(25,35,40,40,suhu_z);
   
  /* menghitung membership grade dari kelembaban */
  Kelembaban.rendah = trap_mf(0,0,25,75,kelembaban_z);
  Kelembaban.tinggi = trap_mf(25,75,100,100,kelembaban_z);

  /* Sugeno crisp mf */
  float pelan = 25;
  float kencang = 75;

  float weight1 = 0; 
  float weight2 = 0;
  float weight3 = 0;
  float weight4 = 0;
  
  /*** FUZZY INFERENCE RULE ***/
  // (1) Jika Suhu Sejuk dan Kelembaban Tinggi maka Blower Pelan
  if (Suhu.sejuk>0 && Kelembaban.tinggi>0) {
    weight1 = min(Suhu.sejuk, Kelembaban.tinggi);
  }
  if(weight1>0){
    rules1=1;  
    }
    else{rules1=0;
    }
  
  // (2) Jika Suhu Sejuk dan Kelembaban Rendah maka Blower Pelan
  if (Suhu.sejuk>0 && Kelembaban.rendah>0) {
    weight2 = min(Suhu.sejuk, Kelembaban.rendah);
  }
   if(weight2>0){
    rules2=1;  
    }
    else{rules2=0;
    }
   
  // (3) Jika Suhu Hangat dan Kelembaban Tinggi maka Blower Kencang
  if (Suhu.hangat>0 && Kelembaban.tinggi>0) {
    weight3 = min(Suhu.hangat, Kelembaban.tinggi);
  }
   if(weight3>0){
    rules3=1;  
    }
    else{rules3=0;
    }
   
  // (4) Jika Suhu Hangat dan Kelembaban Rendah maka Blower Kencang
  if (Suhu.hangat>0 && Kelembaban.rendah>0) {
    weight4 = min(Suhu.hangat, Kelembaban.rendah);
  }
   if(weight4>0){
    rules4=1;  
    }
    else{rules4=0;
    }

  // defuzzyfikasi
 /*** WEIGHTED AVERAGE ***/
  float weightedSum = weight1*pelan + weight2*pelan + weight3*kencang + weight4*kencang;
  float sumofWeight = weight1 + weight2 + weight3 + weight4;
  blower_z = weightedSum/sumofWeight;  

  lcd.clear();
  lcd.setCursor(0, 0); // (kolom, baris)
  lcd.print("Kandang Ayam");
  lcd.setCursor(0, 1);
  lcd.print("Suhu: ");
  lcd.setCursor(8, 1);
  lcd.print(suhu_z);
  lcd.setCursor(0, 2);
  lcd.print("Lembab: ");
  lcd.setCursor(8, 2);
  lcd.print(kelembaban_z);
  lcd.setCursor(0, 3);
  lcd.print("Out: ");
  lcd.setCursor(8, 3);
  lcd.print(blower_z);
  
  Serial.print(suhu_z);
  Serial.print(",");
  Serial.print(kelembaban_z);
  Serial.print(",");
  Serial.print(blower_z);
  Serial.print(",");
  Serial.print(rules1);
  Serial.print(",");
  Serial.print(rules2);
  Serial.print(",");
  Serial.print(rules3);
  Serial.print(",");
  Serial.println(rules4);
  delay(100);
}

float trap_mf(float a, float b, float c, float d, float x) {
  /* a,b, dan c parameter trapesium */
  /* x adalah besaran yang ingin diketahui mf-nya*/
  return max(min(min(((x-a)/(b-a)),((d-x)/(d-c))),1), 0);
}
