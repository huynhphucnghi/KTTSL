#define ledPin 16    

int count, T, i;
bool status;

void setup(){
  count = 0;
  status = 1;
  T = 10;      // T = 1/F = 0.2s
  pinMode(ledPin, OUTPUT);   
  digitalWrite(ledPin, status);
}

void loop(){
  if(i < T) I ++;
  else{
    i = 0;
    status = !status;
    digitalWrite(ledPin, status);
  }
  delay(10);
}
