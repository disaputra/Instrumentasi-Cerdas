#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9, 10, 11, 3, 5, 6);

int i;
float sum_of_output[100];   // untuk penjumlahan output
float sum_of_output_temp; // untuk penjumlahan output temporary
float sum_of_weight[100];   // untuk penjumlahan weight
float sum_of_weight_temp; // untuk penjumlahan weight temporary
float output_1, output_2, max_output;
int rules1=0,rules2=0,rules3=0,rules4=0;
float weight1=0, weight2=0, weight3=0, weight4=0;

/** PART 1: Fuzzifikasi **/
typedef struct suhu{
  float sejuk;          /* membership sejuk */
  float hangat;         /* membership kotor */
  };

typedef struct kelembaban{
  float rendah;   /* membership rendah */
  float tinggi;   /* membership tinggi */
  };

typedef struct blower{ // dilihat dari output rules
  float pelan_1;       /* xxxxxxxxxxxxxxxx */
  float pelan_2;       /* xxxxxxxxxxxxxxxx */
  float kencang_1;     /* xxxxxxxxxxxxxxxx */
  float kencang_2;     /* xxxxxxxxxxxxxxxx */
  };

/** PART 3: Main function **/
void setup() {
  // put your setup code here, to run once:
lcd.begin(16, 4);
pinMode(A1,INPUT);
pinMode(A2,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // program mulai
  float suhu_z, kelembaban_z, blower_z;
  float anSuhuFloat, anKelembabanFloat;
  
  anSuhuFloat  = analogRead(A1);        // analogi sensor 1
  anKelembabanFloat = analogRead(A2);   // analogi sensor 2
  //suhu_z = map(anSuhuFloat,0,1023,20,40); 
  suhu_z = 27; // input suhu manual      
  //kelembaban_z = map(anKelembabanFloat,0,1023,0,100);
  kelembaban_z = 45; // input kelembaban manual 
  
  suhu Suhu;
  kelembaban Kelembaban;
  blower Blower;
  
  /* menghitung membership grade dari suhu */
  Suhu.sejuk = trap_mf(20,20,25,35,suhu_z);
  Suhu.hangat = trap_mf(25,35,40,40,suhu_z);
   
  /* menghitung membership grade dari kelembaban */
  Kelembaban.rendah = trap_mf(0,0,25,75,kelembaban_z);
  Kelembaban.tinggi = trap_mf(25,75,100,100,kelembaban_z);

  float weight1 = 0; 
  float weight2 = 0;
  float weight3 = 0;
  float weight4 = 0;
  
  /*** FUZZY RULE BASE ***/
  // (1) Jika Suhu Sejuk dan Kelembaban Tinggi maka Blower Pelan
  if (Suhu.sejuk>0 && Kelembaban.tinggi>0) {
    weight1 = min(Suhu.sejuk, Kelembaban.tinggi);
    }
    if(weight1>0){
      rules1 = 1;  
      }
      else{rules1 = 0;
      }
  
  // (2) Jika Suhu Sejuk dan Kelembaban Rendah maka Blower Pelan
  if (Suhu.sejuk>0 && Kelembaban.rendah>0) {
    weight2 = min(Suhu.sejuk, Kelembaban.rendah);
    }
    if(weight2>0){
      rules2 = 1;  
      }
      else{rules2 = 0;
      }
   
  // (3) Jika Suhu Hangat dan Kelembaban Tinggi maka Blower Kencang
  if (Suhu.hangat>0 && Kelembaban.tinggi>0) {
    weight3 = min(Suhu.hangat, Kelembaban.tinggi);
    }
    if(weight3>0){
      rules3 = 1;  
      }
      else{rules3 = 0;
      }
   
  // (4) Jika Suhu Hangat dan Kelembaban Rendah maka Blower Kencang
  if (Suhu.hangat>0 && Kelembaban.rendah>0){
    weight4 = min(Suhu.hangat, Kelembaban.rendah);
    }
    if(weight4>0){
      rules4 = 1;  
      }
      else{rules4 = 0;
      }
  
  /* Mamdani crisp mf */
  for(i=0;i<=100;i++){
    if(i==0){
      sum_of_output_temp = 0;
      sum_of_weight_temp = 0;
      }

    // PROSES AGREGASI
    // mencari output 1
    Blower.pelan_1 = mamdani_rule(0,0,25,75,weight1,i);
    Blower.pelan_2 = mamdani_rule(0,0,25,75,weight2,i);
    output_1 = max(Blower.pelan_1, Blower.pelan_2);  // proses agregasi 1
  
    // mencari output 2
    Blower.kencang_1 = mamdani_rule(25,75,100,100,weight3,i);
    Blower.kencang_2 = mamdani_rule(25,75,100,100,weight4,i);
    output_2 = max(Blower.kencang_1, Blower.kencang_2);  // proses agregasi 2
  
    max_output = max(output_1, output_2);
    sum_of_output[i] = max_output*i;
    sum_of_output_temp = sum_of_output[i] + sum_of_output_temp;
    sum_of_weight[i] = max_output;
    sum_of_weight_temp = sum_of_weight[i] + sum_of_weight_temp;
  }  
  
  blower_z = sum_of_output_temp/sum_of_weight_temp;

  if(i==100){
      i=0;
      }
      
  // program akhir
  
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

  delay(30);
}

/** PART 4: Implementasi fungsi **/

float trap_mf(float a, float b, float c, float d, float x) {
  /* a,b, dan c parameter trapesium */
  /* x adalah besaran yang ingin diketahui mf-nya*/
  return max(min(min(((x-a)/(b-a)),((d-x)/(d-c))),1), 0);
}

float mamdani_rule(float a, float b, float c, float d, float e, float x) {
  /* a,b,c dan d merupakan parameter menghitung output mamdani */
  /* x adalah besaran yang ingin diketahui mf-nya*/
  return max(min(min(((x-a)/(b-a)),((d-x)/(d-c))),e), 0);
}
