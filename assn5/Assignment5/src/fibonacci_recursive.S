/**
* Name        : fibonacci_recursive.S
* Author      : Abhay Parashar, 658152558, S22N03, CSCI 261, VIU
* Version     : 1.0.0
* Description : int fibonacci_recursive(int fib_index) function,
* 		Accepts an index of fibonacci sequence (there is max limit
*		of the index) and computes the fibonacci sequence value of the
*		index using recursive function call
*/


		.text						// Define the code section
		.global fibonacci_recursive

fibonacci_recursive:
		sub sp, sp, #32				// Adjust the stack pointer to hold return address, current index value, and the temporary results

		str lr, [sp,#24]			// Save the return address at sp + 24
		str x0, [sp, #16]			// Save the index at stack on sp + 16
		cmp x0, #0					// Compare the index value with zero.
		beq base					// If the index value is equal to zero, it's a base case branch to base case
		cmp x0, #1					// Compare the index value with one
		beq base					// If the index value is equal to one, it's a base case, follow through otherwise its a recursive case

recur:

		ldr x1, [sp, #16]			// Retrieve the index in x1
		sub x1, x1, #1				// index = index - 1
		mov x0, x1					// Pass x1 to ARM register x0.
		bl fibonacci_recursive		// Recursively call the function with the decremented index
		str x0,[sp]					// Save the result of the recursive call return at sp + 0

		ldr x1, [sp, #16]			// Retrive the current index value from the stack into an ARM register again
		sub x1, x1, #2				// Decrement the index value by 2
		mov x0, x1					// Pass x1 into ARM register x0.
		bl fibonacci_recursive		// Recursively call the function again with the decremented index

		ldr x2, [sp]				// Retrive the previously saved result from the stack into ARM register x2
		add x0 , x0 , x2			// Add previous 2 results into x0
		str x0, [sp]				// Save x0 at stack + 0

		b end						// Branch to the end of the function


base:
		str x0, [sp]				// For the base case, fibonacci sequence value is equal to its index value, store result at sp + 0
		b end						// Branch to the end of the function in order to return from the current call with the return value


end:
		ldr x0, [sp]				// Retrive the fibonacci sequence value of the current index from stack into ARM register x0
		ldr lr, [sp, #24]			// Retrieve the return address from the stack
		add sp, sp, #32				// Adjust the stack pointer to its original address before this function was called

		ret lr						// Return from the function



