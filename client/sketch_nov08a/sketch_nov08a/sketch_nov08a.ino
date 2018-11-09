#include <SerialCommands.h>
#include <ESP8266WiFi.h>
#include <SocketIOClient.h>
 
SocketIOClient client;
const char* ssid = "wifi quan chung";
const char* password = "wifidanghong";

//const char* ssid = "Redmi";
//const char* password = "12345678";
char hostname[] = "192.168.100.126";// host cua server
int port = 3484;
//char namespace_esp8266[] = "esp8266";   //Thêm Arduino!
 
// RID: Tên hàm (tên sự kiện
// Rfull: Danh sách biến (được đóng gói lại là chuối JSON)
extern String RID;
extern String Rfull;
//
int InputPin = 2;   //using digital pin10 as input
int ledPin = 16;
bool Pin_Status = LOW;
void setup()
{
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
    
//    if (!client.connect(hostname, port)) {
//        Serial.println(F("Ket noi den socket server that bai!"));
//        return;
//    } 
//     if (client.connected())
//     {
//        client.send("connection", "message", "Connected !!!!");
//     }
//     else
//    {
//     Serial.println("Connection Error");
//     while(1);
//    }
//   delay(1000);  
}
 
void loop()
{
  Pin_Status = digitalRead(InputPin);
  //Serial.print(Pin_Status);
  if (Pin_Status == HIGH){
    digitalWrite(ledPin, LOW);
  }
  if (Pin_Status == LOW){
    digitalWrite(ledPin, HIGH);
    //client.send("PIR","status","Motion detected");
  }
//  if (!client.connected()) {
//    client.reconnect(hostname, port);
//  }
}
