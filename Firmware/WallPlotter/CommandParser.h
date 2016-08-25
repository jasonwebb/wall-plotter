#include "Command.cpp"

class CommandParser
{
  private:
    int source;
    boolean newCommandAvailable = false;
    static Command command;

    /*
     * Creates a new Command from a String provided through some stream
     */
    void createCommandFromString(String line)
    {
      char type;
      int code;
      String param1, param2, param3;
      int firstSpaceIndex = line.indexOf(' ',1);
      int secondSpaceIndex = line.indexOf(' ',firstSpaceIndex);
          
      switch(line.charAt(0))
      {        
        case 'G':
          type = 'G';                    
          break;
          
        case 'M':
          type = 'M';
          break;
          
        default:
          // Not valid
          if(source == USE_SERIAL)
          {
            Serial.print("Invalid command type: ");
            Serial.println(line);
          }
          
          return;
          break;
      }

      // No parameters
      if(firstSpaceIndex < 0)
      {
        code = line.substring(1,line.length()-1).toInt();
        command = Command(type, code);
      } 
      
      // At least one parameter
      else    
      {
        code = line.substring(1,firstSpaceIndex).toInt();

        // Get first parameter
        param1 = line.substring(firstSpaceIndex,secondSpaceIndex);

        // Get second parameter, if there is one
        if(secondSpaceIndex < 0)
        {
          param2 = line.substring(secondSpaceIndex,line.length()-1);
          command = Command(type,code,param1,param2);
        } 
        else
        {
          command = Command(type,code,param1);
        }
      }
    }
    
  public:
    const static int USE_SERIAL = 0;
    const static int USE_SD = 1;

    /*
     * Constructors
     */
    CommandParser() {}
    
    CommandParser(int _source)
    {
      source = _source;
    }

    /*
     * Try to fetch a new command from the specified source
     */
    void fetch()
    {
      switch(source)
      {
        case USE_SERIAL:
          // If serial data is available, read it all in and create a new Command object
          while(Serial.available())
          {
            String line = Serial.readStringUntil('\n');
            createCommandFromString(line);
          }          
          
          break;
        case USE_SD:
          // Fetch a new line from the SD card and read it into a new Command object

//          newCommandAvailable = true;
          break;
      }
    }

    /*
     * New command is ready for running
     */
    boolean hasNewCommand()
    {
      return newCommandAvailable;
    }

    /*
     * Get the current command
     */
    Command getCommand() { return command; }
    
    /* 
     * Get/set source 
     */
    int getSource() { return source; }
    void setSource(int _source) { source = _source; }
};

