#include "Arduino.h"
#include "Diplom_Car.h"

//#define DBG // ������������ �������
//#define REVERSE // ������������ ������ ������������ ��� ����� �����������, ���� ������� �� ��������� ������� ��� ������ ����� �������� ��������  

namespace Diplom {
	Car::Car(uint8_t _DR1, uint8_t _DR2, uint8_t _DR3, uint8_t _DR4, uint8_t _DRA, uint8_t _DRB)
		: DR1(_DR1), DR2(_DR2), DR3(_DR3), DR4(_DR4), DRA(_DRA), DRB(_DRB) {} // ����������� ������ 

	void Car::Advance(uint8_t Speed) {
#ifdef REVERSE // ���������� ��� REVERSE
		digitalWrite(DR1, LOW);
		digitalWrite(DR2, HIGH);
		digitalWrite(DR3, LOW);
		digitalWrite(DR4, HIGH);
#else // ���������� ��� REVERSE
		digitalWrite(DR1, HIGH);
		digitalWrite(DR2, LOW);
		digitalWrite(DR3, HIGH);
		digitalWrite(DR4, LOW);
#endif
		analogWrite(DRA, Speed);
		analogWrite(DRB, Speed);
#ifdef DBG // ���������� ��� DBG
		Serial.println('A');
#endif

	}

	void Car::Advance(uint8_t SpeedA, uint8_t SpeedB) {
#ifdef REVERSE // ���������� ��� REVERSE
		digitalWrite(DR1, LOW);
		digitalWrite(DR2, HIGH);
		digitalWrite(DR3, LOW);
		digitalWrite(DR4, HIGH);
#else // ���������� ��� REVERSE
		digitalWrite(DR1, HIGH);
		digitalWrite(DR2, LOW);
		digitalWrite(DR3, HIGH);
		digitalWrite(DR4, LOW);
#endif
		analogWrite(DRA, SpeedA);
		analogWrite(DRB, SpeedB);

#ifdef DBG // ���������� ��� DBG
		Serial.print('A');
		Serial.print("\t");
		Serial.print(SpeedA);
		Serial.print("\t");
		Serial.println(SpeedB);
#endif

	}

	void Car::Back(uint8_t Speed) {
#ifdef REVERSE // ���������� ��� REVERSE
		digitalWrite(DR1, HIGH);
		digitalWrite(DR2, LOW);
		digitalWrite(DR3, HIGH);
		digitalWrite(DR4, LOW);
#else // ���������� ��� REVERSE
		digitalWrite(DR1, LOW);
		digitalWrite(DR2, HIGH);
		digitalWrite(DR3, LOW);
		digitalWrite(DR4, HIGH);
#endif
		analogWrite(DRA, Speed);
		analogWrite(DRB, Speed);
#ifdef DBG // ���������� ��� DBG
		Serial.println('B');
#endif

	}

	void Car::Back(uint8_t SpeedA, uint8_t SpeedB)
	{
#ifdef REVERSE // ���������� ��� REVERSE
		digitalWrite(DR1, HIGH);
		digitalWrite(DR2, LOW);
		digitalWrite(DR3, HIGH);
		digitalWrite(DR4, LOW);
#else // ���������� ��� REVERSE
		digitalWrite(DR1, LOW);
		digitalWrite(DR2, HIGH);
		digitalWrite(DR3, LOW);
		digitalWrite(DR4, HIGH);
#endif
		analogWrite(DRA, SpeedA);
		analogWrite(DRB, SpeedB);
#ifdef DBG // ���������� ��� DBG
		Serial.print('B');
		Serial.print("\t");
		Serial.print(SpeedA);
		Serial.print("\t");
		Serial.println(SpeedB);
#endif
	}

	void Car::Right(uint8_t Speed) {
#ifdef REVERSE // ���������� ��� REVERSE
		digitalWrite(DR2, LOW);
		digitalWrite(DR3, LOW);
		digitalWrite(DR4, LOW);
		digitalWrite(DR1, HIGH);
#else // ���������� ��� REVERSE
		digitalWrite(DR1, LOW);
		digitalWrite(DR2, LOW);
		digitalWrite(DR4, LOW);
		digitalWrite(DR3, HIGH);
#endif
		analogWrite(DRA, Speed);
		analogWrite(DRB, Speed);
#ifdef DBG // ���������� ��� DBG
		Serial.println('R');
#endif

	}

	void Car::Left(uint8_t Speed) {
#ifdef REVERSE // ���������� ��� REVERSE
		digitalWrite(DR1, LOW);
		digitalWrite(DR2, LOW);
		digitalWrite(DR4, LOW);
		digitalWrite(DR3, HIGH);
#else// ���������� ��� REVERSE
		digitalWrite(DR2, LOW);
		digitalWrite(DR3, LOW);
		digitalWrite(DR4, LOW);
		digitalWrite(DR1, HIGH);
#endif
		analogWrite(DRA, Speed);
		analogWrite(DRB, Speed);
#ifdef DBG // ���������� ��� DBG
		Serial.println('L');
#endif

	}

	void Car::Round(uint8_t Speed)
	{
#ifdef REVERSE // ���������� ��� REVERSE
		digitalWrite(DR1, HIGH);
		digitalWrite(DR4, HIGH);
		digitalWrite(DR2, LOW);
		digitalWrite(DR3, LOW);
#else // ���������� ��� REVERSE
		digitalWrite(DR1, LOW);
		digitalWrite(DR4, LOW);
		digitalWrite(DR2, HIGH);
		digitalWrite(DR3, HIGH);
#endif
		analogWrite(DRA, Speed);
		analogWrite(DRB, Speed);
#ifdef DBG // ���������� ��� DBG
		Serial.println('L');
#endif

	}

	void Car::Arret(){
		
		for (uint8_t i = 0; i < 4; i++) {

			digitalWrite(DriverArray[i], LOW);
		}
#ifdef DBG // ���������� ��� DBG
		Serial.println('-');
#endif
	}

	void Car::SetDriver() {
		for (uint8_t i = 0; i < 7; i++) {

			pinMode(DriverArray[i], OUTPUT);
		}
	}

	void Car::SetLights(uint8_t FLight){
		this -> FLight = FLight;
		pinMode(FLight, OUTPUT);
	}

	void Car::FrontEndLight(bool flag){
		digitalWrite(FLight, flag);
	}

	void Car::SetBuzzer(uint8_t Buzz){   
		this -> Buzz = Buzz;
		pinMode(Buzz, OUTPUT);
	}


	void Car::Beep(bool flag) {
		analogWrite(Buzz, BuzzerSound * flag);

	}	

}

