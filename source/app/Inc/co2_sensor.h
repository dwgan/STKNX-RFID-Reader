#ifndef _CO2_SENSOR_H_
#define _CO2_SENSOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "type_def.h"
#include <stdint.h>
#include <stddef.h>

// CRC-16/MODBUS
#define POLY 0xA001 // This is 0x8005 reflected to LSB. 
#define CRC_INIT 0xFFFF

#define FUN_CODE_READ_COIL 0x44
  
#define INIT_PERIOD  50 //Init Period, this parameter is used to control sending period of the init command, 100 ms
#define LOOP_PERIOD  2000 //Loop Period, 1000 ms
  
#define COMMAND_LEN 20

typedef struct
{
    WORD16 co2_value;
    BYTE co2_valueflag;
    float temperature;
    BYTE temperatureflag;
} co2_sensor_knx_bus_t;
#pragma pack(1)
typedef struct
{
    BYTE address;
    BYTE func_code;
    BYTE reg_start_addr[2];
    BYTE byte_count;
    BYTE crc[2];
} modbus_master_t;

typedef struct
{
    BYTE address;
    BYTE func_code;
    BYTE byte_count;
    union
    {
        BYTE reg_value[16];
        BYTE *reg_value_p;
    };
    BYTE crc[2];
} modbus_slave_t;
#pragma pack()

extern unsigned char co2Buff[];
extern co2_sensor_knx_bus_t co2_sensor_knx_bus;
extern void co2_sensor_Loop();
extern void seneair_decoder( uint8_t nByte );
        
#ifdef __cplusplus
}
#endif

#endif /* _CO2_SENSOR_H_ */


