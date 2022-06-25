#include <bits/stdc++.h>

int main(){
	std::freopen("points-1.txt", "r", stdin);
	std::freopen("input.txt", "w", stdout);

	std::string s;
	while(std::getline(std::cin, s)){
		for(size_t ch : s){			
			if(ch == '+') ch = ' ';
			if(ch == ';') ch = '\n';
			putchar(ch);
		}
	}
	return 0;
}
