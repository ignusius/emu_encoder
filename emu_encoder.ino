const int inA = 2;     // button +
const int inB = 3;      // button -
const int inS = 6;      // STEP MODE ON/OFF


int outA = 4 ;
int outB = 5 ;
int stepOFF = 0;
int forward_loop = 0;
int back_loop = 0;
int analog_value = 0;
int speed_value = 0;

//Change it. Frequency range in ms.
int freq_max_ms = 100;
int freq_min_ms = 10;
//=================================


int freq_ms = 0;


volatile char stat_step = 0;
volatile char stat_loop = 0;
volatile char loopON = 0;
volatile char step_forward = 0;
volatile char step_back = 0;



void setup() {

  pinMode(outA, OUTPUT);
  pinMode(outB, OUTPUT);
  pinMode(inA, INPUT_PULLUP);
  pinMode(inB, INPUT_PULLUP);
  attachInterrupt(0, forward, FALLING);
  attachInterrupt(1, back, FALLING);

}

void forward() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 100ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 100)
  {
    step_back = 0;
     step_forward = 1;
  }
  last_interrupt_time = interrupt_time;
}

void back() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 100ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 100)
  {
    step_forward = 0;
    step_back = 1;
  }
  last_interrupt_time = interrupt_time;
}

void loop() {

  analog_value = analogRead(A0);
  freq_ms = freq_max_ms - int((((freq_max_ms - freq_min_ms / 2) / 1024.0) * analog_value));


  stepOFF = digitalRead(inS);


  if (!stepOFF) {
    if (loopON) {
      step_forward=0;
      step_back=0;
      loopON = 0;
    }


    if (step_forward){
      
      digitalWrite(outA, LOW);
      digitalWrite(outB, LOW);
      delay(freq_ms);

      digitalWrite(outA, HIGH);
      digitalWrite(outB, LOW);
      delay(freq_ms);

      digitalWrite(outA, HIGH);
      digitalWrite(outB, HIGH);
      delay(freq_ms);

      digitalWrite(outA, LOW);
      digitalWrite(outB, HIGH);
      delay(freq_ms);

      digitalWrite(outA, LOW);
      digitalWrite(outB, LOW);
      step_forward = 0;

    }
     if (step_back){
      
      digitalWrite(outA, LOW);
      digitalWrite(outB, LOW);
      delay(freq_ms);

      digitalWrite(outA, LOW);
      digitalWrite(outB, HIGH);
      delay(freq_ms);

      digitalWrite(outA, HIGH);
      digitalWrite(outB, HIGH);
      delay(freq_ms);

      digitalWrite(outA, HIGH);
      digitalWrite(outB, LOW);
      delay(freq_ms);

      digitalWrite(outA, LOW);
      digitalWrite(outB, LOW);
      step_back = 0;

    }
  
    
  }
  else {
    loopON = 1;
    stat_step == 0;
    forward_loop = digitalRead(inA);
    back_loop = digitalRead(inB);
    stepOFF = digitalRead(inS);
    if (!forward_loop) {


      digitalWrite(outA, LOW);
      digitalWrite(outB, LOW);
      stat_step = 1;
      delay(freq_ms);

      digitalWrite(outA, HIGH);
      digitalWrite(outB, LOW);
      stat_step = 2;
      delay(freq_ms);

      digitalWrite(outA, HIGH);
      digitalWrite(outB, HIGH);
      stat_step = 3;
      delay(freq_ms);

      digitalWrite(outA, LOW);
      digitalWrite(outB, HIGH);
      stat_step = 0;
      delay(freq_ms);

    } else {
      digitalWrite(outA, LOW);
      digitalWrite(outB, LOW);
    }

    if (!back_loop) {


      digitalWrite(outA, LOW);
      digitalWrite(outB, LOW);
      stat_step = 1;
      delay(freq_ms);

      digitalWrite(outA, LOW);
      digitalWrite(outB, HIGH);
      stat_step = 2;
      delay(freq_ms);

      digitalWrite(outA, HIGH);
      digitalWrite(outB, HIGH);
      stat_step = 3;
      delay(freq_ms);

      digitalWrite(outA, HIGH);
      digitalWrite(outB, LOW);
      stat_step = 0;
      delay(freq_ms);

    } else {
      digitalWrite(outA, LOW);
      digitalWrite(outB, LOW);
    }


  }
}


