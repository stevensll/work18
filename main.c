#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <errno.h>
#include <fcntl.h>

#include <ctype.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1
#define MAX_INPUT_SIZE 1000

int main(){
    int running = 1;
    int pc[2];
    int cp[2];
    pipe(pc);
    pipe(cp);
    // while(running){
        // printf("%s", input);
        int f = fork();
        //CHILD needs only W for CP and READ from PC
        if(f == 0){
            close(pc[WRITE]); //child wont need parent to child write
            close(cp[READ]); //child won't need child to parent read

            char buff[MAX_INPUT_SIZE];
            read(pc[READ], buff, sizeof(buff));
            buff[strlen(buff)-1] = '\0';
            int i;
            int len = strlen(buff);
            for(i = 0; i < len; i++){
                if (buff[i] >= 'a' && buff[i] <= 'z') buff[i] -= 32;
            }
            write(cp[WRITE], buff, sizeof(buff));
            return 0;
        }
        //PARENT needs only W for PC and READ from CP
        else {
            close(pc[READ]);
            close(cp[WRITE]);

            printf("Please enter an input (no more than 1000 chars):\n");
            char input[MAX_INPUT_SIZE];
            fgets(input, sizeof(input), stdin);

            write(pc[WRITE], input, sizeof(input));
           
            int status;
            wait(&status);
           
            char output[MAX_INPUT_SIZE];
            read(cp[READ], output, sizeof(output));
            printf("Output: %s\n", output);
        }
    // }
    return 0;
}