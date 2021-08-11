#include <linux/input.h>
#include <linux/input-event-codes.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
    const int NUM_KEYS = 249;
    const int ARG_LENGTH = 20;
    const int MAX_ARGS = 20;
    char validChars[NUM_KEYS][2];
    for (int i = 0; i < NUM_KEYS; i++)
    {
        switch (i)
        {
        case KEY_0:
            validChars[i][0] = '0';
            validChars[i][1] = '0';
            break;
        case KEY_1:
            validChars[i][0] = '1';
            validChars[i][1] = '1';
            break;
        case KEY_2:
            validChars[i][0] = '2';
            validChars[i][1] = '2';
            break;
        case KEY_3:
            validChars[i][0] = '3';
            validChars[i][1] = '3';
            break;
        case KEY_4:
            validChars[i][0] = '4';
            validChars[i][1] = '4';
            break;
        case KEY_5:
            validChars[i][0] = '5';
            validChars[i][1] = '5';
            break;
        case KEY_6:
            validChars[i][0] = '6';
            validChars[i][1] = '6';
            break;
        case KEY_7:
            validChars[i][0] = '7';
            validChars[i][1] = '7';
            break;
        case KEY_8:
            validChars[i][0] = '8';
            validChars[i][1] = '8';
            break;
        case KEY_9:
            validChars[i][0] = '9';
            validChars[i][1] = '9';
            break;
        case KEY_A:
            validChars[i][0] = 'A';
            validChars[i][1] = 'a';
            break;
        case KEY_B:
            validChars[i][0] = 'B';
            validChars[i][1] = 'b';
            break;
        case KEY_C:
            validChars[i][0] = 'C';
            validChars[i][1] = 'c';
            break;
        case KEY_D:
            validChars[i][0] = 'D';
            validChars[i][1] = 'd';
            break;
        case KEY_E:
            validChars[i][0] = 'E';
            validChars[i][1] = 'e';
            break;
        case KEY_F:
            validChars[i][0] = 'F';
            validChars[i][1] = 'f';
            break;
        case KEY_G:
            validChars[i][0] = 'G';
            validChars[i][1] = 'g';
            break;
        case KEY_H:
            validChars[i][0] = 'H';
            validChars[i][1] = 'h';
            break;
        case KEY_I:
            validChars[i][0] = 'I';
            validChars[i][1] = 'i';
            break;
        case KEY_J:
            validChars[i][0] = 'J';
            validChars[i][1] = 'j';
            break;
        case KEY_K:
            validChars[i][0] = 'K';
            validChars[i][1] = 'k';
            break;
        case KEY_L:
            validChars[i][0] = 'L';
            validChars[i][1] = 'l';
            break;
        case KEY_M:
            validChars[i][0] = 'M';
            validChars[i][1] = 'm';
            break;
        case KEY_N:
            validChars[i][0] = 'N';
            validChars[i][1] = 'n';
            break;
        case KEY_O:
            validChars[i][0] = 'O';
            validChars[i][1] = 'o';
            break;
        case KEY_P:
            validChars[i][0] = 'P';
            validChars[i][1] = 'p';
            break;
        case KEY_Q:
            validChars[i][0] = 'Q';
            validChars[i][1] = 'q';
            break;
        case KEY_R:
            validChars[i][0] = 'R';
            validChars[i][1] = 'r';
            break;
        case KEY_S:
            validChars[i][0] = 'S';
            validChars[i][1] = 's';
            break;
        case KEY_T:
            validChars[i][0] = 'T';
            validChars[i][1] = 't';
            break;
        case KEY_U:
            validChars[i][0] = 'U';
            validChars[i][1] = 'u';
            break;
        case KEY_V:
            validChars[i][0] = 'V';
            validChars[i][1] = 'v';
            break;
        case KEY_W:
            validChars[i][0] = 'W';
            validChars[i][1] = 'w';
            break;
        case KEY_X:
            validChars[i][0] = 'X';
            validChars[i][1] = 'x';
            break;
        case KEY_Y:
            validChars[i][0] = 'Y';
            validChars[i][1] = 'y';
            break;
        case KEY_Z:
            validChars[i][0] = 'Z';
            validChars[i][1] = 'z';
            break;
        case KEY_MINUS:
            validChars[i][0] = '_';
            validChars[i][1] = '-';
            break;
        default:
            validChars[i][0] = 0;
            validChars[i][1] = 1;
            break;
        }
    }
    
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
    int fd;
    int len;
    if(argc < 2) {
        printf("usage: %s <device>\n", argv[0]);
        callErrorSound(1);
        return 1;
    }
    
    fd = open(argv[1], O_RDWR);
    
    if (fd < 0)
    {
        callErrorSound(2);
        exit(2);
    }
    struct input_event ev;

    /*
     * Waits for a split second to let any keystrokes that triggered the program
     * (i.e. the enter key used to execute the terminal command) to be processed)
     */
    sleep(1);
    
    int grabCode = ioctl(fd, EVIOCGRAB, 1);
    if (grabCode < 0)
    {
        /*
         * Something else probably has it
         */
        exit(4);
    }
    
    callSound("triggerActivate.wav");
    
    while (len >= 0 && ev.value != 0 || waitEnter == 0 || (ev.code != KEY_ENTER && ev.code != KEY_ESC))
    {
        len = read(fd, &ev, sizeof(struct input_event));

        if (len < 0)
        {
            break;
        }
        
        if ((ev.code == KEY_ENTER || ev.code == KEY_ESC) && ev.value == 1)
        {
            waitEnter = 1;
        }
        if (ev.type == 1 && ev.value == 1)
        {
            //printf("Keycode: %i, status %i\n", ev.code, ev.value);
            if ((ev.code == KEY_SPACE || ev.code == KEY_ENTER) && index > 0)
            {
                if (ev.code == KEY_SPACE)
                {
                    callSound("bit.wav");
                }
                BUFFER[index] = '\0';
                ARGS[numArgs++] = BUFFER;
                BUFFER = (char*) calloc(ARG_LENGTH, sizeof(char));
                index = 0;
            }
            else if (ev.code < NUM_KEYS && validChars[ev.code][1] != 0)
            {
                if (index < ARG_LENGTH)
                {
                    BUFFER[index++] = validChars[ev.code][1];
                    BUFFER[index] = '\0';
                    callSound("bit.wav");
                }
            }
        }
    }
    ioctl(fd, EVIOCGRAB, 0);
    
    close(fd);
    ARGS[numArgs] = NULL;
    
    if (len < 0)
    {
        callErrorSound(3);
        exit(3);
    }
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
