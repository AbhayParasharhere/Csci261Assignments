/**
 * @file utility.c
 * @author Abhay Parashar, 658152558, S22N03,  CSCI 261, VIU
 * @version 1.0.0
 * @date January 29, 2022
 *
 * It implements the functions specified in 'signed_convert.h' header file that
 * are helpful in converting signed numbers from one number umber system
 * to another.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h"

/** @brief Reverses a c string that was passed as a
 *         parameter
 *
 * This fuction reverses the string with the help of pointers that point
 * to the first and the last valid character in the string(excluding null)
 * First it sets the pointers to the start and end poition of the string
 * then it swaps half of the characters in the string which effectively
 * reverses the the whole string.
 *
 *  @param  *str The pointer to the C style string that needs to be reversed
 *  @return void
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

        // update the end and start pointers
        start++;
        end--;
    }
}

/** @brief Adds a sign at the beginning of the string and shifts all
 *      characters in the string 1 position to the right
 *
 * This fuction add a sign to the beginning of the passed c string
 * with the help of a pointer that points to the end of the string
 * (excluding the null character), then it moves all characters in the
 * string one poistion to the right. Finally, it sets the first character
 * in the string to be the passed sign
 *
 *  @param  *str The pointer to the C style string in which sign has to be added
 *  @param sign The sign that is to be inserted
 *  @return void
 */
void add_sign(char *number, char sign)
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
        // shift the characters in the string one pos to the right
        *(end + 1) = *end;
        // keep adjusting the end pointer
        end--;
    }
    // Finally add the sign to the beginning of the string
    number[0] = sign;
}

/** @brief Adds two characters that were passed as parameters into the string
 *         from the start.
 * With the help of an end pointer pointing to the end char of the string, swaps
 * each character in the string 2 pos to the right.
 * 
 * @param number The string to add the prefix to
 * @param p0 the first letter of the prefix to add
 * @param p0 the first letter of the prefix to add
 * return the string with the prefix attached
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

/** @brief Extends a string to the required size and fills the
 * most signifcant extra digits with zeroes and copies the string
 * content in the required space.
 *
 * This function first checks if the size to be extended is less than the size
 * of the size which would clearly mean that the string does not need any
 * extension, then if it is not the case then it creates a new string in the
 * heap with sufficient space, fills the whole string with zeroes and then finally
 * loops to copy the string,inserting characters from the size difference between
 * the extended and the orginal string.
 *
 *  @param  *str The pointer to the C style string to be extended
 *  @param word_size Size to which the string needs to be sxtended
 *  @return c string that has been extended
 */
char *extend_integer_binary_to_word_size(char *number, int word_size)
{
    int size = (int)strlen(number);
    int diff = word_size - size;

    if (size > word_size)
    {
        return NULL;
    }
    else
    {
        char *newWord = (char *)calloc((word_size + 1), sizeof(char));
        memset(newWord, '0', sizeof(char) * word_size); // Initialise to zero

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

/** @brief Extends a string to the required size copies the string
 * content in the start of the string and fills the
 * least significant extra digits with zeroes 
 *
 * This function first checks if the size to be extended is less than the size
 * of the size which would clearly mean that the string does not need any
 * extension, then if it is not the case then it creates a new string in the
 * heap with sufficient space, fills the whole string with zeroes and then finally
 * loops to copy the string,inserting characters to the start of the extended string.
 *
 *  @param  *str The pointer to the C style string to be extended
 *  @param word_size Size to which the string needs to be sxtended
 *  @return c string that has been extended
 */
char *extend_fraction_binary_to_word_size(char *number, int word_size)
{
    int size = strlen(number);

    if (size > word_size)
    {
        return NULL;
    }
    else
    {
        char *newWord = (char *)calloc((word_size + 1), sizeof(char));
        memset(newWord, '0', sizeof(char) * word_size); // Initialise to zero

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

/** @brief Checks if the given string is just made up of 0's and 1's
 *
 * This function first loops to the string and checks if any character in the string
 * is not a 0 or a 1, if this is the case then it returns FALSE. And after the loop
 * is finished this means that every character in the string is either a 0 or a 1.
 * Therefore, it returns TRUE.
 *
 *  @param  number The pointer to the C style string which is to be checked
 *  @return int Returns the correponding value of TRUE or FALSE based on the check
 */
int are_binary_digits(char *number)
{
    int size = strlen(number);

    for (int i = 0; i < size; i++)
    {
        // check if each character is not a 0 and not a 1
        if (number[i] != '0' && number[i] != '1')
        {
            return FALSE;
        }
    }
    // return true when every digit is 0 or 1
    return TRUE;
}

/** @brief Checks if the given string is just made up digits used in decimal number system.
 *
 * This function first loops to the string and checks if any character in the string
 * is not one of the decimal digits, if this is the case then it returns FALSE. And after
 * the loop is finished this means that every character in the string is one of
 * the decimal digit. Therefore, it returns TRUE.
 *
 *  @param  number The pointer to the C style string which is to be checked
 *  @return int Returns the correponding value of TRUE or FALSE based on the check
 */
int are_decimal_digits(char *number)
{
    int size = strlen(number);

    for (int i = 0; i < size; i++)
    {
        // Check to see if any character's ASCII val is not in the range of 0-9
        if (!(number[i] >= '0' && number[i] <= '9'))
        {
            return FALSE; // return false if any character is not in the decimal digits
        }
    }
    // return true when every digit is one among the valid decimal digits
    return TRUE;
}

/** @brief Checks if the given string contains a valid binary number
 *
 * This function ensures that all digits in the passed string are 0 or 1
 * by passing the number into the are_binary_digits function then it further
 * ensures that the length of the string excluding the null character is within
 * the maximum length which is BINARY_WORD_SIZE. If this is the case, then it
 * returns TRUE, otherwise it returns FALSE.
 *
 *  @param  number The pointer to the C style string which is to be checked
 *  @return int Returns the correponding value of TRUE or FALSE based on the check
 */
int is_binary(char *number)
{
    if (strlen(number) <= BINARY_WORD_SIZE && are_binary_digits(number) == TRUE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/** @brief Checks if the given string contains a valid decimal number
 *
 * This function ensures that all digits in the passed string are one of the valid
 * decimal digits by passing the number into the are_decimal_digits function
 * then it further ensures that the length of the string excluding the null character
 * is within the maximum length which is DECIMAL_MAX_DIGITS. If this is the case,
 * then it returns TRUE, otherwise it returns FALSE.
 *
 *  @param number The pointer to the C style string which is to be checked
 *  @return int Returns the correponding value of TRUE or FALSE based on the check
 */
int is_decimal(char *number)
{
    if (strlen(number) <= DECIMAL_MAX_DIGITS && are_decimal_digits(number) == TRUE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/** @brief Checks if the given string contains a valid biased 127 decimal
 *
 * This function ensures that all digits in the passed string are one of the valid
 * decimal digits by passing the number into the are_decimal_digits function
 * then it further ensures that the length of the string excluding the null character
 * is within the maximum length for a biased number which is
 * BIASED_127_DECIMAL_MAX_DIGITS. If this is the case,
 * then it returns TRUE, otherwise it returns FALSE.
 *
 *  @param number The pointer to the C style string which is to be checked
 *  @return int Returns the correponding value of TRUE or FALSE based on the check
 */
int is_biased_127_decimal(char *number)
{
    if (strlen(number) <= BIASED_127_DECIMAL_MAX_DIGITS && are_decimal_digits(number) == TRUE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/** @brief Checks if the given string contains a valid biased 127 binary
 *
 * This function ensures that all digits in the passed string are one of the valid
 * binary digits by passing the number into the are_binary_digits function
 * then it further ensures that the length of the string excluding the null character
 * is within the maximum length for a biased number which is
 * BIASED_127_BINARY_MAX_DIGITS. If this is the case,
 * then it returns TRUE, otherwise it returns FALSE.
 *
 *  @param number The pointer to the C style string which is to be checked
 *  @return int Returns the correponding value of TRUE or FALSE based on the check
 */
int is_biased_127_binary(char *number)
{
    if (strlen(number) <= BIASED_127_BINARY_MAX_DIGITS && are_binary_digits(number) == TRUE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/** @brief Checks if the given string contains a valid significand
 *
 * This function ensures that all digits in the passed string are one of the valid
 * binary digits by passing the number into the are_binary_digits function
 * then it further ensures that the length of the string excluding the null character
 * is within the maximum length for a significand which is
 * FLOATING_POINT_SIGNIFICAND_DIGITS. If this is the case,
 * then it returns TRUE, otherwise it returns FALSE.
 *
 *  @param number The pointer to the C style string which is to be checked
 *  @return int Returns the correponding value of TRUE or FALSE based on the check
 */
int is_significand(char *number)
{
    if (strlen(number) <= FLOATING_POINT_SIGNIFICAND_DIGITS && are_binary_digits(number) == TRUE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/** @brief Checks if the given string contains a valid decimal number
 *
 * This function ensures that the length of the string excluding the null character
 * is within the maximum length which is REAL_MAX_DIGITS, then it further ensures
 * that all digits in the passed string are one of the valid
 * decimal digits or a decimal point by checking each character with the help of loop
 * against the valid decimal digits or a decimal point. If all cases are true then
 * the function returns else, otherwise it returns FALSE.
 *
 *  @param number The pointer to the C style string which is to be checked
 *  @return int Returns the correponding value of TRUE or FALSE based on the check
 */
int is_real(char *number)
{
    int size = strlen(number);

    if (size <= REAL_MAX_DIGITS)
    {
        for (int i = 0; i < size; i++)
        {
            // Check to see if any character's ASCII val is not in the range of 0-9
            if (!(number[i] >= '0' && number[i] <= '9'))
            {
                if (!(number[i] == '.'))
                    return FALSE; // return false if any character is not in the decimal digits
            }
        }
        // return true when every digit is one among the valid decimal digits
        return TRUE;
    }
    else
    {
        return FALSE; // return false since size of the number is not within the limit
    }
}

/** @brief Checks if the given string contains a valid floating point number
 *
 * This function ensures that all digits in the passed string are 0 or 1
 * by passing the number into the are_binary_digits function then it further
 * ensures that the length of the string excluding the null character is within
 * the maximum length which is FLOATING_POINT_MAX_DIGITS. If this is the case, then it
 * returns TRUE, otherwise it returns FALSE.
 *
 *  @param  number The pointer to the C style string which is to be checked
 *  @return int Returns the correponding value of TRUE or FALSE based on the check
 */
int is_floating_point(char *number)
{
    if (strlen(number) <= FLOATING_POINT_MAX_DIGITS && are_binary_digits(number) == TRUE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/** @brief Extracts the integert part of the given real number
 *
 * This function first creates a c style string with enough memory to store the
 * extracted integer part of the number, then it converts the string into its
 * corresponding number using the strtod function after this it simply stores the
 * result in an integer which stores the integer part of the strtod function result
 * ,after this the integer is converted into a string and returned. It also frees
 * the parameter passed to it as it will not be used later.
 *
 *  @param  number The pointer to the C style string whose integer part is to be extracted
 *  @return char* Returns the pointer to the c string of the extracted integer part of the number
 */
char *get_integer_part(char *number)
{
    int size = strlen(number);

    char *end_ptr;
    char *int_part = (char *)calloc(size + 1, sizeof(char)); // allocate sufficient memory for int_part

    int dec_num = strtod(number, &end_ptr);

    sprintf(int_part, "%d", dec_num);

    return int_part;
}

/** @brief Extracts the fractional part of the given real number
 *
 * This function first creates a c style string with enough memory to store the
 * extracted integer part of the number, then it stores the position of the decimal point
 * in the passed real number by comparing each character in the number against the decimal
 * point for a match, after this with the help of a loop it stores the fraction part
 * which we know where it start from the index of the decimal point and we simply loop
 * and store the fraction part and return the result.
 *
 *  @param  number The pointer to the C style string whose fractional part is to be extracted
 *  @return char* Returns the pointer to the c string of the extracted fraction part of the number
 */
char *get_fraction_part(char *number)
{
    int size = strlen(number);
    int fraction_start_at = 1;

    char *fraction_part = (char *)calloc(size, sizeof(char)); // allocate sufficient memory for frac_part

    for (int i = 0; number[i] != '.'; i++)
    {
        ++fraction_start_at;
    }

    for (int i = 0; i <= (size - fraction_start_at); i++)
    {
        fraction_part[i] = number[fraction_start_at + i];
    }

    return fraction_part;
}
