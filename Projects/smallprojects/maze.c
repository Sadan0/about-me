#include <stdio.h>
#include <string.h>
#define MAZELENTH 8 // i (row)
#define MAZEBREATH 8 // j (column)
#define STEPS 100 // limits how much the program  runs

void printmaze(int maze[MAZELENTH][MAZEBREATH], char direction);
void getdirectionalcoords(char direction, char turn[], int coords[]);
char changedirection(char direction, char turn[]);
int canturnleft(int position[], char direction, int maze[MAZELENTH][MAZEBREATH]);
int canturnright(int position[], char direction, int maze[MAZELENTH][MAZEBREATH]);
int canmoveforward(int position[], char direction, int maze[MAZELENTH][MAZEBREATH]);
void moveforward(int position[], char direction, int maze[MAZELENTH][MAZEBREATH]);
char moveright(int position[], char direction, int maze[MAZELENTH][MAZEBREATH]);
char moveleft(int position[], char direction, int maze[MAZELENTH][MAZEBREATH]);
char turnaround(int position[], char direction, int maze[MAZELENTH][MAZEBREATH]);
void solvemaze(int maze[MAZELENTH][MAZEBREATH], int start[], char direction);

int exitfound = 0;

int main(){

    int maze[8][8] = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 3, 0, 0, 1, 0, 0, 1},
        {1, 1, 0, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 1},
        {1, 1, 0, 1, 1, 1, -1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}
    };

    char direction = 'E'; // have to provide direction which the bob is facing 
    int start[2] = {1, 1}; // and its starting position
    printmaze(maze, direction);
    solvemaze(maze, start, direction);

    return 0;
}

void printmaze(int maze[MAZELENTH][MAZEBREATH], char direction){
    for (int i = 0; i < MAZELENTH; i++){
        for (int j = 0; j < MAZEBREATH; j++){
            if (maze[i][j] == 1)
                printf("||");
            else if (maze[i][j] == -1)
                printf("**");
            else if (maze[i][j] == 3){
                if (direction == 'N'){
                    printf("^^");
                }
                else if (direction == 'S'){
                    printf("VV");
                }
                else if (direction == 'E'){
                    printf(">>");
                }
                else if (direction == 'W'){
                    printf("<<");
                }
            }
            else 
                printf("  ");
        }
        printf("\n");
    }
};

void getdirectionalcoords(char direction, char turn[], int coords[]){

    coords[0] = 0;
    coords[1] = 0;

    if (direction == 'N'){
        if (strcmp(turn, "left") == 0){
            coords[1] = -1;
        }
        else if (strcmp(turn, "right") == 0){
            coords[1] = 1;
        }
        else if (strcmp(turn, "forward") == 0){
            coords[0] = -1;
        }
        else if (strcmp(turn, "backward") == 0){
            coords[0] = 1;
        }
    }
    else if (direction == 'E'){

        if (strcmp(turn, "left") == 0){
            coords[0] = -1;
        }
        else if (strcmp(turn, "right") == 0){
            coords[0] = 1;
        }
        else if (strcmp(turn, "forward") == 0){
            coords[1] = 1;
        }
        else if (strcmp(turn, "backward") == 0){
            coords[1] = -1;
        }
    }
    else if (direction == 'W'){

        if (strcmp(turn, "left") == 0){
            coords[0] = 1;
        }
        else if (strcmp(turn, "right") == 0){
            coords[0] = -1;
        }
        else if (strcmp(turn, "forward") == 0){
            coords[1] = -1;
        }
        else if (strcmp(turn, "backward") == 0){
            coords[1] = 1;
        }
    }
    else if (direction == 'S'){

        if (strcmp(turn, "left") == 0){
            coords[1] = 1;
        }
        else if (strcmp(turn, "right") == 0){
            coords[1] = -1;
        }
        else if (strcmp(turn, "forward") == 0){
            coords[0] = 1;
        }
        else if (strcmp(turn, "backward") == 0){
            coords[0] = -1;
        }
    }
}

char changedirection(char direction, char turn[]){

    if (strcmp(turn, "around") == 0){
        if (direction == 'N'){
            return 'S';
        }
        else if (direction == 'S'){
            return 'N'; 
        }
        else if (direction == 'E'){
            return 'W';
        }
        else if (direction == 'W'){
            return 'E';
        }
    }
    else if (direction == 'N'){
        if (!strcmp(turn, "left")){
            return 'W';
        }
        else if (strcmp(turn, "right") == 0){
            return 'E';
        }
    }
    else if (direction == 'S'){
        if (strcmp(turn, "left") == 0){
            return 'E';
        }
        else if (strcmp(turn, "right") == 0){
            return 'W';
        }
    }
    else if (direction == 'W'){
        if (strcmp(turn, "left") == 0){
            return 'S';
        }
        else if (strcmp(turn, "right") == 0){
            return 'N';
        }
    }
    else if (direction == 'E'){
        if (strcmp(turn, "left") == 0){
            return 'N';
        }
        else if (strcmp(turn, "right") == 0){
            return 'S';
        }
    }
    return 'F';
}

// turn codition checks
int canturnleft(int position[], char direction, int maze[MAZELENTH][MAZEBREATH]){

    char turn[10] = "left"; 
    int coords[2] = {0, 0};
    getdirectionalcoords(direction, turn, coords);

    int lookatidxi = position[0] + coords[0];
    int lookatidxj = position[1] + coords[1];
    if (maze[lookatidxi][lookatidxi] == -1)
        exitfound = 1;

    return (maze[lookatidxi][lookatidxj] == 0 || maze[lookatidxi][lookatidxj] < 0);
}

int canturnright(int position[], char direction, int maze[MAZELENTH][MAZEBREATH]){


    char turn[10] = "right"; 
    int coords[2] = {0, 0};
    getdirectionalcoords(direction, turn, coords);

    //printf("%d, %d\n", position[0], position[1]);
    //printf("%d, %d\n", coords[0], coords[1]);
    int lookatidxi = position[0] + coords[0];
    int lookatidxj = position[1] + coords[1];
    // printf("%d, %d\n", lookatidxi, lookatidxj);
    if (maze[lookatidxi][lookatidxi] == -1)
        exitfound = 1;

    return (maze[lookatidxi][lookatidxj] == 0 ||maze[lookatidxi][lookatidxj] < 0);
}

int canmoveforward(int position[], char direction, int maze[MAZELENTH][MAZEBREATH]){

    char turn[10] = "forward"; 
    int coords[2] = {0, 0};
    getdirectionalcoords(direction, turn, coords);

    int lookatidxi = position[0] + coords[0];
    int lookatidxj = position[1] + coords[1];

    if (maze[lookatidxi][lookatidxi] == -1)
        exitfound = 1;

    return (maze[lookatidxi][lookatidxj] == 0 || maze[lookatidxi][lookatidxj] < 0);
}

// moving operation
void moveforward(int position[], char direction, int maze[MAZELENTH][MAZEBREATH]){

    char turn[10] = "forward"; 
    int coords[2] = {0, 0};
    getdirectionalcoords(direction, turn, coords);

    maze[position[0]][position[1]] = 0; 
    position[0] += coords[0];
    position[1] += coords[1];
    maze[position[0]][position[1]] = 3;
}

char moveright(int position[], char direction, int maze[MAZELENTH][MAZEBREATH]){

    // getting coords to update
    char turn[10] = "right";
    int coords[2] = {0, 0};
    getdirectionalcoords(direction, turn, coords);

    // updating maze
    maze[position[0]][position[1]] = 0;
    position[0] += coords[0];
    position[1] += coords[1];
    maze[position[0]][position[1]] = 3;

    // updating DIRECTION 
    return changedirection(direction, turn);
}
char moveleft(int position[], char direction, int maze[MAZELENTH][MAZEBREATH]){

    // getting coords to update
    char turn[10] = "left"; 
    int coords[2] = {0, 0};
    getdirectionalcoords(direction, turn, coords);

    // updating maze
    maze[position[0]][position[1]] = 0;
    position[0] += coords[0];
    position[1] += coords[1];
    maze[position[0]][position[1]] = 3;

    // updating DIRECTION 
    return changedirection(direction, turn);
}


char turnaround(int position[], char direction, int maze[MAZELENTH][MAZEBREATH]){

    // getting coords to update
    char turn[10] = "around"; 

    // updating DIRECTION 
    return changedirection(direction, turn);
}

// main solve logic
void solvemaze(int maze[MAZELENTH][MAZEBREATH], int start[], char direction){


    int idxi = start[0], idxj = start[1], step = 0;
    int position[2] = {idxi, idxj}; 

    while(step != STEPS){

        // if you can turn left turn left
        if (canturnleft(position, direction, maze)){
            direction = moveleft(position, direction, maze);
        }
        else if(canmoveforward(position, direction, maze)){
            moveforward(position, direction, maze);
        }
        else if(canturnright(position, direction, maze)){
            direction = moveright(position, direction, maze);
        }
        else{
            direction = turnaround(position, direction, maze);
        }
        if (direction == 'F'){
            printf("%d, %d\n", position[0], position[1]);
            printf("EROOR:\n");
            break;
        }
        if (exitfound){
            printf("\nMaze exit found at (%d, %d)!! in %d Steps.\n", position[0], position[1], step+1);
            printmaze(maze, direction);
            break;
        }
        
        step++;
        printf("Step: %d\n", step);
        printmaze(maze, direction);
    }
}
/*
 *
 * ok first big question how do you represent maze in program
 *
 * by two dimensional array like i theorized
 *
 * algorithm for sloving maze
 * just follow the leftside
 *
 * can turn left ? turn left : can move ahead ? move ahead : can turn right ? turn right : turn around
 *
 *
 *
 *
    int maze[MAZELENTH][MAZEBREATH] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 3, 1, 1, 1, 1, -1, 1, 1, 1}
    };
 * */
