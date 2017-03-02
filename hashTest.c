#include "NonTypedHashMap.c"

int main(){
	hashDefault testHash = newHash();
	int numVal = 400;
	testHash.add("num\0", &numVal, sizeof(int), &testHash);
	printf("num found: %d\n", *((int *) testHash.find("num", &testHash)));
	char str[] = "hello world";
	testHash.add("string\0", str, strlen(str) + 1, &testHash);
	printf("string found: %s\n", (char *) testHash.find("string\0", &testHash));
	printf("num found: %d\n", *((int *) testHash.find("num", &testHash)));
	testHash.remove("string", &testHash);
	printf("string not found: %s\n", (char *) testHash.find("string", &testHash));	
	printf("num found: %d\n", *((int *) testHash.find("num", &testHash)));
	testHash.remove("num", &testHash);
	char str2[] = "welcome to my house";
	testHash.add("welcome\0", str2, strlen(str2) + 1, &testHash);
	int num2 = 500;
	testHash.add("num2\0", &num2, sizeof(int), &testHash);
	char str3[] = "we in here";
	testHash.add("inhere\0", str3, strlen(str3) + 1, &testHash);
	printf("num2 found: %d\n", *((int *) testHash.find("num2\0", &testHash)));
	printf("str2: %s\n", (char *) testHash.find("welcome\0", &testHash));	
	printf("str3: %s\n", (char *) testHash.find("inhere\0", &testHash));	
	return 0;
}
