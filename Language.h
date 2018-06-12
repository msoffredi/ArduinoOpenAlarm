#ifndef LANGUAGE_H
#define LANGUAGE_H

#define TEXT_INITIALIZING "Initializing Alarm..."
#define TEXT_INIT_DONE "Ready!"

#define TEXT_SOFTWARE_VERSION "Ver "

#define TEXT_LIST_SENSORS_SENSOR_ROW "Sensor #"
#define TEXT_LIST_SENSORS_STATUS_TEXT ", status: "
#define TEXT_LIST_SENSORS_STATUS_ON "on"
#define TEXT_LIST_SENSORS_STATUS_OFF "off"
#define TEXT_LIST_SENSORS_NO_SENSORS "No sensors found"

#define TEXT_ALARM_STATUS "Alarm status: "
#define TEXT_ALARM_ARMED "Alarm armed"
#define TEXT_ALARM_DISARMED "Alarm disarmed"
#define TEXT_ALARM_NOT_ARMED_SENSORS_ACTIVE "Alarm not armed. All sensors must be inactive."

#define TEXT_SENSOR_ADDED "Sensor added. Sensor #"
#define TEXT_SENSOR_ADDED_PIN ", attached to pin "
#define TEXT_SENSOR_DELETED "Deleted sensor #"
#define TEXT_SENSOR_NOT_ADDED_BLACKLIST "Sensor not added. Pin in blacklist."
#define TEXT_SENSOR_NOT_ADDED_USED_PIN "Sensor not added. Used pin."

#define TEXT_ENTER_ADMIN_MODE "Admin mode on"
#define TEXT_EXIT_ADMIN_MODE "No longer in admin mode"
#define TEXT_ADMIN_USER_CODE_CHANGED "User code changed to "
#define TEXT_ADMIN_ADMIN_CODE_CHANGED "Admin code changed to "

#define TEXT_LIST_SENSORS_ID ", ID "
#define TEXT_LIST_SENSORS_S2_ID ", State 2 ID "
#define TEXT_LIST_SENSORS_PIN ", Pin "

// Wireless RF texts 
#define TEXT_WIRELESS_LEARNING "Wireless learning mode activated. Waiting for new sensor to transmit..."
#define TEXT_WIRELESS_LEARNING2_1 "Wireless 2 states learning mode activated. Waiting for new sensor to transmit state 1..."
#define TEXT_WIRELESS_LEARNING2_2 "Waiting for new sensor to transmit state 2..."
#define TEXT_WIRELESS_LEARNING2_3 "Waiting for new sensor to re-transmit state 1 to finish"
#define TEXT_WIRELESS_SENSOR_S1_FAIL "State 1 ID does not match recorded one. Sensor not added."
#define TEXT_WIRELESS_SENSOR_ADDED "Wireless sensor added. Sensor #"
#define TEXT_WIRELESS_SENSOR_EXISTS "Wireless sensor already registered!"
#define TEXT_WIRELESS_TIMEOUT_LEARNING "Timeout while learning new sensor!"

#define TEXT_ADMIN_SENSOR_ON_OFF_1 "Sensor "
#define TEXT_ADMIN_SENSOR_ON_OFF_2 " was turned "

#endif /* LANGUAGE_H */
