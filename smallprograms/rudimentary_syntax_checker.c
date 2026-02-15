#include <stdio.h>
#define NUMBEROFTOKENS 5
#define CLOSURETOKENS 2
#define SIZE 10000
#define COMMENTSCHAR 1
#define ESCAPESEQUENCELEN 9

#define TOKENARRAY {{'{', '}'}, {'[', ']'}, {'(', ')'}, {'"', '"'}, {'<', '>'}}

#define TRUE 1
#define FALSE 0

int detectsyntaxerror(int letter_count, int char_array[]);
int istoken(int current_char, int tokens_reference[][CLOSURETOKENS]);
int gettokennum(int current_char, int tokens_reference[][CLOSURETOKENS]);

int main(){
    int letter_count = 0;
    int idx = 0;
    int char_array[SIZE];
    int c;

    while ((c=getchar()) != EOF) {
        char_array[idx++] = c;
        letter_count++;
    }
    detectsyntaxerror(letter_count, char_array);
    printf("\n");
    return 0;
}

// to check wether a given char is token or not
int istoken(int current_char, int tokens_reference[][CLOSURETOKENS]){

    for (int i = 0; i < NUMBEROFTOKENS; i++){
        for (int j = 0; j < CLOSURETOKENS; j++){
            if (current_char == tokens_reference[i][j])
                return 1;
        }
    }
    return 0;
}

// to return number of current closure token int gettokennum(int current_char, int tokens_reference[][CLOSURETOKENS]){
int gettokennum(int current_char, int tokens_reference[][CLOSURETOKENS]){
    for (int i = 0; i < NUMBEROFTOKENS; i++){
        for (int j = 0; j < CLOSURETOKENS; j++){
            if (current_char == tokens_reference[i][j])
                return i;
        }
    }
    return -1;
}

int in_it(int current_char, int escape_sequence_list[]){
    for (int i = 0; i < ESCAPESEQUENCELEN; i++){
        if (escape_sequence_list[i] == current_char){
            return 1;
        }
    }
    return 0;
}


// main error finding function 
int detectsyntaxerror(int letter_count, int char_array[])
{
    // closure var
    int closure_tracker[SIZE];
    int closure_tracker_top = 0;

    int tokens_reference[NUMBEROFTOKENS][CLOSURETOKENS] = TOKENARRAY;

    // for comments var
    int single_line_comment = FALSE;
    int multi_line_comment = FALSE;

    // closure var 
    int current_closure_token_number = 0;
    int inside_single_quote = FALSE;
    int inside_single_quote_len = 0;
    int escape_sequence_list[ESCAPESEQUENCELEN] = {'n', 'v', 't', '"', '\'', '0', 'b', '\\', 'r'};

    // error var
    int line_count = 1;
    int line_letter_count = 0;


    for (int idx = 0; idx < letter_count; idx++){

        // for new line count 
        if (char_array[idx] == '\n'){
            line_count++;
            line_letter_count = 0;
        }
        line_letter_count++;

        /* for comments */

        // single line comments logic 
        if (char_array[idx] == '/' && char_array[idx+1] == '/'){
            single_line_comment = TRUE;
            // idx, because above checked char at current idx, and next one so 1 but taking into account when turn skipped 1 will be added later
            idx = idx + COMMENTSCHAR;
            continue;
        }

        if (single_line_comment && char_array[idx] == '\n'){
            single_line_comment = FALSE;
            continue;
        }

        // multiple line comments logic 
        if (!single_line_comment){
            if (!multi_line_comment && char_array[idx] == '/' && char_array[idx+1] == '*'){
                multi_line_comment = TRUE;
                // taking in to account that when continue happens it will add 1 only 1 is added
                idx = idx + COMMENTSCHAR;
                continue;
            }

            if (multi_line_comment){
                if (char_array[idx] == '/' && char_array[idx+1] == '*'){
                    printf("\nError : Cant use Comment within comment bitch. Line: %d, Letter count: %d.\n", line_count, line_letter_count);
                    idx = idx + COMMENTSCHAR;
                    continue;
                }
                if (char_array[idx] == '*' && char_array[idx+1] == '/'){
                    multi_line_comment = FALSE;
                    idx = idx + COMMENTSCHAR;
                    continue;
                }
            }
        }

        /* done comments */

        /* for character constants */

        if (!inside_single_quote && char_array[idx] == '\''){
            inside_single_quote = TRUE;
            // checks if not escape sequence char const should have only one char
            if (char_array[idx+1] != '\\' && char_array[idx+2] != '\''){
                printf("\nError: Bitch character constants can have only one char, Line: %d\n", line_count);
                return 0;
            }
            else if (char_array[idx+1] == '\''){
                printf("\nError: Character constant is empty. Line:%d, letter Count %d\n", line_count, line_letter_count);
            }
            continue;
        }
        // checks the entire character constant at once 
        if (inside_single_quote && char_array[idx] == '\\'){
            if (in_it(char_array[idx+1], escape_sequence_list)){
                if (char_array[idx+2] == '\''){
                    idx = idx + 2;
                    continue;
                }
            }
            else {
                printf("\nError: unknown Escape Sequence: '");
                putchar(char_array[idx+1]);
                printf("' At Line: %d, At Line Letter count:  %d\n", line_count, line_letter_count+1);
                return 0;
            }
        }
        else if (inside_single_quote && char_array[idx+2] == '\''){
            inside_single_quote = FALSE;
            idx = idx + 1;
            continue;
        }
        /* done for character constant */


        /* closure properties  */


        if (!single_line_comment && !multi_line_comment && !inside_single_quote){

            if (istoken(char_array[idx], tokens_reference)){
                current_closure_token_number = gettokennum(char_array[idx], tokens_reference);
                // check wheter new 
                // check wheter closure tracker top and current char have same token number
                if (current_closure_token_number == gettokennum(closure_tracker[closure_tracker_top-1], tokens_reference)){
                    if (tokens_reference[current_closure_token_number][1] == char_array[idx]){
                        closure_tracker_top = closure_tracker_top - 1;
                        continue;
                    }
                    else {
                        closure_tracker[closure_tracker_top++] = char_array[idx];
                        continue;
                    }
                }
                // if new opening of a new token 
                else if (tokens_reference[current_closure_token_number][0] == char_array[idx]){
                    closure_tracker[closure_tracker_top++] = char_array[idx];
                    continue;
                }
                else if (tokens_reference[current_closure_token_number][1] == char_array[idx]){ 
                    printf("\nError : Not proper closure of ");
                    putchar(closure_tracker[closure_tracker_top-1]);
                    printf(", No line: %d, Letter Count: %d.\n",line_count, line_letter_count);
                }
            }

        }

        /* done closure */




        if (idx == (letter_count-1)){
            if (multi_line_comment){
                printf("\nError : not proper closure of Comment\n");
            }
            if (closure_tracker_top >= 0){
                for(int num = 0; num < closure_tracker_top; num++){
                    printf("Error: Not proper Closure of,__");
                    putchar(closure_tracker[num]);
                    printf("__\n");
                }
            }
        } 
    }
    return 0;
}




/*
 * so what will we need to consider 
 * {}
 * ()
 * []
 * <>
 * ""
 * ''
 * //
 * /--* *--/
 *
 * all this and various combination of which will be considered 
 * lets note all the exceptions
 * -- <>
 *  - all allowed inside 
 *  - apart from <>
 *  - closing
 *
 * -- comments 
 *  - anything shall be present apart from itself 
 *  - closing
 *
 * -- ' '
 *  - anything shall be present
 *  - cannot be empty
 *  - cannot have multiple things
 *  - closing
 *
 * -- " "
 *  - can contain anything 
 *  - closing
 *
 * -- ()
 *  - closing
 *
 * -- {}
 *  - closing
 *  - cannot be inside ()
 * -- /
 *
 * -- escape sequences
 *  - \n
 *  - \t
 *  - \v
 *  - \b
 *  - \'
 *  - \"
 *  - \0
 *  - \\
 *  - \r
 *  all common es cannot contain es outiside of this with this \
 *  - can only be present inside "" or ''
 *
 *
 *
 * */
