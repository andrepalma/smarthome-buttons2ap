//=================================================
//  MULTI-CLICK:  One Button, Multiple Events
// Button timing variables
int debounce = 30;          // ms debounce period to prevent flickering when pressing or releasing the button
int DCgap = 250;            // max ms between clicks for a double click event
int holdTime = 2000;        // ms hold period: how long to wait for press+hold event
int longHoldTime = 4000;    // ms long hold period: how long to wait for press+hold event

// Button variables
boolean buttonVal = HIGH;   // value read from button
boolean buttonLast = HIGH;  // buffered value of the button's previous state
boolean DCwaiting = false;  // whether we're waiting for a double click (down)
boolean DConUp = false;     // whether to register a double click on next release, or whether to wait and click
boolean singleOK = true;    // whether it's OK to do a single click
long downTime = -1;         // time the button was pressed down
long upTime = -1;           // time the button was released
boolean ignoreUp = false;   // whether to ignore the button release because the click+hold was triggered
boolean waitForUp = false;        // when held, whether to wait for the up event
boolean holdEventPast = false;    // whether or not the hold event happened already
boolean longHoldEventPast = false;// whether or not the long hold event happened already

const int PIN_BUTTON1 = D5;
const int PIN_BUTTON2 = D6;


int checkButton() {
   int event = 0;
   buttonVal = digitalRead(PIN_BUTTON1);
   // Button pressed down
   if (buttonVal == LOW && buttonLast == HIGH && (millis() - upTime) > debounce)
   {
       downTime = millis();
       ignoreUp = false;
       waitForUp = false;
       singleOK = true;
       holdEventPast = false;
       longHoldEventPast = false;
       if ((millis()-upTime) < DCgap && DConUp == false && DCwaiting == true)  DConUp = true;
       else  DConUp = false;
       DCwaiting = false;
   }
   // Button released
   else if (buttonVal == HIGH && buttonLast == LOW && (millis() - downTime) > debounce)
   {
       if (not ignoreUp)
       {
           upTime = millis();
           if (DConUp == false) DCwaiting = true;
           else
           {
               event = 2;
               DConUp = false;
               DCwaiting = false;
               singleOK = false;
           }
       }
   }
   // Test for normal click event: DCgap expired
   if ( buttonVal == HIGH && (millis()-upTime) >= DCgap && DCwaiting == true && DConUp == false && singleOK == true && event != 2)
   {
       event = 1;
       DCwaiting = false;
   }
   // Test for hold
   if (buttonVal == LOW && (millis() - downTime) >= holdTime) {
       // Trigger "normal" hold
       if (not holdEventPast)
       {
           event = 3;
           waitForUp = true;
           ignoreUp = true;
           DConUp = false;
           DCwaiting = false;
           //downTime = millis();
           holdEventPast = true;
       }
       // Trigger "long" hold
       if ((millis() - downTime) >= longHoldTime)
       {
           if (not longHoldEventPast)
           {
               event = 4;
               longHoldEventPast = true;
           }
       }
   }
   buttonLast = buttonVal;
   return event;
}

boolean buttonVal2 = HIGH;   // value read from button
boolean buttonLast2 = HIGH;  // buffered value of the button's previous state
boolean DCwaiting2 = false;  // whether we're waiting for a double click (down)
boolean DConUp2 = false;     // whether to register a double click on next release, or whether to wait and click
boolean singleOK2 = true;    // whether it's OK to do a single click
long downTime2 = -1;         // time the button was pressed down
long upTime2 = -1;           // time the button was released
boolean ignoreUp2 = false;   // whether to ignore the button release because the click+hold was triggered
boolean waitForUp2 = false;        // when held, whether to wait for the up event
boolean holdEventPast2 = false;    // whether or not the hold event happened already
boolean longHoldEventPast2 = false;// whether or not the long hold event happened already

int checkButton2() {
   int event = 0;
   buttonVal2 = digitalRead(PIN_BUTTON2);
   // Button pressed down
   if (buttonVal2 == LOW && buttonLast2 == HIGH && (millis() - upTime2) > debounce)
   {
       downTime2 = millis();
       ignoreUp2 = false;
       waitForUp2 = false;
       singleOK2 = true;
       holdEventPast2 = false;
       longHoldEventPast2 = false;
       if ((millis()-upTime2) < DCgap && DConUp2 == false && DCwaiting2 == true)  DConUp2 = true;
       else  DConUp2 = false;
       DCwaiting2 = false;
   }
   // Button released
   else if (buttonVal2 == HIGH && buttonLast2 == LOW && (millis() - downTime2) > debounce)
   {
       if (not ignoreUp2)
       {
           upTime2 = millis();
           if (DConUp2 == false) DCwaiting2 = true;
           else
           {
               event = 2;
               DConUp2 = false;
               DCwaiting2 = false;
               singleOK2 = false;
           }
       }
   }
   // Test for normal click event: DCgap expired
   if ( buttonVal2 == HIGH && (millis()-upTime2) >= DCgap && DCwaiting2 == true && DConUp2 == false && singleOK2 == true && event != 2)
   {
       event = 1;
       DCwaiting2 = false;
   }
   // Test for hold
   if (buttonVal2 == LOW && (millis() - downTime2) >= holdTime) {
       // Trigger "normal" hold
       if (not holdEventPast2)
       {
           event = 3;
           waitForUp2 = true;
           ignoreUp2 = true;
           DConUp2 = false;
           DCwaiting2 = false;
           //downTime = millis();
           holdEventPast2 = true;
       }
       // Trigger "long" hold
       if ((millis() - downTime2) >= longHoldTime)
       {
           if (not longHoldEventPast2)
           {
               event = 4;
               longHoldEventPast2 = true;
           }
       }
   }
   buttonLast2 = buttonVal2;
   return event;
}

//=================================================
// Events to trigger
void clickEvent() {
  // Event to singleclick UP


  // switch (shutState) {
  //   case GoingUP:
  //     shutHalt();
  //     // delay(20);
  //     Serial.println("Already going up, so stopped.");
  //     break;
  //   case GoingDOWN:
  //     shutHalt();
  //     // delay(20);
  //     Serial.println("Going up, so stopped.");
  //     // shutGoUp();
  //     break;
  //   case GoToLevel:
  //     shutHalt();
  //     // delay(20);
  //     break;
  //   case HALT:
  //     shutGoUp();
  //     // delay(20);
  //     break;
  //   case Open:
  //     shutHalt();
  //     break;
  //   case Closed:
  //     shutGoUp();
  //     break;
  // }

  // if (shutState != GoingUP){
  //   shutHalt();
  //   delay(20);
  //   shutGoUp();
  // }

  // ledVal1 = !ledVal1;
  // digitalWrite(PIN_LED1, ledVal1);
  Serial.println("Click");
}
void doubleClickEvent() {
   // ledVal2 = !ledVal2;
   // digitalWrite(PIN_LED2, ledVal2);
   Serial.println("DoubleClick");
}

void clickEvent2() {

  switch (shutState) {
    case GoingUP:
      shutHalt();
      // delay(20);
      Serial.println("going Up, so stopped.");
      break;
    case GoingDOWN:
      shutHalt();
      // delay(20);
      Serial.println("Already Going Down, so stopped.");
      // shutGoUp();
      break;
    case GoToLevel:
      shutHalt();
      // delay(20);
      break;
    case HALT:
      shutGoDn();
      // delay(20);
      break;
    case Open:
      shutGoDn();
      break;
    case Closed:
      shutHalt();


      break;
  }

  Serial.println("Click2");
}
void doubleClickEvent2() {
   // ledVal4 = !ledVal4;
   // digitalWrite(PIN_LED4, ledVal4);
   Serial.println("DoubleClick2");
}

void buttonsSetup(){

  pinMode(PIN_BUTTON1, INPUT_PULLUP);
  digitalWrite(PIN_BUTTON1, HIGH);

  pinMode(PIN_BUTTON2, INPUT_PULLUP);
  digitalWrite(PIN_BUTTON2, HIGH);

}

void buttonsLoop(){
  int b = checkButton();
  if (b == 1) clickEvent();
  if (b == 2) doubleClickEvent();

  int c = checkButton2();
  if (c == 1) clickEvent2();
  if (c == 2) doubleClickEvent2();


}
