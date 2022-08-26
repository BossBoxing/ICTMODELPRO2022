float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;
long currentTime = 0;
int Slow_L=60,Slow_R=60;

void Stop(int t) {
  motor(1, 0); motor(2, 0);
  delay(t);
}
void Fw(int t) {
  motor(1, 70); motor(2, 70);
  delay(t);
}
void FwCan(int t) {
  motor(1, 20); motor(2, 20);
  delay(t);
}
void BkCan(int t) {
  motor(1, -20); motor(2, -20);
  delay(t);
}
void Bk(int t) {
  motor(1, -30); motor(2, -30);
  delay(t);
}
void Log(int t) {
  motor(1, -10); motor(2, -10);
  delay(t);
}
void Place() {
  Stop(1);
  for (int i = Lift; i > Lift_Max; i-=5)
  {
    servo(A0, i); delay(15);
  }
  delay(200);
  Lift = Lift_Max;
  servo(A1, Pin_Max);  delay(300);
  Pin = Pin_Max;
  Stop(1);
}
int findError(){
  if(S_LL > Ref_LL && S_L < Ref_L && S_R < Ref_R && S_RR < Ref_RR)
  {
    return ((((S_LL*2) + S_L) ) - (S_R + S_RR));
  }
  else if(S_LL > Ref_LL && S_L > Ref_L && S_R < Ref_R && S_RR < Ref_RR)
  {
    return ((((S_LL*2) + S_L) ) - (S_R + S_RR));
  }

  else if(S_LL < Ref_LL && S_L < Ref_L && S_R < Ref_R && S_RR > Ref_RR)
  {
    return (((S_LL + S_L) ) - (S_R + (S_RR*2)));
  }
  else if(S_LL < Ref_LL && S_L < Ref_L && S_R > Ref_R && S_RR > Ref_RR)
  {
    return (((S_LL + S_L) ) - (S_R + (S_RR*2)));
  }

  else
  {
    return (((S_LL + S_L) ) - (S_R + S_RR));
  }
}
void calculate_pid(int power) {
  error = findError();
  P = error;
  I = I + previous_I;
  D = error - previous_error;
  PID_value = (0.7 * P) + (0.5 * I) + (8 * D);
  previous_I = I;
  previous_error = error;
}
void motor_control(int power) {
  int left_motor_speed = power - PID_value;
  int right_motor_speed = power + PID_value;

  if (left_motor_speed > 100) {
    left_motor_speed = 100;
  }
  if (right_motor_speed > 100) {
    right_motor_speed = 100;
  }

  motor(1, left_motor_speed);
  motor(2, right_motor_speed);
}
void Pid(int power) {
  calculate_pid(power);
  motor_control(power);
}
void calculate_pid_circle(int power) {
  error = findError();
  P = error;
  I = I + previous_I;
  D = error - previous_error;
  PID_value = (0.35 * P) + (0.5 * I) + (1 * D);
  previous_I = I;
  previous_error = error;
}
void PidTime(int power, unsigned int Time) {
  currentTime = millis();
  while (millis() - currentTime < Time) {
    Pid(power);
  }
}
void Track() {
  Pid(70);
}
void TrackSlow() {
  Pid(50);
}
void TrackTime(int Time) {
  int looptime = 0;
  while (looptime < Time) {
    Track();
    delay(1);
    looptime++;
  }
}
void TrackSlowTime(int Time) {
  int looptime = 0;
  while (looptime < Time) {
    TrackSlow();
    delay(1);
    looptime++;
  }
}
void TR90() {
  Fw(40);
  Stop(50);
  motor(1, Slow_L); motor(2, -(Slow_R + 8)); delay(100);
  // while (S_R <= Ref_R) {
  //   motor(1, Slow_L);
  //   motor(2, -(Slow_R + 10));
  // }
  while (S_R < Ref_R) {
    motor(1, Slow_L);
    motor(2, -(Slow_R + 10));
  }
}
void TL90() {
  Fw(40);
  Stop(50);
  motor(1, -(Slow_L + 8)); motor(2, Slow_R); delay(120);
  // while (S_L <= Ref_L) {
  //   motor(1, -(Slow_L + 10));
  //   motor(2, Slow_R);
  // }
  while (S_L < Ref_L) {
    motor(1, -(Slow_L + 10));
    motor(2, Slow_R);
  }
}
void U90(){
  Stop(50);
  //motor(1, -40);  motor(2, 40); delay(200);

    // TL90();
  Stop(50);
  motor(1, -(Slow_L + 8)); motor(2, Slow_R); delay(120);
  // while (S_L <= Ref_L) {
  //   motor(1, -(Slow_L + 10));
  //   motor(2, Slow_R);
  // }
  while (S_L < Ref_L) {
    motor(1, -(Slow_L + 10));
    motor(2, Slow_R);
  }
  
    // TL90();
  Stop(50);
  motor(1, -(Slow_L + 8)); motor(2, Slow_R); delay(120);
  // while (S_L <= Ref_L) {
  //   motor(1, -(Slow_L + 10));
  //   motor(2, Slow_R);
  // }
  while (S_L < Ref_L) {
    motor(1, -(Slow_L + 10));
    motor(2, Slow_R);
  }
  // Stop(30);
}
void PlaceCan() {
    Stop(100);
    Place();
      
    motor(1, -60);  motor(2, -60); delay(100);
    Stop(30);

    while(S_LLL < Ref_LLL && S_RRR < Ref_RRR){
      motor(1, -60);  motor(2, -60);
    }

    U90();

    if ((S_LLL < Ref_LLL) || (S_RRR < Ref_RRR))
    {
      while ((S_LLL < Ref_LLL) && (S_RRR < Ref_RRR))
      {
        Track();
      }
    }
    TrackTime(100);
}

void FFF(){
  while(S_LLL < Ref_LLL && S_RRR < Ref_RRR){Track();}
  TrackTime(100);
}
void FFF_Can(){
  while(S_LLL < Ref_LLL && S_RRR < Ref_RRR){Track();}
  TrackTime(50);
}
void LLL(){
  while(S_LLL < Ref_LLL && S_RRR < Ref_RRR){Track();}
  TL90();
  TrackTime(100);
}
void RRR(){
  while(S_LLL < Ref_LLL && S_RRR < Ref_RRR){Track();}
  TR90();
  TrackTime(100);
}

void Start() {
  motor(1, Slow_R); motor(2, Slow_L);
  delay(600);
  if(S_LLL > Ref_LLL || S_RRR > Ref_RRR){
    while(S_LLL > Ref_LLL || S_RRR > Ref_RRR)
    {
      motor(1, Slow_R); motor(2, Slow_L);
      delay(10);
    }
    motor(1, Slow_R); motor(2, Slow_L);
    delay(100);
  }
}
void Finish() {
  while ((S_LL < Ref_LLL) && (S_RR < Ref_RR)) {
    Track();
  }
  Fw(500);
  Stop(100);
  beep();
  delay(200);
}

void Wait() {
  Stop(100);
  while (SW_OK() == true) {
    Stop(10);
  }
  while (SW_OK() == false) {

  }
  beep();
}
void ok() {
  XIO();
  servo(A0, Lift);    delay(1000);
  servo(A1, Pin);     delay(500);
  setTextSize(2);
  Serial1.begin(9600);

  while (SW_OK() == 1) {
    function = knob(0, 5);
    setTextSize(5);
    oled(50, 15, "%d", function);
    oledClear();
    if (SW_OK() == 0)
    {
      setTextSize(1);
      beep();
      break;
    }
  }
  oledClear();
}
void readServo() {
  int p, d;
  delay(800);
  while (SW_OK() == 1) {
    p = knob(1, 3);
    oled(0, 0, "Port = %d ", p);
    oledClear();
  }
  delay(500);
  while (SW_OK() == 1) {
    d = knob(1, 180);
    servo(p, d);
    oled(0, 0, "Port = %d ", p);
    oled(0, 15, "results = %d ", d);
    oledClear();
    delay(20);
  }
}

void setSensor() {
  delay(500);
  int Max[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  int Min[9] = {100, 100, 100, 100, 100, 100, 100, 100, 100};
  int i = 1;

  while (SW_OK() == 1) {
    if (S_LLL > Max[0]) {
      Max[0] = S_LLL;
      i = 1;
    }
    if (S_LLL < Min[0]) {
      Min[0] = S_LLL;
      i = 1;
    }

    if (S_LL > Max[1]) {
      Max[1] = S_LL;
      i = 1;
    }
    if (S_LL < Min[1]) {
      Min[1] = S_LL;
      i = 1;
    }

    if (S_L > Max[2]) {
      Max[2] = S_L;
      i = 1;
    }
    if (S_L < Min[2]) {
      Min[2] = S_L;
      i = 1;
    }

    if (S_C > Max[3]) {
      Max[3] = S_C;
      i = 1;
    }
    if (S_C < Min[3]) {
      Min[3] = S_C;
      i = 1;
    }

    if (S_R > Max[4]) {
      Max[4] = S_R;
      i = 1;
    }
    if (S_R < Min[4]) {
      Min[4] = S_R;
      i = 1;
    }

    if (S_RR > Max[5]) {
      Max[5] = S_RR;
      i = 1;
    }
    if (S_RR < Min[5]) {
      Min[5] = S_RR;
      i = 1;
    }

    if (S_RRR > Max[6]) {
      Max[6] = S_RRR;
      i = 1;
    }
    if (S_RRR < Min[6]) {
      Min[6] = S_RRR;
      i = 1;
    }

    if (i == 1) {
      oledClear();
      oled(0, 0,  "Sen  B  W |Sen  B  W");
      oled(0, 7,  "---------------------");
      oled(0, 13, "LLL %d %d", Min[0], Max[0]);
      oled(60, 13, "|RR    %d %d", Min[5], Max[5]);
      oled(0, 23, "LL  %d %d", Min[1], Max[1]);
      oled(60, 23, "|RRR   %d %d", Min[6], Max[6]);
      oled(0, 33, "L   %d %d", Min[2], Max[2]);
      // oled(60, 33, "|RRR  %d %d", Min[7], Max[7]);
      oled(0, 43, "C    %d %d", Min[3], Max[3]);
      // oled(60, 43, "|RRRR %d %d", Min[8], Max[8]);
      oled(0, 53, "R    %d %d", Min[4], Max[4]);
      delay(10);
      i = 0;
    }
  }
  beep();
  EEPROM.update(startReffAddress + 1, (Max[0] + Min[0]) / 2); // LLL
  EEPROM.update(startReffAddress + 2, (Max[1] + Min[1]) / 2); // LL
  EEPROM.update(startReffAddress + 3, (Max[2] + Min[2]) / 2); // L
  EEPROM.update(startReffAddress + 4, (Max[3] + Min[3]) / 2); // C
  EEPROM.update(startReffAddress + 5, (Max[4] + Min[4]) / 2); // R
  EEPROM.update(startReffAddress + 6, (Max[5] + Min[5]) / 2); // RR
  EEPROM.update(startReffAddress + 7, (Max[6] + Min[6]) / 2); // RRR
  // EEPROM.update(7, (Max[7] + Min[7]) / 2);
  // EEPROM.update(8, (Max[8] + Min[8]) / 2);
  oledClear();
  oled(0, 0,  "Sensor Ref|Sensor Ref");
  oled(0, 7,  "---------------------");
  oled(0, 13, "LLL   %d |RR      %d", EEPROM.read(startReffAddress + 1), EEPROM.read(startReffAddress + 6));
  oled(0, 23, "LL    %d |RRR     %d", EEPROM.read(startReffAddress + 2), EEPROM.read(startReffAddress + 7));
  oled(0, 33, "L     %d", EEPROM.read(startReffAddress + 3));
  oled(0, 43, "C      %d", EEPROM.read(startReffAddress + 4));
  oled(0, 53, "R      %d", EEPROM.read(startReffAddress + 5));
  while (1) {}
}

void Stop() {
  motor(1, 0);  motor(2, 0);
  // oledClear();
}
void Fast_forward() { //เดินหน้า เร็ว
  motor(1, power_manual_fast_L);
  motor(2, power_manual_fast_R);
}
void Fast_backward() { //ถอยหลัง เร็ว
  motor(1, -power_manual_fast_L);
  motor(2, -power_manual_fast_R);
}
void Fast_left() { //เลี้ยวซ้าย เร็ว
  motor(1, -power_manual_fast_L + 45);
  motor(2, power_manual_fast_R - 45);
}
void Fast_righ() { //เลี้ยวขวา เร็ว
  motor(1, power_manual_fast_L - 45);
  motor(2, -power_manual_fast_R + 45);
}


void Slow_forward() { //เดินหน้า ช้า
  motor(1, power_manual_slow_L);
  motor(2, power_manual_slow_R);
}
void Slow_backward() { //ถอยหลัง ช้า
  motor(1, -power_manual_slow_L);
  motor(2, -power_manual_slow_R);
}
void Slow_left() { //เลี้ยวซ้าย ช้า
  motor(1, -power_manual_slow_L + 15);
  motor(2, power_manual_slow_R - 15);
}
void Slow_righ() { //เลี้ยวขวา ช้า
  motor(1, power_manual_slow_L - 15);
  motor(2, -power_manual_slow_R + 15);
}

void Lift_up() { //ยกมือขึ้น
  Lift += 6;
  Lift = (Lift > Lift_Min) ? Lift_Min : Lift;
  servo(A0, Lift);
}
void Lift_down() { //ยกมือลง
  Lift -= 6;
  Lift = (Lift < Lift_Max) ? Lift_Max : Lift;
  servo(A0, Lift);
}
void Pin_in() { //หนีบ
  Pin += 5;
  Pin = (Pin > Pin_Min) ? Pin_Min : Pin;
  servo(A1, Pin);
}
void Pin_out() { //วาง
  Pin -= 6;
  Pin = (Pin < Pin_Max) ? Pin_Max : Pin;
  servo(A1, Pin);
}
