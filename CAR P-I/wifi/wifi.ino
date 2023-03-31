// #include <Adafruit_ESP8266.h>

#include <SoftwareSerial.h>

SoftwareSerial esp8266(12, 13);
// Adafruit_ESP8266 wifi(&esp8266, &Serial, 4);

void setup()
{
    esp8266.begin(115200);

    Serial.begin(115200);
    while (!Serial)
        ;

    Serial.println("Started");

    // esp8266.print("AT+CWLAP\r\n");
    // esp8266.print("AT+CWJAP=\"alqatrasqa\", \"desforget\"\r\n");
}

void loop()
{
    if (esp8266.available())
    {
        Serial.write(esp8266.read());
    }

    if (Serial.available())
    {
        esp8266.write(Serial.read());
    }
}
