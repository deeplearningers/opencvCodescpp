#include<iostream>
#include<stdio.h>

int func(int a);

int main()
{
	
	int n;
	std::cout << "������n��ֵ" << std::endl;
	std::cin >> n ;
	
	int y;
	y = func(n);
	std::cout << "n�Ľ׳���" << y << std::endl;
	return 0;
	system("pause");
}
int func(int a)
{
	int f;
	if (a == 0 ||a == 1){
		f = 1;
	}
	else{
		f = a*func(a - 1);
	}
	
	return f; 
}