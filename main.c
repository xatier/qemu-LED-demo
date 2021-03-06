#define delay() \
do { \
	register unsigned int i; \
	for (i = 0; i < 100000; ++i) \ 
	__asm__ __volatile__ ("nop\n\t":::"memory"); \
} while (0)

typedef unsigned int uint32_t;


//----------------------------------------------------------------
// Constantes: Address
//----------------------------------------------------------------

//GPIO_B - LEDs
#define RCC_AHBENR 0x4002381c /* Reset and clock control enbable register */
#define GPIOB 0x40020400 /* GPIO_B */
#define GPIOB_MODER (GPIOB + 0x00) /* Mode register */
#define GPIOB_ODR (GPIOB + 0x14) /* Output data register */

//LED pins
#define GPIOB_PIN_BLUE_LED (1 << 6) /* port B, pin 6 */
#define GPIOB_PIN_GREEN_LED (1 << 7) /* port B, pin 7 */

//----------------------------------------------------------------
// Fonctions: LEDs
//----------------------------------------------------------------

static inline void switch_leds_on(void) {
	*(volatile uint32_t*)GPIOB_ODR = GPIOB_PIN_BLUE_LED | GPIOB_PIN_GREEN_LED;
}

static inline void switch_leds_off(void) {
	*(volatile uint32_t*)GPIOB_ODR = 0;
}

static inline void setup_leds(void)
{
	*(volatile uint32_t*)RCC_AHBENR |= (1 << 1);
	*(volatile uint32_t*)GPIOB_MODER |= (1 << (7 * 2)) | (1 << (6 * 2)); /* Configure port 6 and 7 as output */
}

void SystemInit(void){
	setup_leds();
	switch_leds_off();
}

void main(void) {
	SystemInit();
	
	while(1) {
		switch_leds_on();
		delay();
		switch_leds_off();
		delay();
	}
}

