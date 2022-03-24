#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
//#include "../include/utility.h"

#define BINARY_WORD_SIZE 32            //Number of digits of a binary word
#define DECIMAL_MAX_DIGITS 10          //Maximum number of digits allowed in a decimal number
#define HEX_MAX_DIGITS 8               //Maximum number of digits allowed in a hex number
#define REAL_PART_MAX_DIGITS 5         //Maximum number of digits allowed in a part of a real number
#define REAL_PART_MAX_VALUE 65536      //Maximum value allowed for a part of a real number
#define FIXED_POINT_PART_MAX_DIGITS 16 //Maximum number of digits allowed in a part of a fixed point number
#define REAL_MAX_DIGITS 11             //Maximum number of digits allowed in a real number
#define FIXED_POINT_MAX_DIGITS 32      //Maximum number of digits allowed in a fixed point number.

#define ASCII_VAL0 48     // Ascii val of 0
#define ASCII_VAL9 57     // Ascii val of 9
#define ASCII_VALPOINT 46 // Ascii val of .(point)
#define ASCII_VALA 65     // Ascii val of 'A'
#define ASCII_VALF 70     // Ascii val of 'F'
#define RADIX_HEX 16      // Radix value for hexadecimal system
#define RADIX_BINARY 2    // Radix value for binary system
#define RADIX_DECIMAL 10  // Radix value for decimal system

#define TRUE 1   //Logical TRUE representation
#define FALSE -1 //Logical FALSE representation

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

int are_binary_digits(char *number)
{
    int size = strlen(number);

    for (int i = 0; i < size; i++)
    {
        // check each character if any character is not 0 or 1 return 1
        if (number[i] != '0' && number[i] != '1')
        {
            return -1;
        }
    }
    // return 1 or true when every digit is 0 or 1
    return 1 /*TRUE*/;
}
//Return TRUE if all the digits of the number are either zero or one.

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

char *get_fraction_part(char *number) // remember to free the string after use
{
    int size = strlen(number);
    int fraction_start_at = 1;
    // Sufficient memory for int_part must be atmost size - 1
    // excluding decimal and atleast one digit after the decimal plus including 1 byte for null char

    char *fraction_part = malloc((sizeof(char) * size) - 1); // allocate sufficient memory for int_part

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

char *decimal_to_binary(char *number, int word_size) // remeber to free the returned c string
{
    int num;
    char *num_binary;
    char *end_ptr;
    const int radix_binary = 2;
    int loop_counter = 0;

    num = strtod(number, &end_ptr);

    num_binary = (char *)malloc((sizeof(char) * word_size) + 2);

    while (num != 0)
    {
        num_binary[loop_counter] = (num % radix_binary) + '0';
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

int is_real_part(char *number)
{
    int size = strlen(number);
    double value;
    char *end_ptr;

    value = strtod(number, &end_ptr);

    if (size <= 5 /*REAL_PART_MAX_DIGITS*/ && are_decimal_digits(number) == 1 /*TRUE*/ && value <= 65536 /*REAL_PART_MAX_VALUE*/)
    {
        return 1; /*TRUE*/
    }
    else
    {
        return -1; /*FALSE*/
    }
}

// WORK IN PROGRESS
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

char *binary_to_decimal(char *number, int word_size) // free mem
{
    if (is_binary(number) == 1 /*TRUE*/)
    {
        const int radix_binary = 2;
        const int radix_decimal = 10;
        int num = 0;
        int total = 0;
        int loop_counter = 0;
        char *end_ptr;
        char *res_decimal;

        num = strtod(number, &end_ptr);

        for (int i = strlen(number) - 1; i >= 0; i--)
        {
            num = pow(radix_binary, i) * (number[loop_counter] - '0');
            total += num;
            ++loop_counter;
        }

        res_decimal = (char *)malloc((sizeof(char) * word_size) + 1);

        res_decimal = itoa(total, res_decimal, radix_decimal);

        return res_decimal;
    }
    else
    {
        printf("\nInput is not in binary format, Error in converting binary to decimal\n");
        return NULL;
    }
}

int are_hex_digits(char *number)
{
    int size = strlen(number);
    char char2check;

    for (int i = 0; i < size; i++)
    {
        char2check = number[i];
        char2check = toupper(char2check);
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

char *hex_to_decimal(char *number) 
{
    if (is_hex(number) == TRUE)
    {
        int num = 0;
        int total = 0;
        int loop_counter = 0;
        char *end_ptr;
        char *res_decimal;
        char hex_char;

        num = strtod(number, &end_ptr);

        for (int i = strlen(number) - 1; i >= 0; i--)
        {
            hex_char = number[loop_counter];
                        printf("Hex val before sub is %d for %c\n",hex_char,hex_char);

            if(hex_char >= ASCII_VALA)
            {
                hex_char -= 17;
                printf("Hex val after sub is now %d for %c\n",hex_char,hex_char);
            }
            num = pow(RADIX_HEX, i) * (number[loop_counter] - '0');
            total += num;
            ++loop_counter;
        }

        res_decimal = (char *)malloc((sizeof(char) * DECIMAL_MAX_DIGITS) + 1);

        res_decimal = itoa(total, res_decimal, RADIX_DECIMAL);

        return res_decimal;
    }
    else
    {
        printf("\nInput is not in hex format, Error in converting hex to decimal\n");
        return NULL;
    }
}
//Pointer 'number' is pointing a string representation of a hex number.
//The hex number is always prefixed with '0x'.
//Use hex-to-decimal conversion algorithm to get the equivalent decimal (integer)
//value from the hex digits.
//Dynamically allocate enough memory for a new string so that it can hold a decimal
//number with 'DECIMAL_MAX_DIGITS' decimal digits.
//Convert the decimal (integer) value into the new string.
//Return the pointer of the new string.

int main()
{
    char test[50];
    char *test_int = "12";
    char *res;
    char *output;
    int result;

    for (int i = 0; i < 6; i++)
    {
        printf("Enter to check : ");
        scanf("%s", res);

        //res = binary_to_decimal(test_int, 2);
        output = hex_to_decimal(res);
        printf("The result is %s \n", output);
    }

    return 0;
}