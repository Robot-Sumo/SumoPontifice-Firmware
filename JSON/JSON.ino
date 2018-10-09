
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

const char* MAC = "A0-20-A6-0D-53-C9";
const char* ssid = "PointCloudLM";
const char* password = "lugalu2630172";
String server_ip = "192.168.1.100";
String server_port = "8001";
String url_server = "http://"+server_ip+":"+server_port+"/ESP8266/postjson";

void setup() {
 
  Serial.begin(57600);                            //Serial connection
  WiFi.begin(ssid, password);  //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(500);
    Serial.println("Waiting for connection");
 
  }
 
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
    JsonObject& JSONencoder = JSONbuffer.createObject(); 
 
    JSONencoder["sensorType"] = "Temperature";
 
    JsonArray& values = JSONencoder.createNestedArray("values"); //JSON array
    values.add(20); //Add value to array
    values.add(21); //Add value to array
    values.add(23); //Add value to array
 
    JsonArray& timestamps = JSONencoder.createNestedArray("timestamps"); //JSON array
    timestamps.add("10:10"); //Add value to array
    timestamps.add("10:20"); //Add value to array
    timestamps.add("10:30"); //Add value to array
 
    char JSONmessageBuffer[300];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    //Serial.println(JSONmessageBuffer);
 
    HTTPClient http;    //Declare object of class HTTPClient
 
    http.begin(url_server);      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header
 
    int httpCode = http.POST(JSONmessageBuffer);   //Send the request
    String payload = http.getString();                                        //Get the response payload

    StaticJsonBuffer<200> jsonBuffer;

    JsonObject& root = jsonBuffer.parseObject(payload);
    
    long rpm         = root["rpm"];
    if (httpCode>0)
    {
    //Serial.println(httpCode);   //Print HTTP return code
    Serial.println(rpm);    //Print request response payload
    }
    else{
      Serial.println("Error sending JSON to Server");
      }
    http.end();  //Close connection
 
  } else {
 
    Serial.println("Error in WiFi connection");
 
  }
 
  delay(100);  //Send a request every 30 seconds
 
}
