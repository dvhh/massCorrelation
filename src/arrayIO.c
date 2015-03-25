#include <stdlib.h>
#include <assert.h>
//#include <stdio.h>
#include "arrayIO.h"

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
extern float* readInputVectors(FILE* input,size_t* cols,size_t* rows) {
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
			rcols++;
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
			float value=0;
			switch(line[i]) {
				case '\t':
					line[i]=0;
					value=atof(line+pos);
					result[lineRead*rcols+idx]=value;
					idx++;
					pos=i+1;
					break;
				case '\0':
					//line[i]=0;
					value=atof(line+pos);
					result[lineRead*rcols+idx]=value;
					//idx++;
					pos=lineSize; // force ending
					break;
			}
		}
		float value=atof(line+pos);
		result[lineRead*rcols+idx]=value;
		idx++;
		//fprintf(stderr,"%i\t%i\n",rcols,idx);
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


