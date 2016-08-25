#include "Command.cpp"
#include "CommandParser.h"
#include "CommandRunner.cpp"
#include "Machine.cpp"
#include "Motor.cpp"

boolean debug = true;

// Custom objects
Machine machine;
CommandParser parser;
CommandRunner runner;

// Configuration variables ===================================
// Serial connection (if used for debug or command source)
int serialRate = 9600;

// CommandParser
int commandSource = CommandParser::USE_SERIAL;

// Machine
int machineWidth = 1500;  // (mm) effective distance between motors

// Stepper motors
int stepsPerRevolution = 200; // 200 steps/rev or 1.8deg
int microstepResolution = 32; // 1/32
int pulleyDiameter = 28;      // (mm) should be as accurate as possible!

// Stepper motor pin assignments
int dirPin_A = 0;
int stepPin_A = 1;
int enablePin_A = 2;

int dirPin_B = 3;
int stepPin_B = 4;
int enablePin_B = 5;
//==========================================================

void setup() {
  if(debug || commandSource == CommandParser::USE_SERIAL)
  {
    Serial.begin(serialRate);
  }
  
  // Set up the CommandParser with:
  // - Source
  parser.setSource(commandSource);

  // Set up the CommandRunner with:
  // - Reference to the Machine
//  runner.setMachine();
  
  // Set up the Machine with:
  // - Machine width
  // - Current position (?)
  machine.setWidth(machineWidth);

  // Set up A and B motors with:
  // - Steps per revolution
  // - Microstep resolution
  // - Pulley diameter
  // - Pins (dir, step, enable)
  // - Current length will be automatically set when machine position is set up above
  machine.motorA = Motor(stepsPerRevolution,
                         microstepResolution,
                         pulleyDiameter,
                         dirPin_A,
                         stepPin_A,
                         enablePin_A);

  machine.motorB = Motor(stepsPerRevolution,
                         microstepResolution,
                         pulleyDiameter,
                         dirPin_B,
                         stepPin_B,
                         enablePin_B);
}

void loop() {
  // If command runner is not busy, fetch another command from the parser
  if(!runner.isBusy())
  {
    // Try to get a new command
    parser.fetch();

    // When a new command is retrieved, pass it into the runner
    if(parser.hasNewCommand())
    {
      runner.runCommand(parser.getCommand());
    }
  } else {
    machine.update();
  }
}
