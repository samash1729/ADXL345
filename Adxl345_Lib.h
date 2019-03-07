
#ifndef Adxl345_H
#define Adxl345_H

#include "../I2cPort/I2cPort.h"

#define Register_2D 0x2D
#define Register_accel_X0 0x32
#define Register_accel_X1 0x33
#define Register_accel_Y0 0x34
#define Register_accel_Y1 0x35
#define Register_accel_Z0 0x36
#define Register_accel_Z1 0x37
#define Register_DataFormat 0x31
#define ADXLadd 0x53


struct AccelerometerScaled
{
	float XAxis;
	float YAxis;
	float ZAxis;
};

struct AccelerometerRaw
{
	  float XAxis;
	  float YAxis;
	  float ZAxis;
};



class ADXL345
{
// constants
private: 
	I2cPort *i2c;

	float accel_x_pos , accel_x_neg; 
	float accel_y_pos , accel_y_neg;
	float accel_z_pos , accel_z_neg;
	

	//Accelometer Axis: Lo/Hi readings
public:
	int16_t accel_X0,accel_X1;
	int16_t accel_Y0,accel_Y1;
	int16_t accel_Z1,accel_Z0;

	ADXL345();
	~ADXL345();

	//Register_2D & Register_DataFormat
	void ADXL345_set(void);

	//first parameter is for Register_2D & Register_DataFormat
	void ADXL345_set(int,int);

	
	void accel_constant(int,int,int,int,int,int);
	
	void accel_Write(int,int);
	
	 int accel_Read(int);
	  
	 AccelerometerRaw rawvalue();
	 AccelerometerScaled scalevalue();
};

#endif
