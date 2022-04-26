/**
* Name        : fibonacci_dynamic.S
* Author      : Abhay Parashar, 658152558, S22N03, CSCI 261, VIU
* Version     : 1.0.0
* Description : int fibonacci_dynamic(int fib_index) function,
* 		Accepts an index of fibonacci sequence (there is max limit
*		of the index) and computes the fibonacci sequence value of the
*		index using dynamic programming		
*/

		.text			// Define the code section
		.global fibonacci_dynamic

fibonacci_dynamic:
		cmp x0,#0		// x0 contains index, compare index with 0
		beq base0		// If index is 0, branch to base0 case
		cmp x0,#1		// x0 contains index, compare index with 1
		beq base1		// If index is 1, branch to base1 case
        mov x1,#0  		// Now, set initial values for x1,x2,x3,x4. Initialise x1 with 0
        mov x2,#1  		// Initialise x2 with 1
        mov x3,#0  		// Initialise x3 with 0
        mov x4,#2  		// Initialise x4 with 2

loop:
		cmp x4, x0		// x4 acts as the loop counter, compare with x0
		beq end			// if x4 is equal to x0, branch to end

		add x3, x1, x2	// x3 = x1 + x2
		mov x1, x2		// put x2 in x1
		mov x2, x3		// put x3 in x2

		add x4, x4, #1	// add 1 to x4 which is loop counter
		b loop			// branch to loop again

end:
		mov x0, x3		// put result stored in x3 in x0
		ret lr			// return from the function

base0:
		mov x0,#0		// put 0 in x0 or result
		ret lr			// return from the function

base1:
	   mov x0,#1		// put 0 in x0 or result
	   ret lr			// return from the function
