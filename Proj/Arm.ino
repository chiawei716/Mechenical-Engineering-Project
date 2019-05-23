
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
    Serial.print("X:");
    Serial.println(X);
    Serial.print("Y:");
    Serial.println(Y);
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

void To_Point(double goal_x, double goal_y){

  //Decide the velocity according to the range we need to move.
  double x_velocity = abs(goal_x - X) / 15;
  double y_velocity = abs(goal_y - Y) / 15;
  if(x_velocity > 0.5) x_velocity = 0.25;
  if(y_velocity > 0.5) y_velocity = 0.25;

  double x_origin = X;
  double y_origin = Y;

  while(1){
    if(X_buf != goal_x){
      if(X_buf < goal_x)
        X_buf += x_velocity;
      else if(X_buf > goal_x)
        X_buf -= x_velocity;
      if(X_buf > goal_x && x_origin <= goal_x) X_buf = goal_x;
      else if(X_buf < goal_x && x_origin >= goal_x) X_buf = goal_x;
    }
    if(Y_buf != goal_y){
      if(Y_buf < goal_y)
        Y_buf += y_velocity;
      else if(Y_buf > goal_y)
        Y_buf -= y_velocity;
      if(Y_buf > goal_y && y_origin <= goal_y) Y_buf = goal_y;
      else if(Y_buf < goal_y && y_origin >= goal_y) Y_buf = goal_y;
    }

    Move();
    delay(20);
    if(X_buf == goal_x && Y_buf == goal_y) break;
  }
}





  
