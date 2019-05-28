
//Initialize the position when start.
void Ini_Arm(){
  //initial the coordination of the gripper
  pwm.setPWM(0, 0, JX_MIN + (L_angle - L_angle_ini) * JX_SC);
  pwm.setPWM(3, 0, JX_MAX - (S_angle - S_angle_ini) * JX_SC);
}


void Move(){

  double theta = (atan(Y_buf/X_buf)/PI*180) + 90.00;
  double l = sqrt(16.00 * 16.00 - (X_buf/2) * (X_buf/2) - (Y_buf/2) * (Y_buf/2));
  double X_stack = X_buf/2 + l * cos(theta/180*PI);
  double Y_stack = Y_buf/2 + l * sin(theta/180*PI);
  if(X_stack > 0){
   L_angle = 180.00 - asin(Y_stack / 16.00)/PI*180;
  }
  else{
    L_angle = asin(Y_stack / 16.00)/PI*180;
  }
    S_angle = asin((L_arm * sin(L_angle / 180 * PI) - Y_buf) / S_arm) / PI * 180;
    Serial.print("S_angle:");
    Serial.println(S_angle);
    Serial.print("L_angle:");
    Serial.println(L_angle);
  if(S_angle >= S_angle_ini && S_angle <= 175 && L_angle >= L_angle_ini && L_angle <= 180){
    X = X_buf;
    Y = Y_buf;
    pwm.setPWM(0, 0, JX_MIN + (L_angle - L_angle_ini) * JX_SC);
    pwm.setPWM(3, 0, JX_MAX - (S_angle - S_angle_ini) * JX_SC);
  }
  else{
    X_buf = X;
    Y_buf = Y;
  }
  return;
}





  
