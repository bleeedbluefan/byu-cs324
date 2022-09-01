/*1. 1, 2, 3
      2. 1,2
      3. 2,3
      4. 2
      5. 
            #include <sys/types.h>
            #include <sys/stat.h>
            #include <fcntl.h>

      6. 2, 7
      7. SO_ACCEPTCONN
      8. 3
      9. Null-terminated
      10. A positive integer

2. I completed the TMUX exercise from part 2.
*/


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define MAX 400

int main(int argc, char* argv []) {
   // Print Pid
   int pid_t = getpid();
	fprintf(stderr, "%d", pid_t);
   printf("\n\n");

   // Open file
   FILE *file_handle;
   file_handle = fopen(argv[1], "r");
   if (file_handle == NULL) {
      printf("Cannot open file \n");
      exit(1);
   }

   // Read and print
   char line[MAX], *result;
   char *point = getenv("CATMATCH_PATTERN");
   

   while ((result = fgets(line, MAX, file_handle)) != NULL) {
      if (point != NULL) {
         if (strstr(result, point) != NULL) {
            fprintf(stdout, "1 ");
         } else {
            fprintf(stdout, "0 ");
         }
      }
      else {
         fprintf(stdout, "0 ");
      }
      fprintf(stdout, "%s",result);
   }
   //printf("\n");
   fclose(file_handle);
   return 0;
}