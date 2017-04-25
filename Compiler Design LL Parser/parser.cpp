#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
#include <map>

using namespace std; 



map<char, vector<string> > G;
map<string, char> reverseG;
map<char, map<char, char> > pTable;

void readPrecedenceTable(){


	ifstream file("Precedence.txt");
	char line[100000];

	if(file.is_open()){
		int cnt = 0;
		string term;
		while(file.getline(line,100000)){
			if(cnt == 0){
				char *token;
				token = strtok(line," ");
				
				while(token!=NULL){
					term += token[0];		
					token = strtok(NULL, " ");
				}				
			}		
			else{
				char *token;
				token = strtok(line," ");
				char row;

				int ch = -1;
				while(token!=NULL){
					if(ch == -1)
						row = token[0];
					else
						pTable[row][term[ch]] = token[0];
					token = strtok(NULL, " ");
					ch++;
				}
			}

			cnt++;
		}
		file.close();
	}
	else
		printf("Unable to open the file\n");

}

void readGrammar(map<char, vector<string> > &G, map<string, char> &reverseG){


	ifstream file("Grammar.txt");
	char line[100000];

	if(file.is_open()){

		while(file.getline(line,100000)){
			
			char *token;
			token = strtok(line," ");
			int cnt = 0;
			
			char NonTerminal;			
	
			while(token!=NULL){
				if(cnt == 0)
					NonTerminal = token[0];
				else if(cnt%2 == 0){
					string rhs;
					int i = 0;

					while(token[i]!='\0')
						rhs += token[i++];

					G[NonTerminal].push_back(rhs);
					reverseG[rhs] = NonTerminal;					
				}	
				cnt++;
				token = strtok(NULL, " ");
			}
		}
		file.close();
	}
	else
		printf("Unable to open the file\n");

}

void printStage(int id, string st, string ip, char action, int i){
	cout<<"Stack - "<<st<<endl;
	cout<<"Input - ";
	while(i<ip.size()){
		cout<<ip[i];
		i++;
	}
	cout<<"\n";	
	cout<<"Action-";
	if(action == 'S')
		cout<<"Shift\n";
	else if(action == 'A')
		cout<<"Accepted\n";
	else
		cout<<"Reduce\n";
	cout<<"\n";	
}

void solve(string ip){
	int cnt = 1;
	ip += '$';
	int i = 0;
	int len = ip.size();
	string st;
	st = "$";
	while(i<len){
		char top;
		int j = st.size()-1;
		while(j>=0 && st[j]>='A' && st[j]<='Z')
			j--;
		top = st[j];
		if(pTable[top][ip[i]] == 'A'){
			printStage(cnt, st, ip, 'A', i);
			i++;
		}
		else if(pTable[top][ip[i]] == '<' || pTable[top][ip[i]] == '='){
			printStage(cnt, st, ip, 'S', i);
			st += ip[i];
			i++; 
		}
		else if(pTable[top][ip[i]] == '>'){
			printStage(cnt, st, ip, 'R', i);
			string rhs;
			int j = st.size()-1;
			bool flag = 1;
			while(j>=0 && flag){
				string tmp;
				tmp += st[j];
				st.erase(st.begin()+j);
				tmp += rhs;
				rhs = tmp;
				if(reverseG[rhs]!='\0'){
					st += reverseG[rhs];
					flag = 0;
				}
				j--;
			}
		}
		else{
			cout<<"Not Valid"<<endl;
			exit(0);
		}
		cnt++;
	}
}

int main(){

	readGrammar(G, reverseG);
	readPrecedenceTable();
	string input;
	printf("Enter the string :: ");
	cin>>input;
	solve(input);			
		
	return 0;
}
