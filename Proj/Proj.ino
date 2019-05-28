#include <Adafruit_PWMServoDriver.h> //For PCA6985 16 channel Servo controller
#include <Wire.h>
#include <PS2X_lib.h> //For ps2 controller

//SG90 angle: 0 ~ 165 degree
#define SG90_MIN 125
#define SG90_MAX 665
#define SG90_SC 3.273

//JX Servo PDI-6221MG angle: 0 ~ 175 degree
#define JX_MIN 107
#define JX_MAX 539.639
#define JX_SC 2.472

//Length of the arms(cm)
#define L_arm 16
#define S_arm 16

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

PS2X ps2x; //Declare a PS2 controller

int error = 0;

//Variables for arm
double L_angle_ini = 49;
double S_angle_ini = 0;
double L_angle = L_angle_ini;
double S_angle = S_angle_ini;
double L_angle_buf;
double S_angle_buf;
double X = L_arm * cos((180 - L_angle) * PI / 180) + S_arm * cos(S_angle * PI / 180);
double Y = L_arm * sin((180 - L_angle) * PI / 180) - S_arm * sin(S_angle * PI / 180);
double X_buf = X;
double Y_buf = Y;

//Variables for gripper
double gripper_angle = 0;
double head_angle = 86;

//Variables for wheel
const byte Motor1_a = 7;
const byte Motor1_b = 6;
const byte Motor2_a = 5;
const byte Motor2_b = 4;
const byte Motor3_a = 9;
const byte Motor3_b = 8;

void setup()
{

  Serial.begin(57600);

  //Set up for PCA6985 16 channel Servo controller
  pwm.begin();
  pwm.setPWMFreq(60); // Analog servos run at ~60 Hz updates(No need to change)

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

  Ini_Arm(); //Initialize the arm
  Ini_Gripper();
<<<<<<< HEAD
<<<<<<< HEAD

  Serial.print("X:");
  Serial.println(X);
  Serial.print("Y:");
  Serial.println(Y);
=======
>>>>>>> parent of f2ea231... Move to point DONE.
=======
>>>>>>> parent of f2ea231... Move to point DONE.
}

void loop()
{

  //skip loop if no controller found
  if (error == 1)
    return;

  //read controller per loop
  ps2x.read_gamepad();

  /*Movement of the Gripper*/
  if (ps2x.Analog(PSS_RY) > 130 || ps2x.Analog(PSS_RY) < 125 || ps2x.Analog(PSS_RX) > 130 || ps2x.Analog(PSS_RX) < 125)
  {
    if (ps2x.Analog(PSS_RY) < 125)
      Y_buf += 0.4;
    else if (ps2x.Analog(PSS_RY) > 130)
<<<<<<< HEAD
<<<<<<< HEAD
      Y_buf -= 0.25;

=======
=======
>>>>>>> parent of f2ea231... Move to point DONE.
      Y_buf -= 0.4;
  
>>>>>>> parent of f2ea231... Move to point DONE.
    if (ps2x.Analog(PSS_RX) < 125)
      X_buf -= 0.4;
    else if (ps2x.Analog(PSS_RX) > 130)
      X_buf += 0.4;

    Move();
  }

  if (ps2x.Button(PSB_TRIANGLE))
    Grap();
  else if (ps2x.Button(PSB_CROSS))
    Release();

  if (ps2x.Button(PSB_CIRCLE))
    Head_right();
  else if (ps2x.Button(PSB_SQUARE))
    Head_left();

<<<<<<< HEAD
<<<<<<< HEAD
  To_Point(14.00, 13.00);
  To_Point(14.00, 7.00);

=======
>>>>>>> parent of f2ea231... Move to point DONE.
=======
>>>>>>> parent of f2ea231... Move to point DONE.
  delay(25);
}
