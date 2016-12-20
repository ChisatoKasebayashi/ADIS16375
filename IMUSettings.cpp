#pragma onece
#include "IMUSettings.h"

IMUSettings::IMUSettings()
{
    my_SPI = -1;
    SPIMode = SPI_MODE_3;
    SPIBits = 8;
    SPISpeed = 1000000;
}

IMUSettings::~IMUSettings()
{
    IMUSettingsClose();
}

 void IMUSettings::IMUError(const char *s)
{
    perror(s);
    abort();
}
bool IMUSettings::setSPIMode(unsigned char SPIMode)
{
    if(ioctl(my_SPI, SPI_IOC_WR_MODE, &SPIMode) < 0)
    {
        IMUError("Failed to set SPI_IOC_WR_MODE");
		close(my_SPI);
        return false;
    }
    if(ioctl(my_SPI,SPI_IOC_RD_MODE, &SPIMode) < 0)
    {
        IMUError("Failed to set SPI_IOC_RD_MODE");
		close(my_SPI);
        return false;
    }
}
bool IMUSettings::setSPIBits(unsigned char SPIBits)
{
	if(ioctl(my_SPI, SPI_IOC_WR_BITS_PER_WORD, &SPIBits) < 0)
	{
		IMUError("Failed ti set SPI_IOC_WR_BITS_PER_WORD");
		close(my_SPI);
		return false;
	}
	if(ioctl(my_SPI, SPI_IOC_RD_BITS_PER_WORD, &SPIBits) < 0)
	{
		IMUError("Failed to set SPI_IOC_RD_BITS_PER_WORD");
		close(my_SPI);
		return false;
	}
}
bool IMUSettings::setSPISpeed(uint32_t SPISpeed)
{
	if(ioctl(my_SPI, SPI_IOC_WR_MAX_SPEED_HZ, &SPISpeed) < 0)
	{
		IMUError("Failed to set SPI_IOC_WR_MAX_SPEED_HZ");
		close(my_SPI);
		return false;
	}
	if(ioctl(my_SPI, SPI_IOC_RD_MAX_SPEED_HZ, &SPISpeed) < 0)
	{
		IMUError("Failed to set SPI_IOC_RD_MAX_SPEED_HZ");
		close(my_SPI);
		return false;
	}
}
void IMUSettings::IMUSettingsClose()
{
    SPIClose();
}

void IMUSettings::SPIClose()
{
    if(my_SPI)
    {
        close(my_SPI);
        my_SPI = -1;
    }
}

bool IMUSettings::SPIOpen()
{
    my_SPI = open(device(),O_RDWR);
    if(my_SPI < 0)
    {
        IMUError("Failed to open SPI bus");
        return false;
    }
    //mode, speed, bit settings
    if(setSPIMode(SPIMode) < 0) 
    {
        printf("mode settings bad");
        return false;
    }
	if(setSPIBits(SPIBits) < 0)
	{
		printf("bits per word settings bad");
		return false;
	}
	if(setSPISpeed(SPISpeed) < 0)
	{
		printf("speed settings bad");
		return false;
	}
}

const char *IMUSettings::device()
{
    static const char *d="/dev/spidev1.0";
    return d;
}
