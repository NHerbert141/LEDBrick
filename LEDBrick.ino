#include <Encoder.h>
#include "./FadeLed.h"
#include "./FadeStatus.h"

#define RED_MAIN 17
#define GREEN_MAIN 20
#define BLUE_MAIN 23

#define RED_STATUS 0
#define GREEN_STATUS 1
#define BLUE_STATUS 2

#define ENCODER_A 9
#define ENCODER_B 10
#define PRESS_BUTTON 8

#define LED_UPDATE_MS 10
#define DEFAULT_FADE_TIME_MS 1000 // The RGB LEDs are set to this constant fade time
#define STATUS_LED_FADE_SPEED_MS 100 // The status LEDs are set to a constant fade speed, this defines that

#define ALERT_TIME_MS 1500 // When a status alert is posted, this is how long it blinks for (5 blinks)

#define MIN_SUM_FADE_CHANGE 10 // When a random fade is commanded, this is the minimum intensity change (0-255)
#define MIN_SUM_BRIGHTNESS 75 // When a random fade is commanded, this is the minimum total brightness (0-(255*3))

// The main RGB led objects (pin)
FadeLed red_led(RED_MAIN);
FadeLed green_led(GREEN_MAIN);
FadeLed blue_led(BLUE_MAIN);

// The status RGB led objects (pin)
FadeStatus red_status(RED_STATUS);
FadeStatus green_status(GREEN_STATUS);
FadeStatus blue_status(BLUE_STATUS);

// the rotary encoder object (pins)
Encoder knob(ENCODER_A, ENCODER_B);

volatile bool clicked_flag = false;

// Used to time led fading
unsigned long last_fade_ms = 0;
unsigned long fade_interval = DEFAULT_FADE_TIME_MS;

void setup() 
{
  // The press button
  pinMode(PRESS_BUTTON, INPUT);
  attachInterrupt(digitalPinToInterrupt(PRESS_BUTTON), click_isr, FALLING);
  
  //Set update interval to 10ms
  FadeLed::setInterval(LED_UPDATE_MS);
  FadeStatus::setInterval(LED_UPDATE_MS);
  
  // ', true)' makes it constant fade time (cannot command new fade until previous is complete)
  // Otherwise it is a constant fade speed (less fading take less time), which can be changed mid-fade
  red_led.setTime(DEFAULT_FADE_TIME_MS, true);
  green_led.setTime(DEFAULT_FADE_TIME_MS, true);
  blue_led.setTime(DEFAULT_FADE_TIME_MS, true);

  red_status.setTime(STATUS_LED_FADE_SPEED_MS);
  green_status.setTime(STATUS_LED_FADE_SPEED_MS);
  blue_status.setTime(STATUS_LED_FADE_SPEED_MS);

  red_led.begin(random(0,255));
  green_led.begin(random(0,255));
  blue_led.begin(random(0,255));
  
  red_status.begin(0);
  green_status.begin(0);
  blue_status.begin(0);
}

void loop() 
{
  FadeLed::update();
  FadeStatus::update();
  
  unsigned int current_red = 0;
  unsigned int current_green = 0;
  unsigned int current_blue = 0;
  unsigned int next_red = 0;
  unsigned int next_green = 0;
  unsigned int next_blue = 0;

  unsigned int total_change = 0;
  unsigned int total_brightness = 0;

  if(clicked_flag == true)
  {
    clicked_flag = false;
    fade_interval_adjust(last_fade_ms);
  }
  
  // Change every fade_interval (check that leds are done fading)
  if((millis() > last_fade_ms + fade_interval) && (red_led.done() && green_led.done() && blue_led.done()))
  {
    // Ensure that consecutive fades aren't too close
    current_red = 255 - red_led.getCurrent();
    current_green = 255 - green_led.getCurrent();
    current_blue = 255 - blue_led.getCurrent();
    while((total_change < MIN_SUM_FADE_CHANGE) && (total_brightness < MIN_SUM_BRIGHTNESS))
    {
      FadeLed::update();
      FadeStatus::update();
      
      // Generate random values
      next_red = random(0, 255);
      next_green = random(0, 255);
      next_blue = random(0,255);
  
      // Calculate the sum of the changes
      total_change = (abs(current_red - next_red) + abs(current_green - next_green) + abs(current_blue - next_blue));
      total_brightness = next_red + next_green + next_blue;
    }
  
    red_led.set(next_red);
    green_led.set(next_green);
    blue_led.set(next_blue);
    // Save time for the next time
    last_fade_ms = millis();
  }
}

void fade_interval_adjust(unsigned long &last_fade_ms)
{
  // Time between changes before it stops listening
  unsigned long control_timeout_ms = 2000;
  // Time of last user interaction
  unsigned long benchmark_ms = millis();
 
  unsigned long max_fade_interval = 20000;
  unsigned long min_fade_interval = LED_UPDATE_MS * 5;
  unsigned int ms_per_pulse = 5;
 
  long new_position = 0;
  long last_position = 0;
  long change = 0;
  long ms_change = 0;

  unsigned int current_red = 0;
  unsigned int current_green = 0;
  unsigned int current_blue = 0;
  unsigned int next_red = 0;
  unsigned int next_green = 0;
  unsigned int next_blue = 0;

  unsigned int total_change = 0;
  unsigned int total_brightness = 0;

  // Reset position
  knob.write(0);

  // Turns on blue status LED
  blue_status.set(255);

  // Runs until the knob has not been adjusted for timeout_ms
  while((benchmark_ms + control_timeout_ms) > millis())
  {
    FadeLed::update();
    FadeStatus::update();
   
    // Change every fade_interval (check that leds are done fading)
    if((millis() > last_fade_ms + fade_interval) && (red_led.done() && green_led.done() && blue_led.done()))
    {
      // Ensure that consecutive fades aren't too close
      current_red = 255 - red_led.getCurrent();
      current_green = 255 - green_led.getCurrent();
      current_blue = 255 - blue_led.getCurrent();
      total_change = 0;
      total_brightness = 0;
      while((total_change < MIN_SUM_FADE_CHANGE) && (total_brightness < MIN_SUM_BRIGHTNESS))
      {
        FadeLed::update();
        FadeStatus::update();
        
        // Generate random values
        next_red = random(0, 255);
        next_green = random(0, 255);
        next_blue = random(0,255);
    
        // Calculate the sum of the changes
        total_change = (abs(current_red - next_red) + abs(current_green - next_green) + abs(current_blue - next_blue));
        total_brightness = next_red + next_green + next_blue;
      }
    
      red_led.set(next_red);
      green_led.set(next_green);
      blue_led.set(next_blue);
      // Save time for the next time
      last_fade_ms = millis();
    }
   
    // return from function if knob is clicked
    if(clicked_flag == true)
    {
      clicked_flag = false;
      blue_status.set(0);
      return;
    }

    // Wait for the fade to be done, this allows us to set the fade time
    while(!(red_led.done() && green_led.done() && blue_led.done()))
    {
      FadeLed::update();
      FadeStatus::update();
      
      // return from function if knob is clicked
      if(clicked_flag == true)
      {
        clicked_flag = false;
        blue_status.set(0);
        return;
      }
    }

    new_position = knob.read();
    change = new_position - last_position;
    last_position = new_position;
   
    // Skip remainder of loop if value didn't change
    if(change == 0)
    {
      continue;
    }

    // Convert pulses to fade_interval ms
    ms_change = ms_per_pulse * change;
   
    // Check that fade_interval stays within bounds
    if(((fade_interval + ms_change) > min_fade_interval) && (max_fade_interval > (fade_interval + ms_change)))
    {
      fade_interval = fade_interval + ms_change;
      red_led.setTime(fade_interval, true);
      green_led.setTime(fade_interval, true);
      blue_led.setTime(fade_interval, true);
      red_led.set(next_red);
      green_led.set(next_green);
      blue_led.set(next_blue);

      if(red_status.getCurrent() > 0)
      {
        red_status.set(0);
      }
    }
    else
    {
      red_status.set(255);
    }
    // Update the timeout benchmark since the knob was changed
    benchmark_ms = millis();
  }
  blue_status.set(0);
  return;
}

void click_isr()
{
  clicked_flag = true;
}

