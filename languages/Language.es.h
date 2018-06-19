#ifndef LANGUAGE_H
#define LANGUAGE_H

#define TEXT_INITIALIZING "Inicializando Alarma..."
#define TEXT_INIT_DONE "Listo!"

#define TEXT_SOFTWARE_VERSION "Ver "

#define TEXT_LIST_SENSORS_SENSOR_ROW "Sensor #"
#define TEXT_LIST_SENSORS_STATUS_TEXT ", estado: "
#define TEXT_LIST_SENSORS_STATUS_ON "on"
#define TEXT_LIST_SENSORS_STATUS_OFF "off"
#define TEXT_LIST_SENSORS_NO_SENSORS "No hay sensores"

#define TEXT_ALARM_STATUS "Estado Alarma: "
#define TEXT_ALARM_ARMED "Alarma armada"
#define TEXT_ALARM_DISARMED "Alarma desarmada"
#define TEXT_ALARM_NOT_ARMED_SENSORS_ACTIVE "Alarma no armada. Todos los sensores deben estar inactivos."

#define TEXT_SENSOR_ADDED "Sensor agregado. Sensor #"
#define TEXT_SENSOR_ADDED_PIN ", conectado al pin "
#define TEXT_SENSOR_DELETED "Borrado sensor #"
#define TEXT_SENSOR_NOT_ADDED_BLACKLIST "Sensor no agregado. Pin prohibido."
#define TEXT_SENSOR_NOT_ADDED_USED_PIN "Sensor no agregado. Pin tomado."
#define TEXT_SENSOR_INVALID "No se puede borrar. Sensor invalido #"

#define TEXT_ENTER_ADMIN_MODE "Modo Admin on"
#define TEXT_EXIT_ADMIN_MODE "Modo admin off"
#define TEXT_ADMIN_USER_CODE_CHANGED "Codigo de usuario cambiado a "
#define TEXT_ADMIN_ADMIN_CODE_CHANGED "Codigo de administrador cambiado a "

#define TEXT_LIST_SENSORS_ID ", ID "
#define TEXT_LIST_SENSORS_S2_ID ", Estado 2 ID "
#define TEXT_LIST_SENSORS_PIN ", Pin "

// Wireless RF texts 
#define TEXT_WIRELESS_LEARNING "Modo aprendizaje inalambrico activado. Esperando que transmita un nuevo sensor..."
#define TEXT_WIRELESS_LEARNING2_1 "Modo aprendizaje inalambrico de 2 estados activado. Esperando que un nuevo sensor transmita el estado 1..."
#define TEXT_WIRELESS_LEARNING2_2 "Esperando que el nuevo sensor transmita el estado 2..."
#define TEXT_WIRELESS_LEARNING2_3 "Esperando que el nuevo sensor re-transmita el estado 1 para finalizar"
#define TEXT_WIRELESS_SENSOR_S1_FAIL "El ID del estado 1 no concuerda con el registrado. Sensor no agregado."
#define TEXT_WIRELESS_SENSOR_ADDED "Sensor wireless agregado. Sensor #"
#define TEXT_WIRELESS_SENSOR_EXISTS "Sensor wireless ya existe!"
#define TEXT_WIRELESS_TIMEOUT_LEARNING "Tiempo limite alcanzado en modo aprendizaje!"

#define TEXT_ADMIN_SENSOR_ON_OFF_1 "El sensor "
#define TEXT_ADMIN_SENSOR_ON_OFF_2 " fue cambiado a "

#endif /* LANGUAGE_H */
