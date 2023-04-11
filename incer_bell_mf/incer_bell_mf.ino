// definisi tipe bentukan (struct)
typedef struct suhu
{
  float sejuk;          /* fungsi keanggotaan sejuk */
  float panas;         /* fungsi keanggotaan normal */
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
  float suhu_in = 51;
  Suhu.panas = beta_mf(5,45, suhu_in);
  Serial.print(Suhu.panas,3);
}

void loop() {
}
