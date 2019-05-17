void Ini_Gripper(){
  pwm.setPWM(5, 0, SG90_MIN);
  pwm.setPWM(8, 0, SG90_MIN + head_angle * SG90_SC);
}

void Grap(){
  if(gripper_angle < 178){
    gripper_angle += 2;
    pwm.setPWM(5, 0, SG90_MIN + gripper_angle * SG90_SC);
  }
  return;
}

void Release(){
  if(gripper_angle > 2){
    gripper_angle -= 2;
    pwm.setPWM(5, 0, SG90_MIN + gripper_angle * SG90_SC);
  }
  return;
}

void Head_right(){
  if(head_angle < 178){
    head_angle += 2;
    pwm.setPWM(8, 0, SG90_MIN + head_angle * SG90_SC);
    Serial.println(head_angle);
  }
  return;
}

void Head_left(){
  if(head_angle > 2){
    head_angle -= 2;
    pwm.setPWM(8, 0, SG90_MIN + head_angle * SG90_SC);
    Serial.println(head_angle);
  }
  return;
}
