void setup(){
  pinMode(16, OUTPUT);     
}

void loop()
{
  digitalWrite(ledPin, LOW);   
  delay(3000);                  
  digitalWrite(ledPin, HIGH);    
  delay(1000);                  
}
