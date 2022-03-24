/**
 * @file convert.c
 * @author Abhay Parashar, 658152558, S22N03, CSCI 261, VIU
 * @version 1.0.0
 * @date August 04, 2021
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "utility.h"

char *decimal_to_binary(char *number, int word_size) // remeber to free the returned c string
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

    return num_binary;
}
//Pointer 'number' is pointing a string representation of a decimal number.
//Get the integer value from the string representation.
//Dynamically allocate enough memory for a new string so that it can hold a binary
//number with 'word_size' binary digits plus 2 prefixes.
//Use decimal-to-binary conversion algorithm to get the equivalent binary digits of
//the decimal number and save the binary digits into the new string.
//Return the pointer of the new string.

char *binary_to_decimal(char *number, int word_size) // free mem fix the prefix problem
{
    int num = 0;
    int total = 0;
    int loop_counter = 2; // Because we want to skip the prefix
    char *res_decimal;

    for (int i = strlen(number) - 3; i >= 0; i--)
    // -2 because we do not want the prefix, additionally we want to start counting
    // from 0 so we have to subtract 1 more so in total we have to subtract 3
    {
        num = pow(RADIX_BINARY, i) * (number[loop_counter] - '0');
        total += num;
        ++loop_counter;
    }

    res_decimal = (char *)malloc((sizeof(char) * word_size) + 1);

    sprintf(res_decimal, "%d", total);

    return res_decimal;
}
//Pointer 'number' is pointing a string representation of a binary number.
//Use binary-to-decimal conversion algorithm to get the equivalent decimal (integer)
//value from the binary digits.
//Dynamically allocate enough memory for a new string so that it can hold a decimal
//number with 'word_size' decimal digits.
//Convert the decimal (integer) value into the new string.
//Return the pointer of the new string.

char *decimal_to_hex(char *number) // remember to free ptr after use
{
    int num;
    char *num_hex;
    char *end_ptr;
    int remainder;
    int loop_counter = 0;

    num = strtod(number, &end_ptr);
    num_hex = (char *)malloc(((sizeof(char) * HEX_MAX_DIGITS) + 1) + 2);

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

    return num_hex;
}
//Pointer 'number' is pointing a string representation of a decimal number.
//Get the integer value from the string representation.
//Dynamically allocate enough memory for a new string so that it can hold a hex
//number with 'HEX_MAX_DIGITS' hex digits plus 2 prefixes.
//Use decimal-to-hex conversion algorithm to get the equivalent hex digits of
//the decimal number and save the hex digits into the new string.
//Add '0x' prefix to the string.
//Return the pointer of the new string.

char *hex_to_decimal(char *number)
{

    long int num = 0;
    long int total = 0;
    int loop_counter = 2;
    char *res_decimal;
    char hex_char;
    int hex_equivalent_digit = 0;

    for (int i = (strlen(number) - 3); i >= 0; i--)
    // -2 because we do not want the prefix, additionally we want to start counting
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

    res_decimal = (char *)malloc((sizeof(char) * DECIMAL_MAX_DIGITS) + 1);

    sprintf(res_decimal, "%li", total);

    return res_decimal;
}
//Pointer 'number' is pointing a string representation of a hex number.
//The hex number is always prefixed with '0x'.
//Use hex-to-decimal conversion algorithm to get the equivalent decimal (integer)
//value from the hex digits.
//Dynamically allocate enough memory for a new string so that it can hold a decimal
//number with 'DECIMAL_MAX_DIGITS' decimal digits.
//Convert the decimal (integer) value into the new string.
//Return the pointer of the new string.

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
//Parameter 'nibble' is a group of four binary digits.
//Return the equivalent hex digit of the nibble.

char *binary_to_hex(char *number) // free the ptr
{
    const int NIBBLE_SIZE = 4;

    char *res_hex;
    char *number_cpy;
    char nibble[NIBBLE_SIZE];
    int num_nibbles;
    int loop_counter = 1;
    int remaining_char = 0;
    int start;

    res_hex = (char *)calloc(HEX_MAX_DIGITS + 1, sizeof(char));

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
    return res_hex;
}

char *hex_to_binary(char *number) // Assume we get hex remember to free after use
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
    return res_bin;
}
//Pointer 'number' is pointing a string representation of a hex number.
//Dynamically allocate enough memory for a new string so that it can hold a binary
//number with 'BINARY_WORD_SIZE' binary digits plus 2 prefixes.
//Add the prefix '0b' to the string.
//Use hex-to-binary conversion algorithm to get the equivalent binary digits of
//the hex number and save the binary digits into the new string.
//Return the pointer of the new string.

char *to_decimal(char *number) // remember to free ptr
{
    char *result;
    char *numcpy = strdup(number);

    if (is_decimal(number) == TRUE)
    {
        int decimal_equi;
        char *end_ptr;

        decimal_equi = strtod(number, &end_ptr);
        sprintf(numcpy, "%d", decimal_equi);
        result = numcpy;

        return result;
    }
    else if (is_binary(number) == TRUE)
    {
        result = binary_to_decimal(number, DECIMAL_MAX_DIGITS);
        return result;
    }
    else if (is_hex(number) == TRUE)
    {
        result = hex_to_decimal(number);
        return result;
    }
    else
    {
        printf("\n Error! Invalid digit in the number: %s\n", number);
        return NULL;
    }
}
//Return the result calling binary_to_decimal() function if the number is
//represented in binary format. Pass the pointer to the first binary digit
//of the binary number into binary_to_decimal() function.
//Return the result calling hex_to_decimal() function if the number is
//represented in hex format.
//Return a copy of the number removing the leading zeros if the number is
//represented in decimal.

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
        return NULL;
    }
}
//Call decimal_to_binary() function if the number is represented in decimal format.
//Add prefix '0b' with the binary number and return.
//Return the result calling hex_to_binary() function if the number is
//represented in hex format.
//Return a copy of the number if the number is represented in binary.

char *to_hex(char *number) // must release mem from strdup
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
        return NULL;
    }
}
//Return the result calling decimal_to_hex() function if the number is
//represented in decimal format.
//Return the result calling binary_to_hex() function if the number is
//represented in binary format.
//Return a copy of the number if the number is represented in hex.

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
//Call is_real_part() function to check whether it is valid integer part of a real number.
//If yes, call decimal_to_binary() function to get the binary representation of the part.
//Extend the binary representation to FIXED_POINT_PART_MAX_SIZE by calling extend_to_word_size()
//function and return the extended binary.

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
//Call is_fixed_point_part() function to check whether it is a valid integer part of a
//fixed point number.
//If yes, call binary_to_decimal() function to return the decimal representation of the part.

char *fraction_part_to_binary(char *number) //remember to free the returned c str
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

        return frac2binary;
    }
    else
    {
        printf(" \nError! Number %s is not in real_part format for conversion:\n", number);
        return NULL;
    }
}
//Call is_real_part() function to check whether it is a valid fraction part of a real number.
//If yes, perform the followings:
//	Allocate enough memory dynamically to a new string to hold
//	FIXED_POINT_PART_MAX_DIGITS binary digits.
//	Use decimal-fraction-to-binary conversion algorithm to get the binary digits and
//	save the binary digits into the new string.
//	Extend the binary representation to FIXED_POINT_PART_MAX_SIZE by calling
//	extend_to_word_size() function and return the extended binary.

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

        snprintf(result, REAL_PART_MAX_DIGITS, "%f", total); // Convert double to string using buffer result

        result = get_fraction_part(result);

        return result;
    }
    else
    {
        printf(" \nError! Number %s is not in fixed point format for conversion:\n", number);
        return NULL;
    }
}
//Call is_fixed_point_part() function to check whether it is a valid fraction part of a
//fixed point number.
//If yes, perform the followings:
//	Use binary-to-fraction conversion algorithm to get the fraction value of a real
//	number.
//	Allocate enough memory dynamically to a new string to hold REAL_PART_MAX_DIGITS
//	decimal digits plus a the decimal point.
//	Convert the fraction value into the new string and return the pointer
//	of the string.

char *to_fixed_point(char *number)
{
    char *int_part;
    char *frac_part;

    char *int_part_bin;
    char *frac_part_bin;
    char *result = calloc(FIXED_POINT_MAX_DIGITS + 1, sizeof(char));

    if (is_real(number) == TRUE)
    {
        int_part = get_integer_part(number);
        int_part_bin = integer_part_to_binary(int_part);

        frac_part = get_fraction_part(number);
        frac_part_bin = fraction_part_to_binary(frac_part);

        result = strcat(result, int_part_bin);

        result = strcat(result, frac_part_bin);

        return result;
    }
    else
    {
        printf(" \nError! Number %s is not in real_part format for conversion:\n", number);
        return NULL;
    }
}
//Call is_real() function to check whether it is a valid  real number.
//If yes, perform the followings:
//	Get the integer part of the real number into a new string by calling
//	get_integer_part() function and pass it to integer_part_to_binary()
//	function to get the binary representation of the integer part of the real number.
//	Get the fraction part of the real number into a new string by calling
//	get_fraction_part() function and pass it to fraction_part_to_binary() function
//	to get the binary representation of the fraction part of the real number.
//	Concatenate both the integer and fraction part binaries into a new
//	fixed point repsrented string.
//	Free all the dynamically allocated memories that are no longer required.
//	Return the pointer of the pointer of the fixed point string.

char *from_fixed_point(char *number)
{
    char *int_part;
    char *frac_part;

    char *int_part_bin = calloc(FIXED_POINT_PART_MAX_DIGITS + 1, sizeof(char));
    char *frac_part_bin = calloc(FIXED_POINT_PART_MAX_DIGITS + 1, sizeof(char));

    char *result = calloc(DECIMAL_MAX_DIGITS + 1, sizeof(char));

    if (is_fixed_point(number) == TRUE)
    {
        memcpy(int_part_bin, &number[0], FIXED_POINT_PART_MAX_DIGITS);
        int_part = binary_to_integer_part(int_part_bin);

        memcpy(frac_part_bin, &number[FIXED_POINT_PART_MAX_DIGITS], FIXED_POINT_PART_MAX_DIGITS);
        frac_part = binary_to_fraction_part(frac_part_bin);

        result = strcat(result, int_part);
        result = strcat(result, ".");

        result = strcat(result, frac_part);

        return result;
    }
    else
    {
        printf(" \nError! Number %s is not in fixed point format for conversion:\n", number);
        return NULL;
    }
}
//Call is_fixed_point() function to check whether it is a valid fixed point number.
//If yes, perform the followings:
//	Get the copy of the integer part of the fixed point number into a new string
//	and pass it to binary_to_integer_part() function to get the decimal
//	representation of the integer part of the fixed point number.
//	Get the copy of the fraction part of the fixed point number into a new string
//	and pass it to binary_to_fraction_part() function to get the decimal fraction
//	representation of the fraction part of the fixed point number.
//	Concatenate both integer and fraction parts into a new
//	real number repsrented string.
//	Free all the dynamically allocated memories that are no longer required.
//	Return the pointer of the real number string.
