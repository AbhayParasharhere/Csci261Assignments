/**
* Name        : show_fibonacci_seq.S
* Author      : Abhay Parashar, 658152558, S22N03, CSCI 261, VIU
* Version     : 1.0.0
* Description : void show_fibonacci_seq(int fibonacci_seq[], int max_index) function,
* 		Accepts an array of fibonacci sequence values and the max index
*		of the array as its paramters and prints the values from the array
*		on the screen.
*/

		.data					// Define the data section
strPrint:	.asciz	"\nfib[%d] = %d\n"

		.text					// Define the code section
		.global show_fibonacci_seq

show_fibonacci_seq:
		str lr, [sp,#-16]!		// Save the return address onto stack
		cmp x1, #0				// Use x1 as the loop counter
		beq base0				// if x1 is 0 branch to base 0 case
		mov x3, x0				// Array address has been passed through x0, copy it to x3
		mov x4, x1				// Max index has been passed through x1, copy it to x4
		mov x1, #0				// Initialise x1 to zero

loop:
		cmp x1, x4				// Compare loop counter value x1 with the max index value x4
		beq end					// End the loop if they are equal by branching to the end of the function

		ldr x0, =strPrint		// Assign the address of the formatted string to x0 to pass it to printf function

		ldr x2, [x3, x1, lsl#3]	// Assign x2 the fibonacci sequence value pointed by index x1 from the array

		str x1, [sp, #-16]!		// Save current index value in x1 onto stack before calling printf function
		str x3, [sp, #-16]!		// Save the address of fibonacci sequence array (in x3) onto stack before calling printf function
		str x4, [sp, #-16]!		// Save fibonacci sequence array max index (in x4) onto stack before calling printf function

		bl printf				// Call printf() function

		ldr x4, [sp], #16		// Retrive fibonacci sequence array index limit from the stack into x4
		ldr x3, [sp], #16		// Retrive the address fibonacci sequence array from the stack into x3
		ldr x1, [sp], #16		// Retrive current loop counter value from the stack into x1

		add x1, x1, #1			// Increment the loop counter
		b loop					// Branch to the beginning of the loop

end:
		ldr lr, [sp], #16		//Retrieve the return address from the stack
		ret lr					//Return from the function

base0:
		ldr x0, =strPrint		// Assign the address of the formatted string to x0 to pass it to printf function
		mov x1, #0				// Fill x1 with 0
		mov x2, #0				// Fill x1 with 0
		bl printf				// Call printf() function
		b end					// branch to end



