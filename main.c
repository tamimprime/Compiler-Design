#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_IDENTIFIERS 1000
#define MAX_OPERATORS 1000
#define MAX_PREPROCESSORS 1000
#define MAX_FUNCTIONS 1000
#define MAX_COMMENT_LENGTH 1000

// Define a structure for storing identifiers

struct identifier
{
    char name[100];
    int count;
};

// Define a structure for storing operators

struct operator
{
    char symbol;
    int count;
};

// Define a structure for storing preprocessors

struct preprocessor
{
    char name[100];
    int count;
};

// Define a structure for storing functions

struct function
{
    char name[100];
    int count;
};

// Function prototypes
int is_identifier_char(char c);

// Check if a character can be part of an identifier

int is_identifier_char(char c)
{
    return isalnum(c) || c == '_';
}

// Function prototypes
int is_operator_char(char c);

// Check if a character is a valid operator symbol

int is_operator_char(char c)
{
    return strchr("+-*/%><=&|!^~?", c) != NULL;
    printf("Operator");
}

// Function prototypes
int is_preprocessor_char(char c);

// Check if a character is a valid preprocessor symbol

int is_preprocessor_char(char c)
{
    return c == '#';
    printf("Preprocessor");
}

// Function prototypes
int is_function_char(char c);

// Check if a character can be part of a function name

int is_function_char(char c)
{
    return isalpha(c) || c == '_';
    printf("Function is Ok.");
}

// Function prototypes
int is_math_char(char c);

// Returns 1 if the character is a valid math character, 0 otherwise

int is_math_char(char c)
{
    char math_chars[] = "+-*/%=<>&|~^()";
    if (strchr(math_chars, c) != NULL)
    {
        return printf("math_char is Ok.");
    }
    return printf("math_char is not Ok.");
}

// Function prototypes
int is_valid_parenthesis(char* line);

// Returns 1 if the line has valid parenthesis, 0 otherwise

int is_valid_parenthesis(char* line)
{
    int open_paren_count = 0;
    int close_paren_count = 0;

    int i;
    for (i = 0; line[i] != '\0'; i++)
    {
        if (line[i] == '(')
        {
            open_paren_count++;
        }
        else if (line[i] == ')')
        {
            close_paren_count++;
        }
    }

    if (open_paren_count == close_paren_count)
    {
        return printf("Parenthesis is Ok.");
    }
    return printf("Parenthesis is not Ok.");
}

// Function prototypes
int has_valid_semicolon(char* line);

// Returns 1 if the line has a valid semicolon, 0 otherwise

int has_valid_semicolon(char* line)
{
    int i = strlen(line) - 1;
    while (i >= 0 && isspace(line[i]))
    {
        i--;
    }
    if (line[i] == ';')
    {
        return 1;
    }
    return 0;
}

int is_comment(char* line);

// Returns 1 if the line is a comment, 0 otherwise
int is_comment(char* line)
{
    char* trimmed_line = strtok(line, " \t\n\r\f\v");
    if (trimmed_line == NULL)
    {
        return 0;
    }
    if (trimmed_line[0] == '/' && trimmed_line[1] == '/')
    {
        return 1;
    }
    return 0;
}

int is_valid_math_expression(char* line);

// Returns 1 if the line is a valid math expression, 0 otherwise
int is_valid_math_expression(char* line)
{
    int open_paren_count = 0;
    int close_paren_count = 0;
    int operator_count = 0;
    int operand_count = 0;
    int i = 0;
    while (line[i] != '\0')
    {
        if (line[i] == '(')
        {
            open_paren_count++;
        }
        else if (line[i] == ')')
        {
            close_paren_count++;
        }
        else if (is_operator_char(line[i]))
        {
            operator_count++;
        }
        else if (isalnum(line[i]) || line[i] == '.')
        {
            // Check if the current character is part of a valid operand
            while (isalnum(line[i]) || line[i] == '.')
            {
                i++;
            }
            operand_count++;
            // Backtrack by 1 to recheck the current character on the next iteration
            i--;
        }
        else if (!isspace(line[i]))
        {
            // If the current character is not a space or a valid operator or operand, the expression is invalid
            return 0;
        }
        i++;
    }
    if (open_paren_count != close_paren_count && operator_count >= operand_count)
    {
        return 0;
    }
    return 1;
}


//****____""""int has_valid_english_grammar(char* line);""""____****
//no idea about how to define this function. Sorry....


// Global variables

struct identifier identifiers[MAX_IDENTIFIERS];
int num_identifiers = 0;
struct operator operators[MAX_OPERATORS];
int num_operators = 0;
struct preprocessor preprocessors[MAX_PREPROCESSORS];
int num_preprocessors = 0;
struct function functions[MAX_FUNCTIONS];
int num_functions = 0;



int main(int argc, char* argv[])
{
    FILE* file;
    char line[1000];
    int line_num = 0;


    // Open the file

    file = fopen("program.cpp", "r");
    if (file == NULL)
    {
        printf("Could not open file %s\n", argv[1]);
        return 1;
    }

    // Read each line of the file

    while (fgets(line, sizeof(line), file))
    {
        line_num++;

        // Count and store the unique valid identifiers, operators, and preprocessors

        char* token = strtok(line, " \t\n\r\f\v");
        char delimiters[] = " ,.;";
        while (token != NULL)
        {
            if (is_identifier_char(token[0]))
            {
                // Check if the identifier is already in the array

                int i;
                for (i = 0; i < num_identifiers; i++)
                {
                    if (strcmp(identifiers[i].name, token) == 0)
                    {
                        identifiers[i].count++;
                        break;
                    }
                }

                // If the identifier is not in the array, add it

                if (i == num_identifiers)
                {
                    strcpy(identifiers[num_identifiers].name, token);
                    identifiers[num_identifiers].count = 1;
                    num_identifiers++;
                }
            }

            // Count and store the unique valid operators

            else if (is_operator_char(token[0]))
            {
                // Check if the operator is already in the array

                int i;
                for (i = 0; i < num_operators; i++)
                {
                    if (operators[i].symbol == token[0])
                    {
                        operators[i].count++;
                        break;
                    }
                }

                // If the operator is not in the array, add it

                if (i == num_operators)
                {
                    operators[num_operators].symbol = token[0];
                    operators[num_operators].count = 1;
                    num_operators++;
                }
            }

            // Count and store the unique valid preprocessors

            else if (is_preprocessor_char(token[0]))
            {
                int i;
                for (i = 0; i < num_preprocessors; i++)
                {
                    if (preprocessors[i].name == token[0])
                    {
                        preprocessors[i].count++;
                        break;
                    }
                }


                // If the preprocessor is not in the array, add it

                if (i == num_preprocessors)
                {
                    strcpy(preprocessors[num_preprocessors].name, token);
                    preprocessors[num_preprocessors].count = 1;
                    num_preprocessors++;
                }
            }
        }

        token = strtok(NULL, delimiters);
    }

    print(preprocessor[0].name, %s);
}

