//include <dht.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"
#define DHTPIN 8    // dht22 pin
#define DHTTYPE DHT22   // DHT 22  (AM2302)s
int ldrPin = 28;// ldr pin
void co(int);

/*declaration of variables for co*/
double ppm1;
int CO_sensor = A1; //Sensor pin 
float m1 = -0.6527; //Slope 
float b1 = 1.30; //Y-Intercept 
float R01 = 7.22; //Sensor Resistance

/*End of declaration of variable of co2 */
#define ONE_WIRE_BUS1 10
//#define dht_apin 2 // digital Pin sensor is connected to

OneWire oneWire1(ONE_WIRE_BUS1);
DallasTemperature sensors1(&oneWire1);

//dht DHT;

int timer = 0;
int remote_interval = 30;
float h=0, t=0, ozone;
int sensorValueso = 0, voltage, sensorValuelu = 0, sensorValueoz = 0, sensorValuepo = 0, sensorValuern = 0, sensorValueBat = 0;
int dB=0, lux, pollu, rain;
int sensorValuemax = 0, Pgauge, Patm = 15.2, Pabs, count = 0, sample = 0, sample1 = 0, sample3 = 0, pressure_mbar, sensorValuemin = 0, x;
String str = "";
String str1 = "";
String ldr_value="0";
String dust_value="0";
String new_sensor[]={"DARK","BRIGHT","CLEAN","GOOD","ACCEPTABLE","HEAVY","HAZARD"};


int v;
int o;
int c = 0;
long int stringOne22 = 0;
int count1 = 0;                                          // count = 0
int counttx = 0;
//char input[12];                                         // character array of size 12
boolean flag = 0;// flag =0
boolean ledstatusflag=0;
int rfid;
String input = "";
String msg = "";
float temp1, cum_sample = 0.0, avg = 0.0, milivoltage = 0.0, percentage = 0.0, Batvoltage = 0.0; //,ActVolt =0.0
int ActVolt = 0;
String intData = "";
byte intBuffer[12];

const byte ledPin = 13;
const byte interruptPin = 18;
const byte interruptPin2 = 19;
const byte interruptPin3 = 20;
const byte interruptPin4 = 21;

volatile byte state = LOW;
int BuzzPin = 12;
int intSOS = 0;
int IntTmr = 0;
int inPin1 = 7;   ///
int val1 = 0;
int val2 = 0;
int inPON = 0, IGNON = 0;
int inPOF = 0, IGNOFF = 0;
int DeviceON = 0, DeviceOF = 0;
int countv = 0;
////////////////////////  Ardunio Code Version  ///////////////////////////////////////////
String ArdCodeVersion = String("ARDV7.2\r\n");

//Variables if NUC does'nt respond
int NewIGNOff = 0;
int NewIgnioffCntr = 0;
int TurnOffTime = 420;
//

int IntTmrOFF = 0;
int inNUCOFF = 0;
int ACKIGNOFF = 0;
String NUCcmd;
String DevON = String("#DEVICEON#");
String DevOFF = String("#DEVICEOFF#");
String NUCON = String("#NUCPOWERON#");
String ACKOFF = String("#ACKIGNOFF#");
String KeepON = String("#KEEPON#");
String ledON = String("#SWITCHON#");
String ledOFF = String("#SWITCHOFF#");
String AckKeepON = String("$ACKKEEPON#");
String CVcommand = String("#CODEVERSION#");

//int Relay = 11;
int RelayTV = 9;
int RelayNUC = 8;
int RelayLED = 4;
//
int pin2 = 6; // dust
int pin1 = 5;// dust sensor
unsigned long duration1;
unsigned long duration2;

unsigned long starttime;
unsigned long sampletime_ms = 3000;                              //sampe 1s ;
unsigned long lowpulseoccupancy1 = 0;
unsigned long lowpulseoccupancy2 = 0;
float ratio1 = 0;
float ratio2 = 0;
float concentration1 = 0;
float concentration2 = 0;
//
DHT dht(DHTPIN, DHTTYPE);
int ldrStatus;
//
void setup()
{
  pinMode(CO_sensor,INPUT);
  
  pinMode(ledPin, OUTPUT);
  pinMode(inPin1, INPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(interruptPin2, INPUT_PULLUP);
  pinMode(interruptPin3, INPUT_PULLUP);
  pinMode(interruptPin4, INPUT_PULLUP);

  pinMode(BuzzPin, OUTPUT);      // sets the digital pin as output
  digitalWrite(BuzzPin, LOW);    // sets the LED off

  pinMode(RelayLED, OUTPUT);     //Set Pin11 as output
  digitalWrite(RelayLED, LOW);   //Turn ON relay(24082017)

  pinMode(RelayTV, OUTPUT);     //Set Pin09 as output
  digitalWrite(RelayTV, LOW);   //Turn off relay

  pinMode(RelayNUC, OUTPUT);     //Set Pin08 as output
  digitalWrite(RelayNUC, LOW);   //Turn off relayNUC

  attachInterrupt(digitalPinToInterrupt(interruptPin), AMB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), FIR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin3), PLC, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin4), Panic, CHANGE);

  Serial.begin(9600);
  Serial2.begin(9600);
  //sensors1.begin();
  dht.begin();////////////////////////////////////////////////////////RB
  pinMode(ldrPin, INPUT);
  pinMode(pin1,INPUT);
  pinMode(pin2,INPUT);
  starttime = millis();                //get the current time;
}

void loop()
{
  ///////////////////
  String stringOne = "";
  // long int stringOne22 = 6152637;
  char *retstr;
  long int decimalNumber = 0, remainder, quotient = 0;
  int i = 0, j = 0, k = 0, l = 0, m = 0, temp = 0;
  int a1 = 0, b2 = 0, c3 = 0;
  int StrLen1 = 0;
  char tempbuff[20] = {'\0'};
  String testbuff = "";
  String dummyhexNum = "";
  String catstring = "";
  ////////////////////////
  //###############################################LDR Sensor #######################################
  int ldrStatus = digitalRead(ldrPin);
if (ldrStatus == 1)
{
  ldr_value=new_sensor[0];
} 
if (ldrStatus == 0)
{
  ldr_value=new_sensor[1];
  //Serial.println(ldr_value); 
}
//#################################################Dust Sensor#######################################

  duration1 = pulseIn(pin1, LOW);
  duration2 = pulseIn(pin2, LOW);
  lowpulseoccupancy1 = lowpulseoccupancy1+duration1;
  lowpulseoccupancy2 = lowpulseoccupancy2+duration2;


  if ((millis()-starttime) > sampletime_ms)                                                      //if the sampel time == 30s
  {
    ratio1 = lowpulseoccupancy1/(sampletime_ms*10.0);                                               // Integer percentage 0=>100
    concentration1 = 1.1*pow(ratio1,3)-3.8*pow(ratio1,2)+520*ratio1+0.62;                        // using spec sheet curve

    ratio2 = lowpulseoccupancy2/(sampletime_ms*10.0);                                   // Integer percentage 0=>100
    concentration2 = 1.1*pow(ratio2,3)-3.8*pow(ratio2,2)+520*ratio2+0.62;                  // 

    
       
    //Serial.print("concentration1 = ");
    //Serial.print(concentration1);
    //Serial.print(" pcs/0.01cf  -  ");

    //Serial.print("concentration2 = ");
    //Serial.print(concentration2);
    //Serial.print(" pcs/0.01cf  -  ");

    
    if (concentration1 > 1 && concentration1 < 1000) 
{
     dust_value=new_sensor[2];
}
    else if (concentration1 > 1000 && concentration1 < 10000) 
{
     dust_value=new_sensor[3];
}
    
    else if (concentration1 > 10000 && concentration1 < 20000) 
{
     dust_value=new_sensor[4];
}
      else if (concentration1 > 20000 && concentration1 < 50000) 
{
     dust_value=new_sensor[5];
}

    else if (concentration1 > 50000 ) 
{
     dust_value=new_sensor[6];
} 
      
    lowpulseoccupancy1 = 0;
    lowpulseoccupancy2 = 0;
    starttime = millis();
}
//Serial.print(dust_value);

  //################################################Temperature sensor###############################

  sensors1.requestTemperatures();
 temp1 = (sensors1.getTempCByIndex(0));

  //###################################### If NUC does't respond ######################################

  if (NewIGNOff == 1)
  {
    ///   Serial.print(NewIgnioffCntr);
    //   Serial.print("\r\n");
    if (NewIgnioffCntr == TurnOffTime)
    {
      //    Serial.print("#DEVCIEOFF# not receied Shutting down....");
      digitalWrite(RelayNUC, LOW); // sets the NUC OFF
      digitalWrite(RelayTV, LOW); // sets the TV OFF
      NewIgnioffCntr = 0;
      NewIGNOff = 0;
    }
    else
    {
      NewIgnioffCntr++;
    }
  }

  //#####################################Panic timer##############################################
  if (IntTmr >= 2)
  {
    IntTmr = 0;
    intSOS = 0;
    digitalWrite(BuzzPin, LOW);    // sets the LED off
  }

  IntTmr++;
  if ((inPOF == 1) && (inNUCOFF == 1))
  {
    // Serial.print("Shuting Down");
    // Serial.print(IntTmrOFF);

    if (IntTmrOFF == 180)
    {
      digitalWrite(RelayNUC, LOW); // sets the NUC OFF
      digitalWrite(RelayTV, LOW); // sets the TV OFF
      IntTmrOFF = 181;
    }
    if (IntTmrOFF < 181)
    {
      IntTmrOFF++;
    }
  }
  //######################################################################################################

  while ((Serial2.available()) > 0)
  {

    // Serial.print("\n Integer Value erftgg:");
    stringOne22 = Serial2.parseInt();

    if (stringOne22 > 0)
    {
      //    Serial.print("\n stringOne22 > 0");
      //  Serial.print("\n Integer Value erftgg:");
      //   Serial.println(stringOne22);

      stringOne =  String(stringOne22, HEX);
      stringOne.toUpperCase();
      //  Serial.println(stringOne);

      for (j = 0; stringOne[j] != '\0'; j++)
      {
        for (k = 2; ((k > 0) && ((j % 2) == 0)); k--)
        {
          tempbuff[k - 1] = stringOne[m];
          m++;
          tempbuff[k - 2] = stringOne[m];
          m++;
          tempbuff[2] = '\0';
          dummyhexNum = dummyhexNum + tempbuff;
          dummyhexNum[m + 1] = '\0';
          k = 0;
        }
        k = 2;
      }

      int StrLen2331 = dummyhexNum.length();
      // Serial.println("\n\n Print String dummyhexNum:");
      //  Serial.println(dummyhexNum);
      //  Serial.println(StrLen2331);
      k = StrLen2331;
      testbuff = "";
      tempbuff[0] = '\0';

      /// reverse a string
      for (j = 0; j <= StrLen2331; j++)
      {
        tempbuff[j] = dummyhexNum[k - 1];
        k--;
      }
      //  Serial.println("\n\n RFID String:");
      //   Serial.println(tempbuff);

      catstring += "#RF$";
      catstring += tempbuff;
      catstring += "#\0";
      /*catstring += ldr_value;
      catstring += ", ";
      catstring += dust_value;
      catstring += ", ";
      catstring += h;
      catstring += " % ";
      catstring += t;
      catstring += "℃";*/ 
      Serial.println(catstring);
      catstring = "";
    }
  }


  while (Serial.available())
  {
    NUCcmd = Serial.readString(); // read the incoming data as string
    Serial.println(NUCcmd);

    if (NUCcmd.equals(DevON))
    {
      //digitalWrite(Relay, LOW);    //Turn on relay  Relay
      digitalWrite(RelayTV, HIGH);    //Turn on relay  RelayTV
      digitalWrite(RelayNUC, HIGH); // sets the NUC ON
    }

    else if (NUCcmd.equals(CVcommand))
    {
      Serial.print(ArdCodeVersion); 
      //Serial.print("\r\n");
    }

    else if (NUCcmd.equals(ledON))
    {
      digitalWrite(RelayLED, LOW); // sets the LED ON
      Serial.print("$ACKSWITCHON#");
      Serial.print("\r\n");
      ledstatusflag=1;
    }

    else if (NUCcmd.equals(ledOFF))
    {
      digitalWrite(RelayLED, HIGH); // sets the LED OFF
      Serial.print("$ACKSWITCHOFF#");
      Serial.print("\r\n");
      ledstatusflag=0;
    }

    else if (NUCcmd.equals(KeepON))   //Keep ssytem of for speed > 3 condition.
    {
      NewIgnioffCntr = 0;
      NewIGNOff = 0;
      Serial.print("$ACKKEEPON#");
      Serial.print("\r\n");
    }

    else if (NUCcmd.equals(DevOFF))
    {
      IntTmrOFF = 0;
      NewIGNOff = 0;
      NewIgnioffCntr = 0;
      //  digitalWrite(Relay, HIGH);
      // digitalWrite(RelayTV, HIGH);
      Serial.print("$RelayOFF#");
      Serial.print("\r\n");

      inNUCOFF = 1;
    }

    else if (NUCcmd.equals(NUCON))
    {
      Serial.print("$NUCON#");
      Serial.print("\r\n");
      if (val1 == HIGH)
      {
        Serial.print("$IGNON#");
        inNUCOFF = 0;
      }
    }
    else if (NUCcmd.equals(ACKOFF))
    {
      ACKIGNOFF = 1;
    }
  }

  //################################################Remote parameter######################################
  /*  if (Serial.available())
    {
    str = Serial.readString();
    if (str != NULL)
    {
    //Serial.println(str);
    str1 = str;

    v = str.indexOf('M');
    //Serial.println(v);

    if (v > 0)
    {
    str.remove(v);
    //Serial.println(str);
    o = v + 1;
    str1.remove(0, o);
    //Serial.println(str1);
    c = str1.toInt();
    //Serial.println(c);
    if (c > 0)
    {
    remote_interval = c;
    timer = 0;
    }
    }
    }
    }*/
  //##########################################################################################################

  //################################################ RFID ####################################################
  /*
    if (Serial1.available())
    {

    count1 = 0;

    char c;
    int ijk = 0;
    long int stringOne22;
    String DummyMsg = "";

    while ((Serial1.available() > 0))
    {

    c = Serial1.read();
    msg += c;
    // msg[ijk] = c;
    //  ijk++;
    }

    // Copy read data into a char array for use by atoi
    // Include room for the null terminator
    int intLength = msg.length() + 1;
    msg.toCharArray(intBuffer, intLength);

    // Reinitialize intData for use next time around the loop
    msg = "";

    // Convert ASCII-encoded integer to an int
    int i = atoi(intBuffer);
    Serial.print("\n Integer Value:");
    Serial.println(i);
    //    msg = msg + '\0';

    //    Serial.print("MSG Value:");
    //    Serial.println(msg);

    //    Serial.print("\n Integer Value:");
    //    stringOne22 = msg.toInt();
    //    Serial.println(stringOne22);

    //    Serial.print("\n Integer Value:");
    //   stringOne22 = input.toInt();
    //   Serial.println(stringOne22);
    }
  */
  //################################################Rakshak + 3 panic key#######################################

  val1 = digitalRead(inPin1);  // read input value
  /* val2 = digitalRead(inPin2);  // read input value
    val3 = digitalRead(inPin3);  // read input value
    val4 = digitalRead(inPin4);  // read input value
    val5 = digitalRead(inPin5);  // read input value
    val6 = digitalRead(inPin6);  // read input value*/


  if (val1 == HIGH)
  {
    if (inPON == 0 && DeviceON == 30)
    {
      Serial.print("$IGNON#");
      Serial.print("\r\n");
      if (inNUCOFF == 1)
      {
        digitalWrite(RelayNUC, LOW); //
        delay(3000);
      }
      digitalWrite(RelayNUC, HIGH); // sets the NUC ON
      digitalWrite(RelayTV, HIGH); // sets the TV ON
      inPON = 1;
      IGNON = 1;
      IGNOFF = 0;
      DeviceON++;
      ACKIGNOFF = 0;
    }

    //   Serial.print("IGN is ON");
    //    Serial.print(DeviceON);
    //   Serial.print("\r\n");
    if (inPON == 0)
    {
      DeviceON++;
    }
    DeviceOF = 0;
    inPOF = 0;
  }

  else if (val1 == LOW)
  {
    /*  if (inPOF == 1 && ACKIGNOFF == 0)
      {
      Serial.print("$IGNOFF#");
      Serial.print("\r\n");
      ACKIGNOFF = 1;
      }*/
    if (inPOF == 0 && DeviceOF == 30)
    {
      Serial.print("$IGNOFF#");
      Serial.print("\r\n");
      NewIGNOff = 1;
      inPOF = 1;
      DeviceOF++;
      IGNOFF = 1;
      IGNON = 0;

    }

    //   Serial.print("IGN is OFF");
    //   Serial.print(DeviceOF);
    //   Serial.print("\r\n");
    if (inPOF == 0)
    {
      DeviceOF++;
    }

    DeviceON = 0;
    inPON = 0;
  }
  /*
    else if (val3 == HIGH)
    {
    Serial.print("$PL#");
    Serial.print("\r\n");
    goto last;
    }

    if (val4 == HIGH)
    {
    Serial.print("$PN1#");
    Serial.print("\r\n");
    goto last;
    }

    if (val5 == HIGH)
    {
    Serial.print("$PN2#");
    Serial.print("\r\n");
    goto last;
    }

    if (val6 == HIGH)
    {
    Serial.print("$PN3#");
    Serial.print("\r\n");
    goto last;
    }
  */
  //#########################################################################################################


  //################################################Humidity & Temp#########################################
  /*if (isnan(h) || isnan(t))
  {
  Serial.println("HUxx,TMxx,");
  delay (1000);
  return;
  }*/
  //DHT.read11(dht_apin);
  //h = DHT.humidity;
  //t = DHT.temperature;

  h = dht.readHumidity();
  //t = dht.readTemperature();
    /*Serial.print(h);
    Serial.print("%");
    Serial.print(",");
    Serial.print(t);
    Serial.print("C");*/


  //##########################################################################################################
  //################################################Sound sensor##############################################
  sensorValueso = analogRead(A0);
  voltage = sensorValueso * ( 5.0 / 1024.0 );
  //int miliv = voltage * 1000;
  //dB=miliv;
  //Serial.println(voltage);

  dB = 20 * (log10 (voltage / 0.001));
  dB = dB + 20;
  //Serial.print(dB);

  //###########################################################################################################

  //################################################Battery level ##############################################
  /*if ((counttx == 25) || (flag == 0))
  {
    Serial.print("BL");
    Serial.print(ActVolt);
    Serial.print(",");
    Serial.print(percentage);
    //Serial.print("milivoltage = ");
    Serial.print(",");

    Serial.print("\r\n");
    counttx = 0;
    flag = 1;

  }*/
  sampling1();

  ActVolt = ((avg / 5.0) * 13.6);
  percentage = ((avg / 1000) * (100 / 5.0));
  cum_sample = 0;
  delay(5);




  //################################################################################################################

  //################################################solar radiation sensor#########################################
  sensorValuelu = analogRead(A8);
  //Serial.println(sensorValuelu);
  if (sensorValuelu > 0 && sensorValuelu <= 100)
  {
    lux = 10;
  }

  else if (sensorValuelu > 100 && sensorValuelu <= 200)
  {
    lux = 9;
  }

  else if (sensorValuelu > 200 && sensorValuelu <= 300)
  {
    lux = 8;
  }
  else if (sensorValuelu > 300 && sensorValuelu <= 400)
  {
    lux = 7;
  }
  else if (sensorValuelu > 400 && sensorValuelu <= 500)
  {
    lux = 6;
  }
  else if (sensorValuelu > 500 && sensorValuelu <= 600)
  {
    lux = 5;
  }
  else if (sensorValuelu > 600 && sensorValuelu <= 700)
  {
    lux = 4;
  }
  else if (sensorValuelu > 700 && sensorValuelu <= 800)
  {
    lux = 3;
  }
  else if (sensorValuelu > 800 && sensorValuelu <= 900)
  {
    lux = 2;
  }
  else if (sensorValuelu > 900 && sensorValuelu <= 1000)
  {
    lux = 1;
  }




  //#############################################################################################################

  //################################################ozone sensor################################################
  sensorValueoz = analogRead(A3);
  //Serial.println(sensorValueoz);

  if (sensorValueoz >= 0 && sensorValueoz < 700)
  {
    ozone = 0.07;
  }
  else if (sensorValueoz >= 700 && sensorValueoz < 800  )
  {
    ozone = 0.08;
  }

  //#############################################################################################################

  //################################################pollution smoke sensor#######################################
  sensorValuepo = analogRead(A7);
  //Serial.println(sensorValuepo);
  pollu = (sensorValuepo * 100) / 1024;
  pollu = abs(pollu);


  //#############################################################################################################

  //################################################rain sensor##################################################
  sensorValuern = analogRead(A5);
  // Serial.println(sensorValuern);
  if (sensorValuern > 900)
  {
    rain = 0;
  }
  else if (sensorValuern <= 900 && sensorValuern > 600)
  {
    rain = 1;
  }
  else if (sensorValuern <= 600 && sensorValuern > 300)
  {
    rain = 2;
  }
  else if (sensorValuern <= 300)
  {
    rain = 3;
  }


  //##################################################################################################################

  //#######################################################################pressure sensor############################
  // sensorValue = analogRead(analogInPin);
  // sensorValue1 = analogRead(analogInPin1);
  // Serial.print("Pressure+ = ");
  // Serial.println(sensorValue);
  // Serial.print("Pressure- = ");
  // Serial.println(sensorValue1);
  sampling();

  x = (sensorValuemax - sensorValuemin) + 5; // difference and offset.

  // Curve fitting by trial and error for the SPX3058D
  if (x > 0)
  {
    pressure_mbar = (x * 5) + (x * x / 13);
  }
  else
  {
    pressure_mbar = (x * 4) - (x * x / 24);
  }

  // sensorValue = analogRead(analogInPin);
  // Serial.print("sensor = ");
  // Serial.println(sensorValue);
  /* Pgauge = (sensorValue * 15)/1024;
    Pabs = Patm + Pgauge; //Pabs in PSI
    Pressure = Pabs * 68.9475728; // 1 PSI = 68.9475728 mbar*/

  for (int i = 0; i <= 300; i++)
  {
    sample3 = sample3 + pressure_mbar;
    count++;
    delay (1);
  }
  if (count >= 300)
  {
    count = 0;
    pressure_mbar = sample3 / 300;
  }

  pressure_mbar = abs(pressure_mbar);

  sample = 0;
  sample1 = 0;
  sample3 = 0;
  //#################################################################################################################
  if (timer == remote_interval)
  {
    uart();
    //  Serial.print("\r\n");
    timer = 0;
  }
  timer++;
last:

  delay(300);
  //timer++;
  // Serial.print(remote_interval); // traces for remote parameter
  // Serial.print(timer);           // traces for remote parameter

  //#################################################################################################################

  //##############################################CO Sensor##########################################################

  float sensor_volt1; //Define variable for sensor voltage 
  float RS_gas1; //Define variable for sensor resistance  
  float ratio1; //Define variable for ratio
  float sensorValue1 = analogRead(CO_sensor); //Read analog values of sensor  
  sensor_volt1 = sensorValue1*(5.0/1023.0); //Convert analog values to voltage 
  RS_gas1 = ((5.0*10.0)/sensor_volt1)-10.0; //Get value of RS in a gas
  ratio1 = RS_gas1/R01;  // Get ratio RS_gas/RS_air
  double ppm_log1 = (log10(ratio1)-b1)/m1; //Get ppm value in linear scale according to the the ratio value  
  ppm1 = pow(10, ppm_log1); //Convert ppm value to log scale 
  //Serial.print("CO PPM = ");
  //Serial.println(ppm1);
}
//#################################################################################################################

  //##############################################CO2 Sensor##########################################################
    float co2 = analogRead(A4);
    float ppm = map(co2,0,1023,400,10000);  
    //Serial.println(co2);
    //Serial.println("CO2 value: ");
    //Serial.print(ppm);

void Panic()
{
  if (intSOS == 0)
  {

    IntTmr = 0;
    intSOS++;
    Serial.print("$PN#");
    Serial.print("\r\n");
    digitalWrite(BuzzPin, HIGH);   // sets the LED on
  }
}

void INT_R()
{
  if (intSOS == 0)
  {

    IntTmr = 0;
    intSOS++;
    Serial.print("$IR#");
    Serial.print("\r\n");
    digitalWrite(BuzzPin, HIGH);   // sets the LED on
  }
}

void INT_F()
{
  if (intSOS == 0)
  {

    IntTmr = 0;
    intSOS++;
    Serial.print("$IF#");
    Serial.print("\r\n");
    digitalWrite(BuzzPin, HIGH);   // sets the LED on
  }
}

void AMB()
{
  if (intSOS == 0)
  {

    IntTmr = 0;
    intSOS++;
    Serial.print("$AB#");
    Serial.print("\r\n");
    digitalWrite(BuzzPin, HIGH);   // sets the LED on
  }
}

void PLC()
{
  if (intSOS == 0)
  {

    IntTmr = 0;
    intSOS++;
    Serial.print("$PL#");
    Serial.print("\r\n");
    digitalWrite(BuzzPin, HIGH);   // sets the LED on
  }
}

void FIR()
{
  if (intSOS == 0)
  {

    IntTmr = 0;
    intSOS++;
    Serial.print("$FR#");
    Serial.print("\r\n");
    digitalWrite(BuzzPin, HIGH);   // sets the LED on
  }
}
void uart()
{
  val2 = digitalRead(RelayLED);
  Serial.print("LDR");
  Serial.print(ldr_value);
  Serial.print(",");
  
  if (concentration1 > 1)
  {
    Serial.print("DU");   
    Serial.print(dust_value);
  }
  else{
     Serial.print("DU");
    Serial.print("xx");
  }
  Serial.print(",");
  if (isnan(h) || isnan(t))
  {
  Serial.print("HUxx");
  //delay (1000);
  }
  else{
  Serial.print("HU");
  Serial.print(h);
  }
  Serial.print(",");
  if(temp1==-127.00)
  {
    Serial.print("TM");
    Serial.print("xx");
    }
  else
  {Serial.print("TM");
  Serial.print(temp1);}
  
  Serial.print(",");
  
  Serial.print("-");
  Serial.print(",");
  
  Serial.print("DB");
  Serial.print(dB);
  Serial.print(",");
  Serial.print("CO");
  Serial.print(ppm1);
  Serial.print(",");
  Serial.print("CO2");
  Serial.print(ppm);
  Serial.print(",");
  Serial.print("BL");
  Serial.print(ActVolt);
  Serial.print(",");
  Serial.print(percentage);
  /*Serial.print(",");
  Serial.print("SR");
  Serial.print(lux);
  Serial.print(",");
  Serial.print("OZ");
  Serial.print(ozone);
  Serial.print(",");
  Serial.print("PU");
  Serial.print(pollu);
  Serial.print(",");
  Serial.print("RN");
  Serial.print(rain);
  Serial.print(",");
  Serial.print("PR");
  Serial.print(pressure_mbar);*/
  Serial.print(",");
  if (IGNON == 1)
  {
    Serial.print("IGON");
    Serial.print(",");
  }
  else if (IGNOFF == 1)
  {
    Serial.print("IGOF");
    Serial.print(",");
  }
  
  Serial.println();

}

void sampling ()
{
  for (int i = 0; i <= 205; i++)
  {
    sensorValuemax = analogRead(A11);
    sensorValuemin = analogRead(A12);

    sample = sample + sensorValuemax;
    sample1 = sample1 + sensorValuemin;

    count++;
    delay (1);
  }
  if (count >= 205)
  {
    count = 0;
    sensorValuemax = sample / 205;
    sensorValuemin = sample1 / 205;

  }
}


void sampling1 ()
{
  for (int i = 0; i <= 20; i++)
  {
    sensorValueBat = analogRead(A9);
    Batvoltage = sensorValueBat * (5.0 / 1024.0);
    milivoltage = Batvoltage * 1000;

    cum_sample = cum_sample + milivoltage;
    //   cum_sample = cum_sample + Batvoltage;
    countv++;
    delay (1);
  }
  if (countv >= 20)
  {
    countv = 0;
    avg = cum_sample / 20;

  }
  counttx++;
}
