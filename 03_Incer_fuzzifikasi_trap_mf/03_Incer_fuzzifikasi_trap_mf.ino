// definisi tipe bentukan (struct)
typedef struct putaran
{
  float lambat;          /* fungsi keanggotaan lambat */
  float menengah;         /* fungsi keanggotaan menengah */
  float cepat;         /* fungsi keanggotaan cepat */
  float sangatCepat;         /* fungsi keanggotaan sangat cepat */
};


float trap_mf(float a, float b, float c, float d, float x) {
  /* a,b, c, dan d parameter trapesium */
  /* x adalah besaran yang ingin diketahui mf-nya*/
  return max(min(min(((x-a)/(b-a)),((d-x)/(d-c))),1), 0);
}

void setup() {
  Serial.begin(9600);
  putaran Putaran;
  
  /* menghitung membership grade dari suhu */
  float putaran_z = 80;
  
  Putaran.lambat = trap_mf(0,0,50,75, putaran_z);
  Serial.print("Putaran Lambat ");
  Serial.println(Putaran.lambat);
  Putaran.menengah = trap_mf(50,75,105,130, putaran_z);
  Serial.print("Putaran Menengah ");
  Serial.println(Putaran.menengah);
  Putaran.cepat = trap_mf(105,130,165,185, putaran_z);
  Serial.print("Putaran Cepat ");
  Serial.println(Putaran.cepat);  
  Putaran.sangatCepat = trap_mf(165,185,200,200, putaran_z);
  Serial.print("Putaran Sangat Cepat ");
  Serial.println(Putaran.sangatCepat);    
}

void loop() {
}
