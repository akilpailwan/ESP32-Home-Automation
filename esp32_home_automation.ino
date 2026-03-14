#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include <Wifi.h>

const char DEVICE_LOGIN_NAME[] = "9f244bd6-04d4-4caf-ac43-*******ac5d94b678a6";

const char SSID[] = "mewt";
const char PASS[] = "87654321";
const char DEVICE_KEY[] = "v1AAZn40a7NufX**********yj#K2tig9B1";

#define RelayPin1 23
#define RelayPin2 22
#define RelayPin3 21
#define RelayPin4 19

#define SwitchPin1 13
#define SwitchPin2 12
#define SwitchPin3 14
#define SwitchPin4 27

#define wifiLed 2

int toggleState_1 = 0;
int toggleState_2 = 0;
int toggleState_3 = 0;
int toggleState_4 = 0;

void onSwitch1Change();
void onSwitch2Change();
void onSwitch3Change();
void onSwitch4Change();

CloudSwitch switch1;
CloudSwitch switch2;
CloudSwitch switch3;
CloudSwitch switch4;

void initProperties(){
 ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
 ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);

 ArduinoCloud.addProperty(switch1, READWRITE, ON_CHANGE, onSwitch1Change);
 ArduinoCloud.addProperty(switch2, READWRITE, ON_CHANGE, onSwitch2Change);
 ArduinoCloud.addProperty(switch3, READWRITE, ON_CHANGE, onSwitch3Change);
 ArduinoCloud.addProperty(switch4, READWRITE, ON_CHANGE, onSwitch4Change);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

const int debounceDelay = 200;

unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime3 = 0;
unsigned long lastDebounceTime4 = 0;

bool previousSwitchState1 = HIGH;
bool previousSwitchState2 = HIGH;
bool previousSwitchState3 = HIGH;
bool previousSwitchState4 = HIGH;

void manual_control() {

  unsigned long currentMillis = millis();

  if (digitalRead(SwitchPin1) == LOW && previousSwitchState1 == HIGH) {
    if (currentMillis - lastDebounceTime1 >= debounceDelay) {
      toggleState_1 = !toggleState_1;
      digitalWrite(RelayPin1, !toggleState_1);
      switch1 = toggleState_1;
      lastDebounceTime1 = currentMillis;
    }
  }
  previousSwitchState1 = digitalRead(SwitchPin1);

  if (digitalRead(SwitchPin2) == LOW && previousSwitchState2 == HIGH) {
    if (currentMillis - lastDebounceTime2 >= debounceDelay) {
      toggleState_2 = !toggleState_2;
      digitalWrite(RelayPin2, !toggleState_2);
      switch2 = toggleState_2;
      lastDebounceTime2 = currentMillis;
    }
  }
  previousSwitchState2 = digitalRead(SwitchPin2);

  if (digitalRead(SwitchPin3) == LOW && previousSwitchState3 == HIGH) {
    if (currentMillis - lastDebounceTime3 >= debounceDelay) {
      toggleState_3 = !toggleState_3;
      digitalWrite(RelayPin3, !toggleState_3);
      switch3 = toggleState_3;
      lastDebounceTime3 = currentMillis;
    }
  }
  previousSwitchState3 = digitalRead(SwitchPin3);

  if (digitalRead(SwitchPin4) == LOW && previousSwitchState4 == HIGH) {
    if (currentMillis - lastDebounceTime4 >= debounceDelay) {
      toggleState_4 = !toggleState_4;
      digitalWrite(RelayPin4, !toggleState_4);
      switch4 = toggleState_4;
      lastDebounceTime4 = currentMillis;
    }
  }
  previousSwitchState4 = digitalRead(SwitchPin4);
}

void setup() {

  Serial.begin(9600);
  delay(1500);

  initProperties();

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);

  pinMode(wifiLed, OUTPUT);

  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);
  pinMode(SwitchPin3, INPUT_PULLUP);
  pinMode(SwitchPin4, INPUT_PULLUP);

  digitalWrite(RelayPin1, HIGH);
  digitalWrite(RelayPin2, HIGH);
  digitalWrite(RelayPin3, HIGH);
  digitalWrite(RelayPin4, HIGH);

  digitalWrite(wifiLed, HIGH);
}

void loop() {

  ArduinoCloud.update();

  manual_control();

  if (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(wifiLed, HIGH);
  }
  else{
    digitalWrite(wifiLed, LOW);
  }
}

void onSwitch1Change() {

  if (switch1 == 1)
  {
    digitalWrite(RelayPin1, LOW);
    Serial.println("Device1 ON");
    toggleState_1 = 1;
  }
  else
  {
    digitalWrite(RelayPin1, HIGH);
    Serial.println("Device1 OFF");
    toggleState_1 = 0;
  }
}

void onSwitch2Change() {

  if (switch2 == 1)
  {
    digitalWrite(RelayPin2, LOW);
    Serial.println("Device2 ON");
    toggleState_2 = 1;
  }
  else
  {
    digitalWrite(RelayPin2, HIGH);
    Serial.println("Device2 OFF");
    toggleState_2 = 0;
  }
}

void onSwitch3Change() {

  if (switch3 == 1)
  {
    digitalWrite(RelayPin3, LOW);
    Serial.println("Device2 ON");
    toggleState_3 = 1;
  }
  else
  {
    digitalWrite(RelayPin3, HIGH);
    Serial.println("Device3 OFF");
    toggleState_3 = 0;
  }
}

void onSwitch4Change() {

  if (switch4 == 1)
  {
    digitalWrite(RelayPin4, LOW);
    Serial.println("Device4 ON");
    toggleState_4 = 1;
  }
  else
  {
    digitalWrite(RelayPin4, HIGH);
    Serial.println("Device4 OFF");
    toggleState_4 = 0;
  }
}
