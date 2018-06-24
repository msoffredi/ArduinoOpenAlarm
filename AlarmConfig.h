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

#endif /* ALARMCONFIG_H */

