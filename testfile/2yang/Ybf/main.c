#include <stdio.h>
#include <string.h>
#include <time.h>

#include "bloom.h"

void bloomfilter(FILE* fp_srcpool,FILE* fp_chkpool,FILE* fp_result)
{
	char mail[150]={0};
	unsigned int hash=0;
	unsigned int K=11;

	BF* BloomFilter=bloom_create(
			HT_MAX_SIZE,
			K,
			RSHash,
			JSHash,
			PJWHash,
			ELFHash,
			BKDRHash,
			SDBMHash,
			DJBHash,
			DEKHash,
			BPHash,
			FNVHash,
			APHash);

	if(NULL==BloomFilter)
	{
		printf("bloomfilter create failed!\n");
		return;
	}
	while(fgets(mail,150,fp_srcpool))
	{
		mail[strlen(mail)-1]=0;
		bloom_add(BloomFilter,mail);

		memset(mail,0,150);
	}

	memset(mail,0,150);
	while(fgets(mail,150,fp_chkpool))
	{
		mail[strlen(mail)-1]=0;
		hash=bloom_check(BloomFilter,mail);

		if(hash==K)
			fprintf(fp_result,"%s    YES\n",mail);
		else
			fprintf(fp_result,"%s    NO\n",mail);

		memset(mail,0,150);
	}
	bloom_destroy(BloomFilter);
}

int main(int argc, char *argv[])
{
	clock_t start=clock(),end;
	FILE* fp_srcpool;
	FILE* fp_chkpool;
	FILE* fp_result;

	if(argc<4) {
		fprintf(stderr, "ERROR: No word file specified\n");
		return EXIT_FAILURE;
	}

	fp_srcpool=fopen(argv[1],"r");
	fp_chkpool=fopen(argv[2],"r");
	fp_result=fopen(argv[3],"w");

	bloomfilter(fp_srcpool,fp_chkpool,fp_result);

	fclose(fp_srcpool);
	fclose(fp_chkpool);
	fclose(fp_result);

	end = clock();
	printf("%f\n",(double)(end-start)/CLOCKS_PER_SEC);
	return 0;
}
