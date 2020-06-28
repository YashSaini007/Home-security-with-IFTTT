
#include <ESP8266WiFi.h>
const char* ssid     = "Name_ABC";      // SSID of local network
const char* password = "Pass_ABC";   // Password on network

void setup() 
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
}

void ifttt() //Wifi connection and send all the data to IFTTT
{
  const char host[ ]        = "maker.ifttt.com";          // maker channel of IFTTT
  const char trigger[ ]     = "Name of the trigger";                   //name of the trigger you would like to send to IFTTT
  const char APIKey[ ]      = "key";      //Your maker key for Webhooks on IFTTT
  Serial.print("Connect to: ");
  Serial.println(host);

  
  // WiFiClient to make HTTP connection
  WiFiClient client;
  if (!client.connect(host, 80))  
   {
      Serial.println("connection failed");
      return;  
   }
    

// Build URL
  String url = String("/trigger/") + trigger + String("/with/key/") + APIKey;
  Serial.print("Requesting URL: ");
  Serial.println(url);

// Send request to IFTTT
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n"); 
  //FYI rn rn is just two new lines to comply with http format
   delay(20);

// Read all the lines of the reply from server and print them to Serial
  Serial.println("Respond:");
  while(client.available())
   {
      String line = client.readStringUntil('\r');
      Serial.print(line);
   }
  Serial.println();
  Serial.println("closing connection");
  client.stop(); 
  
  delay (1000); //This delay here just to stop spamming of emails- should be polished to a better method/location
  
  Serial.println("Deep Sleep");
  ESP.deepSleep(0); // Goes to deep sleep after it sends message to ifttt
 
 }
 
  
void loop()  // keeps on repeating untill it connects to your wifi

{
     ifttt(); //Tell IFTTT that intruder detected
} 
 

  
