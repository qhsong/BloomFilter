/*
 * �����Ⱥ�����Bloom Filter�㷨��ѹ��trie���㷨���������н����������ʱ��
 * ����ʱ����������������ʱ�估����ʱ�䣬�������㷨����ʱ�ͷŶ�̬�ڴ�ռ��ʱ��
 * ����ʱ������̨����������Ϣ������ʱ��
 * �����������exe���������ļ�������result_bf.dat,result_trie.datΪ��Ҫ������
 * ��Ա��ë�� �ǻ�ͮ
 */
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include"bloom.h"
//#include"trie.h"

#define SEG_NUM	1024
#define BIG_PRIME 100000007

int check_string(char *str) {
	//��֤�����Ƿ�Ϸ�
	int len = strlen(str);
	int i = 0;
	for (i = 0; i < len; i++) {
		if (str[i] <= 95 && str[i] >= 45) {
			continue;
		} else {
			return 0;
		}
	}
	return 1;
}

void upper_string(char *str) {
	//Сдת��д
	int i = 0;
	int length = strlen(str);
	for (i = 0; i < length; i++) {
		if (str[i] >= 'a' && str[i] <= 'z') {
			str[i] -= 32;
		}
	}
}

void fan(char *str) {
	//��ת�ַ�����δʹ�ã�
	int len = strlen(str);
	char temp[len + 1];
	strcpy(temp, str);
	int i;
	for (i = 0; i < len; i++) {
		temp[i] = str[len - i - 1];
	}
	temp[i] = '\0';
	strcpy(str, temp);
}

int main(int argc, char *argv[]) {
	clock_t start=clock();
	//��������ʱ���cmd����������������������ΪԴ�ַ����ʹ���ѯ�ַ������ļ������ļ���ַ��
	char line[1024];
	if (argc < 2) {
		fprintf(stderr, "ERROR: No word file specified\n");
		return -1;
	}

	//��ȡʱ��

	int big_count = 0;
	int count = 0;

	//bloom filter algorithm

	BF *bloomfilter = bloom_create(BIG_PRIME);
	freopen(argv[1], "r", stdin);
	while (scanf("%s", line) != EOF) {
		upper_string(line);
		if (check_string(line) == 1) {
			bloom_add(bloomfilter, line);
			big_count++;
		}
	}
	fclose(stdin);
	freopen(argv[2], "r", stdin);
	freopen("result_bf.dat", "w", stdout);
	while (scanf("%s", line) != EOF) {
		upper_string(line);
		if (check_string(line) == 1 && bloom_check(bloomfilter, line) == 1) {
			printf("yes\n");
			count++;
		} else {
			printf("no\n");
		}
	}
	fclose(stdin);
	fclose(stdout);
	freopen("/dev/stdin", "r", stdin);
	freopen("computer.time", "a", stdout);

	printf("%f\n",(double)(clock()-start)/CLOCKS_PER_SEC);
	bloom_destroy(bloomfilter);

	/*****************************************************************************/
/*
	//ѹ��trie��
	trie_Node* root;
	root = trie_create();
	//���ļ�������ѹ��trie��
	freopen(argv[1], "r", stdin);
	while (scanf("%s", line) != EOF) {
		upper_string(line);
		if (check_string(line) == 1) {
			trie_add(line, root);
		}
	}
	fclose(stdin);

	//��ѯ�Ƿ�������
	count = 0;
	freopen(argv[2], "r", stdin);
	freopen("result_trie.dat", "w", stdout);
	while (scanf("%s", line) != EOF) {
		upper_string(line);
		if (check_string(line) == 1 && trie_check(line, root) == 1) {
			printf("yes\n");
			count++;
		} else {
			printf("no\n");
		}
	}
	fclose(stdin);
	fclose(stdout);
	freopen("/dev/pts/3", "r", stdin);
	freopen("computer.time", "a", stdout);
	//printf("����%d��\n", count);
*/	
//	trie_destroy(root);//������ֱ���˳����Զ��ͷ��ڴ棬�Ƿ�destroy����Ҫ��ȡ��ע�Ϳ�������destroy��
	return 0;
}
