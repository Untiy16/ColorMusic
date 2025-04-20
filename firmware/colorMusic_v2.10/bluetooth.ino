#if (USE_BT == 1)
String command = "";
void bluetoothTick() {
  while(btSerial.available() > 0) {
    command += (char)btSerial.read();
     delay(10);
  }

  if (command != "") {

    command.trim();  // Remove added LF in transmit
    // We expect Command from bluetooth

    if (command.length() == 3 && command[1] == '.') { 
      byte subMode = command.substring(command.indexOf('.') + 1).toInt() - 1;
      this_mode = command.substring(0, command.indexOf('.')).toInt() - 1;

      if (this_mode == 4 || this_mode == 7) {
        freq_strobe_mode = subMode;
      } else if(this_mode == 6) {
        light_mode = subMode;
      } else if(this_mode == 8) {
        multi_frequencies_mode = subMode;
      }
    } else {
      // Check if the first and last characters match
      if (command.charAt(0) == '^' && command.charAt(command.length() - 1) == '$') {
        // Extract the part of the string between '^' and '$'
        command = command.substring(1, command.length() - 1);
        byte parsedCommand = command.toInt();

        // if (command.equals("1.1")) { this_mode = 0; }
        if (parsedCommand == 1) { SMOOTH = smartIncrFloat(SMOOTH, -0.05, 0.05, 1); }//if (command.equals("1.1_smooth-") || command.equals("2.1_smooth-")) { SMOOTH = smartIncrFloat(SMOOTH, -0.05, 0.05, 1); }
        else if (parsedCommand == 2) { SMOOTH = smartIncrFloat(SMOOTH, 0.05, 0.05, 1); }//else if (command.equals("1.1_smooth+") || command.equals("2.1_smooth+")) { SMOOTH = smartIncrFloat(SMOOTH, 0.05, 0.05, 1); }
        // else if (command.equals("2.1")) { this_mode = 1; }
        else if (parsedCommand == 3) { RAINBOW_STEP = smartIncrFloat(RAINBOW_STEP, 0.5, 0.5, 20); }//else if (command.equals("2.1_rstep+")) { RAINBOW_STEP = smartIncrFloat(RAINBOW_STEP, 0.5, 0.5, 20); }
        else if (parsedCommand == 4) { RAINBOW_STEP = smartIncrFloat(RAINBOW_STEP, -0.5, 0.5, 20); }//else if (command.equals("2.1_rstep-")) { RAINBOW_STEP = smartIncrFloat(RAINBOW_STEP, -0.5, 0.5, 20); }
        // else if (command.equals("3.1")) { this_mode = 2; }
        //for 3 4 5 mode
        else if (parsedCommand == 5) { SMOOTH_FREQ = smartIncrFloat(SMOOTH_FREQ, -0.05, 0.05, 1); }//else if (command.equals("3_smooth-")) { SMOOTH_FREQ = smartIncrFloat(SMOOTH_FREQ, -0.05, 0.05, 1); }
        else if (parsedCommand == 6) { SMOOTH_FREQ = smartIncrFloat(SMOOTH_FREQ, 0.05, 0.05, 1); }//else if (command.equals("3_smooth+")) { SMOOTH_FREQ = smartIncrFloat(SMOOTH_FREQ, 0.05, 0.05, 1); }
        else if (parsedCommand == 7) { MAX_COEF_FREQ = smartIncrFloat(MAX_COEF_FREQ, -0.1, 0, 5); } //3 4 5 and 8//else if (command.equals("3_sens-")) { MAX_COEF_FREQ = smartIncrFloat(MAX_COEF_FREQ, -0.1, 0, 5); } //3 4 5 and 8
        else if (parsedCommand == 8) { MAX_COEF_FREQ = smartIncrFloat(MAX_COEF_FREQ, 0.1, 0, 5); } //3 4 5 and 8//else if (command.equals("3_sens+")) { MAX_COEF_FREQ = smartIncrFloat(MAX_COEF_FREQ, 0.1, 0, 5); } //3 4 5 and 8
        //for 3 4 5 mode END
        // else if (command.equals("4.1")) { this_mode = 3; }
        // else if (command.equals("5.1")) { this_mode = 4; freq_strobe_mode = 0; }
        // else if (command.equals("5.2")) { this_mode = 4; freq_strobe_mode = 1; }
        // else if (command.equals("5.3")) { this_mode = 4; freq_strobe_mode = 2; }
        // else if (command.equals("5.4")) { this_mode = 4; freq_strobe_mode = 3; }
        // else if (command.equals("6.1")) { this_mode = 5; }
        else if (parsedCommand == 9) { STROBE_SMOOTH = smartIncr(STROBE_SMOOTH, -20, 0, 255); }//else if (command.equals("6.1_smooth-")) { STROBE_SMOOTH = smartIncr(STROBE_SMOOTH, -20, 0, 255); }
        else if (parsedCommand == 10) { STROBE_SMOOTH = smartIncr(STROBE_SMOOTH, 20, 0, 255); }//else if (command.equals("6.1_smooth+")) { STROBE_SMOOTH = smartIncr(STROBE_SMOOTH, 20, 0, 255); }
        else if (parsedCommand == 11) { STROBE_PERIOD = smartIncr(STROBE_PERIOD, -20, 1, 1000); }//else if (command.equals("6.1_freq-")) { STROBE_PERIOD = smartIncr(STROBE_PERIOD, -20, 1, 1000); }
        else if (parsedCommand == 12) { STROBE_PERIOD = smartIncr(STROBE_PERIOD, 20, 1, 1000); }//else if (command.equals("6.1_freq+")) { STROBE_PERIOD = smartIncr(STROBE_PERIOD, 20, 1, 1000); }
        // else if (command.equals("7.1")) { this_mode = 6; light_mode = 0; }
        // else if (command.equals("7.2")) { this_mode = 6; light_mode = 1; }
        // else if (command.equals("7.3")) { this_mode = 6; light_mode = 2; }
        // else if (command.equals("7.4")) { this_mode = 6; light_mode = 3; }
        // else if (command.equals("7.5")) { this_mode = 6; light_mode = 4; }
        // else if (command.equals("7.6")) { this_mode = 6; light_mode = 5; }
        // else if (command.equals("7.7")) { this_mode = 6; light_mode = 6; }
        // else if (command.equals("7.8")) { this_mode = 6; light_mode = 7; }
        //for 7.1 7.6 7.7
        else if (parsedCommand == 13) { LIGHT_COLOR = smartIncr(LIGHT_COLOR, -10, 0, 255); }//else if (command.equals("7_color-")) { LIGHT_COLOR = smartIncr(LIGHT_COLOR, -10, 0, 255); }
        else if (parsedCommand == 14) { LIGHT_COLOR = smartIncr(LIGHT_COLOR, 10, 0, 255); }//else if (command.equals("7_color+")) { LIGHT_COLOR = smartIncr(LIGHT_COLOR, 10, 0, 255); }
        else if (parsedCommand == 15) { LIGHT_SAT = smartIncr(LIGHT_SAT, -20, 0, 255); }//else if (command.equals("7_satur-")) { LIGHT_SAT = smartIncr(LIGHT_SAT, -20, 0, 255); }
        else if (parsedCommand == 16) { LIGHT_SAT = smartIncr(LIGHT_SAT, +20, 0, 255); }//else if (command.equals("7_satur+")) { LIGHT_SAT = smartIncr(LIGHT_SAT, +20, 0, 255); }
        //for 7.1 7.6 7.7 END
        else if (parsedCommand == 17) { COLOR_SPEED = smartIncr(COLOR_SPEED, -10, 0, 255); }//else if (command.equals("7.2_speed-")) { COLOR_SPEED = smartIncr(COLOR_SPEED, -10, 0, 255); }
        else if (parsedCommand == 18) { COLOR_SPEED = smartIncr(COLOR_SPEED, 10, 0, 255); }//else if (command.equals("7.2_speed+")) { COLOR_SPEED = smartIncr(COLOR_SPEED, 10, 0, 255); }
        else if (parsedCommand == 19) { RAINBOW_STEP_2 = smartIncrFloat(RAINBOW_STEP_2, -0.5, 0.5, 10); }//else if (command.equals("7.3_step-") || command.equals("9.5_step-")) { RAINBOW_STEP_2 = smartIncrFloat(RAINBOW_STEP_2, -0.5, 0.5, 10); }
        else if (parsedCommand == 20) { RAINBOW_STEP_2 = smartIncrFloat(RAINBOW_STEP_2, 0.5, 0.5, 10); }//else if (command.equals("7.3_step+") || command.equals("9.5_step+")) { RAINBOW_STEP_2 = smartIncrFloat(RAINBOW_STEP_2, 0.5, 0.5, 10); }
        else if (parsedCommand == 21) { RAINBOW_PERIOD = smartIncr(RAINBOW_PERIOD, -1, -20, 20); }//else if (command.equals("7.3_speed-")) { RAINBOW_PERIOD = smartIncr(RAINBOW_PERIOD, -1, -20, 20); }
        else if (parsedCommand == 22) { RAINBOW_PERIOD = smartIncr(RAINBOW_PERIOD, 1, -20, 20); }//else if (command.equals("7.3_speed+")) { RAINBOW_PERIOD = smartIncr(RAINBOW_PERIOD, 1, -20, 20); }
        else if (parsedCommand == 23) { FIRE_SPARKING = smartIncr(FIRE_SPARKING, -10, 50, 200); }//else if (command.equals("7.5_spark-")) { FIRE_SPARKING = smartIncr(FIRE_SPARKING, -10, 50, 200); }
        else if (parsedCommand == 24) { FIRE_SPARKING = smartIncr(FIRE_SPARKING, 10, 50, 200); }//else if (command.equals("7.5_spark+")) { FIRE_SPARKING = smartIncr(FIRE_SPARKING, 10, 50, 200); }
        else if (parsedCommand == 25) { FIRE_COOLING = smartIncr(FIRE_COOLING, -10, 20, 100); }//else if (command.equals("7.5_height-")) { FIRE_COOLING = smartIncr(FIRE_COOLING, -10, 20, 100); }
        else if (parsedCommand == 26) { FIRE_COOLING = smartIncr(FIRE_COOLING, 10, 20, 100); }//else if (command.equals("7.5_height+")) { FIRE_COOLING = smartIncr(FIRE_COOLING, 10, 20, 100); }
        else if (parsedCommand == 27) { TRAVEL_LIGHT_SPEED = smartIncr(TRAVEL_LIGHT_SPEED, 50, 10, 1000); }//else if (command.equals("7.6_speed-") || command.equals("7.7_speed-")) { TRAVEL_LIGHT_SPEED = smartIncr(TRAVEL_LIGHT_SPEED, 50, 10, 1000); }
        else if (parsedCommand == 28) { TRAVEL_LIGHT_SPEED = smartIncr(TRAVEL_LIGHT_SPEED, -50, 10, 1000); }//else if (command.equals("7.6_speed+") || command.equals("7.7_speed+")) { TRAVEL_LIGHT_SPEED = smartIncr(TRAVEL_LIGHT_SPEED, -50, 10, 1000); }
        // else if (command.equals("8.1")) { this_mode = 7; freq_strobe_mode = 0; }
        // else if (command.equals("8.2")) { this_mode = 7; freq_strobe_mode = 1; }
        // else if (command.equals("8.3")) { this_mode = 7; freq_strobe_mode = 2; }
        // else if (command.equals("8.4")) { this_mode = 7; freq_strobe_mode = 3; }
        else if (parsedCommand == 29) { RUNNING_SPEED = smartIncr(RUNNING_SPEED, -10, 1, 255); }//else if (command.equals("8_speed-")) { RUNNING_SPEED = smartIncr(RUNNING_SPEED, -10, 1, 255); }
        else if (parsedCommand == 30) { RUNNING_SPEED = smartIncr(RUNNING_SPEED, 10, 1, 255); }//else if (command.equals("8_speed+")) { RUNNING_SPEED = smartIncr(RUNNING_SPEED, 10, 1, 255); }
        // else if (command.equals("9.1")) { this_mode = 8; multi_frequencies_mode = 0; }
        // else if (command.equals("9.2")) { this_mode = 8; multi_frequencies_mode = 1; }
        // else if (command.equals("9.3")) { this_mode = 8; multi_frequencies_mode = 2; }
        // else if (command.equals("9.4")) { this_mode = 8; multi_frequencies_mode = 3; }
        // else if (command.equals("9.5")) { this_mode = 8; multi_frequencies_mode = 4; }
        else if (parsedCommand == 31) { HUE_STEP = smartIncr(HUE_STEP, -1, 1, 255); }//else if (command.equals("9.1_step-") || command.equals("9.2_step-")) { HUE_STEP = smartIncr(HUE_STEP, -1, 1, 255); }
        else if (parsedCommand == 32) { HUE_STEP = smartIncr(HUE_STEP, 1, 1, 255); }//else if (command.equals("9.1_step+") || command.equals("9.2_step+")) { HUE_STEP = smartIncr(HUE_STEP, 1, 1, 255); }
        else if (parsedCommand == 33) { HUE_START = smartIncr(HUE_START, -10, 0, 255); }
        else if (parsedCommand == 34) { HUE_START = smartIncr(HUE_START, 10, 0, 255); }
        else if (parsedCommand == 35) { BRIGHTNESS = smartIncr(BRIGHTNESS, -20, 0, 255); FastLED.setBrightness(BRIGHTNESS); }//else if (command.equals("bright_on-")) { BRIGHTNESS = smartIncr(BRIGHTNESS, -20, 0, 255); }
        else if (parsedCommand == 36) { BRIGHTNESS = smartIncr(BRIGHTNESS, 20, 0, 255); FastLED.setBrightness(BRIGHTNESS); }//else if (command.equals("bright_on+")) { BRIGHTNESS = smartIncr(BRIGHTNESS, 20, 0, 255); }
        else if (parsedCommand == 37) { EMPTY_BRIGHT = smartIncr(EMPTY_BRIGHT, -5, 0, 255); }//else if (command.equals("bright_off-")) { EMPTY_BRIGHT = smartIncr(EMPTY_BRIGHT, -5, 0, 255); }
        else if (parsedCommand == 38) { EMPTY_BRIGHT = smartIncr(EMPTY_BRIGHT, 5, 0, 255); }//else if (command.equals("bright_off+")) { EMPTY_BRIGHT = smartIncr(EMPTY_BRIGHT, 5, 0, 255); }
        else if (parsedCommand == 39) { ONstate = !ONstate; FastLED.clear(); FastLED.show(); updateEEPROM(); }/* On/OFF star btn*/
        else if (parsedCommand == 40) { fullLowPass(); } /* calibration 0 btn */
        else if (parsedCommand == 41) { FREQ_COUNT = smartIncr(FREQ_COUNT, -1, 1, 20); }
        else if (parsedCommand == 42) { FREQ_COUNT = smartIncr(FREQ_COUNT, 1, 1, 20); }
      } 
    }
    
    
   

    command = ""; //reset cmd
  }
}
#else
void bluetoothTick() {}
#endif
