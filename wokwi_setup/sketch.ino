#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define LED_PIN 13        
#define PIR_PIN 15        
#define BUZZER_PIN 14    
#define SCREEN_WIDTH 128  
#define SCREEN_HEIGHT 64  
#define OLED_RESET -1     

#define DHT_PIN 13       
#define DHT_TYPE DHT22   

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT dht(DHT_PIN, DHT_TYPE);

int pirstate = LOW; 
int value = 0;       

const char* ssid = "Wokwi-GUEST";        
const char* password = ""; 

const char* serverUrl = "https://esp8266-cf2819a51709.herokuapp.com/motion";  

void setup() {
  pinMode(LED_PIN, OUTPUT);   
  pinMode(PIR_PIN, INPUT);     
  pinMode(BUZZER_PIN, OUTPUT); 
  
  Serial.begin(115200);      

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Initializing...");
  display.display();

  dht.begin();

  connectToWiFi();
}

void loop() {
  value = digitalRead(PIR_PIN);  
  float temperature = dht.readTemperature();  
  float humidity = dht.readHumidity();    

  // Check if readings failed and output error message to serial
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    temperature = 0.0;  // Set default/fallback values
    humidity = 0.0;
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");
    
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  } 

  if (value == HIGH) {        
    digitalWrite(LED_PIN, HIGH);   
    digitalWrite(BUZZER_PIN, HIGH);  
    displayMotionStatus("Motion Detected!");
    displayTempHumidity(temperature, humidity); 

    if (pirstate == LOW) {  
      Serial.println("Motion detected!");
      sendMotionData(temperature, humidity);  
      pirstate = HIGH;   
    }
  } else {  
    digitalWrite(LED_PIN, LOW);     
    digitalWrite(BUZZER_PIN, LOW);  
    displayMotionStatus("No Motion");  
    displayTempHumidity(temperature, humidity);  

    if (pirstate == HIGH) {
      Serial.println("Motion ended!");
      pirstate = LOW;    
    }
  }

  delay(500); 
}

void displayMotionStatus(String status) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(status);
  display.display();
}

void displayTempHumidity(float temp, float humidity) {
  display.setCursor(0, 20);
  display.print("Temp: ");
  display.print(temp);
  display.print(" C");
  display.setCursor(0, 30);
  display.print("Humidity: ");
  display.print(humidity);
  display.print(" %");
  display.display();
}

void sendMotionData(float temp, float humidity) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);  
    http.begin(serverUrl);  

    http.addHeader("Content-Type", "application/json");

    String requestData = "{\"motion\":\"detected\", \"temperature\":\"" + String(temp) + "\", \"humidity\":\"" + String(humidity) + "\"}";  // JSON payload with temp and humidity
    int httpResponseCode = http.POST(requestData); 

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);  
      Serial.println(response);          
    } else {
      Serial.println("Error on sending POST");
    }

    http.end(); 
  }
}

void connectToWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected!");
  displayMotionStatus("Connected to WiFi");
}
