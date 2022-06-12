#include<stdint.h>

/* ENDEREÇO BASE DO MÓDULO RCC (RESET AND CONTROL CLOCK) */

#define BASE_RCC_STM32 0x40023800 /* 0x40023800 - 0x40023bff */

/* ENDEREÇO BASE DO GPIOC*/

#define BASE_GPIOC_STM32 0x48000800U /* 0x48000800-0x48000bff: GPIO*/

/* OFFSET DOS REGISTRADORES*/

#define OFFSET_RCC_AHB1ENR_STM32 0x0030  /*OFFSET DPCLOCK ENABLE DO BARRAMENTO AHB1*/

#define OFFSET_MODER_GPIO_STM32 0x0000 /* GPIO port do mode register */
#define OFFSET_OTYPER_GPIO_STM32 0x0004 /* GPIO port do output type register */
#define OFFSET_PUPDR_GPIO_STM32 0x000c /* GPIO port do pull-up/pull-down register */
#define OFFSET_BSRR_GPIO_STM32 0x0018 /* GPIO port bit set/reset register */

/* ENDEREÇO DOS REGISTRADORES*/

#define AHB2ENR_RCC_STM32 (BASE_RCC_STM32 + OFFSET_RCC_AHB1ENR_STM32) /* ENDEREÇO DO CLOCK ENABLE DO BARRAMENTO AHB1*/

#define MODER_GPIOC_STM32 (BASE_GPIOC_STM32+OFFSET_MODER_GPIO_STM32)
#define OTYPER_GPIOC_STM32 (BASE_GPIOC_STM32+OFFSET_OTYPER_GPIO_STM32)
#define PUPD_GPIOC_STM32 (BASE_GPIOC_STM32+OFFSET_PUPDR_GPIO_STM32)
#define BSRR_GPIO_STM32 (BASE_GPIOC_STM32+ OFFSET_BSRR_GPIO_STM32)


/* BIT CLOCK ENABLE*/

#define RCC_AHB1ENR_GPIOCEN (1 << 2) /* Bit 2 GPIOCEN: IO port C clock enable */

/* GPIO port mode register */

#define GPIO_MODER_INPUT (0) /* Input */
#define GPIO_MODER_OUTPUT (1) /* General purpose output mode */
#define GPIO_MODER_ALT (2) /* Alternate mode */
#define GPIO_MODER_ANALOG (3) /* Analog mode */
#define GPIO_MODER13_SHIFT (26)
#define GPIO_MODER13_MASK (3 << GPIO_MODER13_SHIFT)

/* GPIO port output type register */
/*Opções*/

#define GPIO_OTYPER_PP (0) /* 0=Output push-pull */
#define GPIO_OTYPER_OD (1) /* 1=Output open-drain */
#define GPIO_OT13_SHIFT (13)
#define GPIO_OT13_MASK (1 << GPIO_OT13_SHIFT)


/* GPIO port pull-up/pull-down register */
/*Opções*/

#define GPIO_PUPDR_NONE (0) /* No pull-up, pull-down */
#define GPIO_PUPDR_PULLUP (1) /* Pull-up */
#define GPIO_PUPDR_PULLDOWN (2) /* Pull-down */
#define GPIO_PUPDR13_SHIFT (26)
#define GPIO_PUPDR13_MASK (3 << GPIO_PUPDR13_SHIFT)


/* GPIO port bit set/reset register */
#define GPIO_BSRR_SET(n) (1 << (n))
#define GPIO_BSRR_RST(n) (1 << (n + 16))

/* LED Delay */
#define LED_DELAY 100


int main (int argc, char *argv[]){
    
    uint32_t reg;

    /* Ponteiros para registradores */
    uint32_t *pRCC_AHB1ENR = (uint32_t *)RCC_AHB1ENR_GPIOCEN;
    uint32_t *pGPIOC_MODER = (uint32_t *)MODER_GPIOC_STM32;
    uint32_t *pGPIOC_OTYPER = (uint32_t *)OTYPER_GPIOC_STM32;
    uint32_t *pGPIOC_PUPDR = (uint32_t *)PUPD_GPIOC_STM32;
    uint32_t *pGPIOC_BSRR = (uint32_t *)BSRR_GPIO_STM32;



    /* Habilita clock GPIOC */
    reg = *pRCC_AHB1ENR;
    reg |= RCC_AHB1ENR_GPIOCEN;
    *pRCC_AHB1ENR = reg;


    /* Configura PC13 como saida pull-up off e pull-down off */
    reg = *pGPIOC_MODER;
    reg &= ~(GPIO_MODER13_MASK);
    reg |= (GPIO_MODER_OUTPUT << GPIO_MODER13_SHIFT);
    *pGPIOC_MODER = reg;
    reg = *pGPIOC_OTYPER;
    reg &= ~(GPIO_OT13_MASK);
    reg |= (GPIO_OTYPER_PP << GPIO_OT13_SHIFT);
    *pGPIOC_OTYPER = reg;
    reg = *pGPIOC_PUPDR;
    reg &= ~(GPIO_PUPDR13_MASK);
    reg |= (GPIO_PUPDR_NONE << GPIO_PUPDR13_SHIFT);
    *pGPIOC_PUPDR = reg;

    while(1){
        *pGPIOC_BSRR = GPIO_BSRR_SET(13);
        for(uint32_t i = 0; i < LED_DELAY; i++);
        *pGPIOC_BSRR = GPIO_BSRR_RST(13);
        for(uint32_t i = 0; i < LED_DELAY; i++);
    }

    return 0;
}