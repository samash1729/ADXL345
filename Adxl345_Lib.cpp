
#include "Adxl345_Lib.h"


ADXL345::ADXL345()
{
	this->i2c = new I2cPort(ADXLadd, 2);
}

ADXL345::~ADXL345()
{
	delete i2c;
}

void ADXL345::ADXL345_set(void)
{
	
	accel_Write(Register_2D,8);
	accel_Write(Register_DataFormat,0b01100111);	

	
} 

void ADXL345::ADXL345_set(int _2D,int DataFormat)
{	
	
	accel_Write(Register_2D, _2D);
	accel_Write(Register_DataFormat,  DataFormat);

}

void ADXL345::accel_constant(int a,int b,int c,int d,int e,int f) 
{
	 accel_x_pos=a; accel_x_neg=b; 
	 accel_y_pos=c; accel_y_neg=d;
	 accel_z_pos=e; accel_z_neg=f;	
}
 
 
 int ADXL345::accel_Read(int add)
{
	int buf;
	i2c->openConnection();
	buf = i2c->readByte(add);
	i2c->closeConnection();
	return buf; 	
} 

void ADXL345::accel_Write(int add,int value)
{
	i2c->openConnection();
	i2c->writeByte(add, value);
	i2c->closeConnection();
}

AccelerometerRaw ADXL345::rawvalue()
{  
  AccelerometerRaw raw= AccelerometerRaw();
  
  accel_X0 = accel_Read(Register_accel_X0); accel_X1 = accel_Read(Register_accel_X1); 
  accel_X1=accel_X1<<8;
  
  raw.XAxis=accel_X0+accel_X1;

  accel_Y0 = accel_Read(Register_accel_Y0); accel_Y1 = accel_Read(Register_accel_Y1); 
  accel_Y1=accel_Y1<<8;

  raw.YAxis=accel_Y0+accel_Y1;
  
  accel_Z0 = accel_Read(Register_accel_Z0); accel_Z1 = accel_Read(Register_accel_Z1); 
  accel_Z1=accel_Z1<<8;

  raw.ZAxis=accel_Z0+accel_Z1;  
 
  return raw;
}

AccelerometerScaled ADXL345::scalevalue()
{
 AccelerometerRaw raw= rawvalue();
 AccelerometerScaled sc;
 if(raw.XAxis>0){sc.XAxis=(float)raw.XAxis/accel_x_pos;} else {sc.XAxis=(float)raw.XAxis/accel_x_neg;}
 if(raw.YAxis>0){sc.YAxis=(float)raw.YAxis/accel_y_pos;} else {sc.YAxis=(float)raw.YAxis/accel_y_neg;} 
 if(raw.ZAxis>0){sc.ZAxis=(float)raw.ZAxis/accel_z_pos;} else {sc.ZAxis=(float)raw.ZAxis/accel_z_neg;} 
 return sc;
}
