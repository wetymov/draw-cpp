# draw-cpp
Репозиторий лабораторной работы по дисциплине "Теория и технологии программирования"
* нужно сделать базовый класс item просто отдельный, это класс должен быть базовым у всех фигур;
* в нем будет метод draw, который будет чисто виртуальным
* в нем будет метод move, который будет чисто виртуальным
* в нем будет метод get_type, который будет чисто виртуальным
* в нем будет метод get_name, который будет чисто виртуальным
* классы линия и дуга и для них базовый класс точка привязки (класс фигура, являющаяся родительской)
* класс как раз хранит координаты точки привязки, а линия - координаты относительно точки привязки
* Чтобы подвинуть линию надо подвинуть точку привязки
* Тоже самое с дугой, там гвоздь привязан к центру, центр задается относительно гвоздя
* Надо сделать несколько объектов линия, дуга
* Сделать массив указателей на точку привязки, присвоить им заданные линии и дуги
* Затем в цикле передвинуть все фигуры на определение значения (влево/вправо/вверх/вниз), то есть сделать move - метод в фигуре - стереть старую линию,

Затем в цикле передвинуть все фигуры на определение значения (влево/вправо/вверх/вниз), то есть сделать move - метод в фигуре - стереть старую линию,
поменять точку привязки, нарисовать новую линию
Функция draw с флагом false/true где false - стереть, true - нарисовать;
Уничтожить хорошо бы что-нибудь еще
Код должен быть коротенький
Дальше реализовать сегмент как единую фигуру - производный от линии и дуги, надо как-то две точки привязки сократить до одной,
фигура должна наследоваться виртуально
сделать сектор по аналогии с сегментом (две линии и дуга)
короче список и там каждый объект себя расписывает по содержимому я линия я дуга я сектор я сегмент, при удалении оно должно удаляться
