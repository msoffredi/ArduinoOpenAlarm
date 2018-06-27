#include "DisarmedMode.h"

DisarmedMode::DisarmedMode(Alarm* alarm, CommandPreprocessor* commPP, OutputProcessor* outP, EEPROMHandler* eeprom)
{
    this->alarm = alarm;
    this->commandPreprocessor = commPP;
    this->outProcessor = outP;
    this->eeprom = eeprom;
    this->adminCodeFailures = 0;
    this->adminCodeFailureTime = millis()-ADMIN_CODE_FAILURES_SUSPEND_TIME;
    
    this->initUserAndAdminCodes();
}

void DisarmedMode::initUserAndAdminCodes()
{
    if (this->eeprom->isFirstTime())
    {
        this->userCode = DEFAULT_USER_CODE;
        this->adminCode = DEFAULT_ADMIN_CODE;
        
        this->writeToEEPROM();
    }
    else
    {
        EEPROM.get(EEPROM_USER_CODE, this->userCode);
        EEPROM.get(EEPROM_ADMIN_CODE, this->adminCode);
    }
}

void DisarmedMode::writeToEEPROM()
{
    EEPROM.put(EEPROM_USER_CODE, this->userCode);
    EEPROM.put(EEPROM_ADMIN_CODE, this->adminCode);
}

void DisarmedMode::loop()
{
    AlarmCommand commandObj = this->commandPreprocessor->getNextCommand();
    
    if (commandObj.getCommand() != ALARM_COMMAND_NONE)
    {
        this->processCommand(commandObj);
    }

    // Alarm status
    //this->processAlarmStatus();
}

void DisarmedMode::processAlarmStatus()
{
    if (this->alarm->getNumSensors())
    {
        String statuses = "";
        
        for (int x=1; x<=this->alarm->getNumSensors(); x++)
        {
            statuses += (this->alarm->getSensor(x)->isActive()) ? "1" : "0"; 
        }
        
        this->outProcessor->processAlarmStatus(statuses);
    }
}

void DisarmedMode::processCommand(AlarmCommand commandObj)
{
    uint8_t command = commandObj.getCommand();
    
    if (this->alarm->getOperationMode() == ALARM_OPERATION_MODE_ADMIN)
    {
        if (command == ALARM_COMMAND_EXIT_ADMIN_MODE)
        {
            this->exitAdmin();
        }
        else if (command == ALARM_COMMAND_WIRELESS_LEARN) 
        {
            this->learnNewWirelessDevice();
        }
        else if (command == ALARM_COMMAND_WIRELESS_LEARN_2S) 
        {
            this->learnNewTwoStatesWirelessDevice();
        }
        else if (command == ALARM_COMMAND_LIST_SENSORS)
        {
            this->listSensors();
        }
        else if (command == ALARM_COMMAND_ADD_SENSOR)
        {
            this->addSensor(&commandObj);
        }
        else if (command == ALARM_COMMAND_DEL_SENSOR)
        {
            this->delSensor(&commandObj);
        }
        else if (command == ALARM_COMMAND_VERSION) 
        {
            this->outProcessor->processOutput(
                    AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_SOFTWARE_VERSION)) + F(SOFTWARE_VERSION))
                    );
        }
        else if (command == ALARM_COMMAND_SENSOR_OFF) 
        {
            this->sensorOnOff(&commandObj, false);
        }
        else if (command == ALARM_COMMAND_SENSOR_ON) 
        {
            this->sensorOnOff(&commandObj, true);
        }
        else if (command == ALARM_COMMAND_SENSOR_DELAYED) 
        {
            this->setSensorAsDelayed(&commandObj);
        }
        else if (command == ALARM_COMMAND_CHANGE_USER_CODE) 
        {
            this->changeUserCode(&commandObj);
        }
        else if (command == ALARM_COMMAND_CHANGE_ADMIN_CODE) 
        {
            this->changeAdminCode(&commandObj);
        }
        else if (command == ALARM_COMMAND_LIST_ONE_SENSOR) 
        {
            this->listOneSensor(&commandObj);
        }
    }
    else if (this->alarm->getOperationMode() == ALARM_OPERATION_MODE_USER)
    {
        if (command == ALARM_COMMAND_ALARM_STATUS)
        {
            this->processAlarmStatus();
        }
        else if (command == ALARM_COMMAND_ARM)
        {
            this->arm(&commandObj);
        }
        else if (command == ALARM_COMMAND_ENTER_ADMIN_MODE)
        {
            this->enterAdminMode(&commandObj);
        }
        else if (command == ALARM_COMMAND_NUMERIC_CODE)
        {
            commandObj.setCommand(ALARM_COMMAND_ARM);
            this->arm(&commandObj);
        }
    }
}

void DisarmedMode::listOneSensor(AlarmCommand* commandObj)
{
    Sensor* sensor;
    uint8_t idx = commandObj->getParameter(1).toInt();

    if (idx > 0 && idx <= this->alarm->getNumSensors())
    {
        sensor = this->alarm->getSensor(idx);

        // Wired: Sensor #<n>, status: {on/off}, Pin <p> [D]
        // Wireless: Sensor #<n>, ID <i>[, State 2 ID <i2>], status: {on/off} [D]
        this->outProcessor->processOutput(
                AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_LIST_SENSORS_SENSOR_ROW)) + idx 
                    + ((sensor->isWireless()) ? String(F(TEXT_LIST_SENSORS_ID)) + sensor->getSensorID() : "")
                    + ((sensor->isTwoStates()) ? String(F(TEXT_LIST_SENSORS_S2_ID)) + sensor->getSensorInactiveID() : "")
                    + F(TEXT_LIST_SENSORS_STATUS_TEXT) 
                    + (sensor->isOn() ? F(TEXT_LIST_SENSORS_STATUS_ON) : F(TEXT_LIST_SENSORS_STATUS_OFF))
                    + ((!sensor->isWireless()) ? String(F(TEXT_LIST_SENSORS_PIN)) + sensor->getSensorPin() : "")
                    + ((this->alarm->getDelayedSensorIndex() == idx) ? " D" : "")
                    )
                );
    }
    else
    {
        this->outProcessor->processOutput(
                AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_LIST_SENSOR_INVALID)))
                );
    }
}

void DisarmedMode::setSensorAsDelayed(AlarmCommand* commandObj)
{
    uint8_t idx = commandObj->getParameter(1).toInt();
    
    // 0 would mean no delayed sensor
    if (idx >= 0 && idx <= this->alarm->getNumSensors())
    {
        this->alarm->setDelayedSensor(idx);
        
        this->outProcessor->processOutput(
                AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_SENSOR_NEW_DELAYED)) + idx)
                );

        delay(200);
        OutputProcessor::beep(BEEP_COMMAND_ACCEPTED_REPETITIONS);
    }
    else
    {
        this->outProcessor->processOutput(
                AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_SENSOR_INVALID)))
                );
        
        OutputProcessor::beep(1, 0, BEEP_COMMAND_ERROR_DURATION);
    }
}

void DisarmedMode::exitAdmin()
{
    this->alarm->setOperationMode(ALARM_OPERATION_MODE_USER);
    this->outProcessor->processOutput(
            AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_EXIT_ADMIN_MODE)))
            );

    delay(200);
    OutputProcessor::beep(BEEP_COMMAND_ACCEPTED_REPETITIONS);
}

void DisarmedMode::sensorOnOff(AlarmCommand* commandObj, bool power)
{
    uint8_t idx = commandObj->getParameter(1).toInt();
    
    if (idx > 0 
            && idx <= this->alarm->getNumSensors() 
            && this->alarm->getSensor(idx)->isOn() != power)
    {
        this->alarm->getSensor(idx)->setPower(power);
        this->alarm->writeToEEPROM();
        
        this->outProcessor->processOutput(
                AlarmOutput(ALARM_OUTPUT_TEXT, 
                String(F(TEXT_ADMIN_SENSOR_ON_OFF_1)) + idx + F(TEXT_ADMIN_SENSOR_ON_OFF_2) + ((power) ? "on" : "off"))
                );
        
        delay(200);
        OutputProcessor::beep(BEEP_COMMAND_ACCEPTED_REPETITIONS);
    }
    else
    {
        OutputProcessor::beep(1, 0, BEEP_COMMAND_ERROR_DURATION);
    }
}

void DisarmedMode::changeUserCode(AlarmCommand* commandObj)
{
    String code = commandObj->getParameter(1);
    
    if (code.toInt() >= 0 && code.toInt() < 10000)
    {
        this->userCode = code.toInt();
        EEPROM.put(EEPROM_USER_CODE, this->userCode);
        this->eeprom->setMessage(MESSAGE_READ_USER_CODE);
        this->outProcessor->processOutput(
                AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_ADMIN_USER_CODE_CHANGED)) + code.toInt())
                );
        
        delay(200);
        OutputProcessor::beep(BEEP_COMMAND_ACCEPTED_REPETITIONS);
    }
    else
    {
        OutputProcessor::beep(1, 0, BEEP_COMMAND_ERROR_DURATION);
    }
}

void DisarmedMode::changeAdminCode(AlarmCommand* commandObj)
{
    String code = commandObj->getParameter(1);
    
    if (code.toInt() >= 0 && code.toInt() < 10000)
    {
        this->adminCode = code.toInt();
        EEPROM.put(EEPROM_ADMIN_CODE, this->adminCode);
        this->outProcessor->processOutput(
                AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_ADMIN_ADMIN_CODE_CHANGED)) + code.toInt())
                );
        
        delay(200);
        OutputProcessor::beep(BEEP_COMMAND_ACCEPTED_REPETITIONS);
    }
    else
    {
        OutputProcessor::beep(1, 0, BEEP_COMMAND_ERROR_DURATION);
    }
}

void DisarmedMode::enterAdminMode(AlarmCommand* commandObj)
{
    String code = commandObj->getParameter(1);
    
    // We verify if the admin mode is suspended for too many failures
    if (this->adminCodeFailures < ADMIN_CODE_FAILURES_MAX 
            || millis()-this->adminCodeFailureTime > ADMIN_CODE_FAILURES_SUSPEND_TIME)
    {
        if (this->adminCodeFailures == ADMIN_CODE_FAILURES_MAX)
        {
            this->adminCodeFailures = 0;
        }
        
        if (code.toInt() == this->adminCode)
        {
            this->adminCodeFailures = 0;
            this->alarm->setOperationMode(ALARM_OPERATION_MODE_ADMIN);
            this->outProcessor->processOutput(
                    AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_ENTER_ADMIN_MODE)))
                    );

            delay(200);
            OutputProcessor::beep(BEEP_COMMAND_ACCEPTED_REPETITIONS);
        }
        else
        {
            OutputProcessor::beep(1, 0, BEEP_COMMAND_ERROR_DURATION);
            this->adminCodeFailures++;
            this->adminCodeFailureTime = millis();
        }
    }
}

void DisarmedMode::listSensors()
{
    AlarmCommand command;
    uint8_t numSensors = this->alarm->getNumSensors();
            
    if (numSensors)
    {
        for (int x=1; x<=numSensors; x++)
        {
            command.setParameter(1, String(x));
            this->listOneSensor(&command);
        }
    }
    else
    {
        this->outProcessor->processOutput(
                AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_LIST_SENSORS_NO_SENSORS)))
                );
    }
}

void DisarmedMode::learnNewWirelessDevice()
{
    this->outProcessor->processOutput(
            AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_WIRELESS_LEARNING)))
            );

    WirelessRF wRFObj;
    String newID = wRFObj.getNewRFDeviceRead();
    Sensor sensor;
    uint8_t sensorNumber = 0;
    
    if (newID != "")
    {
        if (!this->sensorExistsInAlarm(newID))
        {
            sensor.setSensorID(newID);
            sensor.setPower(true);
            sensor.setWireless(true);

            sensorNumber = this->alarm->addSensor(sensor);

            this->outProcessor->processOutput(
                    AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_WIRELESS_SENSOR_ADDED)) 
                        + String(sensorNumber)
                        + F(TEXT_LIST_SENSORS_ID) + newID
                        )
                    );
            
            delay(200);
            OutputProcessor::beep(BEEP_COMMAND_ACCEPTED_REPETITIONS);
        }
        else
        {
            this->outProcessor->processOutput(
                    AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_WIRELESS_SENSOR_EXISTS)))
                    );
            
            OutputProcessor::beep(1, 0, BEEP_COMMAND_ERROR_DURATION);
        }
    }
    else
    {
        this->outProcessor->processOutput(
                AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_WIRELESS_TIMEOUT_LEARNING)))
                );
        
        OutputProcessor::beep(1, 0, BEEP_COMMAND_ERROR_DURATION);
    }
}

void DisarmedMode::learnNewTwoStatesWirelessDevice()
{
    this->outProcessor->processOutput(
            AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_WIRELESS_LEARNING2_1)))
            );

    WirelessRF wRFObj;
    String stateOneID, newID = wRFObj.getNewRFDeviceRead();
    Sensor sensor;
    uint8_t sensorNumber = 0;
    
    if (newID != "")
    {
        if (!this->sensorExistsInAlarm(newID))
        {
            sensor.setSensorID(newID);
            stateOneID = newID;
            sensor.setPower(true);
            sensor.setWireless(true);
            sensor.setTwoStates(true);

            delay(3000);
            this->outProcessor->processOutput(
                    AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_WIRELESS_LEARNING2_2)))
                    );

            newID = wRFObj.getNewRFDeviceRead();
            
            if (newID != "")
            {
                if (!this->sensorExistsInAlarm(newID))
                {
                    sensor.setSensorInactiveID(newID);
                    
                    delay(3000);
                    this->outProcessor->processOutput(
                            AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_WIRELESS_LEARNING2_3)))
                            );

                    newID = wRFObj.getNewRFDeviceRead();
                    
                    if (newID == stateOneID)
                    {
                        sensorNumber = this->alarm->addSensor(sensor);

                        this->outProcessor->processOutput(
                                AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_WIRELESS_SENSOR_ADDED)) 
                                    + String(sensorNumber)
                                    + F(TEXT_LIST_SENSORS_ID) + newID
                                    + F(TEXT_LIST_SENSORS_S2_ID) + sensor.getSensorInactiveID()
                                    )
                                );
                        
                        delay(200);
                        OutputProcessor::beep(BEEP_COMMAND_ACCEPTED_REPETITIONS);
                    }
                    else
                    {
                        this->outProcessor->processOutput(
                                AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_WIRELESS_SENSOR_S1_FAIL)))
                                );
                        
                        OutputProcessor::beep(1, 0, BEEP_COMMAND_ERROR_DURATION);
                    }
                }
                else
                {
                    this->outProcessor->processOutput(
                            AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_WIRELESS_SENSOR_EXISTS)))
                            );
                    
                    OutputProcessor::beep(1, 0, BEEP_COMMAND_ERROR_DURATION);
                }
            }
            else
            {
                this->outProcessor->processOutput(
                        AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_WIRELESS_TIMEOUT_LEARNING)))
                        );
                
                OutputProcessor::beep(1, 0, BEEP_COMMAND_ERROR_DURATION);
            }            
        }
        else
        {
            this->outProcessor->processOutput(
                    AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_WIRELESS_SENSOR_EXISTS)))
                    );
            
            OutputProcessor::beep(1, 0, BEEP_COMMAND_ERROR_DURATION);
        }
    }
    else
    {
        this->outProcessor->processOutput(
                AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_WIRELESS_TIMEOUT_LEARNING)))
                );
        
        OutputProcessor::beep(1, 0, BEEP_COMMAND_ERROR_DURATION);
    }
}

uint8_t DisarmedMode::sensorExistsInAlarm(String sensorID)
{
    bool returnValue = 0;
    Sensor* sensor;
    
    for (int x=1; x<=this->alarm->getNumSensors(); x++)
    {
        sensor = this->alarm->getSensor(x);
        
        if (sensor->getSensorID() == sensorID)
        {
            returnValue = x;
            break;
        }
    }
        
    return returnValue;
}

void DisarmedMode::addSensor(AlarmCommand* commandObj)
{
    String pin = commandObj->getParameter(1);
    Sensor sensor;
    uint8_t sensorNumber = 0;
    
    if (pin.toInt() >= 0 && pin.toInt() < NUM_DIGITAL_PINS)
    {
        if (this->pinNotInBlacklist(pin.toInt()))
        {
            if (this->alarm->isFreePin(pin.toInt()))
            {
                sensor.setPower(true);
                sensor.setSensorPin(pin.toInt());

                sensorNumber = this->alarm->addSensor(sensor);

                this->outProcessor->processOutput(
                        AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_SENSOR_ADDED)) 
                            + String(sensorNumber)
                            + F(TEXT_SENSOR_ADDED_PIN) + pin.toInt()
                            )
                        );

                pinMode(pin.toInt(), INPUT_PULLUP);
                
                delay(200);
                OutputProcessor::beep(BEEP_COMMAND_ACCEPTED_REPETITIONS);
            }
            else
            {
                this->outProcessor->processOutput(
                        AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_SENSOR_NOT_ADDED_USED_PIN)))
                        );
                
                OutputProcessor::beep(1, 0, BEEP_COMMAND_ERROR_DURATION);
            }
        }
        else
        {
            this->outProcessor->processOutput(
                    AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_SENSOR_NOT_ADDED_BLACKLIST)))
                    );
            
            OutputProcessor::beep(1, 0, BEEP_COMMAND_ERROR_DURATION);
        }
    }
}

bool DisarmedMode::pinNotInBlacklist(uint8_t pin)
{
    bool notInBL = true;
    
    for (int x=0; x<sizeof(pinBlacklist); x++)
    {
        if (pinBlacklist[x] == pin)
        {
            notInBL = false;
            break;
        }
    }
    
    return notInBL;
}

void DisarmedMode::delSensor(AlarmCommand* commandObj)
{
    uint8_t idx = commandObj->getParameter(1).toInt();
    
    if (idx > 0 && idx <= this->alarm->getNumSensors())
    {
        this->alarm->delSensor(idx);

        this->outProcessor->processOutput(
                AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_SENSOR_DELETED)) + idx)
                );
        
        delay(200);
        OutputProcessor::beep(BEEP_COMMAND_ACCEPTED_REPETITIONS);
    }
    else
    {
        this->outProcessor->processOutput(
                AlarmOutput(ALARM_OUTPUT_TEXT, String(F(TEXT_SENSOR_INVALID)) + idx)
                );
        
        OutputProcessor::beep(1, 0, BEEP_COMMAND_ERROR_DURATION);
    }
}

void DisarmedMode::arm(AlarmCommand* commandObj)
{
    String code = commandObj->getParameter(1);
    
    // TODO: add verification all sensors are inactive
    if (code.toInt() == this->userCode)
    {
        if (this->alarm->noSensorsActive())
        {
            this->alarm->setStatus(ALARM_STATUS_ARMED);
            
            this->outProcessor->processOutput(
                    AlarmOutput(ALARM_OUTPUT_ARM, String(F(TEXT_ALARM_ARMED)))
                    );
            
            delay(200);
            OutputProcessor::beep(BEEP_COMMAND_ACCEPTED_REPETITIONS);
        }
        else
        {
            this->outProcessor->processOutput(
                    AlarmOutput(ALARM_OUTPUT_ARM, String(F(TEXT_ALARM_NOT_ARMED_SENSORS_ACTIVE)))
                    );
            
            OutputProcessor::beep(1, 0, BEEP_COMMAND_ERROR_DURATION);
        }
    }
    else
    {
        OutputProcessor::beep(1, 0, BEEP_COMMAND_ERROR_DURATION);
    }
}
