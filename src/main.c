#include<stdint.h>
#include<stdbool.h>

/* ENDEREÇO BASE DO MÓDULO RCC (RESET AND CONTROL CLOCK) */

#define BASE_RCC_STM32 0x40023800 /* 0x40023800 - 0x40023bff */

/* ENDEREÇO BASE DO GPIOA*/

#define BASE_GPIOA_STM32 0x40020000U /* 0x40020000 - 0x400203FF: GPIOA*/

/* ENDEREÇO BASE DO GPIOC*/

#define BASE_GPIOC_STM32 0x48000800U /* 0x48000800-0x48000bff: GPIOC*/

/* OFFSET DOS REGISTRADORES*/

#define OFFSET_RCC_AHB1ENR_STM32 0x0030  /*OFFSET DPCLOCK ENABLE DO BARRAMENTO AHB1*/

#define OFFSET_MODER_GPIO_STM32  0x0000 /* GPIO port do mode register */
#define OFFSET_OTYPER_GPIO_STM32 0x0004 /* GPIO port do output type register */
#define OFFSET_PUPDR_GPIO_STM32  0x000c /* GPIO port do pull-up/pull-down register */
#define OFFSET_BSRR_GPIO_STM32   0x0018 /* GPIO port bit set/reset register */
#define OFFSET_IDR_GPIO_STM32    0x0010  /* GPIO port input data register */
#define OFFSET_ODR_GPIO_STM32    0x0014  /* GPIO port output data register */

/* ENDEREÇO DOS REGISTRADORES*/

#define AHB2ENR_RCC_STM32 (BASE_RCC_STM32 + OFFSET_RCC_AHB1ENR_STM32) /* ENDEREÇO DO CLOCK ENABLE DO BARRAMENTO AHB1*/


/* ENDEREÇO DOS REGISTRADORES P/ GPIOA */

#define MODER_GPIOA_STM32  (BASE_GPIOA_STM32+OFFSET_MODER_GPIO_STM32)
#define PUPDR_GPIOA_STM32  (BASE_GPIOA_STM32+OFFSET_PUPDR_GPIO_STM32)
#define IDR_GPIOA_STM32    (BASE_GPIOA_STM32+OFFSET_IDR_GPIO_STM32)


/* ENDEREÇO DOS REGISTRADORES P/ GPIOC */

#define MODER_GPIOC_STM32  (BASE_GPIOC_STM32+OFFSET_MODER_GPIO_STM32)
#define OTYPER_GPIOC_STM32 (BASE_GPIOC_STM32+OFFSET_OTYPER_GPIO_STM32)
#define PUPD_GPIOC_STM32   (BASE_GPIOC_STM32+OFFSET_PUPDR_GPIO_STM32)
#define BSRR_GPIOC_STM32   (BASE_GPIOC_STM32+OFFSET_BSRR_GPIO_STM32)
#define ODR_GPIOC_STM32    (BASE_GPIOC_STM32+OFFSET_ODR_GPIO_STM32)



/* BIT CLOCK ENABLE*/

#define RCC_AHB1ENR_GPIOAEN (1 << 0) /* Bit 0 GPIOAEN: IO port A clock enable */
#define RCC_AHB1ENR_GPIOCEN (1 << 2) /* Bit 2 GPIOCEN: IO port C clock enable */



/* GPIO port mode register */

#define GPIO_MODER_INPUT     (0) /* Input */
#define GPIO_MODER_OUTPUT    (1) /* General purpose output mode */
#define GPIO_MODER_ALT       (2) /* Alternate mode */
#define GPIO_MODER_ANALOG    (3) /* Analog mode */
#define GPIO_MODER_SHIFT(n)  (n << 1)
#define GPIO_MODER_MASK(n)   (3 << GPIO_MODER_SHIFT(n))

/* GPIO port output type register */
/*Opções*/

#define GPIO_OTYPER_PP      (0) /* 0=Output push-pull */
#define GPIO_OTYPER_OD      (1) /* 1=Output open-drain */
#define GPIO_OT_SHIFT(n)    (n)
#define GPIO_OT_MASK(n)     (1 << GPIO_OT_SHIFT(n))


/* GPIO port pull-up/pull-down register */
/*Opções*/

#define GPIO_PUPDR_NONE        (0) /* No pull-up, pull-down */
#define GPIO_PUPDR_PULLUP      (1) /* Pull-up */
#define GPIO_PUPDR_PULLDOWN    (2) /* Pull-down */
#define GPIO_PUPDR_SHIFT(n)    (n)
#define GPIO_PUPDR_MASK(n)     (3 << (n << 1))


/* GPIO port input data register */

#define GPIO_IDR_MASK(n)    (1 << n)


/* GPIO port bit set/reset register */
#define GPIO_BSRR_SET(n) (1 << (n))
#define GPIO_BSRR_RST(n) (1 << (n + 16))

/* LED Delay */
#define LED_DELAY_LOW_frequency   10000
#define LED_DELAY_HIGH_frequency  100


void delay (uint32_t time_delay){
    uint32_t i;
    for(i=0; i<time_delay; i++){
        asm("nop");
    }
}

bool botton_pressed (uint32_t *pGPIOA_IDR){
    uint32_t reg;
    reg = *pGPIOA_IDR;
    reg &= GPIO_IDR_MASK(0);
    return !reg;
}


int main (int argc, char *argv[]){
    
    uint32_t reg;

    /* Ponteiros para registradores do GPIOC*/
    uint32_t *pRCC_AHB1ENR  = (uint32_t *)RCC_AHB1ENR_GPIOCEN;

    uint32_t *pGPIOC_MODER  = (uint32_t *)MODER_GPIOC_STM32;
    uint32_t *pGPIOC_OTYPER = (uint32_t *)OTYPER_GPIOC_STM32;
    uint32_t *pGPIOC_PUPDR  = (uint32_t *)PUPD_GPIOC_STM32;
    uint32_t *pGPIOC_BSRR   = (uint32_t *)BSRR_GPIOC_STM32;

    /* Ponteiros para registradores do GPIOA*/

    uint32_t *pGPIOA_MODER  = (uint32_t *)MODER_GPIOA_STM32;
    uint32_t *pGPIOA_PUPDR  = (uint32_t *)PUPDR_GPIOA_STM32;
    uint32_t *pGPIOA_IDR    = (uint32_t *)IDR_GPIOA_STM32;

    /* Habilita clock GPIOC */
    reg = *pRCC_AHB1ENR;
    reg |= RCC_AHB1ENR_GPIOAEN;
    reg |= RCC_AHB1ENR_GPIOCEN;
    *pRCC_AHB1ENR = reg;

    /* Configura PC13 como saida pull-up off e pull-down off */
    reg = *pGPIOC_MODER;
    reg &= ~GPIO_MODER_MASK(13);
    reg |= (GPIO_MODER_OUTPUT << GPIO_MODER_SHIFT(13));
    *pGPIOC_MODER = reg;

    reg = *pGPIOC_OTYPER;
    reg &= ~(GPIO_OT_MASK(13));
    reg |= (GPIO_OTYPER_PP << GPIO_OT_SHIFT(13));
    *pGPIOC_OTYPER = reg;

    reg = *pGPIOC_PUPDR;
    reg &= ~(GPIO_PUPDR_MASK(13));
    reg |= (GPIO_PUPDR_NONE << GPIO_PUPDR_SHIFT(13));
    *pGPIOC_PUPDR = reg;

    /* Configura PA0 como saida pull-up on e pull-down off */
    reg = *pGPIOA_MODER;
    reg &= ~GPIO_MODER_MASK(0);
    reg |= (GPIO_MODER_INPUT << GPIO_MODER_SHIFT(0));
    *pGPIOA_MODER = reg;

    reg = *pGPIOA_PUPDR;
    reg &= ~GPIO_PUPDR_MASK(0);
    reg |= (GPIO_PUPDR_PULLUP << GPIO_PUPDR_SHIFT(0));
    *pGPIOA_PUPDR = reg;


    while(1){

        /*Liga o led*/
        *pGPIOC_BSRR = GPIO_BSRR_SET(13);
        delay(botton_pressed(pGPIOA_IDR) ? LED_DELAY_LOW_frequency : LED_DELAY_HIGH_frequency);

        /*Liga o led*/
        *pGPIOC_BSRR = GPIO_BSRR_RST(13);
        delay(botton_pressed(pGPIOA_IDR) ? LED_DELAY_LOW_frequency : LED_DELAY_HIGH_frequency);

    }

    return 0;
}