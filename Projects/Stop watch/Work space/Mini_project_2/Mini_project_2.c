//Abdelrahman Mohamed Farid (Diploma60)
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define NUMBER_OF_TICKS_PER_SECOND 15625
unsigned char clock[6]={0,0,0,0,0,0};
void Timer1_CTC(void);
ISR(TIMER1_COMPA_vect);		//Reset the whole array
void INT0_Init(void);
ISR(INT0_vect);		//Reset the whole array
void INT1_Init(void);
ISR(INT1_vect);		//Pause
void INT2_Init(void);
ISR(INT2_vect);		//Resume
int main(void)
{
	Timer1_CTC();
	INT0_Init();
	INT1_Init();
	INT2_Init();
	SREG = 1<<7;
	DDRA |= 0x3F;
	DDRC |= 0x0F;
	PORTC &= 0xF0;
	for(;;)
	{
		for(unsigned char i=0 ; i<6 ; i++)
		{
			if(i==0)
				PORTA |= 1<<PA0;		//Enable the 9-secs counter.
			PORTC = (PORTC & 0xF0) | clock[5-i];	//Display on the current counter(7-segment 1of6).
			_delay_ms(1);		//Delay so that the 7-segment can respond.
			PORTA = (PORTA & 0xC0) | (PORTA<<1);		//Switch to the next counter.
		}
	}
}
ISR(INT0_vect)
{
	for(unsigned char i=0; i<6; i++)		//Reset all the array
		clock[i]=0;
}
void INT0_Init(void)
{
	SREG &= ~(1<<7);
	GICR |= 1<<INT0;
	DDRD &= ~(1<<PD2);
	PORTD |= (1<<PD2);
	MCUCR |= 1<<ISC11;
	MCUCR &= ~(1<<ISC10);
	SREG |= (1<<7);
}
ISR(INT1_vect)
{
	TIMSK &= ~(1 << OCIE1A);
}
void INT1_Init(void)
{
	SREG &= ~(1<<7);
	GICR |= 1<<INT1;
	DDRD &= ~(1<<PD3);
	MCUCR |= (1 << ISC11) | (1<<ISC10);
	SREG |= (1<<7);
}

ISR(INT2_vect)
{
	TIMSK |= (1 << OCIE1A);
}
void INT2_Init(void)
{
	SREG &= ~(1<<7);
	GICR |= 1<<INT2;
	DDRB &= ~(1<<PB2);
	MCUCSR |= 1<<ISC2;
	SREG |= (1<<7);
}

ISR(TIMER1_COMPA_vect)
{
	clock[5]++;
	unsigned char display_position;
	if(clock[5]==10)	//For not to enter the for loop unless the seconds R.H.S counter overflows.
	{
		for(unsigned char i=5; i>0; i--)		//A counter that passes on the 5 R.H.S displays (All except the hrs L.H.S that counts till 24).
		{
			if(i%2 != 0)		//If it is the R.H.S of secs or mins or hrs, count till 9.
				display_position=4;
			else		//If it is the L.H.S of secs or mins or hrs, count till 5.
				display_position=0;
			if(clock[i]==6+display_position)
			{
				clock[i]=0;
				clock[i-1]++;
				if(clock[0]==24)
					clock[0]=0;
			}
		}
	}
}

void Timer1_CTC(void)
{
	TCCR1A |= 1<<FOC1A;
	TCCR1B |= (1<<WGM12) | (1<<CS10) | (1<<CS11);
	TCNT1=0;
	OCR1A=NUMBER_OF_TICKS_PER_SECOND;
	TIMSK |= (1<<OCIE1A);
}
