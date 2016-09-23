//*****************************************************************************
//
// Pseudocode demonstrating button input, debounce and Finite State Engines (FSE)
// Remember, this is PSEUDOCODE!
//
//*****************************************************************************

void main(void)
{
  int state_1 = 0;        //Finite state engine, state 1 variable
  int state_2 = 0;        //Finite state engine, state 2 variable
  int button1_press = 0;  //Button 1 input
  int button1_press_last = button1_press; //Initialize Button 1 hysteresis variable
  int button2_press = 0;  //Button 2 input
  int button2_press_last = button2_press; //Initialize Button 2 hysteresis variable
  
  int FSE1_clock_delay = 0; //FSE clock-tick counter (milliseconds, perhaps)
  int FSE2_clock_delay = 0; //...same as above but for FSE2

//*****************************************************************************
// Collecting/determining new button presses, kicking off finite state engine(s)
//*****************************************************************************
   
  while(1)                                      //Run forever (main loop of robot code)
  {
    update_buttons();                           //Obtain button inputs updating...
                                                //...button1_press and button2_press
    if(button1_press ^ button1_press_last)      //XOR to determine button just changed
    {
      button1_press_last = button1_press;       //Save the latest button condition
      //Since the FSEs implement time delays, the following line debounces buttons too
      if(button1_press & !state_1) state_1 = 1; //If button1 just pressed and...
                                                //...FSE not underway, start FSE
                                               
    }
    if(button2_press ^ button2_press_last)      //XOR to determine button just changed
    {
      button2_press_last = button2_press;       //Save the latest button condition
      //Since the FSEs implement time delays, the following line debounces buttons too
      if(button1_press & !state_2) state_2 = 1; //If button2 just pressed and...
                                                //...FSE not underway, start FSE
    }

//*****************************************************************************
// Start of finite state engine (FSE) functionality   
//*****************************************************************************
    switch(state_1)                           //Determine which state is active
    {
      case 1:   //Drive forward for 5 seconds
        //Start robot action, for this example drive all motors forward
        //Another FSE can be started here by incrementing its state variable
        FSE1_clock_delay = get_clock(); //Get initial clock value
        ++state_1;  //Increment state of FSE1, passing to following state(s)
      case 2:
        //Wait for desired delay to expire
        if(get_clock() < FSE1_clock_delay+5000) //If desired delay has NOT passed,
          break;
        //End robot action, for this example kill all drive motors
        state_1 = 0;  //Reset state variable, allowing this FSE to again be started later
      break;
      default:
    } 
  }

    switch(state_2)                           //Determine which state is active
    {
      case 1:   //Drive forward for 2.5 seconds, then turn left for 1 second
        //Start robot action, for this example drive all motors forward
        FSE2_clock_delay = get_clock(); //Get initial clock value
        ++state_2;  //Increment state of FSE2, passing to following state(s)
        //case 2 implements a time delay, then the next action
      case 2:
        //Wait for desired delay to expire
        if(get_clock() < FSE2_clock_delay+2500) //If desired delay has NOT passed,
          break;    //Get out of FSE until the next pass
        //Start a different robot action, for this example turn left
        FSE2_clock_delay = get_clock(); //Reinitialize clock value
        ++state_2;  //Increment state of FSE2, then fall through to next state
      case 3:
        //Another FSE can be started here by initializing its state variable
        //Wait for desired delay to expire
        if(get_clock() < FSE2_clock_delay+1000) //If desired delay has NOT passed,
          break;    //Get out of FSE until the next pass
        //End robot action, for this example kill all drive motors
        state_2 = 0;  //Reset state variable, allowing this FSE to again be started later
        break;
      default:
        //Print debug message indicating unexpected/unprocessed state
    } 
  }
}
