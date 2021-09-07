# File:   Makefile
# Author: Hayley Krippner & Nitish Singh
# Date:   12 October 2020
# Descr:  Makefile for the game, 'Rock, Paper and  Scissors'.

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../utils -I../../fonts -I../../drivers -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: game.out


# Compile: create object files from C source files.
game.o: game.c ../../drivers/avr/system.h mainGame.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

mainGame.o: mainGame.c mainGame.h ../../drivers/avr/system.h ../../drivers/display.h ../../fonts/font5x7_1.h ../../utils/font.h ../../utils/pacer.h ../../utils/tinygl.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

mainGameDisplay.o: mainGameDisplay.c mainGameDisplay.h ../../utils/tinygl.c ../../drivers/avr/system.h ../../drivers/display.h ../../utils/font.h ../../utils/tinygl.h ../../drivers/avr/timer.h ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@

gameLogic.o: gameLogic.c gameLogic.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

stateOne.o: stateOne.c stateOne.h mainGameDisplay.h ../../drivers/avr/system.h ../../fonts/font5x7_1.h ../../utils/pacer.h ../../utils/tinygl.h ../../drivers/avr/ir_uart.h ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@

stateTwo.o: stateTwo.c stateTwo.h ../../drivers/avr/system.h ../../drivers/display.h ../../fonts/font5x7_1.h ../../utils/font.h ../../utils/pacer.h ../../utils/tinygl.h ../../drivers/avr/ir_uart.h
	$(CC) -c $(CFLAGS) $< -o $@

stateThree.o: stateThree.c stateThree.h mainGameDisplay.h gameLogic.h ../../drivers/avr/system.h ../../fonts/font5x7_1.h ../../utils/font.h ../../utils/pacer.h ../../utils/tinygl.h ../../drivers/avr/ir_uart.h
	$(CC) -c $(CFLAGS) $< -o $@

stateFour.o: stateFour.c stateFour.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

stateFive.o: stateFive.c stateFive.h ../../drivers/avr/system.h mainGameDisplay.h
	$(CC) -c $(CFLAGS) $< -o $@



ir_uart.o: ../../drivers/avr/ir_uart.c ../../drivers/avr/ir_uart.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/avr/timer0.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

prescale.o: ../../drivers/avr/prescale.c ../../drivers/avr/prescale.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

timer0.o: ../../drivers/avr/timer0.c ../../drivers/avr/bits.h ../../drivers/avr/prescale.h ../../drivers/avr/system.h ../../drivers/avr/timer0.h
	$(CC) -c $(CFLAGS) $< -o $@

usart1.o: ../../drivers/avr/usart1.c ../../drivers/avr/system.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../../drivers/display.c ../../drivers/avr/system.h ../../drivers/display.h ../../drivers/ledmat.h ../../drivers/led.h
	$(CC) -c $(CFLAGS) $< -o $@

ledmat.o: ../../drivers/ledmat.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../drivers/navswitch.c ../../drivers/avr/delay.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../utils/font.c ../../drivers/avr/system.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: ../../utils/pacer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h ../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../utils/tinygl.c ../../drivers/avr/system.h ../../drivers/display.h ../../utils/font.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@




# Link: create ELF output file from object files.
game.out: game.o mainGame.o ir_uart.o pio.o prescale.o system.o timer.o timer0.o usart1.o display.o ledmat.o navswitch.o font.o pacer.o tinygl.o mainGameDisplay.o gameLogic.o stateOne.o stateTwo.o stateThree.o stateFour.o stateFive.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean:
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: game.out
	$(OBJCOPY) -O ihex game.out game.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start


