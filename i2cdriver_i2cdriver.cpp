/*
 * MIT License
 *
 * Copyright (c) 2020 Adrian Carpenter
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "i2cdriver_i2cdriver.h"
#include <fcntl.h>
#include <termios.h>
#include <iostream>
#include <unistd.h>

#include <sys/ioctl.h>

#if defined(__APPLE__)
#include <IOKit/serial/ioss.h>
#endif

I2CDriver_I2CDriver::I2CDriver_I2CDriver(const char *deviceName)
{
    this->fdDevice = 0;
    this->deviceName = deviceName;
}

int I2CDriver_I2CDriver::initialise(unsigned int /*speed*/, unsigned int /*mode*/)
{
	struct termios termSettings;
	uint8_t cmd[64];

    fdDevice = open(deviceName, O_RDWR | O_NOCTTY);

    if (fdDevice == -1) {
		return I2CError::UnableToInitialise;
	}

    tcgetattr(fdDevice, &termSettings);

#if defined(__APPLE__)
	cfmakeraw(&termSettings);
#endif

	termSettings.c_cc[VMIN] = 1;
	
    if (tcsetattr(fdDevice, TCSANOW, &termSettings) != 0) {
		return I2CError::UnableToInitialise;
	}

#if defined(__APPLE__) && !defined(B1000000)
  speed_t speed = (speed_t)1000000;
  ioctl(fdDevice, IOSSIOSPEED, &speed);
#endif

	// resync

	memset(cmd, '@', sizeof(cmd));

    ::write(fdDevice, cmd, sizeof(cmd));

	return(I2CError::Ok);
}

int I2CDriver_I2CDriver::deinitialise()
{
    if (!fdDevice) {
		return I2CError::NotOpen;
	}

    close(fdDevice);

	return I2CError::Ok;
}

int I2CDriver_I2CDriver::start(uint8_t address, bool read)
{
	uint8_t cmd[2];

	cmd[0] = 's';
	cmd[1] = (address<<1) | (read?1:0);

    if (!fdDevice) {
		return I2CError::NotOpen;
	}

    ::write(fdDevice, cmd, sizeof(cmd));

	return(I2CError::Ok);
}

int I2CDriver_I2CDriver::stop()
{
    char cmd = 'p';

    if (!fdDevice) {
		return I2CError::NotOpen;
	}

    ::write(fdDevice, &cmd, 1);

	return(I2CError::Ok);
}

int I2CDriver_I2CDriver::write(uint8_t *dataOut, unsigned int dataLength)
{
	uint8_t cmd[65];
	int bytesToWrite;

    if (!fdDevice) {
		return I2CError::NotOpen;
	}

    while (dataLength) {
        if (dataLength>64) {
			bytesToWrite = 64;
		} else {
            bytesToWrite = dataLength;
		}

        dataLength -= bytesToWrite;

		cmd[0] = 0xC0+bytesToWrite-1;

        if (dataOut) {
            memcpy(&cmd[1], dataOut, bytesToWrite);

            dataOut += bytesToWrite;
		}

        ::write(fdDevice, &cmd, 1+bytesToWrite);
	}

	return(I2CError::Ok);
}

int I2CDriver_I2CDriver::read(uint8_t *data, unsigned int dataLength)
{
	uint8_t cmd[2];
	int bytesToRead, cmdLength;

    if (!fdDevice) {
		return I2CError::NotOpen;
	}

    while (dataLength) {
        if (dataLength>64) {
			bytesToRead = 64;
            cmd[0] = 'a';
            cmd[1] = bytesToRead;
            cmdLength = 2;
		} else {
            bytesToRead = dataLength;
            cmd[0] = 0x80+bytesToRead-1;
            cmdLength = 1;
		}

        dataLength -= bytesToRead;

        ::write(fdDevice, &cmd, cmdLength);

        ::read(fdDevice, data, bytesToRead);

        data += bytesToRead;
	}

	return(I2CError::Ok);
}
