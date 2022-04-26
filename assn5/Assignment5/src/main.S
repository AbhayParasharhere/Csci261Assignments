/**
* Name        : main.S
* Author      : Abhay Parashar, 658152558, S22N03, CSCI 261, VIU
* Version     : 1.0.0
* Description : Main function, the entry point of the program.
*/

		.data						// Define the data section
strindex:	.asciz "Enter a Fibonnaci Sequence Index (max 40) : "
			.align 3, 0
fibArray:	.skip	328, 0			// Define the array to store 41 integers and initialise them to 0
			.align 3, 0
index:		.long 0
			.align 3, 0
prevIndex:	.long 0
			.align 3,0
strOutput:	.asciz "\nYou Entered Fibonacci Sequence Index %d\n"
			.align 3, 0
dynOutput:	.asciz "\nUsing Dynamic Programming, Fibonnaci[%d] = %d\n"
			.align 3, 0
recOutput:	.asciz "\nUsing Recursive Function, Fibonnaci[%d] = %d\n"
			.align 3, 0
seqOutput:	.asciz "\nFibonacci sequence values for index 0 to %d:\n"
			.align 3, 0
strFormat:	.asciz "%d"


		.text						// Define the code section
		.global main

main:
		str lr,[sp, #-16]!			// Store the return address on stack
		ldr x0,=strindex			// Store x0 with the print format for asking the index
		bl printf					// Call the printf function

		ldr x0, =strFormat			// Store x0 with the format for storing the index
		ldr x1, =index				// Initialise x1 with the address of the label to store index
		bl scanf					// Call the scanf function

		ldr x0, =prevIndex			// Load x0 with the previous Index
		ldr x1, =index				// Load x1 with the index
		ldr x1, [x1]				// Load index value in x1
		str x1, [x0]				// Store index value in prevIndex

		ldr x0, =strOutput			// Store x0 with the print format for the output of entered index
		ldr x1, =index				// Load x1 with the index address
		ldr x1,[x1]					// Load index value in x1
		bl printf					// Call the printf function

		ldr x0, =index				// Load x0 with the index address
		ldr x0, [x0]				// Load x0 with the index value
		bl fibonacci_recursive		// Call the fibonacci_recursive function

		mov x2,x0					// Store the result from fibonacci_recursive function in x2
		ldr x1, =index				// Load x1 with the index address
		ldr x1, [x1]				// Load index value in x1
		ldr x0, =recOutput			// Load x0 with the print format to output recursion result
		bl printf					// Call the printf function

		ldr x1, =index				// Load x1 with the index address
		ldr x1, [x1]				// Load index value in x1
		cmp x1, #0					// If the index value is 0, then dont add 1 to x1 otherwise add 1
		bne addIndex				// Branch if not equal to 0 to addIndex

continue:

		ldr x0, =index				// Load x0 with the index address
		ldr x0, [x0]				// Load x0 with the index value
		bl fibonacci_dynamic		// Call the fibonacci_dynamic function

		mov x1,x0					// Move the index to x1
		ldr x0, =dynOutput			// Load x0 with the print format to output the result from fibonacci_dynamic function
		ldr x1, =prevIndex			// Load x1 with the address of index user entered
		ldr x1, [x1]				// Load x1 with the index value
		bl printf					// Call the printf function

		ldr x0, =seqOutput			// Load x0 with the print format to output the prompt that sequence is being printed
		ldr x1, =prevIndex			// Load x1 with the address of index user entered
		ldr x1, [x1]				// Load x1 with the index value
		bl printf					// Call the printf function

		ldr x0, =fibArray			// Load x0 with the array address
		ldr x1, =index				// Load x1 with the index address
		ldr x1, [x1]				// Load x1 with the value of the index
		bl fibonacci_sequence		// Call the fibonacci_sequence function


		ldr x0, =fibArray			// Load x0 with the array address
		ldr x1, =index				// Load x1 with the index address
		ldr x1, [x1]				// Load x1 with the value of the index
		bl show_fibonacci_seq		// Call the show_fibonacci_seq function

		mov x0,xzr					// Fill the x0 with 0
		ldr lr,[sp],#16				// Pop the return value from the function
		ret lr						// Return from the function

addIndex:
		add x1,x1,#1				// Add 1 to index
		ldr x2,=index				// Store the address of index to x2
		str x1,[x2]					// Update the index label with index + 1
		b continue					// Continue the execution of the program
