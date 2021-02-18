#include <WiFi.h>

const String id ="180263G";
const char* ssid     = "";
const char* password = "";
const char* host ="";
const uint16_t port=12345;
String msg="Guess my name? Hint:"+id;
void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
  delay(5000);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
  
void loop() {
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(":");
  Serial.println(port);
  WiFiClient client;      // create a TCP connection
  if (!client.connect(host,port)){
    Serial.println("Connection failed");
    delay(5000);
    return;
  }
  Serial.println("Sending data to server");
  if (client.connected()){
    client.println(msg);
  }
  unsigned long timeout=millis();
  while(client.available()==0){
    if (millis()-timeout>5000){
      Serial.println(">>>Client timeout>>>");
      client.stop();
      delay(5000);return;
    }
  }
  Serial.println("Receiving data from remote server");
  while(client.available()){
    char ch =static_cast<char>(client.read());
    Serial.print(ch);
  }
  Serial.println();
  Serial.println("closing connection");
  client.stop();
  delay(300000);

}
