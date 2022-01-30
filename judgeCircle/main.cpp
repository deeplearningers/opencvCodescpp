#include<stdio.h>
int judgeCircle(char *moves, int size){

	int x = 0, y = 0, i = 0,j=0,t=0;
	for (t = 0; t < size; t++){
		if (*(moves + t) == 'U') x++;
		else if (*(moves + t) == 'D') y++;
		else if (*(moves + t) == 'L') i++;
		else if (*(moves + t) == 'R') j++;
	}
	if (x == y && i == j)
		return 2;
	else 
		return 0;
}

int main(){

	char ch[] = "UDLR";
	printf("%d\n", judgeCircle(ch, 4));
	return 0;
}