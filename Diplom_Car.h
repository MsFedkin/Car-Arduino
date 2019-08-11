#include "Arduino.h"  // ����������� ����������� �������

#ifndef Diplom_Car_h  // ���� ���������� Diplom_Car �� ����������
#define Diplom_Car_h  // ����� ���������� ��

/*   ��� ���������� ������������� ��� ���������� �������, !!!!! 

*/
namespace Diplom { // ���� ������������ ����
	class Car { // ��� �����
	
	public:
		/***��������� ������� � ������ ����������***/
	   Car(uint8_t _DR1, uint8_t _DR2, uint8_t _DR3, uint8_t _DR4, uint8_t _DRA, uint8_t _DRB); // �����������. � ������������ ��������� �������� ��������� ������ �������� L298N
	   /*�������� ����������� �������*/
	   void Advance(uint8_t Speed); // ���� ������, � ����������� ���������
	   void Advance(uint8_t SpeedA, uint8_t SpeedB); // ���� ������, � ������������� ���������
	   void Back(uint8_t Speed); // ���� �����, � ����������� ��������� 
	   void Back(uint8_t SpeedA, uint8_t SpeedB);// ���� �����, � ������������� ���������
	   void Right(uint8_t Speed); // ���� � �����
	   void Left(uint8_t Speed); // ���� � ����
	   void Round(uint8_t Speed); // ���� �� �����
	   void Arret(); // �����. Arret � ������������ ����
	   void SetDriver(); // ��������� �����. ��������� ��� ��������� ������� ��� ����������� 
	   /*�������������� ����������� ��� �������*/
	   void SetLights(uint8_t FLight); // ��������������� �������� ����, ���������� ������ ��� ����� ���
	   void FrontEndLight(bool flag); // ��������� �������� �����
	   void SetBuzzer(uint8_t buzz); // ���������� ����� ������� 
	   void Beep(bool flag); // ������� ��� ������� 

	   uint8_t BuzzerSound; // ���������� ��� �������� ��������� �������
	   
	protected: 
		/***���������� � ������ ����������***/
		/*����� ������ L298N*/
		uint8_t DR1;
		uint8_t DR2;
		uint8_t DR3;
		uint8_t DR4;
		uint8_t DRA;
		uint8_t DRB;
		uint8_t DriverArray[6] = { DR1,DR2,DR3,DR4,DRA,DRB }; // ������ ��� �������� �������������
		/*������ �����*/
		uint8_t FLight; // ����
		uint8_t Buzz; // �������

	};
	
}

#endif
