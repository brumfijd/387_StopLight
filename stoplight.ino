
// JACOB BRUMFIELD
// ECE 387 Individual Project
// STOPLIGHT 
// 8 May 2017

//=============== Pins

int nsWalkWay1 = 6;

int ewWalkWay1 = 4;

int ewRED = 13;
int ewYELLOW = 12;
int ewGREEN = 11;

int nsRED = 7;
int nsYELLOW = 8;
int nsGREEN = 9;

int northTrig = 12;
int northEcho = 11;
int southPing = 13;

//============== Digital Communication pins
int relayData = 10;

//=============== States

const int redLight = 0;         // RED LIGHT
const int delayRed = 1;         // DELAY RED
const int setSignalTimer = 2;   // BLINKER TIMER    
const int blinkOn = 3;          // GREEN LIGHT ON
const int blinkOff = 4;         // GREEN LIGHT OFF
const int setWalkerTimer = 5;   // WALKER TIMER FOR NORTH/SOUTH
const int walk = 6;             // WALKER FOR NORTH/SOUTH
const int greenLight = 7;       // GREEN
const int delayGreen = 8;       // DELAY GREEN
const int walkerTimer = 9;      // WALKER TIMER FOR EAST/WEST
const int walk2 = 10;           // WALKER FOR EAST/WEST
const int yellowLight = 11;     // YELLOW
const int delayYellow = 12;     // DELAY YELLOW
const int carDetect = 13;       // CAR SETUP
const int carTimer = 14;        // EXTRA TIME


// =============== Variables
int nsButtonState1 = 0;
int nsButtonState2 = 0;
int ewButtonState1 = 0;

static int state = setSignalTimer;
int rounds = 0;
int turnSignal = 0;
int countBlink = 0;

// =============== Time Stamps
unsigned long timeChecker;

unsigned long redTimer = 9000;      // 9 second long red light
unsigned long yellowTimer = 3000;   // 3 second long yellow light
unsigned long greenTimer = 6000 ;   // 6 second long green light
unsigned long walkTimer = 2000;     // makes the red light 2 seconds longer
unsigned long greenTurnTime = 500;  // Turns green light on/off for .5 sec to indicate turn arrow
unsigned long carTime = 6000;      // Makes the green light 5 seconds longer because of car detection


void setup() {
  Serial.begin(9600);
 
  pinMode(nsRED, OUTPUT);
  pinMode(nsYELLOW, OUTPUT);
  pinMode(nsGREEN, OUTPUT);

  pinMode(ewRED, OUTPUT);
  pinMode(ewYELLOW, OUTPUT);
  pinMode(ewGREEN, OUTPUT);
  
  pinMode(nsWalkWay1, INPUT);
  pinMode(ewWalkWay1, INPUT);

  pinMode(relayData, INPUT);
  timeChecker = millis();

//  pinMode(relayRed, OUTPUT);
//  pinMode(relayYellow, OUTPUT);
//  pinMode(relayGreen, OUTPUT);
}


void loop() {
  
  switch(state){

   // ================================= 1st STATE
      case redLight:
      // Testing purposes
      Serial.println("STATE: redLight");

      // LEDS on North and South lanes
      digitalWrite(nsRED, HIGH);
      digitalWrite(nsGREEN, LOW);
      digitalWrite(nsYELLOW, LOW);
      digitalWrite(ewRED, LOW);
      digitalWrite(ewYELLOW, LOW);
      digitalWrite(ewGREEN, HIGH);
      
      turnSignal++;
      state = delayRed;
      timeChecker = millis();
      break;

   // ================================= 2nd STATE
      case delayRed:
        //Testing purposes
        Serial.println("STATE: delayRed");
             

        if (millis() >= timeChecker + 6000){
           digitalWrite(ewRED, LOW);
           digitalWrite(ewYELLOW, HIGH);
           digitalWrite(ewGREEN, LOW);
        }
          
   
        if ((digitalRead(nsWalkWay1) == HIGH && millis() <= timeChecker + 5000))
         state = setWalkerTimer;
          
        else if (millis() >= timeChecker + redTimer)
          state = greenLight;     
         
        if (turnSignal >= 1){
          if (millis() >= timeChecker + redTimer)
          state = setSignalTimer;
        }
       
        break;

   // ================================= 3rd STATE
      case setSignalTimer:
      // Serial.println("STATE: setSignalTimer");

          turnSignal = 0;
          Serial.println(countBlink);
      
          if (countBlink % 2 == 1)
              state = blinkOn;
          if (countBlink % 2 == 0)
              state = blinkOff;
          if (countBlink >= 300)
              state = greenLight;
          
       timeChecker = millis();
       break;
       
   // ================================= 4th STATE
     case blinkOn:

        Serial.println("STATE: blinkOn");
        
        digitalWrite(nsGREEN, HIGH);
        digitalWrite(nsYELLOW, LOW);
        digitalWrite(nsRED, LOW);
        digitalWrite(ewGREEN, LOW);
        digitalWrite(ewYELLOW, LOW);
        digitalWrite(ewRED, HIGH);
        countBlink++;

        if (millis() >= timeChecker + greenTurnTime)
          state = setSignalTimer;
        break;
       
   // ================================= 5th STATE
      case blinkOff:

       Serial.println("STATE: blinkOff");
        digitalWrite(nsGREEN, LOW);
        digitalWrite(nsYELLOW, LOW);
        digitalWrite(nsRED, LOW);
        digitalWrite(ewGREEN, LOW);
        digitalWrite(ewYELLOW, LOW);
        digitalWrite(ewRED, HIGH);
        countBlink++;

        if (millis() >= timeChecker + greenTurnTime)
          state = setSignalTimer;
        
        break;
          
   // ================================= 6th STATE
       case setWalkerTimer:
            Serial.println("STATE: setWalkerTimer");
            digitalWrite(ewRED, LOW);
            digitalWrite(ewYELLOW, HIGH);
            digitalWrite(ewGREEN, LOW);
           state = walk;
           
         timeChecker = millis();
         break;

   // ================================= 7th STATE
      case walk:

         Serial.println("STATE: walk" );
        
        
        if (millis() >= timeChecker + walkTimer)
           state = greenLight;

        break;
   // ================================= 8th STATE
     case greenLight:
    
      // LEDS on North and South lanes
      Serial.println("STATE: greenLight");
     
      digitalWrite(nsRED, LOW);
      digitalWrite(nsGREEN, HIGH);
      digitalWrite(nsYELLOW, LOW);
      digitalWrite(ewRED, HIGH);
      digitalWrite(ewYELLOW, LOW);
      digitalWrite(ewGREEN, LOW);
      
      countBlink = 0;

      state = delayGreen;
      timeChecker = millis();

      break;
      
   // ================================= 9th STATE
      case delayGreen:
        Serial.println("STATE: delayGreen");

            
         if (millis() >= timeChecker + greenTimer)
            state = yellowLight; 

         if ((digitalRead(ewWalkWay1)== HIGH && millis() <= timeChecker + 5000))
            state = walkerTimer;
    
         if (digitalRead(relayData) == HIGH)
            state = carDetect;

         break;

   // ================================= 10th STATE
      case walkerTimer:

        Serial.println("STATE: walkerTimer");

        state = walk2;
        timeChecker = millis();

        break;
   // ================================= 11th STATE
      case walk2:
        Serial.println("STATE: walk2");

        if (millis() >= timeChecker + walkTimer)
            state = yellowLight;

        break;
   // ================================= 12th STATE
      case yellowLight:

       // LEDS on North and South lanes
      Serial.println("STATE: yellowLight");
      
      digitalWrite(nsRED, LOW);
      digitalWrite(nsGREEN, LOW);
      digitalWrite(nsYELLOW, HIGH);
      digitalWrite(ewRED, HIGH);
      digitalWrite(ewYELLOW, LOW);
      digitalWrite(ewGREEN, LOW);
  
      state = delayYellow;
      timeChecker = millis();

      break;

   // ================================= 13th STATE
      case delayYellow:

      Serial.println("STATE: delayYellow");
    
        if (millis() >= timeChecker + yellowTimer)
          state = redLight;

   
      break;
    

   // ================================= 14th STATE
      case carDetect:

      Serial.println("STATE: carDetect");
        digitalWrite(nsRED, LOW);
        digitalWrite(nsGREEN, HIGH);
        digitalWrite(nsYELLOW, LOW);
        digitalWrite(ewRED, HIGH);
        digitalWrite(ewYELLOW, LOW);
        digitalWrite(ewGREEN, LOW);

        state = carTimer;
        
      timeChecker = millis();
      break;

   // ================================= 15th STATE
      case carTimer:


      Serial.println("STATE: carTimer");
      if (millis() >= timeChecker + carTime){
        state = yellowLight;
      }

      break;
       
    }
}

//
//// Ultra sonic sensor reads in a car
//void northUltra(){
//  pinMode(northTrig, OUTPUT);              // 4 pin ultraSonic sensor
//  //pinMode(ultra, OUTPUT);           // 3 pin ultraSonic sensor
//  digitalWrite(northTrig, LOW);            // 4 pin ultraSonic sensor
//  //digitalWrite(ultra, LOW);         // 3 pin ultraSonic sensor
//  delayMicroseconds(5);
//  digitalWrite(northTrig, HIGH);           // 4 pin ultraSonic sensor
//  //digitalWrite(ultra, HIGH);        // 3 pin ultraSonic sensor
//  delayMicroseconds(5);
//  digitalWrite(northTrig, LOW);            // 4 pin ultraSonic sensor
//  //digitalWrite(ultra, LOW);         // 3 pin ultraSonic sensor
//
//  pinMode(northEcho, INPUT);               // 4 pin ultraSonic sensor
//  //pinMode(ultra, INPUT);            // 3 pin ultraSonic sensor
//  
//  duration = pulseIn(northEcho, HIGH);       // 4 pin ultraSonic sensor
//  //duration = pulseIn(ultra, HIGH);   //3 pin ultraSonic sensor
//
//  // Converts the duration of pings into inches
//  inch = toInches(duration);
//

//}
//
////ultra sonic sensor reads in a car
//void southUltra(){
//  //pinMode(trig, OUTPUT);              // 4 pin ultraSonic sensor
//  pinMode(southPing, OUTPUT);           // 3 pin ultraSonic sensor
//  //digitalWrite(trig, LOW);            // 4 pin ultraSonic sensor
//  digitalWrite(southPing, LOW);         // 3 pin ultraSonic sensor
//  delayMicroseconds(5);
//  //digitalWrite(trig, HIGH);           // 4 pin ultraSonic sensor
//  digitalWrite(southPing, HIGH);        // 3 pin ultraSonic sensor
//  delayMicroseconds(5);
//  //digitalWrite(trig, LOW);            // 4 pin ultraSonic sensor
//  digitalWrite(southPing, LOW);         // 3 pin ultraSonic sensor
//
//  //pinMode(echo, INPUT);               // 4 pin ultraSonic sensor
//  pinMode(southPing, INPUT);            // 3 pin ultraSonic sensor
//  
//  //duration = pulseIn(echo, HIGH);       // 4 pin ultraSonic sensor
//  duration = pulseIn(southPing, HIGH);   //3 pin ultraSonic sensor
//
//  // Converts the duration of pings into inches
//  inch = toInches(duration);
//
//
//}



// Method that converts the time of the pings to inches. 
long toInches(long microseconds) {return microseconds / 74 / 2;}

