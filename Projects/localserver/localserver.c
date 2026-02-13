#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>

bool pythonAvailable();
bool startServer();
char* getIp();

void handle_exit(int sig);


int main(){


    // for handling <Ctrl-c>
    signal(SIGINT, handle_exit);
    char ouputBuffer[BUFSIZ];
    char *iP;
    // the server commands
    const char serverOpenCmd[] = "python3 -I -m  http.server 8000";
    const char sudoPortCreate[] = "sudo ufw allow 8000/tcp";
    const char portCloseCmd[] = "sudo ufw delete allow 8000/tcp > /dev/null 2>&1";

    char tempMessage[] = "To Establish a Temperory HTTP Server to the Local Network We Will Be Making Creating a port for 8000:\
                           \nWill Be Deleted on Exit.\n\nYou can exit This by <Ctrl-c>.\n\n";

    char portCloseMessage[] = "-\n--Closing Your Port, And Exiting Program----\n";
    char InstructionMessage[] = "\n... To Close This Program: To Exit <Ctrl-c>\n\n";
    char askToStartServer[] = "\nDo you want to start the server? [y, n]: ";
    char addressMessage[300] = "Type this address In any Browser URL: http://";
    char addressMessageAlt[] = "\n\nType this address In any Browser URL: http://{Your Ip}.8000";

    
    if (pythonAvailable()){
        // ask for port 
        printf("%s", tempMessage);
        (void)system(sudoPortCreate);

        if (startServer()){
            if ((iP = getIp()) != NULL){
                // span check to remove tailing space
                strcat(addressMessage, iP);
                printf("%s:8000\n", addressMessage);
            }
            free(iP);
            printf("%s", InstructionMessage);
            (void)system(serverOpenCmd);
        }
    }
    else{
        exit(EXIT_FAILURE);
    }

    // exit logic 
    printf("%s", portCloseMessage);
    (void)system(portCloseCmd);

    return EXIT_SUCCESS;
}

void handle_exit(int sig){
    printf("\n----Closing Your Port, And Exiting Program----\n");
    (void)system("sudo ufw delete allow 8000/tcp > /dev/null 2>&1");
    exit(0);
}

char *getIp(){
    int size = 30;
    char *iP = (char *)malloc(size*sizeof(char));
    char iPCmd[] = "hostname -I";
    FILE *fp = popen(iPCmd, "r");
    if (fp != NULL){
        if (fgets(iP, size, fp) != NULL){
            iP[strcspn(iP, "\r\n ")] = 0;
        }
        return iP;
    }
    return NULL;
}

bool startServer(){
    char askToStartServer[] = "\nDo you want to start the server? [y, n]: ";
    char c;
    printf("%s", askToStartServer);
    while ((c = getchar()) != 'n' && (c != 'y')){
        printf("%s", askToStartServer);
    }
    if (c == 'n'){
        return false;
    }
    return true;
}

bool pythonAvailable(){

    const char pyVersion[] = "python3 --version";
    const char expectedOuput[] = "Python 3.";
    FILE *fp;
    char buff[200];
    bool pyavail = false;

    // accessing python version from terminal 
    fp = popen(pyVersion, "r");
    if (fp == NULL){
        fprintf(stderr, "Could not execute command in your terminal: Loser :)\n"); 
    }
    else {
        fgets(buff, sizeof(buff), fp);
        if (strncasecmp(buff, expectedOuput, strlen(expectedOuput)) == 0){
            pyavail = true;
        }
        else {
            fprintf(stderr, "Your Terminal does not have : Python or Current Version < 3.0\n"); 
        }
    }
    fclose(fp);
    return pyavail;
}
/*
 *
 * idea:
 * so have a c script execute python -m http.server 8000 
 * and no exit do exit process
 *
 * */
