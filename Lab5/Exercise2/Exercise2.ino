
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

String apiKey = "64GZ3MKYCSGQ42RJ";  
const char *ssid = "Sosad";  
const char *pass = "12345679";
const char *server = "api.thingspeak.com";
WiFiClient client;  

String ADCData;      
int adcvalue = 0;  

void setup() {
  Serial.begin(115200);
  delay(10);
  WiFi.mode(WIFI_STA);        
  WiFi.begin(ssid, pass);  

  Serial.print("Connecting to");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  const int httpPort = 80; 
  
  if(!client.connect(server, httpPort)){
    Serial.println("Connection Failed");
    delay(300);
    return; 
  }
 
  adcvalue = adcvalue + 1;  
  ADCData = String(adcvalue);   
  String postStr="GET /update?api_key="+apiKey+"&field1="; 
  postStr = postStr + ADCData;
  postStr = postStr + " HTTP/1.1\r\n" 
  postStr = postStr + "Host: " + server + "\r\n" 
  postStr = postStr + "Connection: close\r\n\r\n";                
  client.print(postStr);
  delay(100);
  
  int timeout=0;
  while((!client.available()) && (timeout < 1000))     
  {
    delay(10); 
    timeout++;
  }

  if(timeout < 500){
    while(client.available()){
      Serial.println(client.readString()); 
    }
  }
  else{
    Serial.println("Request timeout..");
  }

 delay(10000);
}
