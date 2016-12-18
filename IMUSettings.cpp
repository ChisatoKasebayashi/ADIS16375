#include "IMUSettings.h"

IMUSettings::IMUSettings()
{
    *device = "/dev/spidev1.0"
    my_SPI = -1;
    SPIMode = SPI_MODE_3;
    SPIBits = 8;
    SPISpeed = 1000000;
}

IMUSettings::~IMUSettings()
{
    IMUSettingsClose();
}

static void IMUSettings::IMUError(const char *s)
{
    perror(s);
    abort();
}
bool setSPIMode(unsigned char SPIMode)
{
    if(ioctl(my_SPI, SPI_IOC_WR_MODE, &SPIMode) < 0)
    {
        IMUEroor("Failed to set SPI_IOC_WR_MODE");
        return false;
    }
    if(ioctl(my_SPI,SPI_IOC_RD_MODE, &SPIMode) < 0)
    {
        IMUError("Failed to set SPI_IOC_RD_MODE");
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
    my_SPI = open(device,O_RDWR);
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

