 #define BLYNK_PRINT Serial    
 #include <SPI.h>  
 #include <ESP8266WiFi.h>  
 #include <BlynkSimpleEsp8266.h>  
 #include <DHT.h>  
 #define BLYNK_PRINT Serial  
BlynkTimer timer;

 // Your WiFi credentials.
// Set password to "" for open networks.
 char auth[] ="NOeVPSiGLpxeyrSWl-VSUI5vz5mFgFbz";   //// You should get Auth Token in the Blynk App.
 char ssid[] = "iPhone";   
 char pass[] = "100200800900"; 
 int moisturelevel= 0; 
 const int relay = 23;
 const int moistureLevelSensor = 15;
 #define DHTPIN 2    //d4    
 #define DHTTYPE DHT11   // DHT11 SENSOR CONNECT D4 PIN  
 DHT dht(DHTPIN, DHTTYPE);  
 
 
 //'''''''''''''''''''''''THIS IS THE FIRST FUNCTION FOR DHT11 SENSOR 
 void sendSensor()  
 {  
  float h = dht.readHumidity();  
  float t = dht.readTemperature();  
  if (isnan(h) || isnan(t)) {  
   Serial.println("Failed to read from DHT sensor!");  
   return;  
  }  
  //''''''''YOU CAN SEND ANY VALUE AT ANY TIME 
  Blynk.virtualWrite(V5, h); //V5 is for Humidity  
  Blynk.virtualWrite(V6, t); //V6 is for Temperature  
 }  
  //'''''''''''''''''''''''THIS IS THE SECOND  FUNCTION FOR SOIL MOISTURE SENSOR 
 void sendSensor2()  
 { moisturelevel=analogRead(moistureLevelSensor);
  moisturelevel=map(moisturelevel,0,4000, 0,40);

  if (isnan(moisturelevel)) {  
   Serial.println("Failed to read from Moisture-Level-Sensor sensor!");  
   return;  
  }  
  
  //''''''''YOU CAN SEND ANY VALUE AT ANY TIME 
  Blynk.virtualWrite(V2, moisturelevel); //V2 is for moisturelevel 
 }
 
 void setup()  
 {  
  Serial.begin(9600);  
  Blynk.begin(auth, ssid, pass);  
  dht.begin();  
    // Setup a function to be called every second
  //The Blynk timer object sends temperature and humidity readings every two seconds 
  // soil moisture levels every five seconds. That data will update in the gauges of the Blynk App.
  timer.setInterval(1000L, sendSensor); 
   timer.setInterval(2000L, sendSensor2);  
  
 }  
 

 void loop() 
 {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();  
 
 }
