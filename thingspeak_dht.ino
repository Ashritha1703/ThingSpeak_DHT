#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>
#define DHTPIN D4
#define DHTTYPE DHT11
const char* SSID="Ashritha";
const char* password="12345678";
WiFiClient client;
unsigned long mychannelNumber=3026434;
const char* myWriteAPIKey="2AAL5D7ETBUQWSP6";
DHT dht(DHTPIN,DHTTYPE);
void setup(){
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(SSID,password);
  Serial.print("connected to WiFi");
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.print("\n connecting to WiFI");
  ThingSpeak.begin(client);

}
void loop(){
  float h= dht.readHumidity();
  float t=dht.readTemperature();
  if(isnan(h)||isnan(t)){
    Serial.print("failed to read values");
    delay(200);
    return;
  }
  Serial.print("Temperature:");
  Serial.print(t);
  Serial.print("c");
  Serial.print("Humidity:");
  Serial.print(h);
  Serial.print("%");
  ThingSpeak.setField(1,t);
  ThingSpeak.setField(2,h);
  int x=ThingSpeak.writeFields(mychannelNumber,myWriteAPIKey);
  if(x==200){
    Serial.print("data pushed successfully");
  }else{
    Serial.print("push error");
    Serial.print(x);
  }
  delay(5000);
}