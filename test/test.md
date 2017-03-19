# Description of test.mini

- test.mini는 하나의 문자열을 입력 받고 하나의 문자열을 출력해주는 프로그램이다. 문자열은 반드시 영어의 소문자와 대문자로만 이루어져 있다. 만약 문자열에 영어 이외의 문자를 입력받으면 다시 입력 받도록 설정하였다. 입력 받은 문자열의 대소문자를 반전시켜 출력해주는 프로그램이며 Mini Language로 작성되어 있다.

- Pseudocode
```C
char buf[8192];
int i = 0, k = 0;

while (k == 0) {
    printf("Input: ");
    scanf("%s", buf);
    k = 1;
    while (buf[i] != '\0') {
	if (buf[i] >= 'a' && buf[i] <= 'z') {
	    buf[i] -= 32;
	} else if (buf[i] >= 'A' && buf[i] <= 'Z') {
	    buf[i] += 32;
	} else {
	    k = 0;
	    break;
	}
	i++;
    }
}

printf("Output: %s", buf);

return 0;
```
