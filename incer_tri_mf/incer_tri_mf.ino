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

float tri_mf(float a, float b, float c, float x) {
  /* a,b, dan c parameter segitiga */
  /* x adalah besaran yang ingin diketahui mf-nya*/
  return maximum(minimum(((x-a)/(b-a)),((c-x)/(c-b))), 0);
}

void setup() {
  Serial.begin(9600);
  suhu Suhu;
  
  /* menghitung membership grade dari suhu */
  float suhu_in = 25;
  Suhu.normal = tri_mf(15,25,35,suhu_in);
  Serial.print(Suhu.normal);
}

void loop() {
}
