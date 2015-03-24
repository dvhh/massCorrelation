/**
@file
@author DINH Viet Huy Hubert <dinh@ifrec.osaka-u.ac.jp>
@version 1.1
@section DESCRIPTION

entry point for processing tab separated data to correlation values

**/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

#include "correlation.h"

const size_t lineMax=131072;

static void die(const char*);
/**
 * print error message and exit program
 *
 * @param [in] message
 * a string containing the message to print before ending the program
 */
static void die(const char* message) {
	fprintf(stderr,"%s\n",message);
	abort();
}

/**
 *  read input vectors as matrix
 *
 *  @param [in] input 
 *  file stream to read the vectors from
 *
 *  @param [out] cols
 *  output, number of cols read
 *
 *  @param [out] row
 *  output, number of row read
 *
 *  @return read matrix
 **/
static float* readInputVectors(FILE* input,size_t* cols,size_t* rows) {
	float* result=NULL;
	size_t rcols=0;
	size_t capacity=16;
	size_t lineRead=0;
	char line[lineMax];
	while(fgets(line,lineMax,input)!=NULL) {
		const size_t lineSize=strlen(line);
		if(lineSize == lineMax - 1) {
			die("line too long");
		}
		if(result==NULL) {
			fprintf(stderr,"getting length %zu\n",lineSize);
			for(size_t i=0;i<lineSize;i++) {
				if(line[i]=='\t') {
					rcols++;
				}
			}
			//rcols++; //off by one 
			size_t size=sizeof(float)*rcols*capacity;
			fprintf(stderr,"found %zu cols (%zu)\n",rcols,size);
			result=malloc(size);
			assert(result!=NULL);
			if(result==NULL) {
				die("insuficient memory");
			}
		}
		size_t pos=0;
		size_t idx=0;
		for(size_t i=0;i<lineSize;i++) {
			switch(line[i]) {
				case '\t':
					line[i]=0;
					float value=atof(line+pos);
					result[lineRead*rcols+idx]=value;
					idx++;
					pos=i+1;
					break;
				case '\0':
					pos=lineSize; // force ending
					break;
			}
		}
		assert(idx==rcols);
		lineRead++;
		if(lineRead==capacity) { // automatic grow results
			capacity += 16;
			result = realloc(result,sizeof(float)*rcols*capacity);
			assert(result!=NULL);
			if(result==NULL) {die("insuficient memory");}

		}
	}
	result=realloc(result,sizeof(float)*rcols*lineRead); /// truncate result
	assert(result!=NULL);
	if(result==NULL) {die("insuficient memory");}
	*rows=lineRead;
	*cols=rcols;
	fprintf(stderr,"found %zu %zu (%zu)\n",rcols,lineRead,sizeof(float)*rcols*lineRead);

	return(result);
}

static void showUsage(char* exeName) {
	fprintf(stderr, 
		"Usage :\n"
		"%s < inputFile.txt > output.bin\n"
		"%s -i inputfile.txt -o outputFile.txt\n"
		"arguments could be mixed with pipe style calling"
		, exeName,exeName);
	exit(0);
}

int main(int argc,char** argv) {
	FILE *input=stdin;
	FILE *output=stdout;
	char* inputPath=NULL;
	char* outputPath=NULL;

	int c;
	opterr=0;
	while((c = getopt(argc,argv,"i:o:h"))!= -1) {
		switch(c) {
			case 'i':
				inputPath=strdup(optarg);
				input=fopen(inputPath,"r");
				if(input==NULL) {
					fprintf(stderr, "error reading [%s]\n", inputPath);
					abort();
				}
				break;
			case 'o':
				outputPath=strdup(optarg);
				output=fopen(outputPath,"w");
				if(input==NULL) {
					fprintf(stderr, "error writing [%s]\n", outputPath);
					abort();
				}
				break;
			case 'h':
				showUsage(argv[0]);
				break;
			default:
				showUsage(argv[0]);
				break;

		}
	}

	if(isatty(fileno(output))||isatty(fileno(input))) {
		showUsage(argv[0]);
	}
	//free(malloc(1024));
	fprintf(stderr,"reading input\n");
	size_t cols=0;
	size_t rows=0;
	float* inputData=readInputVectors(input,&cols,&rows);

	if(inputPath!=NULL) {
		free(inputPath);
		inputPath=NULL;
		fclose(input);
	}

	fprintf(stderr,"read %zu cols ,%zu rows\n",cols,rows);
	//abort();
	float* outputData=getCorrelation(inputData,cols,rows);
	free(inputData);

	fprintf(stderr,"writing output data\n");

	fwrite(outputData,sizeof(float),(rows*(rows-1)/2),output);
	free(outputData);
	if(outputPath!=NULL) {
		free(outputPath);
		outputPath=NULL;
		fclose(output);
	}
	fprintf(stderr,"done\n");
	return(EXIT_SUCCESS);
}

