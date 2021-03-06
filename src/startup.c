#include<stdint.h>

#define SRAM_START 0x20000000                         /*Início da SRAM para Cortex M*/
#define SRAM_SIZE (128u * 1024u)                      /*Tamanho da SRAM para STM32F411 - 128k* (Obs: o u representa um número unsignal)*/
#define SRAM_END ((SRAM_START)+ (SRAM_SIZE))          /*O fim da pilha SRAM para STM32F411*/

#define STACK_START (SRAM_END)                        /*O ínicio da stack: o SP(stack pointer) inicia e decrescendo*/

int main(void);

void reset_handler      (void);
void nmi_handler        (void) __attribute__ ((weak, alias("default_handler")));
void hardfault_handler  (void) __attribute__ ((weak, alias("default_handler")));
void memmanage_handler  (void) __attribute__ ((weak, alias("default_handler")));
void busfault_handler   (void) __attribute__ ((weak, alias("default_handler")));
void usagefault_handler (void) __attribute__ ((weak, alias("default_handler")));
void svc_handler        (void) __attribute__ ((weak, alias("default_handler")));
void debugmon_handler   (void) __attribute__ ((weak, alias("default_handler")));
void pendsv_handler     (void) __attribute__ ((weak, alias("default_handler")));
void systick_handler    (void) __attribute__ ((weak, alias("default_handler")));
void wwdg_handler       (void) __attribute__ ((weak, alias("default_handler")));
void exti16_pvd_handler (void) __attribute__ ((weak, alias("default_handler")));
void exti21_ps_handler  (void) __attribute__ ((weak, alias("default_handler")));
void exti22_rw_handler  (void) __attribute__ ((weak, alias("default_handler")));
void flash_handler      (void) __attribute__ ((weak, alias("default_handler")));
void rcc_handler        (void) __attribute__ ((weak, alias("default_handler")));
void exti0_handler      (void) __attribute__ ((weak, alias("default_handler")));
void exti1_handler      (void) __attribute__ ((weak, alias("default_handler")));
void exti2_handler      (void) __attribute__ ((weak, alias("default_handler")));
void exti3_handler      (void) __attribute__ ((weak, alias("default_handler")));
void exti4_handler      (void) __attribute__ ((weak, alias("default_handler")));
void dma1s0_handler     (void) __attribute__ ((weak, alias("default_handler")));
void dma1s1_handler     (void) __attribute__ ((weak, alias("default_handler")));
void dma1s2_handler     (void) __attribute__ ((weak, alias("default_handler")));
void dma1s3_handler     (void) __attribute__ ((weak, alias("default_handler")));
void dma1s4_handler     (void) __attribute__ ((weak, alias("default_handler")));
void dma1s5_handler     (void) __attribute__ ((weak, alias("default_handler")));
void dma1s6_handler     (void) __attribute__ ((weak, alias("default_handler")));
void adc_handler        (void) __attribute__ ((weak, alias("default_handler")));
void exti95_handler     (void) __attribute__ ((weak, alias("default_handler")));
void tim1_brk_9_handler (void) __attribute__ ((weak, alias("default_handler")));
void tim1_up_10_handler (void) __attribute__ ((weak, alias("default_handler")));
void tim1_trg_11_handler(void) __attribute__ ((weak, alias("default_handler")));
void tim1_cc_handler    (void) __attribute__ ((weak, alias("default_handler")));
void tim2_handler       (void) __attribute__ ((weak, alias("default_handler")));
void tim3_handler       (void) __attribute__ ((weak, alias("default_handler")));
void tim4_handler       (void) __attribute__ ((weak, alias("default_handler")));
void i2c1_ev_handler    (void) __attribute__ ((weak, alias("default_handler")));
void i2c1_er_handler    (void) __attribute__ ((weak, alias("default_handler")));
void i2c2_ev_handler    (void) __attribute__ ((weak, alias("default_handler")));
void i2c2_er_handler    (void) __attribute__ ((weak, alias("default_handler")));
void spi1_handler       (void) __attribute__ ((weak, alias("default_handler")));
void spi2_handler       (void) __attribute__ ((weak, alias("default_handler")));
void usart1_handler     (void) __attribute__ ((weak, alias("default_handler")));
void usart2_handler     (void) __attribute__ ((weak, alias("default_handler")));
void exti15_10_handler  (void) __attribute__ ((weak, alias("default_handler")));
void exti17_RTC_handler (void) __attribute__ ((weak, alias("default_handler")));
void exti18_OTG_handler (void) __attribute__ ((weak, alias("default_handler")));
void dma1_s7_handler    (void) __attribute__ ((weak, alias("default_handler")));
void sdio_handler       (void) __attribute__ ((weak, alias("default_handler")));
void tim5_handler       (void) __attribute__ ((weak, alias("default_handler")));
void spi3_handler       (void) __attribute__ ((weak, alias("default_handler")));
void dma2_s0_handler    (void) __attribute__ ((weak, alias("default_handler")));
void dma2_s1_handler    (void) __attribute__ ((weak, alias("default_handler")));
void dma2_s2_handler    (void) __attribute__ ((weak, alias("default_handler")));
void dma2_s3_handler    (void) __attribute__ ((weak, alias("default_handler")));
void dma2_s4_handler    (void) __attribute__ ((weak, alias("default_handler")));
void otg_fs_handler     (void) __attribute__ ((weak, alias("default_handler")));
void dma2_s5_handler    (void) __attribute__ ((weak, alias("default_handler")));
void dma2_s6_handler    (void) __attribute__ ((weak, alias("default_handler")));
void dma2_s7_handler    (void) __attribute__ ((weak, alias("default_handler")));
void usart6_handler     (void) __attribute__ ((weak, alias("default_handler")));
void i2c3_ev_handler    (void) __attribute__ ((weak, alias("default_handler")));
void i2c3_er_handler    (void) __attribute__ ((weak, alias("default_handler")));
void fpu_handler        (void) __attribute__ ((weak, alias("default_handler")));
void spi4_handler       (void) __attribute__ ((weak, alias("default_handler")));
void spi5_handler       (void) __attribute__ ((weak, alias("default_handler")));





/* Variaveis exportadas pelo linker script */

extern uint32_t _startData;     /* Inicio da secao .data */
extern uint32_t _endData;       /* Fim da secao .data */
extern uint32_t _la_data;       /* Endereco de carga na RAM da secao .data */
extern uint32_t _startBss;      /* Inicio da secao .bss */
extern uint32_t _endBss;        /* Fim da secao .bss */


uint32_t vectors[] __attribute__((section(".isr_vectors"))) =
{
    STACK_START,                    /* 0x0000 0000 */
    (uint32_t)reset_handler,        /* 0x0000 0004 */
    (uint32_t)nmi_handler,          /* 0x0000 0008 */
    (uint32_t)hardfault_handler,    /* 0x0000 000c */
    (uint32_t)memmanage_handler,    /* 0x0000 0010 */
    (uint32_t)busfault_handler,     /* 0x0000 0014 */
    (uint32_t)usagefault_handler,   /* 0x0000 0018 */
    0,                              /* 0x0000 001c */
    0,                              /* 0x0000 0020 */
    0,                              /* 0x0000 0024 */
    0,                              /* 0x0000 0028 */
    (uint32_t)svc_handler,          /* 0x0000 002c */
    (uint32_t)debugmon_handler,     /* 0x0000 0030 */
    0,                              /* 0x0000 0034 */
    (uint32_t)pendsv_handler,       /* 0x0000 0038 */
    (uint32_t)systick_handler,      /* 0x0000 003c */
    (uint32_t)wwdg_handler,         /* 0x0000 0040 */
    (uint32_t)exti16_pvd_handler,   /* 0x0000 0044 */
    (uint32_t)exti21_ps_handler,    /* 0x0000 0048 */
    (uint32_t)exti22_rw_handler,    /* 0x0000 004C */
    (uint32_t)flash_handler,        /* 0x0000 0050 */
    (uint32_t)rcc_handler,          /* 0x0000 0054 */
    (uint32_t)exti0_handler,        /* 0x0000 0058 */
    (uint32_t)exti1_handler,        /* 0x0000 005C */
    (uint32_t)exti2_handler,        /* 0x0000 0060 */
    (uint32_t)exti3_handler,        /* 0x0000 0064 */
    (uint32_t)exti4_handler,        /* 0x0000 0068 */
    (uint32_t)dma1s0_handler,       /* 0x0000 006C */
    (uint32_t)dma1s1_handler,       /* 0x0000 0070 */
    (uint32_t)dma1s2_handler,       /* 0x0000 0074 */
    (uint32_t)dma1s3_handler,       /* 0x0000 0078 */
    (uint32_t)dma1s4_handler,       /* 0x0000 007C */
    (uint32_t)dma1s5_handler,       /* 0x0000 0080 */
    (uint32_t)dma1s6_handler,       /* 0x0000 0084 */
    (uint32_t)adc_handler,          /* 0x0000 0088 */
    (uint32_t)adc_handler,          /* 0x0000 008C */
    (uint32_t)adc_handler,          /* 0x0000 0090 */
    (uint32_t)adc_handler,          /* 0x0000 0094 */
    (uint32_t)adc_handler,          /* 0x0000 0098 */
    (uint32_t)exti95_handler,       /* 0x0000 009C */
    (uint32_t)tim1_brk_9_handler,   /* 0x0000 00A0 */
    (uint32_t)tim1_up_10_handler,   /* 0x0000 00A4 */
    (uint32_t)tim1_trg_11_handler,  /* 0x0000 00A8 */
    (uint32_t)tim1_cc_handler,      /* 0x0000 00AC */
    (uint32_t)tim2_handler,         /* 0x0000 00B0 */
    (uint32_t)tim3_handler,         /* 0x0000 00B4 */
    (uint32_t)tim4_handler,         /* 0x0000 00B8 */
    (uint32_t)i2c1_ev_handler,      /* 0x0000 00BC */
    (uint32_t)i2c1_er_handler,      /* 0x0000 00C0 */
    (uint32_t)i2c2_ev_handler,      /* 0x0000 00C4 */
    (uint32_t)i2c2_er_handler,      /* 0x0000 00C8 */
    (uint32_t)spi1_handler,         /* 0x0000 00CC */
    (uint32_t)spi2_handler,         /* 0x0000 00D0 */
    (uint32_t)usart1_handler,       /* 0x0000 00D4 */
    (uint32_t)usart2_handler,       /* 0x0000 00D8 */
    (uint32_t)usart2_handler,       /* 0x0000 00DC */
    (uint32_t)exti15_10_handler,    /* 0x0000 00E0 */
    (uint32_t)exti17_RTC_handler,   /* 0x0000 00E4 */
    (uint32_t)exti18_OTG_handler,   /* 0x0000 00E8 */
    (uint32_t)exti18_OTG_handler,   /* 0x0000 00EC */
    (uint32_t)exti18_OTG_handler,   /* 0x0000 00F0 */
    (uint32_t)exti18_OTG_handler,   /* 0x0000 00F4 */
    (uint32_t)exti18_OTG_handler,   /* 0x0000 00F8 */
    (uint32_t)dma1_s7_handler,      /* 0x0000 00FC */
    (uint32_t)dma1_s7_handler,      /* 0x0000 0100 */
    (uint32_t)sdio_handler,         /* 0x0000 0104 */
    (uint32_t)tim5_handler,         /* 0x0000 0108 */
    (uint32_t)spi3_handler,         /* 0x0000 010C */
    (uint32_t)spi3_handler,         /* 0x0000 0110 */
    (uint32_t)spi3_handler,         /* 0x0000 0114 */
    (uint32_t)spi3_handler,         /* 0x0000 0118 */
    (uint32_t)spi3_handler,         /* 0x0000 011C */
    (uint32_t)dma2_s0_handler,      /* 0x0000 0120 */
    (uint32_t)dma2_s1_handler,      /* 0x0000 0124 */
    (uint32_t)dma2_s2_handler,      /* 0x0000 0128 */
    (uint32_t)dma2_s3_handler,      /* 0x0000 012C */
    (uint32_t)dma2_s4_handler,      /* 0x0000 0130 */
    (uint32_t)dma2_s4_handler,      /* 0x0000 0134 */
    (uint32_t)dma2_s4_handler,      /* 0x0000 0138 */
    (uint32_t)dma2_s4_handler,      /* 0x0000 013C */
    (uint32_t)dma2_s4_handler,      /* 0x0000 0140 */
    (uint32_t)dma2_s4_handler,      /* 0x0000 0144 */
    (uint32_t)dma2_s4_handler,      /* 0x0000 0148 */
    (uint32_t)otg_fs_handler,       /* 0x0000 014C */
    (uint32_t)dma2_s5_handler,      /* 0x0000 0150 */
    (uint32_t)dma2_s6_handler,      /* 0x0000 0154 */
    (uint32_t)dma2_s7_handler,      /* 0x0000 0158 */
    (uint32_t)usart6_handler,       /* 0x0000 015C */
    (uint32_t)i2c3_ev_handler,      /* 0x0000 0160 */
    (uint32_t)i2c3_er_handler,      /* 0x0000 0164 */
    (uint32_t)i2c3_er_handler,      /* 0x0000 0168 */
    (uint32_t)i2c3_er_handler,      /* 0x0000 016C */
    (uint32_t)i2c3_er_handler,      /* 0x0000 0170 */
    (uint32_t)i2c3_er_handler,      /* 0x0000 0174 */
    (uint32_t)i2c3_er_handler,      /* 0x0000 0178 */
    (uint32_t)i2c3_er_handler,      /* 0x0000 017C */
    (uint32_t)i2c3_er_handler,      /* 0x0000 0180 */
    (uint32_t)fpu_handler,          /* 0x0000 0184 */
    (uint32_t)fpu_handler,          /* 0x0000 0188 */
    (uint32_t)fpu_handler,          /* 0x0000 018C */
    (uint32_t)spi4_handler,         /* 0x0000 0190 */
    (uint32_t)spi5_handler,         /* 0x0000 0194 */

};

void reset_handler (void){
    /*
        Objetivos do reset handler:
            - copiar os dados da seção .data para a memória SRAM
            - preencher com zero a seção .bss 
            - chamar a função main() (obs: esta função no main.c)
    */
    
    uint32_t i; 

    /* Copiar os dados da seção .data para a memória SRAM*/
    uint32_t size = (uint32_t)&_endData - (uint32_t)&_startData;
    uint8_t *pDst = (uint8_t*)&_startData;                          /* SRAM  */
    uint8_t *pSrc = (uint8_t*)&_endData;                             /* FLASH */

    for(i=0; i<size; i++){
        *pDst = *pSrc++;
    }

    /* Preenche a secao .bss com */

    size = (uint32_t)&_endBss - (uint32_t)&_startBss;
    pDst = (uint8_t*)&_startBss;
    for(i=0; i<size; i++){
        *pDst = 0;
    }

    /* Chama a função main() */

    main();
}

void default_handler(void){
    while(1){};
}