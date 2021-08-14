#include <linux/input.h>
#include <linux/input-event-codes.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/wait.h>

int msleep(long time)
{
    struct timespec timeDet;
    int res;
    timeDet.tv_sec = time / 1000;
    timeDet.tv_nsec = (time % 1000) * 1000000;
    
    do
    {
        res = nanosleep(&timeDet, &timeDet);
    }
    while (res && errno == EINTR);
    
    return res;
}

int callSound(char* path)
{
    int child = fork();
    if (child == 0)
    {
        char finalPath[60];
        strcpy(finalPath, getenv("HOME"));
        strcat(finalPath, "/.local/share/sounds/");
        strcat(finalPath, path);
        
        execlp("ffmpeg", "ffmpeg", "-loglevel", "error", "-i", finalPath, "-f", "alsa", "default", NULL);
    }
    else if (child < 0)
    {
        printf("Could not generate sound %s\n", path);
        exit(5);
    }
    else
    {
        return child;
    }
}

void callErrorSound(int code)
{
    int returnCode = callSound("error.wav");
    wait(NULL);
    for (int i = 0; i < code; i++)
    {
        returnCode = callSound("bit.wav");
        wait(NULL);
    }
}

int main(int argc, char **argv)
{
    const int BUFFER_LENGTH = 120;
    const int ARG_LENGTH = 20;
    const int MAX_ARGS = 20;
    
    /*
     * We need this command for when we trigger the app from the command line,
     * because otherwise the upstroke on the enter key will kill the app.
     */
    int waitEnter = 0;
    char* ARGS[MAX_ARGS];
    int numArgs = 0;
    ARGS[numArgs++] = "play";
    //ARGS[numArgs++] = "--directory=/home/markil3/.local/share/lollypop";
    char* BUFFER = (char*) calloc(ARG_LENGTH, sizeof(char));
    int index = 0;
    BUFFER[index] = '\0';
    FILE* fd;
    int len;
    
    fd = fopen("/tmp/play_args.txt", "r");
    
    if (fd < 0)
    {
        callErrorSound(1);
        exit(1);
    }
    
    do
    {
        len = fscanf(fd, "%s", BUFFER);

        if (len < 0)
        {
            break;
        }
        
        ARGS[numArgs++] = BUFFER;
        BUFFER = (char*) calloc(ARG_LENGTH, sizeof(char));
    }
    while (len >= 0);
    
    fclose(fd);
    ARGS[numArgs] = NULL;
    
    if (index > 0)
    {
        /*
         * If index was not reset, then we canceled.
         */
        callSound("end.wav");
        exit(0);
    }
    
    callSound("triggerDeactivate.wav");
    
    printf("Running args: ");
    for (int i = 0; i <= numArgs; i++)
    {
        printf("'%s' ", ARGS[i]);
    }
    printf("\n");
    
    execvp(ARGS[0], ARGS);
}
