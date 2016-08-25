#ifndef Motor_h
#define Motor_h

#include <AccelStepper.h>
#include <Arduino.h>

class Motor
{
  private:
    boolean moving = false;
    boolean initialized = false;
    AccelStepper motor;

    // Physical characteristics
    int stepsPerRevolution;
    int microstepResolution;
    int pulleyDiameter;

    // Lengths
    float currentLength;
    float targetLength;

    // Electronics characteristics
    int dirPin, stepPin, enablePin;

  public:
    /*
     * Constructors
     */
    Motor() {}

    Motor(int _steps, int _microsteps, int _diameter, int _dirPin, int _stepPin, int _enablePin)
    {
      stepsPerRevolution = _steps;
      microstepResolution = _microsteps;
      pulleyDiameter = _diameter;

      dirPin = _dirPin;
      stepPin = _stepPin;
      enablePin = _enablePin;

      initialize();
    }

    void update()
    {
      if(initialized)
      {
        if(motor.distanceToGo() > 0)
        {
          motor.run();  
        }   
      }
    }

    /*
     * Initialize AccelStepper object
     * - Requires that dir, step and enable pins have all been set already
     */
    void initialize()
    {
      motor = AccelStepper(AccelStepper::DRIVER, stepPin, dirPin);
      motor.setEnablePin(enablePin);
      initialized = true;
    }

    /*
     * Step, dir and enable pin assignments
     */
    int getDirPin() { return dirPin; }
    void setDirPin(int _pin) { dirPin = _pin; }
    
    int getStepPin() { return stepPin; }
    void setStepPin(int _pin) { stepPin = _pin; }

    int getEnablePin() { return enablePin; }
    void setEnablePin(int _pin) { enablePin = _pin; }

    void setPins(int _dirPin, int _stepPin, int _enablePin)
    {
      dirPin = _dirPin;
      stepPin = _stepPin;
      enablePin = _enablePin;
    }
    
    /*
     * Steps per revolution get/set
     */
    int getStepsPerRevolution() { return stepsPerRevolution; }
    void setStepsPerRevolution(int _steps) { stepsPerRevolution = _steps; }

    /* 
     * Microstep resolution get/set 
     */
    int getMicrostepResolution() { return microstepResolution; }
    void setMicrostepResolution(int _resolution) { microstepResolution = _resolution; }

    /*
     * Pulley diameter get/set
     */
    int getPulleyDiameter() { return pulleyDiameter; }
    void setPulleyDiameter(int _diameter) { pulleyDiameter = _diameter; }

    /*
     * Current length get/set
     */
    float getCurrentLength() { return currentLength; }
    void setCurrentLength(float _length) { currentLength = _length; }

    /*
     * Target length get/set
     */
    float getTargetLength() { return targetLength; }
    void setTargetLength(float _length) { targetLength = _length; }

    /*
     * Distance to go (provided by AccelStepper)
     */
    float getDistanceToGo() { return motor.distanceToGo(); }

    /*
     * Is moving indicator
     */
    boolean isMoving() { return moving; }

    /* 
     *  Initialized indicator
     */
    boolean isInitialized() { return initialized; }
    void setInitialized(boolean _initialized) { initialized = _initialized; }

    /*
     * Emergency stop
     */
    void stop()
    {
      motor.stop();
      motor.disableOutputs();
      moving = false;
    }
};

#endif

