/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"

using namespace pcde;

Task::Task(std::string const& name)
    : TaskBase(name)
    , driver()
{
}

Task::Task(std::string const& name, RTT::ExecutionEngine* engine)
    : TaskBase(name, engine)
    , driver()
{
}

Task::~Task()
{
}



void Task::processIO()
{
    /** Check whether a change of the MCS state is requested */
    bool mcs_status;
    if(_set_MCS_status.read(mcs_status) == RTT::NewData)
    {
        driver.setMCSStatus(mcs_status);
    }

    /** Check the MCS state and write it to output port */
    bool mcs_status_read;
    driver.getMCSStatus(mcs_status_read);
    _MCS_status.write(mcs_status_read);

    /** Read all the voltage and current channels and write them to the output ports */
    float voltage;
    float current;

    driver.getVA(VA_Request::CHANNEL::BATTERY_INPUT, voltage, current);
    _battery_voltage.write(voltage);
    _battery_current.write(current);
    
    driver.getVA(VA_Request::CHANNEL::EXTERNAL_INPUT, voltage, current);
    _external_voltage.write(voltage);
    _external_current.write(current);

    driver.getVA(VA_Request::CHANNEL::OUT_24VDC, voltage, current);
    _24VDC_voltage.write(voltage);
    _24VDC_current.write(current);

    driver.getVA(VA_Request::CHANNEL::OUT_12VOBC, voltage, current);
    _12VOBC_voltage.write(voltage);
    _12VOBC_current.write(current);

    driver.getVA(VA_Request::CHANNEL::OUT_12V, voltage, current);
    _12V_voltage.write(voltage);
    _12V_current.write(current);

    driver.getVA(VA_Request::CHANNEL::OUT_5V, voltage, current);
    _5V_voltage.write(voltage);
    _5V_current.write(current);

    driver.getVA(VA_Request::CHANNEL::PTU, voltage, current);
    _PTU_voltage.write(voltage);
    _PTU_current.write(current);

    driver.getVA(VA_Request::CHANNEL::MCS, voltage, current);
    _MCS_voltage.write(voltage);
    _MCS_current.write(current);

    /** Check battery percentage and write it to output port */
    int battery_percentage;
    driver.getBatteryPercentage(battery_percentage);
    _battery_percentage.write(battery_percentage);

}

/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See Task.hpp for more detailed
// documentation about them.

bool Task::configureHook()
{
    if (! TaskBase::configureHook())
        return false;

    /** Configure serial connection */
    SerialConfig config;
    config.port=_serial_port.get();
    config.baudrate=_serial_baudrate.get();
    config.read_timeout_ms=_serial_read_timeout.get();
    config.write_timeout_ms=_serial_write_timeout.get();

    driver.setupSerial(config);

    return true;
}
bool Task::startHook()
{
    if (! TaskBase::startHook())
        return false;
    return true;
}
void Task::updateHook()
{
    TaskBase::updateHook();

    processIO();
}
void Task::errorHook()
{
    TaskBase::errorHook();
}
void Task::stopHook()
{
    TaskBase::stopHook();
}
void Task::cleanupHook()
{
    TaskBase::cleanupHook();
}
