ENTRY (reset_handler)

MEMORY{
    FLASH(rx): ORIGIN = 0x08000000, LENGTH = 512K
    SRAM(rxw): ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS{

    .text : 
    {
        KEEP(*(.isr_vectors))
        *(.text)
        *(.rodata)
        . = ALIGN(4);
        _etext = .;
        _la_data = _etext;  
    }> FLASH

    .data :
    {
        _startData = .;
        *(.data);
        . = ALIGN(4);
        _endData = .;
    }>SRAM AT> FLASH

    .bss : 
    {
        . = ALIGN(4);
        _startBss = .;
        *(.bss);
        . = ALIGN(4);
        _endBss = .;
    }> SRAM

}