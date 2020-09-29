/* ----------------------------------------------------------------------
Program file: caramkp5.c
Author: 	Keith Caram
Emial: 		Keith_Caram@student.uml.edu
Date: 		April 4, 2020
Assignment: program #5 
Course #: 	INFO 2120.061 
Objective:	This program will promt the user for a file to read a list of employee
			first names, last names, ID numbers, and salaries from. It will then ask
			the user which kind of data they would like to sort their employees
			by. The program will then sort the data according to the user input, and
			then it will print the sorted data to an output screen and to a file
			called report5.txt
------------------------------------------------------------------------ */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

/* begin main */
main()
{
	/* Declare Structure Prototypes */
	/* ---------------------------- */
	
	struct emp
	{
		int 	id_num; /* employee number */
		char 	first_name[20]; /* employee first name */
		char 	last_name[30]; /* employee last name */
		float 	salary; /* employee salary */
	};/* end struct */
	
	struct name
	{
		char	full_name[50]; /* struct to store all concatanated full names */
	};/* end struct */
	
	/* Variable Declaration */
	/* -------------------- */
	
	struct emp		records[100], temp;
	struct name		rec_name[100];
	
	int		i, x; /* loop control variables */
	int		count = 0; /* count number of employees */
	int		sort = -1; /* sort/switch control variable */
	FILE	*in_file_ptr, *out_file_ptr; /* set up file pointers */
	char	file_name[80] = "n7.txt";
	char 	c, sort_type;
	
	/* Time Variables and Structures */
	/* ----------------------------- */
	
	char			date_and_time[25];	
	time_t			rawtime;
	struct tm		*timeptr;
	
	/* Prompt user to enter file name */
	printf("Welcome to Employee Center\n\n");
	printf("Enter File Name: ");
	scanf("%79[^\n]", file_name);
	while ( (c = getchar() != '\n') && c != EOF); /* clear input buffer */
	
	/* Open read file and if it doesn't exist print error message */
	in_file_ptr = fopen (file_name, "r");
	
	if ( in_file_ptr == NULL)
	{
		printf("\nCannot open file %s for reading.\n", file_name);
		return 1;
	}/* end if */
	
	/* Open file to write to and if it is read only print error message */	
	out_file_ptr = fopen ("report5.txt", "w");
	
	if ( out_file_ptr == NULL)
	{
		printf("\nCannot open file report5.txt for writing.\n");
		return 1;
	}/* end if */
	
	/* Copy all elements of the read file into our 'records' struct */
	for( i = 0; !feof(in_file_ptr) && i < 100; i++)
	{
		fscanf (in_file_ptr, "%i\n", &records[i].id_num);
		fscanf (in_file_ptr, "%[^\n]\n", &records[i].first_name);
		fscanf (in_file_ptr, "%[^\n]\n", &records[i].last_name);
		fscanf (in_file_ptr, "%f", &records[i].salary);
		
		count++;/* count number of elements in 'records' struct */
		
		fgetc (in_file_ptr);/* look at where file ptr is to see if it is at EOF */
		
	}/* end for */
	
	/* Set up Time Display for write and cmd prompt output */
	time  (&rawtime);
	timeptr = localtime(&rawtime);
	strncpy(date_and_time, asctime(timeptr),24);
	date_and_time[24] = '\n';
	
	/* Let user know how many employees were entered into our 'records' struct */
	printf("\n %i employees", count);

	/* Start do while to decide which value the 'records' struct will be sorted by */
	do
	{
		printf("\n\nSort by Number(N), Name(A), or Balance(B): ");
		scanf("%c", &sort_type);
		while ( (c = getchar() != '\n') && c != EOF); /* clear input buffer */
		
		if(toupper(sort_type) == 'A')
			sort = 1;/* end if */
			
		if(toupper(sort_type) == 'N')
			sort = 2;/* end if */
				
		if(toupper(sort_type) == 'B')
			sort = 3;/* end if */
			
		if(sort == -1)
			printf("\nInvalid Entry");/* end if */
			
	}while(sort == -1);/* end do while */
	
	/* Start switch statement based on the type of sort chosen by user */
	switch(sort)
	{
		/* If user chooses to sort by Name */
		case 1:
		
			for (i = 1; i < count; i++)
			{
				for (x = 0; x < count - i; x++) 
				{
  					if (strcmp(records[x].last_name, records[x + 1].last_name) > 0) 
					{
 						temp = records[x];
   						records[x] = records[x + 1];
   						records[x + 1] = temp;
   						
     				}/* end if */   
					  			
   				}/* end for */   
				   			
			}/* end for */
			
			break;/* end case 0 */

		/* If user chooses to sort by Number */
		case 2:
	
			for (i = 1; i < count; i++)
			{
				for (x = 0; x < count - i; x++) 
 				{
         			if (records[x].id_num < records[x + 1].id_num) 
 					{
            			temp = records[x];
            			records[x] = records[x + 1];
            			records[x + 1] = temp;
            			
         			}/* end if */
					 	
      			}/* end for */	
      			
			}/* end for */
			
			break;/* end case 1 */
	
		/* If user chooses to sort by Balance */
		case 3:	
			for (i = 1; i < count; i++)
			{
				for (x = 0; x < count - i; x++) 
				{
  					if (records[x].salary < records[x + 1].salary) 
	 				{
            			temp = records[x];
            			records[x] = records[x + 1];
           				records[x + 1] = temp;
           				
   					}/* end if */
					   	
   				}/* end for */   	
				   		
			}/* end for */	
				
			break;/* end case 2 */
		
		/* Just in case there is an error I didn't program around */	
		default:
			printf("Unexpected Error");
			return 0;
						
	}/* end switch */
	
	/* Begin Print and Write to File */
	/* ----------------------------- */
	
	/* Print Header */
	printf("\n\n    Employee Salary Report %s\n", date_and_time);
	printf("  Employee\n  No.     Name			      	  Salary\n\n");
	
	/* Print Header to output file */
	fprintf(out_file_ptr, "\n\n    Employee Salary Report %s\n", date_and_time);
	fprintf(out_file_ptr, "  Employee\n  No.      Name			      	  Salary\n\n");
	
	/* Start for loop to print all sorted data in the output screen and write to output file*/
	for( i = 0; i < count; i++)
	{
		/* Concatenate first and last name, and store in the full_name struct */
		strcat(rec_name[i].full_name, records[i].last_name);
		strcat(rec_name[i].full_name, ", ");
		strcat(rec_name[i].full_name, records[i].first_name);
		
		/* Print in file */
		fprintf(out_file_ptr, "  %-5i ", records[i].id_num);
		fprintf(out_file_ptr, "  %-30s", rec_name[i].full_name);
		fprintf(out_file_ptr, "  %.2f\n", records[i].salary);
		
		/* Print to output screen */
		printf("  %-5i ", records[i].id_num);
		printf("  %-30s", rec_name[i].full_name);
		printf("  %.2f\n", records[i].salary);
		
	}/* end for */
	
	/* close read and write files */
	fclose(in_file_ptr);
	fclose(out_file_ptr);
	
	/* Display message to user that the write has been successful */
	printf("\n(Report has been sent to report5.txt)\n");
	printf("\nThank you for using the program.\n\n");
	
}/* end main */

