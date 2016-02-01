const int shift = 2;
const int base = 20;
const int base2 = -5;

/* const int "pin_name" = "pin_number + arduino_shift
   For example ONE_PIN represents BCD 1. Its pin number on
   Autopol is 1, but on Arduino, its pin number is 22 = 1+shift
   Similarly, for EIGHT_PIN represents BCD 8. Its number on
   Autopol is 15, but on Arduino, its pin number is 25 = 15+shift2 
*/
   
const int ONE_PIN = base + (1 * shift);       // Arduino pin = 22 
const int TWO_PIN = base2 + (14 * shift);     // Arduino pin = 23
const int FOUR_PIN = base + (2 * shift);      // Arduino pin = 24
const int EIGHT_PIN = base2 + (15 * shift);   // Arduino pin = 25, etc ...
const int DEC_PIN = base + (3 * shift); 
const int ONE0_PIN = base2 + (16 * shift);
const int TWO0_PIN = base + (4 * shift); 
const int FOUR0_PIN = base2 + (17 * shift);
const int EIGHT0_PIN = base + (5 * shift); 
const int DEC0_PIN = base2 + (18 * shift);
const int ONE00_PIN = base + (6 * shift); 
const int TWO00_PIN = base2 + (19 * shift);
const int FOUR00_PIN = base + (7 * shift); 
const int EIGHT00_PIN = base2 + (20 * shift);
const int LATCH_PIN = base + (8 * shift); 
const int ONE000_PIN = base2 + (21 * shift);
const int TWO000_PIN = base + (9 * shift); 
const int FOUR000_PIN = base2 + (22 * shift);
const int EIGHT000_PIN = base + (10 * shift); 
const int GND_PIN = base2 + (23 * shift);
const int ONE0000_PIN = base + (11 * shift); 
const int TWO0000_PIN = base2 + (24 * shift);
const int FOUR0000_PIN = base + (12 * shift); 
const int EIGHT0000_PIN = base2 + (25 * shift);
const int SIGN_PIN = base + (13 * shift); 
const int VCC_PIN = base2 + (26 * shift);

void setup() {
  // put your setup code here, to run once:
  pinMode(ONE_PIN, INPUT);        pinMode(TWO_PIN, INPUT);
  pinMode(FOUR_PIN, INPUT);       pinMode(EIGHT_PIN, INPUT);
  pinMode(DEC_PIN, INPUT);        pinMode(ONE0_PIN, INPUT);
  pinMode(TWO0_PIN, INPUT);       pinMode(FOUR0_PIN, INPUT);
  pinMode(EIGHT0_PIN, INPUT);     pinMode(DEC0_PIN, INPUT);
  pinMode(ONE00_PIN, INPUT);      pinMode(TWO00_PIN, INPUT);
  pinMode(FOUR00_PIN, INPUT);     pinMode(EIGHT00_PIN, INPUT);
  pinMode(LATCH_PIN, OUTPUT);     pinMode(ONE000_PIN, INPUT);
  pinMode(TWO000_PIN, INPUT);     pinMode(FOUR000_PIN, INPUT);
  pinMode(EIGHT000_PIN, INPUT);   //pinMode(GND_PIN, INPUT);
  pinMode(ONE0000_PIN, INPUT);    pinMode(TWO0000_PIN, INPUT);
  pinMode(FOUR0000_PIN, INPUT);   pinMode(EIGHT0000_PIN, INPUT);
  pinMode(SIGN_PIN, INPUT);       //pinMode(VCC_PIN, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:  
  Serial.println(convert());  //just report the value every 500ms
  delay(500);
}

float convert() {
  digitalWrite(LATCH_PIN, HIGH);      // latch the value
  
  int one = digitalRead(ONE_PIN);                     int two = digitalRead(TWO_PIN) * 2;
  int four = digitalRead(FOUR_PIN) * 4;               int eight = digitalRead(EIGHT_PIN) * 8;
  boolean dec = digitalRead(DEC_PIN);                 int one0 = digitalRead(ONE0_PIN) * 10;
  int two0 = digitalRead(TWO0_PIN) * 20;              int four0 = digitalRead(FOUR0_PIN) * 40;
  int eight0 = digitalRead(EIGHT0_PIN) * 80;          boolean dec0 = digitalRead(DEC0_PIN);
  int one00 = digitalRead(ONE00_PIN) * 100;           int two00 = digitalRead(TWO00_PIN) * 200;
  int four00 = digitalRead(FOUR00_PIN) * 400;         int eight00= digitalRead(EIGHT00_PIN) * 800;
  /* latch ignored */                                 int one000 = digitalRead(ONE000_PIN) * 1000;
  int two000 = digitalRead(TWO000_PIN) * 2000;        int four000 = digitalRead(FOUR000_PIN) * 4000;
  int eight000 = digitalRead(EIGHT000_PIN) * 8000;    // gnd pin ignored
  int one0000 = digitalRead(ONE0000_PIN) * 10000;     long two0000 = digitalRead(TWO0000_PIN) * 20000;
  long four0000 = digitalRead(FOUR0000_PIN) * 40000;  long eight0000 = digitalRead(EIGHT0000_PIN) * 80000;
  boolean sign = digitalRead(SIGN_PIN);               // vcc pin ignored

  digitalWrite(LATCH_PIN, LOW);      // unlatch the value
  
  long long_result = eight0000 + four0000 + two0000 + one0000 + 
                     eight000 + four000 + two000 + one000 +
                     eight00 + four00 + two00 + one00 +
                     eight0 + four0 + two0 + one0 +
                     eight + four + two + one;
  
  // change sign if necessary
  if (sign) {
    long_result *= -1;
  }
  
  return long_result/1000.0;
  
  // add the correct decimal place
//  if (dec) {
//    return long_result/100.0;
//  }
//  else if (dec0) {
//    return long_result/1000.0;
//  }
//  else {
//    return long_result;
//  }
}

