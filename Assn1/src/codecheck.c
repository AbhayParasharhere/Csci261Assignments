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

char *extend_to_word_size_trailing(char *number, int word_size)
{
    int size = strlen(number);
    if (size > word_size)
    {
        printf("Error in extending\n");
    }
    else
    {
        char *newWord = malloc(sizeof(char) * (word_size + 1));
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
//If the length of the 'number' is greater than 'word_size' report error.
//If the length of the 'number' is less than 'word_size' do the followings:
//	Allocate enough memory for a new word.
//	Fill the most significant extra digits of the word with zeros and copy
//	the least significant digits from the number.
//	Free the memory from the pointer 'number'.
//	Point the new word by the pointer 'number'.

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
        //free(number);
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

    num_binary = (char *)calloc(word_size + 2, sizeof(char));

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

// // WORK IN PROGRESS
// char *fraction_part_to_binary(char *number) //remember to free the returned c str
// {
//     if (is_real_part(number))
//     {
//         char *frac2binary;
//         double num;
//         int decimal_part;
//         char *end_ptr;
//         int loop_counter = 0;
//         const int radix_binary = 2;

//         frac2binary = (char *)malloc((sizeof(char) * 16 /*FIXED_POINT_PART_MAX_DIGITS*/) + 1);
//         num = strtod(number, &end_ptr);
//         decimal_part = num;

//         while ((num - decimal_part) != 0 && loop_counter < 16 /*FIXED_POINT_PART_MAX_DIGITS*/)
//         {
//             frac2binary[loop_counter] = decimal_part + '0';
//             printf("The decimal part at %d is %d \n", loop_counter, decimal_part);
//             num = num * radix_binary;
//             decimal_part = num;
//             num = num - decimal_part;
//             ++loop_counter;
//         }

//         return frac2binary;
//     }
//     else
//     {
//         printf("\nError in converting fraction part to binary as input is not a real number\n");
//         return NULL;
//     }
// }
// //Call is_real_part() function to check whether it is a valid fraction part of a real number.
// //If yes, perform the followings:
// //	Allocate enough memory dynamically to a new string to hold
// //	FIXED_POINT_PART_MAX_DIGITS binary digits.
// //	Use decimal-fraction-to-binary conversion algorithm to get the binary digits and
// //	save the binary digits into the new string.
// //	Extend the binary representation to FIXED_POINT_PART_MAX_SIZE by calling
// //	extend_to_word_size() function and return the extended binary.

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

char *hex_to_decimal(char *number)
{
    if (is_hex(number) == TRUE)
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
                hex_char -= ASCII_VALA - ASCII_VAL0;        // Shift the char to the equivalent number - 10
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

    sprintf(res_decimal,"%d",total);

    return res_decimal;
}
//Pointer 'number' is pointing a string representation of a binary number.
//Use binary-to-decimal conversion algorithm to get the equivalent decimal (integer)
//value from the binary digits.
//Dynamically allocate enough memory for a new string so that it can hold a decimal
//number with 'word_size' decimal digits.
//Convert the decimal (integer) value into the new string.
//Return the pointer of the new string.

char nibble_to_hex_digit(char *nibble)
{
    const int nibble_length = 4;
    if (are_binary_digits(nibble) && strlen(nibble) == nibble_length)
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
    }
    else
    {
        printf("Error the input is not a nibble, error in converting from nibble to hex\n");
        return '\0';
    }
}
//Parameter 'nibble' is a group of four binary digits.
//Return the equivalent hex digit of the nibble.

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

// WORK IN PROGRESS
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
    int end;

    res_hex = (char *)calloc(HEX_MAX_DIGITS + 1, sizeof(char));

    number_cpy = strdup(number); // remember to free num cpy

    num_nibbles = ((int)strlen(number_cpy) - 2) / 4;

    for (int i = 0; i < num_nibbles; i++)
    {
        start = (int)strlen(number_cpy) - 4 * loop_counter;
        printf("start is %d length is %d\n", start, (int)strlen(number_cpy));
        memcpy(nibble, &number_cpy[start], 4);
        nibble[4] = '\0';
        res_hex[i] = nibble_to_hex_digit(nibble);
        printf("Nibble is %s res_hex is %s\n", nibble, res_hex);
        ++loop_counter;
    }
    remaining_char = ((int)strlen(number_cpy) - 2) - (4 * num_nibbles);

    if (remaining_char != 0)
    {
        end = (int)strlen(number_cpy) - (4 * num_nibbles);
        memcpy(nibble, &number_cpy[2], remaining_char);
        nibble[remaining_char] = '\0';
        res_hex[loop_counter - 1] = nibble_to_hex_digit(extend_to_word_size(nibble, NIBBLE_SIZE));
    }

    reverse(res_hex);
    add_prefix(res_hex, '0', 'x');
    return res_hex;
}
//Create an array of nibbles from the binary number.
//Dynamically allocate enough memory for a new string so that it can hold a hex
//number with 'HEX_MAX_DIGITS' hex digits plus 2 prefixes.
//Add the prefix '0x' to the new string.
//Get the hex digits from the nibbles in the array and save them into the string.
//Return the pointer of the new string.

char *get_integer_part(char *number) // remember to free memory of returned ptr after use
{
    int size = strlen(number);
    char *end_ptr;
    char *int_part = malloc(sizeof(char) * size); // allocate sufficient memory for int_part

    int dec_num = strtod(number, &end_ptr);

    int_part = itoa(dec_num, int_part, RADIX_DECIMAL);

    return int_part;
}
//Return a new string copying the integer part of the real number.

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

char *to_decimal(char *number)
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
        printf("Just passed %s to the hex dude\n",numcpy+2);
        result = hex_to_binary(numcpy+2); // +2 because we do not want to pass the prefix
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
        return NULL;
    }
}
//Return the result calling decimal_to_hex() function if the number is
//represented in decimal format.
//Return the result calling binary_to_hex() function if the number is
//represented in binary format.
//Return a copy of the number if the number is represented in hex.

char *binary_to_fraction_part(char *number) // free output
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

        prinf("\n\nNow holdup the actual precision for frac is %f\n",total);

        snprintf(result, REAL_PART_MAX_DIGITS, "%f", total); // Convert double to string using buffer result
        result = get_fraction_part(result);

        return result;
    }
    else
    {
        printf("Can't convert from binary to fraction\0");
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

char *integer_part_to_binary(char *number)
{
    char *result;

    if (is_real_part(number) == TRUE)
    {
        result = decimal_to_binary(number, BINARY_WORD_SIZE);
        printf("Without extension is %s \n", result);
        result = extend_to_word_size(result, FIXED_POINT_PART_MAX_DIGITS);
        return result;
    }
    else
    {
        printf("Can't convert from integer part to binary\n");
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
        printf("Can't convert from binary to integer part\n");
        return NULL;
    }
}
//Call is_fixed_point_part() function to check whether it is a valid integer part of a
//fixed point number.
//If yes, call binary_to_decimal() function to return the decimal representation of the part.

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

        printf("Int part is %s\n",int_part);

        int_part_bin = integer_part_to_binary(int_part);

        printf("Int bin part is %s\n",int_part_bin);

        frac_part = get_fraction_part(number);
        
        printf("frac part is %s\n",frac_part);

        frac_part_bin = fraction_part_to_binary(frac_part);

        printf("Int bin part is %s\n",frac_part_bin);


        result = strcat(result, int_part_bin);

        result = strcat(result, ".");
        result = strcat(result, frac_part_bin);

        return result;
    }
    else
    {
        printf("Can't convert to fixed point\n");
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
        output = fraction_part_to_binary(res);
        printf("The result is %s \n", output);
    }

    return 0;
}