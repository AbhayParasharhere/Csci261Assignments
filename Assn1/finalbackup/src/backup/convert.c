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
#include "../include/utility.h"

char *decimal_to_binary(char *number, int word_size) // remeber to free the returned c string
{
    // check if decimal
    int num;
    char *num_binary;
    char *end_ptr;
    int loop_counter = 0;

    num = strtod(number, &end_ptr);

    num_binary = (char *)malloc(((sizeof(char) * word_size) + 1) + 2);

    while (num != 0)
    {
        num_binary[loop_counter] = (num % RADIX_BINARY) + '0';
        num = (num / radix_binary);

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

char *binary_to_decimal(char *number, int word_size) // free mem
{
    if (is_binary(number) == TRUE)
    {
        int num = 0;
        int total = 0;
        int loop_counter = 0;
        char *end_ptr;
        char *res_decimal;

        num = strtod(number, &end_ptr);

        for (int i = strlen(number) - 1; i >= 0; i--)
        {
            num = pow(RADIX_BINARY, i) * (number[loop_counter] - '0');
            total += num;
            ++loop_counter;
        }

        res_decimal = (char *)malloc((sizeof(char) * word_size) + 1);

        res_decimal = itoa(total, res_decimal, RADIX_DECIMAL);

        return res_decimal;
    }
    else
    {
        printf("\nInput is not in binary format, Error in converting binary to decimal\n");
        return NULL;
    }
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
    if (is_decimal(number) == TRUE)
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
    else
    {
        printf("\nError in converting decimal to hex as input is not in decimal format\n");
        return NULL;
    }
}
//Pointer 'number' is pointing a string representation of a decimal number.
//Get the integer value from the string representation.
//Dynamically allocate enough memory for a new string so that it can hold a hex
//number with 'HEX_MAX_DIGITS' hex digits plus 2 prefixes.
//Use decimal-to-hex conversion algorithm to get the equivalent hex digits of
//the decimal number and save the hex digits into the new string.
//Add '0x' prefix to the string.
//Return the pointer of the new string.

char *hex_to_decimal(char *number) {}
//Pointer 'number' is pointing a string representation of a hex number.
//The hex number is always prefixed with '0x'.
//Use hex-to-decimal conversion algorithm to get the equivalent decimal (integer)
//value from the hex digits.
//Dynamically allocate enough memory for a new string so that it can hold a decimal
//number with 'DECIMAL_MAX_DIGITS' decimal digits.
//Convert the decimal (integer) value into the new string.
//Return the pointer of the new string.

char nibble_to_hex_digit(char *nibble) {}
//Parameter 'nibble' is a group of four binary digits.
//Return the equivalent hex digit of the nibble.

char *binary_to_hex(char *number) {}
//Create an array of nibbles from the binary number.
//Dynamically allocate enough memory for a new string so that it can hold a hex
//number with 'HEX_MAX_DIGITS' hex digits plus 2 prefixes.
//Add the prefix '0x' to the new string.
//Get the hex digits from the nibbles in the array and save them into the string.
//Return the pointer of the new string.

char *hex_to_binary(char *number) {}
//Pointer 'number' is pointing a string representation of a hex number.
//Dynamically allocate enough memory for a new string so that it can hold a binary
//number with 'BINARY_WORD_SIZE' binary digits plus 2 prefixes.
//Add the prefix '0b' to the string.
//Use hex-to-binary conversion algorithm to get the equivalent binary digits of
//the hex number and save the binary digits into the new string.
//Return the pointer of the new string.

char *to_decimal(char *number) {}
//Return the result calling binary_to_decimal() function if the number is
//represented in binary format. Pass the pointer to the first binary digit
//of the binary number into binary_to_decimal() function.
//Return the result calling hex_to_decimal() function if the number is
//represented in hex format.
//Return a copy of the number removing the leading zeros if the number is
//represented in decimal.

char *to_binary(char *number) {}
//Call decimal_to_binary() function if the number is represented in decimal format.
//Add prefix '0b' with the binary number and return.
//Return the result calling hex_to_binary() function if the number is
//represented in hex format.
//Return a copy of the number if the number is represented in binary.

char *to_hex(char *number) {}
//Return the result calling decimal_to_hex() function if the number is
//represented in decimal format.
//Return the result calling binary_to_hex() function if the number is
//represented in binary format.
//Return a copy of the number if the number is represented in hex.

char *integer_part_to_binary(char *number) {}
//Call is_real_part() function to check whether it is valid integer part of a real number.
//If yes, call decimal_to_binary() function to get the binary representation of the part.
//Extend the binary representation to FIXED_POINT_PART_MAX_SIZE by calling extend_to_word_size()
//function and return the extended binary.

char *binary_to_integer_part(char *number) {}
//Call is_fixed_point_part() function to check whether it is a valid integer part of a
//fixed point number.
//If yes, call binary_to_decimal() function to return the decimal representation of the part.

//WORK IN PROGRESS
char *fraction_part_to_binary(char *number) //remember to free the returned c str
{
    if (is_real_part(number))
    {
        char *frac2binary;
        double num;
        int decimal_part;
        char *end_ptr;
        int loop_counter = 0;
        const int radix_binary = 2;

        frac2binary = (char *)malloc((sizeof(char) * 16 /*FIXED_POINT_PART_MAX_DIGITS*/) + 1);
        num = strtod(number, &end_ptr);
        decimal_part = num;

        while ((num - decimal_part) != 0 && loop_counter < 16 /*FIXED_POINT_PART_MAX_DIGITS*/)
        {
            frac2binary[loop_counter] = decimal_part + '0';
            printf("The decimal part at %d is %d \n", loop_counter, decimal_part);
            num = num * radix_binary;
            decimal_part = num;
            num = num - decimal_part;
            ++loop_counter;
        }

        return frac2binary;
    }
    else
    {
        printf("\nError in converting fraction part to binary as input is not a real number\n");
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

char *binary_to_fraction_part(char *number) {}
//Call is_fixed_point_part() function to check whether it is a valid fraction part of a
//fixed point number.
//If yes, perform the followings:
//	Use binary-to-fraction conversion algorithm to get the fraction value of a real
//	number.
//	Allocate enough memory dynamically to a new string to hold REAL_PART_MAX_DIGITS
//	decimal digits plus a the decimal point.
//	Convert the fraction value into the new string and return the pointer
//	of the string.

char *to_fixed_point(char *number) {}
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

char *from_fixed_point(char *number) {}
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

/*
 * Include necessary header files.
 * Include library header files first, then the custom header files
 */
