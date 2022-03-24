/**
 * @file utility.c
 * @author Abhay Parashar, 658152558, S22N03, CSCI 261, VIU
 * @version 1.0.0
 * @date January 25, 2021
 *
 * Implementation file for utility functions helpful in conversion
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/utility.h"

/** @brief Reverses a c string that was passed as a 
 *         parameter
 */
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

/** @brief Adds two characters that were passed as parameters into the string
 *         from the start.
 */
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

/** @brief Increases the length of the string to the passed size and 
 *          while copying the string and filling most significant digits
 *          with 0's.
 */
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
        char *newWord = (char *)calloc((word_size + 1), sizeof(char));
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

/** @brief Increases the length of the string to the passed size and 
 *         while copying the string and filling least significant digits
 *         with 0's.
 */
char *extend_to_word_size_trailing(char *number, int word_size)
{
    int size = strlen(number);
    if (size > word_size)
    {
        printf("Error in extending\n");
        return NULL;
    }
    else
    {
        char *newWord = (char *)calloc((word_size + 1), sizeof(char));
        memset(newWord, ASCII_VAL0, sizeof(char) * word_size); // Initialise to zero

        for (int i = 0; i < word_size; i++)
        {
            if (i < size)
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

/** @brief Checks if every digit is a binary digit
 */
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

/** @brief Checks if every digit is a binary digit including a point.
 */
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

/** @brief Checks if every digit is a valid hexadecimal
 */
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

/** @brief Checks if every digit is a valid decimal digit
 */
int are_decimal_digits(char *number)
{
    int size = strlen(number);
    for (int i = 0; i < size; i++)
    {
        // Check to see if any character's ASCII val is not in the range of 0-9
        if (!(number[i] >= ASCII_VAL0 && number[i] <= ASCII_VAL9))
        {
            return FALSE; // return false if any character is not in the decimal digits
        }
    }
    // return 1 or true when every digit is one among the valid decimal digits
    return TRUE;
}

/** @brief Checks if every digit is a valid decimal digit including a point
 */
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

/** @brief Checks all specified conditions for the string to be a binary number
 */
int is_binary(char *number)
{
    int size = strlen(number);
    char *number_no_prefix = (char *)calloc(size, sizeof(char));

    for (int i = 0; i < size; i++)
    {
        number_no_prefix[i] = number[i + 2]; //Copy digits of number to number no prefix
    }

    if (strlen(number_no_prefix) <= BINARY_WORD_SIZE && number[0] == '0' && number[1] == 'b' && are_binary_digits(number_no_prefix) == TRUE)
    {
        free(number_no_prefix); //Free number_no_prefix as checking is already done
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/** @brief Checks all specified conditions for the string to be a hex value
 */
int is_hex(char *number)
{
    int size = strlen(number);
    char *number_no_prefix = (char *)calloc(size, sizeof(char)); //Required size for a copy of number with no prefix

    for (int i = 0; i < size; i++)
    {
        number_no_prefix[i] = number[i + 2]; //Copy digits of number to number no prefix
    }

    if (strlen(number_no_prefix) <= HEX_MAX_DIGITS && number[0] == '0' && number[1] == 'x' && are_hex_digits(number_no_prefix) == TRUE)
    {
        free(number_no_prefix); //Free number_no_prefix as checking is already done
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/** @brief Checks all specified conditions for the string to be a decimal value
 */
int is_decimal(char *number)
{
    int size = strlen(number);

    if (size <= DECIMAL_MAX_DIGITS && are_decimal_digits(number) == TRUE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/** @brief Validates if the given string is a valid real value
 */
int is_real_part(char *number)
{
    int size = strlen(number);
    double value;
    char *end_ptr;

    value = strtod(number, &end_ptr);

    if (size <= REAL_PART_MAX_DIGITS && are_decimal_point_digits(number) == TRUE && value <= REAL_PART_MAX_VALUE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/** @brief Validates if the given string is a valid value in fixed point number system
 */
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

/** @brief Validates if the given string is a valid real value
 */
int is_real(char *number)
{
    int size = strlen(number);

    if (size <= REAL_MAX_DIGITS && are_decimal_point_digits(number) == TRUE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/** @brief Validates if the given string is a valid value in fixed point number system
 */
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

/** @brief Extracts the decimal part from a given string, basically it extracts digits
 *          encountered before the decimal point
 */
char *get_integer_part(char *number) // remember to free memory of returned ptr after use
{
    int size = strlen(number);
    char *end_ptr;
    char *int_part = (char *)calloc(size, sizeof(char)); // allocate sufficient memory for int_part

    int dec_num = strtod(number, &end_ptr);

    sprintf(int_part, "%d", dec_num);

    free(number); // Free as not in use

    return int_part;
}

/** @brief Extracts the fraction part from a given string, basically it extracts digits
 *          encountered after the decimal point
 */
char *get_fraction_part(char *number)
{
    int size = strlen(number);
    int fraction_start_at = 1;

    char *fraction_part = (char *)calloc(size, sizeof(char)); // allocate sufficient memory for int_part

    for (int i = 0; number[i] != '.'; i++)
    {
        ++fraction_start_at;
    }

    for (int i = 0; i <= (size - fraction_start_at); i++)
    {
        fraction_part[i] = number[fraction_start_at + i];
    }

    free(number); // Free as not in use later

    return fraction_part;
}