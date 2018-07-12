#include "Alarm.h"
#include "OutputProcessor.h"

Alarm::Alarm(EEPROMHandler* eeprom)
{
    this->eeprom = eeprom;
    
    this->init();
}

void Alarm::init()
{
    this->numSensors = 0;
    this->status = ALARM_STATUS_DISARMED;
    this->operationMode = ALARM_OPERATION_MODE_USER;
    this->bell = false;
    this->armedTime = millis()-ALARM_ARM_GRACE_PERIOD_TIME;
    this->delayedSensorIndex = 0;

    this->delayedSensorBeepingOff();
    this->initSensors();
}

void Alarm::initSensors()
{
    if (this->eeprom->isFirstTime())
    {
        this->writeToEEPROM();
    }
    else
    {
        EEPROM.get(EEPROM_NUMSENSORS_ADDR, this->numSensors);
        EEPROM.get(EEPROM_SENSORS_ADDR, this->sensors);
        EEPROM.get(EEPROM_DELAYED_SENSOR, this->delayedSensorIndex);
    }    
    
    for (int x=0; x<this->numSensors; x++)
    {
        if (!(this->sensors[x].isWireless()))
        {
            pinMode(this->sensors[x].getSensorPin(), INPUT_PULLUP);
        }
    }
}

void Alarm::writeToEEPROM()
{
    EEPROM.put(EEPROM_NUMSENSORS_ADDR, this->numSensors);
    EEPROM.put(EEPROM_SENSORS_ADDR, this->sensors);
    EEPROM.put(EEPROM_DELAYED_SENSOR, this->delayedSensorIndex);
}

uint8_t Alarm::addSensor(Sensor sensor) 
{
    if (this->numSensors < MAX_SENSORS)
    {
        sensors[this->numSensors] = sensor;
        this->numSensors++;
        
        this->writeToEEPROM();
        
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
    
    if (status == ALARM_STATUS_ARMED)
    {
        this->armedTime = millis();
        this->delayedArmBeep = false;
        this->delayedSensorActive = false;
    }
    else
    {
        this->delayedSensorBeepingOff();
    }
}

void Alarm::delayedSensorBeepingOff()
{
    this->delayedSensorActive = false;
    this->delayedSensorActiveTime = millis()-ALARM_DISARM_GRACE_PERIOD_TIME;
    digitalWrite(BEEPER_PIN, !BEEPER_ACTIVE_PIN_SIGNAL);
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
    bool ringBell = false;
    
    if (millis()-this->armedTime > ALARM_ARM_GRACE_PERIOD_TIME)
    {
        if (this->checkWiredSensorsActive())
        {
            ringBell = true;
        }
        /*
        else
        {
            Serial.print(millis());
            Serial.print(" - ");
            Serial.println(this->delayedSensorActiveTime);
        }
        */ 

        if (this->checkWirelessSensorsActive())
        {
            ringBell = true;
        }
        
        if (ringBell && this->getStatus() == ALARM_STATUS_ARMED && !this->bell)
        {
            this->bell = true;
        }
    }
    else
    {
        this->delayedArmBeeping();
    }
}

void Alarm::delayedArmBeeping()
{
    unsigned long now = (unsigned long)(millis()/1000);
    
    if (now%2 == 1 && !this->delayedArmBeep)
    {
        OutputProcessor::beep(1, 0, 100);
        this->delayedArmBeep = true;
    }
    else if (now%2 == 0 && this->delayedArmBeep)
    {
        this->delayedArmBeep = false;
    }
}

bool Alarm::getBell()
{
    return this->bell;
}

bool Alarm::checkWirelessSensorsActive()
{
    WirelessRF wRFObj;
    String ID;
    bool returnValue = false;

    do 
    {
        ID = wRFObj.getRFDeviceRead();

        if (ID != "")
        {
            for (int x=0; x<this->numSensors; x++)
            {
                if (this->sensors[x].isOn() && this->sensors[x].isWireless())
                {
                    if (this->sensors[x].getSensorID() == ID 
                            || (this->delayedSensorActive && this->delayedSensorIndex == x+1))
                    {
                        if (!this->checkDelayedSensor(x))
                        {
                            continue;
                        }
                            
                        this->sensors[x].setActive(true);
                        returnValue = true;
                        break;
                    }
                    else if (!this->bell 
                            && (this->delayedSensorIndex != x+1 || !this->delayedSensorActive)
                            && this->sensors[x].getSensorInactiveID() == ID)
                    {
                        this->sensors[x].setActive(false);
                    }
                }
            }
        }
    }
    while (ID != "");
    
    return returnValue;
}

bool Alarm::checkWiredSensorsActive()
{
    bool returnValue = false;
    
    for (int x=0; x<this->numSensors; x++)
    {
        if (this->sensors[x].isOn() && !(this->sensors[x].isWireless()))
        {
            if (digitalRead(this->sensors[x].getSensorPin()) 
                    || (this->delayedSensorActive && this->delayedSensorIndex == x+1))
            {
                if (!this->checkDelayedSensor(x))
                {
                    continue;
                }
                
                this->sensors[x].setActive(true);
                returnValue = true;
                break;
            }
            else if (!this->bell 
                    && (this->delayedSensorIndex != x+1 || !this->delayedSensorActive))
            {
                this->sensors[x].setActive(false);
            }
        }
    }
    
    return returnValue;
}

bool Alarm::checkDelayedSensor(uint8_t x)
{
    if (this->delayedSensorIndex == x+1 
            && this->status == ALARM_STATUS_ARMED
            && !this->bell) 
    {
        if (!this->delayedSensorActive)
        {
            this->delayedSensorActive = true;
            this->delayedSensorActiveTime = millis();
            digitalWrite(BEEPER_PIN, BEEPER_ACTIVE_PIN_SIGNAL);
        }
        else if (millis()-this->delayedSensorActiveTime < ALARM_DISARM_GRACE_PERIOD_TIME)
        {
            return false;
        }
    }
    
    return true;
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
    if (index <= this->numSensors)
    {
        for (int x=index-1; x<(this->numSensors-1); x++)
        {
            this->sensors[x] = this->sensors[x+1];
        }
        
        this->sensors[this->numSensors-1].clearSensor();
        this->numSensors--;
        
        this->writeToEEPROM();
    }
}

void Alarm::setBell(bool bell)
{
    this->bell = bell;
}

bool Alarm::noSensorsActive()
{
    bool noSensorsActive = true;
    
    for (int x=1; x<=this->numSensors; x++)
    {
        if (this->sensors[x-1].isActive())
        {
            noSensorsActive = false;
            break;
        }
    }
    
    return noSensorsActive;
}

bool Alarm::isFreePin(uint8_t pin)
{
    bool isFree = true;
    
    for (int x=1; x<=this->numSensors; x++)
    {
        if (this->sensors[x-1].getSensorPin() == pin)
        {
            isFree = false;
            break;
        }
    }
    
    return isFree;
}

/*
 * 1 based index of the sensor we need to mark as delayed sensor
 */
void Alarm::setDelayedSensor(uint8_t index)
{
    this->delayedSensorIndex = index;
    this->writeToEEPROM();
}

/*
 * Get delayed sensor index in a 1 based index
 */
uint8_t Alarm::getDelayedSensorIndex()
{
    return this->delayedSensorIndex;
}
