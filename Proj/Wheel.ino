
void Wheel_setup(){ // /ok
  pinMode(Motor1_a, OUTPUT);
  pinMode(Motor1_b, OUTPUT);
  pinMode(Motor2_a, OUTPUT);
  pinMode(Motor2_b, OUTPUT);
  pinMode(Motor3_a, OUTPUT);
  pinMode(Motor3_b, OUTPUT);
}

void stopped(){  // OK
  digitalWrite(Motor1_a, LOW);
  digitalWrite(Motor1_b, LOW);
  digitalWrite(Motor2_a, LOW);
  digitalWrite(Motor2_b, LOW);
  digitalWrite(Motor3_a, LOW);
  digitalWrite(Motor3_b, LOW);
}

void move_forward(){ // OK
  digitalWrite(Motor1_a, LOW); 
  digitalWrite(Motor1_b, HIGH);
  digitalWrite(Motor2_a, HIGH);
  digitalWrite(Motor2_b, LOW);
  digitalWrite(Motor3_a,LOW);
  digitalWrite(Motor3_b,LOW);
}

void move_backward() { //OK
  digitalWrite(Motor1_a, HIGH); 
  digitalWrite(Motor1_b, LOW);
  digitalWrite(Motor2_a, LOW);
  digitalWrite(Motor2_b, HIGH);
  digitalWrite(Motor3_a,LOW);
  digitalWrite(Motor3_b,LOW);
}

void move_left_backward(){   //OK
  digitalWrite(Motor1_a,LOW);
  digitalWrite(Motor1_b,LOW);
  digitalWrite(Motor2_a, LOW);  //Move backward
  digitalWrite(Motor2_b, HIGH);
  digitalWrite(Motor3_a, HIGH);
  digitalWrite(Motor3_b, LOW);
}

void move_right_backward(){
  digitalWrite(Motor1_a, HIGH); 
  digitalWrite(Motor1_b,LOW);
  digitalWrite(Motor2_a, LOW);
  digitalWrite(Motor2_b,LOW);
  digitalWrite(Motor3_a, LOW);
  digitalWrite(Motor3_b, HIGH);
}    
void move_left_forward(){
  digitalWrite(Motor1_a, LOW);
  digitalWrite(Motor1_b, HIGH);
  digitalWrite(Motor2_a, LOW);
  digitalWrite(Motor2_b,LOW);
  digitalWrite(Motor3_a, HIGH);
  digitalWrite(Motor3_b,LOW );
}
void move_right_forward(){
  digitalWrite(Motor1_a, LOW);
  digitalWrite(Motor1_b, LOW);
  digitalWrite(Motor2_a, HIGH);
  digitalWrite(Motor2_b,LOW);
  digitalWrite(Motor3_a, LOW);
  digitalWrite(Motor3_b,HIGH );
}


void move_leftward() {
  digitalWrite(Motor1_a,LOW);
  analogWrite(Motor1_b,150);
  digitalWrite(Motor2_a,LOW);
  analogWrite(Motor2_b,150);
  digitalWrite(Motor3_a,HIGH);
  digitalWrite(Motor3_b,LOW);
  /*
  digitalWrite(Motor1_a,HIGH);
  digitalWrite(Motor1_b,LOW );
  digitalWrite(Motor3_a,LOW);
  digitalWrite(Motor3_b,HIGH);*/
}

void move_rightward() {
  digitalWrite(Motor1_a,HIGH);
  analogWrite(Motor1_b,110);
  digitalWrite(Motor2_a,HIGH);
  analogWrite(Motor2_b,150);
  digitalWrite(Motor3_a,LOW);
  digitalWrite(Motor3_b,HIGH);
}
void CCW(){
    digitalWrite(Motor1_a,LOW);//OK
    digitalWrite(Motor1_b,HIGH );
    digitalWrite(Motor2_a,LOW);
    digitalWrite(Motor2_b,HIGH);
    digitalWrite(Motor3_a,LOW);
    digitalWrite(Motor3_b,HIGH);
  }
void CW(){
    digitalWrite(Motor1_a,HIGH);//OK
    digitalWrite(Motor1_b,LOW );
    digitalWrite(Motor2_a,HIGH);
    digitalWrite(Motor2_b,LOW);
    digitalWrite(Motor3_a,HIGH);
    digitalWrite(Motor3_b,LOW);
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

void step_front(){
    digitalWrite(Motor1_a,LOW);
    digitalWrite(Motor1_b,LOW);
    digitalWrite(Motor2_a, HIGH); 
    digitalWrite(Motor2_b, LOW);
    digitalWrite(Motor3_a, LOW);
    digitalWrite(Motor3_b, HIGH);
    delay(100);
    digitalWrite(motor1in1,LOW);
    digitalWrite(motor1in2,LOW);
    digitalWrite(motor2in1,LOW);
    digitalWrite(motor2in2,LOW);
    digitalWrite(motor3in1,LOW);
    digitalWrite(motor3in2,LOW);      
  }
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
