//Alexander Lutkenhouse and Mike Weiss's Soil Moisture Sensor
//January 7, 2017

// Create the Variables
const int sensorPin= A0;    // pin that the sensor is attached to 
const int ledPin = 9;        // pin that the LED is attached to that's brigthness is proportional to the signal

int sensorValue = 0;         // the sensor value
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value



void setup(){
  //Start Serial
  Serial.begin(9600);

  Serial.print("variables: created");
  
  pinMode(13, OUTPUT); //LED will stay on until calibration is complete
  pinMode(14,OUTPUT);
  digitalWrite(13,HIGH);
  digitalWrite(14,LOW);
  
  while(millis()<5000){
    sensorValue = analogRead(sensorPin);
    //sensorValue1 = analogRead(sensorPin1);
    
    // Record the Maximum Sensor Value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }
    
    // Record the Minimum Sensor Value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
    digitalWrite(13,LOW);
    delay(500);
    digitalWrite(13,HIGH);
  }
  // Signal end of the calibration period
  digitalWrite(13, LOW);
  digitalWrite(14,HIGH);
  delay(1500);
  digitalWrite(14,LOW);
//  for(i = 1 : i<=5 : i++){
//    digitalWrite(14,HIGH);
//    delay(1500);
//    digitalWrite(14,LOW);
//    delay(500);
//  }
//  Serial.print("Max_Value\tMin_Value\n");
//  Serial.print(sensorMax);
//  Serial.print("\t");
//  Serial.print(sensorMin);
}

void loop{
   // read the sensor:
  sensorValue = analogRead(sensorPin);

  // apply the calibration to the sensor reading
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);

  // in case the sensor value is outside the range seen during calibration
  sensorValue = constrain(sensorValue, 0, 255);

  // fade the LED using the calibrated value:
  analogWrite(ledPin, sensorValue);
}
}
