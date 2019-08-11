#include "Arduino.h"  // Стандартная бибилиотека Ардуино

#ifndef Diplom_Car_h  // Если библиотека Diplom_Car не подключена
#define Diplom_Car_h  // тогда подключаем ее

/*   Эта библиотека преднозначена для дипломного проекта, !!!!! 

*/
namespace Diplom { // Наше пространство имен
	class Car { // Наш класс
	
	public:
		/***прототипы функций в классе библиотеки***/
	   Car(uint8_t _DR1, uint8_t _DR2, uint8_t _DR3, uint8_t _DR4, uint8_t _DRA, uint8_t _DRB); // Конструктор. В конструкторе заключены основные состовные выводы драйвера L298N
	   /*Основные позможности машинки*/
	   void Advance(uint8_t Speed); // Езда вперед, с равномерной скоростью
	   void Advance(uint8_t SpeedA, uint8_t SpeedB); // Езда вперед, с неравномерной скоростью
	   void Back(uint8_t Speed); // Езда назад, с равномерной скоростью 
	   void Back(uint8_t SpeedA, uint8_t SpeedB);// Езда назад, с неравномерной скоростью
	   void Right(uint8_t Speed); // Езда в право
	   void Left(uint8_t Speed); // Езда в лево
	   void Round(uint8_t Speed); // Езда по кругу
	   void Arret(); // Сотоп. Arret с французского стоп
	   void SetDriver(); // Установка пинов. Вынесенна как отдельная функция для наглядности 
	   /*Дополнительные возможности для машинки*/
	   void SetLights(uint8_t FLight); // Инциализировать передние фары, перегрузка только для одних фар
	   void FrontEndLight(bool flag); // Зажигание передних огней
	   void SetBuzzer(uint8_t buzz); // Объявления порта пищалки 
	   void Beep(bool flag); // функция для пищалки 

	   uint8_t BuzzerSound; // переменная для значения громкости пищалки
	   
	protected: 
		/***переменные в классе библиотеки***/
		/*вводы модуля L298N*/
		uint8_t DR1;
		uint8_t DR2;
		uint8_t DR3;
		uint8_t DR4;
		uint8_t DRA;
		uint8_t DRB;
		uint8_t DriverArray[6] = { DR1,DR2,DR3,DR4,DRA,DRB }; // Массив для удобного использования
		/*Другие вводы*/
		uint8_t FLight; // Фары
		uint8_t Buzz; // Пищалка

	};
	
}

#endif
