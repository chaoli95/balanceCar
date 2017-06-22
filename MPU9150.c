///////////////////////////////////////////////////////////////////////////////
//   Malcolm Ma
//   UT Dallas
//   Dec 2015
//   Built with CCSv6.1.1
//
//	 Version: v0.1
//
//  Description:
//  Basic I2C driver for MPU9150
//	MPU9150 is basically a MPU6050 integrated with a magnetometer,that's why
//	so many MPU6050 namings are used here.However,namings can be done in a
//	better way.This is due to the tight schedule.
//
//
//                                /|\  /|\
//                MSP430F5529     10k  10k      MSP430F5529
//                   slave         |    |         master
//             -----------------   |    |   -----------------
//           -|XIN  P3.0/UCB0SDA|<-|----+->|P3.0/UCB0SDA  XIN|-
//            |                 |  |       |                 |
//           -|XOUT             |  |       |             XOUT|-
//            |     P3.1/UCB0SCL|<-+------>|P3.1/UCB0SCL     |
//            |                 |          |                 |
///////////////////////////////////////////////////////////////////////////////
#include <msp430.h>
#include "I2C.h"
#include "MPU9150.h"



//Variables where our values can be stored
//static int mgn[3];
static int accl[3];
static int gyro[3];
static unsigned char TxData[] =              // Table of data to transmit
{0,0,0};


void MPU6050_WriteReg(unsigned char addr,unsigned char data)
{
  setI2CAddress(MPU6050_SLAVE_ADDRESS);
  TxData[0]=addr;
  TxData[1]=data;
  sendI2C(TxData,2,STOP);
}

void MPU6050_ReadData(unsigned char reg_add,unsigned char*Read,unsigned char num)
{
  setI2CAddress(MPU6050_SLAVE_ADDRESS);
    //read data
  TxData[0]=reg_add;
  sendI2C(TxData,1,NO_STOP);
  readI2CBytes(num,Read);
}


void initMPU9150(void)
{
  //MPU6050_WriteReg(MPU6050_RA_PWR_MGMT_1, 0x00);       //wake up
  //MPU6050_WriteReg(MPU6050_RA_SMPLRT_DIV , 0x07);     //gyro sampling rate
  //MPU6050_WriteReg(MPU6050_RA_CONFIG , 0x06);
  //MPU6050_WriteReg(MPU6050_RA_ACCEL_CONFIG , 0x01);   //accel works at 16G
  //MPU6050_WriteReg(MPU6050_RA_GYRO_CONFIG, 0x18);     //gyro 2000deg/s

	MPU6050_WriteReg(MPU6050_RA_PWR_MGMT_1,0x02);//…Ë÷√ ±÷”
	MPU6050_WriteReg(MPU6050_RA_GYRO_CONFIG, 0x18);		//gyro 2000 deg/s
	MPU6050_WriteReg(MPU6050_RA_ACCEL_CONFIG , 0x00);  //accel works at 2g
	MPU6050_WriteReg(MPU6050_RA_INT_ENABLE, 0x01);
	MPU6050_WriteReg(MPU6050_RA_CONFIG , 0x01);
//	MPU6050_WriteReg(MPU6050_RA_INT_PIN_CFG , 0x30);
	MPU6050_WriteReg(MPU6050_RA_SMPLRT_DIV , 0x00);
}


u8 readMPU6050ID(void)
{
  unsigned char Re = 0;
  MPU6050_ReadData(MPU6050_RA_WHO_AM_I,&Re,1);
  return Re;
}

void readMPU6050Acc(int *accData)
{
    unsigned char buf[6];
    MPU6050_ReadData(MPU6050_ACC_OUT, buf, 6);
    accData[0] = (buf[0] << 8) | buf[1];
    accData[1] = (buf[2] << 8) | buf[3];
    accData[2] = (buf[4] << 8) | buf[5];
}

void readMPU6050Gyro(int *gyroData)
{
    unsigned char buf[6];
    MPU6050_ReadData(MPU6050_GYRO_OUT,buf,6);
    gyroData[0] = (buf[0] << 8) | buf[1];
    gyroData[1] = (buf[2] << 8) | buf[3];
    gyroData[2] = (buf[4] << 8) | buf[5];
}

void readMPU6050GyroFloat(float *gyroData)
{
	unsigned char buf[6];
	MPU6050_ReadData(MPU6050_GYRO_OUT,buf,6);
    gyroData[0] = (buf[0] << 8) + buf[1];
    gyroData[1] = (buf[2] << 8) + buf[3];
    gyroData[2] = (buf[4] << 8) + buf[5];
}

void readMPU6050AccFloat(float *accData)
{
	unsigned char buf[6];
	MPU6050_ReadData(MPU6050_ACC_OUT, buf, 6);
    accData[0] = (buf[0] << 8) + buf[1];
    accData[1] = (buf[2] << 8) + buf[3];
    accData[2] = (buf[4] << 8) + buf[5];
}

//void readMPU6050Mgn(int *mgnData)
//{
//    unsigned char buf[6];
//    MPU6050_WriteReg(MPU6050_RA_INT_PIN_CFG, 0x02);
//    __delay_cycles(16000);//1ms
//    MPU9150_WriteReg(0x0A, 0x01);
//    __delay_cycles(16000);//1ms
//   // MPU9150_ReadData(MPU9150_RA_MAG_XOUT_L,buf,6);
//    mgnData[0] = (buf[0] << 8) | buf[1];
//    mgnData[1] = (buf[2] << 8) | buf[3];
//    mgnData[2] = (buf[4] << 8) | buf[5];
//}

void getMPU6050Acc(float *ax,float *ay,float *az)
{
	readMPU6050Acc(accl);
	*ax = accl[0]*16.0f/32768.0f; // 16 g full range for accelerometer
	*ay = accl[1]*16.0f/32768.0f;
	*az = accl[2]*16.0f/32768.0f;
}

void getMPU6050Gyro(float *gx,float *gy,float *gz)
{
	readMPU6050Gyro(gyro);
	*gx = gyro[0]*2000.0f/32768.0f; // 2000 deg/s full range for gyroscope
	*gy = gyro[1]*2000.0f/32768.0f;
	*gz = gyro[2]*2000.0f/32768.0f;
}

//void getMPU6050Mgn(float *mx,float *my,float *mz)
//{
//	readMPU6050Mgn(mgn);
//	*mx = mgn[0]*10.0f*1229.0f/4096.0f + 18.0f; // milliGauss (1229 microTesla per 2^12 bits, 10 mG per microTesla)
//	*my = mgn[1]*10.0f*1229.0f/4096.0f + 70.0f; // apply calibration offsets in mG that correspond to your environment and magnetometer
//	*mz = mgn[2]*10.0f*1229.0f/4096.0f + 270.0f;
//}

u8 MPU6050_ClearInterupt(void)
{
	unsigned char buf[1];
	MPU6050_ReadData(MPU6050_RA_INT_STATUS, buf, 1);
	return *buf;
}

float readMPU6050Temp( )
{
  unsigned char buf[2];
  int temp;
    MPU6050_ReadData(MPU6050_RA_TEMP_OUT_H,buf,2);
    temp = (buf[0] << 8) | buf[1];
  return ((temp + 13200) / 280)-13;
}

