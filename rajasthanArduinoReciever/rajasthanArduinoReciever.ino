#define rfReceivePin A0
#define ledPin 7
const int ldrPin = A1;
const int AOUTpin = A2;
const int ml1 = 9;
int b;
unsigned int data = 0;
const unsigned int upperThreshold = 900;
int threshold1 = 500;
int threshold2 = 700;
int value;

void setup() {

  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
  pinMode(ldrPin, LOW);
  pinMode(ml1, OUTPUT);
  digitalWrite(ml1, LOW);
  Serial.begin(9600);
}

void loop() {

  data = analogRead(rfReceivePin);
  value = analogRead(AOUTpin);
  b = analogRead(ldrPin);
  
  if (data > upperThreshold && b < 100)
  {
    digitalWrite(ledPin, LOW);
    Serial.print(data);
    Serial.print(" = Data greater than threshold. ");
    Serial.print("Alcohol value: ");
    Serial.print(value);
    Serial.print("  LDR value= ");
    Serial.print(b);
    delay(500);
  }

else if(data > upperThreshold && b > 100)
{
    digitalWrite(ledPin, HIGH);
    Serial.print(data);
    Serial.print(" = Car is not close  ");
    Serial.print("Alcohol value: ");
    Serial.print(value);
    Serial.print("  LDR value= ");
    Serial.print(b);
    delay(500);
}
else 
{
    digitalWrite(ledPin, HIGH);
    Serial.print(data);
    Serial.print("= Disconnected.  ");
    Serial.print("Alcohol value: ");
    Serial.print(value);
    Serial.print("  LDR value= ");
    Serial.print(b);
    delay(500);
  }
  
  if (value > threshold2)
  {
    digitalWrite(ml1, LOW);
    Serial.println();
    Serial.print("  OFF");
    Serial.println();
  }
  else if (value < threshold2 && value > threshold1)
  {
    analogWrite(ml1, 100);
    Serial.println();
    Serial.print("   mid");
    Serial.println();
  }
  else
  {
    digitalWrite(ml1, 255);
    Serial.println();
    Serial.print("   high");
    Serial.println();
  }

}


