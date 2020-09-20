#define PIN_LED 7

unsigned int toggle;
unsigned int count;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  while (!Serial) {;}
  toggle = 0;
  count = 0;
  digitalWrite(PIN_LED, toggle);
  delay(1000);
}

void loop() {
  
  while(1)
  {
    if(count >= 10)
    {
        break;
    }
    toggle = toggle_state(toggle);
    digitalWrite(PIN_LED,toggle);
    delay(200);
    count++;
    //Serial.println(count);
  }
  digitalWrite(PIN_LED,1);
}

int toggle_state(int toggle) {
  if(toggle == 1)
  {
    return 0; 
  }
  else if(toggle == 0)
  {
    return 1;
  }
}