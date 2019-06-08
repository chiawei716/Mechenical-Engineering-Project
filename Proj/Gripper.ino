void Ini_Gripper(){
  pwm.setPWM( PIN_GRIPPER, 0, SG90_MIN + Gripper_angle * SG90_SC);
  pwm.setPWM( PIN_HEAD, 0, SG90_MIN + Head_angle * SG90_SC);
}

void Grap(){
  if(Gripper_angle < Gripper_angle_MAX){
    Gripper_angle += Grap_velocity;
    pwm.setPWM( PIN_GRIPPER, 0, SG90_MIN + Gripper_angle * SG90_SC);
  }
  return;
}

void Release(){
  if(Gripper_angle > Gripper_angle_ini){
    Gripper_angle -= Release_velocity;
    pwm.setPWM( PIN_GRIPPER, 0, SG90_MIN + Gripper_angle * SG90_SC);
  }
  return;
}

void Head_left(){
  if(Head_angle < Head_angle_MAX){
    Head_angle += Head_velocity;
    pwm.setPWM( PIN_HEAD, 0, SG90_MIN + Head_angle * SG90_SC);
  }
  return;
}

void Head_right(){
  if(Head_angle > Head_angle_MIN){
    Head_angle -= Head_velocity;
    pwm.setPWM( PIN_HEAD, 0, SG90_MIN + Head_angle * SG90_SC);
  }
  return;
}
