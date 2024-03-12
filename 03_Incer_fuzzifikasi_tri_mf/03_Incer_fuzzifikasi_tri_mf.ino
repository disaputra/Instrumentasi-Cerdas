// definisi tipe bentukan (struct)
typedef struct kelembaban
{
  float kering;        /* fungsi keanggotaan kering */
  float sedang;        /* fungsi keanggotaan sedang */
  float lembab;        /* fungsi keanggotaan lembab */
  float basah;         /* fungsi keanggotaan basah  */
};

// fungsi keanggotaan segitiga
float tri_mf(float a, float b, float c, float x) {
  /* a,b, dan c parameter segitiga */
  /* x adalah besaran yang ingin diketahui mf-nya*/
  return max(min(((x-a)/(b-a)),((c-x)/(c-b))), 0);
}

void setup() {
  Serial.begin(9600);
  kelembaban Kelembaban;
  
  /* menghitung membership grade dari suhu */
  float kelembaban_y = 45;
  
  Kelembaban.kering = tri_mf(0,0,45,kelembaban_y);
  Serial.print("u kering = ");
  Serial.println(Kelembaban.kering);
  Kelembaban.sedang = tri_mf(0,45,75,kelembaban_y);
  Serial.print("u sedang = ");
  Serial.println(Kelembaban.sedang);  
  Kelembaban.lembab = tri_mf(45,75,100,kelembaban_y);
  Serial.print("u lembab = ");
  Serial.println(Kelembaban.lembab);  
  Kelembaban.basah = tri_mf(75,100,100,kelembaban_y);
  Serial.print("u basah = ");
  Serial.println(Kelembaban.basah);
}

void loop() {
}
