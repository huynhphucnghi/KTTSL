#define ledPin 16
#define LED_ON 1
#define LED_OFF 0
#define READY 2
#define INIT 3

char charReceived;
int state;
bool OFF_check;
int T, T_OUT;
char cmdBuffer[4] = "";

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
    char temp = Serial.read();
    Serial.println(temp);
    if((32 <= temp && temp <= 126)) 
//      charReceived = temp;
      strncat(cmdBuffer, &temp, 1); 
  }
  switch(state){
    case READY:
      if (strcmp("O", cmdBuffer) == 0){
        state = LED_ON;
        Serial.println("LED_ON_PRE");
      }
      break;
    case LED_ON:
      if (strcmp("O", cmdBuffer) == 0) T++;
      else if (strcmp("ON", cmdBuffer) == 0){
        state = READY;
        digitalWrite(ledPin,LOW);
        Serial.println("LED_ON");
        T = 0;
        cmdBuffer[0] = 0;
      }
      else if (strcmp("OF", cmdBuffer) == 0){
        state = LED_OFF;
        Serial.println("LED_OFF_PRE");
      }
      else {
        state = READY;
        T = 0;
        cmdBuffer[0] = 0;
      }
      break;
    case LED_OFF:
      if (strcmp("OF", cmdBuffer) == 0) T++;
      else if (strcmp("OFF", cmdBuffer) == 0){
        state = READY;
        digitalWrite(ledPin,HIGH);
        Serial.println("LED_OFF");
        T = 0;
        cmdBuffer[0] = 0;
      }
      else {
        state = READY;
        T = 0;
        cmdBuffer[0] = 0;
      }
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
