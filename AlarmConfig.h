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
const uint8_t pinBlacklist[] = {0, 1, 2, 7};

// If you don't have a beeper (buzzer with driver connected to a pin) you can
// comment this line to save flash space.
#define ALARM_BEEPER_AVAILABLE

#endif /* ALARMCONFIG_H */

