#define ledPin 16
int charReceived;

void setup(){
  pinMode(ledPin, OUTPUT); 
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()){
    char temp = Serial.read();
    if(32 <= temp && temp <= 126) 
      charReceived = temp;
  }
  if (charReceived == 'O') 
    digitalWrite(ledPin,LOW);
  else if (charReceived == 'F') 
    digitalWrite(ledPin,HIGH);
  delay(10);
}
