#include <Arduino.h>
#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

const int columnInput = 5;
const int rCtrlKey = 32;          // input pin for pushbutton
int previousButtonState = HIGH; // for checking the state of a pushButton
int cpu_freq_mhz = 240;

void setup() 
{
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  // make the pushButton pin an output:
  pinMode(rCtrlKey, OUTPUT);
  pinMode(rCtrlKey, HIGH);
  // Column recives the signal from a pulse
  pinMode(columnInput, INPUT); 

  //function takes the following frequencies as valid values:
  //  240, 160, 80    <<< For all XTAL types
  //  40, 20, 10      <<< For 40MHz XTAL
  //  26, 13          <<< For 26MHz XTAL
  //  24, 12          <<< For 24MHz XTAL
  bool setCpuFrequencyMhz(uint32_t cpu_freq_mhz);

  bleKeyboard.begin();
}

void loop()
{  
  if(bleKeyboard.isConnected()) 
  {
    Serial.println("Connected to system");

    delay(10);
    
    // read the pushbutton:
    int buttonState = digitalRead(columnInput);

    // if the button state has changed,
    if ((buttonState != previousButtonState)

      // and it's currently pressed:
      && (buttonState == HIGH)) 
      {
        // type out a message
        Serial.println("Sending Play/Pause media key...");
        bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
      }
    // save the current button state for comparison next time:
    previousButtonState = buttonState;
  }
}

// void loop() {
//  if(bleKeyboard.isConnected()) {
//    Serial.println("Connected to system");
//    bleKeyboard.print("Hello world");

//    delay(1000);

//    Serial.println("Sending Enter key...");
//    bleKeyboard.write(KEY_RETURN);

//    delay(1000);

//    Serial.println("Sending Play/Pause media key...");
//    bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);

 ///   delay(1000);

 //   Serial.println("Sending Ctrl+Alt+Delete...");
 //   bleKeyboard.press(KEY_LEFT_CTRL);
 //   bleKeyboard.press(KEY_LEFT_ALT);
 //   bleKeyboard.press(KEY_DELETE);
//    delay(100);
 //   bleKeyboard.releaseAll();
 // }

 // Serial.println("Waiting 5 seconds...");
//  delay(5000);
// }
