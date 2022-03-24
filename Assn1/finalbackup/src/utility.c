/**
 * @file utility.c
 * @author Abhay Parashar, 658152558, S22N03, CSCI 261, VIU
 * @version 1.0.0
 * @date August 04, 2021
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/utility.h"

// All maloc cast to char *

void reverse(char *str)
{
    int size = strlen(str);
    char *start;
    char *end;
    char temp;

    start = str;
    end = str;

    for (int i = 0; i < (size - 1); i++)
    {
        //set end to the end character in the string
        end++;
    }
    for (int i = 0; i < size / 2; i++)
    {
        // perform a swap
        temp = *end;
        (*end) = (*start);
        (*start) = temp;

        // update the end ad start pointers
        start++;
        end--;
    }
}
//Parameter 'str' is a NULL terminted string.
//Reverse all the characters, except NULL, in the string 'str'

void add_prefix(char *number, char p0, char p1)
{
    int size = strlen(number);
    char *end = number;

    for (int i = 0; i < size; i++)
    {
        // set end to the end character in the string
        end++;
    }
    for (int i = 0; i <= size; i++)
    {
        // move the end two characters to the right
        *(end + 2) = *end;
        // keep adjusting the end pointer
        end--;
    }
    number[0] = p0;
    number[1] = p1;
}
//Pointer 'number' is pointing a NULL terminated string, which has enough memory to add
//two more characters.
//Move all the characters of the string 2 positions right.
//Insert 'p0' at the first index of the string.
//Insert 'p1' at the second index of the string.

char *extend_to_word_size(char *number, int word_size)
{
    int size = (int)strlen(number);
    int diff = word_size - size;
    if (size > word_size)
    {
        printf("Error in extending\n");
        return NULL;
    }
    else
    {
        char *newWord = malloc(sizeof(char) * (word_size + 1));
        memset(newWord, ASCII_VAL0, sizeof(char) * word_size); // Initialise to zero

        for (int i = 0; i < size; i++)
        {
            newWord[diff + i] = number[i];
        }

        newWord[word_size] = '\0';
        free(number);
        number = newWord;
        return number;
    }
}
//If the length of the 'number' is greater than 'word_size' report error.
//If the length of the 'number' is less than 'word_size' do the followings:
//	Allocate enough memory for a new word.
//	Fill the most significant extra digits of the word with zeros and copy
//	the least significant digits from the number.
//	Free the memory from the pointer 'number'.
//	Point the new word by the pointer 'number'.

char* extend_to_word_size_trailing(char* number, int word_size)
{
    int size = strlen(number);
    if(size > word_size)
    {
        printf("Error in extending\n");
    }
    else
    {
        char *newWord = malloc(sizeof(char)*(word_size+1));
        memset(newWord, ASCII_VAL0, sizeof(char) * word_size); // Initialise to zero

        for(int i = 0; i < word_size;i++)
        {
            if(i < size)
            {
                newWord[i] = number[i];
            }

        }
        newWord[word_size] = '\0';
        free(number);
        number = newWord; 
        return number;
    }
} 
// New fx

int are_binary_digits(char *number)
{
    int size = strlen(number);

    for (int i = 0; i < size; i++)
    {
        // check each character if any character is not 0 or 1 return 1
        if (number[i] != '0' && number[i] != '1')
        {
            return FALSE;
        }
    }
    // return 1 or true when every digit is 0 or 1
    return TRUE;
}
//Return TRUE if all the digits of the number are either zero or one.

int are_binary_point_digits(char *number)
{
    int size = strlen(number);

    for (int i = 0; i < size; i++)
    {
        // check each character if any character is not 0 or 1 return 1
        if (number[i] != '0' && number[i] != '1' && number[i] != '.')
        {
            return FALSE;
        }
    }
    // return 1 or true when every digit is 0 or 1
    return TRUE;
}
//Return TRUE if all the digits of the number are either zero or one or pt.

int are_hex_digits(char *number)
{
    int size = strlen(number);
    char char2check;

    for (int i = 0; i < size; i++)
    {
        char2check = number[i];
        char2check = toupper(char2check); // convert to upper case to avoid lowercase conflict
        // Check to see if any character's ASCII val is not in the range of 0-9
        if (!(char2check >= ASCII_VAL0 && char2check <= ASCII_VAL9))
        {
            // Further check if any characters ASCII val is not in the range of A-F
            if (!(char2check >= ASCII_VALA && char2check <= ASCII_VALF))
                return FALSE; // return false if any character is not a hex digit
        }
    }
    return TRUE;
}
//Return TRUE if all the digits of the number are one of the hex digits.

int is_hex(char *number)
{
    int size = strlen(number);
    char *number_no_prefix = malloc(sizeof(char) * size - 1); //Required size for a copy of number with no prefix

    for (int i = 0; i < size; i++)
    {
        number_no_prefix[i] = number[i + 2]; //Copy digits of number to number no prefix
    }

    if (strlen(number_no_prefix) <= 8 /*HEX_MAX_DIGITS*/ && number[0] == '0' && number[1] == 'x' && are_hex_digits(number_no_prefix) == 1 /*TRUE*/)
    {
        free(number_no_prefix); //Free number_no_prefix as checking is already done
        return 1;               /*TRUE*/
    }
    else
    {
        return -1; /*FALSE*/
    }
}
//Return TRUE if the number of digits in parameter 'number' is within the limit
//of a hex number, starts with the prefix '0x', and all the digits are hex digits.

int are_decimal_digits(char *number)
{
    int size = strlen(number);
    for (int i = 0; i < size; i++)
    {
        // Check to see if any character's ASCII val is not in the range of 0-9
        if (!(number[i] >= ASCII_VAL0 && number[i] <= ASCII_VAL9))
        {
            return -1 /*FALSE*/; // return false if any character is not in the decimal digits
        }
    }
    // return 1 or true when every digit is one among the valid decimal digits
    return 1 /*TRUE*/;
}

int are_decimal_point_digits(char *number)
{
    int size = strlen(number);

    for (int i = 0; i < size; i++)
    {
        // Check to see if any character's ASCII val is not in the range of 0-9
        if (!(number[i] >= ASCII_VAL0 && number[i] <= ASCII_VAL9))
        {
            if (!(number[i] == ASCII_VALPOINT))
                return FALSE; // return false if any character is not in the decimal digits or point
        }
    }
    // return 1 or true when every digit is one among the valid decimal digits or decimal point
    return TRUE;
}
//Return TRUE if all the digits of the number are one of the decimal digits or a decimal point

int is_binary(char *number)
{
    int size = strlen(number);
    char *number_no_prefix = malloc(sizeof(char) * size - 1); //Required size for a copy of number with no prefix

    for (int i = 0; i < size; i++)
    {
        number_no_prefix[i] = number[i + 2]; //Copy digits of number to number no prefix
    }
    printf("%d\n", strlen(number));

    if (strlen(number_no_prefix) <= 32 /*BINARY_WORD_SIZE*/ && number[0] == '0' && number[1] == 'b' && are_binary_digits(number_no_prefix) == 1 /*TRUE*/)
    {
        free(number_no_prefix); //Free number_no_prefix as checking is already done
        return 1;               /*TRUE*/
    }
    else
    {
        return -1; /*FALSE*/
    }
}
//Return TRUE if the number of digits in parameter 'number' is within the limit
//of a binary number, starts with the prefix '0b', and all the digits are binary digits.

int is_hex(char *number)
{
    int size = strlen(number);
    char *number_no_prefix = malloc(sizeof(char) * size - 1); //Required size for a copy of number with no prefix

    for (int i = 0; i < size; i++)
    {
        number_no_prefix[i] = number[i + 2]; //Copy digits of number to number no prefix
    }

    if (strlen(number_no_prefix) <= 8 /*HEX_MAX_DIGITS*/ && number[0] == '0' && number[1] == 'x' && are_hex_digits(number_no_prefix) == 1 /*TRUE*/)
    {
        free(number_no_prefix); //Free number_no_prefix as checking is already done
        return 1;               /*TRUE*/
    }
    else
    {
        return -1; /*FALSE*/
    }
}
//Return TRUE if the number of digits in parameter 'number' is within the limit
//of a hex number, starts with the prefix '0x', and all the digits are hex digits.

int is_decimal(char *number)
{
    int size = strlen(number);

    if (size <= 10 /*DECIMAL_MAX_DIGITS*/ && are_decimal_digits(number) == 1 /*TRUE*/)
    {
        return 1; /*TRUE*/
    }
    else
    {
        return -1; /*FALSE*/
    }
}
//Return TRUE if the number of digits in parameter 'number' is within the limit
//of a decimal number, starts with no prefix, and all the digits are decimal digits.

int is_real_part(char *number)
{
    int size = strlen(number);
    double value;
    char *end_ptr;

    value = strtod(number, &end_ptr);

    if (size <= REAL_PART_MAX_DIGITS && are_decimal_digits(number) == TRUE && value <= REAL_PART_MAX_VALUE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
//Return TRUE if the number of digits in parameter 'number' is within the limit
//of a part of a real number, all the digits are decimal digits, and its value
//is within the limit.

int is_fixed_point_part(char *number)
{
    int size = strlen(number);

    if (size <= FIXED_POINT_PART_MAX_DIGITS && are_binary_digits(number) == TRUE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
//Return TRUE if the number of digits in parameter 'number' is within the limit
//of a part of a fixed point number, and all the digits are binary digits.

int is_real(char *number)
{
    int size = strlen(number);

    if (size <= 11 /*REAL_MAX_DIGITS*/ && are_decimal_point_digits(number) == 1 /*TRUE*/)
    {
        return 1; /*TRUE*/
    }
    else
    {
        return -1; /*FALSE*/
    }
}
//Return TRUE if the number of digits in parameter 'number' is within the limit
//of a real number, and the digits are either a decimal digit or a decimal point ('.')

int is_fixed_point(char *number)
{
    int size = strlen(number);

    if (size <= FIXED_POINT_MAX_DIGITS && are_binary_point_digits(number) == TRUE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
//Return TRUE if the number of digits in parameter 'number' is within the limit
//of a part of fixed point number, and all the digits are binary digits.

char *get_integer_part(char *number) // remember to free memory of returned ptr after use
{
    int size = strlen(number);
    char *end_ptr;
    char *int_part = malloc(sizeof(char) * size); // allocate sufficient memory for int_part

    int dec_num = strtod(number,&end_ptr);

    int_part = itoa(dec_num,int_part,RADIX_DECIMAL);

    return int_part;
}
//Return a new string copying the integer part of the real number.

char *get_fraction_part(char *number) // remember to free the string after use very easy sol wh=ithout this crap but check if applicable to hex
{
    int size = strlen(number);
    int fraction_start_at = 1;

    char *fraction_part = malloc(sizeof(char) * size); // allocate sufficient memory for the fraction part

    for (int i = 0; number[i] != '.'; i++)
    {
        ++fraction_start_at;
    }

    for (int i = 2; i <= (size - fraction_start_at); i++)
    {
        fraction_part[i] = number[fraction_start_at + i];
    }

    fraction_part[0] = '0';
    fraction_part[1] = '.';

    return fraction_part;
}
//Return a new string copying the fraction part of the real number.

/*
 * Include necessary header files.
 * Include library header files first, then the custom header files
 */
