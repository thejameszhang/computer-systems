#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "photoalbum.h"
#include "my_memory_checker_216.h"

int main() {
   Album album;
   
   /*start_memory_check();*/ /* Start memory check */

   initialize_album(&album);
   add_photo_to_album(&album, 0, "Computer"); 
   add_photo_to_album(&album, 1, "Car"); 
   add_photo_to_album(&album, 2, "TV");
   add_photo_to_album(&album, 3, NULL);
   add_photo_to_album(&album, 4, "Jack");
   add_photo_to_album(&album, 5, "Dank");
   add_photo_to_album(&album, 6, "sdjkf");
   add_photo_to_album(&album, 7, "skdjfssdkj");
   print_album(&album);
   destroy_album(&album);
   print_album(&album);

   /*stop_memory_check();*/ /* End memory check */

   return EXIT_SUCCESS;
}