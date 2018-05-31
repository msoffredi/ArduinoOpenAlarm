#include "Sensor.h"

Sensor::Sensor() 
{
    this->power = false;
    this->active = false;
    this->lastActive = 0;
    this->twoStates = false;
    
    this->wireless = false;
    this->sensorID = "";
    this->sensorInactiveID = "";
    
    // 255 means undefined as we can't have 255 wired sensors connected (not enough ports)
    this->sensorPin = 255;
}

bool Sensor::isOn() 
{
    return this->power;
}

bool Sensor::isActive() 
{
    if (this->active 
        && (this->isTwoStates() || (millis()-this->lastActive) <= SENSOR_ACTIVATED_TIME))
    {
        return true;
    }
    
    this->setActive(false);
    return false;
}

void Sensor::setPower(bool power) 
{
    this->power = power;
}

void Sensor::setActive(bool activeStatus) 
{
    this->active = activeStatus;
    
    if (activeStatus)
    {
        this->lastActive = millis();
    }
}

void Sensor::setSensorID(String ID) 
{
    this->sensorID = ID;
}

String Sensor::getSensorID() 
{
    return this->sensorID;
}

void Sensor::setWireless(bool wireless) 
{
    this->wireless = wireless;
}

bool Sensor::isWireless()
{
    return this->wireless;
}

void Sensor::setSensorPin(uint8_t pin)
{
    this->sensorPin = pin;
}

uint8_t Sensor::getSensorPin()
{
    return this->sensorPin;
}

String Sensor::getSensorInactiveID() 
{
    return this->sensorInactiveID;
}

void Sensor::setSensorInactiveID(String ID) 
{
    this->sensorInactiveID = ID;
}

void Sensor::setTwoStates(bool value)
{
    this->twoStates = value;
}

bool Sensor::isTwoStates()
{
    return this->twoStates;
}
