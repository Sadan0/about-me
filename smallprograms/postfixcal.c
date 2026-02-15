#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXTOP 100
#define NUMBER '0'
#define NAME 'n'

int getop(char[]);
void push(double);
double pop(void);

// my functions 
void clear();
void swap();
void top();
void utilfunc(char s[]);

int gettline(char s[], int lim){

    int i;
    int c;
    for (i = 0; i < lim-2 && (c = getchar()) != EOF && c != '\n'; i++){
        s[i] = c; 
    }
    if (c == EOF || c == '\n'){
        s[i++] = c;
    }
    s[i] = '\0';
    if (c ==  EOF){
        return -1;
    }
    return i;
}
int getnext(char s[]);


int main(){


    // polish calculator 
    int type, var, limit;
    double op1, op2, v, debugger;
    char s[MAXTOP];
    double variables[MAXTOP];

    while ((type = getnext(s)) != EOF){

        switch (type) {
            case NUMBER: 
                push(atof(s));
                break;
            case '+':
                push(pop()+pop());
                break;
            case '*':
                push(pop()*pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0){
                        push(pop()/op2);
                }
                else {
                    printf("error: zero divisor\n");
                }
                break;
            case '%':
                op2 = pop();
                push(fmod(pop(), op2));
                break;
            case '\n':
                v = pop();
                printf("\t%.8g\n", v);
                break;
            case '^':
                op2 = pop();
                push(pow(pop(), op2));
                break;
            case '=':
                pop();
                if (var >= 'A' && var <= 'Z'){
                    variables[var - 'A'] = pop();
                }
                else {
                    printf("error: non variable name\n");
                }
                break;
            case NAME:
                utilfunc(s);
                break;
            default:
                if (type >= 'A' && type <= 'Z'){
                    push(variables[type - 'A']);
                }
                else if (type == 'v'){
                    push(v);
                }
                else {
                    printf("error: unknown command %s\n", s);
                }
                break;
        }
        var = type;
    }
    return 0;
}

#define MAXVAL 100
int sp = 0;
double val[MAXVAL];

void clear(){
    sp = 0;
}

void top(){
    if (sp > 0){
        printf("Top of the stack: %.8g\n", val[sp]);
    }
}

void push(double f){
    if (sp < MAXVAL){
        val[sp++] = f;
    }
    else {
        printf("error: stack is full cannot insert your value\n");
    }
}

double pop(){
    if (sp > 0){
        return val[--sp];
    }
    else {
        printf("error : the stack is empty\n");
        return 0.0;
    }
}

void swap(){
    if (sp > 1){
        double op2 = pop();
        double op1 = pop();

        push(op2);
        push(op1);
    }
    else {
        printf("not enough numbers to swap\n");
    }
}

int start = 0, end = 0, lim = MAXTOP;
char storeline[MAXTOP];

int getop(char s[]){
    
    /* 
     *
     * so we access the str 
     * then we see for a number, operator or command
     * so its a stack problem
     *
     * */

    // will be used by s string
    int idx = 0;
    
    for ( ; start < end && storeline[start] != EOF ; start++){

        int i;
        for (i = start; storeline[i] == ' ' || storeline[i] == '\t'; i++)
            ;
        start = i;

        // for commands
        if (storeline[start] == 'v'){
            start++;
            return 'v';
        }
        if (isalpha(storeline[start]) && islower(storeline[start])){
            for (; isalpha(storeline[start]); start++){
                s[idx++] = storeline[start];
            }
            s[idx] = '\0';
            if (idx > 1){
                return 'n';
            }
        }

        if (storeline[start] == '-'){
            if (isdigit(storeline[start+1])){
                s[idx++] = storeline[start++];
            }
            else{
                return storeline[start++];
            }
        }
        // for non digits
        if (!isdigit(storeline[start]) && storeline[start] != '.'){
            return storeline[start++];
        }

        // for numbers
        if (isdigit(storeline[start])){
            for (; start < end && isdigit(storeline[start]); start++)
                s[idx++] = storeline[start];
        }

        if (storeline[start] == '.'){
            s[idx++] = storeline[start++];
            for (; start < end && isdigit(storeline[start]); start++)
                s[idx++] = storeline[start];
        }
        return NUMBER;
    }
    if (storeline[start] == EOF){
        printf("\nThe Program is Closed\n");
        return EOF;
    }
    return NUMBER;
}

int getnext(char s[]){
    if (start == end){
        end = gettline(storeline,lim);
        start = 0;
    }
    return getop(s);
}

void utilfunc(char s[]){
    if (strcmp(s, "sin") == 0){
        push(sin(pop()));
    }
    else if (strcmp(s, "exp") == 0){
        push(exp(pop()));
    }
    else if (strcmp(s, "cos") == 0){
        push(cos(pop()));
    }
    else if (strcmp(s, "swap") == 0){
        swap();
    }
    else if (strcmp(s, "top") == 0){
        top();
    }
    else if (strcmp(s, "clear") == 0){
        clear();
    }
    else {
        printf("%s is not suppported.\n", s);
    }
}
