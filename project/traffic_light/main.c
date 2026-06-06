#include <stdint.h>

#define RCC_BASE         0x40021000UL
#define GPIOA_BASE       0x40010800UL

#define RCC_APB2ENR      (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define GPIOA_CRL		 (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_CRH		 (*(volatile uint32_t *)(GPIOA_BASE + 0x04))
#define GPIOA_BSRR		 (*(volatile uint32_t *)(GPIOA_BASE + 0x10))

void delay(int t) {
	while (t--)
		;
}

void GPIOA_MOD(int num, int mod) {
	if (!(RCC_APB2ENR & (1 << 2)))RCC_APB2ENR |= (1 << 2);
	int mod_value = 0;
	switch (mod) {
	case 0:
		mod_value = 0b0000;
		break;
	case 1:
		mod_value = 0b0011;
		break;
	default:
		return;
	}
	if (num >= 0 && num <= 7) {
		GPIOA_CRL &= ~(0b1111 << 4 * num);
		GPIOA_CRL |= (mod_value << 4 * num);
	} else if (num >= 8 && num <= 15) {
		GPIOA_CRH &= ~(0b1111 << 4 * (num - 8));
		GPIOA_CRH |= (mod_value << 4 * (num - 8));
	} else {
		return;
	}
}

void GIOPA_IO_BSRR(char lights[17]) {
	uint32_t temp = 0;
	for (int i = 0; i < 16; i++) {
		switch (lights[i]) {
		case '1':
			temp |= (1 << i);
			break;
		case '0':
			temp |= (1 << (i + 16));
			break;
		default:
			return;
		}
	}
	GPIOA_BSRR = temp;
}

int main() {

	GPIOA_MOD(0, 1);
	GPIOA_MOD(1, 1);
	GPIOA_MOD(2, 1);

	while (1) {
		int t;

		GIOPA_IO_BSRR("1000000000000000");
		delay(5000000);
		t = 3;
		while (t--) {
			GIOPA_IO_BSRR("0000000000000000");
			delay(1000000);
			GIOPA_IO_BSRR("1000000000000000");
			delay(1000000);
		}

		GIOPA_IO_BSRR("0100000000000000");
		delay(1000000);
		t = 3;
		while (t--) {
			GIOPA_IO_BSRR("0000000000000000");
			delay(1000000);
			GIOPA_IO_BSRR("0100000000000000");
			delay(1000000);
		}
		GIOPA_IO_BSRR("0010000000000000");
		delay(5000000);
		t = 3;
		while (t--) {
			GIOPA_IO_BSRR("0000000000000000");
			delay(1000000);
			GIOPA_IO_BSRR("0010000000000000");
			delay(1000000);
		}
	}
}
