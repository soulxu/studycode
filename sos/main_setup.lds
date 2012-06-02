SECTIONS
{
.text 0x100000 : { main_setup.o (.text) }
.text : {* (.text) }
.data : { *(.data) }
.edata 0x100000+0xffe : 
{ 
   BYTE(0x55);
   BYTE(0xaa);
}
}
