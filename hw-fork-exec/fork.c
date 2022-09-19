#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	int pid;
	int child_status;
	int pipefd[2];

	printf("Starting program; process has pid %d\n", getpid());

	FILE * fp; fp = fopen("fork-output.txt", "w+"); 
	fprintf(fp, "%s", "BEFORE FORK\n");
   fflush(fp);
	
	
	pipe(pipefd);


	if ((pid = fork()) < 0) {
		fprintf(stderr, "Could not fork()");
		exit(1);
	}

	/* BEGIN SECTION A */

	fprintf(fp, "%s", "SECTION A\n");
	fflush(fp); 

	printf("Section A;  pid %d\n", getpid());
	//sleep(30);

	/* END SECTION A */
	if (pid == 0) {
		/* BEGIN SECTION B */
		fprintf(fp, "%s", "SECTION B\n");
      fflush(fp);
      FILE * fd_one = fdopen(pipefd[1],"w");
      fputs( "hello from Section B\n", fd_one);

		close(pipefd[0]);

		printf("Section B\n");
		//sleep(30);
		//sleep(30);
		printf("Section B done sleeping\n");

		// NEW CODE
		char *newenviron[] = { NULL };


		printf("Program \"%s\" has pid %d. Sleeping.\n", argv[0], getpid());
		//sleep(30);

		if (argc <= 1) {
			printf("No program to exec.  Exiting...\n");
			exit(0);
		}

		printf("Running exec of \"%s\"\n", argv[1]);
		int file_descriptor = fileno(fp);
      dup2(fileno(fp), 1);
		execve(argv[1], &argv[1], newenviron);
		printf("End of program \"%s\".\n", argv[0]);
		// NEW CODE END

		exit(0);

		/* END SECTION B */
	} else {
		/* BEGIN SECTION C */

		fprintf(fp, "%s", "SECTION C\n");
      fflush(fp); 
		wait(&child_status);

		close(pipefd[1]);
      FILE * fd;
      fd = fdopen(pipefd[0],"r");
		char buf[100];
      fgets(buf,100,fd);
      fputs(buf,stdout);  

		printf("Section C\n");
		//sleep(30);
		printf("Section C done sleeping\n");

		exit(0);

		/* END SECTION C */
	}
	/* BEGIN SECTION D */

	printf("Section D\n");
	//sleep(30);

	/* END SECTION D */
}

