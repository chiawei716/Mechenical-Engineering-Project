void dump_ini(){
  pwm.setPWM( PIN_DUMPER_1, 0, JX_MIN + Dumper_angle_1_OFF * JX_SC);
  pwm.setPWM( PIN_DUMPER_2, 0, JX_MIN + Dumper_angle_2_OFF * JX_SC);
  pwm.setPWM( PIN_DUMPER_3, 0, JX_MIN + Dumper_angle_3_OFF * JX_SC);
  pwm.setPWM( PIN_DUMPER_4, 0, JX_MIN + Dumper_angle_4_OFF * JX_SC);
}

void dump(int num){
  if(num == 1){
    for(; Dumper_angle_1 < Dumper_angle_1_ON - Dumper_velocity; Dumper_angle_1 += Dumper_velocity)
      pwm.setPWM( PIN_DUMPER_1, 0, JX_MIN + Dumper_angle_1 * JX_SC);
    Dumper_1 = true;
  }
  else if(num == 2){
    for(; Dumper_angle_2 > Dumper_angle_2_ON + Dumper_velocity; Dumper_angle_2 -= Dumper_velocity) 
      pwm.setPWM( PIN_DUMPER_2, 0, JX_MIN + Dumper_angle_2 * JX_SC);
    Dumper_2 = true;
  }
  else if(num == 3){
    for(; Dumper_angle_3 < Dumper_angle_3_ON - Dumper_velocity; Dumper_angle_3 += Dumper_velocity)
      pwm.setPWM( PIN_DUMPER_3, 0, MG996_MIN + Dumper_angle_3 * MG996_SC);
    Dumper_3 = true;
  }
  else if(num == 4){
    for(; Dumper_angle_4 > Dumper_angle_4_ON + Dumper_velocity; Dumper_angle_4 -= Dumper_velocity)
      pwm.setPWM( PIN_DUMPER_4, 0, MG996_MIN + Dumper_angle_4 * MG996_SC);
    Dumper_4 = true;
  }
  return;
}

void undump(int num){
  if(num == 1){
    for(; Dumper_angle_1 > Dumper_angle_1_OFF + Dumper_velocity*2; Dumper_angle_1 -= Dumper_velocity*2)
      pwm.setPWM( PIN_DUMPER_1, 0, JX_MIN + Dumper_angle_1 * JX_SC);
    Dumper_1 = false;
  }
  else if(num == 2){
    for(; Dumper_angle_2 < Dumper_angle_2_OFF - Dumper_velocity; Dumper_angle_2 += Dumper_velocity)
      pwm.setPWM( PIN_DUMPER_2, 0, JX_MIN + Dumper_angle_2 * JX_SC);
    Dumper_2 = false;
  } 
  else if(num == 3){
    for(; Dumper_angle_3 > Dumper_angle_3_OFF + Dumper_velocity; Dumper_angle_3 -= Dumper_velocity)
      pwm.setPWM( PIN_DUMPER_3, 0, MG996_MIN + Dumper_angle_3 * MG996_SC);
    Dumper_3 = false;
  }  
  else if(num == 4){
    for(; Dumper_angle_4 < Dumper_angle_4_OFF - Dumper_velocity; Dumper_angle_4 += Dumper_velocity)
      pwm.setPWM( PIN_DUMPER_4, 0, MG996_MIN + Dumper_angle_4 * MG996_SC);
    Dumper_4 = false;
  }
  return;
}
