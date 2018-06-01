#ifndef ALARMCONFIG_H
#define ALARMCONFIG_H

// Alarm software version
#define SOFTWARE_VERSION "0.1.1"

// When a sensor gets activated, for how long we keep it that way
#define SENSOR_ACTIVATED_TIME 5000

#define DEFAULT_USER_CODE 1234
#define DEFAULT_ADMIN_CODE 9999

// Time window after arming the alarm when sensors will be ignored
#define ALARM_JUST_ARMED_TIMER 20000

// List all reserved pins you don't want assigned to sensors
const uint8_t pinBlacklist[] = {0, 1, 2};

#endif /* ALARMCONFIG_H */

