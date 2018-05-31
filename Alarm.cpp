#include "Alarm.h"

Alarm::Alarm()
{
    this->numSensors = 0;
    this->status = ALARM_STATUS_DISARMED;
    this->operationMode = ALARM_OPERATION_MODE_USER;
}

uint8_t Alarm::addSensor(Sensor sensor) 
{
    if (this->numSensors < MAX_SENSORS)
    {
        sensors[this->numSensors] = sensor;
        this->numSensors++;
        
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
    WirelessRF wRFObj;
    String ID;
    Sensor* sensor;

    // We check wired sensors first
    for (int x=1; x<=this->numSensors; x++)
    {
        if (!(this->sensors[x-1].isWireless()))
        {
            if (digitalRead(this->sensors[x-1].getSensorPin()))
            {
                this->sensors[x-1].setActive(true);
            }
            else
            {
                this->sensors[x-1].setActive(false);
            }
        }
    }
    
    // Read until we don't have any Wireless sensor reporting
    do 
    {
        ID = wRFObj.getRFDeviceRead();

        if (ID != "")
        {
            for (int x=1; x<=this->numSensors; x++)
            {
                if (this->sensors[x-1].isWireless() 
                    && this->sensors[x-1].getSensorID() == ID)
                {
                    this->sensors[x-1].setActive(true);
                    break;
                }
                else if (this->sensors[x-1].isWireless() 
                    && this->sensors[x-1].getSensorInactiveID() == ID)
                {
                    this->sensors[x-1].setActive(false);
                    break;
                }
            }
        }
    }
    while (ID != "");
}

uint8_t Alarm::getOperationMode()
{
    return this->operationMode;
}

void Alarm::setOperationMode(uint8_t operationMode)
{
    this->operationMode = operationMode;
}

void Alarm::delSensor(uint8_t index)
{
    if (index < this->numSensors)
    {
        for (int x=index-1; x<(this->numSensors-1); x++)
        {
            this->sensors[x] = this->sensors[x+1];
        }
    }
    
    this->numSensors--;
}
