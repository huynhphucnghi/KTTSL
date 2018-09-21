#define ledPin 16    
#define LED_ON 1
#define LED_OFF 0     
#define INIT 2      

int T_on, T_off, T, state;

void setup(){
  T_on = 100;
  T_off = 200;
  T = 0;
  state = INIT;
  pinMode(ledPin, OUTPUT);    
  Serial.begin(9600); 
}

void loop(){
  switch(state){
    case LED_ON:
      if (T > T_on){ 
        state = LED_OFF; T = 0; 
        digitalWrite(ledPin, HIGH); 
      }
      else T++;
      break;
    case LED_OFF:
      if (T > T_off){ 
        state = LED_ON; T = 0; 
        digitalWrite(ledPin, LOW); 
      }
      else T++;
      break; 
    default: 
      T = 0;
      state = LED_ON;
      digitalWrite(ledPin, HIGH);
      break;
  }
  delay(10);
}
