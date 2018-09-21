#define ledPin 16
#define inPin 2
#define MID 3
#define LED_ON 2
#define LED_OFF 1
#define INIT 0
#define TIMEON 300

int T, state, sensor;
void setup(){
  T = 0;
  state = INIT;
  sensor = 0;
  pinMode(ledPin, OUTPUT);  
  pinMode(inPin, INPUT);   
  Serial.begin(9600); 
}

void loop(){
  
  
  switch(state){
    case LED_ON:
      if (T > TIMEON){ 
        state = MID; 
        Serial.print(state);
        T = 0;
      }
      else T++;
      break;
    case MID:
      if (digitalRead(inPin) == 1){ 
        state = LED_ON;
        Serial.print(state);
      }
      else{
        state = LED_OFF;
        Serial.print(state);
        digitalWrite(ledPin, HIGH); 
      }
      break;
    case LED_OFF:
      if (digitalRead(inPin) == 1){ 
        state = LED_ON; T = 0; 
        Serial.print(state);
        digitalWrite(ledPin, LOW); 
      }
      else T++;
      break; 
    default: 
      Serial.print(state);
      T = 0;
      state = LED_OFF;
      digitalWrite(ledPin, HIGH);
      break;
  }
  delay(10);
}
