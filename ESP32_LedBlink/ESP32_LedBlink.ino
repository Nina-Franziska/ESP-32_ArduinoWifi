// LED on GPIO2
int ledPin = 2;
 
void setup()
{
    // Set LED as output
    pinMode(ledPin, OUTPUT);
  
}
 
void loop()
{
    digitalWrite(ledPin, HIGH);
    
    delay(50);
    
    digitalWrite(ledPin, LOW);
    
    delay(100);
}