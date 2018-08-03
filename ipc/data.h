#define MAX_PERSON 5

struct Person // 새롭게 만들 구조체  총 8 + 12 + 4 +4 byte =28 byte
{
    long int my_msg_type; // 필수
    char name[10];  // 12byte -> unused 2byte + char 10byte
    int age;
				    /*unsigned char age;  숫자를 다루기 위해 char type을 사용할 경우 signed char : -127~127
					                            unsigned char : 0 ~255,       1byte */
    int id; //4byte 
};


