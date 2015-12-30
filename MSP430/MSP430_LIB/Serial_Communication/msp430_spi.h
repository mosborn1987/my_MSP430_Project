/* msp430_spi.c
 * Library for performing SPI I/O on a wide range of MSP430 chips.
 *
 * Copyright (c) 2013, Eric Brundick <spirilis@linux.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any purpose
 * with or without fee is hereby granted, provided that the above copyright notice
 * and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT,
 * OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _MSP430_SPI_H_
#define _MSP430_SPI_H_

//#include <stdint.h>
#include <msp430G2553.h>

void spi_init();
unsigned char spi_transfer(unsigned char);  // SPI xfer 1 byte
unsigned int spi_transfer16(unsigned int);  // SPI xfer 2 bytes
unsigned int spi_transfer9(unsigned int);   // SPI xfer 9 bits (courtesy for driving LCD screens)

#endif
