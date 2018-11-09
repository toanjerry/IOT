#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SocketIOClient.h>
#include <SerialCommands.h>
 
// Replace with your network credentials
const char* ssid = "Redmi";
const char* password = "12345678";
 
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
 
String page = "";
int InputPin = 2;   //using digital pin10 as input
int ledPin = 16;
bool Pin_Status = LOW;
void setup(void){
  //the HTML of the web page
  page = "<h1><h1>NodeMCU Web Server</h1><p><a href=\"status\"><button>Get</button></a>&nbsp;</p>";
  //make the LED pin output and initially turned off
   
  pinMode(InputPin, INPUT);  //input declaration
    pinMode(ledPin, OUTPUT);
    //Bật baudrate ở mức 115200 để giao tiếp với máy tính qua Serial
    Serial.begin(115200);
    delay(10);
 
    //kết nối vào mạng Wifi
    Serial.println();
    Serial.print("Ket noi vao mang ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
 
    //Chờ đến khi đã được kết nối
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print('.');
    }
// 
    Serial.println();
    Serial.println(F("Da ket noi WiFi"));
    Serial.println(F("Di chi IP cua ESP8266 (Socket Client ESP8266): "));
    Serial.println(WiFi.localIP());
   
  server.on("/", [](){
    server.send(200, "text/html", page);
  });
  server.on("/status", [](){
    //delay(1000);
  });
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){
  server.handleClient();
  Pin_Status = digitalRead(InputPin);
  Serial.print(Pin_Status);
  if (Pin_Status == HIGH){
    digitalWrite(ledPin, LOW);
    page = "<h1>NodeMCU Web Server</h1><p><a href=\"status\"><button>Get</button></a>&nbsp;<br><p>status:no motion</p></p>";
    server.send(200, "text/html", page);
     delay(1000);
  }
  if (Pin_Status == LOW){
    digitalWrite(ledPin, HIGH);
    delay(200);
    page = "<h1>NodeMCU Web Server</h1><p><a href=\"status\"><button>Get</button></a>&nbsp;<br><p>status: motion detected</p></p>";
    server.send(200, "text/html", page);
     delay(1000);
  }
}
