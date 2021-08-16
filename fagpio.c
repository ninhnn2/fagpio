#include "fagpio.h"

struct cpu_peripheral gpio = {GPIO_PAGE_OFFSET};

// Exposes the physical address defined in the passed structure using mmap on /dev/mem
int map_peripheral(struct cpu_peripheral *p) {
	// Open /dev/mem
	if ((p->mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
		printf("Failed to open /dev/mem, try checking permissions.\n");
		return -1;
	}

	p->map = mmap(
				NULL,
				BLOCK_SIZE,
				PROT_READ|PROT_WRITE,
				MAP_SHARED,
				p->mem_fd,  // File descriptor to physical memory virtual file '/dev/mem'
				p->addr_p      // Address in physical map that we want this memory block to expose
				);

	if (p->map == MAP_FAILED) {
		perror("mmap");
		return -1;
	}

	p->addr = (volatile unsigned int *)p->map;

	return 0;
}

void unmap_peripheral(struct cpu_peripheral *p) {
	munmap(p->map, BLOCK_SIZE);
	close(p->mem_fd);
}

//int main(void) {

//	if(map_peripheral(&gpio) == -1) {
//		printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
//		return -1;
//	}

//	pinMode(4, 1);
//	pinMode(5, 1);
//	pinMode(6, 1);
//	pinMode(7, 1);

//	while(1) {
//		digitalWrite(4, 1);
//		digitalWrite(5, 1);
//		digitalWrite(6, 1);
//		digitalWrite(7, 1);

//		digitalWrite(4, 0);
//		digitalWrite(5, 0);
//		digitalWrite(6, 0);
//		digitalWrite(7, 0);

//	}

//	unmap_peripheral(&gpio);

//	return 0;
//}

/*
PE_CFG0: PE Configure Register 0: Offset: 0x90

PIN         BIT            OUTPUT            INPUT

PE0        2:0              001               000
PE1        6:4              001               000
PE3        10:8             001               000
PE4        14:12            001               000
PE5        22:20            001               000
PE6        26:24            001               000
PE7        30:28            001               000

BIT
32                                            0
  PE7   PE6   PE5   PE4   PE3   PE2   PE1   PE0
0 000 0 000 0 000 0 000 0 000 0 000 0 000 0 000

*/

int fagpio_setup(void) {
		if(map_peripheral(&gpio) == -1) {
			printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
			return -1;
		}
		return 0;
}

void fagpio_free(void) {
	unmap_peripheral(&gpio);
}

void pinMode(uint8_t Pin, uint8_t Mode) {
	volatile unsigned int PE_CFG0;
	PE_CFG0 = *(volatile unsigned int *)((unsigned char*)gpio.addr + PIO_ADDR_PORT + rPE_CFG0);
	volatile unsigned int MASK_CONFIG = (~(15 << (4*Pin)));
	volatile unsigned int MASK_X      = (1 << (4*Pin));
	*(volatile unsigned int *)((unsigned char*)gpio.addr + GPIO_BASE_OFFSET+rPE_CFG0)=((PE_CFG0 & MASK_CONFIG)|MASK_X);
}

void digitalWrite(uint8_t pin, uint8_t value) {
	if(value == 1) {
		volatile unsigned int PE_DAT;
		volatile unsigned int MASK_CONFIG = (~(1 << (pin)));
		volatile unsigned int MASK_X      = (1 << (pin));
		PE_DAT=*(volatile unsigned int *)((unsigned char*)gpio.addr + GPIO_BASE_OFFSET+rPE_DAT);
		*(volatile unsigned int *)((unsigned char*)gpio.addr + GPIO_BASE_OFFSET + rPE_DAT)=((PE_DAT & MASK_CONFIG)|MASK_X);
	}
	else if(value == 0) {
		volatile unsigned int PE_DAT;
		volatile unsigned int MASK_CONFIG = (~(1 << (pin)));
		PE_DAT=*(volatile unsigned int *)((unsigned char*)gpio.addr + GPIO_BASE_OFFSET+rPE_DAT);
		*(volatile unsigned int *)((unsigned char*)gpio.addr + GPIO_BASE_OFFSET + rPE_DAT)=((PE_DAT & MASK_CONFIG));
	}
}



