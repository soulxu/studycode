SECTIONS
{
.text 0x7c00 : { boot.o(.text) }
.text : { p.o(.text) }
.edata 0x7c00+0x1fe : 
{ 
   BYTE(0x55);
   BYTE(0xaa);
}
}
