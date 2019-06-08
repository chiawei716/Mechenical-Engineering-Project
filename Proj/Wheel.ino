
void Wheel_setup(){
  pinMode(Motor1_a, OUTPUT);
  pinMode(Motor1_b, OUTPUT);
  pinMode(Motor2_a, OUTPUT);
  pinMode(Motor2_b, OUTPUT);
  pinMode(Motor3_a, OUTPUT);
  pinMode(Motor3_b, OUTPUT);
}

void stopped(){
  digitalWrite(Motor1_a, LOW);
  digitalWrite(Motor1_b, LOW);
  digitalWrite(Motor2_a, LOW);
  digitalWrite(Motor2_b, LOW);
  digitalWrite(Motor3_a, LOW);
  digitalWrite(Motor3_b, LOW);
}

void move_backward(){
  digitalWrite(Motor1_a, LOW); 
  digitalWrite(Motor1_b, HIGH);
  digitalWrite(Motor3_a,LOW);
  digitalWrite(Motor3_b,LOW);
  delay(40);
  digitalWrite(Motor2_a, HIGH);
  digitalWrite(Motor2_b, LOW);
}

void move_forward(){
  digitalWrite(Motor1_a, HIGH); 
  digitalWrite(Motor1_b, LOW);
  digitalWrite(Motor2_a, LOW);
  analogWrite(Motor2_b, 245);
  digitalWrite(Motor3_a,LOW);
  digitalWrite(Motor3_b,LOW);
}

void move_right_forward(){
  digitalWrite(Motor1_a,LOW);
  digitalWrite(Motor1_b,LOW);
  digitalWrite(Motor2_a, LOW);  //Move backward
  digitalWrite(Motor2_b, HIGH);
  digitalWrite(Motor3_a, HIGH);
  digitalWrite(Motor3_b, LOW);
}

void move_left_forward(){
  digitalWrite(Motor1_a, HIGH); 
  digitalWrite(Motor1_b,LOW);
  digitalWrite(Motor2_a, LOW);
  digitalWrite(Motor2_b,LOW);
  digitalWrite(Motor3_a, LOW);
  digitalWrite(Motor3_b, HIGH);
}    
void move_right_backward(){
  digitalWrite(Motor1_a, LOW);
  digitalWrite(Motor1_b, HIGH);
  digitalWrite(Motor2_a, LOW);
  digitalWrite(Motor2_b,LOW);
  digitalWrite(Motor3_a, HIGH);
  digitalWrite(Motor3_b,LOW );
}
void move_left_backward(){
  digitalWrite(Motor1_a, LOW);
  digitalWrite(Motor1_b, LOW);
  digitalWrite(Motor2_a, HIGH);
  digitalWrite(Motor2_b,LOW);
  digitalWrite(Motor3_a, LOW);
  digitalWrite(Motor3_b,HIGH );
}


void move_rightward() {
  if(righting == false){
    digitalWrite(Motor1_a,LOW);
    digitalWrite(Motor1_b,LOW);
    //analogWrite(Motor1_b,30);
    digitalWrite(Motor2_a,LOW);
    digitalWrite(Motor2_b,LOW);
    //analogWrite(Motor2_b,60);
    digitalWrite(Motor3_a,HIGH);
    digitalWrite(Motor3_b,LOW);
    delay(35);
  }
  digitalWrite(Motor1_a,LOW);
  analogWrite(Motor1_b,120);
  digitalWrite(Motor2_a,LOW);
  analogWrite(Motor2_b,145);
  digitalWrite(Motor3_a,HIGH);
  digitalWrite(Motor3_b,LOW);
}

void move_leftward() {
  digitalWrite(Motor1_a,HIGH);
  analogWrite(Motor1_b,110);
  digitalWrite(Motor2_a,HIGH);
  analogWrite(Motor2_b,130);
  digitalWrite(Motor3_a,LOW);
  digitalWrite(Motor3_b,HIGH);
}
void CCW(){
    digitalWrite(Motor1_a,LOW);//OK
    analogWrite(Motor1_b,155);
    digitalWrite(Motor2_a,LOW);
    analogWrite(Motor2_b,155);
    digitalWrite(Motor3_a,LOW);
    analogWrite(Motor3_b,155);
  }
void CW(){
    digitalWrite(Motor1_a,HIGH);//OK
    analogWrite(Motor1_b,100 );
    digitalWrite(Motor2_a,HIGH);
    analogWrite(Motor2_b,100);
    digitalWrite(Motor3_a,HIGH);
    analogWrite(Motor3_b,100);
  }
/*
void CW(){
    digitalWrite(Motor1_a,HIGH);//OK
    digitalWrite(Motor1_b,LOW );
    digitalWrite(motor2in1,HIGH);
    digitalWrite(motor2in2,LOW);
    digitalWrite(Motor3_a,HIGH);
    digitalWrite(Motor3_b,LOW);
  }

void CCW(){
    digitalWrite(motor1in1,LOW);//OK
    digitalWrite(motor1in2,HIGH );
    digitalWrite(motor2in1,LOW);
    digitalWrite(motor2in2,HIGH);
    digitalWrite(Motor3_a,LOW);
    digitalWrite(Motor3_b,HIGH);
  }
*/
void move_slow_backward(){
  digitalWrite(Motor1_a, LOW);
  analogWrite(Motor1_b, 75);
  digitalWrite(Motor2_a, HIGH);
  analogWrite(Motor2_b, 180);
  digitalWrite(Motor3_a, LOW);
  digitalWrite(Motor3_b, LOW);   
}

void move_slow_forward() {
  digitalWrite(Motor1_a, HIGH); 
  analogWrite(Motor1_b, 180);
  digitalWrite(Motor2_a, LOW);
  analogWrite(Motor2_b, 75);
  digitalWrite(Motor3_a,LOW);
  digitalWrite(Motor3_b,LOW);
}

void move_slow_rightward() {
  digitalWrite(Motor1_a,LOW);
  analogWrite(Motor1_b,33);
  digitalWrite(Motor2_a,LOW);
  analogWrite(Motor2_b,42);
  digitalWrite(Motor3_a,HIGH);
  analogWrite(Motor3_b,190);
}

void move_slow_leftward() {
  digitalWrite(Motor1_a,HIGH);
  analogWrite(Motor1_b,215);
  digitalWrite(Motor2_a,HIGH);
  analogWrite(Motor2_b,215);
  digitalWrite(Motor3_a,LOW);
  analogWrite(Motor3_b,68);
}
/*
void step_back(){
    digitalWrite(motor1in1,LOW);
    digitalWrite(motor1in2,LOW); 
    digitalWrite(motor2in1, LOW);  
    digitalWrite(motor2in2, HIGH);
    digitalWrite(motor3in1, HIGH)
    digitalWrite(motor3in2, LOW);
    delay(100);
    digitalWrite(motor1in1,LOW);
    digitalWrite(motor1in2,LOW);
    digitalWrite(motor2in1,LOW);
    digitalWrite(motor2in2,LOW);
    digitalWrite(motor3in1,LOW);
    digitalWrite(motor3in2,LOW);  
  }
void step_right(){
      digitalWrite(motor1in1, HIGH); //OK!
      digitalWrite(motor1in2,LOW);
      digitalWrite(motor2in1, LOW);
      analogWrite(motor2in2,150);
      digitalWrite(motor3in1, LOW);
      analogWrite(motor3in2, 150);
      delay(100);
      digitalWrite(motor1in1,LOW);
      digitalWrite(motor1in2,LOW);
      digitalWrite(motor2in1,LOW);
      digitalWrite(motor2in2,LOW);
      digitalWrite(motor3in1,LOW);
      digitalWrite(motor3in2,LOW);  
  
  }
void step_left(){
      digitalWrite(motor1in1, LOW); //OK!
      digitalWrite(motor1in2, HIGH);
      digitalWrite(motor2in1, HIGH);
      analogWrite(motor2in2,150);
      digitalWrite(motor3in1, HIGH);
      analogWrite(motor3in2, 150);
      delay(100);
      digitalWrite(motor1in1,LOW);
      digitalWrite(motor1in2,LOW);
      digitalWrite(motor2in1,LOW);
      digitalWrite(motor2in2,LOW);
      digitalWrite(motor3in1,LOW);
      digitalWrite(motor3in2,LOW);  
 }*/
