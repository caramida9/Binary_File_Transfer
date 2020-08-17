#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Person.h"

FILE *config_file, *input, *output;

void create_input_file()
{
	PersonTmpl person;
	FILE* temp;
	temp = fopen("Person.dat", "wb");
	scanf("%d", &person.nPersonID);
	while (!feof(stdin) && person.nPersonID != -1)
	{
		scanf(" %c", &person.chRecordType);
		if (person.chRecordType == '1')
		{
			gets_s(person.Details.PersonalInfo.sFirstName, 30);
			gets_s(person.Details.PersonalInfo.sLastName, 30);
			gets_s(person.Details.PersonalInfo.sBirthdate, 10);
			scanf("%d", &person.Details.PersonalInfo.theGender);
		}
		else if (person.chRecordType == '2')
		{
			gets_s(person.Details.HomeDetails.homeAddress.sStreet, 30);
			gets_s(person.Details.HomeDetails.homeAddress.sCity, 30);
			gets_s(person.Details.HomeDetails.homeAddress.sCountry, 30);
			gets_s(person.Details.HomeDetails.sPhone, 15);
			gets_s(person.Details.HomeDetails.sEmail, 30);
		}
		else if (person.chRecordType == '3')
		{
			gets_s(person.Details.WorkDetails.sCompany, 30);
			gets_s(person.Details.WorkDetails.workAddress.sStreet, 30);
			gets_s(person.Details.WorkDetails.workAddress.sCity, 30);
			gets_s(person.Details.WorkDetails.workAddress.sCountry, 30);
			gets_s(person.Details.WorkDetails.sPhone, 15);
			gets_s(person.Details.WorkDetails.sFax, 15);
			gets_s(person.Details.WorkDetails.sEmail, 30);
		}
		fwrite(&person, sizeof(PersonTmpl), 1, temp);
		scanf("%d", &person.nPersonID);
	}
	fclose(temp);
}

int open_file(char key[])
{
	char *ptr;
	ptr = strtok(key, "=");
	if (strcmp(ptr, "in") == 0)
	{
		ptr = strtok(NULL, "");
		input = fopen(ptr, "rb");
		if (input == NULL)
		{
			printf("Missing input file\n");
			return -1;
		}
	}
	else if (strcmp(ptr, "out") == 0)
	{
		ptr = strtok(NULL, "");
		output = fopen(ptr, "wt");
		if (output == NULL)
		{
			printf("Output file couldn't be created\n");
			return -1;
		}
	}
	return 1;
}

void write_output()
{
	PersonTmpl person;
	fread(&person, sizeof(PersonTmpl), 1, input);
	while (!feof(input))
	{
		if (person.chRecordType == '1')
		{
			fprintf(output, "%-4d %c %-30s %-30s %-10s ",
				person.nPersonID,
				person.chRecordType,
				person.Details.PersonalInfo.sFirstName,
				person.Details.PersonalInfo.sLastName,
				person.Details.PersonalInfo.sBirthdate);
			if (person.Details.PersonalInfo.theGender == 1)
				fprintf(output, "M \n");
			else
				fprintf(output, "F \n");
		}
		else if (person.chRecordType == '2')
		{
			fprintf(output, "%-4d %c %-30s %-30s %-30s %-15s %-30s \n",
				person.nPersonID,
				person.chRecordType,
				person.Details.HomeDetails.homeAddress.sStreet,
				person.Details.HomeDetails.homeAddress.sCity,
				person.Details.HomeDetails.homeAddress.sCountry,
				person.Details.HomeDetails.sPhone,
				person.Details.HomeDetails.sEmail);
		}
		else if (person.chRecordType == '3')
		{
			fprintf(output, "%-4d %c %-30s %-30s %-30s %-30s %-15s %-15s %-30s \n",
				person.nPersonID,
				person.chRecordType,
				person.Details.WorkDetails.sCompany,
				person.Details.WorkDetails.workAddress.sStreet,
				person.Details.WorkDetails.workAddress.sCity,
				person.Details.WorkDetails.workAddress.sCountry,
				person.Details.WorkDetails.sPhone,
				person.Details.WorkDetails.sFax,
				person.Details.WorkDetails.sEmail);
		}
		fread(&person, sizeof(PersonTmpl), 1, input);
	}
}

int prepare_files()
{
	int error1, error2;
	char key[20];
	fscanf(config_file, "%s", key);
	error1 = open_file(key);
	fscanf(config_file, "%s", key);
	error2 = open_file(key);
	if (error1 == -1) 
	{
		return -1;
	}
	if (error2 == -1)
	{
		return -2;
	}
	return 1;
}

void close_files()
{
	if (input)
	{
		fclose(input);
	}
	if (output)
	{
		fclose(output);
	}
	if (config_file)
	{
		fclose(config_file);
	}
}

int main() 
{
	int error;

	config_file = fopen("testc.ini", "rt");
	if (config_file == NULL)
	{
		printf("Missing config file\n");
		return -1;
	}

	error = prepare_files();
	if (error == -1)
	{
		printf("Creating file Person.h using keyboard input(type -1 to stop):\n");
		create_input_file();
		return -1;
	}
	if (error == -2)
	{
		printf("Check permissions and/or memory space\n");
		return -2;
	}

	write_output();
	close_files();
	return 0;
}
