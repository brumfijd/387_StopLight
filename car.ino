
int ping = 7;
int relayData = 5;

long inch, duration;

void setup() {
Serial.begin(9600);
pinMode(relayData, OUTPUT);

}

void loop() {
 sensor();

 if (inch <= 2)
  digitalWrite(relayData, HIGH);
 
 else 
 
  digitalWrite(relayData, LOW);
 

  Serial.print(inch);
  Serial.print(" ");
  Serial.println(digitalRead(relayData));

}


//ultra sonic sensor reads in a car
void sensor(){
  
  //pinMode(trig, OUTPUT);              // 4 pin ultraSonic sensor
  pinMode(ping, OUTPUT);           // 3 pin ultraSonic sensor
  //digitalWrite(trig, LOW);            // 4 pin ultraSonic sensor
  digitalWrite(ping, LOW);         // 3 pin ultraSonic sensor
  delayMicroseconds(5);
  //digitalWrite(trig, HIGH);           // 4 pin ultraSonic sensor
  digitalWrite(ping, HIGH);        // 3 pin ultraSonic sensor
  delayMicroseconds(5);
//digitalWrite(trig, LOW);            // 4 pin ultraSonic sensor
  digitalWrite(ping, LOW);         // 3 pin ultraSonic sensor

  //pinMode(echo, INPUT);               // 4 pin ultraSonic sensor
  pinMode(ping, INPUT);            // 3 pin ultraSonic sensor
 
  //duration = pulseIn(echo, HIGH);       // 4 pin ultraSonic sensor
  duration = pulseIn(ping, HIGH);   //3 pin ultraSonic sensor

  // Converts the duration of pings into inches
  inch = toInches(duration);


}



// Method that converts the time of the pings to inches. 
long toInches(long microseconds) {return microseconds / 74 / 2;}

