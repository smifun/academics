#include <avr/io.h>
#include <util/delay.h>
#define BAUD(x) (((F_CPU/16)/x))
void USART_Init(int baud);
void USART_PutChar(unsigned char data);
unsigned char USART_GetChar(void);
void USART_GetString(char *s);
void USART_PutString(char *s);
int main(void)
{
    char Message[18];
    DDRD = 0xFF;
    USART_Init(BAUD(1200));
    do
    {
        USART_GetString(Message);
        USART_PutString(Message);
    }
    while (1);
    return 0;
}
void USART_Init(int baud)
{
    UBRRH = (unsigned char)(baud >> 8);
    UBRRL = (unsigned char)baud;
    UCSRB = (1 << RXEN) | (1 << TXEN);
    UCSRC = (1 << URSEL) | (3 << UCSZ0);
}
void USART_PutChar(unsigned char data)
{
    while (!(UCSRA & (1 << UDRE)));
    UDR = data;
}
unsigned char USART_GetChar(void)
{
    while (!(UCSRA & (1 << RXC)));
    return UDR;
}
void USART_PutString(char *s)
{
    while (*s)
        USART_PutChar(*s++);
}
void USART_GetString(char *s)
{
    char c;
    do
    {
        c = USART_GetChar();
        USART_PutChar(c);
        if (c == '\b') // if backspace
            s--;
        else
            *s++ = c;
        if (c == '\r') // if CR
            *s = 0;
    }
    while (c != '\r');
}