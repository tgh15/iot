/**
 * Created by K. Suwatchai (Mobizt)
 *
 * Email: k_suwatchai@hotmail.com
 *
 * Github: https://github.com/mobizt/Firebase-ESP8266
 *
 * Copyright (c) 2023 mobizt
 *
 */

/** This example will show how to access the RTDB in Test Mode (no authentication).
 */

#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#elif defined(PICO_RP2040)
#include <WiFi.h>
#include <FirebaseESP8266.h>
#endif

//library sensor arus
#include "ACS712.h"

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "ASUS_X00TD"
#define WIFI_PASSWORD "12345678a"

//server firebase
/* 2. Define the RTDB URL */
#define DATABASE_URL "iot-project-fcc11-default-rtdb.firebaseio.com" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 3. Define the Firebase Data object */
FirebaseData fbdo;

/* 4, Define the FirebaseAuth data for authentication data */
FirebaseAuth auth;

/* Define the FirebaseConfig data for config data */
FirebaseConfig config;

//inisialisasi sensor arus
ACS712 sensor(ACS712_30A, A0);

void setup()
{
    
    Serial.begin(115200);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
//    relay
    pinMode(2, OUTPUT); 
    
    /* Assign the certificate file (optional) */
    // config.cert.file = "/cert.cer";
    // config.cert.file_storage = StorageType::FLASH;

    /* Assign the database URL(required) */
    config.database_url = DATABASE_URL;

    config.signer.test_mode = true;

    Firebase.reconnectWiFi(true);

    /* Initialize the library with the Firebase authen and config */
    Firebase.begin(&config, &auth);

//    kalibrasi sensor
     Serial.println("Calibrating... Ensure that no current flows through the sensor at this moment");
     sensor.calibrate();
     Serial.println("Done!");
    
}

void loop()
{
   if (Firebase.getInt(fbdo, "/LED_STATUS")) {

      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
      Serial.println(fbdo.to<int>());
      
      if(fbdo.to<int>() == 1){
        
        digitalWrite(2, HIGH);
        
        float U = 230; //tegangan
        float I = sensor.getCurrentAC();
        float P = U * I;
        Serial.println(String("I = ") + I + " A");
        Serial.println(String("P = ") + P + " Watts");
        Serial.printf("Set int... %s\n", Firebase.setFloat(fbdo, "/sensor/arus", I) ? "ok" : fbdo.errorReason().c_str());
        Serial.printf("Set int... %s\n", Firebase.setFloat(fbdo, "/sensor/daya", P) ? "ok" : fbdo.errorReason().c_str());
        Serial.println("OK");
      }else{
        digitalWrite(2, LOW);
        Serial.printf("Set int... %s\n", Firebase.setFloat(fbdo, "/sensor/arus", 0.0) ? "ok" : fbdo.errorReason().c_str());
        Serial.printf("Set int... %s\n", Firebase.setFloat(fbdo, "/sensor/daya", 0.0) ? "ok" : fbdo.errorReason().c_str());
        Serial.println("NOT OK");
      }
      
    }

  } else {
    Serial.println(fbdo.errorReason());
  }
  delay(1000);
}
