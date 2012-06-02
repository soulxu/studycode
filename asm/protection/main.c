#include "util.h"

int main_exec() {
   int i = 0;
   char *hello = "Hello world!";

   print_init();

   for (i = 0; i < 12; i++) {
       print_char(hello[i], 'b');
   }

   while(1) {}
}
