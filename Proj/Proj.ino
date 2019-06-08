//Library
#include <Adafruit_PWMServoDriver.h>  //For PCA6985 16 channel Servo controller
#include <Wire.h>
#include <Servo.h>      //For SG90 Servo
#include <PS2X_lib.h>   //For ps2 controller

//SG90 angle: 0 ~ 165 degree
#define SG90_MIN 125
#define SG90_MAX 665
#define SG90_SC 3.273

//JX Servo PDI-6221MG angle: 0 ~ 175 degree
#define JX_MIN 107
#define JX_MAX 539.639
#define JX_SC 2.472

//MG996 angle: 0 ~ 180 degree
#define MG996_MIN 147
#define MG996_MAX 503
#define MG996_SC 1.978

//Length of the arms(cm)
#define L_arm 16
#define S_arm 16

//Movement for BT
#define PLACE_1 'a'
#define PLACE_2 'b'
#define PLACE_3 'c'
#define PLACE_4 'd'
#define EMPTY_1 'e'
#define EMPTY_2 'f'
#define EMPTY_3 'g'
#define EMPTY_4 'h'
#define INITIALIZE 'i'
#define GRAP_FOR_LOWER 'j'
#define GRAP_FOR_UPPER 'k'
#define CONNECT 'l'
#define DISCONNECT 'm'


//Pin on PCA9685
#define PIN_LONG_ARM      0
#define PIN_SHORT_ARM     1
#define PIN_HEAD          3
#define PIN_GRIPPER       4
#define PIN_ARM_ROTATION  7
#define PIN_DUMPER_1      8
#define PIN_DUMPER_2      10
#define PIN_DUMPER_3      12
#define PIN_DUMPER_4      14





//***** Adjustable Variables *****


//*** Variables for Arm ***

//Initial position
double Arm_angle_ini = 20;            /* Arm's initial rotate angle */
double L_angle_ini = 72;          /* Long arm's initial angle */
double S_angle_ini = 60;           /* Short arm's initial angle */

//Velocity for manual control
double X_velocity_MAX = 0.2;         /* Velocity of gripper along X-direction */
double Y_velocity_MAX = 0.2;        /* Velocity of gripper along Y-direction */
double Rotate_velocity = 0.5;    /* Velocity of arm rotation */


//Velocity for auto control
double auto_Velocity_scale = 15;
double auto_X_MAX_velocity = 0.1;          /* Auto velocity of gripper along X-direction */
double auto_Y_MAX_velocity = 0.1;         /* Auto velocity of gripper along Y-direction */
double auto_Rotate_MAX_velocity = 0.7;     /* Auto velocity of arm rotation */

//*************************

//*** Variables for Gripper ***

//Initial position
double Gripper_angle_ini = 15;    /* open */
double Head_angle_ini = 0;
double Head_angle_MAX = 176;
double Head_angle_MIN = 4;
double Gripper_angle_MAX = 150;   /* close */

//Velocity
double Grap_velocity = 1;
double Release_velocity = 3;
double Head_velocity = 2;

//*****************************

//*** Variables for Dumper ***

//Position
double Dumper_angle_1_OFF = 0;
double Dumper_angle_2_OFF = 180;
double Dumper_angle_3_OFF = 0;
double Dumper_angle_4_OFF = 180;
double Dumper_angle_1_ON = 100;
double Dumper_angle_2_ON = 120;
double Dumper_angle_3_ON = 100;
double Dumper_angle_4_ON = 80;

//Velocity
double Dumper_velocity = 0.8;

//****************************

//Variable for arm
double L_angle_default = 72;          /* Long arm's initial angle */
double S_angle_default = 0;           /* Short arm's initial angle */
double X_analog;
double Y_analog;
double R_angle;
double R_value;
double Arm_angle = Arm_angle_ini;
double L_angle = L_angle_ini;
double S_angle = S_angle_ini;
double L_angle_buf = L_angle_ini;
double S_angle_buf = S_angle_ini;
double X = L_arm * cos((180 - L_angle_ini) * PI / 180) + S_arm * cos(S_angle_ini * PI / 180);
double Y = L_arm * sin((180 - L_angle_ini) * PI / 180) - S_arm * sin(S_angle_ini * PI / 180);
double X_buf = X;
double Y_buf = Y;
const double X_ini = X;
const double Y_ini = Y;
double X_velocity;
double Y_velocity;

//Variables for gripper
double Gripper_angle = Gripper_angle_ini;
double Head_angle = Head_angle_ini;

//Variables for dumper
bool Dumper_1 = false;
bool Dumper_2 = false;
bool Dumper_3 = false;
bool Dumper_4 = false;
double Dumper_angle_1 = Dumper_angle_1_OFF;
double Dumper_angle_2 = Dumper_angle_2_OFF;
double Dumper_angle_3 = Dumper_angle_3_OFF;
double Dumper_angle_4 = Dumper_angle_4_OFF;

//Variables for wheel
const byte Motor1_a = 7;
const byte Motor1_b = 6;
const byte Motor2_a = 5;
const byte Motor2_b = 4;
const byte Motor3_a = 9;
const byte Motor3_b = 8;

//Variables for Bluetooth control
char BT_signal;

//Variables for debuging
bool righting = false;
bool erroring = false;
int count = 1;
bool consist_moving = false;

bool righting_2 = false;
bool erroring_2 = false;
int count_2 = 1;
bool consist_moving_2 = false;

bool Place_1 = false;
bool Place_2 = false;
bool Place_3 = false;
bool Place_4 = false;

//Declare a servo controller
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();  

//Declare a PS2 controller
PS2X ps2x;  

int error = 0;

void setup() {
  
  Serial.begin(9600);

  //Set up for Bluetooth Receiver
  Serial2.begin(38400);
  Serial.println("bt connect");
  
  //Set up for PCA6985 16 channel Servo controller
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates(No need to change)

  //Check if the ps2 controller is connected.
  error = ps2x.config_gamepad(13, 11, 10, 12, true, true); //GamePad(clock, command, attention, data, Pressures?, Rumble?)
  if (error == 0)
    Serial.println("Found Controller, configured successful");
  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  
  Ini_Arm();  //Initialize the arm 
  Ini_Gripper();
  Wheel_setup();
  dump_ini();
}

void loop() {



  //skip loop if no controller found
  if (error == 1) return;
  
  //read controller per loop
  ps2x.read_gamepad();   

  if(ps2x.Analog(PSS_LX) == 255 || ps2x.Analog(PSS_LY) == 255){
      if(erroring == false){
        if(count > 0){
          count--;
          consist_moving = false;
        }
        else{
          erroring = true;
          consist_moving = false;
        }
      }
      else consist_moving = true;
   }
   else{
     count = 1;
     erroring = false;
     consist_moving = true;
   }

   if(ps2x.Analog(PSS_RX) == 255 || ps2x.Analog(PSS_RY) == 255){
      if(erroring_2 == false){
        if(count_2 > 0){
          count_2--;
          consist_moving_2 = false;
        }
        else{
          erroring_2 = true;
          consist_moving_2 = false;
        }
      }
      else consist_moving_2 = true;
   }
   else{
     count_2 = 1;
     erroring_2 = false;
     consist_moving_2 = true;
   }

  //Movement of the Gripper
  if(!consist_moving_2){;}
  else if(ps2x.Analog(PSS_RY) > 128 || ps2x.Analog(PSS_RY) < 127 || ps2x.Analog(PSS_RX) > 128 || ps2x.Analog(PSS_RX) < 127){
    X_analog = ps2x.Analog(PSS_RX);
    Y_analog = ps2x.Analog(PSS_RY);
    X_buf += X_velocity_MAX * ((X_analog-127) / 127);
    Y_buf -= Y_velocity_MAX * ((Y_analog-127) / 127);
    Move();
    Serial.print("X:");
    Serial.println(X);
    Serial.print("Y:");
    Serial.println(Y);
    Serial.print("Angle:");
    Serial.println(Arm_angle);
  }

  //Grap and release
  if(ps2x.Button(PSB_TRIANGLE)) Grap();
  else if(ps2x.Button(PSB_CROSS)) Release();

  //Rotate of the arm
  if(ps2x.Button(PSB_R2)) Arm_right();
  else if(ps2x.Button(PSB_L2)) Arm_left();

  //Rotate of the gripper
  if(ps2x.Button(PSB_CIRCLE)) Head_right();
  else if(ps2x.Button(PSB_SQUARE)) Head_left();

  //BT control
  if(Serial2.available()){
    BT_signal=Serial2.read();
    Serial.write(BT_signal);

    if(BT_signal == EMPTY_1){
      if(!Dumper_1) dump(1);
      else undump(1);
    }
    else if(BT_signal == EMPTY_2){
      if(!Dumper_2) dump(2);
      else undump(2);
    }
    else if(BT_signal == EMPTY_3){
      if(!Dumper_3) dump(3);
      else undump(3);
    }
    else if(BT_signal == EMPTY_4){
      if(!Dumper_4) dump(4);
      else undump(4);
    }

    else if(BT_signal == INITIALIZE){
      To_Point(8.26, 0.62, 20);
      To_Point(X_ini+0.2, Y_ini-0.2, Arm_angle_ini);
    }

    else if(BT_signal == PLACE_1){
      if(!Place_1){
        To_Point(11.26, 5.62, 20);
        To_Point(12.86, 7.31, 50.50);
        To_Point(11.57, 11.29, 47.50);
        To_Point(16.60, 15.37, 82.00);
        To_Point(11.72, 13.37, 83.00);
        Place_1 = true;
      }
      else{
        To_Point(11.72, 13.37, 83.00);
        To_Point(16.60, 15.37, 82.00);
        To_Point(11.57, 11.29, 47.50);
        To_Point(11.26, 5.62, 20);
        Place_1 = false;
      }
    }
    else if(BT_signal == PLACE_2){
      if(!Place_2){
        To_Point(11.26, 5.62, 20);
        To_Point(12.86, 7.31, 50.50);
        To_Point(11.57, 11.29, 47.50);
        To_Point(16.60, 15.37, 82.00);
        To_Point(15.28, 13.40, 108.00);
        To_Point(10.91, 10.24, 108.50);
        Place_2 = true;
      }
      else{
        To_Point(10.91, 10.24, 105.00);
        To_Point(15.28, 13.40, 108.00);
        To_Point(16.60, 15.37, 82.00);
        To_Point(11.57, 11.29, 47.50);
        To_Point(11.26, 5.62, 20);
        Place_2 = false;
      }
    }
    else if(BT_signal == PLACE_3){
      if(!Place_3){
        To_Point(11.26, 5.62, 20);
        To_Point(12.86, 7.31, 50.50);
        To_Point(11.57, 11.29, 47.50);
        To_Point(16.60, 15.37, 82.00);
        To_Point(16.71, 12.47, 130.00);
        To_Point(10.96, 10.13, 134.00);
        Place_3 = true;
      }
      else{
        To_Point(10.96, 10.13, 134.00);
        To_Point(16.71, 12.47, 130.00);
        To_Point(16.60, 15.37, 82.00);
        To_Point(11.57, 11.29, 47.50);
        To_Point(11.26, 5.62, 20);
        Place_3 = false;
      }
    }
    else if(BT_signal == PLACE_4){
      if(!Place_4){
        To_Point(11.26, 5.62, 20);
        To_Point(12.86, 7.31, 50.50);
        To_Point(11.57, 11.29, 47.50);
        To_Point(16.60, 15.37, 82.00);
        To_Point(15.10, 13.26, 132.50);
        To_Point(16.67, 11.73, 149.00);
        To_Point(13.49, 10.73, 159.00);
        Place_4 = true;
      }
      else{
        To_Point(13.49, 10.73, 159.00);
        To_Point(16.67, 11.73, 149.00);
        To_Point(15.10, 13.26, 132.50);
        To_Point(16.60, 15.37, 82.00);
        To_Point(11.57, 11.29, 47.50);
        To_Point(11.26, 5.62, 20);
        Place_4 = false;
      }
    }
    
    else if(BT_signal == GRAP_FOR_UPPER){
      To_Point(22.54, 11.07, 20.00);
    }
    else if(BT_signal == GRAP_FOR_LOWER){
      To_Point(19.60, 0.62, 20.00);
      To_Point(28.51, -8.04, 20.00);
    }
  }

  //Movement of the body
   
  if(!consist_moving){;}
  else{
    if (ps2x.Analog(PSS_LY) <= 120 && ps2x.Analog(PSS_LX) > 120 && ps2x.Analog(PSS_LX) < 130) {
      move_forward();
    }
    else if (ps2x.Analog(PSS_LY) >= 130 && ps2x.Analog(PSS_LX) > 120 && ps2x.Analog(PSS_LX) < 130)
    {
      move_backward();
    }
  
    /*horizon*/
    else if (ps2x.Analog(PSS_LX) <= 120 && ps2x.Analog(PSS_LY) > 120 && ps2x.Analog(PSS_LY) < 135)
    {
      move_leftward();
    }
    if (ps2x.Analog(PSS_LX) >= 135 && ps2x.Analog(PSS_LY) > 120 && ps2x.Analog(PSS_LY) < 135)
    {
      move_rightward();
      righting = true;
    }
    else righting = false;

    /*diagonal*/
    if (ps2x.Analog(PSS_LX) >= 135 && ps2x.Analog(PSS_LY) <= 120)
    {
      move_right_forward();
    }

    else if (ps2x.Analog(PSS_LX) <= 120 && ps2x.Analog(PSS_LY) <= 120)
    {
      move_left_forward();
    }
    else if (ps2x.Analog(PSS_LX) >= 135 && ps2x.Analog(PSS_LY) >= 135)
    {
      move_right_backward();
    }

    else if (ps2x.Analog(PSS_LX) <= 120 && ps2x.Analog(PSS_LY) >= 135)
    {
      move_left_backward();
    }

    else if (ps2x.Analog(PSS_LX) >= 120 && ps2x.Analog(PSS_LX) <= 135 && ps2x.Analog(PSS_LY) >= 120 && ps2x.Analog(PSS_LY) <= 135)
      stopped();
}
 

  


  //Rotate of the body
  if(ps2x.Button(PSB_R1))
    CW();
  else if(ps2x.Button(PSB_L1))
    CCW();

  if(ps2x.Button(PSB_PAD_UP))
    move_slow_forward();
  else if(ps2x.Button(PSB_PAD_DOWN))
    move_slow_backward();
  else if(ps2x.Button(PSB_PAD_LEFT))
    move_slow_leftward();
  else if(ps2x.Button(PSB_PAD_RIGHT))
    move_slow_rightward();

 

  delay(10);
  
}
