// definisi tipe bentukan (struct)
typedef struct suhu
{
  float sejuk;          /* fungsi keanggotaan sejuk */
  float normal;         /* fungsi keanggotaan normal */
};

// definisi fungsi minimun dengan operator ternary
float minimum(float a, float b) { 
  return a<b ? a : b;
} 

// definisi fungsi maksimum dengan operator ternary
float maximum(float a, float b) {
  return a>b ? a : b;
}

float trap_mf(float a, float b, float c, float d, float x) {
  /* a,b, dan c parameter trapesium */
  /* x adalah besaran yang ingin diketahui mf-nya*/
  return maximum(minimum(minimum(((x-a)/(b-a)),((d-x)/(d-c))),1), 0);
}

void setup() {
  Serial.begin(9600);
  suhu Suhu;
  
  /* menghitung membership grade dari suhu */
  float suhu_in = 24;
  Suhu.normal = trap_mf(15,24,27,35, suhu_in);
  Serial.print(Suhu.normal,3);
}

void loop() {
}
