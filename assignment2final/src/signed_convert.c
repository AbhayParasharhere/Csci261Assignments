/**
 * @file signed_convert.c
 * @author Abhay Parashar, 658152558, S22N03,  CSCI 261, VIU
 * @version 1.0.0
 * @date January 29, 2022
 *
 * It implements the functions specified in 'signed_convert.h' header file that
 * converts signed numbers from one number system to another.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "signed_convert.h"
#include "utility.h"

/** @brief Converts from integer to binary
 *
 * Uses the integer to binary algorithm to convert the given decimal into
 * a binary and store the result in a c string. To do this we first
 * create a new string in the heap with enough memory to hold the converted
 * binary number, then we follow the conversion algorithm from integer to binary in which we
 * continuously divide the int_num by 2 and note the remainder until int_num
 * becomes zero. After this we reverse the order of the remainders we have noted
 * so far to get the converted result in binary.
 *
 *  @param int_num The decimal number to be converted
 *  @param binary_size Number of binary digits to hold
 *  @return the converted binary number in a c string
 */
char *integer_to_binary(int int_num, int binary_size)
{
    int num = int_num; // copy of int_num
    char *num_binary;
    int loop_counter = 0;

    num_binary = (char *)calloc(binary_size + 1, sizeof(char));

    while (num != 0)
    {
        num_binary[loop_counter] = (num % 2) + '0';
        num = (num / 2);
        ++loop_counter;
    }

    reverse(num_binary);

    return num_binary;
}

/** @brief Converts from fraction to binary
 *
 * Uses the fraction to binary algorithm to convert the given fraction into
 * a binary and store the result in a c string. To do this we first
 * create a new string in the heap with enough memory to hold the converted
 * binary number, then we convert the number into a double from a c string.
 * Following this, we convert the fractional part into its corresponding fraction
 * in the form 0."fractionapart" by dividing the fractional part with 10 raised
 * to the power of the number of digits fractional part has, which can be easily
 * found using the formula log10(fractional_part) + 1. Afterwards we follow the
 * conversion algorithm from fraction to binary in which we continuously multiply
 * the digit starting at the position after point by 2 and noting the integer part
 * until either the integer part of the result becomes zero or we reach the required
 * precision given by binary_size. After this we extend the result with zeroes in the
 * back as per our requirement.
 *
 *  @param *number The fractional part in a c string
 *  @param binary_size Number of binary digits to hold
 *  @return the converted binary number in a c string
 */
char *fraction_to_binary(char *number, int binary_size)
{
    char *frac2binary;
    char *num_cpy = strdup(number);
    double num;
    int decimal_part;
    char *end_ptr;
    int loop_counter = 0;

    frac2binary = (char *)calloc(binary_size + 1, sizeof(char));
    memset(frac2binary, '0', sizeof(char) * strlen(frac2binary)); // Initialise to zero

    add_prefix(num_cpy, '0', '.');
    num = strtod(num_cpy, &end_ptr);

    while ((num - decimal_part) != 0 && loop_counter < binary_size)
    {
        frac2binary[loop_counter] = decimal_part + '0';
        num = num * 2;
        decimal_part = num;
        num = num - decimal_part;
        ++loop_counter;
    }

    memcpy(frac2binary, &frac2binary[1], strlen(frac2binary)); // Remove extra 0 in the start

    if (strlen(frac2binary) < binary_size)
    {
        frac2binary = extend_fraction_binary_to_word_size(frac2binary, binary_size);
    }

    // free(num_cpy); // free as no longer in use
    return frac2binary;
}

/** @brief Converts from binary to integer
 *
 * Uses the binary to integer algorithm to convert the given binary into
 * an integer and store the result in a c string. First we chek if the
 * flag is_sign_magnitude is TRUE or not, to determine the numbers in the
 * binary string we want to include in our conversion. We raise 2 to the
 * position of that number and multiply it by the corresponding binary digit at that
 * position. NOTE the most significant digit has position 1.Then we finally accumulate
 *  each of these results to get the converted result in decimal.
 *
 *  @param *number The binary number to convert in a c string
 *  @param is_sign_magnitude Flag to check if we want to include the sign bit in conversion
 *  @return the converted intger number in a c string
 */
int binary_to_int(char *number, int is_sign_magnitude)
{
    int num = 0;
    int res_int = 0;
    int loop_counter = 0;
    int start = 0;
    int end_cond = 0;
    start = strlen(number) - 1; // -1 as we are counting from 0

    if (is_sign_magnitude == TRUE)
    {
        start -= 1;       // Loop one time less than normally
        loop_counter = 1; // Do not include the most significant bit
    }

    for (int i = start; i >= end_cond; i--)
    {
        num = pow(2, i) * (number[loop_counter] - '0');
        res_int += num;
        ++loop_counter;
    }

    return res_int;
}

/** @brief Perform bit addition between 2 operands and a carryin
 *
 * Uses binary addition algorthm to add op1,op2 while keeping track
 * of the carryin stored in cin and updates the carryout *cout
 * accordingly and returns the result of the binary addition.
 *
 *  @param op1 Operand 1 in binary addition stored in a char
 *  @param op2 Operand 1 in binary addition stored in a char
 *  @param cin The carryin stored in a char
 *  @param *cout The carry out stored in a *char
 *  @return resultant char of the binary addition
 */
char one_bit_add(char op1, char op2, char cin, char *cout)
{
    char res;

    if (op1 == '0' && op2 == '0' && cin == '0')
    {
        cout[0] = '0';
        res = '0';
    }
    if (op1 == '0' && op2 == '1' && cin == '0')
    {
        cout[0] = '0';
        res = '1';
    }
    if (op1 == '1' && op2 == '0' && cin == '0')
    {
        cout[0] = '0';
        res = '1';
    }
    if (op1 == '1' && op2 == '1' && cin == '0')
    {
        cout[0] = '1';
        res = '0';
    }
    if (op1 == '0' && op2 == '0' && cin == '1')
    {
        cout[0] = '0';
        res = '1';
    }
    if (op1 == '0' && op2 == '1' && cin == '1')
    {
        cout[0] = '1';
        res = '0';
    }
    if (op1 == '1' && op2 == '0' && cin == '1')
    {
        cout[0] = '1';
        res = '0';
    }
    if (op1 == '1' && op2 == '1' && cin == '1')
    {
        cout[0] = '1';
        res = '1';
    }
    return res;
}

/** @brief Extracts the magnitiude in binary format for an integer
 *
 *  Checks for the sign bit, if yes then replaces the sign with 0 then
 *  converts the string into a number and changes the number into a binary
 *  by calling function integer_to_binary and returns the resultant string.
 *
 *  @param *signed_number C string containing the number to convert
 *  @param binary_size No of binary digits for the resultant string to hold
 *  @return the extracted magnitude in binary form stored in a c string
 */
char *get_magnitude_binary(char *signed_number, int binary_size)
{
    char *res_binary;
    char *signed_number_cpy = strdup(signed_number);
    int res_integer;

    if (signed_number[0] == '+' || signed_number[0] == '-')
    {
        signed_number_cpy[0] = '0'; // For ignoring the sign bit
    }

    res_integer = atoi(signed_number_cpy);

    free(signed_number_cpy);

    res_binary = integer_to_binary(res_integer, binary_size);

    return res_binary;
}

/** @brief Converts the given decimal to a binary number in signed format
 *
 *  First this function checks if the given input is a decimal, then it fetches
 *  the magnitude of the number in binary format by calling the get_magnitude_binary
 *  and then the result is extended to BINARY_WORD_SIZE. Finally the appropriate
 *  sign is added by comparing the first number in our input to + or - sign.
 *
 *  @param *_number C string containing the number to convert
 *  @return the converted result in binary form stored in a c string
 */
char *to_sign_magnitude(char *number)
{
    char *result;

    if (is_decimal(number + 1) == TRUE)
    {
        result = get_magnitude_binary(number, BINARY_WORD_SIZE);
        result = extend_integer_binary_to_word_size(result, BINARY_WORD_SIZE);

        if (number[0] == '-') // Set sign bit to 1
        {
            result[0] = '1';
        }

        return result;
    }
    else
    {
        printf("\n Error can't convert to_sign_magnitude input invalid not a decimal\n");
        return NULL;
    }
}

/** @brief Converts the given signed binary number to a decimal number with the appropriate sign
 *
 *  First this function checks if the given input is a binary, then it converts the input
 *  into a decimal by calling binary_to_int with the is_sign_magnitude flag true. Finally we
 *  add the appropriate sign based on the sign bit of the input, convert the result into
 *  decimal and return the output.
 *
 *  @param *number C string containing the number to extract the magnitude
 *  @return the converted result in decimal form stored in a c string
 */
char *from_sign_magnitude(char *number)
{
    int res_int;

    if (is_binary(number) == TRUE)
    {
        char *result = (char *)calloc(DECIMAL_MAX_DIGITS + 1, sizeof(char));

        res_int = binary_to_int(number, TRUE);

        snprintf(result, DECIMAL_MAX_DIGITS + 1, "%d", res_int);

        if (number[0] == '1') // Add the sign as appropriate
        {
            add_sign(result, '-');
        }
        else
        {
            add_sign(result, '+');
        }

        return result;
    }
    else
    {
        printf("\n Error can't convert input invalid not a binary\n");
        return NULL;
    }
}

/** @brief Flips each bit from 0 to 1 or 1 to 0 in a given binary
 *
 *  This function loops through the entire number and changes each bit from 0
 *  to 1 or 1 to 0.
 *
 *  @param *number C string containing the number to flip.
 *  @return void
 */
void ones_complement(char *number)
{
    for (int i = 0; i < strlen(number); i++)
    {
        if (number[i] == '0')
        {
            number[i] = '1';
        }
        else
        {
            number[i] = '0';
        }
    }
}

/** @brief Finds the two's complement of a given binary number
 *
 *  This function first finds the 1's complement of the given binary
 *  by calling the ones_complement function, then it adds 1 bit to
 *  the result of the 1's complement by calling the one_bit_add
 *  function. For adding, initially the carry in is set to 0 and
 *  later the operand 2 is set to 0. Finally we return the result stored
 *  in a c string.
 *
 *  @param *number C string containing the binary numebr
 *  @return void
 */
void twos_complement(char *number)
{
    char *carryout = (char *)calloc(2,sizeof(char));
    int loop_counter = 0;

    loop_counter = strlen(number) - 1;
    carryout[0] = '1';
    ones_complement(number); // Get the 1's complement

    while (carryout[0] != '0' && loop_counter >= 0)
    {
        if (loop_counter == strlen(number) - 1) // The starting case
        {
            number[loop_counter] = one_bit_add(number[loop_counter], carryout[0], '0', carryout);
        }
        else
        {
            number[loop_counter] = one_bit_add(number[loop_counter], '0', carryout[0], carryout);
        }
        --loop_counter;
    }
    free(carryout);
}

/** @brief Finds the two's complement of a given decimal
 *
 *  This function first checks if the input is a valid decimal. Then it converts
 *  the number into a binary, extends the result and finally if the input was
 *  negative it converts ther resultant binary into 2's complement.Finally we
 *  return the result stored in a c string.
 *
 *  @param *number C string containing the decimal numebr
 *  @return c string containing the converted 2's complement number
 */
char *to_twos_complement(char *number)
{
    char *result;

    if (is_decimal(number + 1) == TRUE)
    {
        result = get_magnitude_binary(number, BINARY_WORD_SIZE);
        result = extend_integer_binary_to_word_size(result, BINARY_WORD_SIZE);

        if (number[0] == '-') // Call the 2's complement
        {
            twos_complement(result);
        }
        return result;
    }
    else
    {
        printf("\n Error can't convert input invalid not a decimal\n");
        return NULL;
    }
}

/** @brief Converts 2's complement into a decimal
 *
 *  This function first checks if the input is a valid binary. Then it converts
 *  the number into a decimal, using the 2's complement to decimal algorithm. We
 *  store the result in a c string and return the result.
 *
 *  @param *number C string containing the 2's complement number
 *  @return c string containing the converted 2's decimal number
 */
char *from_twos_complement(char *number)
{
    int num = 0;
    int res_int = 0;
    int loop_counter = 0;
    int start = 0;

    if (is_binary(number) == TRUE)
    {
        char *result = (char *)calloc(DECIMAL_MAX_DIGITS + 1,sizeof(char));

        start = strlen(number) - 1; // as we are counting from 0

        for (int i = start; i >= 0; i--)
        {
            num = pow(2, i) * (number[loop_counter] - '0');
            if (loop_counter == 0) // the first bit in 2's complement
            {
                num *= -1;
            }
            res_int += num;
            ++loop_counter;
        }

        snprintf(result, DECIMAL_MAX_DIGITS + 1, "%d", res_int);

        return result;
    }
    else
    {
        printf("\n Error can't convert input invalid not a binary\n");
        return NULL;
    }
}

/** @brief Converts the given integer into a biased 127 number
 *
 *  This function first checks if the input is in the valid range.Adds the biased
 *  value into the number. Then it converts the result into a binary, using the
 *  integer to binary function. Finally we extend the result and return it.
 *
 *  @param number The decimal to convert
 *  @return c string containing the converted biased 127 number.
 */
char *int_to_biased_127(int number)
{
    char *res_biased;

    if (number <= BIASED_127_DECIMAL_MAX_VALUE && number >= BIASED_127_DECIMAL_MIN_VALUE)
    {
        number += BIASED_VALUE; // add the biased value
        res_biased = integer_to_binary(number, BIASED_127_BINARY_MAX_DIGITS);
        res_biased = extend_integer_binary_to_word_size(res_biased, BIASED_127_BINARY_MAX_DIGITS);

        return res_biased;
    }
    else
    {
        printf("\n Error can't convert input invalid \n");
        return NULL;
    }
}

/** @brief Converts the given biased 127 decimal into a biased 127 binary
 *
 *  This function first checks if the input is in the valid biased 127 decimal.Then
 *  it converts the result into a binary 127 integer, using the integer to biased 127
 *  function. Finally we extend the result and return it.
 *
 *  @param number The decimal to convert
 *  @return c string containing the converted biased 127 binary number.
 */
char *to_biased_127(char *number)
{
    char *result;
    char *endptr;
    char *valid_input = strdup(number);
    int decimal = 0;

    decimal = strtod(valid_input, &endptr);

    if (number[0] == '+' || number[0] == '-')
    {
        memcpy(valid_input, &number[1], strlen(number));
    }

    if (is_biased_127_decimal(valid_input) == TRUE)
    {
        result = int_to_biased_127(decimal);
        free(valid_input);
        return result;
    }
    else
    {
        printf("\n Error can't convert input invalid \n");
        free(valid_input);
        return NULL;
    }
}

/** @brief Converts the given biased 127 binary into decimal
 *
 *  This function first checks if the input is in the valid biased 127 binary.Then
 *  it converts the result into a integer, using the binary to int function and
 *  subtract the biased value to get the final result. Finally we return the result
 *  stored in a c string.
 *
 *  @param *number C string containing the biased 127 binary to convert
 *  @return The converted decimal
 */
int int_from_biased_127(char *number)
{
    int result;

    if (is_biased_127_binary(number) == TRUE)
    {
        result = binary_to_int(number, FALSE);
        result -= BIASED_VALUE;
        return result;
    }
    else
    {
        printf("\n Error can't convert input invalid \n");
        return 0;
    }
}

/** @brief Converts the given biased 127 binary into decimal
 *
 *  This function first checks if the input is in the valid biased 127 binary.Then
 *  it converts the result into a integer, using the int to biased 127 function.
 *  Finally we return the result stored in a c string.
 *
 *  @param *number C string containing the biased 127 binary to convert
 *  @return The converted biased 127 stored in a c string
 */
char *from_biased_127(char *number)
{
    int int_biased = 0;

    if (is_biased_127_binary(number) == TRUE)
    {
        char *result = (char *)calloc(BIASED_127_DECIMAL_MAX_DIGITS + 2,sizeof(char));

        int_biased = int_from_biased_127(number);
        snprintf(result, BIASED_127_DECIMAL_MAX_DIGITS + 2, "%d", int_biased);
        return result;
    }
    else
    {
        printf("\n Error can't convert input invalid \n");
        return NULL;
    }
}

/** @brief Sets the value of exponent for any given integer and fraction part of a real number
 *  and shifts the frac and int part accordingly
 *
 *  Uses the floating-point-normalization algorithm to shift the integer and the fraction so that
 *  the real number is in the scientific format and updates the exponent accordingly.
 *
 *  @param *integer the integer part of the real number
 *  @param *fraction the fraction part of the real number
 *  @param *exponent the exponent stored in an integer string
 *  @return void
 */
void normalize(char *integer, char *fraction, int *exponent)
{
    if (strlen(integer) > 1)
    {
        char *buffer = (char *)calloc((FLOATING_POINT_SIGNIFICAND_DIGITS * 3),sizeof(char));
        memcpy(buffer,integer,strlen(integer));// copy the integer to the buffer

        *exponent = strlen(integer) - 1;
        strcat(&buffer[1], fraction);
        memcpy(fraction, &buffer[1], FLOATING_POINT_SIGNIFICAND_DIGITS);
        integer[1] = 0;
        free(buffer);
    }
    else
    {
        if (integer[0] == '0')
        {
            for (int i = 0; fraction[i] != '1'; i++)
            {
                --(*exponent);
            }
            --(*exponent); // as it does not decrease exponent when we reach i
                           // we need to decrease once more by 1
            memcpy(fraction, &fraction[-1 * (*exponent)], strlen(fraction) - (-1 * (*exponent)));
            integer[0] = '1';
            integer[1] = 0;
        }
    }
}

/** @brief Converts the given number to floating point
 *
 *  This function uses the real number to iee754 algotithm to convert
 *  the number into floating point. It sets the sign bit, gets the
 *  exponent in 127 biased binary and finally the mantissa, then
 *  concatenates them to get the final result.
 *
 *  @param *number C string containing the number to convert
 *  @return The converted floating point number stored in a c string
 */
char *to_floating_point(char *number)
{
    char *frac_part;
    char *frac_part_final = (char *)calloc((FLOATING_POINT_SIGNIFICAND_DIGITS * 2) + 10,sizeof(char));
    char *int_part;
    int real_flag = FALSE;
    char sign_bit;
    char *result = (char *)calloc(FLOATING_POINT_MAX_DIGITS + 1,sizeof(char));
    int exponent = 0;
    char *stored_exponent = (char *)calloc(FLOATING_POINT_EXPONENT_DIGITS + 1,sizeof(char));

    if (number[0] == '-')
    {
        real_flag = is_real(&number[1]);
        sign_bit = '1';
    }
    else
    {
        real_flag = is_real(number);
        sign_bit = '0';
    }

    if (real_flag == TRUE)
    {
        int_part = get_integer_part(number);
        frac_part = get_fraction_part(number);

        int_part = get_magnitude_binary(int_part, FLOATING_POINT_MAX_DIGITS);
        frac_part_final = fraction_to_binary(frac_part, FLOATING_POINT_SIGNIFICAND_DIGITS * 2);
        free(frac_part);

        if (strlen(int_part) == 0)
        {
            int_part[0] = '0';
            int_part[1] = 0;
        }

        normalize(int_part, frac_part_final, &exponent);

        stored_exponent = int_to_biased_127(exponent);
        stored_exponent = extend_integer_binary_to_word_size(stored_exponent, FLOATING_POINT_EXPONENT_DIGITS);

        snprintf(result, FLOATING_POINT_MAX_DIGITS + 1, "%c%s%s", sign_bit, stored_exponent, frac_part_final);

        free(frac_part_final);
        free(stored_exponent);
        free(int_part);

        return result;
    }
    else
    {
        printf("\n Error can't convert input invalid \n");
        return NULL;
    }
}


/** @brief Finds the significand value for the given significand in floating point
 *
 *  This function use significand binary to double conversion algorithm to
 *  find the value of the significand and return it.
 *
 *  @param *sig C string containing the number to convert
 *  @return The converted result
 */
double get_significand_value(char *sig)
{
    if (is_significand(sig) == TRUE)
    {
        double num = 0;
        double total = 0;

        for (int i = 0; i < strlen(sig); i++)
        {
            num = (1 / pow(2, i + 1)) * (sig[i] - '0');
            total += num;
        }

        return total;
    }
    else
    {
        printf("\n Error can't convert input invalid \n");
        return 0.0;
    }
}


/** @brief Converts the given floating number to decimal
 *
 *  This function uses iee754 to real number algotithm to convert
 *  the number. It sets the sign, gets the exponent and finally the
 *  significand, then returns the result.
 *
 *  @param *number C string containing the number to convert
 *  @return The converted number stored in a c string
 */
char *from_floating_point(char *number)
{
    char *result_str = (char *)calloc(REAL_MAX_DIGITS + 1, sizeof(char));
    char *exponent = (char *)calloc(FLOATING_POINT_EXPONENT_DIGITS + 1, sizeof(char));
    char *significand = (char *)calloc(FLOATING_POINT_SIGNIFICAND_DIGITS + 1, sizeof(char));
    char *stored_exponent = (char *)calloc((FLOATING_POINT_EXPONENT_DIGITS + 1),sizeof(char));

    double result = 0.0;
    int exp_power = 0;

    if (is_floating_point(number) == TRUE)
    {
        memcpy(exponent, &number[1], FLOATING_POINT_EXPONENT_DIGITS);
        memcpy(significand, &number[FLOATING_POINT_EXPONENT_DIGITS + 1], FLOATING_POINT_SIGNIFICAND_DIGITS);
        exp_power = int_from_biased_127(exponent);
        result = get_significand_value(significand);
        result += 1;
        result *= pow(2, exp_power);
        sprintf(stored_exponent,"%d",exp_power);

        if (number[0] == '1')
        {
            result *= -1;
        }

        free(exponent);
        free(significand);
        free(stored_exponent);
        snprintf(result_str, REAL_MAX_DIGITS, "%f", result);

        return result_str;
    }
    else
    {
        printf("\n Error can't convert input invalid \n");
        return NULL;
    }
}

