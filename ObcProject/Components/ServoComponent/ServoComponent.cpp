// ======================================================================
// \title  ServoComponent.cpp
// \author diegoalmendrow
// \brief  cpp file for ServoComponent component implementation class
// ======================================================================

#include "ObcProject/Components/ServoComponent/ServoComponent.hpp"

namespace ObcProject {
int ServoDriver::s_users = 0;
bool ServoDriver::s_initialized = false;

ServoDriver::ServoDriver(int gpio)
: m_gpio(gpio)
, m_status(PI_NOT_INITIALISED)
, m_ready(false)
, m_registered(false)
{
    if (!s_initialized) {
        const int initStatus = gpioInitialise();
        if (initStatus < 0) {
            m_status = initStatus;
            return;
        }
        s_initialized = true;
    }

    s_users += 1;
    m_registered = true;

    m_status = gpioSetMode(m_gpio, PI_OUTPUT);
    if (m_status < 0) {
        return;
    }

    m_status = gpioSetPWMfrequency(m_gpio, 50);
    if (m_status < 0) {
        return;
    }

    m_status = gpioServo(m_gpio, 1500);
    if (m_status < 0) {
        return;
    }

    m_status = 0;
    m_ready = true;
}

ServoDriver::~ServoDriver()
{
    if (!m_registered) {
        return;
    }

    (void) gpioServo(m_gpio, 0);
    s_users -= 1;

    if (s_users == 0 && s_initialized) {
        gpioTerminate();
        s_initialized = false;
    }
}

int ServoDriver::angleToPulseUs(float angle) const
{
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;

    return 1000 + (int)((angle / 180.0f) * 1000.0f);
}

int ServoDriver::setAngle(float angle)
{
    if (!m_ready) {
        return m_status;
    }

    const int pulse = angleToPulseUs(angle);
    m_status = gpioServo(m_gpio, pulse);

    return m_status;
}

bool ServoDriver::isReady() const
{
    return m_ready;
}

int ServoDriver::status() const
{
    return m_status;
}
// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

ServoComponent::ServoComponent(const char* const compName, int gpioPin)
    : ServoComponentComponentBase(compName)
    , m_servo(gpioPin)
{
    const int angle = 90;
    const int pigpioStatus = m_servo.setAngle(angle);
    if (pigpioStatus < 0) {
        this->log_WARNING_HI_PigpioError(pigpioStatus);
    } else {
        this->tlmWrite_Angle(angle);
        this->log_ACTIVITY_HI_AngleSet(angle);
    }
}

ServoComponent ::~ServoComponent() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void ServoComponent ::angleIn_handler(FwIndexType portNum, F32 angle) {
    if (angle < 0.0f || angle > 180.0f) {
        this->log_WARNING_HI_InvalidAngle(angle);
        return;
    }

    if (!m_servo.isReady()) {
        this->log_WARNING_HI_PigpioError(m_servo.status());
        return;
    }

    const int pigpioStatus = m_servo.setAngle(angle);
    if (pigpioStatus < 0) {
        this->log_WARNING_HI_PigpioError(pigpioStatus);
        return;
    }

    this->tlmWrite_Angle(angle);

    this->log_ACTIVITY_HI_AngleSet(angle);
}

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

    if (!m_servo.isReady()) {
        this->log_WARNING_HI_PigpioError(m_servo.status());
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
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
