#include <stdio.h>

extern FILE* out;

void printUseage()
{
	fprintf(out, 
	"\nsocial_network [-i]|[-f input_file output_file] [-h]\n\n-i : To run the program interactively and read the commands from the command-line and output back to the command-line. All error messages are also reported to the command-line.\n\n-f input_file output_file : To read the program command inputs from input_file and output the results to the output_file. All error messages are also reported in the output_file. Make sure that if the user is using this switch, he is providing names for input_file and output_file. Only one of –i or –f switch should be provided. If both are provided –i takes precedence over –f and the program will behave interactively.\n\n-h : Prints the usage information. The usage information includes the commands supported by the program (a one line description and usage information) and the switch arguments.\n\nCOMMANDS:\n\nexit_program\n\n");

}

