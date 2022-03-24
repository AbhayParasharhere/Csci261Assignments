/**
 * @file convert.c
 * @author Abhay Parashar, 658152558, S22N03, CSCI 261, VIU
 * @version 1.0.0
 * @date January 25, 2021
 *
 * Implementation file for functions used in conversion from one number system to another
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "utility.h"

/** @brief Converts from decimal to binary
 *
 * Uses the decimal to binary algorithm to convert the given decimal into
 * a binary and store the result in a c string
 *
 *  @param *number The decimal number in a c string
 *  @param word_size Number of binary digits to hold
 *  @return the converted binary number in a c string
 */
char *decimal_to_binary(char *number, int word_size)
{
    int num;
    char *num_binary;
    char *end_ptr;
    int loop_counter = 0;

    num = strtod(number, &end_ptr);

    num_binary = (char *)calloc(word_size + 2, sizeof(char));

    while (num != 0)
    {
        num_binary[loop_counter] = (num % RADIX_BINARY) + '0';
        num = (num / RADIX_BINARY);

        ++loop_counter;
    }

    reverse(num_binary);

    free(number); // Free memory as number is no longer in use

    return num_binary;
}

/** @brief Converts from binary to decimal
 *
 * Uses the binary to decimal algorithm to convert the given binary into
 * a decimal and store the result in a c string
 *
 *  @param *number The binary number in a c string
 *  @param word_size Number of decimal digits to hold
 *  @return the converted decimal number in a c string
 */
char *binary_to_decimal(char *number, int word_size)
{
    int num = 0;
    int total = 0;
    int loop_counter = 2; // Because we want to skip the prefix
    char *res_decimal;

    res_decimal = (char *)calloc(word_size + 1, sizeof(char));

    for (int i = strlen(number) - 3; i >= 0; i--)
    // -2 because we do not want the prefix, additionally we want to start counting
    // from 0 so we have to subtract 1 more so in total we have to subtract 3
    {
        num = pow(RADIX_BINARY, i) * (number[loop_counter] - '0');
        total += num;
        ++loop_counter;
    }

    sprintf(res_decimal, "%d", total);

    free(number); // Free memory as number is no longer in use

    return res_decimal;
}

/** @brief Converts from decimal to hexadecimal
 *
 * Uses the decimal to hexadecimal algorithm to convert the given decimal into
 * a hexadecimal and store the result in a c string
 *
 *  @param *number The decimal number in a c string
 *  @return the converted hexadecimal number in a c string
 */
char *decimal_to_hex(char *number)
{
    int num;
    char *num_hex;
    char *end_ptr;
    int remainder;
    int loop_counter = 0;

    num = strtod(number, &end_ptr);

    num_hex = (char *)calloc(HEX_MAX_DIGITS + 3, sizeof(char));

    while (num != 0)
    {
        remainder = num % RADIX_HEX;
        if (remainder < 10)
        {
            num_hex[loop_counter] = remainder + ASCII_VAL0;
        }

        else
        {
            num_hex[loop_counter] = remainder + (ASCII_VALA - 10); // We have to subtract by 10 as our character is already greater than 10
        }

        num = (num / RADIX_HEX);

        ++loop_counter;
    }
    num_hex[loop_counter] = '\0'; // End the string to avoid garbage values

    reverse(num_hex);

    add_prefix(num_hex, '0', 'x');

    free(number); // Free number as no longer in use

    return num_hex;
}

/** @brief Converts from hexadecimal to decimal
 *
 * Uses the hexadecimal to decimal algorithm to convert the given hexadecimal into
 * a decimal and store the result in a c string
 *
 *  @param *number The hexadecimal number in a c string
 *  @return the converted decimal number in a c string
 */
char *hex_to_decimal(char *number)
{
    long int num = 0;
    long int total = 0;
    int loop_counter = 2;
    char *res_decimal;
    char hex_char;
    int hex_equivalent_digit = 0;

    res_decimal = (char *)calloc(DECIMAL_MAX_DIGITS + 1, sizeof(char));

    for (int i = (strlen(number) - 3); i >= 0; i--)
    // subtracting 2 as we do not want the prefix, additionally we want to start counting
    // from 0 so we have to subtract 1 more so in total we have to subtract 3
    {
        hex_char = number[loop_counter];
        hex_equivalent_digit = hex_char - '0';

        if (hex_char >= ASCII_VALA)
        {
            hex_char = toupper(hex_char);               // To avoid lowecase conflicts
            hex_char -= ASCII_VALA - ASCII_VAL0;        // Shift the char to the number side
            hex_equivalent_digit = hex_char - '0' + 10; // To get equivalent hex digit for a,b,c etc to be 11,12,12,etc
        }
        num = pow(RADIX_HEX, i) * (hex_equivalent_digit);
        total += num;
        ++loop_counter;
    }

    sprintf(res_decimal, "%li", total);

    free(number); // Free number as no longer in use

    return res_decimal;
}

/** @brief Converts from nibble to hexadecimal
 *
 * Uses the hex table values to convert the given nibble into
 * a hexadecimal character
 *
 *  @param *nibble the given nibble in a c string
 *  @return the converted hexadecimal number in a c string
 */
char nibble_to_hex_digit(char *nibble)
{
    if (strcmp(nibble, "0000") == 0)
    {
        return '0';
    }
    else if (strcmp(nibble, "0001") == 0)
    {
        return '1';
    }
    else if (strcmp(nibble, "0010") == 0)
    {
        return '2';
    }
    else if (strcmp(nibble, "0011") == 0)
    {
        return '3';
    }
    else if (strcmp(nibble, "0100") == 0)
    {
        return '4';
    }
    else if (strcmp(nibble, "0101") == 0)
    {
        return '5';
    }
    else if (strcmp(nibble, "0110") == 0)
    {
        return '6';
    }
    else if (strcmp(nibble, "0111") == 0)
    {
        return '7';
    }
    else if (strcmp(nibble, "1000") == 0)
    {
        return '8';
    }
    else if (strcmp(nibble, "1001") == 0)
    {
        return '9';
    }
    else if (strcmp(nibble, "1010") == 0)
    {
        return 'A';
    }
    else if (strcmp(nibble, "1011") == 0)
    {
        return 'B';
    }
    else if (strcmp(nibble, "1100") == 0)
    {
        return 'C';
    }
    else if (strcmp(nibble, "1101") == 0)
    {
        return 'D';
    }
    else if (strcmp(nibble, "1110") == 0)
    {
        return 'E';
    }
    else if (strcmp(nibble, "1111") == 0)
    {
        return 'F';
    }
    else
    {
        return '\0';
    }
}

/** @brief Converts from binary to hexadecimal
 *
 * Uses the binary to hexadecimal algorithm to convert the given binary into
 * a hexadecimal and store the result in a c string
 *
 *  @param *number The binary number in a c string
 *  @return the converted hexadecimal number in a c string
 */
char *binary_to_hex(char *number)
{
    const int NIBBLE_SIZE = 4;

    char *res_hex;
    char *number_cpy;
    char *nibble;
    int num_nibbles;
    int loop_counter = 1;
    int remaining_char = 0;
    int start;

    res_hex = (char *)calloc(HEX_MAX_DIGITS + 1, sizeof(char));
    nibble = (char *)calloc(NIBBLE_SIZE + 2, sizeof(char));

    number_cpy = strdup(number); // remember to free num cpy

    num_nibbles = ((int)strlen(number_cpy) - 2) / 4;

    for (int i = 0; i < num_nibbles; i++)
    {
        start = (int)strlen(number_cpy) - 4 * loop_counter;
        memcpy(nibble, &number_cpy[start], 4);
        nibble[4] = '\0';
        res_hex[i] = nibble_to_hex_digit(nibble);
        ++loop_counter;
    }
    remaining_char = ((int)strlen(number_cpy) - 2) - (4 * num_nibbles);

    if (remaining_char != 0)
    {
        memcpy(nibble, &number_cpy[2], remaining_char);
        nibble[remaining_char] = '\0';
        res_hex[loop_counter - 1] = nibble_to_hex_digit(extend_to_word_size(nibble, NIBBLE_SIZE));
    }

    reverse(res_hex);
    add_prefix(res_hex, '0', 'x');

    free(number);     // Free number as no longer in use
    free(number_cpy); // Free as no longer in use

    return res_hex;
}

/** @brief Converts from hexadecimal to binary
 *
 * Uses the hexadecimal to binary algorithm to convert the given 
 * hexadecimal into a binary and store the result in a c string
 *
 *  @param *number The hexadecimal number in a c string
 *  @return the converted binary number in a c string
 */
char *hex_to_binary(char *number)
{
    char *res_bin = (char *)calloc(BINARY_WORD_SIZE + 3, sizeof(char));

    for (int i = 0; i < strlen(number); i++)
    {
        switch (toupper(number[i]))
        {
        case '0':
            strcat(res_bin, "0000");
            break;
        case '1':
            strcat(res_bin, "0001");
            break;
        case '2':
            strcat(res_bin, "0010");
            break;
        case '3':
            strcat(res_bin, "0011");
            break;
        case '4':
            strcat(res_bin, "0100");
            break;
        case '5':
            strcat(res_bin, "0101");
            break;
        case '6':
            strcat(res_bin, "0110");
            break;
        case '7':
            strcat(res_bin, "0111");
            break;
        case '8':
            strcat(res_bin, "1000");
            break;
        case '9':
            strcat(res_bin, "1001");
            break;
        case 'A':
            strcat(res_bin, "1010");
            break;
        case 'B':
            strcat(res_bin, "1011");
            break;
        case 'C':
            strcat(res_bin, "1100");
            break;
        case 'D':
            strcat(res_bin, "1101");
            break;
        case 'E':
            strcat(res_bin, "1110");
            break;
        case 'F':
            strcat(res_bin, "1111");
            break;
        }
    }
    add_prefix(res_bin, '0', 'b');

    free(number - 2); // Free the original string passed to it with the prefix, so go back 2 units

    return res_bin;
}

/** @brief Converts any valid given number system to decimal number system
 *
 * Splits the input in terms of all possible valid number system cases
 * and converts them using the functions previously defined into a 
 * decimal value and stores the result in a c string
 *
 *  @param *number The given number to convert in a c string
 *  @return the converted number in decimal number system in a c string
 */
char *to_decimal(char *number)
{
    char *result;
    char *numcpy = strdup(number);

    if (is_decimal(number) == TRUE)
    {
        int decimal_equi;
        char *end_ptr;

        decimal_equi = strtod(number, &end_ptr); // Convert to integer to remove leading zeroes

        sprintf(numcpy, "%d", decimal_equi); // Convert back to string

        result = numcpy;
        return result;
    }
    else if (is_binary(number) == TRUE)
    {
        result = binary_to_decimal(numcpy, DECIMAL_MAX_DIGITS);
        return result;
    }
    else if (is_hex(number) == TRUE)
    {
        result = hex_to_decimal(numcpy);
        return result;
    }
    else
    {
        printf("\n Error! Invalid digit in the number: %s\n", number);
        free(numcpy); // Free as no longer in use
        return NULL;
    }
}

/** @brief Converts any valid given number system to binary
 *
 * Splits the input in terms of all possible valid numbersystem cases
 * and converts them using the functions previously defined into a
 * binary value and stores the result in a c string
 *
 *  @param *number The given number to convert in a c string
 *  @return the converted binary number in a c string
 */
char *to_binary(char *number)
{
    char *result;
    char *numcpy = strdup(number);

    if (is_binary(number) == TRUE)
    {
        result = numcpy;
        return result;
    }
    else if (is_hex(number) == TRUE)
    {
        result = hex_to_binary(numcpy + 2); // We have added 2 when passing as we do not want to pass the prefix 0,x
        return result;
    }
    else if (is_decimal(number) == TRUE)
    {
        result = decimal_to_binary(numcpy, BINARY_WORD_SIZE);
        add_prefix(result, '0', 'b');
        return result;
    }
    else
    {
        printf("\nError! Invalid digit in the number: %s\n", number);
        free(numcpy); // Free as no longer in use
        return NULL;
    }
}

/** @brief Converts any valid given number system to hexadecimal number system
 *
 * Splits the input in terms of all possible valid number system cases
 * and converts them using the functions previously defined into
 * a hexadecimal value stored in a c string
 *
 *  @param *number The given number to convert in a c string
 *  @return the converted binary number in a c string
 */
char *to_hex(char *number)
{
    char *result;
    char *numcpy = strdup(number);

    if (is_decimal(number) == TRUE)
    {
        result = decimal_to_hex(numcpy);
        return result;
    }
    else if (is_binary(number) == TRUE)
    {
        result = binary_to_hex(numcpy);
        return result;
    }
    else if (is_hex(number) == TRUE)
    {
        result = numcpy;
        return result;
    }
    else
    {
        printf("\n Error! Invalid digit in the number: %s\n", number);
        free(numcpy); // Free as no longer in use
        return NULL;
    }
}

/** @brief Converts any valid integer part to binary
 *
 * Uses the decimal to binary function to first convert the 
 * given integer part in a c string into a binary
 * then we add 0s to the right of our output until we complete
 * all 16 max binary bits for our integer part
 *
 *  @param *number The integer part number to convert stored in a c string
 *  @return the converted binary number in a c string
 */
char *integer_part_to_binary(char *number)
{
    char *result;

    if (is_real_part(number) == TRUE)
    {
        result = decimal_to_binary(number, BINARY_WORD_SIZE);
        result = extend_to_word_size(result, FIXED_POINT_PART_MAX_DIGITS);
        return result;
    }
    else
    {
        printf(" \nError! Number %s is not in real_part format for conversion:\n\n", number);
        return NULL;
    }
}

/** @brief Converts any valid binary number in fixed point format into to an integer
 * 
 * Uses the binary to decimal function to first convert the 
 * given integer part in a c string to convert into a binary
 * number then we store it into a c string
 *
 *  @param *number The binary number to convert stored in a c string
 *  @return the converted integer in a c string
 */
char *binary_to_integer_part(char *number)
{
    char *result;
    char *num_cpy = strdup(number);

    if (is_fixed_point_part(number) == TRUE)
    {
        add_prefix(num_cpy, '0', 'b');
        result = binary_to_decimal(num_cpy, DECIMAL_MAX_DIGITS);
        return result;
    }
    else
    {
        printf(" \nError! Number %s is not in fixed_point format for conversion:\n", number);
        return NULL;
    }
}

/** @brief Converts any valid fraction part to binary
 *
 * Uses the decimal to binary function to first convert the 
 * given fraction part in a c string into a binary
 * then we add 0s to the left of our output until we complete
 * all 16 max binary bits for our fraction part
 *
 *  @param *number The fraction part number to convert stored in a c string
 *  @return the converted binary number in a c string
 */
char *fraction_part_to_binary(char *number)
{
    if (is_real_part(number) == TRUE)
    {
        char *frac2binary;
        char *num_cpy = strdup(number);
        double num;
        int decimal_part;
        char *end_ptr;
        int loop_counter = 0;

        frac2binary = (char *)calloc(FIXED_POINT_PART_MAX_DIGITS + 1, sizeof(char));
        memset(frac2binary, ASCII_VAL0, sizeof(char) * strlen(frac2binary)); // Initialise to zero

        add_prefix(num_cpy, '0', '.');
        num = strtod(num_cpy, &end_ptr);
        decimal_part = num;

        while ((num - decimal_part) != 0 && loop_counter < FIXED_POINT_PART_MAX_DIGITS)
        {
            frac2binary[loop_counter] = decimal_part + '0';
            num = num * RADIX_BINARY;
            decimal_part = num;
            num = num - decimal_part;
            ++loop_counter;
        }

        memcpy(frac2binary, &frac2binary[1], strlen(frac2binary)); // Remove extra 0 in the start

        if (strlen(frac2binary) < FIXED_POINT_PART_MAX_DIGITS)
        {
            frac2binary = extend_to_word_size_trailing(frac2binary, FIXED_POINT_PART_MAX_DIGITS);
        }

        free(num_cpy); // free as no longer in use
        return frac2binary;
    }
    else
    {
        printf(" \nError! Number %s is not in real_part format for conversion:\n", number);
        return NULL;
    }
}

/** @brief Converts any valid binary number into a fraction
 * 
 * Uses the binary to fraction part algorithm to first convert the 
 * given binary number stored in a c string into a fractional
 * number and then we store the result into a c string
 *
 *  @param *number The binary number to convert stored in a c string
 *  @return the converted fraction in a c string
 */
char *binary_to_fraction_part(char *number)
{
    if (is_fixed_point(number) == TRUE)
    {
        double num = 0;
        double total = 0;
        char *result;

        for (int i = 0; i < strlen(number); i++)
        {
            num = (1 / pow(RADIX_BINARY, i + 1)) * (number[i] - '0');
            total += num;
        }

        result = (char *)calloc(REAL_PART_MAX_DIGITS + 2, sizeof(char));

        snprintf(result, REAL_PART_MAX_DIGITS, "%0.5f", total); // Convert double to string using buffer result

        result = get_fraction_part(result);

        return result;
    }
    else
    {
        printf(" \nError! Number %s is not in fixed point format for conversion:\n", number);
        return NULL;
    }
}

/** @brief Converts any real number into a binary in a fixed point format 
 * 
 * First, it splits the real number into its respective integer and fractional
 * componenent then converts each into a binary in a fixed point format using the
 * function's integer_part_to_binary and fraction_part_to_binary respectively.
 * Finally it concatenates them into an output string to get the valid
 * binary number in a fixed point format
 *
 *  @param *number The real number to convert stored in a c string
 *  @return converted fixed point binary number stored in a c string
 */
char *to_fixed_point(char *number)
{
    char *int_part;
    char *frac_part;

    char *int_part_bin;
    char *frac_part_bin;
    char *result = (char *)calloc(FIXED_POINT_MAX_DIGITS + 1, sizeof(char));

    if (is_real(number) == TRUE)
    {
        int_part = get_integer_part(strdup(number)); // allocated string by strdup is freed in get_int_part
        int_part_bin = integer_part_to_binary(int_part);

        frac_part = get_fraction_part(strdup(number)); // allocated string by strdup is freed in get_frac_part
        frac_part_bin = fraction_part_to_binary(frac_part);

        result = strcat(result, int_part_bin);

        result = strcat(result, frac_part_bin);

        free(frac_part_bin); // Free as no longer used
        free(int_part_bin);  // Free as no longer used
        return result;
    }
    else
    {
        printf(" \nError! Number %s is not in real_part format for conversion:\n", number);
        free(result); // Free as result is not used
        return NULL;
    }
}

/** @brief Converts any binary in a fixed point format into a real number 
 * 
 * First, it splits the binary into its respective integer and fractional
 * componenent then converts each into decimal number system format using the
 * function's binary_to_integer_part and binary_to_fraction_part respectively.
 * Finally it concatenates them into an output string to get the valid
 * real number
 *
 *  @param *number The binary number to convert stored in a c string
 *  @return converted real number stored in a c string
 */
char *from_fixed_point(char *number)
{
    char *int_part;
    char *frac_part;

    char *int_part_bin;
    char *frac_part_bin;
    char *result;

    if (is_fixed_point(number) == TRUE)
    {
        result = (char *)calloc(DECIMAL_MAX_DIGITS + 1, sizeof(char));
        int_part_bin = (char *)calloc(FIXED_POINT_PART_MAX_DIGITS + 1, sizeof(char));
        frac_part_bin = (char *)calloc(FIXED_POINT_PART_MAX_DIGITS + 1, sizeof(char));

        memcpy(int_part_bin, &number[0], FIXED_POINT_PART_MAX_DIGITS);
        int_part = binary_to_integer_part(int_part_bin);

        memcpy(frac_part_bin, &number[FIXED_POINT_PART_MAX_DIGITS], FIXED_POINT_PART_MAX_DIGITS);
        frac_part = binary_to_fraction_part(frac_part_bin);

        result = strcat(result, int_part);
        result = strcat(result, ".");

        result = strcat(result, frac_part);

        free(int_part);  // Free as no longer used
        free(frac_part); // Free as no longer used

        return result;
    }
    else
    {
        printf(" \nError! Number %s is not in fixed point format for conversion:\n", number);
        return NULL;
    }
}
