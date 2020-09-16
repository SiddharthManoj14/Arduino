// Pin Initialization
const int buzzer = 5;
const int led = 6;
const int motion = 7;
const int button = 12;

int LED = 8;
int flame_sensor = 4;
int flame_detected;


// Setting Buzzer mode to False
bool buzzer_mode = false;

// For LED
int ledState = LOW;
long previousMillis = 0; 
long interval = 100;  // Interval at which LED blinks


void setup()
{
  
  pinMode(led,OUTPUT); 
  pinMode(buzzer,OUTPUT);

  //Button is our Input
  pinMode(button, INPUT);
  
  
  delay(5000);
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(flame_sensor, INPUT);
}

void loop()

{
   if (digitalRead(motion)) {
    buzzer_mode = true; 
  }

 
  if (buzzer_mode){
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;   
      if (ledState == LOW)
        ledState = HIGH;
      else
        ledState = LOW;
    // Switch the LED
    digitalWrite(led, ledState);
    }
    tone(buzzer,1000);
  }

  // If the alarm is OFF
  if (buzzer_mode == false) {
  
    // No tone & LED off
    noTone(buzzer);  
    digitalWrite(led, LOW);
  }

 
  int button_state = digitalRead(button);
  if (button_state) {buzzer_mode = false;}


  flame_detected = digitalRead(flame_sensor);
  if (flame_detected == 1)
  {
    Serial.println("Flame detected!!");
    digitalWrite(buzzer, HIGH);
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    delay(200);
  }
  else
  {
    Serial.println("No flame detected.");
    digitalWrite(buzzer, LOW);
    digitalWrite(LED, LOW);
  }
  delay(1000);
}
