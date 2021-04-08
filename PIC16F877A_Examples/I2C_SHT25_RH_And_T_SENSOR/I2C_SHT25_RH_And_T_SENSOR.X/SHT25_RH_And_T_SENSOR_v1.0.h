/* 
 * File:   SHT25_RH_And_T_SENSOR_v1.0.h
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 21 Mart 2021 Pazar, 04:03
 * Version: v1.0
 */

#ifndef SHT25_RH_And_T_SENSOR_V1_0_H
#define	SHT25_RH_And_T_SENSOR_V1_0_H
#include<stdint.h>
#ifdef	__cplusplus
extern "C" {
#endif
    
/*@FUNCTION_PROTOTYPES*/
    unsigned int I2C_SHT25_Temperature_Read(void);
    unsigned int I2C_SHT25_Relative_Humidity_Read(void);
    void I2C_SHT25_Soft_Reset(void);


#ifdef	__cplusplus
}
#endif

#endif	/* SHT25_RH_And_T_SENSOR_V1_0_H */

