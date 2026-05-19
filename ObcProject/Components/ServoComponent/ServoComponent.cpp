// ======================================================================
// \title  ServoComponent.cpp
// \author diegoalmendrow
// \brief  cpp file for ServoComponent component implementation class
// ======================================================================

#include "ObcProject/Components/ServoComponent/ServoComponent.hpp"

namespace ObcProject {

ServoDriver::ServoDriver(int gpio)
: m_gpio(gpio)
{
    gpioInitialise();
    gpioSetMode(m_gpio, PI_OUTPUT);
    gpioSetPWMfrequency(m_gpio, 50);
    gpioServo(m_gpio, 1500);
}

ServoDriver::~ServoDriver()
{
    (void) gpioServo(m_gpio, 0);
    gpioTerminate();
}

int ServoDriver::angleToPulseUs(float angle) const
{
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;

    return 1000 + (int)((angle / 180.0f) * 1000.0f);
}

int ServoDriver::setAngle(float angle)
{
    const int pulse = angleToPulseUs(angle);
    return gpioServo(m_gpio, pulse);
}

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

ServoComponent::ServoComponent(const char* const compName, int gpioPin)
    : ServoComponentComponentBase(compName)
    , m_servo(gpioPin)
{}

ServoComponent ::~ServoComponent() {}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void ServoComponent::SET_ANGLE_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, F32 angle)
{
    if (angle < 0.0f || angle > 180.0f) {

        this->log_WARNING_HI_InvalidAngle(angle);

        this->cmdResponse_out(
            opCode,
            cmdSeq,
            Fw::CmdResponse::VALIDATION_ERROR
        );

        return;
    }

    const int pigpioStatus = m_servo.setAngle(angle);

    if (pigpioStatus < 0) {
        this->log_WARNING_HI_PigpioError(pigpioStatus);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }

    this->tlmWrite_Angle(angle);

    this->log_ACTIVITY_HI_AngleSet(angle);

    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // namespace ObcProject
