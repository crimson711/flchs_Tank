/*
 Example sketch for the Xbox Wireless Reciver library - developed by Kristian Lauszus
 It supports up to four controllers wirelessly
 For more information see the blog post: http://blog.tkjelectronics.dk/2012/12/xbox-360-receiver-added-to-the-usb-host-library/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <XBOXRECV.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
XBOXRECV Xbox(&Usb);

<<<<<<< HEAD
/** ^^^^^^ DO NOT CHANGE ABOVE THIS ^^^^^^^ **/

/** Concept of Operation

L1 - 
L2 - 
R1 - Actuator Fine Adjust (In)
R2 - Actuator Fine Adjust (Out)
Left Hat - Drive Motor
Right Hat - Lift Motor (Up/Down)
L3 - 
R3 - 
Up - 
Down - 
Left - 
Right - 
A - Actuator Pre-set 1
B - Actuator Pre-set 2
X - Actuator Pre-set 3
Y - Actuator Pre-set 4

**/


/** pin definition **/
const int PWM_A   = 3,
          DIR_A   = 12,
          BRAKE_A = 9,
          PWM_B   = 11,
          DIR_B   = 13,
          BRAKE_B = 8,
          SNS_A   = A0,
          SNS_B   = A1;

/** variable definiton **/

bool L1_State = 0,
     L2_State = 0,
     R1_State = 0,
     R2_State = 0,
     L3_State = 0,
     R3_State = 0, 
     Up_State = 0,
     Down_State = 0,
     Left_State = 0,
     Right_State = 0,
     A_State = 0,
     B_State = 0,
     X_State = 0,
     Y_State = 0;

int  LeftHatX_Raw = 0,
     LeftHatY_Raw = 0,
     RightHatX_Raw = 0,
     RightHatY_Raw = 0;

int i = 0; // variable to xbox code counter

int left_x = 0,
    left_y = 0,
    right_x = 0,
    right_y = 0;
=======
const int
PWM_A   = 3,
DIR_A   = 12,
BRAKE_A = 9,
PWM_B   = 11,
DIR_B   = 13,
BRAKE_B = 8,
SNS_A   = A0,
SNS_B   = A1;

int pos = 0;
int pos2 = 0;
int i = 0;
int r = 0;
int l = 0;
int f = 0;
int a = 0;
int b = 0;
int c = 0;
int posX1=0;
int posY1=0;
int posX2=0;
int posY2=0;
//int w = 0;
//int v = 0;

/*#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 
// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
// You can also make another motor on port M2
Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(3);*/
>>>>>>> refs/remotes/crimson711/master

void setup() {
  Serial.begin(115200); // set up Serial library at 115200 bps
  
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif

  /** USB start error **/
  /** !!!!!!!!!!!!!!!!!!!!!! NEED ANOTHER ACTION OR INDUCTION !!!!!!!!!!!!!!!!!!!!!!!! **/
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));

  // Configure the A output
  pinMode(BRAKE_A, OUTPUT);  // Brake pin on channel A
  pinMode(DIR_A, OUTPUT);    // Direction pin on channel A
  pinMode(BRAKE_B, OUTPUT);  // Brake pin on channel B
  pinMode(DIR_B, OUTPUT);    // Direction pin on channel B
  
}

void loop() {
  
  /** Main loop logics:
  
  - Read USB Joystick
  - Update Motor Speed
  - Individual buttons action
  
  **/
  
  if (!readJoystickInput()) {
    Serial.println("USB Joystick Failed/Not Connected!");
  }
  
  updateMotorSpeed();
    
  
}

bool readJoystickInput() {
  /** Reading USB Value **/
  Usb.Task();
  if (Xbox.XboxReceiverConnected) {
    
    /** can connect up to 4 XBox controller **/
    for (uint8_t i = 0; i < 4; i++) {
      if (Xbox.Xbox360Connected[i]) {
<<<<<<< HEAD
        
        // use global variables to save reading to reduce process load
        // and allow all function to access the readings
        L1_State = Xbox.getButtonPress(L1, i);
        L2_State = Xbox.getButtonPress(L2, i);
        L3_State = Xbox.getButtonPress(L3, i);
        R1_State = Xbox.getButtonPress(R1, i);
        R2_State = Xbox.getButtonPress(R2, i);
        R3_State = Xbox.getButtonPress(R3, i);
        Up_State = Xbox.getButtonPress(UP, i);
        Down_State = Xbox.getButtonPress(DOWN, i);
        Left_State = Xbox.getButtonPress(LEFT, i);
        Right_State = Xbox.getButtonPress(RIGHT, i);
        A_State = Xbox.getButtonPress(A, i);
        B_State = Xbox.getButtonPress(B, i);
        X_State = Xbox.getButtonPress(X, i);
        Y_State = Xbox.getButtonPress(Y, i);
        LeftHatX_Raw = Xbox.getAnalogHat(LeftHatX, i);
        LeftHatY_Raw = Xbox.getAnalogHat(LeftHatY, i);
        RightHatX_Raw = Xbox.getAnalogHat(RightHatX, i);
        RightHatY_Raw = Xbox.getAnalogHat(RightHatY, i);
        
        // Adjust for null zone
        if (LeftHatX_Raw < 7500 && LeftHatX_Raw > -7500) LeftHatX_Raw = 0;
        if (LeftHatY_Raw < 7500 && LeftHatY_Raw > -7500) LeftHatY_Raw = 0;
        if (RightHatX_Raw < 7500 && RightHatX_Raw > -7500) RightHatX_Raw = 0;
        if (RightHatY_Raw < 7500 && RightHatY_Raw > -7500) RightHatY_Raw = 0;
        
        // debug printout
        Serial.print("LX:");
        Serial.print(LeftHatX_Raw);
        Serial.print(" LY:");
        Serial.print(LeftHatY_Raw);
        Serial.print(" RX:");
        Serial.print(RightHatX_Raw);
        Serial.print(" RY:");
        Serial.print(RightHatY_Raw);
        Serial.print(" RY:");
        Serial.print(RightHatY_Raw);
        
        Serial.print(" L1:");
        Serial.print((L1_State) ? 1 : 0);
        Serial.print(" L2:");
        Serial.print((L2_State) ? 1 : 0);
        Serial.print(" L3:");
        Serial.print((L3_State) ? 1 : 0);
        Serial.print(" R1:");
        Serial.print((R1_State) ? 1 : 0);
        Serial.print(" R2:");
        Serial.print((R2_State) ? 1 : 0);
        Serial.print(" R3:");
        Serial.print((R3_State) ? 1 : 0);
        
        Serial.print(" U:");
        Serial.print((Up_State) ? 1 : 0);
        Serial.print(" D:");
        Serial.print((Down_State) ? 1 : 0);
        Serial.print(" L:");
        Serial.print((Left_State) ? 1 : 0);
        Serial.print(" R:");
        Serial.print((Right_State) ? 1 : 0);
        
        Serial.print(" A:");
        Serial.print((A_State) ? 1 : 0);
        Serial.print(" B:");
        Serial.print((B_State) ? 1 : 0);
        Serial.print(" X:");
        Serial.print((X_State) ? 1 : 0);
        Serial.print(" Y:");
        Serial.println((Y_State) ? 1 : 0);
        // debug printout end
        
        /** Analog reading is from -32768 (left/down) to 32767 (right/up) **/
        // convert raw value into useable value (-255 - +255)
        left_x = map(LeftHatX_Raw, -32768, 32767, -255, 255);
        left_y = map(LeftHatY_Raw, -32768, 32767, -255, 255);
        
        right_x = map(RightHatX_Raw, -32768, 32767, -255, 255);
        right_y = map(RightHatY_Raw, -32768, 32767, -255, 255);
=======
        if (Xbox.getButtonPress(L2, i) || Xbox.getButtonPress(R2, i)) {
          Serial.print("L2: ");
          Serial.print(Xbox.getButtonPress(L2, i));
          Serial.print("\tR2: ");
          Serial.println(Xbox.getButtonPress(R2, i));
          Xbox.setRumbleOn(Xbox.getButtonPress(L2, i), Xbox.getButtonPress(R2, i), i);
        }

        if (Xbox.getAnalogHat(LeftHatX, i) > 7500 || Xbox.getAnalogHat(LeftHatX, i) < -7500 || Xbox.getAnalogHat(LeftHatY, i) > 7500 || Xbox.getAnalogHat(LeftHatY, i) < -7500 || Xbox.getAnalogHat(RightHatX, i) > 7500 || Xbox.getAnalogHat(RightHatX, i) < -7500 || Xbox.getAnalogHat(RightHatY, i) > 7500 || Xbox.getAnalogHat(RightHatY, i) < -7500) {
          if (Xbox.getAnalogHat(LeftHatX, i) > 7500 || Xbox.getAnalogHat(LeftHatX, i) < -7500) {
            Serial.print(F("LeftHatX: "));
            Serial.print(Xbox.getAnalogHat(LeftHatX, i));
            Serial.print("\t");
          }
          if (Xbox.getAnalogHat(LeftHatY, i) > 7500 || Xbox.getAnalogHat(LeftHatY, i) < -7500) {
            Serial.print(F("LeftHatY: "));
            Serial.print(Xbox.getAnalogHat(LeftHatY, i));
            Serial.print("\t");
          }
          if (Xbox.getAnalogHat(RightHatX, i) > 7500 || Xbox.getAnalogHat(RightHatX, i) < -7500) {
            Serial.print(F("RightHatX: "));
            Serial.print(Xbox.getAnalogHat(RightHatX, i));
            Serial.print("\t");
          }
          if (Xbox.getAnalogHat(RightHatY, i) > 7500 || Xbox.getAnalogHat(RightHatY, i) < -7500) {
            Serial.print(F("RightHatY: "));
            Serial.print(Xbox.getAnalogHat(RightHatY, i));
          }
          Serial.println();
        }


        /*pos = map(Xbox.getAnalogHat(LeftHatX, i), -32768, 32767, -255, 255);
        pos2 = map(Xbox.getAnalogHat(LeftHatY, i), -32768, 32767, -255, 255);
        
        if(pos>0){
          digitalWrite(DIR_A, HIGH);   // setting direction to HIGH the motor will spin forward
          digitalWrite(DIR_B, LOW);   // setting direction to HIGH the motor will spin forward
        }
                if(pos<0){
          digitalWrite(DIR_A, LOW);   // setting direction to HIGH the motor will spin forward
          digitalWrite(DIR_B, HIGH);   // setting direction to HIGH the motor will spin forward
        }
        
        //Serial.print("pos: "+pos);
        //Serial.println("pos2: "+pos2);
        
       // pos = 1/pos;

       /* v = (256-abs(pos)) * (pos2/256) + pos2;
        w = (256-abs(pos2)) * (pos/256) + pos;
        r = (v+w)/2;
        l = (v-w)/2;*/

        Serial.print("Speed: ");
        Serial.print(pos);
        Serial.print(" and ");
        Serial.print(pos);
        if(pos>0){
        Serial.println("\nDirection: Forward");
        }
        else{
          Serial.println("\nDirection: Backward");
        }
        //mathew's code
        

        a = Xbox.getAnalogHat(LeftHatX, i);
        b = Xbox.getAnalogHat(LeftHatY, i);
        c = (int) (sqrt(pow(abs(a), 2) + pow(abs(b), 2)));
        Serial.print("Speed: ");
        Serial.println(c/128);
        
        r=abs(round(c/128));
        l=abs(round(b/128));
        f=abs(round(a/128));

        //Must Fix Down-Right and Up-Left

        if (a > 4095 && b >= -4096 && b <= 4095){
          digitalWrite(BRAKE_A, LOW);
              digitalWrite(BRAKE_B, LOW);
              digitalWrite(DIR_A, HIGH);
              digitalWrite(DIR_B, LOW);
              analogWrite(PWM_A, r); 
              analogWrite(PWM_B, r);
        }
        else if (a < -4096 && b >= -4096 && b <= 4095){
          digitalWrite(BRAKE_A, LOW);
              digitalWrite(BRAKE_B, LOW);
              digitalWrite(DIR_A, HIGH);
              digitalWrite(DIR_B, HIGH);
              analogWrite(PWM_A, r); 
              analogWrite(PWM_B, r);
        }
        else if (b > 4095 && a >= -4096 && a <= 4095){
          digitalWrite(BRAKE_A, LOW);
              digitalWrite(BRAKE_B, LOW);
              digitalWrite(DIR_A, HIGH);
              digitalWrite(DIR_B, LOW);
              analogWrite(PWM_A, r); 
              analogWrite(PWM_B, r);
        }
        else {
          digitalWrite(BRAKE_A, LOW);
              digitalWrite(BRAKE_B, LOW);
              digitalWrite(DIR_A, LOW);
              digitalWrite(DIR_B, HIGH);
              analogWrite(PWM_A, r); 
              analogWrite(PWM_B, r);
        }

          if (a > 4095){                             //Stick is pointed right
            if (b > 4095){
              digitalWrite(BRAKE_A, LOW);
              digitalWrite(BRAKE_B, LOW);
              digitalWrite(DIR_A, HIGH);
              digitalWrite(DIR_B, LOW);
              analogWrite(PWM_A, l); 
              analogWrite(PWM_B, r);
            }
            else //if (b < -4096)
            {
              digitalWrite(BRAKE_A, LOW);
              digitalWrite(BRAKE_B, LOW);
              digitalWrite(DIR_A, LOW);
              digitalWrite(DIR_B, HIGH);
              analogWrite(PWM_A, r); 
              analogWrite(PWM_B, l);
            }
           /* else{                                   //Tank turn Right
              digitalWrite(BRAKE_A, LOW);
              digitalWrite(BRAKE_B, LOW);
              digitalWrite(DIR_A, LOW);
              digitalWrite(DIR_B, LOW);
              analogWrite(PWM_A, f); 
              analogWrite(PWM_B, f);
            }*/
          }
          else if (a < -4096){                      //Stick is pointed left
            if (b > 4095){
              digitalWrite(BRAKE_A, LOW);
              digitalWrite(BRAKE_B, LOW);
              digitalWrite(DIR_A, HIGH);
              digitalWrite(DIR_B, LOW);
              analogWrite(PWM_A, r); 
              analogWrite(PWM_B, l);
            }
            else //if (b < -4096)
            {
              digitalWrite(BRAKE_A, LOW);
              digitalWrite(BRAKE_B, LOW);
              digitalWrite(DIR_A, LOW);
              digitalWrite(DIR_B, HIGH);
              analogWrite(PWM_A, r); 
              analogWrite(PWM_B, l);
            }
           /* else{                                   //Tank turn Left
              digitalWrite(BRAKE_A, LOW);
              digitalWrite(BRAKE_B, LOW);
              digitalWrite(DIR_A, HIGH);
              digitalWrite(DIR_B, HIGH);
              analogWrite(PWM_A, f); 
              analogWrite(PWM_B, f);
            }*/
          }
         /* else{                                   //Stick pointed Up, Forwards
            if(b > 4095){
              digitalWrite(BRAKE_A, LOW);
              digitalWrite(BRAKE_B, LOW);
              digitalWrite(DIR_A, HIGH);
              digitalWrite(DIR_B, LOW);
              analogWrite(PWM_A, r); 
              analogWrite(PWM_B, r);
            }
            else if(b < -4096){                           //Stick pointed Down, Backwards
              digitalWrite(BRAKE_A, LOW);
              digitalWrite(BRAKE_B, LOW);
              digitalWrite(DIR_A, LOW);
              digitalWrite(DIR_B, HIGH);
              analogWrite(PWM_A, r); 
              analogWrite(PWM_B, r);
            }*/
            else if (a <= 4095 && a >= -4096 && b <= 4095 && b >= -4096){                              //Stick is in the centre, Stop
              digitalWrite(BRAKE_A, HIGH);
              digitalWrite(BRAKE_B, HIGH);
            }
        //  }
        
        /*if(b>3000){
          digitalWrite(BRAKE_A, LOW);
          digitalWrite(BRAKE_B, LOW);
          digitalWrite(DIR_A, HIGH);
          digitalWrite(DIR_B, LOW);
        }
        else if(b<-3000){
         digitalWrite(BRAKE_A, LOW);
         digitalWrite(BRAKE_B, LOW);
         digitalWrite(DIR_A, LOW);
         digitalWrite(DIR_B, HIGH);
        }
        else{
        digitalWrite(BRAKE_A, HIGH);
        digitalWrite(BRAKE_B, HIGH);
        }
        
        if(a>=32767-512){
          digitalWrite(DIR_A, LOW);
          digitalWrite(DIR_B, HIGH);
        }
        if(a<=-32768+512){
          digitalWrite(DIR_A, HIGH);
          digitalWrite(DIR_B, LOW);
        }
        if(b>=32767-512){
          digitalWrite(DIR_A, HIGH);
          digitalWrite(DIR_B, LOW);
        }
        if(b<=-32767+512){
          digitalWrite(DIR_A, LOW);
          digitalWrite(DIR_B, HIGH);
        }
        r=(c-a)/128;
        l=(c-b)/128;
        
        analogWrite(PWM_A, r); 
        analogWrite(PWM_B, l);
        
        //chris code
  /*     
        posX1 = map(Xbox.getAnalogHat(RightHatX, i), -32768, 32767, -255, 255);
        posY1 = map(Xbox.getAnalogHat(RightHatY, i), -32768, 32767, 255, -255);
        posY2 = map(Xbox.getAnalogHat(RightHatY, i), -32768, 32767, -255, 255);
        analogWrite(PWM_A, (-posX1+posY1)); 
        analogWrite(PWM_B, (-posX1+posY1));
*/
  /*
        int x_axis = AnalogRead(0); // value of X-Axis joystick (0-1023, 512 = centered)
  int y_axis = AnalogRead(1); // value of Y-Axis joystick (0-1023, 512 = centered)
  // filter out a centered joystick - no action
  if (x_axis < 510 || x_axis > 514) {
    if (y_axis < 510 || y_axis > 514) {
      // Map values from potentiometers to a smaller range for the PWM motor controllers (0-255)
      x_axis = map(x_axis, 0, 1023, 0, 255);
      y_axis = map(y_axis, 0, 1023, 0, 255);
      int ly_axis = y_axis;
      int ry_axis = y_axis;
      if (x_axis < 126) { // turning left, so slow-down left track
        if (y_axis > 130) { // moving forward
          ly_axis -= (255 - x_axis); // decreasing the value - moving it closer to the center-point - slows it down
        }
        if (y_axis < 126) { // moving in reverse
          ly_axis += (255 - x_axis); // increasing the value - moving it closer to the center-point - slows it down
        }
      }
      if (x_axis > 130) { // turning right, so slow-down right track
        if (y_axis > 130) { // moving forward
          ry_axis -= (255 - x_axis); // decreasing the value - moving it closer to the center-point - slows it down
        }
        if (y_axis < 126) { // moving in reverse
          ry_axis += (255 - x_axis); // increasing the value - moving it closer to the center-point - slows it down
        }
      }
      l_track.write(ly_axis); // here we assume that values > 128 = forward, and < 128 = reverse for the left track motor controller
      r_track.write(ry_axis); // here we assume that values > 128 = forward, and < 128 = reverse for the right track motor controller
    }
  }
  // center both PWM values if the joystick is centered (bringing both motor controllers and tracks to a stop)
  if (x_axis >= 510 || x_axis <= 514) {
    if (y_axis >= 510 || y_axis <= 514) {
      l_track.write(128);
      r_track.write(128);
 
         */
        //end
        /*if(r==l){
          digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
            digitalWrite(DIR_A, HIGH);   // setting direction to HIGH the motor will spin forward
            analogWrite(PWM_A, r); 
            analogWrite(PWM_B, l); 
        }*/
        
        
        
        /*if (r>0){
            digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
            digitalWrite(DIR_A, HIGH);   // setting direction to HIGH the motor will spin forward
            analogWrite(PWM_A, r); 
          
        }
        else if (r<0){
           digitalWrite(BRAKE_A, LOW);  // setting againg the brake LOW to disable motor brake
           digitalWrite(DIR_A, LOW);    // now change the direction to backward setting LOW the DIR_A pin
           analogWrite(PWM_A, r);     // Set the speed of the motor
        }
        else {
           digitalWrite(BRAKE_A, HIGH);
        }
         if (l>0){
          digitalWrite(BRAKE_B, LOW);  // setting brake LOW disable motor brake
          digitalWrite(DIR_B, LOW);   // setting direction to HIGH the motor will spin forward
          analogWrite(PWM_B, l);
        }
        else if (l<0){
          digitalWrite(BRAKE_B, LOW);  // setting againg the brake LOW to disable motor brake
          digitalWrite(DIR_B, HIGH);    // now change the direction to backward setting LOW the DIR_A pin
          analogWrite(PWM_B, l);     // Set the speed of the motor
        }
        else {
          digitalWrite(BRAKE_A, HIGH);
        }
     /*   
         if (Xbox.getAnalogHat(LeftHatX, i) < 32639){
            if (Xbox.getAnalogHat(LeftHatX, i) > -32640){
              if (Xbox.getAnalogHat(LeftHatY, i) < 2047 && Xbox.getAnalogHat(LeftHatY, i) > -2048/* || Xbox.getAnalogHat(LeftHatX, i) < 2047 && Xbox.getAnalogHat(LeftHatX, i) > -2048*/ /*){
     /*           myMotor->run(RELEASE);
              myOtherMotor->run(RELEASE);
              }
           }
         }
*/
       //  if (Xbox.getAnalogHat(LeftHatY, i) >= 2047 /*|| Xbox.getAnalogHat(LeftHatY, i) < 0*/ /*){ */
        // pos = map(Xbox.getAnalogHat(LeftHatY, i), /*-32768*/ /*-32768*/0, 32767, /*-256*/ 0, 255);
         /* Serial.print(F("pos: "));
          Serial.println(pos);
                myMotor->setSpeed(pos);
                myOtherMotor->setSpeed(pos);
                delay(10);
                myMotor->run(FORWARD);
              myOtherMotor->run(FORWARD);
         }
         if (Xbox.getAnalogHat(LeftHatY, i) <= -2048){
         pos = map(Xbox.getAnalogHat(LeftHatY, i), 0, -32768, 0, 255);
          Serial.print(F("pos: "));
          Serial.println(pos);
                myMotor->setSpeed(pos);
                myOtherMotor->setSpeed(pos);
                delay(10);
                myMotor->run(BACKWARD);
              myOtherMotor->run(BACKWARD);
         }
         
         if (Xbox.getAnalogHat(LeftHatX, i) > 2048 && Xbox.getAnalogHat(LeftHatY, i) > -2048 && Xbox.getAnalogHat(LeftHatY, i) < 2047){
         pos2 = map(Xbox.getAnalogHat(LeftHatX, i), 0, 32767, 0, 255);
          Serial.print(F("pos: "));
          Serial.println(pos);
                myMotor->setSpeed(pos2);
                myOtherMotor->setSpeed(pos2);
                delay(10);
                myMotor->run(BACKWARD);
              myOtherMotor->run(FORWARD);
         }
         
         if (Xbox.getAnalogHat(LeftHatX, i) < -2048 && Xbox.getAnalogHat(LeftHatY, i) > -2048 && Xbox.getAnalogHat(LeftHatY, i) < 2047){
         pos2 = map(Xbox.getAnalogHat(LeftHatX, i), 0, 32767, 0, 255);
          Serial.print(F("pos: "));
          Serial.println(pos);
                myMotor->setSpeed(pos2);
                myOtherMotor->setSpeed(pos2);
                delay(10);
                myMotor->run(FORWARD);
              myOtherMotor->run(BACKWARD);
         }
         if (Xbox.getAnalogHat(LeftHatX, i) > 2047 && Xbox.getAnalogHat(LeftHatY, i) <= -2048 && Xbox.getAnalogHat(LeftHatY, i) >= 2047){
         pos2 = map(Xbox.getAnalogHat(LeftHatX, i), 0, 32767, 0, 255);
          Serial.print(F("pos: "));
          Serial.println(pos);
                myMotor->setSpeed(pos);
                myOtherMotor->setSpeed(pos2);
                delay(10);
                myMotor->run(FORWARD);
              myOtherMotor->run(FORWARD);
         }
         if (Xbox.getAnalogHat(LeftHatX, i) < -2048 && Xbox.getAnalogHat(LeftHatY, i) <= -2048 && Xbox.getAnalogHat(LeftHatY, i) >= 2047){
         pos2 = map(Xbox.getAnalogHat(LeftHatX, i), 0, -32768, 0, 255);
          Serial.print(F("pos: "));
          Serial.println(pos);
                myMotor->setSpeed(pos2);
                myOtherMotor->setSpeed(pos);
                delay(10);
                myMotor->run(FORWARD);
              myOtherMotor->run(FORWARD);
         }
*/
        
        if (Xbox.getButtonClick(UP, i)) {
          Xbox.setLedOn(LED1, i);
          Serial.println(F("Up"));
          digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
          digitalWrite(BRAKE_B, LOW);  // setting brake LOW disable motor brake
          digitalWrite(DIR_A, HIGH);
          digitalWrite(DIR_B, LOW);
          analogWrite(PWM_A, 200); 
          analogWrite(PWM_B, 200);    
        }
        if (Xbox.getButtonClick(DOWN, i)) {
          Xbox.setLedOn(LED4, i);
          Serial.println(F("Down"));
          digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
          digitalWrite(BRAKE_B, LOW);  // setting brake LOW disable motor brake
          digitalWrite(DIR_A, LOW);
          digitalWrite(DIR_B, HIGH); 
          analogWrite(PWM_A, 200); 
          analogWrite(PWM_B, 200);    
        }
        if (Xbox.getButtonClick(LEFT, i)) {
          Xbox.setLedOn(LED3, i);
          digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
          digitalWrite(BRAKE_B, LOW);  // setting brake LOW disable motor brake
          Serial.println(F("Left"));
          digitalWrite(DIR_A, HIGH);
          digitalWrite(DIR_B, HIGH); 
          analogWrite(PWM_A, 200); 
          analogWrite(PWM_B, 200);    
        }
        if (Xbox.getButtonClick(RIGHT, i)) {
          Xbox.setLedOn(LED2, i);
          Serial.println(F("Right"));
          digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
          digitalWrite(BRAKE_B, LOW);  // setting brake LOW disable motor brake
          digitalWrite(DIR_A, LOW);
          digitalWrite(DIR_B, LOW);
          analogWrite(PWM_A, 200); 
          analogWrite(PWM_B, 200);    
        }

        if (Xbox.getButtonClick(START, i)) {
          Xbox.setLedMode(ALTERNATING, i);
          Serial.println(F("Start"));
        }
        if (Xbox.getButtonClick(BACK, i)) {
          Xbox.setLedBlink(ALL, i);
          Serial.println(F("Back"));
        }
        if (Xbox.getButtonClick(L3, i))
        {
          Serial.println(F("L3"));
            digitalWrite(BRAKE_A, HIGH);
            digitalWrite(BRAKE_B, HIGH);}
        if (Xbox.getButtonClick(R3, i))
          Serial.println(F("R3"));

        if (Xbox.getButtonClick(L1, i))
          Serial.println(F("L1"));
        if (Xbox.getButtonClick(R1, i))
          Serial.println(F("R1"));
        if (Xbox.getButtonClick(XBOX, i)) {
          Xbox.setLedMode(ROTATING, i);
          Serial.print(F("Xbox (Battery: "));
          Serial.print(Xbox.getBatteryLevel(i)); // The battery level in the range 0-3
          Serial.println(F(")"));
        }
        if (Xbox.getButtonClick(SYNC, i)) {
          Serial.println(F("Sync"));
          Xbox.disconnect(i);
        }

        if (Xbox.getButtonClick(A, i))
          Serial.println(F("A"));
        if (Xbox.getButtonClick(B, i)){
          Serial.println(F("B"));
              digitalWrite(BRAKE_A, HIGH);;
              digitalWrite(BRAKE_B, HIGH);}
        if (Xbox.getButtonClick(X, i))
          Serial.println(F("X"));
        if (Xbox.getButtonClick(Y, i))
          Serial.println(F("Y"));
>>>>>>> refs/remotes/crimson711/master
      }
    }
    
    return true;
    
  } else {
    
    return false;
    
  }
}

void updateMotorSpeed() {
  
  static int old_speed_left,
             old_speed_right;
  
  int speed_left = left_x;
  int speed_right = left_x;
  
  // update motor speed only if there are change
  if (speed_left != old_speed_left || speed_right != old_speed_right) {
    if (left_x > 0) {
      digitalWrite(DIR_A, HIGH);
      digitalWrite(DIR_B, HIGH);
    } else {
      digitalWrite(DIR_A, LOW);
      digitalWrite(DIR_B, LOW);
    }
    
    analogWrite(PWM_A, speed_left);
    analogWrite(PWM_B, speed_right);
  }
  
  old_speed_left = speed_left;
  old_speed_right = speed_right;
  
}
