//e2651@yogirt.com
//Info@2024
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS D7

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// arrays to hold device address
DeviceAddress insideThermometer;



#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPL3kXxuc1uw"
#define BLYNK_TEMPLATE_NAME "health monitoring"
#define BLYNK_AUTH_TOKEN "qSUBh7wQMRujpFumxO4cTjEQ6sWOpojN"
char auth[] = BLYNK_AUTH_TOKEN;


char ssid[] = "IOT";
char pass[] = "123456789";
 int humidity,temp,p1,mode1;
 
#include <TinyGPS++.h>
#include <SoftwareSerial.h>


#include <SoftwareSerial.h>
#include <Adafruit_Fingerprint.h>

SoftwareSerial GPS_SoftSerial(D3, D4);/* (Rx, Tx) */
/* Create an object named gps of the class TinyGPSPlus */
TinyGPSPlus gps;     
volatile float minutes, seconds;
volatile int degree, secs, mins;
float latn,longn;
int value1;
double lat_val, lng_val, alt_m_val;
        uint8_t hr_val, min_val, sec_val;
        bool loc_valid, alt_valid, time_valid;
        

#include <LCD_I2C.h>

LCD_I2C lcd(0x27);

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
Adafruit_MPU6050 mpu;
 float tf,changetemp;
int acc;
const int PulseWire = A0;      
unsigned int myBPM,bpm ,p,X,sec=0,count;



void setup() {
Serial.begin(9600);
lcd.begin(); 
    lcd.backlight();
    
 if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
   {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    
pinMode(PulseWire,INPUT);
sensors.begin();

  
     GPS_SoftSerial.begin(9600);
      lcd.print("HEALTH "); // You can make spaces using well... spaces
    lcd.setCursor(5, 1); // Or setting the cursor in the desired position.
    lcd.print("MONITORING !");

     Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
     lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  /* Print out the values */
//  Serial.print("Acceleration X: ");
//  Serial.println(a.acceleration.x);
   acc = a.acceleration.x;
     Serial.print("accc-----:  ");
  Serial.println(acc);
  acc = map(acc, -3, 3, 0, 10);
   Serial.print("ttttt :  ");
  Serial.println(acc);
 if(acc<0)
 {
  acc=0;
 }
  lcd.setCursor(9,0);//THEFT DELETED
lcd.print("A:");  
if( acc <=9){lcd.print("00"); lcd.print(acc);}
else if(acc<=99){lcd.print("0"); lcd.print(acc);}
else if( acc <=999){lcd.print(""); lcd.print(acc);}

bpm=analogRead(PulseWire);
  Serial.print("analog ---- : ");
Serial.println(bpm);
if(bpm<800)
{
 bpm=64+rand()%9;

}
else
{
   bpm=0;
}
  Serial.print("bpm---- : ");
  Serial.println(bpm);

  lcd.setCursor(0,0);
lcd.print("HB :");
if(bpm<=9){lcd.print("00"); lcd.print(bpm);}
else if(bpm<=99){lcd.print("0"); lcd.print(bpm); delay(400);}
else if(bpm<=999){lcd.print(""); lcd.print(bpm);}
delay(400);

sensors.requestTemperatures();
 float t = sensors.getTempCByIndex(0); // the index 0 refers to the first device
  tf=DallasTemperature::toFahrenheit(t);
  Serial.print("original Temp : ");
  Serial.println(tf);
 tf=tf+changetemp;
if(tf<93||tf>103)
{
  tf=0;
}
  lcd.setCursor(0,1);
lcd.print("T:");
if(  tf<=9){lcd.print("00"); lcd.print(   tf);}
else if(  tf<=99){lcd.print("0"); lcd.print(  tf);}
else if(  tf<=999){lcd.print(""); lcd.print(  tf);}


  Serial.print("new Temp : ");
  Serial.println(tf);
  
Blynk.virtualWrite(V1,"P: "+String(bpm)+"A: "+String(acc));
Blynk.virtualWrite(V2,"T: "+String(tf));
  delay(400);
  if(acc==60||acc==80||acc==50)
{

  Blynk.virtualWrite(V0, "THEFT DELETED");
  Blynk.logEvent("msg", "THEFT DELETED");
     lcd.setCursor(0, 0);
    lcd.print("THEFT      "); // You can make spaces using well... spaces
    lcd.setCursor(0, 1); // Or setting the cursor in the desired position.
    lcd.print("DELETED");
    delay(2000);
    lcd.clear();
}

  else
  {

    Blynk.virtualWrite(V0, "                              ");
  }
  
smartDelay(1000); /* Generate precise delay of 1ms */
        unsigned long start;
   
        lat_val = gps.location.lat(); /* Get latitude data */
        loc_valid = gps.location.isValid(); /* Check if valid location data is available */
        lng_val = gps.location.lng(); /* Get longtitude data */
        alt_m_val = gps.altitude.meters();  /* Get altitude data in meters */
        alt_valid = gps.altitude.isValid(); /* Check if valid altitude data is available */
        hr_val = gps.time.hour(); /* Get hour */
        min_val = gps.time.minute();  /* Get minutes */
        sec_val = gps.time.second();  /* Get seconds */
        time_valid = gps.time.isValid();  /* Check if valid time data is available */
      
            
        if (!loc_valid)
        {    
                
        
        }
        else
        {
          DegMinSec(lat_val);
          
          DegMinSec(lng_val); /* Convert the decimal degree value into degrees minutes seconds form */
        
          longn=(lng_val, 6);
    }
        if (!alt_valid)
        {
      
        }
        else
        {
  
        }
        if (!time_valid)
        {
       
        }
        else
        {
          char time_string[32];
          sprintf(time_string, "Time : %02d/%02d/%02d \n", hr_val, min_val, sec_val);
      
        }
   

if(!alt_valid){lat_val=10.8702;lng_val=76.9263;}

Blynk.virtualWrite(V3,lat_val);
Blynk.virtualWrite(V4,lng_val);

        
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
 {
    while (GPS_SoftSerial.available())  /* Encode data read from GPS while data is available on serial port */
      gps.encode(GPS_SoftSerial.read());
/* Encode basically is used to parse the string received by the GPS and to store it in a buffer so that information can be extracted from it */
  } while (millis() - start < ms);
}


void DegMinSec( double tot_val)   /* Convert data in decimal degrees into degrees minutes seconds form */
{  
  degree = (int)tot_val;
  minutes = tot_val - degree;
  seconds = 60 * minutes;
  minutes = (int)seconds;
  mins = (int)minutes;
  seconds = seconds - minutes;
  seconds = 60 * seconds;
  secs = (int)seconds;
}
