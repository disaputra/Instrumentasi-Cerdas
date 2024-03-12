
// definisi tipe bentukan (struct)
typedef struct suhu
{
  float dingin;          /* fungsi keanggotaan dingin */
  float normal;         /* fungsi keanggotaan normal */
  float hangat;         /* fungsi keanggotaan hangat */
  float panas;         /* fungsi keanggotaan panas */
};

float beta_mf(float beta, float gamma, float x) {
  /* beta, gamma parameter bell */
  /* x adalah besaran yang ingin diketahui mf-nya*/
  return 1/(1+ pow(abs((x-gamma)/beta),2));
}

void setup() {
  Serial.begin(9600);
  suhu Suhu;
  /* menghitung membership grade dari suhu */
  float suhu_in = 15;
  
  Suhu.dingin = beta_mf(10,0, suhu_in);
  Serial.print("Suhu Dingin ");
  Serial.println(Suhu.dingin,3);
  Suhu.normal = beta_mf(10,20, suhu_in);
  Serial.print("Suhu Normal ");
  Serial.println(Suhu.normal,3);
  Suhu.hangat = beta_mf(10,40, suhu_in);
  Serial.print("Suhu Hangat ");
  Serial.println(Suhu.hangat,3);
  Suhu.panas = beta_mf(10,60, suhu_in);
  Serial.print("Suhu Panas ");
  Serial.println(Suhu.panas,3);
}

void loop() {
}
