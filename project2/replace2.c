#include <stdio.h>
#include <string.h>
#include "document.h"

int main() {
   Document doc;
   const char *doc_name = "Testing Replace";
   int data_lines = 8;
   char data[20][MAX_STR_SIZE + 1] = {
	"The next course youyou youwill take is cmsc216.",
   };

   init_document(&doc, doc_name);
   load_document(&doc, data, data_lines);
   remove_text(&doc, "you");
   print_document(&doc);

   return 0;
}