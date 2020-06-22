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

#ifndef I2CDRIVER_H_INCLUDED
#define I2CDRIVER_H_INCLUDED

#include <cstddef>
#include <cstdint>

namespace I2CError {
	enum {
		Ok = 0,
		NotImplemented = -1,
		UnknownError = -2,
		UnableToInitialise = -3,
		UnableToOpenDevice = -4,
		NotOpen = -5
	};
}

class I2CDriver {
	public:

        virtual int initialise(unsigned int speed, unsigned int mode)
		{
			return I2CError::NotImplemented;
		}

		virtual int deinitialise()
		{
			return I2CError::NotImplemented;
		}

		virtual int start(uint8_t address, bool read)
		{
			return I2CError::NotImplemented;
		}

        virtual int write(uint8_t */*dataOut*/, unsigned int /*dataLength*/)
		{
			return I2CError::NotImplemented;
		}

        virtual int read(uint8_t */*data*/, unsigned int /*dataLength*/)
		{
			return I2CError::NotImplemented;
		}

		virtual int stop()
		{
			return I2CError::NotImplemented;
		}
};

#endif
