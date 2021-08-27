#ifndef _FAGPIO_H
#define _FAGPIO_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

#define MAP_SIZE			0x400							//MMU page size
#define GPIO_REG_BASE		0x01C20800						//GPIO physical base address (small page 4kb)
#define GPIO_BASE_OFFSET	(GPIO_REG_BASE & 0X00000FFF)	//GPIO base address offset calculation
#define GPIO_PAGE_OFFSET	(GPIO_REG_BASE & 0XFFFFF000)	//Get page offset

#define PIO_DAT_OFF			0x10
#define PIO_ADDR_PORT		0x800
#define INPUT				0
#define OUTPUT				1
#define DISABLE				2

#define HIGH				1
#define LOW					0

#define rPE_CFG0			0X90	//PE_CFG0 register address offset
#define rPE_DAT				0XA0	//PE_DAT register address offset
#define rPE_PULL0			0XAC	//PE_PULL0 register address offset
#define rPE_PULL1			0XB0	//PE_PULL1 register address offset

#define BLOCK_SIZE			0x4000

struct cpu_peripheral {
	unsigned long addr_p;
	int mem_fd;
	void *map;
	volatile unsigned int *addr;
};

int fagpio_setup(void);
void fagpio_free(void);

void pinMode(uint8_t Pin, uint8_t Mode);
void digitalWrite(uint8_t pin, uint8_t value);
uint8_t digitalRead(uint8_t pin);

#endif
