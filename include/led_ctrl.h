int switch_pwm_A = 0;
int switch_pwm_B = 0;

void switchPinInit(){
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);


  ledcSetup(channel_A, freq, 8);
  ledcAttachPin(PWMA, channel_A);


  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);

}


void switchEmergencyStop(){
  switch_pwm_A = 0;
  
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);

}


void switchPortCtrlA(float pwmInputA){
  int pwmIntA = round(pwmInputA);
  if(abs(pwmIntA) < 1e-6){
    Serial.println("check1");
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    return;
  }

  if(pwmIntA > 0){
    Serial.println("check2");
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    ledcWrite(channel_A, pwmIntA);
  }
  else{
    Serial.println("check3");
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    ledcWrite(channel_A,-pwmIntA);
  }
}




void switchCtrl(int pwmIntA) {
    switch_pwm_A = pwmIntA;
    // switch_pwm_B = pwmIntB;
    switchPortCtrlA(switch_pwm_A);
    // switchPortCtrlB(switch_pwm_B);
}


void lightCtrl(int pwmIn) {
  switch_pwm_A = pwmIn;
  switchPortCtrlA(-abs(switch_pwm_A));
}