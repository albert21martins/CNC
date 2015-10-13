#include <msp430.h>
#include <stdint.h>
#include "spi.h"


#define SPI_MODE_0 UCCKPH | UCMSB| UCMST | UCSYNC /* CPOL=0 CPHA=0 */
#define SPI_MODE_3 UCCKPL | UCMSB| UCMST | UCSYNC /* CPOL=1 CPHA=1 */

/**
 * spi_initialize() - Initialize and enable the SPI module
 *
 * P2.0 - CS (active low)
 * P1.5 - SCLK
 * P1.6 - SIMO
 * P1.7 - MOSI
 *
 */
void spi_initialize(void)
{
	 P3SEL |= BIT3+BIT4;                       // P3.3,4 option select
	 P2SEL |= BIT7;                            // P2.7 option select

	 UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
	 UCA0CTL0 |= UCMST+UCSYNC+UCCKPL+UCMSB;    // 3-pin, 8-bit SPI master
		                                            // Clock polarity high, MSB
	 P8OUT |= BIT1;							// CS on P2.0. start out disabled
	 P8DIR |= BIT1;							// CS configured as output


	 UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	 UCA0BR0 = 62;                           // /2
	 UCA0BR1 = 0;                              //
	 UCA0MCTL = 0;                             // No modulation
	 UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

/**
 * spi_send() - send a byte and recv response
 */
uint8_t spi_send(const uint8_t c)
{
	while (!(UCA0IFG & UCTXIFG));               // USCI_A0 TX buffer ready?
	UCA0TXBUF = c;                  	   		// Transmit first character
	while (!(UCA0IFG & UCRXIFG)); 				// wait for an rx character?
	//while(!(UCA0IFG & UCRXIFG));
	//while (!(UCA0IFG & UCTXIFG));

	return UCA0RXBUF; 							// reading clears RXIFG flag

}

/**
 * spi_receive() - send dummy btye then recv response
 */

uint8_t spi_receive(void)
{

	while (!(UCA0IFG & UCTXIFG));               // USCI_A0 TX buffer ready?
	UCA0TXBUF = 0xFF; 							// Send dummy packet to get data back.
	while (!(UCA0IFG & UCRXIFG)); 				// wait for an rx character?
	//while (!(UCA0IFG & UCTXIFG));
	//while(!(UCA0IFG & UCRXIFG));

	return UCA0RXBUF; 							// reading clears RXIFG flag

}

/**
 * spi_setspeed() - set new clock divider for USCI
 *
 * USCI speed is based on the SMCLK divided by BR0 and BR1
 * initially we start slow (400kHz) to conform to SDCard
 * specifications then we speed up once initialized (16Mhz)
 *
 */
void spi_set_divisor(const uint16_t clkdiv)
{
	UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
	UCA0BR0 = clkdiv;                           // /divisor
	UCA0BR1 = clkdiv >> 8;                              //
	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}
