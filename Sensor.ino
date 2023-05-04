#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"
#include "DHTesp.h"
#include "Adafruit_SSD1306.h"
#include "Fonts/FreeSerif9pt7b.h"
#define DHTPIN 14
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

DHTesp dht;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 5, /* data=*/ 4);

const char *ssid = "HOTSPOT - TI";
const char *password = "ptpn9jaya";
const char *host = "http://dash.ptpnix.co.id/hrsistems/api/trysendnotif?nik=9015463";
const int analogInPin = 0;  // Analog input pin that the potentiometer is attached to
// int sensorValue = 0;        // value read from the potentiometer
// int outputValue = 0;
float hm= 0;
float temp= 0;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)");
  // Autodetect is not working reliable, don't use the following line
  // dht.setup(17);
  // use this instead: 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  dht.setup(DHTPIN, DHTesp::DHT22); // Connect DHT sensor to GPIO 5
 
  // Explicitly set the ESP8266 to be a WiFi-client
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // u8g2.begin();
  // u8g2.setFont(u8g2_font_logisoso62_tn);
  // u8g2.setFontMode(0);    // enable transparent mode, which is faster

  Serial.println("Wifi Connected");
  Serial.println(WiFi.localIP());
}

void loop() {
    // read the analog in value:
    // temp = analogRead(A0);
    //   // map to range. The pot goes from about 3 to 1023. This makes the sent value be between 0 and 999 to fit on the OLED
    // outputValue = map(temp, 3, 1023, 0, 999);

    // char intToPrint[5];
    // itoa(outputValue, intToPrint, 10); //integer to string conversion for OLED library
    // u8g2.firstPage();
    // u8g2.drawUTF8(0, 64, intToPrint);
    // u8g2.nextPage();
    delay(3000);
    display.setFont(&FreeSerif9pt7b);
    display.clearDisplay();
    display.setTextSize(0.5);
    display.setTextColor(WHITE);
    display.setCursor(0, 40);
    // Your code here 
    hm= dht.getHumidity();
    temp=dht.getTemperature();
    //  Serial.println(temp);
    //  Serial.println(hm);

    // Serial.print(" Connecting to ");
    // Serial.println(host);
 
  // if (WiFi.status() == WL_CONNECTED && (temp>=27 || hm>68 )) {
  //     WiFiClient client;
  //     HTTPClient http;
  //     http.begin(client,host);
  //     http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  //     // Data to send with HTTP POST
  //     String httpRequestData = String("temp=")+temp+"&hum="+hm;  
  //     Serial.println(httpRequestData);         
  //     // Send HTTP POST request
  //     int httpResponseCode = http.POST(httpRequestData);
     
      // Serial.print("HTTP Response code: ");
      // Serial.println(httpResponseCode);
    Serial.print("Temperature ");
    Serial.println(temp);
    Serial.print("Humidity ");
    Serial.println(hm);
    display.println("Temp : " + String(temp) + " C");
    display.display();
    display.println("Hum : " + String(hm) + " %");
    display.display();
    // Serial.print("sensor = ");
    // Serial.print(temp);
    // Serial.print("\t output = ");
    // Serial.println(outputValue);  
      // Free resources
      // http.end();
  // }
  
}


/*
  Since Temperature is READ_WRITE variable, onTemperatureChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onTemperatureChange()  {
  // Add your code here to act upon Temperature change
}

/*
  Since Humidity is READ_WRITE variable, onHumidityChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onHumidityChange()  {
  // Add your code here to act upon Humidity change
}



/*
  Since Message is READ_WRITE variable, onMessageChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onMessageChange()  {
  // Add your code here to act upon Message change
}


