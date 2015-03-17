/*
 ============================================================================
 Name        : Basics.c
 Author      : Saliya Ekanayake
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/* Our structure */
/*struct rec
{
	double x,y;
};*/

struct rec
{
	double x,y;
};

/* writes and then reads 10 arbitrary records
   from the file "junk". */
int main()
{
	int i,j;
	FILE *f;
	struct rec r;

	/* create the file of 10 records */
	/*f=fopen("junk","w");
	if (!f)
		return 1;
	for (i=1;i<=10; i++)
	{
		r.x=i*2;
		r.y=i*2+1;
		fwrite(&r,sizeof(struct rec),1,f);
	}
	fclose(f);*/

	/* read the 10 records */
	f=fopen("E:\\Sali\\git\\github\\JavaStack\\kmeans\\points.bin","r");
	if (!f)
		return 1;
	for (i=1;i<=10; i++)
	{
		fread(&r,sizeof(struct rec),1,f);
		printf("%f %f\n",r.x, r.y);
	}
	fclose(f);
	printf("\n");


	return 0;
}

int otherFancyReads(){
	int i,j;
	struct rec r;
	/* use fseek to read the 10 records
		   in reverse order */

	FILE *f=fopen("junk","r");
	if (!f)
		return 1;
	for (i=9; i>=0; i--)
	{
		fseek(f,sizeof(struct rec)*i,SEEK_SET);
		fread(&r,sizeof(struct rec),1,f);
		printf("%f\n",r.x);
	}
	fclose(f);
	printf("\n");

	/* use fseek to read every other record */
	f=fopen("junk","r");
	if (!f)
		return 1;
	fseek(f,0,SEEK_SET);
	for (i=0;i<5; i++)
	{
		fread(&r,sizeof(struct rec),1,f);
		printf("%f\n",r.x);
		fseek(f,sizeof(struct rec),SEEK_CUR);
	}
	fclose(f);
	printf("\n");

	/* use fseek to read 4th record,
	   change it, and write it back */
	f=fopen("junk","r+");
	if (!f)
		return 1;
	fseek(f,sizeof(struct rec)*3,SEEK_SET);
	fread(&r,sizeof(struct rec),1,f);
	r.x=100;
	fseek(f,sizeof(struct rec)*3,SEEK_SET);
	fwrite(&r,sizeof(struct rec),1,f);
	fclose(f);
	printf("\n");

	/* read the 10 records to insure
	   4th record was changed */
	f=fopen("junk","r");
	if (!f)
		return 1;
	for (i=1;i<=10; i++)
	{
		fread(&r,sizeof(struct rec),1,f);
		printf("%f\n",r.x);
	}
	fclose(f);
}

int writeBinaryFile(){
	int counter;
	FILE *ptr_myfile;
	struct rec my_record;

	ptr_myfile=fopen("e:\\points.bin","wb");
	if (!ptr_myfile)
	{
		printf("Unable to open file for writing!");
		return 1;
	}
	for (counter=1; counter <= 10; counter++)
	{
		my_record.x= counter*2;
		my_record.y= counter*2+1;

		write(&my_record, sizeof(struct rec), 1, ptr_myfile);
	}
	fclose(ptr_myfile);
	return 0;
}
int readBinaryFile(){
	int counter;
	FILE *ptr_myfile;
	struct rec my_record;

	ptr_myfile=fopen("e:\\points.bin","rb");
	if (!ptr_myfile)
	{
		printf("Unable to open file for reading!");
		return 1;
	}
	for ( counter=0; counter <10; counter++)
	{
		fread(&my_record,sizeof(struct rec),1,ptr_myfile);
		printf("%f %f\n",my_record.x, my_record.y);
	}
	fclose(ptr_myfile);
	return 0;
}
