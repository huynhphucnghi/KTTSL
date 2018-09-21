#define ledPin 16
#define READY 1
#define INIT 0
#define CHECK 2

#define SECRET_CODE "OPEN"

int state;
int T, T_OUT;
char temp;
char cmdBuffer[32] = "";

void setup() {
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  state = INIT;
  T = 0;
  T_OUT = 500;
  delay(1000);
}

void loop() {
  if (Serial.available()){
    temp = Serial.read();
    Serial.println(temp);
  }
  switch(state){
    case READY:
      if (temp =='#') state = CHECK;
      else if((32 <= temp && temp <= 126)) 
        strncat(cmdBuffer, &temp, 1); 
      if (cmdBuffer[0] != 0) T++;
      break;
    case CHECK:
      if (strlen(cmdBuffer) >= strlen(SECRET_CODE) && strcmp(SECRET_CODE, cmdBuffer+strlen(cmdBuffer)-4) == 0) {
        digitalWrite(ledPin,LOW);
        Serial.println("LED_ON");
      }
      else{
        digitalWrite(ledPin,HIGH);
        Serial.println("LED_OFF");
      }
        state = READY;
      T = 0;
      cmdBuffer[0] = 0;
      break;
    default:
      state = READY;
      digitalWrite(ledPin,HIGH);
      Serial.println("INIT");
      break;
  }
  if (T > T_OUT) {
    state = READY;
    Serial.println("TIME OUT");
    T = 0;
    cmdBuffer[0] = 0;
  }
  delay(10);
}
