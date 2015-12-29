/*
 * SPI.h
 *
 *  Created on: Dec 27, 2015
 *      Author: Mario Osborn
 */

#ifndef MSP430_LIB_SPI_H_
#define MSP430_LIB_SPI_H_

/******************************************************************************
 * SPI example for MSP430.
 *
 * Stefan Wendler
 * sw@kaltpost.de
 * http://gpio.kaltpost.de
 *
 *****************************************************************************/
//----------------------------------------
// * RXD  P1.1				UART - TXD serial line
// * TXD  P1.2				UART - RXD serial line
// * SCLK P1.5				NRF SCK
// * SOMI P1.6				NRF MO
// * SIMO P1.7				NRF MI
// * CS   P1.3				NRF CS
// * </pre>
// * <br/><br/>
// * For the NRF also connect the following:
// * <br/><br/>
// * <pre>
// * NRF						To
// * ----------------------------------------
// * VCC						3.3v
// * CE						3.3v
// * GND						GND
// * </pre>
// * <br/><br/>
// * Stefan Wendler
// * sw@kaltpost.de
// * http://gpio.kaltpost.de
// *

/**
 * Initialize HW interface (SPI) to nRF24l01.
 */
void spi_init(void);

/**
 * Drive CS high.
 */
void spi_csh(void);

/**
 * Drive CS low.
 */
void spi_csl(void);

/**
 * Write-/Read one byte of data to/from the nRF through the SPI bus.
 *
 * @param[in]	data	byte to send
 * @return				byte received
 */
unsigned char spi_xfer_byte(unsigned char data);


/**
 * SPI Clock at P1.5
 */
#define SCLK    BIT5

/**
 * SPI SOMI (Slave Out, Master In) at P1.6
 */
#define SOMI    BIT6

/**
 * SPI SIMO (Slave In, Master Out) at P1.7
 */
#define SIMO    BIT7

/**
 * CS (Chip Select) at P1.3
 */
#define CS      BIT3

void spi_init(void)
{
	/**
	 * From TIs users manual
	 *
     * The recommended USCI initialization/re-configuration process is:
 	 * 1. Set UCSWRST (BIS.B #UCSWRST,&UCxCTL1)
 	 * 2. Initialize all USCI registers with UCSWRST=1 (including UCxCTL1)
 	 * 3. Configure ports
 	 * 4. Clear UCSWRST via software (BIC.B #UCSWRST,&UCxCTL1)
 	 * 5. Enable interrupts (optional) via UCxRXIE and/or UCxTXIE
 	 */

	// (1)
	UCB0CTL1 = UCSWRST;

	// (2)
    P1DIR  |= CS;
    P1OUT  |= CS;
  	P1SEL  |= SOMI + SIMO + SCLK;
  	P1SEL2 |= SOMI + SIMO + SCLK;

    // (3) 3-pin, 8-bit SPI master
    UCB0CTL0 |= UCCKPH + UCMSB + UCMST + UCSYNC;
	UCB0CTL1 |= UCSSEL_2;   // SMCLK

	// (4)
	UCB0CTL1 &= ~UCSWRST;

	spi_csh();

}

void spi_csh(void)
{
    P1OUT |= CS;
}

void spi_csl(void)
{
    P1OUT &= ~CS;
}

unsigned char spi_xfer_byte(unsigned char data)
{
  	UCB0TXBUF = data;

	// wait for TX
	while (!(IFG2 & UCB0TXIFG));

	return UCB0RXBUF;
}


#endif /* MSP430_LIB_SPI_H_ */
