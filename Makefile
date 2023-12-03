device := atmega328p
cpufreq := 16000000
port := /dev/ttyACM0
flags := -O1 -I Inc/
 
default:
		avr-gcc $(flags) -DF_CPU=$(cpufreq) -mmcu=$(device) -c -o main.o Src/main.c
		avr-gcc $(flags) -DF_CPU=$(cpufreq) -mmcu=$(device) -c -o system_time.o Src/system_time.c
		avr-gcc $(flags) -DF_CPU=$(cpufreq) -mmcu=$(device) -c -o sw_pwm.o Src/sw_pwm.c
		avr-gcc $(flags) -DF_CPU=$(cpufreq) -mmcu=$(device) -c -o i2c.o Src/i2c.c
		avr-gcc $(flags) -DF_CPU=$(cpufreq) -mmcu=$(device) -c -o ssd1306.o Src/ssd1306.c
		avr-gcc $(flags) -DF_CPU=$(cpufreq) -mmcu=$(device) -c -o drv8825.o Src/drv8825.c
		avr-gcc $(flags) -DF_CPU=$(cpufreq) -mmcu=$(device) -c -o adc.o Src/adc.c
		avr-gcc $(flags) -DF_CPU=$(cpufreq) -mmcu=$(device) -c -o jitterplot.o Src/jitterplot.c
		avr-gcc $(flags) -DF_CPU=$(cpufreq) -mmcu=$(device) -c -o static_letter_function.o Src/static_letter_function.c
		avr-gcc $(flags) -mmcu=$(device) -o main.bin main.o system_time.o sw_pwm.o i2c.o ssd1306.o drv8825.o adc.o jitterplot.o static_letter_function.o
		avr-objcopy -O ihex -R .eeprom main.bin main.hex

		rm -rf *.o
		rm -rf *.bin

		avrdude -F -V -c avrisp -p $(device) -P $(port) -b 57600 -U flash:w:main.hex

clean:
	
	rm -rf *.hex

