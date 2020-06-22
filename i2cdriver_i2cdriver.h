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

#ifndef I2CDRIVER_I2CDRIVER_H_INCLUDED
#define I2CDRIVER_I2CDRIVER_H_INCLUDED

#include "i2cdriver.h"

class I2CDriver_I2CDriver : public I2CDriver {

	public:
        I2CDriver_I2CDriver(const char *deviceName);

        virtual int initialise(unsigned int speed, unsigned int mode);
	virtual int deinitialise();

	virtual int start(uint8_t address, bool read);
        virtual int write(uint8_t *dataOut, unsigned int dataLength);
        virtual int read(uint8_t *data, unsigned int dataLength);
	virtual int stop();

	private:
        int fdDevice;

        const char *deviceName;
};

#endif

