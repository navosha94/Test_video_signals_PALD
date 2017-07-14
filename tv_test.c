	#include <avr/io.h>
	#include <avr/interrupt.h>
	#define F_CPU 20000000L
	#include <util/delay.h>
	#define FOSC 20000000 //clock speed
	#define NOP(); { __asm__ __volatile__ ("nop"); }
	#define numScanlines 625
	#define valCounter 2
	#define mask 0xF0
	#define l_sync() NOP();PORTB = ((PORTB & mask) | 0x00)
	#define l_black() PORTB = ((PORTB & mask) | 0x01)
	#define l_data() PORTB = ((PORTB & mask) | 0x03)
	#define l_white() PORTB = ((PORTB & mask) | 0x0A)
	void init_data_dir_reg();
	void testSignal();
	void Frame();
//	#define nVertSync 5
//	void verticalSuncPulses();
//	void equalizingPulses();
		volatile uint8_t keyState = 0;
		volatile uint8_t prevKeyState = 0;
		volatile uint8_t keyCounter = 0;
		volatile uint16_t globCounterButt = 0;
		volatile uint16_t scanlineCounter = 0;
		volatile uint8_t empty_string_counter;
		void (*funcString)();
		void (*forwFuncString)();
		void (*backwFuncString)();
	int main (void)
	{
		init_data_dir_reg();
		
		funcString = testSignal;
		//forwFuncString = 
		//backwFuncString = 
		while(1){
			keyScan();
			l_sync();
			l_black();
			l_data();
			l_white();
			Frame();
		
		}
		
	}


void Frame(){
	//========================Vertical_sync_pulses=============================
			_delay_us(27.1);//1
			l_black();
			keyScan();
			keyScan();		
			_delay_us(1.3);
			l_sync();
			_delay_us(27.1);//2
			l_black();
			keyScan();
			keyScan();		
			_delay_us(1.4);
			l_sync();
			_delay_us(27.1);//3
			l_black();
			keyScan();
			keyScan();		
			_delay_us(1.4);
			l_sync();
			_delay_us(27.1);//4
			l_black();
			keyScan();
			keyScan();		
			_delay_us(1.4);
			l_sync();
			_delay_us(27.1);//5
			l_black();
			keyScan();
			keyScan();		
			_delay_us(1.4);
			l_sync();
//===========================equalizing_pulses_5============================
			keyScan(); NOP();
			_delay_us(0.7);//1
			PORTC = 0x01;
			_delay_us(29.6);
			PORTC = 0x00;
			keyScan(); NOP();
			_delay_us(0.7);//2
			PORTC = 0x01;
			_delay_us(29.6);
			PORTC = 0x00;
			keyScan(); NOP();
			_delay_us(0.7);//3
			PORTC = 0x01;
			_delay_us(29.6);
			PORTC = 0x00;
			keyScan(); NOP();
			_delay_us(0.7);//4
			PORTC = 0x01;
			_delay_us(29.6);
			PORTC = 0x00;
			keyScan(); NOP();
			_delay_us(0.7);//5
			PORTC = 0x01;
			_delay_us(29.6);
			PORTC = 0x00;
//==========================empty_strings_field1============================
			empty_string_counter = 0;
			_delay_us(0.2);
			do{
				keyScan(); NOP();
				keyScan(); NOP();
				_delay_us(1.1);
				PORTC = 0x01;
				NOP();
				empty_string_counter++;
				NOP();
				_delay_us(58.9);
				PORTC = 0x00;
				NOP();
			}while(empty_string_counter < 17);
//==========================forw_half_string=================================
			keyScan(); NOP();
			keyScan(); NOP();
			_delay_us(1.1);
			NOP();
			PORTC = 0x01;
			//_delay_us(25.9);
			//PORTC = 0x03;
			//_delay_us(26);
			//PORTC = 0x01;
			_delay_us(1.4);
			NOP();
			PORTC = 0x00;
			//==============
//===============================Field1_strings==============================
			empty_string_counter = 0;
			_delay_us(0.25);
			do{
				/*_delay_us(4.3);
				PORTC = 0x01;
				_delay_us(5.7);
				NOP();
				PORTC = 0x03;
				empty_string_counter++;
				NOP();
				_delay_us(51.6);
				NOP();
				PORTC = 0x01;
				_delay_us(1.4);
				NOP();
				PORTC = 0x00;
				NOP();NOP();NOP();*/
				//_delay_us(4.3);
				keyScan(); NOP();
				keyScan(); NOP();
				_delay_us(1.1);
				PORTC = 0x01;
				_delay_us(5.1);
				//PORTC = 0x03;
				empty_string_counter++;
				funcString();
				NOP();
				PORTC = 0x01;
				_delay_us(1.4);
				NOP();
				PORTC = 0x00;
				NOP();NOP();
			}while(empty_string_counter < 2);//287
//===========================equalizing_pulses_5============================
			keyScan();
			_delay_us(0.4);//1
			PORTC = 0x01;
			_delay_us(29.6);
			PORTC = 0x00;
			keyScan(); NOP();
			_delay_us(0.7);//2
			PORTC = 0x01;
			_delay_us(29.6);
			PORTC = 0x00;
			keyScan(); NOP();
			_delay_us(0.7);//3
			PORTC = 0x01;
			_delay_us(29.6);
			PORTC = 0x00;
			keyScan(); NOP();
			_delay_us(0.7);//4
			PORTC = 0x01;
			_delay_us(29.6);
			PORTC = 0x00;
			keyScan(); NOP();
			_delay_us(0.7);//5
			PORTC = 0x01;
			_delay_us(29.6);
			PORTC = 0x00;
//=======================================================================================			
//==========================FIELD2!!!!!!!!!!!!!!!========================================
//========================Vertical_sync_pylses=============================
			_delay_us(27.2);NOP();//1
			PORTC = 0x01;
			keyScan();
			keyScan();			
			_delay_us(1.5); NOP();
			PORTC = 0x00;
			_delay_us(27.2);NOP();//2
			PORTC = 0x01;
			keyScan();
			keyScan();
			_delay_us(1.5); NOP();
			PORTC = 0x00;
			_delay_us(27.2);NOP();//3
			PORTC = 0x01;
			keyScan();
			keyScan();
			_delay_us(1.5); NOP();
			PORTC = 0x00;
			_delay_us(27.2);NOP();//4
			PORTC = 0x01;
			keyScan();
			keyScan();
			_delay_us(1.5); NOP();
			PORTC = 0x00;
			_delay_us(27.2);NOP();//5
			PORTC = 0x01;
			keyScan();
			keyScan();
			_delay_us(1.5); NOP();
			PORTC = 0x00;
//===========================equalizing_pulses_4============================
			keyScan(); NOP();
			_delay_us(0.7);//1
			PORTC = 0x01;
			_delay_us(29.6);
			PORTC = 0x00;
			keyScan(); NOP();
			_delay_us(0.7);//2
			PORTC = 0x01;
			_delay_us(29.6);
			PORTC = 0x00;
			keyScan(); NOP();
			_delay_us(0.7);//3
			PORTC = 0x01;
			_delay_us(29.6);
			PORTC = 0x00;
			keyScan(); NOP();
			_delay_us(0.7);//4
			PORTC = 0x01;
			_delay_us(29.6);
			PORTC = 0x00;
			keyScan(); NOP();
//==========================empty_strings_field1============================
			empty_string_counter = 0;
			_delay_us(0.2);
			do{
				keyScan(); NOP();
				keyScan(); NOP();
				_delay_us(1.1);
				PORTC = 0x01;
				NOP();
				empty_string_counter++;
				NOP();
				_delay_us(58.9);
				PORTC = 0x00;
				NOP();
			}while(empty_string_counter < 18);
//===============================Field2_strings==============================
			empty_string_counter = 0;
			do{
				/*_delay_us(4.3);
				PORTC = 0x01;
				_delay_us(5.7);
				NOP();
				PORTC = 0x03;
				empty_string_counter++;
				NOP();
				_delay_us(51.6);
				NOP();
				PORTC = 0x01;
				_delay_us(1.4);
				NOP();
				PORTC = 0x00;
				NOP();NOP();NOP();*/
				//_delay_us(4.3);
				keyScan(); NOP();
				keyScan(); NOP();
				_delay_us(1.1);
				PORTC = 0x01;
				_delay_us(5.1);
				//PORTC = 0x03;
				empty_string_counter++;
				funcString();
				NOP();
				PORTC = 0x01;
				_delay_us(1.4);
				NOP();
				PORTC = 0x00;
				NOP();NOP();
			}while(empty_string_counter < 2);//287
//=======================backward_half_string=====================================
}
//=========================Init_data_dir_reg================================	
void init_data_dir_reg(){
		//Init data direction registors
		DDRC = (1 << DDC0) | (1 << DDC1) ;//| (1 << DDC2) | (1 << DDC3);
		DDRB = (1 << DDB6) | (1 << DDB4) | (7 << DDB0);//comments on paper
		DDRD = (0 << DDD4) | (0 << DDD0) | (0 << DDD1) | (0 << DDD2) | (0 << DDD3) | (0 << DDD5);// kn
		PORTD = (1 << PD4) | (1 << PD0);// pull-up to PD0, PD4;
}
//================================Key_scan===============================
void keyScan(){
	uint8_t currentKeyState = PINC & 0x0F;
	if(prevKeyState == currentKeyState){
		keyCounter++;
		if(keyCounter == valCounter){
			keyState = prevKeyState;
			keyCounter = 0;
		}else{
		_delay_us(0.35);
		}
	}else{
		_delay_us(0.6);
		prevKeyState = currentKeyState;
		keyCounter = 0;
	}
}
//==========================cell_for_func_pointer==========================
void testSignal(){//51.8us
	PORTC = 0x03;
	_delay_us(51.7);
}

void forwardHalfTestSignal(){
	PORTC = 0x03;
}
//=============================LongSunc=====================================
/*void verticalSuncPulses(){

		_delay_us(26.6);NOP();NOP();PORTC = 0x01;_delay_us(4.8);NOP();PORTC = 0x00;

		_delay_us(27);NOP();NOP();PORTC = 0x01;_delay_us(4.8);NOP();PORTC = 0x00;

		_delay_us(27);NOP();NOP();PORTC = 0x01;_delay_us(4.8);NOP();PORTC = 0x00;

		_delay_us(27);NOP();NOP();PORTC = 0x01;_delay_us(4.8);NOP();PORTC = 0x00;

		_delay_us(27);NOP();NOP();PORTC = 0x01;_delay_us(4.8);NOP();
		PORTC = 0x00;
}
//===================ShortSunc_4_clock's====================================
void equalizingPulses4(){

		_delay_us(1.8);NOP();NOP();PORTC = 0x01;_delay_us(29.5);NOP();NOP();PORTC = 0x00;

		_delay_us(2.2);NOP();NOP();PORTC = 0x01;_delay_us(29.5);NOP();NOP();PORTC = 0x00;

		_delay_us(2.2);NOP();NOP();PORTC = 0x01;_delay_us(29.5);NOP();NOP();PORTC = 0x00;

		_delay_us(2.2);NOP();NOP();PORTC = 0x01;_delay_us(29.5);NOP();NOP();
		PORTC = 0x00;
}
//===================ShortSunc_5_clock's====================================
void equalizingPulses5(){

		_delay_us(1.8);NOP();NOP();PORTC = 0x01;_delay_us(29.5);NOP();NOP();PORTC = 0x00;

		_delay_us(2.2);NOP();NOP();PORTC = 0x01;_delay_us(29.5);NOP();NOP();PORTC = 0x00;

		_delay_us(2.2);NOP();NOP();PORTC = 0x01;_delay_us(29.5);NOP();NOP();PORTC = 0x00;

		_delay_us(2.2);NOP();NOP();PORTC = 0x01;_delay_us(29.5);NOP();NOP();PORTC = 0x00;

		_delay_us(2.2);NOP();NOP();PORTC = 0x01;_delay_us(29.5);NOP();NOP();
		PORTC = 0x00;
}
void gradientStripesString(){
	_delay_us(4.3);PORTC = 0x01;_delay_us(5.5);NOP();PORTC = 0x03;
	_delay_us(51);NOP();PORTC = 0x01;_delay_us(1.6);NOP();PORTC = 0x00;
}*/
//2.3
//PORTC = 0x00;  0.05ms
// 0.20 back from a function; 0.15 enter to function; 0.1 while
