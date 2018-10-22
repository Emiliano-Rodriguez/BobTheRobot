/* 
 *This algorithm was created by Emiliano Rodriguez, 
 *Controls Bob the Robot by 2 servos, Leds and push button. 
 *
 *Bob looks around the room given random coordinates, also pulls LED vison when 
 *needed. After 3-6 minutes (premeditated by BOB) he goes to sleep and can only
 *be woken by (electric shock) via the push button located on its side. 
*/


#include <Servo.h> //adds Servo library for methods 

//Initialize objects/ data types 
Servo body, eyes; 
unsigned long timer; 
unsigned long tic; 
int brightness;    // how bright the LED is
int n = 0; 
int Num = 0;
int photoCell;


void setup() {
  // attaches objects/data types to arduino pins and declare Input/Output 
    body.attach(3);
    eyes.attach(4);
    pinMode(2, INPUT);
    pinMode(6, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    
    randomSeed(analogRead(5)); //seeds random number for random sequence upon start

    Serial.begin(9600); //begin Serial monitor (useful for debugging)


}

void loop() {

    /*
     * sets timer (seconds) and random number 1-13 to read from
     * prints to Serial monitor 
     */
    timer = ((millis()/1000) - (tic/1000));
    Num = random(1,13);
    Serial.println(Num); 


    if(Num == 2 || Num == 3 ||Num == 4 || Num == 8 || Num == 12)
       bod(); // call bod method if random numbers above appear (see below)
   
    eye(); //call eye method (see below)

    if(Num == 5 || Num == 7 )
       led(); // calls LED eye method if numbers generated (see below)
       
    if(timer > random(180,360)){  
       sleep(); //if timer is inbetween (180-360) seconds, go to sleep
       tic=millis(); 
    }
}

void bod() {
    body.write(random(115,170)); //random servo (body) position range (115-170)
  
}

void eye() {

  for(int i = 0; i<4;i++) { //for loop writes random eye position range (93-102)
    analogWrite(9,255);
    eyes.write(random(93,102));
    delay(random(400,2000));
  }
}

void sleep() {
    analogWrite(9,0); //turn LEDs off

  while(digitalRead(2) != HIGH) {
    eyes.write(47); //turn to sleeping eye position (47) while button is NOT pushed 
  }
   for(int i = 0; i< 10; i++) {
       
    digitalWrite(10,255); 
    body.write(100);
    delay(50); 
    digitalWrite(10,LOW); 
    body.write(120);
    delay(40);
     eyes.write(97);
   }
}


void led() {
  analogWrite(9,LOW); //turn off blue LED
  for(int i = 0; i<30;i++) {
    eyes.write(random(140,148)); //switch LED eye posistion randomly
    digitalWrite(6, 220);   
    digitalWrite(11, i);   
    delay(150);
    if(i % 3 == 0)
    analogWrite(11,LOW); //On/off for red light on top
    delay(150);
  }
      digitalWrite(11, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(6, LOW);    // turn the LED off by making the voltage LOW
}
