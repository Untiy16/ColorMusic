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

void pride() 
{
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;
 
  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);
  
  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = sPseudotime;
  
  for( uint16_t i = 0 ; i < NUM_LEDS; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);
    
    CRGB newcolor = CHSV( hue8, sat8, bri8);
    
    uint16_t pixelnumber = i;
    pixelnumber = (NUM_LEDS-1) - pixelnumber;
    
    nblend( leds[pixelnumber], newcolor, 64);
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