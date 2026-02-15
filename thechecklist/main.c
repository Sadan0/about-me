#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>

// datatypes 
enum FLAGOPTIONS {
    TASKDONE, // -c
    TASKADD, // -a
    TASKLIST, // -l
    DONELIST,  // --ld
    DELDONELIST, // --dd
    DELTASK // -d
};

#define NUMOFFLAGOPTIONS 6

struct UserRequest {
    enum FLAGOPTIONS flag;
    char *flagAragument;
};


// functions 
struct UserRequest *processUsrInput(int argc, char *argv[]);
void freeUsrReq(struct UserRequest*);
int parseData(struct UserRequest*);
char *getPath(char *filename);

int main(int argc, char *argv[])
{
    struct UserRequest *usrReq;
    if (argc < 2){
        printf("No: Input Given\n");
        exit(EXIT_FAILURE);
    }

    usrReq = processUsrInput(argc, argv);

    parseData(usrReq);
    
    freeUsrReq(usrReq);
    return EXIT_SUCCESS;
}


char *getPath(char *filename){
    char *home = getenv("HOME");
    if (!home) return NULL;

    char *dirPath = malloc(512);
    sprintf(dirPath, "%s/.config/chklist",  home);

    // if chklist does not exsist
    mkdir(dirPath, 0700);

    char *fullPath = malloc(500);
    sprintf(fullPath, "%s/%s",  dirPath, filename);

    free(dirPath);
    return fullPath;
}


int deldonelist(){

    char *donepath = getPath("done.csv");
    FILE *donefp = fopen(donepath, "w");

    if (!donefp){
        fprintf(stderr, "Could Not create the done.csv file.");
        return -1;
    }
    free(donepath);
    fclose(donefp);
    return 0;
}

int addtask(char *str){
    char *taskpath= getPath("task.csv");
    FILE *taskfp = fopen(taskpath, "a");

    if (taskfp ==  NULL){
        fprintf(stderr, "Could Not create the task.csv file.");
        return -1;
    }
    fprintf(taskfp, "%s\n", str); 
    free(taskpath);
    fclose(taskfp);
    return 0;
}

int taskdone(char *str){

    char buff[BUFSIZ];

    char *donepath = getPath("done.csv");
    FILE *donefp = fopen(donepath, "a");


    if (!donefp){
        fprintf(stderr, "1Could Not create the task.csv file OR done.csv\n");
        free(donepath);
        return -1;
    }
    char *temppath = getPath("temp.csv");
    FILE *tempfp = fopen(temppath, "a");
    if (!tempfp){
        fprintf(stderr, "1Coul Not create the task.csv file OR done.csv\n");
        free(donepath);
        free(temppath);
        fclose(donefp);
        return -1;
    }
    char *taskpath= getPath("task.csv");
    FILE *taskfp = fopen(taskpath, "r+");
    if (!taskfp){
        fprintf(stderr, "1Coul Not create the task.csv file OR done.csv\n");
        free(donepath);
        free(temppath);
        free(taskpath);
        fclose(donefp);
        fclose(tempfp);
        return -1;
    }

    int deltaskNumber = atoi(str);
    int taskNum = 1;
    while (fgets(buff, BUFSIZ, taskfp) != NULL){
        if (deltaskNumber == taskNum){
            fprintf(donefp, "%s", buff);
        }
        else {
            // add to temp file for later use
            fprintf(tempfp, "%s", buff);
        }
        taskNum += 1;
    }
    fclose(donefp);
    fclose(taskfp);
    fclose(tempfp);
    if (rename(temppath, taskpath) != 0){
        fprintf(stderr, "Could Not create the task.csv file OR done.csv.");
        return -1;
    }
    free(taskpath);
    free(temppath);
    free(donepath);
    return 0;
}

int deletetask(char *str){
    char buff[BUFSIZ];

    char *taskpath= getPath("task.csv");
    FILE *taskfp = fopen(taskpath, "r+");

    // not task exsists, no tasks to delete
    if (!taskfp){
        free(taskpath);
        return 0;
    }
    char *temppath = getPath("temp.csv");
    FILE *tempfp = fopen(temppath, "w+");

    if (!tempfp){
        fprintf(stderr, "Could Not create the temp.csv file in deltask()\n");
        fclose(taskfp);
        free(taskpath);
        free(temppath);
        return -1;
    }

    int deltaskNumber = atoi(str);
    int currtaskNum = 1;

    while (fgets(buff, BUFSIZ, taskfp) != NULL){
        if (deltaskNumber == currtaskNum){}
        else {
            // add to temp file for later use
            fprintf(tempfp, "%s", buff);
        }
        currtaskNum += 1;
    }

    fclose(taskfp);
    fclose(tempfp);

    if (rename(temppath, taskpath) != 0){
        fprintf(stderr, "could not rename temp.csv int deltask().\n");
        free(taskpath);
        free(temppath);
        return -1;
    }
    free(taskpath);
    free(temppath);
    return 0;

}

void displayfile(enum FLAGOPTIONS file){
    char *filename;
    char buff[BUFSIZ];

    filename = (file == DONELIST) ? getPath("done.csv"): getPath("task.csv");
    FILE *fp = fopen(filename, "r");

    if (!fp){
        free(filename);
        fprintf(stderr, "1Coul Not create the task.csv file OR done.csv\n");
        return ;
    }

    int idx = 1;
    while (fgets(buff, BUFSIZ, fp) != NULL){
        buff[strcspn(buff, "\n")]=0;
        if (file == DONELIST){
            printf("-- %d [X] %s\n", idx++, buff);
        }
        else {
            printf("-- %d [ ] %s\n", idx++, buff);
        }
    }
    free(filename);
    fclose(fp);
}

int parseData(struct UserRequest*usrReq){
    if (usrReq == NULL){
        return -1;
    }
    if (usrReq->flag == DELDONELIST){
        return (deldonelist() == 0) ? 0 : -1;
    }
    else if (usrReq->flag == TASKADD){
        addtask(usrReq->flagAragument);
    }
    else if (usrReq->flag == TASKDONE){
        taskdone(usrReq->flagAragument);
    }
    else if (usrReq->flag == DELTASK){
        deletetask(usrReq->flagAragument);
    }
    else if (usrReq->flag == DONELIST || usrReq->flag == TASKLIST){
        displayfile(usrReq->flag);
    }
    return 1;
}

void freeUsrReq(struct UserRequest*usrReq){
    free(usrReq->flagAragument);
    free(usrReq);
}

struct UserRequest *
processUsrInput(int argc, char *argv[]){

    // variables
    int flag;
    struct UserRequest *usrReqP = malloc(sizeof(struct UserRequest));
    if (!usrReqP) return NULL;
    usrReqP->flag = -1;
    usrReqP->flagAragument = NULL;

    // for flags defining getopt_long struct 
    struct option flagOptions[] = {
        {"ld", no_argument, NULL, DONELIST},
        {"dd", no_argument, NULL, DELDONELIST},
        {"dt", required_argument, NULL, DELTASK},
        {"l", no_argument, NULL, TASKLIST},
        {"c", required_argument, NULL, TASKDONE},
        {"a", required_argument, NULL, TASKADD},
        {0, 0, 0, 0}
    };

    while ((flag = getopt_long_only(argc, argv, "", flagOptions, NULL)) != -1){
        usrReqP->flag = flag;
        if (optarg){
            free(usrReqP->flagAragument);
            usrReqP->flagAragument = strdup(optarg); 
        }
        break;
    }
    return usrReqP;
}
