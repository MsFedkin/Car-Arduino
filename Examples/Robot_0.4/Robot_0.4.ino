
// определение режима соединения и подключение библиотеки RemoteXY  
#define REMOTEXY_MODE__HARDSERIAL
// подключение библиотек
#include <RemoteXY.h> 
#include <Diplom_Car.h>

// настройки соединения  
#define REMOTEXY_SERIAL Serial 
#define REMOTEXY_SERIAL_SPEED 9600 


// конфигурация интерфейса   
#pragma pack(push, 1) 

uint8_t RemoteXY_CONF[] = 
  { 255,8,0,0,0,185,0,8,28,0,
  1,0,72,9,12,12,3,31,208,146,
  0,1,0,61,19,12,12,6,31,208,
  155,0,1,0,72,30,12,12,12,31,
  208,157,0,1,0,83,19,12,12,1,
  31,208,159,0,3,6,45,11,8,42,
  2,26,2,0,10,9,26,12,2,26,
  31,31,208,146,208,154,208,155,0,208,
  146,208,171,208,154,208,155,0,2,0,
  66,46,26,13,2,26,31,31,208,161,
  208,162,208,158,208,159,0,208,147,208,
  144,208,151,0,129,0,17,3,12,4,
  17,208,164,208,176,209,128,209,139,0,
  129,0,66,3,24,4,17,208,163,208,
  191,209,128,208,176,208,178,208,187,208,
  181,208,189,208,184,208,181,0,1,0,
  12,32,21,21,2,31,208,145,208,152,
  208,159,33,0,129,0,17,26,11,4,
  17,208,147,209,131,208,180,208,190,208,
  186,0 }; 
   
// структура определяет все переменные вашего интерфейса управления  
struct { 

    // входные переменные
  // input variable
  uint8_t F_button; // =1 если кнопка нажата, иначе =0 
  uint8_t L_button; // =1 если кнопка нажата, иначе =0 
  uint8_t B_button; // =1 если кнопка нажата, иначе =0 
  uint8_t R_button; // =1 если кнопка нажата, иначе =0 
  uint8_t SpeedSwitch; // =0 если переключатель в положении A, =1 если в положении B, =2 если в положении C, ... 
  uint8_t LED_switch; // =1 если переключатель включен и =0 если отключен 
  uint8_t Arret_flag; // =1 если переключатель включен и =0 если отключен 
  uint8_t Buzzer_button; // =1 если кнопка нажата, иначе =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY; 
#pragma pack(pop) 

// ***объявление пинов***
// пины для Драйвера L298N
#define IN1 5 
#define IN2 6
#define IN3 7
#define IN4 8
#define ENA 9
#define ENB 10
// фары
#define FRONT_LED 12
// пищалка
#define CAR_BUZZER 11
// Сумма кнопак
#define SUMBUTTON RemoteXY.F_button + RemoteXY.B_button + RemoteXY.R_button +  RemoteXY.L_button
// Полином кнопак в двоичной системе
#define POLYNOMBUTTON  RemoteXY.F_button*8 + RemoteXY.B_button*4 + RemoteXY.R_button*2 +  RemoteXY.L_button*1 

#define DBG
const uint8_t SpeedCollection [6] = {80,115,150,185,220,255}; // набор скоростей 
Diplom :: Car car (IN1,IN2,IN3,IN4,ENA,ENB); // объявляем объект car

void setup()  
{ 
#ifdef DBG // подключение последовательного порта при отладке
 Serial.begin(9600); 
#endif
  RemoteXY_Init (); // инициализация Bluetooth интерфейса
  RemoteXY.SpeedSwitch = 0; // присваеваем нулевую скорость  
  
  car.SetDriver(); // инициализация портов драйвера
  car.SetLights(FRONT_LED); // инициализация порта светодиодов
  car.SetBuzzer(CAR_BUZZER); // инициализация порта пищалки
  car.BuzzerSound = 80; // установления значения громкости пищалки
   
} 

void loop()  
{ 
  // передания пакетов информации по Bluetooth 
  RemoteXY_Handler (); 
  // вкл/выкл светодиодов 
  car.FrontEndLight(RemoteXY.LED_switch);
  // вкл/выкл пищалки  
  car.Beep(RemoteXY.Buzzer_button);  
  // тормаз, если флаг = истина возврат в начало кода  
  if(RemoteXY.Arret_flag == HIGH)return; 
  // управление скорости для поворотов 
  volatile uint8_t sub;
  RemoteXY.SpeedSwitch < 2? sub = 0: sub = 2;
  // проверка на количество нажатых кнопак
  if (SUMBUTTON < 2) goto oneB; // если нажата 1 кнопка идем по лейблу oneB 
  else goto twoB; // если нажата 2 кнопки идем по лейблу twoB 

  oneB: 
  switch(POLYNOMBUTTON){ // выбор движение по значению полинома 
    case 1:car.Left(SpeedCollection[RemoteXY.SpeedSwitch]); // движение влево
    break;
    case 2:car.Right(SpeedCollection[RemoteXY.SpeedSwitch]); // движение вправо
    break;
    case 4:car.Back(SpeedCollection[RemoteXY.SpeedSwitch]); // движение назад
    break;
    case 8:car.Advance(SpeedCollection[RemoteXY.SpeedSwitch]); // движение вперед
    break;
    default:car.Arret(); // стоп
  }
  
  return; // разгранечение 
  
  twoB:
  switch(POLYNOMBUTTON){ // выбор движение по значению полинома 
    case 3: car.Round(SpeedCollection[RemoteXY.SpeedSwitch]); // движение по кругу
    break; 
    case 5:car.Back(SpeedCollection[RemoteXY.SpeedSwitch-sub],SpeedCollection[RemoteXY.SpeedSwitch]); // движение назад и влево
    break;
    case 6:car.Back(SpeedCollection[RemoteXY.SpeedSwitch],SpeedCollection[RemoteXY.SpeedSwitch-sub]); // движение назад и вправо
    break;
    case 9:car.Advance(SpeedCollection[RemoteXY.SpeedSwitch],SpeedCollection[RemoteXY.SpeedSwitch-sub]); // движение вперед и влево
    break;
    case 10:car.Advance(SpeedCollection[RemoteXY.SpeedSwitch-sub],SpeedCollection[RemoteXY.SpeedSwitch]); // движение вперед и вправо
    break;
    default:car.Arret(); // стоп 
  }
                           
}
