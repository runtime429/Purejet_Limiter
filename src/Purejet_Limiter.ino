#include <EEPROM.h>
#include <RCSwitch.h>

const int TPSo1 = 10;    // OUTPUT TO TPS
const int TPSo2 = 9;   // OUTPUT TO TPS

const byte TPSi1 = A0;  // INPUT OF TPS
const byte TPSi2 = A1;  // INPUT OF TPS

const int receivePin = 1;     // Remote receive interrupt Pin
const int valRcSig = 4433;    // Value of rc remote signal for receive

bool rcSwitch = false;        // State of rc Switch
int valrc = 0;                // Value of remote signal if no Signal received

const int teachPin = 2;       // Teach button
const int ledPin = 13;        // Toggle LED teach-mode

const int revPin = 4;         // rev_limit_switch
bool revPinState;             // state of rev_limit_switch
int ledState = LOW;           // current state of the output pin
int buttonState;              // current reading from the input pin
int lastButtonState = LOW;    // previous reading from the input pin
int lastDebounceTime = 0;     // last time the output pin was toggled
int debounceDelay = 50;       // debounce time

int adc0, adc1;           // variables to read input of TPS
int adcsetup0, adcsetup1; // variables to read input of TPS on Setup

int maxadc0 = 0;        // lowest value in teach mode

int revlv1; // variables of Voltage limiter to ECU
float limitfactor;      // Limit factor to output

RCSwitch mySwitch = RCSwitch();

void setup() {
  
  TCCR1B = TCCR1B & B11111000 | B00000001;    // set timer 1 divisor to 1 for PWM frequency of 31372.55 Hz for D9 & D10

  adcsetup0 = analogRead(TPSi1);    // read value of TPS1 0,5V
  adcsetup1 = analogRead(TPSi2);    // read value of TPS2 4,5V
  analogWrite(TPSo1, adcsetup0 / 4);     // set TPS1 value to ECU output voltage
  analogWrite(TPSo2, adcsetup1 / 4);     // set TPS2 value to ECU output voltage

  pinMode(teachPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(revPin, INPUT_PULLUP);

  
  Serial.begin(115200);
  revlv1 = read_int(0);     // read value of TPS1 limit from EEPROM


  mySwitch.enableReceive(receivePin); // Receiver on interrupt 0 => that is pin #2


  limitfactor = (100.00 / map(revlv1, adcsetup0, adcsetup1, 0, 100) + 2);

  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW

  while (adcsetup0 > adcsetup1) {   // TPS Signal is twisted
  blinkLED(100, 100);     // LED blinks on for 100 milliseconds, then off for 100 milliseconds
  blinkLED(500, 500);     // LED blinks on for 500 milliseconds, then off for 500 milliseconds
}

}

void loop() {

  revPinState = digitalRead(revPin); // if no RC_connected

  teach_tps_toggle();
  
  if (ledState == HIGH) {
    if (maxadc0 < adc0) maxadc0 = adc0;
  }
  
  if (valrc != valRcSig) {
    received_remote();
  }

  adc0 = analogRead(TPSi1);     // read value of TPS1
  adc1 = analogRead(TPSi2);     // read value of TPS2
  
  if (valrc == valRcSig || revPinState == LOW) {
    analogWrite(TPSo1, adc0 / 4);     // set TPS1 value to ECU output voltage
    analogWrite(TPSo2, adc1 / 4);     // set TPS2 value to ECU output voltage
  } else {
    analogWrite(TPSo1, ((adc0 - adcsetup0) / limitfactor + adcsetup0) / 4);
    analogWrite(TPSo2, (adcsetup1 - (adcsetup1 - adc1) / limitfactor) / 4);
  }
 
}

void received_remote() {
  if (mySwitch.available()) {
    valrc = mySwitch.getReceivedValue();
    Serial.print("Received ");
    Serial.print(valrc);
    Serial.print(" / ");
    Serial.print(mySwitch.getReceivedBitlength());
    Serial.print("bit ");
    Serial.print("Protocol: ");
    Serial.println(mySwitch.getReceivedProtocol());
    mySwitch.resetAvailable();
  }
}

void write_int(int address, int value) {
  byte byte_2 = (value & 0xFF);
  byte byte_1 = ((value >> 8) & 0xFF);
  EEPROM.update(address, byte_2);
  EEPROM.update(address + 1, byte_1);
  Serial.print("Write to EEPROM (Address: ");
  Serial.print(address);
  Serial.print(",");
  Serial.println(value);
}

int read_int(int address) {
  long byte_2 = EEPROM.read(address);
  long byte_1 = EEPROM.read(address + 1);
  int val = ((byte_2 << 0) & 0xFFFFFF) + ((byte_1 << 8) & 0xFFFFFFFF);
  Serial.print("Read from EEPROM (Address: ");
  Serial.print(address);
  Serial.print(",");
  Serial.println(val);
  return val;
}

void blinkLED(int onTime, int offTime) {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(onTime);                     // wait for a certain time
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(offTime);                    // wait for a certain time
}

void teach_tps_toggle() {
  int reading = digitalRead(teachPin);    // read the state of the switch into a local variable
  
  if (reading != lastButtonState) {     // check if the switch state has changed
    lastDebounceTime = millis();        // reset the debounce timer
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {    // check if debounce delay has passed
    if (reading != buttonState) {       // check if button state has changed
      buttonState = reading;
      
      if (buttonState == HIGH) {        // toggle LED if the new button state is HIGH
        ledState = !ledState;
        Serial.println(ledState);
        
        if (ledState == HIGH) {
          Serial.println("Teaching TRUE");
        } else {
          write_int(0, maxadc0);
          maxadc0 = 0;            // reset to lowest value in teach mode for next teach
          Serial.println("Teaching End");
          revlv1 = read_int(0);     // read value of TPS1 limit
          Serial.println("Set new values from EEPROM to var");
          limitfactor = (100.00 / map(revlv1, adcsetup0, adcsetup1, 0, 100) + 2);
          Serial.print("Set limitfactor:");
          Serial.println(limitfactor);
        }
      }
    }
  }
  
  digitalWrite(ledPin, ledState); // set the LED according to the ledState value
  lastButtonState = reading;      // save the reading. Next time through the loop, it'll be the lastButtonState

}
