// ======================================================================
// \title  ServoComponent.hpp
// \author diegoalmendrow
// \brief  hpp file for ServoComponent component implementation class
// ======================================================================

#ifndef ObcProject_ServoComponent_HPP
#define ObcProject_ServoComponent_HPP

#include "ObcProject/Components/ServoComponent/ServoComponentComponentAc.hpp"
#include <pigpio.h>

namespace ObcProject {

class ServoDriver {

public:

    ServoDriver(int gpio);
    ~ServoDriver();

    int setAngle(float angle);

private:

    int m_gpio;

    int angleToPulseUs(float angle) const;

};

class ServoComponent final : public ServoComponentComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct ServoComponent object
    ServoComponent(const char* const compName, int gpioPin = 18  //!< The component name
    );

    //! Destroy ServoComponent object
    ~ServoComponent();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command TODO
    //!
    //! TODO
    void SET_ANGLE_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                         U32 cmdSeq,            //!< The command sequence number
                         F32 angle              //!< The angle to set
                         ) override;
  
  private:
    ServoDriver m_servo;  // GPIO pin 18 (PWM0)
};

}  // namespace ObcProject

#endif
