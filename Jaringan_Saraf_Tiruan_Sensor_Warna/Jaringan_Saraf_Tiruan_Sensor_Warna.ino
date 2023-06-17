/*
 * Jaringan Saraf Tiruan Sensor Warna
 * Referensi : https://wangready.wordpress.com/2013/02/11/penerapan-jst-pada-sensor-warna/
 * Bandung
 */

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define sensorPinA0 A0
#define sensorPinA1 A1
#define sensorPinA2 A2

unsigned char readADC(unsigned char adc_input) {
  ADMUX = adc_input | (0x40);
  ADCSRA |= (1 << ADSC);
  while (ADCSRA & (1 << ADSC));
  return ADCH;
}

float W1[3][9] = {
  {-0.0552, 0.2011, -0.0775, -0.2480, 0.0759, -0.6707, 2.7798, 0.3610, -0.2911},
  {7.2505, 2.3445, 0.4637, -2.1228, -3.8145, -0.3211, 4.3576, -2.4067, -0.6085},
  {1.4586, -1.5528, -0.7996, -0.8682, 0.4503, -0.1916, -0.7845, 0.2793, -0.5579}
};

float W2[9][3] = {
  {-8.8792, 8.8622, -2.1603},
  {-1.7257, 0.2986, 0.8022},
  {-0.8877, -7.1093, 7.0267},
  {0.8346, -0.5394, -0.5260},
  {2.9642, -3.0433, -4.9297},
  {-0.9731, -0.2062, -0.4736},
  {5.9101, -5.9067, -1.8619},
  {3.0977, -3.0036, -3.7159},
  {0.7786, 0.5356, 0.2736}
};

float X[9];
float Y[3];
int kelas[3];
float v = 0;

void run_JST() {
  unsigned int i, j, jj;

  for (i = 0; i < 9; i++) {
    v = 0;

    for (j = 0; j < 3; j++) {
      v += X[j] * W1[j][i];
    }

    X[i] = 1 / (1 + (exp(-v)));
  }

  for (jj = 0; jj < 3; jj++) {
    v = 0;

    for (j = 0; j < 9; j++) {
      v += X[j] * W2[j][jj];
    }

    Y[jj] = 1 / (1 + (exp(-v)));
  }

  for (jj = 0; jj < 3; jj++) {
    if (Y[jj] < 0.5) {
      kelas[jj] = 0;
    } else {
      kelas[jj] = 1;
    }
  }
}

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("APLIKASI JST");

  ADMUX = (1 << REFS0);
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);

  delay(1000);
}

void loop() {
  unsigned char data_adc[3];
  char kata[16];
  const char* warna;

  lcd.clear();
  lcd.setCursor(0, 0);

  for (unsigned int i = 0; i < 3; i++) {
    data_adc[i] = readADC(i);
  }

  sprintf(kata, "%d=%d=%d", data_adc[0], data_adc[1], data_adc[2]);
  lcd.print(kata);

  int CP[3];
  for (unsigned int i = 0; i < 3; i++) {
    CP[i] = data_adc[i];
  }

  for (unsigned int i = 0; i < 3; i++) {
    X[i] = CP[i];
  }

  run_JST();

  if (kelas[0] == 1 && kelas[1] == 0 && kelas[2] == 0) {
    warna = "merah";
  } else if (kelas[0] == 0 && kelas[1] == 1 && kelas[2] == 0) {
    warna = "biru";
  } else if (kelas[0] == 0 && kelas[1] == 0 && kelas[2] == 1) {
    warna = "hijau";
  }

  lcd.setCursor(0, 1);
  sprintf(kata, "%d=%d=%d ", kelas[0], kelas[1], kelas[2]);
  lcd.print(kata);
  lcd.print(warna);

  delay(1000);
}
