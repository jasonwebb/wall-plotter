#include <Arduino.h>
#include "Motor.cpp"

class Machine 
{
  private:
    int width;                  // width between motors
    float currentX, currentY;
    float targetX, targetY;
    float homeX, homeY;
    boolean moving = false;    
    
  public:
    Motor motorA, motorB;
    
    /*
     * Constructors
     */
    Machine() {}

    Machine(int _width)
    {
      width = _width;
    }

    void update()
    {
      if(currentX != targetX && currentY != targetY)
      {
        motorA.update();
        motorB.update();
        moving = true;
      } 
      else
      {
        moving = false;
      }
    }

    /*
     * Machine width get/set
     */
    int getWidth() { return width; }
    void setWidth(int _width) { width = _width; }

    /*
     * Current X/Y get/set
     */
    int getCurrentX() { return currentX; }
    int getCurrentY() { return currentY; }
    void setCurrentX(int _currentX) { currentX = _currentX; }
    void setCurrentY(int _currentY) { currentY = _currentY; }

    /*
     * Target X/Y get/set
     */
    int getTargetX() { return targetX; }
    int getTargetY() { return targetY; }
    void setTargetX(int _targetX) { targetX = _targetX; }
    void setTargetY(int _targetY) { targetY = _targetY; }

    /*
     * Conversions from X,Y to A,B
     */
    float getALengthAt(float x, float y)
    {
      
    }

    float getBLengthAt(float x, float y)
    {
      
    }

    float getXForLengths(float a, float b)
    {
      
    }

    float getYForLengths(float a, float b)
    {
      
    }
    

    /*
     * Is moving indicator
     */
    boolean isMoving() { return moving; }

    /*
     * Emergency stop
     */
    void stop()
    {
      motorA.stop();
      motorB.stop();
      moving = false;
    }
};

