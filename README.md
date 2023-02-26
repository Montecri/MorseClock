# PICMorseClock

![ezgif-3-ada55f94c0](https://user-images.githubusercontent.com/38574378/221368142-74aa8a26-9c00-403d-9cce-baf0d1a795c5.gif)

A PIC16 based Morse Code Clock

It will blink green once a second, on the top of every minute will blink the hours in blue and the minutes in red following the morse code pattern for numbers, if picked up the tilt sensor will be activated and the alien tune from Close Encounters will play on the buzzer, followed by a multitude of colors blinking on the RGB led.

Parts list:

- PIC16F1827
- DS1037 RTC
- NBR18650B Li-Ion Battery
- 18650 battery holder
- TP4056 charging module
- Piezo buzzer
- 10mm RGB led
- Resistors (3 x 150, 100 and 10k Ohms)
- Tilt switch

PWM code based on:

- https://github.com/leozulfiu/pic16f88-piezobuzzer

![Morse Clock Sketch2_bb-Modificado](https://user-images.githubusercontent.com/38574378/221368391-db06acdf-d253-488d-a0c6-89eb9fa72cd5.png)

Reference:

https://www.linkedin.com/pulse/pic-tac-dit-dah-microcontroller-based-morse-code-clock-monteiro
