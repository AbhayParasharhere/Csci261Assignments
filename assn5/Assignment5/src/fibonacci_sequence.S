/**
* Name        : fibonacci_sequence.S
* Author      : Abhay Parashar, 658152558, S22N03, CSCI 261, VIU
* Version     : 1.0.0
* Description : void fibonacci_sequence(int fibonacci_seq[], int max_index) function,
* 		Accepts an array to place fibonacci sequence values and a max index
*		of the array as its paramters.
*		Computes all the fibonacci sequence values for index 0 to max_index and
*		places the sequence values at appropriate position into the array.
*/

		.text					// Define the code section
		.global fibonacci_sequence

fibonacci_sequence:
		mov x5,x0				// x5 for array base address, move x0 to x5
		mov x0,x1				// x0 for index, move x1 to x0
		cmp x0,#0				// Compare index with 0, if 0 then its a base 0 case
		beq base0				// Branch to base 0 case
		cmp x0,#1				// Compare index with 1, if 1 then its a base 1 case
		beq base1				// Branch to base 1 case
        mov x1,#0  				// Initialise x1 with 0, x1 stores the first value
        mov x2,#1  				// Initialise x2 with 1, x2 stores the second value
        mov x3,#0				// Initialise x3 with 0, x2 stores the second value
        mov x4,#2  				// Initialise x4 with 2, x4 for loop counter

loop:
		cmp x4, x0				// If loop counter is 0 , branch to end
		beq end					// branch to end

		add x3, x1, x2			// sum = first + second
		mov x1, x2				// first = second
		mov x2, x3				// second = sum

		str x3,[x5, x4, lsl#3]	// Store the value of sum in array at index x4

		add x4, x4, #1			// Increment the loop counter
		b loop					// branch to loop again

end:

		mov x0,#0				// initialise arr[0] = 0
		str x0, [x5]			// store in array[0]
		add x5,x5,#8			// move to arr[1]

	    mov x0,#1				// store 1 in x0, so that
		str x0, [x5]			// arr[1] = 1

		mov x0, x3				// move the value of sum in x0
		ret lr					// return from the function

base0:
		mov x0,#0				// store 0 in x0 register
		str x0, [x5]			// array[0] = 0
		ret lr					// return from the function

base1:
		mov x0,#0				// store 0 in x0 register
		str x0, [x5]			// array[0] = 0
		add x5,x5,#8			// move to next element in array

	    mov x0,#1				// store 1 in x0 register
		str x0, [x5]			// array[1] = 1

	    ret lr					// return from the function
