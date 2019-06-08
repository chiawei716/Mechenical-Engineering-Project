//Initialize the position when start.
void Ini_Arm(){
  //initial the coordination of the gripper
  pwm.setPWM( PIN_LONG_ARM, 0, JX_MIN + (L_angle_ini - L_angle_default) * JX_SC);
  pwm.setPWM( PIN_SHORT_ARM, 0, JX_MAX - (S_angle_ini - S_angle_default) * JX_SC);
  pwm.setPWM( PIN_ARM_ROTATION, 0, MG996_MIN + Arm_angle * MG996_SC);
}

//Move by (X, Y)
void Move(){
  
  double theta = (atan(Y_buf/X_buf)/PI*180) + 90.00;
  double l = sqrt(L_arm * L_arm - (X_buf/2) * (X_buf/2) - (Y_buf/2) * (Y_buf/2));
  double X_stack = X_buf/2 + l * cos(theta/180*PI);
  double Y_stack = Y_buf/2 + l * sin(theta/180*PI);
  
  if(X_stack > 0) L_angle = 180.00 - asin(Y_stack / 16.00)/PI*180;
  else L_angle = asin(Y_stack / 16.00)/PI*180;
  S_angle = asin((L_arm * sin(L_angle / 180 * PI) - Y_buf) / S_arm) / PI * 180;
  
  if(S_angle >= S_angle_default && S_angle <= 175 && L_angle >= L_angle_default && L_angle <= 180){
    X = X_buf;
    Y = Y_buf;
    pwm.setPWM( PIN_LONG_ARM, 0, JX_MIN + (L_angle - L_angle_default) * JX_SC);
    pwm.setPWM( PIN_SHORT_ARM, 0, JX_MAX - (S_angle - S_angle_default) * JX_SC);
  }
  else{
    X_buf = X;
    Y_buf = Y;
  }
  return;
}

//Rotate the arm (CW)
void Arm_right(){
  if(Arm_angle > Arm_angle_ini){
    Arm_angle -= Rotate_velocity;
    pwm.setPWM( PIN_ARM_ROTATION, 0, MG996_MIN + Arm_angle * MG996_SC);
  }
  return;
}

//Rotate the arm (CCW)
void Arm_left(){
  if(Arm_angle < 176){
    Arm_angle += Rotate_velocity;
    pwm.setPWM( PIN_ARM_ROTATION, 0, MG996_MIN + Arm_angle * MG996_SC);
  }
  return;
}

//Move arm to (X,Y) automaticly
void To_Point(double goal_x, double goal_y, double goal_arm_angle){
  stopped();
  int looping = 120;

  //Decide the velocity according to the range we need to move.
  double x_velocity = abs(goal_x - X) / auto_Velocity_scale;
  double y_velocity = abs(goal_y - Y) / auto_Velocity_scale;
  double rotate_velocity = abs(goal_arm_angle - Arm_angle) / auto_Velocity_scale;
  if(x_velocity > auto_X_MAX_velocity) x_velocity = auto_X_MAX_velocity;
  if(y_velocity > auto_Y_MAX_velocity) y_velocity = auto_Y_MAX_velocity;
  if(rotate_velocity > auto_Rotate_MAX_velocity) rotate_velocity = auto_Rotate_MAX_velocity;

  double x_origin = X;
  double y_origin = Y;
  double arm_angle_origin = Arm_angle;

  while(1){
    looping--;
    if(X_buf != goal_x){
      //Move
      if(X_buf < goal_x) X_buf += x_velocity;
      else X_buf -= x_velocity;
      //Check
      if(x_origin <= goal_x && X_buf > goal_x) X_buf = goal_x;
      else if( x_origin >= goal_x && X_buf < goal_x) X_buf = goal_x;
    }
    if(Y_buf != goal_y){
      //Move
      if(Y_buf < goal_y) Y_buf += y_velocity;
      else Y_buf -= y_velocity;
      //Check
      if(y_origin <= goal_y && Y_buf > goal_y) Y_buf = goal_y;
      else if( y_origin >= goal_y && Y_buf < goal_y) Y_buf = goal_y;
    }
    if(Arm_angle != goal_arm_angle){
      //Move
      if(Arm_angle < goal_arm_angle)  Arm_angle += rotate_velocity;
      else Arm_angle -= rotate_velocity;
      if(arm_angle_origin >= goal_arm_angle && Arm_angle < goal_arm_angle) Arm_angle = goal_arm_angle;
      else if(arm_angle_origin <= goal_arm_angle && Arm_angle > goal_arm_angle) Arm_angle = goal_arm_angle;
    }

    Move();
    pwm.setPWM(PIN_ARM_ROTATION, 0, MG996_MIN + Arm_angle * MG996_SC);

    if(X_buf == goal_x && Y_buf == goal_y && Arm_angle == goal_arm_angle) break;
    if(looping == 0) break;
    delay(4);
    Serial.println(looping);
  }
}
