// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 5;

// defines variables
long duration = 0; // duration of sound travel time
int distance = 0; // distance between water and the sensor
unsigned long timeOn = 0; // total time the shower is used for in one cycle

bool showerState = false; 
bool programState = false;

unsigned long startTime = 0;
unsigned long currentTime = 0;

bool timeStatePrint = false; 

String readString;

void setup() 
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzzerPin, OUTPUT);
  
  Serial.begin(9600); // Starts the serial communication
}

void sensor()
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance= duration*0.034/2;

  if(distance <= 20)
  {
    showerState = true;    
  } 

  else
  {
    showerState = false;
  }
}

void startFunction()
{
  if(Serial.available() > 0)
  {
    if(Serial.parseInt() == 1)
    {
      programState = true;
      //Serial.println("ON!");

      tone(buzzerPin, 1000); 
      delay(100);        
      tone(buzzerPin, 2000);  
      delay(100);
      noTone(buzzerPin);     
    }
  }
}

void loop() 
{
  unsigned long timeThisCycle = 0;

  startFunction();
  
  if(programState == true)
  {    
    sensor();
    startTime = millis();
    while(showerState == true)
    {  
      currentTime = millis();
      timeThisCycle = currentTime - startTime;

      timeStatePrint = false;
      sensor();
    }

    timeOn += timeThisCycle / 1000;
    
    if(timeStatePrint == false)
    {
      //Serial.println(timeOn);
      timeStatePrint  = true;
    }

    if(Serial.available() > 0)
    {
      if(Serial.parseInt() == 0)
      {
        Serial.println(timeOn);
        //Serial.println("OFF!");
        programState = false;
        timeOn = 0;

        tone(buzzerPin, 2000); 
        delay(100);        
        tone(buzzerPin, 1000);  
        delay(100);
        noTone(buzzerPin);
      }
    }
  }   
}
