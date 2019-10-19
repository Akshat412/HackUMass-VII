// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;

// defines variables
long duration; // duration of sound travel time
int distance; // distance between water and the sensor
long timeOn; // total time the shower is used for in one cycle

bool showerState; 
bool programState;

unsigned long startTime;
unsigned long currentTime;

void setup() 
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication

  programState = true;
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

void loop() 
{
  if(programState == true)
  {
    sensor();
    startTime = millis();
    while(showerState == true)
    {  
      currentTime = millis();
      unsigned long timeThisCycle = currentTime - startTime;

      if(timeThisCycle % 1000 == 0)
      {
        Serial.println(timeThisCycle / 1000);
      }
            
      sensor();
    }
  } 
}
