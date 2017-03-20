/* This is the code of Team 7 Touch for a hand sensory
 * rehabilitation device. Team 7 is a part of UT Dallas
 * Senior Design. The project is sponsored by TX Biomedical
 * Center by Dr. Robert Rennaker. Team's engineering director
 * is Dr. Robert Hart.
 * 
 * The members of the team are Nicole Aragon, Mallory
 * Bing, Jamie Kunnappally, Grace McFarland, and Michelle
 * Toro. The team is assisted by their technical manager
 * Dr. James Hilkert.
 */


// Calling libraries 
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Calling and naming motor shields
Adafruit_MotorShield AFMSone(0x61);                                                           // Bottom-most motor shield // change to 65
Adafruit_MotorShield AFMStwo(0x60);                                                           // Second from the bottom motor shield // change to 64
// Adafruit_MotorShield AFMSthree(0x63);                                                      // Third from the bottom motor shield
// Adafruit_MotorShield AFMSfour(0x61);                                                       // Second from the top motor shield
// Adafruit_MotorShield AFMSfive(0x60);                                                       // Top motor shield

// Calling and naming individual motors
//Adafruit_StepperMotor *myStepper5 = AFMSfive.getStepper(200, 1);                            // Rotary stepper on motor shield 5
//Adafruit_StepperMotor *myCanstack5 = AFMSfive.getStepper(200, 2);                           // Linear stepper on motor shield 5

//Adafruit_StepperMotor *myStepper4 = AFMSfour.getStepper(200, 1);                            // Rotary stepper on motor shield 4
//Adafruit_StepperMotor *myCanstack4 = AFMSfour.getStepper(200, 2);                           // Linear stepper on motor shield 4

//Adafruit_StepperMotor *myStepper3 = AFMSthree.getStepper(200, 1);                           // Rotary stepper on motor shield 3
//Adafruit_StepperMotor *myCanstack3 = AFMSthree.getStepper(200, 2);                          // Linear stepper on motor shield 3

Adafruit_StepperMotor *myStepper2 = AFMStwo.getStepper(200, 1);                               // Rotary stepper on motor shield 2
Adafruit_StepperMotor *myCanstack2 = AFMStwo.getStepper(200, 2);                              // Linear stepper on motor shield 2

Adafruit_StepperMotor *myStepper1 = AFMSone.getStepper(200, 2);                               // Rotary stepper on motor shield 1
Adafruit_StepperMotor *myCanstack1 = AFMSone.getStepper(200, 1);                              // Linear stepper on motor shield 1

// Setup library, frequency, and motors
void setup() {

  Serial.begin(9600); // set up Serial library at 9600 bps
  
  AFMSone.begin(); // create with the default frequency 1.6KHz
  AFMStwo.begin();
//  AFMSthree.begin();
//  AFMSfour.begin();
//  AFMSfive.begin();
   
  myCanstack1->setSpeed(10);                                                                  //turn linear motor 1 to 10 rpm
  myStepper1->setSpeed(10);                                                                   //turn rotary motor 1 to 10 rpm
  myCanstack2->setSpeed(10);                                                                  //turn linear motor 2 to 10 rpm
  myStepper2->setSpeed(10);                                                                   //turn rotary motor 2 to 10 rpm 
//  myCanstack3->setSpeed(10);                                                                  //turn linear motor 3 to 10 rpm
//  myStepper3->setSpeed(10);                                                                   //turn rotary motor 3 to 10 rpm 
//  myCanstack4->setSpeed(10);                                                                  //turn linear motor 4 to 10 rpm
//  myStepper4->setSpeed(10);                                                                   //turn rotary motor 4 to 10 rpm 
//  myCanstack5->setSpeed(10);                                                                  //turn linear motor 5 to 10 rpm
//  myStepper5->setSpeed(10);                                                                   //turn rotary motor 5 to 10 rpm  
}

// Main function
void loop(){  
  Serial.println("Which test would you like to begin? f = force, t = two point discrimination test, else = end program.");          //print to serial monitor
  while (!Serial.available()){}                                                                                                         //Do Absolutely Nothing until something is received over the serial port
  int begintest = Serial.read();                                                                                                        //define variable begintest as the choice the user makes as to which test they would like to run

  //starts the force test
  if (begintest == 'f'){
    Serial.println("You are beginning the force test.");
    force();
  } 

  //starts the two point discrimination test
  if (begintest == 't'){
    Serial.println("You are beginning the twopoint test.");
    twopoint();
  }

  //end program
  else {
    Serial.println("You did not choose a test and the program has ended.");
    return 0;
   }
}




//force test
int force() {
  Serial.println("Beginning the force test");
  Serial.println("Which finger do you want to test? a=1");                                        //1 is thumb, 2 is forefinger, 3 is middle finger, 4 is ring finger, 5 is pinky
  while (!Serial.available()){}                                                                   //Do Absolutely Nothing until something is received over the serial port
  int fingernumber = Serial.read();                                                               //fingernumber is the number associated with the finger they want to test
  fingernumber = fingernumber - '0';
  
  //run appropriate force function according to the fingernumber that was input by the user
  switch (fingernumber) {
    case 1:{
      forceone();
    }
      break;
    case 2:{
      forcetwo();
    }
      break;
    case 3:{
//      forcethree();
    }
      break;
    case 4:{
//      forcefour();
    }
      break;
    case 5:{
//      forcefive();
    }
      break;  
  }
  return fingernumber;
}

//function for thumb
void forceone(){
  Serial.println("When you feel something, push down.");
  
  int forcesensor = 14;                                                                            //calling on the force sensor for a value
  float grams = 0;                                                                                 //initalize variable grams

  //loop to continue until force greater than gravity of a finger is applied to force sensor (equivalent to pushing on the force sensor)
  while (grams < 100) {                                                                            //Canstack motor moves until pushed down

    float sensedforce = analogRead(forcesensor);                                                   //value received from force sensor
    float voltage = sensedforce*5/1023;                                                            //convert value to voltage
    grams = voltage/0.12;                                                                          //convert voltage to grams
    Serial.println(grams);                                                                         //print grams to screen
  
    myCanstack1->step(100, FORWARD, DOUBLE);                                                       //continually rotate linear stepper motor
  }                                                                                                

  Serial.println("Test will end."); 
  return;                                                                                         //signal a return to GUI to stop test and output number
}

//function for forefinger
void forcetwo(){
  Serial.println("When you feel something, push down.");
  
  int forcesensor = 15;                                                                           //calling on the force sensor for a value
  float grams = 0;                                                                                //initialize variable grams

  //loop to continue until force greater than gravity of a finger is applied to force sensor (equivalent to pushing on the force sensor)
  while (grams < 100) {                                                                           //Canstack motor moves until pushed down

    float sensedforce = analogRead(forcesensor);                                                  //value received from force sensor
    float voltage = sensedforce*5/1023;                                                           //convert value to voltage
    grams = voltage/0.12;                                                                         //convert voltage to grams
    Serial.println(grams);                                                                        //print grams to screen
  
    myCanstack2->step(100, FORWARD, DOUBLE); 
  }  
  
  Serial.println("Test will end.");
  return;                                                                                         //signal a return to GUI to stop test and output number
}

//void forcethree(){
//  Serial.println("When you feel something, push down.");
//  
//  int forcesensor = 16;                                                                           //calling on the force sensor for a value
//  float grams = 0;                                                                                //initialize variable grams
//
//  //loop to continue until force greater than gravity of a finger is applied to force sensor (equivalent to pushing on the force sensor)
//  while (grams < 100) {                                                                           //Canstack motor moves until pushed down
//
//    float sensedforce = analogRead(forcesensor);                                                  //value received from force sensor
//    float voltage = sensedforce*5/1023;                                                           //convert value to voltage
//    grams = voltage/0.12;                                                                         //convert voltage to grams
//    Serial.println(grams);                                                                        //print grams to screen
//  
//    myCanstack3->step(100, FORWARD, DOUBLE); 
//  }
//
//  Serial.println("Test will end.");
//  return;                                                                                         //signal a return to GUI to stop test and output number
//}

//void forcefour(){
//  Serial.println("When you feel something, push down.");
//  
//  int forcesensor = 17;                                                                           //calling on the force sensor for a value
//  float grams = 0;                                                                                //initialize variable grams
//
//  //loop to continue until force greater than gravity of a finger is applied to force sensor (equivalent to pushing on the force sensor)
//  while (grams < 100) {                                                                           //Canstack motor moves until pushed down
//
//    float sensedforce = analogRead(forcesensor);                                                  //value received from force sensor
//    float voltage = sensedforce*5/1023;                                                           //convert value to voltage
//    grams = voltage/0.12;                                                                         //convert voltage to grams
//    Serial.println(grams);                                                                        //print grams to screen
//  
//    myCanstack4->step(100, FORWARD, DOUBLE); 
//  }
//  
//  Serial.println("Test will end.");
//  return;                                                                                        //signal a return to GUI to stop test and output number
//}

//void forcefive(){
//  Serial.println("When you feel something, push down.");
//  
//  int forcesensor = 18;                                                                           //calling on the force sensor for a value
//  float grams = 0;                                                                                //initialize variable grams
//
//  //loop to continue until force greater than gravity of a finger is applied to force sensor (equivalent to pushing on the force sensor)
//  while (grams < 100) {                                                                           //Canstack motor moves until pushed down
//
//    float sensedforce = analogRead(forcesensor);                                                  //value received from force sensor
//    float voltage = sensedforce*5/1023;                                                           //convert value to voltage
//    grams = voltage/0.12;                                                                         //convert voltage to grams
//    Serial.println(grams);                                                                        //print grams to screen
//  
//    myCanstack5->step(100, FORWARD, DOUBLE); 
//  }
//  
//  Serial.println("Test will end.");
//  return;                                                                                        //signal a return to GUI to stop test and output number
//}

/////Randomize two-point test
//
//  Serial.println("Would you like to randomize the finger you test? y = yes, n = no");
//  while (!Serial.available()){            //Do Absolutely Nothing until something is received over the serial port
//  }
//  int randomconfirmation = Serial.read();
//  if (randomconfirmation = 'y'){
//    int fingernumber = random(1, 6);
//  }
//  else {
//    Serial.println("Enter which finger you want to test (1-5).");
//    while (!Serial.available()){            //Do Absolutely Nothing until something is received over the serial port
//    }
//    int fingernumber = Serial.read();
//  }




//two-point discrimination test
int twopoint() {

  Serial.println("Enter which finger you want to test (1-5).");
  while (!Serial.available()){}                                                                   //Do Absolutely Nothing until something is received over the serial port
  int fingernumber = Serial.read(); //user chooses finger
  fingernumber = fingernumber - '0';
  int totalstepsaround = 25;                                                                      //the rotary motor must go 25 steps to turn to each side of the octagon wheel - this represents the first side

  //loops until the code returns a value (the user correctly felt something) or the wheel exceeds 5 turns (the user failed 5 times)
  //based on finger user chose, will activate specific motors
  while(totalstepsaround <= 125){
    switch (fingernumber) {
      case 1:{
        twopointone();
      }
        break;
      case 2:{
        twopointtwo();
      }
        break;
      case 3:{
        twopointthree();
      }
        break;
      case 4:{
        twopointfour();
      }
        break;
      case 5:{
        twopointfive();
      }
        break;  
    }
  
    Serial.println("Push down on the finger you feel 2 points on. If you don't feel anything enter '0'.");
//may have to loop all of this for force sensors to collect something substantial
    //calling all force sensors

    int threshold = 100;                                                                          //initialize varaible threshold - the grams that must be exceeded for the maximum force to be something substantial

//    while (threshold < 100)
    int finger1 = analogRead(14);
    int finger2 = analogRead(15);
    int finger3 = analogRead(16);
    int finger4 = analogRead(17);
    int finger5 = analogRead(18);

    int fingernumberread = 0;                                                                     //initialize variable fingernumberread - the maximum force returned from a force sensor

    //finding which forcesensor felt the largest force
    //when finger1 feels the largest force
    if(finger1 > threshold && finger1 > finger2 && finger1 > finger3 && finger1 > finger4 && finger1 > finger5 ){
      fingernumberread = '1';
    }
    //when finger2 feels the largest force
    else if(finger2 > threshold && finger2 > finger1 && finger2 > finger3 && finger2 > finger4 && finger2 > finger5 ){
      fingernumberread = '2';
    }
    //when finger3 feels the largest force
    else if(finger3 > threshold && finger3 > finger1 && finger3 > finger2 && finger3 > finger4 && finger3 > finger5 ){
      fingernumberread = '3';
    }
    //when finger4 feels the largest force
    else if(finger4 > threshold && finger4 > finger1 && finger4 > finger2 && finger4 > finger3 && finger4 > finger5 ){
      fingernumberread = '4';
    }
    //when finger5 feels the largest force
    else if(finger5 > threshold && finger5 > finger1 && finger5 > finger2 && finger5 > finger3 && finger5 > finger4 ){
      fingernumberread = '5';
    }
    //if they type in 0 meaning they didn't feel two points
    else {
      while (!Serial.available()){}                                                               //Do Absolutely Nothing until something is received over the serial port
      fingernumberread = Serial.read();
      if (fingernumberread == 0){
        threshold = 100;
      }
    }

    //if they picked the correct finger
    if (fingernumberread == fingernumber){
      Serial.println("That is the correct finger. Test will end.");
      return fingernumber;                                                                        //also need to return totalstepstotake
    }

    //if they picked the incorrect finger
    else {
      Serial.println("That is the incorrect finger.");
      totalstepsaround = totalstepsaround + 25;
      lowermotors();  
    }
  }
  Serial.println("You have completed all parts of the two-point discrimination test. The test will now end.");
}

//function to lower the motors
void lowermotors(){
  myCanstack1->step(100, BACKWARD, DOUBLE);
  myCanstack2->step(100, BACKWARD, DOUBLE);
//  myCanstack3->step(100, BACKWARD, DOUBLE);
//  myCanstack4->step(100, BACKWARD, DOUBLE);
//  myCanstack5->step(100, BACKWARD, DOUBLE);
}

//function to run a two point test on finger one
void twopointone(){
  myStepper1->step(25, FORWARD, DOUBLE);                                                          //25 is the number of steps per turn
  myCanstack1->step(100, FORWARD, DOUBLE);                                                        //100 is temporary, should be steps needed to feel force in force test
  myCanstack2->step(100, FORWARD, DOUBLE);
//  myCanstack3->step(100, FORWARD, DOUBLE);
//  myCanstack4->step(100, FORWARD, DOUBLE);
//  myCanstack5->step(100, FORWARD, DOUBLE);
}

//function to run a two point test on finger two
void twopointtwo(){
  myStepper2->step(25, FORWARD, DOUBLE);
  myCanstack1->step(100, FORWARD, DOUBLE); 
  myCanstack2->step(100, FORWARD, DOUBLE);
//  myCanstack3->step(100, FORWARD, DOUBLE);
//  myCanstack4->step(100, FORWARD, DOUBLE);
//  myCanstack5->step(100, FORWARD, DOUBLE);
}

//function to run a two point test on finger three
void twopointthree(){
//  myStepper3->step(25, FORWARD, DOUBLE);
  myCanstack1->step(100, FORWARD, DOUBLE); 
  myCanstack2->step(100, FORWARD, DOUBLE);
//  myCanstack3->step(100, FORWARD, DOUBLE);
//  myCanstack4->step(100, FORWARD, DOUBLE);
//  myCanstack5->step(100, FORWARD, DOUBLE);
}

//function to run a two point test on finger four
void twopointfour(){
//  myStepper4->step(25, FORWARD, DOUBLE);
  myCanstack1->step(100, FORWARD, DOUBLE); 
  myCanstack2->step(100, FORWARD, DOUBLE);
//  myCanstack3->step(100, FORWARD, DOUBLE);
//  myCanstack4->step(100, FORWARD, DOUBLE);
//  myCanstack5->step(100, FORWARD, DOUBLE); 
}

//function to run a two point test on finger five
void twopointfive(){
//  myStepper5->step(25, FORWARD, DOUBLE);
  myCanstack1->step(100, FORWARD, DOUBLE); 
  myCanstack2->step(100, FORWARD, DOUBLE);
//  myCanstack3->step(100, FORWARD, DOUBLE);
//  myCanstack4->step(100, FORWARD, DOUBLE);
//  myCanstack5->step(100, FORWARD, DOUBLE); 
}

