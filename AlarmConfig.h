#ifndef ALARMCONFIG_H
#define ALARMCONFIG_H

// Alarm software version
#define SOFTWARE_VERSION "0.1.2"

// When a sensor gets activated, for how long we keep it that way
#define SENSOR_ACTIVATED_TIME 5000

// These are the default User & Admin codes for a new alarm
#define DEFAULT_USER_CODE 1234
#define DEFAULT_ADMIN_CODE 9999

// Time window after arming the alarm when sensors will be ignored
#define ALARM_JUST_ARMED_TIMER 20000

// List all reserved pins you don't want assigned to sensors
const uint8_t pinBlacklist[] = {0, 1, 2, 7, 8};

// Time the alarm will wait before checking sensors after being armed
// Set to 0 if you don't want a grace period. Defaults to 20 seconds
#define ALARM_ARM_GRACE_PERIOD_TIME 20000

// When a delayed sensor is configured, this is the time the alarm will wait
// if the sensor is activated before triggering the bell/siren
#define ALARM_DISARM_GRACE_PERIOD_TIME 20000

// Maximum number of sensors the alarm can manage
// NOTE: Increasing this constant results in MORE MEMORY REQUIRED
#define MAX_SENSORS 10

// Beeper related constants
#define BEEPER_PIN 7
#define BEEPER_ACTIVE_PIN_SIGNAL LOW
#define BEEP_DURATION 30
#define BEEP_REPETITION_DURATION 100
#define BEEP_COMMAND_ERROR_DURATION 500
#define BEEP_COMMAND_ACCEPTED_REPETITIONS 3

// Bell related constants
#define BELL_PIN 8
#define BELL_ACTIVE_PIN_SIGNAL LOW

// General RF Wireless sensors constants
// Timeout in milliseconds for when we have to wait for communication to happen
#define WAIT_RF_TIMEOUT 20000

// Pin where the RF receiver will be connected to and has to be an interrupt 
// enabled pin.
#define RF_RECEIVE_PIN 2

// Maximum failures entering admin code before suspension
#define ADMIN_CODE_FAILURES_MAX 3
// Admin mode will be blocked for this number of milliseconds
#define ADMIN_CODE_FAILURES_SUSPEND_TIME 20000

#endif /* ALARMCONFIG_H */

