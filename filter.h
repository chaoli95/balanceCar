#ifndef __FILTER_H
#define __FILTER_H
  /**************************************************************************

**************************************************************************/
extern volatile float angle, angle_dot;
void Kalman_Filter(float Accel,float Gyro);		
float Yijielvbo(float angle_m, float gyro_m);
#endif
