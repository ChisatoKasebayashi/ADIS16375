#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/types.h>
//#include <sys/stat.h>
#include <fcntl.h>
#include <getopt.h>
#include <unistd.h>
#include <linux/spi/spidev.h>

class IMUSettings
{
private:

public:
    const static char *device();
public:
    IMUSettings();
    ~IMUSettings();
    bool SPIOpen();
    bool setSPIMode(unsigned char SPIMode);
    bool setSPIBits(unsigned char SPIBits);
    bool steSPISpeed(unsigned char SPISpeed);
    void IMUSettingsClose();
    void SPIClose();
    unsigned char SPIMode;
    unsigned char SPIBits;
    uint32_t SPISpeed;
    unsigned char buf[32];
    int my_SPI;
    void IMUError(const char *s);
};
