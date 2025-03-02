void fire() {
  static byte heat[NUM_LEDS];
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < NUM_LEDS; i++) {
    heat[i] = qsub8( heat[i],  random8(0, ((FIRE_COOLING * 10) / NUM_LEDS) + 2));
  }
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
  }
  // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
  if( random8() < FIRE_SPARKING ) {
    int y = random8(7);
    heat[y] = qadd8( heat[y], random8(160,255) );
  }
  // Step 4.  Map from heat cells to LED colors
  for( int j = 0; j < NUM_LEDS/*/2*/; j++) {
    CRGB color = HeatColor( heat[j]);
    int pixelnumber;
    pixelnumber = j;
    leds[pixelnumber] = color;
  }
}

void travel_light() {
   static int runningLed = 0;
   EVERY_N_MILLISECONDS_DYNAMIC(TRAVEL_LIGHT_SPEED) {
      runningLed++;
      if (runningLed >= NUM_LEDS) {
         runningLed = 0;
      }
   }

   for (int i = 0; i < NUM_LEDS; i++) {
       if (i == runningLed) {
         leds[i] = CHSV(LIGHT_COLOR, LIGHT_SAT, 255);
       } else {
         leds[i] = CRGB::Black;
       }
   }
}

void beads() {
   static int runningLed = 0;
   static int numLeds = NUM_LEDS;

   EVERY_N_MILLISECONDS_DYNAMIC(TRAVEL_LIGHT_SPEED) {
      runningLed++;
      if (runningLed >= numLeds) {
          runningLed = 0;
          numLeds--;
      }
      if (numLeds <= 0) {
          numLeds = NUM_LEDS;
      }
   }

   for (int i = 0; i < numLeds + 1; i++) {
       if (i == runningLed) {
         leds[i] = CHSV(LIGHT_COLOR, LIGHT_SAT, 255);
       } else {
         leds[i] = CRGB::Black;
       }
   }
   for (int j = NUM_LEDS - 1; j >= numLeds; j--) {
       leds[j] = CHSV(LIGHT_COLOR, LIGHT_SAT, 255);
   }
}

byte policeStrobeSectionLength = 5;
byte policeStrobeWhiteLength = 3 * policeStrobeSectionLength + 3 - 1;
void policeStrobe() {
    static bool direction = true;
    static bool blink = true;
    static byte sectionCounter = 0;
    EVERY_N_MILLISECONDS(900) {direction = !direction;}
    EVERY_N_MILLISECONDS(100) {blink = !blink;}

    if (blink) {
      if (direction) {
        for (int i = NUM_LEDS / 2 - 1; i >= 0; i--) {
          if (sectionCounter != policeStrobeSectionLength) {
						if (i > (NUM_LEDS / 2 - 1) - policeStrobeWhiteLength) {
							leds[i] = CRGB::White;
						} else {
              leds[i] = CRGB::Blue;
						}
            sectionCounter++;
          } else {
							sectionCounter = 0;
          }  
				}
      } else {
					for (int i = NUM_LEDS / 2; i < NUM_LEDS; i++) {
            if (sectionCounter != policeStrobeSectionLength) {
              if (i < (NUM_LEDS / 2) + policeStrobeWhiteLength) {
                leds[i] = CRGB::White;
              } else {
                leds[i] = CRGB::Red;
              }
              sectionCounter++;
            } else {
							sectionCounter = 0;
						}
					}
      }
    }
    sectionCounter = 0;

}