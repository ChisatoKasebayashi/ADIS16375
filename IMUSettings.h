#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <linux/spi/spidev.h>

class IMUSettings
{
private:

public:
    IMUSettings();
    ~IMUSettings();
    bool SPIOpen();
    bool setSPIMode(unsigned char SPIMode);
    bool setSPIBits(unsigned char SPIBits);
    bool steSPISpeed(unsigned char SPISpeed);
    void IMUSettingsClose();
    void SPIClose();
    static const char *device;
    unsigned char SPIMode;
    unsigned char SPIBits;
    uint32_t SPISpeed;
    unsigned char buf[32];

    static void IMUError(const char*s);
};
