// Audio code derived from Qt sample code under the following license

/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <stdlib.h>
#include <stdint.h>
#include <math.h>

int kl_colorbar_tonegenerator(int toneFreqHz, int sampleSize,
			      int channelCount, int durationUs,
			      int sampleRate, int signedSample,
			      char *buf, size_t maxBufLen,
			      size_t *resultBufLen)
{
	const int channelBytes = sampleSize / 8;

	int64_t length = (int64_t) sampleRate * (int64_t) channelCount * (sampleSize / 8)
		* (int64_t) durationUs / 100000;
	*resultBufLen = length;

	if (length > maxBufLen) {
		return -1;
	}

	unsigned char *ptr = (unsigned char *) buf;
	int sampleIndex = 0;

	while (length) {
		double x = sin(2 * M_PI * toneFreqHz * (double)(sampleIndex % sampleRate) / sampleRate);
		for (int i=0; i < channelCount; ++i) {
			if (sampleSize == 8 && !signedSample) {
				const uint8_t value = ((1.0 + x) / 2 * 255);
				*ptr = value;
			} else if (sampleSize == 8 && signedSample) {
				const int8_t value = (x * 127);
				*ptr = value;
			} else if (sampleSize == 16 && !signedSample) {
				uint16_t value = ((1.0 + x) / 2 * 65535);
				uint16_t *tmp = (uint16_t *) ptr;
				*tmp = value; /* FIXME: endianness */
			} else if (sampleSize == 16 && signedSample) {
				int16_t value = (x * 32767);
				int16_t *tmp = (int16_t *) ptr;
				*tmp = value; /* FIXME: endianness */
			}

			ptr += channelBytes;
			length -= channelBytes;
		}
		++sampleIndex;
	}
	return 0;
}
