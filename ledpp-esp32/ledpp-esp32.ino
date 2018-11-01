
#include <WiFi.h>
#include <Adafruit_NeoPixel.h>

#define PIN 5
#define NUMPIXELS 10

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const char* ssid     = "ssid";
const char* password = "password";

WiFiServer server(80);

void setup() {
  // start serial connection
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.println();

  // init NeoPixels lib
  Serial.println("Init NeoPixels lib");
  pixels.begin();

  // set color
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(150,150,150));
    pixels.show();
  }

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

  // start server
  server.begin();
  Serial.println("Server started");
  Serial.println();
}


void sendHttpResponse(WiFiClient client) {
  // HTTP header
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();

  // HTTP content
  client.print("Hello world!");

  // HTTP response end
  client.println();
}


void loop() {
  // listen for incoming connections
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New client");
    String incommingLine = "";

    while (client.connected()) {
      // if there is something to read from client
      if (client.available()) {
        // read char
        char c = client.read();

        // if byte is newline char
        if (c == '\n') {
          if (incommingLine.length() == 0) {
            // second newline => end of HTTP request
            Serial.println();
            sendHttpResponse(client);
            break;
          }
        // cariage return
        } else if (c == '\r') {
          Serial.println(incommingLine);
          incommingLine = "";
        // other byte
        } else {
          incommingLine += c;
        }
      }
    }

    // close the connection:
    client.stop();
  }
}
