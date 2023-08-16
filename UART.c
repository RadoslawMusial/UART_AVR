#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL      // 8 MHz
#define USART_BAUDRATE 9600  // desired baud rate
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void UART_init(unsigned int baud)
{
    UBRRH = (BAUD_PRESCALE >> 8);  // Set the 8 lower bits of the baud rate
    UBRRL = BAUD_PRESCALE;         // Set the 8 upper  bits

    // Enable transmitter and receiver, and enable receive complete interrupt
    UCSRB = (1 << TXEN) | (1 << RXEN) | (1 << RXCIE);

    // Set frame format: 8 data bits, 1 stop bit, no parity
    UCSRC = (1 << UCSZ1) | (1 << UCSZ0);
}

void USART_SEND(uint8_t data)
{
    while (!(UCSRA & (1 << UDRE)));  // Wait until the data register is empty

    UDR = data;  // Transmit data
}

uint8_t USART_RECEIVE()
{
    while (!(UCSRA & (1 << RXC)));  // Wait until data is received

    return UDR;  // Return the received data
}

int main()
{
    USART_SEND('1'); 
    UART_init(USART_BAUDRATE);  // Initialize UART with desired baud rate

    sei();  // Enable global interrupts

    while (1)
    {
    
        
        
        DDRB|=PORTB0; 
        uint8_t received_data = USART_RECEIVE(); // received data 

        if (received_data == '1')
        {
            PORTB|=(1<<PORTB0); // LED ON 
        }
        else 
        {
            PORTB &=~(1<<PORTB0); 
        }
       
    }

    return 0;
}

ISR(USART_RXC_vect)
{
    // USART receive complete interrupt service routine
    uint8_t received_data = UDR;  // Read the received data
    
}
