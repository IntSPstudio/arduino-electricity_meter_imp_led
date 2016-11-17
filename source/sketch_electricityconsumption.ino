/*|==============================================================|
 * Made by IntSPstudio
 * Get data from electricity meter '1000 imp/kWh' led
 * Thank you for using this sketch!
 * Version: 0.0.0.20161117
 * ID: 820002001
 * Twitter: @IntSPstudio
 *|==============================================================|
 */
//LED VALUE
int sensorApPin =A0;
int sensorApValue =0;
int sensorApLedPin =8;
int sensorApCheckCounterHis =0;
int sensorApCheckCounter =0;
//CALIBRATION
int startSteps =2;
int sensorBpPin =A1;
int sensorBpValue =0;
//MAIN SETTINGS
unsigned long systemClock;
unsigned long systemCheckClock;
int systemCheckClockAlimit =400;
int currentElecCons =0;
int sensorOldValue =0;
int sensorMainValue =0;
//SETUP
void setup() {
  //SERIAL
  Serial.begin(9600);
  //CHECK LED
  pinMode(sensorApLedPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}
//MAIN LOOP
void loop() {
  //LED VALUE
  sensorApValue = analogRead(sensorApPin);
  //CALIBRATION
  sensorBpValue = analogRead(sensorBpPin);
  //MAIN VALUE
  sensorOldValue = sensorMainValue;
  sensorMainValue = sensorApValue - sensorBpValue;
  if (sensorMainValue < 1)
  {
    sensorMainValue =0;
  }
  //CHECK
  sensorApCheckCounterHis = sensorApCheckCounter;
  if (sensorMainValue > 0)
  {
    digitalWrite(sensorApLedPin, HIGH);
    sensorApCheckCounter +=1;
  }
  else
  {
    digitalWrite(sensorApLedPin, LOW);
    sensorApCheckCounter =0;
  }
  //MAIN
  if ((sensorApCheckCounter == 0 ) && (sensorApCheckCounterHis > 0))
  {
    //CLOCK
    systemCheckClock = millis() - systemClock;
    systemClock = millis();
    if (systemCheckClock > systemCheckClockAlimit)
    {
      if (startSteps < 1)
      {
        //MATH (Wh)
        currentElecCons = 3.6 / (systemCheckClock / 1000) * 1000;
        //LED SIM
        digitalWrite(LED_BUILTIN, HIGH);
        //PRINT
        Serial.print(systemCheckClock);
        Serial.print(" ms");
        Serial.print(", ");
        Serial.print(currentElecCons);
        Serial.println(" Wh");
      }
      else
      {
        startSteps -=1;
      }
    }
    else
    {
       //LED SIM
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
  else
  {
     //LED SIM
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(10);
}

