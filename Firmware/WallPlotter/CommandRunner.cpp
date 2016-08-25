#include "Command.cpp"

#include <Arduino.h>

class CommandRunner
{
  private:
    boolean busy = false;
    boolean hasNextCommand = false;
    Command currentCommand;

  public:
    /*
     * Constructors
     */
    CommandRunner() {}    

    /*
     * 
     */
    void runCommand(Command _command)
    {
      currentCommand = _command;
      
      switch(currentCommand.getType())
      {
        case 'G':
          switch(currentCommand.getCode())
          {
            case 0:   // Rapid move: G0 [X###] [Y###]
//              machine.setTargetX( currentCommand.getParameterValue(1) );
//              machine.setTargetY( currentCommand.getParameterValue(2) );
//              machine.setSpeed( [fast speed] );
              break;
              
            case 1:   // Linear move: G1 [X###] [Y###]
//              machine.setTargetX( currentCommand.getParameterValue(1) );
//              machine.setTargetY( currentCommand.getParameterValue(2) );
//              machine.setSpeed( [slow speed] );
              break;

            case 4:   // Dwell: G4 [P####] (in milliseconds)
//              delay( currentCommand.getParameterValue(1) );
              break;

            case 28:  // Home axes
//              machine.home();
              break;
              
            case 90:  // Use absolute coordinates
              break;

            case 91:  // Use relative coordinates
              break;
              
            default:  // Invalid code
              break;
          }
          break;
          
        case 'M':
          switch(currentCommand.getCode()) {
            case 112: // Emergency stop
//              machine.stop();
              break;

            default:  // Invalid code
              break;
          }
          break;
          
        default:  // Invalid type
          break;
      }
    }

    /*
     * Busy indicator get/set
     */
    boolean isBusy() { return busy; }
    void setBusy(boolean _busy) { busy = _busy; }
};

