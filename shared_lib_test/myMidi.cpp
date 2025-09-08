//*****************************************//
//  midi controller prototype for my custom SDR++ implementation.
//  Based on,
//    https://github.com/thestk/rtmidi
//    https://github.com/thestk/rtmidi/blob/master/LICENSE
//
//*****************************************//

#include <iostream>
#include <cstdlib>
#include <string>
#include "RtMidi.h"

using namespace std;


void myMidi_cb( double deltatime, std::vector< unsigned char > *message, void */*userData*/ )
{
  unsigned int nBytes = message->size();
  for ( unsigned int i=0; i<nBytes; i++ )
    cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
  if ( nBytes > 0 )
    cout << "stamp = " << deltatime << std::endl;
}


class Midi {

private:
  string last_command = "Last Message";
  RtMidiIn *midiin = 0;
  bool message_ready = false;

public:

  // Returns true if all went OK.
  bool init(string desired_controller_name)
  {
    try {
      midiin = new RtMidiIn();

      unsigned int nPorts = midiin->getPortCount();

      for(unsigned int i = 0 ; i < nPorts ; i++)
      {
        string portName = midiin->getPortName(i);

        if(portName.find(desired_controller_name) != string::npos)
        {
          // Found the name - try to open the port number
          midiin->openPort(i);

          // Set our callback function.  This should be done immediately after
          // opening the port to avoid having incoming messages written to the
          // queue instead of sent to the callback function.
          midiin->setCallback(&myMidi_cb);

          // Don't ignore sysex, timing, or active sensing messages.
          midiin->ignoreTypes( false, false, false );

          // All set, so return
          return true;
        }
      }

    } catch ( RtMidiError &error ) {
        error.printMessage();
  }

    // If here then port was NOT opened properly, clean up
  //cleanup:
    delete midiin;
    return false;
  }

  bool messageReady()
  {
    // TODO
    return true;
  }

  string getMessage()
  {
     // TODO
    message_ready = false;
    return last_command;
  }

  void clearAllMessage()
  {
     // TODO
    message_ready = false;
  }

};


int main()
{

  Midi m = Midi();

  string controller_to_look_for = "Pico CircuitPython";
  if (m.init(controller_to_look_for) == false)
  {
    cout << "Init failed!!!!" << endl;
    return -1;
  }

  // if( m.messageReady() )
  // {
  //   cout << m.getMessage() << endl;
  // }

  cout << "\nReading MIDI input ... press <enter> to quit.\n";
    char input;
    cin.get(input);

  cout << "Finished.." << endl;
  return 0;
}


