#ifndef ALARMCONFIG_H
#define ALARMCONFIG_H

////////////////////////////////////
// HERE BEGINS CONFIGURATION AREA //
////////////////////////////////////

/*
 * This configuration variable tells the alarm for how long a sensor will be 
 * internally kept as active after being triggered and despite of the later 
 * status. This is for example when you activate a sensor and you see the 
 * monitoring light stays on for a few seconds.
 * The time in milliseconds and it defaults to 3 seconds (3000 milliseconds)
 */
#define SENSOR_ACTIVATED_TIME 3000

/*
 * When a new alarm is installed these are the codes you need to use for 
 * entering Admin mode and for arming/disarming the alarm. They can be changed
 * whenever you want (refere to operation manual), but these are the factory 
 * initial ones.
 * Due to internal validations, they should be numeric and within the range of
 * 0-9999.
 */
#define DEFAULT_USER_CODE 1234
#define DEFAULT_ADMIN_CODE 9999

/*
 * Here you should list all pins of your Arduino board you use for something 
 * else and don't want your alarm to use them for sensors. Pins listed here will
 * be considered during validation when you add new sensors to your alarm.
 * We propose 0 & 1 for USB communication, 2 for RF receiver and 7 & 8 for 
 * a buzzer and a siren, but feel free to customize with your own selection.
 */
const uint8_t pinBlacklist[] = {0, 1, 2, 7, 8};

/*
 * This is a typical alarm feature where the alarm will give you a few seconds
 * to leave the covered place before finally effectively arm itself. This is
 * to give you time to arm the alarm, leave the place even activating one or 
 * more sensors and still have the alarm fully armed after some time. This 
 * "time" is configurable and it defaults to 20 seconds (20000 milliseconds).
 * Set to 0 if you want the alarm to immediately starts checking sensors.
 */
#define ALARM_ARM_GRACE_PERIOD_TIME 20000

/*
 * When you configure a delayed sensor in your alarm, that's the sensor you are
 * allowed to trigger without triggering the alarm siren right away. Instead,
 * the alarm will give you some time to reach the alarm keypad (if any) and 
 * disarm it gracefully. This time the alarm will wait is configurable in 
 * milliseconds and defaults to 20 seconds (20000 milliseconds).
 * 
 * NOTE: this configuration has no effect if you don't define a delayed sensor
 */
#define ALARM_DISARM_GRACE_PERIOD_TIME 20000

/*
 * The following is the maximum number of sensors allowed to be added to the 
 * alarm anytime.
 * 
 * NOTE: be aware that increasing this number will increase the required memory
 * used by the alarm. Specially important if you plan to run the alarm in an 
 * Arduino UNO board.
 */
#define MAX_SENSORS 10

/*
 * The alarm beeper is optional, but if you plan to integrate one, the next few 
 * configurations may be useful to you. 
 */
// Pin the beeper is connected to
#define BEEPER_PIN 7
// Default signal the beeper will activate upon
#define BEEPER_ACTIVE_PIN_SIGNAL LOW
// This is the default duration of a short beep in milliseconds
#define BEEP_DURATION 30
// This is the delay between beep repetitions (when used) in milliseconds
#define BEEP_REPETITION_DURATION 100
// This is how long an error beep (long beep) will last in milliseconds
#define BEEP_COMMAND_ERROR_DURATION 500
// This is how many repeated beeps a successful command will trigger
#define BEEP_COMMAND_ACCEPTED_REPETITIONS 3

/*
 * Although a siren (internally called "bell") is also optional, I would expect
 * most alarms to have one connected to it. The next 2 configurations are 
 * related to it.
 */
// Pin the siren is connected to
#define BELL_PIN 8
// Default signal the siren will activate upon
#define BELL_ACTIVE_PIN_SIGNAL LOW

/*
 * If you plan to integrate wireless sensors to your alarm, you will probably
 * be working with RF modules and sensors. The following configurations are 
 * related to wireless integration.
 */
// Time the alarm will wait for a new sensor to transmit when learning new
// wireless sensors.
#define WAIT_RF_TIMEOUT 20000

// Pin the RF receiver is connected to. Typically, an interrupt enabled pin.
#define RF_RECEIVE_PIN 2

/*
 * This is a configuration that states how many consecutive failures entering
 * the admin code the alarm will allow before penalizing you.
 */
#define ADMIN_CODE_FAILURES_MAX 3

/*
 * And this is for how long you won't be allowed to enter admin mode after being
 * penalized. Time in milliseconds and defaults to 20 seconds (20000 
 * milliseconds)
 */
#define ADMIN_CODE_FAILURES_SUSPEND_TIME 20000

//////////////////////////////////
// HERE ENDS CONFIGURATION AREA //
//////////////////////////////////

// Alarm software version
#define SOFTWARE_VERSION "0.1.2"

#endif /* ALARMCONFIG_H */
