
#include <WiFi.h>

const char* ssid     = "ssid";
const char* password = "passwordgit";

void setup() {
  // start serial connection
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.println();

  // start wifi connection
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println();
  Serial.println();
  Serial.println();
 
}


void loop() {
  // put your main code here, to run repeatedly:

}
