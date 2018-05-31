#include "Alarm.h"

Alarm::Alarm()
{
    this->numSensors = 0;
    this->hasWirelessSensors = false;
    this->status = ALARM_STATUS_DISARMED;
    this->operationMode = ALARM_OPERATION_MODE_USER;
}

uint8_t Alarm::addSensor(Sensor sensor) 
{
    if (this->numSensors < MAX_SENSORS)
    {
        sensors[this->numSensors] = sensor;
        this->numSensors++;
        
        if (sensor.isWireless())
        {
            this->hasWirelessSensors = true;
        }
        
        return this->numSensors;
    }
    
    return 0;
}

uint8_t Alarm::getStatus()
{
    return this->status;
}

void Alarm::setStatus(uint8_t status)
{
    this->status = status;
}

uint8_t Alarm::getNumSensors()
{
    return this->numSensors;
}

Sensor* Alarm::getSensor(uint8_t sensorIdx)
{
    if (sensorIdx <= this->numSensors)
    {
        return &(this->sensors[sensorIdx-1]);
    }
    else
    {
        return NULL;
    }
}

void Alarm::loop()
{
    // Should be taken out to a private method when we expand the loop() work
    if (this->hasWirelessSensors)
    {
        WirelessRF wRFObj;
        String ID;
        Sensor* sensor;

        // Read until we don't have any Wireless sensor reporting
        do 
        {
            ID = wRFObj.getRFDeviceRead();

            if (ID != "")
            {
                for (int x=1; x<=this->numSensors; x++)
                {
                    if (sensors[x-1].isWireless() 
                        && sensors[x-1].getSensorID() == ID)
                    {
                        sensors[x-1].setActive(true);
                        break;
                    }
                    else if (sensors[x-1].isWireless() 
                        && sensors[x-1].getSensorInactiveID() == ID)
                    {
                        sensors[x-1].setActive(false);
                        break;
                    }
                }
            }
        }
        while (ID != "");
    }
}

uint8_t Alarm::getOperationMode()
{
    return this->operationMode;
}
