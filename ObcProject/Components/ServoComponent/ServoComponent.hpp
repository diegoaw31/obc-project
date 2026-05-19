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
    bool isReady() const;
    int status() const;

private:

    int m_gpio;
    int m_status;
    bool m_ready;
    bool m_registered;
    static int s_users;
    static bool s_initialized;

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
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for angleIn
    void angleIn_handler(FwIndexType portNum,  //!< The port number
                         F32 angle             //!< the result of the operation
                         ) override;

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
    ServoDriver m_servo;
};

}  // namespace ObcProject

#endif
