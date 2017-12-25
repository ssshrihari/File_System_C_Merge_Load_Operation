#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "queryprocessor.h"
struct student_info_data{
	int rolno;
	char phone[50];
	char address[100];
	char city[50];
	long int pincode;
};
struct marks_database{
	int rolno;
	char name[50];
	int m1, m2, m3, m4;
	float avg;
	int grade;
};
static int reciveing_marks_lines = 0;
static int reci = 0;
static int marks_record_index = 1;
static int info_record_index = 1;

struct marks_database *info = (struct marks_database*)malloc(sizeof(struct marks_database) * 11);
struct student_info_data *input = (struct student_info_data*)malloc(sizeof(struct student_info_data) * 11);
char query_string[30];


int check(char *token, int size, int curr,int option)
{
	if (option==1)
	for (int index = 1; index <= size; index++)
		if (info[index].rolno == atoi(token))
		{
			return index;
		}
	if (option==2)
		for (int index = 1; index <= size; index++)
			if (input[index].rolno == atoi(token))
			{
				return index;
			}

	return 0;
}
void load_file()
{
	int option, m = 0;
	printf("*******************************************************************************\n\n");
	printf("\n \t\t\tENTER YOUR OPTION \n\t\t\t1.LOAD STUDENT MARKS FILE \n\t\t\t2.LOAD STUDENT INFO FILES\n\t\t\t\n\n\n");
	printf("*******************************************************************************\n\n\t\t\t");
	scanf("%d", &option);
	FILE* fptr;
	char *token, c;
	if (option == 1)
	{
		char line[1024];
		int n = 6, h = 1, i = 0;
		reciveing_marks_lines = 0;
		int b = 0;
		int nex_file;
		char filename[100];
		printf("*******************************************************************************\n\n");
		printf("\n \t\t\tENTER THE FILE NAME\n\t\t\t\n\n\n");
		printf("*******************************************************************************\n\n\t\t\t");
		scanf("%s", filename);
		fptr = fopen(filename, "r");
		if (fptr==NULL)
		{
			perror("\n\t\tHEY I GUESS YOU MISSED SOMETHING THERE IS NO SUCH FILE!!");
			getchar();
			exit(1);
		}
		for (c = getc(fptr); c != EOF; c = getc(fptr))
		{
			if (c == '\n')
				reciveing_marks_lines++;
		}
		if (marks_record_index > 3)
		{
			marks_record_index = marks_record_index + reciveing_marks_lines;
			(struct marks_database*)realloc(info, sizeof(struct marks_database) * marks_record_index);
		}
		fclose(fptr);
		fptr = fopen(filename, "r");
		i = marks_record_index;
		int x;
		int opt;
		while (fgets(line, 1024, fptr) && i <= (marks_record_index + reciveing_marks_lines - 1))
		{
			char *tok;
			int opt;
			tok = strtok(line, ",");
			m = check(tok, marks_record_index, i,option);
			if (marks_record_index > 5 && b == 0)
			{
				printf("*******************************************************************************\n\n");
				printf("\n \t\t\tDUPLICATE FOUND DO U WANT ME TO \n \t\t\t 1.UPDATE \n\t\t\t2.DROP\n\t\t\t\n\n\n");
				printf("*******************************************************************************\n\n\t\t\t");
				scanf("%d", &opt);
				b = 1;
			}
			if (m != 0)
			{
				if (opt == 1)
				{
					info[m].rolno = atoi(tok);
					tok = strtok(0, ",");
					strcpy(info[m].name, tok);
					tok = strtok(0, ",");
					info[m].m1 = atoi(tok);
					tok = strtok(0, ",");
					info[m].m2 = atoi(tok);
					tok = strtok(0, ",");
					info[m].m3 = atoi(tok);
					tok = strtok(0, ",");
					info[m].m4 = atoi(tok);
					info[m].avg = 0;
					info[m].grade = 0;
				}
			}
			else
			{
				info[i].rolno = atoi(tok);
				tok = strtok(0, ",");
				strcpy(info[i].name, tok);
				tok = strtok(0, ",");
				info[i].m1 = atoi(tok);
				tok = strtok(0, ",");
				info[i].m2 = atoi(tok);
				tok = strtok(0, ",");
				info[i].m3 = atoi(tok);
				tok = strtok(0, ",");
				info[i].m4 = atoi(tok);
				i++;
			}
		}
		marks_record_index = i;
		for (int i = 1; i < (marks_record_index); i++)
		{
			printf("%d\t", info[i].rolno);
			printf("%s\t\t", info[i].name);
			printf("%d\t", info[i].m1);
			printf("%d\t", info[i].m2);
			printf("%d\t", info[i].m3);
			printf("%d\n", info[i].m4);
		}
		
	}
	if (option == 2)
	{
		char filename[50];
		printf("*******************************************************************************\n\n");
		printf("\n \t\tENTER THE FILE NAME\n\t\t\t\n\n\n");
		printf("*******************************************************************************\n\n\t\t\t\n");
		scanf("%s", filename);
		fptr = fopen(filename, "r");
		if (fptr==NULL)
		{

			perror("\n\t\t\tHEY I GUESS YOU MISSED SOMETHING THERE IS NO SUCH FILE!!");
			getchar();
			exit(1);
		}
		int n = 6, h = 1, i = 0;
		int b = 0;
		reci = 0;
		for (c = getc(fptr); c != EOF; c = getc(fptr))
		{
			if (c == '\n')
				reci++;
		}
		if (info_record_index > 9)
		{
			(struct student_info_data*)realloc(input, sizeof(struct student_info_data) * info_record_index);
		}
		char line[1024];
		i = info_record_index;
		fclose(fptr);
		fptr = fopen(filename, "r");
		while (fgets(line, 1024, fptr) && i <= (info_record_index + reci - 1))
		{
			char *tok;
			int opt;
			tok = strtok(line, ",");
			m = check(tok, info_record_index, i,option);
			if (info_record_index > 8 && b == 0)
			{
				printf("*******************************************************************************\n\n");
				printf("\n \t\t\tDUPLICATE FOUND DO U WANT ME TO \n \t\t\t 1.UPDATE \n\t\t\t2.DROP\n\t\t\t\n\n\n");
				printf("*******************************************************************************\n\n\t\t\t");
				scanf("%d", &opt);
				b = 1;
			}
			if (m != 0)
			{

				if (opt == 1)
				{
					info[m].rolno = atoi(tok);
					tok = strtok(0, ",");
					strcpy(input[m].phone, tok);
					tok = strtok(0, ",");
					strcpy(input[m].address, tok);
					tok = strtok(0, ",");
					strcpy(input[m].city, tok);
					tok = strtok(0, ",");
					input[m].pincode = atoi(tok);
				}

			}
			else
			{
				input[i].rolno = atoi(tok);
				tok = strtok(0, ",");
				strcpy(input[i].phone, tok);
				tok = strtok(0, ",");
				strcpy(input[i].address, tok);
				tok = strtok(0, ",");
				strcpy(input[i].city, tok);
				tok = strtok(0, ",");
				input[i].pincode = atoi(tok);
				i++;
			}
		}
		info_record_index = i;
		for (int i = 1; i < (info_record_index); i++)
		{
			printf("%d\t", input[i].rolno);
			printf("%s\t\t", input[i].phone);
			printf("%s\t", input[i].address);
			printf("%s\t", input[i].city);
			printf("%ld\n", input[i].pincode);
		}
	}

	getchar();
}
void compute_result()
{
	if (marks_record_index == 1)
	{
		printf("*******************************************************************************\n\n");
		printf("\n \t\t\t NO FILE LOADED\n\t\t\t\n\n\n");
		printf("*******************************************************************************\n\n\t\t\t");
	}
	else
	{
		int m1sum = 0, m2sum = 0, m3sum = 0, m4sum = 0;
		int i;
		for (i = 1; i <= (marks_record_index ); i++)
		{
			m1sum = m1sum + info[i].m1;
			m2sum = m2sum + info[i].m2;
			m3sum = m3sum + info[i].m3;
			m4sum = m4sum + info[i].m4;
			info[i].avg = (info[i].m1 + info[i].m2 + info[i].m3 + info[i].m4) / 4.0;
		}
		for (i = 1; i <= (marks_record_index); i++)
		{
			if (info[i].avg >= 91)
				info[i].grade = 10;
			else if (info[i].avg >= 81)
				info[i].grade = 9;
			else if (info[i].avg >= 71)
				info[i].grade = 8;
			else if (info[i].avg >= 61)
				info[i].grade = 7;
			else if (info[i].avg >= 51)
				info[i].grade = 6;
			else if (info[i].avg >= 41)
				info[i].grade = 5;
			else if (info[i].avg >= 31)
				info[i].grade = 4;
			else if (info[i].avg >= 21)
				info[i].grade = 3;
			else if (info[i].avg >= 11)
				info[i].grade = 2;
			else if (info[i].avg >= 1)
				info[i].grade = 1;
		}
		m1sum = m1sum / 200.0;
		m2sum = m2sum / 200.0;
		m3sum = m3sum / 200.0;
		m4sum = m4sum / 200.0;
		printf("*******************************************************************************\n\n");
		printf("\n \t\t\tCOMPUTATION SUCCEFULLY COMPLETED\n\t\t\t\n\n\n");
		printf("*******************************************************************************\n\n\t\t\t");
	}
	getchar();
	
}
void join()
{

	if (marks_record_index == 1 && reci == 1)
	{
		printf("*******************************************************************************\n\n");
		printf("\n \t\t\t NO FILE LOADED\n\t\t\t\n\n\n");
		printf("*******************************************************************************\n\n\t\t\t");
	}
	else
	{
		int i, j, c = 0;
		for (i = 1; i < (marks_record_index); i++)
		{
			c = 0;
			for (j = 1; j < (info_record_index); j++)
			{
				if (info[i].rolno == input[j].rolno)
				{
					printf("\n%d\t", info[i].rolno);
					printf("%s\t\t", info[i].name);
					printf("%d\t", info[i].m1);
					printf("%d\t", info[i].m2);
					printf("%d\t", info[i].m3);
					printf("%d\t", info[i].m4);
					printf("%f\t", info[i].avg);
					printf("%d\t", info[i].grade);
					printf("%s\t", input[j].phone);
					printf("%s\t\t", input[j].address);
					printf("%s\t\t", input[j].city);
					printf("%ld\n", input[j].pincode);
					c++;
				}
			}
			if (c == 0)
			{
				printf("\n%d\t", info[i].rolno);
				printf("%s\t\t", info[i].name);
				printf("%d\t", info[i].m1);
				printf("%d\t", info[i].m2);
				printf("%d\t", info[i].m3);
				printf("%d\t", info[i].m4);
				printf("%f\t", info[i].avg);
				printf("%d\t", info[i].grade);
				printf("NULL\t\t ");
				printf("NULL\t\t ");
				printf("NULL\t\t ");
				printf("NULL\n ");
			}
		}
	}
	getchar();
}
void save_progress()
{
	if (marks_record_index == 1 && reci == 1)
	{
		printf("*******************************************************************************\n\n");
		printf("\n \t\t\t NO FILE LOADED\n\t\t\t\n\n\n");
		printf("*******************************************************************************\n\n\t\t\t");
	}
	else
	{
		int n;
		printf("Enter your choice\n1.MarkList File\n2.StudentInfo File\n");
		scanf("%d", &n);
		if (n == 1)
		{
			
			FILE *f1;
			f1 = fopen("C:\\Users\\Shrihari\\Documents\\Visual Studio 2013\\Projects\\ConsoleApplication4\\ConsoleApplication4\\savemarks.txt", "w+");
			int r, a, b, c, d;
			char str[1000];
			int g;
			float av;
			for (int i = 1; i < marks_record_index; i++)
			{
				a = info[i].m1;
				b = info[i].m2;
				c = info[i].m3;
				d = info[i].m4;
				strcpy(str, info[i].name);
				r = info[i].rolno;
				g = info[i].grade;
				av = info[i].avg;
				fprintf(f1, "%d ", r);
				fprintf(f1, "%s ", str);
				fprintf(f1, "%d ", a);
				fprintf(f1, "%d ", b);
				fprintf(f1, "%d ", c);
				fprintf(f1, "%d ", d);
				if (av < 0)
					av = 0;

				fprintf(f1, "%.2f ", av);
				if (g < 0)
					g = 0;
				fprintf(f1, "%d\n", g);
			}
			fclose(f1);
		}
		else if (n == 2)
		{
			FILE *f2;
			f2 = fopen("C:\\Users\\Shrihari\\Documents\\Visual Studio 2013\\Projects\\ConsoleApplication4\\ConsoleApplication4\\saveinfo.txt", "w+");
			int r;
			long int pin;
			char p[100], add[1000], ci[100];
			for (int i = 1; i < info_record_index; i++)
			{
				r = input[i].rolno;
				pin = input[i].pincode;
				strcpy(p, input[i].phone);
				strcpy(add, input[i].address);
				strcpy(ci, input[i].city);
				fprintf(f2, "%d ", r);
				fprintf(f2, "%s ", p);
				fprintf(f2, "%s ", add);
				fprintf(f2, "%s ", ci);
				fprintf(f2, "%ld\n ", pin);
			}
			fclose(f2);
			
		}
		printf("*******************************************************************************\n\n");
		printf("\n \t\t\tSAVE PROGRESS COMPLETED\n\t\t\t\n\n\n");
		printf("*******************************************************************************\n\n\t\t\t");
	}
	getchar();
}
void display(int i)
{
	printf("%d\t", info[i].rolno);
	printf("%s\t", info[i].name);
	printf("%d\t", info[i].m1);
	printf("%d\t", info[i].m2);
	printf("%d\t", info[i].m3);
	printf("%d\t", info[i].m4);
	printf("%f\t", info[i].avg);
	printf("%d\n ", info[i].grade);
}
void query()
{
	if (marks_record_index == 1&&reci==1)
	{
		printf("*******************************************************************************\n\n");
		printf("\n \t\t\t NO FILE LOADED\n\t\t\t\n\n\n");
		printf("*******************************************************************************\n\n\t\t\t");
	}
	else
	{
			char value[100];
			char h[10];
			int i, j;
			char *tok;
			char con[100];
			char colname[100], table[100];
			printf("Enter the query\n");
			scanf("%s",query_string);
			//send_to_tokenizer(query_string);
		
			printf("enter the COLUMN and CONDITION and VALUE\n");
			scanf("%s %s %s", h, con, value);
			for (i = 1; i <= (marks_record_index + 10); i++)
			{
				if (strcmp(h, "m1") == 0 && strcmp(con, "contains") != 0)
				{
					if (strcmp(con, "LT") == 0)
					{
						if (info[i].m1 < atoi(value))
						{
							display(i);
						}
					}
					else if (strcmp(con, "EQ") == 0)
					{
						if (info[i].m1 == atoi(value))
						{
							display(i);
						}
					}
					else if (strcmp(con, "GT") == 0)
					{
						if (info[i].m1 > atoi(value))
						{
							display(i);
						}
					}
					else if (strcmp(con, "LE") == 0)
					{
						if (info[i].m1 <= atoi(value))
						{
							display(i);
						}
					}
					if (strcmp(con, "GE") == 0)
					{
						if (info[i].m1 >= atoi(value))
						{
							display(i);
						}
					}
				}
				else if (strcmp(h, "m2") == 0 && strcmp(con, "contains") != 0)
				{
					if (strcmp(con, "LT") == 0)
					{
						if (info[i].m2 < atoi(value))
						{
							display(i);
						}
					}
					else if (strcmp(con, "EQ") == 0)
					{
						if (info[i].m2 == atoi(value))
						{
							display(i);
						}
					}
					else if (strcmp(con, "GT") == 0)
					{
						if (info[i].m2 > atoi(value))
						{
							display(i);
						}
					}
					else if (strcmp(con, "LE") == 0)
					{
						if (info[i].m2 <= atoi(value))
						{
							display(i);
						}
					}
					if (strcmp(con, "GE") == 0)
					{
						if (info[i].m2 >= atoi(value))
						{
							display(i);
						}
					}
				}
				else if (strcmp(h, "m3") == 0 && strcmp(con, "contains") != 0)
				{
					if (strcmp(con, "LT") == 0)
					{
						if (info[i].m3 < atoi(value))
						{
							display(i);
						}
					}
					else if (strcmp(con, "EQ") == 0)
					{
						if (info[i].m3 == atoi(value))
						{
							display(i);
						}
					}
					else if (strcmp(con, "GT") == 0)
					{
						if (info[i].m3 > atoi(value))
						{
							display(i);
						}
					}
					else if (strcmp(con, "LE") == 0)
					{
						if (info[i].m4 <= atoi(value))
						{
							display(i);
						}
					}
					else if (strcmp(con, "GE") == 0)
					{
						if (info[i].m4 >= atoi(value))
						{
							display(i);
						}
					}
				}
				else if (strcmp(h, "m4") == 0 && strcmp(con, "contains") != 0)
				{
					if (strcmp(con, "LT") == 0)
					{
						if (info[i].m4 < atoi(value))
						{
							display(i);
						}
					}
					else if (strcmp(con, "EQ") == 0)
					{
						if (info[i].m4 == atoi(value))
						{
							display(i);
						}
					}
					else if (strcmp(con, "GT") == 0)
					{
						if (info[i].m4 > atoi(value))
						{
							display(i);
						}
					}
					else if (strcmp(con, "LE") == 0)
					{
						if (info[i].m4 <= atoi(value))
						{
							display(i);
						}
					}
					if (strcmp(con, "GE") == 0)
					{
						if (info[i].m4 >= atoi(value))
						{
							display(i);
						}
					}
				}
				else if (strcmp(h, "name") == 0)
				{
					if (strcmp(con, "contains") == 0)
					{
						if (strcmp(info[i].name, value) == 0)
							display(i);
					}
					else if (strcmp(con, "startswith") == 0)
					{
						if (info[i].name[0] == value[0])
							display(i);
					}
				}
				else if (strcmp(h, "m1") == 0 && strcmp(con, "contains") == 0)
				{
					if (info[i].m1 == atoi(value))
						display(i);
				}
				else if (strcmp(h, "m2") == 0 && strcmp(con, "contains") == 0)
				{
					if (info[i].m2 == atoi(value))
						display(i);
				}
				else if (strcmp(h, "m3") == 0 && strcmp(con, "contains") == 0)
				{
					if (info[i].m3 == atoi(value))
						display(i);
				}
				else if (strcmp(h, "m4") == 0 && strcmp(con, "contains") == 0)
				{
					if (info[i].m4 == atoi(value))
						display(i);
				}
			}
		}
	}
		getchar();

}
void menu()
{
	int option;
	do
	{
		printf("*******************************************************************************\n\n");
		printf("\n \t\t\tENTER YOUR OPTION \n\t\t\t1.LOAD FILE \n\t\t\t2.COMPUTE AVG AND GRADE\n\t\t\t3.SAVE CURRENT FILE\n\t\t\t4.JOIN TWO DATA SETS\n\t\t\t5.QUERY ON FILE\n\t\t\t6.EXIT\n\n\n");
		printf("*******************************************************************************\n\n\t\t\t");
			scanf_s("%d", &option);
		switch (option)
		{
		case 1:
			load_file();
			break;
		case 2:
		{
			compute_result();
			break;
		}
		case 3:
			save_progress();
			break;
		case 4:
			join();
			break;
		case 5:query();
			break;
		case 6:break;
		}
		getchar();
		system("cls");
	} while (option != 6);
}
int main()
{
	menu();
	getchar();
	return 0;
}


