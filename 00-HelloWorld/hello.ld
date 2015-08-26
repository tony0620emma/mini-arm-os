
MEMORY
{
	FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 128K
}

SECTIONS
{
	.text :
	{
		KEEP(*(.isr_vector))
		*(.text)
	} >FLASH
}
