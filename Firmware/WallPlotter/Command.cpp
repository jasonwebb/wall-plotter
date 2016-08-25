#ifndef Command_h
#define Command_h

#include <Arduino.h>

class Command
{
  private:
    int line;   // line number N[###]
    char type;  // 'G' or 'M'
    int code;
    const static int maxParameters = 3;
    String parameters[maxParameters]; // ex. "X100"

  public:
    /*
     * Constructors
     */
    Command() {}

    Command(char _type, int _code)
    {
      type = _type;
      code = _code;
    }
    
    Command(char _type, int _code, String _param1)
    {
      type = _type;
      code = _code;
      parameters[0] = _param1;
    }

    Command(char _type, int _code, String _param1, String _param2)
    {
      type = _type;
      code = _code;
      parameters[0] = _param1;
      parameters[1] = _param2;
    }

    Command(char _type, int _code, String _param1, String _param2, String _param3)
    {
      type = _type;
      code = _code;
      parameters[0] = _param1;
      parameters[1] = _param2;
      parameters[2] = _param3;
    }

    /*
     * Type get/set
     */
    char getType() { return type; }
    void setType(char _type) { type = _type; }

    /*
     * Code get/set
     */
    int getCode() { return code; }
    void setCode(int _code) { code = _code; }

    /*
    * Line number get/set
    */
    int getLineNumber() { return line; }
    void setLineNumber(int _line) { line = _line; }

    /*
    * Parameters get/set
    */
    String getParameter(int _num) { return parameters[_num - 1]; }
    void setParameter(int _num, String _param) { parameters[_num - 1] = _param; }

    /*
     * Parameter value (parameter minus first character) get
     */
    float getParameterValue(int _num)
    {
      if(_num > maxParameters)
        return -1;
        
      return parameters[_num - 1].substring(1,parameters[_num - 1].length()).toFloat();
    }

    /*
     * Report the presence of a specified parameter
     */
    boolean hasParameter(int _num)
    {
      if(_num <= maxParameters && parameters[_num - 1].length() > 0)
      {
        return true;
      }
      
      return false;
    }    
};

#endif

