#include<iostream>
#include <fstream>
#include<string>
#include<vector>
#include <algorithm>
#include <utility>
#include<map>
#include<math.h>
using namespace std;

typedef pair<int,int> pii;
typedef pair<int, pair<int,int> > pipii;
typedef vector<pair<int,int> > vpii;
typedef vector<vector<pair<int,int> > >vvpii;
typedef vector<pair<int, pair<int,int> > >vpipii;

const int boardSize=19;
const int playerBoardSize=6;

pii finalRowScore=make_pair(0,0);
pii finalThreatScore=make_pair(0,0);




vvpii completeRowScore,completeThreatScore,completeControlScore;

int getIndex(int a,int b,bool sum){
	if(sum)
		return (a+b)%boardSize;
	return (a-b+boardSize)%boardSize;

}

vector<int>split(string s){
	vector<int>res;
	string temp="";
	
	for(long i=0;i<s.length();i++){
		if(s[i]==' '){
			res.push_back(stoi(temp));
			temp="";
		}else
			temp = temp+s[i];
	}
	res.push_back(stoi(temp));
	return res;
}


void Output(int i,int j){
	char ch[] = {'A','B','C','D','E','F','G','H','J','K','L','M','N','O','P','Q','R','S','T'};
	
	ofstream outFile("output.txt");
	outFile<<i<<ch[getIndex(j,1,false)];
	
	outFile.close();
}


vector<pipii>canICaptureFunction(string board[],string player){
	vector<pipii>res;
	map<pii,int> mp;
	char p = player=="WHITE"?'w':'b';

	for(int i=0;i<19;i++){
		for(int j=0;j<19;j++){
			if(board[i][j]==p){
				//NW working
				if(i-3>=0 && j-3>=0){
					if(board[getIndex(i,1,false)][getIndex(j,1,false)]!='.' && board[getIndex(i,1,false)][getIndex(j,1,false)]!=p){
						if(board[getIndex(i,2,false)][getIndex(j,2,false)]!='.' && board[getIndex(i,2,false)][getIndex(j,2,false)]!=p)
							if(board[getIndex(i,3,false)][getIndex(j,3,false)]=='.')
								mp[make_pair(i-3,j-3)]++;			
					}
				}

				//N working
				if(i-3>=0){
					if(board[getIndex(i,1,false)][j]!='.' && board[getIndex(i,1,false)][j]!=p){
						if(board[getIndex(i,2,false)][j]!='.' && board[getIndex(i,2,false)][j]!=p)
							if(board[getIndex(i,3,false)][j]=='.')
								mp[make_pair(i-3,j)]++;			
					}
				}


				//NE working
				if(i-3>=0 && j+3<19){
					if(board[getIndex(i,1,false)][getIndex(j,1,true)]!='.' && board[getIndex(i,1,false)][getIndex(j,1,true)]!=p){
						if(board[getIndex(i,2,false)][getIndex(j,2,true)]!='.' && board[getIndex(i,2,false)][getIndex(j,2,true)]!=p)
							if(board[getIndex(i,3,false)][getIndex(j,3,true)]=='.')
								mp[make_pair(i-3,j+3)]++;			
					}
				}

				//W working
				if(j-3>=0){
					if(board[i][getIndex(j,1,false)]!='.' && board[i][getIndex(j,1,false)]!=p){
						if(board[i][getIndex(j,2,false)]!='.' && board[i][getIndex(j,2,false)]!=p)
							if(board[i][getIndex(j,3,false)]=='.')
								mp[make_pair(i,j-3)]++;			
					}
				}
			
				//E working
				if(j+3>=0){
					if(board[i][getIndex(j,1,true)]!='.' && board[i][getIndex(j,1,true)]!=p){
						if(board[i][getIndex(j,2,true)]!='.' && board[i][getIndex(j,2,true)]!=p)
							if(board[i][getIndex(j,3,true)]=='.')
							mp[make_pair(i,j+3)]++;			
					}
				}

				//S working
				if(i+3>=0){
					if(board[getIndex(i,1,true)][j]!='.' && board[getIndex(i,1,true)][j]!=p){
						if(board[getIndex(i,2,true)][j]!='.' && board[getIndex(i,2,true)][j]!=p)
							if(board[getIndex(i,3,true)][j]=='.')
								mp[make_pair(i+3,j)]++;			
					}
				}

				//SW working
				if(i+3>=0 && j-3>=0){
					if(board[getIndex(i,1,true)][getIndex(j,1,false)]!='.' && board[getIndex(i,1,true)][getIndex(j,1,false)]!=p){
						if(board[getIndex(i,2,true)][getIndex(j,2,false)]!='.' && board[getIndex(i,2,true)][getIndex(j,2,false)]!=p)
							if(board[getIndex(i,3,true)][getIndex(j,3,false)]=='.')
								mp[make_pair(i+3,j-3)]++;			
					}
				}

				//SE working
				else if(i+3>=0 && j+3>=0){
					if(board[getIndex(i,1,true)][getIndex(j,1,true)]!='.' && board[getIndex(i,1,true)][getIndex(j,1,true)]!=p){
						if(board[getIndex(i,2,true)][getIndex(j,2,true)]!='.' && board[getIndex(i,2,true)][getIndex(j,2,true)]!=p)
							if(board[getIndex(i,3,true)][getIndex(j,3,true)]=='.')
								mp[make_pair(i+3,j+3)]++;			
					}
				}
			}
		}
	}

	for(auto i:mp){
		res.push_back(make_pair(i.second,make_pair(i.first.first,i.first.second)));
	}
	

	sort(res.begin(),res.end(), greater<pipii>());
	
	return res;
}

vector<pipii>canOpponentCapture(string board[], string player){
	vector<pipii>res;
	map<pii,int> mp;
	char p = player=="WHITE"?'w':'b';
	char o = p =='w'?'b':'w';

	for(int i=0;i<19;i++){
		for(int j=0;j<19;j++){
			if(board[i][j]==p){
				//NW working
				if(i-2>=0 && j-2>=0 && i+1<19 && j+1<19){
					if(board[getIndex(i,1,false)][getIndex(j,1,false)]==p){
						if(board[getIndex(i,2,false)][getIndex(j,2,false)]==o){
							if(board[getIndex(i,1,true)][getIndex(j,1,true)]!='.')
								mp[make_pair(i+1,j+1)];
						}else if(board[getIndex(i,1,true)][getIndex(j,1,true)]==o){
							if(board[getIndex(i,2,false)][getIndex(j,2,false)]=='.')
								mp[make_pair(i-2,j-2)];
						}			
					}
				}

				//N working
				if(i-2>=0 && i+1<19){
					if(board[getIndex(i,1,false)][j]==p){

						if(board[getIndex(i,2,false)][j]==o){
							if(board[getIndex(i,1,true)][j]!='.')
								mp[make_pair(i+1,j)];
						}else if(board[getIndex(i,1,true)][j]==o){
							
							if(board[getIndex(i,2,false)][j]=='.')
								mp[make_pair(i-2,j)];
						}			
					}
				}

				//NE working
				if(i-2>=0 && j+2<19 && i+1<19 && j-1>=0){
					if(board[getIndex(i,1,false)][getIndex(j,1,true)]==p){
						if(board[getIndex(i,2,false)][getIndex(j,2,true)]==o){
							if(board[getIndex(i,1,true)][getIndex(j,1,false)]!='.')
								mp[make_pair(i+1,j-1)];
						}else if(board[getIndex(i,1,true)][getIndex(j,1,false)]==o){
							if(board[getIndex(i,2,false)][getIndex(j,2,true)]=='.')
								mp[make_pair(i-2,j+2)];
						}			
					}
				}


				//W working
				if(j-2>=0 && j+1<19){
					if(board[i][getIndex(j,1,false)]==p){
						if(board[i][getIndex(j,2,false)]==o){
							if(board[i][getIndex(j,1,true)]!='.')
								mp[make_pair(i,j+1)];
						}else if(board[i][getIndex(j,1,true)]==o){
							if(board[i][getIndex(j,2,false)]=='.')
								mp[make_pair(i,j-2)];
						}			
					}
				}


				//E working
				if(j+2<19 && j-1>=0){
					if(board[i][getIndex(j,1,true)]==p){
						if(board[i][getIndex(j,2,true)]==o){
							if(board[i][getIndex(j,1,false)]!='.')
								mp[make_pair(i,j-1)];
						}else if(board[i][getIndex(j,1,false)]==o){
							if(board[i][getIndex(j,2,true)]=='.')
								mp[make_pair(i,j+2)];
						}			
					}
				}


				//SW working
				if(i+2<19 && j-2>=0 && i-1>=0 && j+1<19){
					if(board[getIndex(i,1,true)][getIndex(j,1,false)]==p){
						if(board[getIndex(i,2,true)][getIndex(j,2,false)]==o){
							if(board[getIndex(i,1,false)][getIndex(j,1,true)]!='.')
								mp[make_pair(i-1,j+1)];
						}else if(board[getIndex(i,1,false)][getIndex(j,1,true)]==o){
							if(board[getIndex(i,2,true)][getIndex(j,2,false)]=='.')
								mp[make_pair(i+2,j-2)];
						}			
					}
				}



				//S working
				if(i+2<19 && i-1<=0){
					if(board[getIndex(i,1,true)][j]==p){
						if(board[getIndex(i,2,true)][j]==o){
							if(board[getIndex(i,1,false)][j]!='.')
								mp[make_pair(i-1,j)];
						}else if(board[getIndex(i,1,false)][j]==o){
							if(board[getIndex(i,2,true)][j]=='.')
								mp[make_pair(i+2,j)];
						}			
					}
				}

				//SE working
				if(i+2<19 && j+2<19 && i-1>=0 && j-1>=0){
					if(board[getIndex(i,1,true)][getIndex(j,1,true)]==p){
						if(board[getIndex(i,2,true)][getIndex(j,2,true)]==o){
							if(board[getIndex(i,1,false)][getIndex(j,1,false)]!='.')
								mp[make_pair(i-1,j-1)];
						}else if(board[getIndex(i,1,false)][getIndex(j,1,false)]==o){
							if(board[getIndex(i,2,true)][getIndex(j,2,true)]=='.')
								mp[make_pair(i+2,j+2)];
						}			
					}
				}
			}
		}
	}

	for(auto i:mp){
		res.push_back(make_pair(i.second,make_pair(i.first.first,i.first.second)));
	}


	sort(res.begin(),res.end(), greater<pipii>());
	return res;	
}



bool cmp(pii a,pii b){
	if(a.first<b.first)
		return true;
	else if(a.first==b.first)
		return a.second<b.second;
	return false;
}




/*
	O(19*19*5)
	weight: 10
	formula: pow(weight,score)*missing

*/

vvpii getThreatScores(string board[boardSize]){

	int weight=10;

	vvpii res;

	for(int i=0;i<boardSize;i++){
		vector<pii >rowScore(19,make_pair(0,0));

		for(int j=0;j<boardSize;j++){

			int white=0,black=0,missing=0;

			for(int k=0;k<5 && j+k<boardSize;k++){
				if(board[i][getIndex(j,k,true)]=='.')
					missing++;
				else if(board[i][getIndex(j,k,true)]=='w')
					white++;
				else
					break;
			}

			if(white){
				rowScore[j]=make_pair(pow(weight,white-1)*missing,0);
			}else{
				for(int k=0;k<5 && j+k<boardSize;k++){
					if(board[i][getIndex(j,k,true)]=='.')
						missing++;
					else if(board[i][getIndex(j,k,true)]=='b')
						black++;
					else
						break;
				}				
				rowScore[j]=make_pair(0,pow(weight,black-1)*missing);	
			}

			

			/**********************/	

			white=0,black=0,missing=0;


			for(int k=0;k<5 && i+k<boardSize;k++){
				if(board[getIndex(i,k,true)][j]=='.')
					missing++;
				else if(board[getIndex(i,k,true)][j]=='w')
					white++;
				else
					break;
			}

			if(white){
				rowScore[j]=make_pair(pow(weight,white-1)*missing,0);
			}else{
				for(int k=0;k<5 && i+k<boardSize;k++){
					if(board[getIndex(i,k,true)][j]=='.')
						missing++;
					else if(board[getIndex(i,k,true)][j]=='b')
						black++;
					else
						break;
				}
				rowScore[j]=make_pair(0,pow(weight,black-1)*missing);				
			}
			


			/**********************/	



			white=0,black=0,missing=0;


			for(int k=0;k<5 && j+k<boardSize && i+k<boardSize;k++){
				if(board[getIndex(i,k,true)][getIndex(j,k,true)]=='.')
					missing++;
				else if(board[getIndex(i,k,true)][getIndex(j,k,true)]=='w')
					white++;
				else
					break;
			}

			if(white){
				rowScore[j]=make_pair(pow(weight,white-1)*missing,0);
			}else{
				for(int k=0;k<5 && j+k<boardSize && i+k<boardSize;k++){
					if(board[getIndex(i,k,true)][getIndex(j,k,true)]=='.')
						missing++;
					else if(board[getIndex(i,k,true)][getIndex(j,k,true)]=='b')
						black++;
					else
						break;
				}			
				rowScore[j]=make_pair(0,pow(weight,black-1)*missing);	
			}
			


			/**********************/	



			white=0,black=0,missing=0;


			for(int k=0;k<5 && j-k>=0 && i-k>=0;k++){
				if(board[getIndex(i,k,false)][j]=='.') /// ERROR i+k nahi i-k aayega
					missing++;
				else if(board[getIndex(i,k,false)][getIndex(j,k,false)]=='w')
					white++;
				else
					break;
			}

			if(white){
				rowScore[j]=make_pair(pow(weight,white-1)*missing,0);
			}else{
				for(int k=0;k<5 && j-k>=0 && i-k>=0;k++){
					if(board[getIndex(i,k,false)][getIndex(j,k,false)]=='.')
						missing++;
					else if(board[getIndex(i,k,false)][getIndex(j,k,false)]=='b')
						black++;
					else
						break;
				}				
				rowScore[j]=make_pair(0,pow(weight,black-1)*missing);
			}
			
		}

		res.push_back(rowScore);
	}
	return res;

}


/*
	O(19*19*10*10)
	weight=10
	formula: weight*controlScore
	Inplementing weight part during call
*/

vvpii getControlScores(string board[boardSize]){
	vvpii res;
	for(int i=0;i<boardSize;i++){
		vector<pii >rowScore(19,make_pair(0,0));

			for(int j=0;j<boardSize;j++){
				int countW=0,countB=0;


				if(board[i][j]=='.'){
					for(int p=-4;p<5;p++){
						for(int q=-4;q<5;q++){
							if(j+q>=0 && j+q<boardSize && i+p>=0 && i+p<boardSize && board[getIndex(i,p,true)][getIndex(j,q,true)]=='w'){
								countW++;
								if(board[getIndex(i,p,true)][getIndex(j,q,true)]=='b')
									countB--;
							}
							else if(j+q>=0 && j+q<boardSize && i+p>=0 && i+p<boardSize && board[getIndex(i,p,true)][getIndex(j,q,true)]=='b'){
								countB++;
								if(board[getIndex(i,p,true)][getIndex(j,q,true)]=='w')
									countW--;
							}
						}
					}
				}
				
				rowScore[j]=make_pair(countW,countB);
			}
			res.push_back(rowScore);

		}
		return res;
}


/* O(19*19*20)
	weight = 5
	formula: pow(weight,rowScore)*smartWeight
	smartWeight=missing

*/
vvpii getRowScores(string board[boardSize]){
	int weight=5;
	vvpii res;
	for(int i=0;i<boardSize;i++){
		vector<pii >rowScore(19,make_pair(0,0));
		
		for(int j=0;j<boardSize;j++){
			
			int white=0,black=0;

			if(board[i][j]=='w'){
				int sequenceLength=1,missing=1;
				for (int k = 1; k < 5; k++) {
			        if (j+k < boardSize && board[i][getIndex(j,k,true)] == 'w') {
			            sequenceLength++;
			        } else {
			        	if (j+k < boardSize && board[i][getIndex(j,k,true)] == '.')
			        		missing++; 
			            break;
			        }
			    }
			    if(sequenceLength>1)
			    	white=pow(weight,sequenceLength-2)*missing;

			    /**************************/

			    sequenceLength = 1,missing=1;

			    for (int k = 1; k < 5; k++) {
			        if (i+k < boardSize && board[getIndex(i,k,true)][j] == 'w') {
			            sequenceLength++;
			        } else {
			        	if (j+k < boardSize && board[i][getIndex(j,k,true)] == '.')
			        			missing++; 
			            break;
			        }
			    }

			    if(sequenceLength>1)
			    	white+=pow(weight,sequenceLength-2)*missing;

			    /**************************/
			    sequenceLength = 1,missing=1;

			    for (int k = 1; k < 5; k++) {
			        if (i+k < boardSize && j+k<boardSize && board[getIndex(i,k,true)][getIndex(j,k,true)] == 'w') {
			            sequenceLength++;
			        } else {
			        	if (j+k < boardSize && board[i][getIndex(j,k,true)] == '.')
			        			missing++; 
			            break;
			        }
			    }

			    if(sequenceLength>0)
			    	white+=pow(weight,sequenceLength-2)*missing;

			    /**************************/
			    sequenceLength = 1,missing=1;

			    for (int k = 1; k < 5; k++) {
			        if (i+k < boardSize && j-k>=0 && board[getIndex(i,k,true)][getIndex(j,k,false)] == 'w') {
			            sequenceLength++;
			        } else {
			        	if (j+k < boardSize && board[i][getIndex(j,k,true)] == '.')
			        			missing++; 
			            break;
			        }
			    }

			    if(sequenceLength>0)
			    	white+=pow(weight,sequenceLength-2)*missing;

			}else if(board[i][j]=='b'){
				int sequenceLength=1,missing=1;
				for (int k = 1; k < 5; k++) {
			        if (j+k < boardSize && board[i][getIndex(j,k,true)] == 'b') {
			            sequenceLength++;
			        } else {
			        	if (j+k < boardSize && board[i][getIndex(j,k,true)] == '.')
			        		missing++; 
			            break;
			        }
			    }
			    if(sequenceLength>1)
			    	black=pow(weight,sequenceLength-2)*missing;

			    
			    /**************************/

			    sequenceLength = 1,missing=1;

			    for (int k = 1; k < 5; k++) {
			        if (i+k < boardSize && board[getIndex(i,k,true)][j] == 'b') {
			            sequenceLength++;
			        } else {
			        	if (j+k < boardSize && board[i][getIndex(j,k,true)] == '.')
			        			missing++; 
			            break;
			        }
			    }

			    if(sequenceLength>1)
			    	black+=pow(weight,sequenceLength-2)*missing;

			    /**************************/
			    sequenceLength = 1,missing=1;

			    for (int k = 1; k < 5; k++) {
			        if (i+k < boardSize && j+k<boardSize && board[getIndex(i,k,true)][getIndex(j,k,true)] == 'b') {
			            sequenceLength++;
			        } else {
			        	if (j+k < boardSize && board[i][getIndex(j,k,true)] == '.')
			        			missing++; 
			            break;
			        }
			    }

			    if(sequenceLength>0)
			    	black+=pow(weight,sequenceLength-2)*missing;

			    /**************************/
			    sequenceLength = 1,missing=1;

			    for (int k = 1; k < 5; k++) {
			        if (i+k < boardSize && j-k>=0 && board[getIndex(i,k,true)][getIndex(j,k,false)] == 'b') {
			            sequenceLength++;
			        } else {
			        	if (j+k < boardSize && board[i][getIndex(j,k,true)] == '.')
			        			missing++; 
			            break;
			        }
			    }

			    if(sequenceLength>0)
			    	black+=pow(weight,sequenceLength-2)*missing;

								
			}

			rowScore[j]=make_pair(white,black);
		}

		res.push_back(rowScore);
	}

	
	return res;
}



/*

	
*/
bool canIMakeIT(string board[19],int i,int j,string playerString){

	char player = playerString=="WHITE"?'w':'b';

	int count=0;
	for(int k=1;k<5;k++){
		if(j+k<boardSize && board[i][getIndex(j,k,true)]==player)
			count++;
		else
			break;		
	}
	if(count==4)
		return 1;


	count=0;
	for(int k=1;k<5;k++){
		if(i+k<boardSize && board[getIndex(i,k,true)][j]==player)
			count++;
		else
			break;		
	}
	if(count==4)
		return 1;

	count=0;
	for(int k=1;k<5;k++){
		if(i+k<boardSize && j+k<boardSize && board[getIndex(i,k,true)][getIndex(j,k,true)]==player)
			count++;
		else
			break;		
	}
	if(count==4)
		return 1;


	count=0;
	for(int k=1;k<5;k++){
		if(j-k>=0 && board[i][getIndex(j,k,false)]==player)
			count++;
		else
			break;		
	}
	if(count==4)
		return 1;


	count=0;
	for(int k=1;k<5;k++){
		if(i-k>=0 && board[getIndex(i,k,false)][j]==player)
			count++;
		else
			break;		
	}
	if(count==4)
		return 1;



	count=0;
	for(int k=1;k<5;k++){
		if(i-k>=0 && j-k>=0 && board[getIndex(i,k,false)][getIndex(j,k,false)]==player)
			count++;
		else
			break;		
	}
	if(count==4)
		return 1;



	count=0;
	for(int k=1;k<5;k++){
		if(i+k<boardSize && j-k>=0 && board[getIndex(i,k,true)][getIndex(j,k,false)]==player)
			count++;
		else
			break;		
	}
	if(count==4)
		return 1;


	count=0;
	for(int k=1;k<5;k++){
		if(i-k>=0 && j+k<boardSize && board[getIndex(i,k,false)][getIndex(j,k,true)]==player)
			count++;
		else
			break;		
	}
	if(count==4)
		return 1;



	/*************************/


	count=0;
	
	if(j-1>=0 && board[i][getIndex(j,1,false)]==player)
		count++;

	for(int k=1;k<4;k++){
		if(j+k<boardSize && board[i][getIndex(j,k,true)]==player)
			count++;
		else
			break;		
	}
	if(count==4)
		return 1;


	count=0;

	if(i-1>=0 && board[getIndex(i,1,false)][j]==player)
		count++;

	for(int k=1;k<4;k++){
		if(i+k<boardSize && board[getIndex(i,k,true)][j]==player)
			count++;
		else
			break;		
	}
	if(count==4)
		return 1;

	count=0;

	if(j-1>=0 &&i-1>=0 && board[getIndex(i,1,false)][getIndex(j,1,false)]==player)
		count++;

	for(int k=1;k<4;k++){
		if(i+k<boardSize && j+k<boardSize && board[getIndex(i,k,true)][getIndex(j,k,true)]==player)
			count++;
		else
			break;		
	}
	if(count==4)
		return 1;


	count=0;


	if(j+1<boardSize && board[i][getIndex(j,1,true)]==player)
		count++;

	for(int k=1;k<4;k++){
		if(j-k>=0 && board[i][getIndex(j,k,false)]==player)
			count++;
		else
			break;		
	}
	if(count==4)
		return 1;


	count=0;

	if(i+1<boardSize && board[getIndex(i,1,true)][j]==player)
		count++;

	for(int k=1;k<4;k++){
		if(i-k>=0 && board[getIndex(i,k,false)][j]==player)
			count++;
		else
			break;		
	}
	if(count==4)
		return 1;



	count=0;



	if(i+1<boardSize && j+1<boardSize && board[getIndex(i,1,true)][getIndex(j,1,true)]==player)
		count++;


	for(int k=1;k<4;k++){
		if(i-k>=0 && j-k>=0 && board[getIndex(i,k,false)][getIndex(j,k,false)]==player)
			count++;
		else
			break;		
	}
	if(count==4)
		return 1;



	count=0;

	if(i-1>=0 && j+1<boardSize && board[getIndex(i,1,false)][getIndex(j,1,true)]==player)
		count++;


	for(int k=1;k<4;k++){
		if(i+k<boardSize && j-k>=0 && board[getIndex(i,k,true)][getIndex(j,k,false)]==player)
			count++;
		else
			break;		
	}
	if(count==4)
		return 1;


	count=0;

	if(i+1<boardSize && j-1>=0 && board[getIndex(i,1,true)][getIndex(j,1,false)]==player)
		count++;

	for(int k=1;k<4;k++){
		if(i-k>=0 && j+k<boardSize && board[getIndex(i,k,false)][getIndex(j,k,true)]==player)
			count++;
		else
			break;		
	}
	if(count==4)
		return 1;


	/************************************************/



	if(i-2>=0 && i+2<boardSize && board[getIndex(i,2,false)][j]==player && board[getIndex(i,1,false)][j]==player && board[getIndex(i,1,true)][j]==player && board[getIndex(i,2,true)][j]==player)
			return 1;
	

	if(j-2>=0 && j+2<boardSize && board[i][getIndex(j,2,false)]==player && board[i][getIndex(j,1,false)]==player && board[i][getIndex(j,1,true)]==player && board[i][getIndex(j,2,true)]==player)
			return 1;


	if(j-2>=0 && j+2<boardSize && i-2>=0 && i+2<boardSize 
		&& board[getIndex(i,2,false)][getIndex(j,2,false)]==player && board[getIndex(i,1,false)][getIndex(j,1,false)]==player && board[getIndex(i,1,true)][getIndex(j,1,true)]==player && board[getIndex(i,2,true)][getIndex(j,2,true)]==player)
			return 1;


	if(j-2>=0 && j+2<boardSize && i-2>=0 && i+2<boardSize 
		&& board[getIndex(i,2,true)][getIndex(j,2,false)]==player && board[getIndex(i,1,true)][getIndex(j,1,false)]==player && board[getIndex(i,1,false)][getIndex(j,1,true)]==player && board[getIndex(i,2,false)][getIndex(j,2,true)]==player)
			return 1;


	/***********************************************/








	return 0;	
}

pii getScore(vvpii param){
	int white=0,black=0;
	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			white+=param[i][j].first;
			black+=param[i][j].second;
		}
	}

	return make_pair(white,black);
}


int getSpecialScore(string board[boardSize],vpii moves,bool white,int i,int j){
	int score=0;
	if(white){
		
		//Vertical

		if(i-4>=0){
			if(board[getIndex(i,4,false)][j]=='.' && board[getIndex(i,3,false)][j]=='w' && board[getIndex(i,2,false)][j]=='w' && board[getIndex(i,1,false)][j]=='w' && board[i][j]=='.')
				score+=90;
			else if(board[getIndex(i,4,false)][j]=='w' && board[getIndex(i,3,false)][j]=='w' && board[getIndex(i,2,false)][j]=='w' && board[getIndex(i,1,false)][j]=='w' && board[i][j]=='w')
				score+=1000;
			else if(board[getIndex(i,4,false)][j]=='w' && board[getIndex(i,3,false)][j]=='b' && board[getIndex(i,2,false)][j]=='b' && board[getIndex(i,1,false)][j]=='w')
				score+=100;

		}else if(i-3>=0 && i+1<boardSize){
			if(board[getIndex(i,3,false)][j]=='.' && board[getIndex(i,2,false)][j]=='w' && board[getIndex(i,1,false)][j]=='w' && board[i][j]=='w' && board[getIndex(i,1,true)][j]=='.')
				score+=90;
			else if(board[getIndex(i,3,false)][j]=='w' && board[getIndex(i,2,false)][j]=='w' && board[getIndex(i,1,false)][j]=='w' && board[i][j]=='w' && board[getIndex(i,1,true)][j]=='w')
				score+=1000;
			else if(board[getIndex(i,3,false)][j]=='w' && board[getIndex(i,2,false)][j]=='b' && board[getIndex(i,1,false)][j]=='b' && board[i][j]=='w')
				score+=100;
		}else if(i-2>=0 && i+2<boardSize){
			if(board[getIndex(i,2,false)][j]=='.' && board[getIndex(i,1,false)][j]=='w' && board[i][j]=='w' && board[getIndex(i,1,true)][j]=='w' && board[getIndex(i,2,true)][j]=='.')
				score+=90;
			else if(board[getIndex(i,2,false)][j]=='w' && board[getIndex(i,1,false)][j]=='w' && board[i][j]=='w' && board[getIndex(i,1,true)][j]=='w' && board[getIndex(i,2,true)][j]=='w')
				score+=1000;
			else if(board[getIndex(i,2,false)][j]=='w' && board[getIndex(i,1,false)][j]=='b' && board[i][j]=='b' && board[getIndex(i,1,true)][j]=='w')
				score+=100;
		}else if(i-1>=0 && i+3<boardSize){
			if(board[getIndex(i,1,false)][j]=='.' && board[i][j]=='w' && board[getIndex(i,1,true)][j]=='w' && board[getIndex(i,2,true)][j]=='w' && board[getIndex(i,3,true)][j]=='.')
				score+=90;
			else if(board[getIndex(i,1,false)][j]=='w' && board[i][j]=='w' && board[getIndex(i,1,true)][j]=='w' && board[getIndex(i,2,true)][j]=='w' && board[getIndex(i,3,true)][j]=='w')
				score+=1000;
			else if(board[getIndex(i,1,false)][j]=='w' && board[i][j]=='b' && board[getIndex(i,1,true)][j]=='b' && board[getIndex(i,2,true)][j]=='w')
				score+=100;
		}else if(i+4<boardSize){
			if(board[i][j]=='.' && board[getIndex(i,1,true)][j]=='w' && board[getIndex(i,2,true)][j]=='w' && board[getIndex(i,3,true)][j]=='w' && board[getIndex(i,4,true)][j]=='.')
				score+=90;
			else if(board[i][j]=='w' && board[getIndex(i,1,true)][j]=='w' && board[getIndex(i,2,true)][j]=='w' && board[getIndex(i,3,true)][j]=='w' && board[getIndex(i,4,true)][j]=='w')
				score+=1000;
			else if(board[i][j]=='w' && board[getIndex(i,1,true)][j]=='b' && board[getIndex(i,2,true)][j]=='b' && board[getIndex(i,3,true)][j]=='w')
				score+=100;
		}


		//Horizontal


		if(j-4>=0){
			if(board[i][getIndex(j,4,false)]=='.' && board[i][getIndex(j,3,false)]=='w' && board[i][getIndex(j,2,false)]=='w' && board[i][getIndex(j,1,false)]=='w' && board[i][j]=='.')
				score+=90;
			else if(board[i][getIndex(j,4,false)]=='w' && board[i][getIndex(j,3,false)]=='w' && board[i][getIndex(j,2,false)]=='w' && board[i][getIndex(j,1,false)]=='w' && board[i][j]=='w')
				score+=1000;
			else if(board[i][getIndex(j,4,false)]=='w' && board[i][getIndex(j,3,false)]=='b' && board[i][getIndex(j,2,false)]=='b' && board[i][getIndex(j,1,false)]=='w')
				score+=100;

		}else if(j-3>=0 && j+1<boardSize){
			if(board[i][getIndex(j,3,false)]=='.' && board[i][getIndex(j,2,false)]=='w' && board[i][getIndex(j,1,false)]=='w' && board[i][j]=='w' && board[i][getIndex(j,1,true)]=='.')
				score+=90;
			else if(board[i][getIndex(j,3,false)]=='w' && board[i][getIndex(j,2,false)]=='w' && board[i][getIndex(j,1,false)]=='w' && board[i][j]=='w' && board[i][getIndex(j,1,true)]=='w')
				score+=1000;
			else if(board[i][getIndex(j,3,false)]=='w' && board[i][getIndex(j,2,false)]=='b' && board[i][getIndex(j,1,false)]=='b' && board[i][j]=='w')
				score+=100;

		}else if(j-2>=0 && j+2<boardSize){
			if(board[i][getIndex(j,2,false)]=='.' && board[i][getIndex(j,1,false)]=='w' && board[i][j]=='w' && board[i][getIndex(j,1,true)]=='w' && board[i][getIndex(j,2,true)]=='.')
				score+=90;
			else if(board[i][getIndex(j,2,false)]=='w' && board[i][getIndex(j,1,false)]=='w' && board[i][j]=='w' && board[i][getIndex(j,1,true)]=='w' && board[i][getIndex(j,2,true)]=='w')
				score+=1000;
			else if(board[i][getIndex(j,2,false)]=='w' && board[i][getIndex(j,1,false)]=='b' && board[i][j]=='b' && board[i][getIndex(j,1,true)]=='w')
				score+=100;

		}else if(j-1>=0 && j+3<boardSize){
			if(board[i][getIndex(j,1,false)]=='.' && board[i][j]=='w' && board[i][getIndex(j,1,true)]=='w' && board[i][getIndex(j,2,true)]=='w' && board[getIndex(i,3,true)][j]=='.')
				score+=90;
			else if(board[i][getIndex(j,1,false)]=='w' && board[i][j]=='w' && board[i][getIndex(j,1,true)]=='w' && board[i][getIndex(j,2,true)]=='w' && board[getIndex(i,3,true)][j]=='w')
				score+=1000;
			else if(board[i][getIndex(j,1,false)]=='w' && board[i][j]=='b' && board[i][getIndex(j,1,true)]=='b' && board[i][getIndex(j,2,true)]=='w')
				score+=100;

		}else if(j+4<boardSize){
			if(board[i][j]=='.' && board[i][getIndex(j,1,true)]=='w' && board[i][getIndex(j,2,true)]=='w' && board[i][getIndex(j,3,true)]=='w' && board[i][getIndex(j,4,true)]=='.')
				score+=90;
			else if(board[i][j]=='w' && board[i][getIndex(j,1,true)]=='w' && board[i][getIndex(j,2,true)]=='w' && board[i][getIndex(j,3,true)]=='w' && board[i][getIndex(j,4,true)]=='w')
				score+=1000;
			else if(board[i][j]=='w' && board[i][getIndex(j,1,true)]=='b' && board[i][getIndex(j,2,true)]=='b' && board[i][getIndex(j,3,true)]=='w')
				score+=100;
		}


		//Diagonal

		if(j-4>=0 && i-4>=0){
			if(board[getIndex(i,4,false)][getIndex(j,4,false)]=='.' && board[getIndex(i,3,false)][getIndex(j,3,false)]=='w' && board[getIndex(i,2,false)][getIndex(j,2,false)]=='w' && board[getIndex(i,1,false)][getIndex(j,1,false)]=='w' && board[i][j]=='.')
				score+=90;
			else if(board[getIndex(i,4,false)][getIndex(j,4,false)]=='w' && board[getIndex(i,3,false)][getIndex(j,3,false)]=='w' && board[getIndex(i,2,false)][getIndex(j,2,false)]=='w' && board[getIndex(i,1,false)][getIndex(j,1,false)]=='w' && board[i][j]=='w')
				score+=1000;
			else if(board[getIndex(i,4,false)][getIndex(j,4,false)]=='w' && board[getIndex(i,3,false)][getIndex(j,3,false)]=='b' && board[getIndex(i,2,false)][getIndex(j,2,false)]=='b' && board[getIndex(i,1,false)][getIndex(j,1,false)]=='w')
				score+=100;

		}else if(j-3>=0 && j+1<boardSize && i-3>=0 && i+1<boardSize){
			if(board[getIndex(i,3,false)][getIndex(j,3,false)]=='.' && board[getIndex(i,2,false)][getIndex(j,2,false)]=='w' && board[getIndex(i,1,false)][getIndex(j,1,false)]=='w' && board[i][j]=='w' && board[getIndex(i,1,true)][getIndex(j,1,true)]=='.')
				score+=90;
			else if(board[getIndex(i,3,false)][getIndex(j,3,false)]=='w' && board[getIndex(i,2,false)][getIndex(j,2,false)]=='w' && board[getIndex(i,1,false)][getIndex(j,1,false)]=='w' && board[i][j]=='w' && board[getIndex(i,1,true)][getIndex(j,1,true)]=='w')
				score+=1000;
			else if(board[getIndex(i,3,false)][getIndex(j,3,false)]=='w' && board[getIndex(i,2,false)][getIndex(j,2,false)]=='b' && board[getIndex(i,1,false)][getIndex(j,1,false)]=='b' && board[i][j]=='w')
				score+=100;

		}else if(j-2>=0 && j+2<boardSize && i-2>=0 && i+2<boardSize){
			if(board[getIndex(i,2,false)][getIndex(j,2,false)]=='.' && board[getIndex(i,1,false)][getIndex(j,1,false)]=='w' && board[i][j]=='w' && board[getIndex(i,1,true)][getIndex(j,1,true)]=='w' && board[getIndex(i,2,true)][getIndex(j,2,true)]=='.')
				score+=90;
			else if(board[getIndex(i,2,false)][getIndex(j,2,false)]=='w' && board[getIndex(i,1,false)][getIndex(j,1,false)]=='w' && board[i][j]=='w' && board[getIndex(i,1,true)][getIndex(j,1,true)]=='w' && board[getIndex(i,2,true)][getIndex(j,2,true)]=='w')
				score+=1000;
			else if(board[getIndex(i,2,false)][getIndex(j,2,false)]=='w' && board[getIndex(i,1,false)][getIndex(j,1,false)]=='b' && board[i][j]=='b' && board[getIndex(i,1,true)][getIndex(j,1,true)]=='w')
				score+=100;

		}else if(j-1>=0 && j+3<boardSize && i-1>=0 && i+3<boardSize){
			if(board[getIndex(i,1,false)][getIndex(j,1,false)]=='.' && board[i][j]=='w' && board[getIndex(i,1,true)][getIndex(j,1,true)]=='w' && board[getIndex(i,2,true)][getIndex(j,2,true)]=='w' && board[getIndex(i,3,true)][getIndex(j,3,true)]=='.')
				score+=90;
			else if(board[getIndex(i,1,false)][getIndex(j,1,false)]=='w' && board[i][j]=='w' && board[getIndex(i,1,true)][getIndex(j,1,true)]=='w' && board[getIndex(i,2,true)][getIndex(j,2,true)]=='w' && board[getIndex(i,3,true)][getIndex(j,3,true)]=='w')
				score+=1000;
			else if(board[getIndex(i,1,false)][getIndex(j,1,false)]=='w' && board[i][j]=='b' && board[getIndex(i,1,true)][getIndex(j,1,true)]=='b' && board[getIndex(i,2,true)][getIndex(j,2,true)]=='w')
				score+=100;

		}else if(j+4<boardSize && i+4<boardSize){
			if(board[i][j]=='.' && board[getIndex(i,1,true)][getIndex(j,1,true)]=='w' && board[getIndex(i,2,true)][getIndex(j,2,true)]=='w' && board[getIndex(i,3,true)][getIndex(j,3,true)]=='w' && board[getIndex(i,4,true)][getIndex(j,4,true)]=='.')
				score+=90;
			else if(board[i][j]=='w' && board[getIndex(i,1,true)][getIndex(j,1,true)]=='w' && board[getIndex(i,2,true)][getIndex(j,2,true)]=='w' && board[getIndex(i,3,true)][getIndex(j,3,true)]=='w' && board[getIndex(i,4,true)][getIndex(j,4,true)]=='w')
				score+=1000;
			else if(board[i][j]=='w' && board[getIndex(i,1,true)][getIndex(j,1,true)]=='b' && board[getIndex(i,2,true)][getIndex(j,2,true)]=='b' && board[getIndex(i,3,true)][getIndex(j,3,true)]=='w')
				score+=100;
		}



		//Diagonal

		if(j-4>=0 && i+4<boardSize){
			if(board[getIndex(i,4,true)][getIndex(j,4,false)]=='.' && board[getIndex(i,3,true)][getIndex(j,3,false)]=='w' && board[getIndex(i,2,true)][getIndex(j,2,false)]=='w' && board[getIndex(i,1,true)][getIndex(j,1,false)]=='w' && board[i][j]=='.')
				score+=90;
			else if(board[getIndex(i,4,true)][getIndex(j,4,false)]=='w' && board[getIndex(i,3,true)][getIndex(j,3,false)]=='w' && board[getIndex(i,2,true)][getIndex(j,2,false)]=='w' && board[getIndex(i,1,true)][getIndex(j,1,false)]=='w' && board[i][j]=='w')
				score+=1000;
			else if(board[getIndex(i,4,true)][getIndex(j,4,false)]=='w' && board[getIndex(i,3,true)][getIndex(j,3,false)]=='b' && board[getIndex(i,2,true)][getIndex(j,2,false)]=='b' && board[getIndex(i,1,true)][getIndex(j,1,false)]=='w')
				score+=100;

		}else if(j-3>=0 && j+1<boardSize && i+3<boardSize && i-1>=0){
			if(board[getIndex(i,3,true)][getIndex(j,3,false)]=='.' && board[getIndex(i,2,true)][getIndex(j,2,false)]=='w' && board[getIndex(i,1,true)][getIndex(j,1,false)]=='w' && board[i][j]=='w' && board[getIndex(i,1,false)][getIndex(j,1,true)]=='.')
				score+=90;
			else if(board[getIndex(i,3,true)][getIndex(j,3,false)]=='w' && board[getIndex(i,2,true)][getIndex(j,2,false)]=='w' && board[getIndex(i,1,true)][getIndex(j,1,false)]=='w' && board[i][j]=='w' && board[getIndex(i,1,false)][getIndex(j,1,true)]=='w')
				score+=1000;
			else if(board[getIndex(i,3,true)][getIndex(j,3,false)]=='w' && board[getIndex(i,2,true)][getIndex(j,2,false)]=='b' && board[getIndex(i,1,true)][getIndex(j,1,false)]=='b' && board[i][j]=='w')
				score+=100;

		}else if(j-2>=0 && j+2<boardSize && i+2<boardSize && i-2>=0){
			if(board[getIndex(i,2,true)][getIndex(j,2,false)]=='.' && board[getIndex(i,1,true)][getIndex(j,1,false)]=='w' && board[i][j]=='w' && board[getIndex(i,1,false)][getIndex(j,1,true)]=='w' && board[getIndex(i,2,false)][getIndex(j,2,true)]=='.')
				score+=90;
			else if(board[getIndex(i,2,true)][getIndex(j,2,false)]=='w' && board[getIndex(i,1,true)][getIndex(j,1,false)]=='w' && board[i][j]=='w' && board[getIndex(i,1,false)][getIndex(j,1,true)]=='w' && board[getIndex(i,2,false)][getIndex(j,2,true)]=='w')
				score+=1000;
			else if(board[getIndex(i,2,true)][getIndex(j,2,false)]=='w' && board[getIndex(i,1,true)][getIndex(j,1,false)]=='b' && board[i][j]=='b' && board[getIndex(i,1,false)][getIndex(j,1,true)]=='w')
				score+=100;

		}else if(j-1>=0 && j+3<boardSize && i+1<boardSize && i-3>=0){
			if(board[getIndex(i,1,true)][getIndex(j,1,false)]=='.' && board[i][j]=='w' && board[getIndex(i,1,false)][getIndex(j,1,true)]=='w' && board[getIndex(i,2,false)][getIndex(j,2,true)]=='w' && board[getIndex(i,3,false)][getIndex(j,3,true)]=='.')
				score+=90;
			else if(board[getIndex(i,1,true)][getIndex(j,1,false)]=='w' && board[i][j]=='w' && board[getIndex(i,1,false)][getIndex(j,1,true)]=='w' && board[getIndex(i,2,false)][getIndex(j,2,true)]=='w' && board[getIndex(i,3,false)][getIndex(j,3,true)]=='w')
				score+=1000;
			else if(board[getIndex(i,1,true)][getIndex(j,1,false)]=='w' && board[i][j]=='b' && board[getIndex(i,1,false)][getIndex(j,1,true)]=='b' && board[getIndex(i,2,false)][getIndex(j,2,true)]=='w')
				score+=100;

		}else if(j+4<boardSize && i-4>=0){
			if(board[i][j]=='.' && board[getIndex(i,1,false)][getIndex(j,1,true)]=='w' && board[getIndex(i,2,false)][getIndex(j,2,true)]=='w' && board[getIndex(i,3,false)][getIndex(j,3,true)]=='w' && board[getIndex(i,4,false)][getIndex(j,4,true)]=='.')
				score+=90;
			else if(board[i][j]=='w' && board[getIndex(i,1,false)][getIndex(j,1,true)]=='w' && board[getIndex(i,2,false)][getIndex(j,2,true)]=='w' && board[getIndex(i,3,false)][getIndex(j,3,true)]=='w' && board[getIndex(i,4,false)][getIndex(j,4,true)]=='w')
				score+=1000;
			else if(board[i][j]=='w' && board[getIndex(i,1,false)][getIndex(j,1,true)]=='b' && board[getIndex(i,2,false)][getIndex(j,2,true)]=='b' && board[getIndex(i,3,false)][getIndex(j,3,true)]=='w')
				score+=100;
		}
	}

	else{
		
		//Vertical

		if(i-4>=0){
			if(board[getIndex(i,4,false)][j]=='.' && board[getIndex(i,3,false)][j]=='b' && board[getIndex(i,2,false)][j]=='b' && board[getIndex(i,1,false)][j]=='b' && board[i][j]=='.')
				score+=90;
			else if(board[getIndex(i,4,false)][j]=='b' && board[getIndex(i,3,false)][j]=='b' && board[getIndex(i,2,false)][j]=='b' && board[getIndex(i,1,false)][j]=='b' && board[i][j]=='b')
				score+=1000;
			else if(board[getIndex(i,4,false)][j]=='b' && board[getIndex(i,3,false)][j]=='w' && board[getIndex(i,2,false)][j]=='w' && board[getIndex(i,1,false)][j]=='b')
				score+=100;

		}else if(i-3>=0 && i+1<boardSize){
			if(board[getIndex(i,3,false)][j]=='.' && board[getIndex(i,2,false)][j]=='b' && board[getIndex(i,1,false)][j]=='b' && board[i][j]=='b' && board[getIndex(i,1,true)][j]=='.')
				score+=90;
			else if(board[getIndex(i,3,false)][j]=='b' && board[getIndex(i,2,false)][j]=='b' && board[getIndex(i,1,false)][j]=='b' && board[i][j]=='b' && board[getIndex(i,1,true)][j]=='b')
				score+=1000;
			else if(board[getIndex(i,3,false)][j]=='b' && board[getIndex(i,2,false)][j]=='w' && board[getIndex(i,1,false)][j]=='w' && board[i][j]=='b')
				score+=100;
		}else if(i-2>=0 && i+2<boardSize){
			if(board[getIndex(i,2,false)][j]=='.' && board[getIndex(i,1,false)][j]=='b' && board[i][j]=='b' && board[getIndex(i,1,true)][j]=='b' && board[getIndex(i,2,true)][j]=='.')
				score+=90;
			else if(board[getIndex(i,2,false)][j]=='b' && board[getIndex(i,1,false)][j]=='b' && board[i][j]=='b' && board[getIndex(i,1,true)][j]=='b' && board[getIndex(i,2,true)][j]=='b')
				score+=1000;
			else if(board[getIndex(i,2,false)][j]=='b' && board[getIndex(i,1,false)][j]=='w' && board[i][j]=='w' && board[getIndex(i,1,true)][j]=='b')
				score+=100;
		}else if(i-1>=0 && i+3<boardSize){
			if(board[getIndex(i,1,false)][j]=='.' && board[i][j]=='b' && board[getIndex(i,1,true)][j]=='b' && board[getIndex(i,2,true)][j]=='b' && board[getIndex(i,3,true)][j]=='.')
				score+=90;
			else if(board[getIndex(i,1,false)][j]=='b' && board[i][j]=='b' && board[getIndex(i,1,true)][j]=='b' && board[getIndex(i,2,true)][j]=='b' && board[getIndex(i,3,true)][j]=='b')
				score+=1000;
			else if(board[getIndex(i,1,false)][j]=='b' && board[i][j]=='w' && board[getIndex(i,1,true)][j]=='w' && board[getIndex(i,2,true)][j]=='b')
				score+=100;
		}else if(i+4<boardSize){
			if(board[i][j]=='.' && board[getIndex(i,1,true)][j]=='b' && board[getIndex(i,2,true)][j]=='b' && board[getIndex(i,3,true)][j]=='b' && board[getIndex(i,4,true)][j]=='.')
				score+=90;
			else if(board[i][j]=='b' && board[getIndex(i,1,true)][j]=='b' && board[getIndex(i,2,true)][j]=='b' && board[getIndex(i,3,true)][j]=='b' && board[getIndex(i,4,true)][j]=='b')
				score+=1000;
			else if(board[i][j]=='b' && board[getIndex(i,1,true)][j]=='w' && board[getIndex(i,2,true)][j]=='w' && board[getIndex(i,3,true)][j]=='b')
				score+=100;
		}


		//Horizontal


		if(j-4>=0){
			if(board[i][getIndex(j,4,false)]=='.' && board[i][getIndex(j,3,false)]=='b' && board[i][getIndex(j,2,false)]=='b' && board[i][getIndex(j,1,false)]=='b' && board[i][j]=='.')
				score+=90;
			else if(board[i][getIndex(j,4,false)]=='b' && board[i][getIndex(j,3,false)]=='b' && board[i][getIndex(j,2,false)]=='b' && board[i][getIndex(j,1,false)]=='b' && board[i][j]=='b')
				score+=1000;
			else if(board[i][getIndex(j,4,false)]=='b' && board[i][getIndex(j,3,false)]=='w' && board[i][getIndex(j,2,false)]=='w' && board[i][getIndex(j,1,false)]=='b')
				score+=100;

		}else if(j-3>=0 && j+1<boardSize){
			if(board[i][getIndex(j,3,false)]=='.' && board[i][getIndex(j,2,false)]=='b' && board[i][getIndex(j,1,false)]=='b' && board[i][j]=='b' && board[i][getIndex(j,1,true)]=='.')
				score+=90;
			else if(board[i][getIndex(j,3,false)]=='b' && board[i][getIndex(j,2,false)]=='b' && board[i][getIndex(j,1,false)]=='b' && board[i][j]=='b' && board[i][getIndex(j,1,true)]=='b')
				score+=1000;
			else if(board[i][getIndex(j,3,false)]=='b' && board[i][getIndex(j,2,false)]=='w' && board[i][getIndex(j,1,false)]=='w' && board[i][j]=='b')
				score+=100;

		}else if(j-2>=0 && j+2<boardSize){
			if(board[i][getIndex(j,2,false)]=='.' && board[i][getIndex(j,1,false)]=='b' && board[i][j]=='b' && board[i][getIndex(j,1,true)]=='b' && board[i][getIndex(j,2,true)]=='.')
				score+=90;
			else if(board[i][getIndex(j,2,false)]=='b' && board[i][getIndex(j,1,false)]=='b' && board[i][j]=='b' && board[i][getIndex(j,1,true)]=='b' && board[i][getIndex(j,2,true)]=='b')
				score+=1000;
			else if(board[i][getIndex(j,2,false)]=='b' && board[i][getIndex(j,1,false)]=='w' && board[i][j]=='w' && board[i][getIndex(j,1,true)]=='b')
				score+=100;

		}else if(j-1>=0 && j+3<boardSize){
			if(board[i][getIndex(j,1,false)]=='.' && board[i][j]=='b' && board[i][getIndex(j,1,true)]=='b' && board[i][getIndex(j,2,true)]=='b' && board[getIndex(i,3,true)][j]=='.')
				score+=90;
			else if(board[i][getIndex(j,1,false)]=='b' && board[i][j]=='b' && board[i][getIndex(j,1,true)]=='b' && board[i][getIndex(j,2,true)]=='b' && board[getIndex(i,3,true)][j]=='b')
				score+=1000;
			else if(board[i][getIndex(j,1,false)]=='b' && board[i][j]=='w' && board[i][getIndex(j,1,true)]=='w' && board[i][getIndex(j,2,true)]=='b')
				score+=100;

		}else if(j+4<boardSize){
			if(board[i][j]=='.' && board[i][getIndex(j,1,true)]=='b' && board[i][getIndex(j,2,true)]=='b' && board[i][getIndex(j,3,true)]=='b' && board[i][getIndex(j,4,true)]=='.')
				score+=90;
			else if(board[i][j]=='b' && board[i][getIndex(j,1,true)]=='b' && board[i][getIndex(j,2,true)]=='b' && board[i][getIndex(j,3,true)]=='b' && board[i][getIndex(j,4,true)]=='b')
				score+=1000;
			else if(board[i][j]=='b' && board[i][getIndex(j,1,true)]=='w' && board[i][getIndex(j,2,true)]=='w' && board[i][getIndex(j,3,true)]=='b')
				score+=100;
		}


		//Diagonal

		if(j-4>=0 && i-4>=0){
			if(board[getIndex(i,4,false)][getIndex(j,4,false)]=='.' && board[getIndex(i,3,false)][getIndex(j,3,false)]=='b' && board[getIndex(i,2,false)][getIndex(j,2,false)]=='b' && board[getIndex(i,1,false)][getIndex(j,1,false)]=='b' && board[i][j]=='.')
				score+=90;
			else if(board[getIndex(i,4,false)][getIndex(j,4,false)]=='b' && board[getIndex(i,3,false)][getIndex(j,3,false)]=='b' && board[getIndex(i,2,false)][getIndex(j,2,false)]=='b' && board[getIndex(i,1,false)][getIndex(j,1,false)]=='b' && board[i][j]=='b')
				score+=1000;
			else if(board[getIndex(i,4,false)][getIndex(j,4,false)]=='b' && board[getIndex(i,3,false)][getIndex(j,3,false)]=='w' && board[getIndex(i,2,false)][getIndex(j,2,false)]=='w' && board[getIndex(i,1,false)][getIndex(j,1,false)]=='b')
				score+=100;

		}else if(j-3>=0 && j+1<boardSize && i-3>=0 && i+1<boardSize){
			if(board[getIndex(i,3,false)][getIndex(j,3,false)]=='.' && board[getIndex(i,2,false)][getIndex(j,2,false)]=='b' && board[getIndex(i,1,false)][getIndex(j,1,false)]=='b' && board[i][j]=='b' && board[getIndex(i,1,true)][getIndex(j,1,true)]=='.')
				score+=90;
			else if(board[getIndex(i,3,false)][getIndex(j,3,false)]=='b' && board[getIndex(i,2,false)][getIndex(j,2,false)]=='b' && board[getIndex(i,1,false)][getIndex(j,1,false)]=='b' && board[i][j]=='b' && board[getIndex(i,1,true)][getIndex(j,1,true)]=='b')
				score+=1000;
			else if(board[getIndex(i,3,false)][getIndex(j,3,false)]=='b' && board[getIndex(i,2,false)][getIndex(j,2,false)]=='w' && board[getIndex(i,1,false)][getIndex(j,1,false)]=='w' && board[i][j]=='b')
				score+=100;

		}else if(j-2>=0 && j+2<boardSize && i-2>=0 && i+2<boardSize){
			if(board[getIndex(i,2,false)][getIndex(j,2,false)]=='.' && board[getIndex(i,1,false)][getIndex(j,1,false)]=='b' && board[i][j]=='b' && board[getIndex(i,1,true)][getIndex(j,1,true)]=='b' && board[getIndex(i,2,true)][getIndex(j,2,true)]=='.')
				score+=90;
			else if(board[getIndex(i,2,false)][getIndex(j,2,false)]=='b' && board[getIndex(i,1,false)][getIndex(j,1,false)]=='b' && board[i][j]=='b' && board[getIndex(i,1,true)][getIndex(j,1,true)]=='b' && board[getIndex(i,2,true)][getIndex(j,2,true)]=='b')
				score+=1000;
			else if(board[getIndex(i,2,false)][getIndex(j,2,false)]=='b' && board[getIndex(i,1,false)][getIndex(j,1,false)]=='w' && board[i][j]=='w' && board[getIndex(i,1,true)][getIndex(j,1,true)]=='b')
				score+=100;

		}else if(j-1>=0 && j+3<boardSize && i-1>=0 && i+3<boardSize){
			if(board[getIndex(i,1,false)][getIndex(j,1,false)]=='.' && board[i][j]=='b' && board[getIndex(i,1,true)][getIndex(j,1,true)]=='b' && board[getIndex(i,2,true)][getIndex(j,2,true)]=='b' && board[getIndex(i,3,true)][getIndex(j,3,true)]=='.')
				score+=90;
			else if(board[getIndex(i,1,false)][getIndex(j,1,false)]=='b' && board[i][j]=='b' && board[getIndex(i,1,true)][getIndex(j,1,true)]=='b' && board[getIndex(i,2,true)][getIndex(j,2,true)]=='b' && board[getIndex(i,3,true)][getIndex(j,3,true)]=='b')
				score+=1000;
			else if(board[getIndex(i,1,false)][getIndex(j,1,false)]=='b' && board[i][j]=='w' && board[getIndex(i,1,true)][getIndex(j,1,true)]=='w' && board[getIndex(i,2,true)][getIndex(j,2,true)]=='b')
				score+=100;

		}else if(j+4<boardSize && i+4<boardSize){
			if(board[i][j]=='.' && board[getIndex(i,1,true)][getIndex(j,1,true)]=='b' && board[getIndex(i,2,true)][getIndex(j,2,true)]=='b' && board[getIndex(i,3,true)][getIndex(j,3,true)]=='b' && board[getIndex(i,4,true)][getIndex(j,4,true)]=='.')
				score+=90;
			else if(board[i][j]=='b' && board[getIndex(i,1,true)][getIndex(j,1,true)]=='b' && board[getIndex(i,2,true)][getIndex(j,2,true)]=='b' && board[getIndex(i,3,true)][getIndex(j,3,true)]=='b' && board[getIndex(i,4,true)][getIndex(j,4,true)]=='b')
				score+=1000;
			else if(board[i][j]=='b' && board[getIndex(i,1,true)][getIndex(j,1,true)]=='w' && board[getIndex(i,2,true)][getIndex(j,2,true)]=='w' && board[getIndex(i,3,true)][getIndex(j,3,true)]=='b')
				score+=100;
		}



		//Diagonal

		if(j-4>=0 && i+4<boardSize){
			if(board[getIndex(i,4,true)][getIndex(j,4,false)]=='.' && board[getIndex(i,3,true)][getIndex(j,3,false)]=='b' && board[getIndex(i,2,true)][getIndex(j,2,false)]=='b' && board[getIndex(i,1,true)][getIndex(j,1,false)]=='b' && board[i][j]=='.')
				score+=90;
			else if(board[getIndex(i,4,true)][getIndex(j,4,false)]=='b' && board[getIndex(i,3,true)][getIndex(j,3,false)]=='b' && board[getIndex(i,2,true)][getIndex(j,2,false)]=='b' && board[getIndex(i,1,true)][getIndex(j,1,false)]=='b' && board[i][j]=='b')
				score+=1000;
			else if(board[getIndex(i,4,true)][getIndex(j,4,false)]=='b' && board[getIndex(i,3,true)][getIndex(j,3,false)]=='w' && board[getIndex(i,2,true)][getIndex(j,2,false)]=='w' && board[getIndex(i,1,true)][getIndex(j,1,false)]=='b')
				score+=100;

		}else if(j-3>=0 && j+1<boardSize && i+3<boardSize && i-1>=0){
			if(board[getIndex(i,3,true)][getIndex(j,3,false)]=='.' && board[getIndex(i,2,true)][getIndex(j,2,false)]=='b' && board[getIndex(i,1,true)][getIndex(j,1,false)]=='b' && board[i][j]=='b' && board[getIndex(i,1,false)][getIndex(j,1,true)]=='.')
				score+=90;
			else if(board[getIndex(i,3,true)][getIndex(j,3,false)]=='b' && board[getIndex(i,2,true)][getIndex(j,2,false)]=='b' && board[getIndex(i,1,true)][getIndex(j,1,false)]=='b' && board[i][j]=='b' && board[getIndex(i,1,false)][getIndex(j,1,true)]=='b')
				score+=1000;
			else if(board[getIndex(i,3,true)][getIndex(j,3,false)]=='b' && board[getIndex(i,2,true)][getIndex(j,2,false)]=='w' && board[getIndex(i,1,true)][getIndex(j,1,false)]=='w' && board[i][j]=='b')
				score+=100;

		}else if(j-2>=0 && j+2<boardSize && i+2<boardSize && i-2>=0){
			if(board[getIndex(i,2,true)][getIndex(j,2,false)]=='.' && board[getIndex(i,1,true)][getIndex(j,1,false)]=='b' && board[i][j]=='b' && board[getIndex(i,1,false)][getIndex(j,1,true)]=='b' && board[getIndex(i,2,false)][getIndex(j,2,true)]=='.')
				score+=90;
			else if(board[getIndex(i,2,true)][getIndex(j,2,false)]=='b' && board[getIndex(i,1,true)][getIndex(j,1,false)]=='b' && board[i][j]=='b' && board[getIndex(i,1,false)][getIndex(j,1,true)]=='b' && board[getIndex(i,2,false)][getIndex(j,2,true)]=='b')
				score+=1000;
			else if(board[getIndex(i,2,true)][getIndex(j,2,false)]=='b' && board[getIndex(i,1,true)][getIndex(j,1,false)]=='w' && board[i][j]=='w' && board[getIndex(i,1,false)][getIndex(j,1,true)]=='b')
				score+=100;

		}else if(j-1>=0 && j+3<boardSize && i+1<boardSize && i-3>=0){
			if(board[getIndex(i,1,true)][getIndex(j,1,false)]=='.' && board[i][j]=='b' && board[getIndex(i,1,false)][getIndex(j,1,true)]=='b' && board[getIndex(i,2,false)][getIndex(j,2,true)]=='b' && board[getIndex(i,3,false)][getIndex(j,3,true)]=='.')
				score+=90;
			else if(board[getIndex(i,1,true)][getIndex(j,1,false)]=='b' && board[i][j]=='b' && board[getIndex(i,1,false)][getIndex(j,1,true)]=='b' && board[getIndex(i,2,false)][getIndex(j,2,true)]=='b' && board[getIndex(i,3,false)][getIndex(j,3,true)]=='b')
				score+=1000;
			else if(board[getIndex(i,1,true)][getIndex(j,1,false)]=='b' && board[i][j]=='w' && board[getIndex(i,1,false)][getIndex(j,1,true)]=='w' && board[getIndex(i,2,false)][getIndex(j,2,true)]=='b')
				score+=100;

		}else if(j+4<boardSize && i-4>=0){
			if(board[i][j]=='.' && board[getIndex(i,1,false)][getIndex(j,1,true)]=='b' && board[getIndex(i,2,false)][getIndex(j,2,true)]=='b' && board[getIndex(i,3,false)][getIndex(j,3,true)]=='b' && board[getIndex(i,4,false)][getIndex(j,4,true)]=='.')
				score+=90;
			else if(board[i][j]=='b' && board[getIndex(i,1,false)][getIndex(j,1,true)]=='b' && board[getIndex(i,2,false)][getIndex(j,2,true)]=='b' && board[getIndex(i,3,false)][getIndex(j,3,true)]=='b' && board[getIndex(i,4,false)][getIndex(j,4,true)]=='b')
				score+=1000;
			else if(board[i][j]=='b' && board[getIndex(i,1,false)][getIndex(j,1,true)]=='w' && board[getIndex(i,2,false)][getIndex(j,2,true)]=='w' && board[getIndex(i,3,false)][getIndex(j,3,true)]=='b')
				score+=100;
		}


		
	}
	return score;

}

int evaluate(string board[19],vpii moves,string playerString){
	
	int playerScore = 0;
    int opponentScore = 0;


    sort(moves.begin(),moves.end(),cmp);

    pii tempRowScore = finalRowScore;

    char player = playerString=="WHITE"?'w':'b';


    // Calibrate Row Score
    int rowWeight=5;
    for(int p=0;p<moves.size();p++){

    	int i=moves[p].first,j=moves[p].second;

    	for(int k=1;k<4;k++){
    		if(j-k>=0){
    			if(board[i][getIndex(j,k,false)]==player){
    				if(player=='w'){
    					tempRowScore.first+=pow(5,k);
    					tempRowScore.second-=pow(5,k);
    				}else if(player!='.'){
    					tempRowScore.first-=pow(5,k);
    					tempRowScore.second+=pow(5,k);
    				}
    				
    			}else
    				break;
    		}

    		if(i-k>=0){
    			if(board[getIndex(i,k,false)][j]==player){
    				if(player=='w'){
    					tempRowScore.first+=pow(5,k);
    					tempRowScore.second-=pow(5,k);
    				}else if(player!='.'){
    					tempRowScore.first-=pow(5,k);
    					tempRowScore.second+=pow(5,k);
    				}
    			}else
    				break;
    		}

    		if(i-k>=0 && j-k>=0){
    			if(board[getIndex(i,k,false)][getIndex(j,k,false)]==player){
    				if(player=='w'){
    					tempRowScore.first+=pow(5,k);
    					tempRowScore.second-=pow(5,k);
    				}else if(player!='.'){
    					tempRowScore.first-=pow(5,k);
    					tempRowScore.second+=pow(5,k);
    				}
    			}else
    				break;
    		}


    		if(i-k>=0 && j+k<boardSize){
    			if(board[getIndex(i,k,false)][getIndex(j,k,true)]==player){
    				if(player=='w'){
    					tempRowScore.first+=pow(5,k);
    					tempRowScore.second-=pow(5,k);
    				}else if(player!='.'){
    					tempRowScore.first-=pow(5,k);
    					tempRowScore.second+=pow(5,k);
    				}
    			}else
    				break;
    		}

    	}
    }

    // Calibrate Control Score // not required


    // Calibrate Threat Score
    pii tempThreatScore = finalThreatScore;
	for(int p=0;p<moves.size();p++){
		
    	int i=moves[p].first,j=moves[p].second;


    	for(int k=1;k<4;k++){
    		if(j-k>=0){
    			if(board[i][getIndex(j,k,false)]=='w'){

    				if(player=='w'){
    					tempThreatScore.first+=pow(10,k);
    					tempThreatScore.second-=pow(10,k);
    				}else if(player!='.'){
    					tempThreatScore.first-=pow(10,k);
    					tempThreatScore.second+=pow(10,k);
    				}
    			}else
    				break;
    		}

    		if(i-k>=0){
    			if(board[getIndex(i,k,false)][j]=='w'){
    				if(player=='w'){
    					tempThreatScore.first+=pow(10,k);
    					tempThreatScore.second-=pow(10,k);
    				}else if(player!='.'){
    					tempThreatScore.first-=pow(10,k);
    					tempThreatScore.second+=pow(10,k);
    				}
    			}else
    				break;
    		}

    		if(i-k>=0 && j-k>=0){
    			if(board[getIndex(i,k,false)][getIndex(j,k,false)]=='w'){
    				if(player=='w'){
    					tempThreatScore.first+=pow(10,k);
    					tempThreatScore.second-=pow(10,k);
    				}else if(player!='.'){
    					tempThreatScore.first-=pow(10,k);
    					tempThreatScore.second+=pow(10,k);
    				}
    			}else
    				break;
    		}


    		if(i-k>=0 && j+k<boardSize){
    			if(board[getIndex(i,k,false)][getIndex(j,k,true)]=='w'){
    				if(player=='w'){
    					tempThreatScore.first+=pow(10,k);
    					tempThreatScore.second-=pow(10,k);
    				}else if(player!='.'){
    					tempThreatScore.first-=pow(10,k);
    					tempThreatScore.second+=pow(10,k);
    				}
    			}else
    				break;
    		}

    	}
    }    


    if(playerString=="WHITE"){
    	playerScore=tempRowScore.first;
		opponentScore=tempRowScore.second;
		opponentScore+=tempThreatScore.second;
    }else{
    	playerScore=tempRowScore.second;
		opponentScore=tempRowScore.first;
		opponentScore+=tempThreatScore.first;
    }

	// Balance offense and defense
    int scoreDiff = playerScore - opponentScore;
    if (scoreDiff > 0 && opponentScore == 0) {
        // Prioritize offense if the opponent has no score
        playerScore += scoreDiff / 2;
    } else if (scoreDiff < 0 && playerScore == 0) {
        // Prioritize defense if the player has no score
        opponentScore -= scoreDiff / 2;
    }
    
    return playerScore - opponentScore;

}



bool DoIHaveAdvantage(string board[boardSize],int i,int j,string player){
	char p = player=="WHITE"?'w':'b';


	if(i-2>=0 && i+3<boardSize){
		if(board[getIndex(i,2,false)][j]=='.' && board[getIndex(i,1,false)][j]==p && board[getIndex(i,1,true)][j]=='.' && board[getIndex(i,2,true)][j]==p && board[getIndex(i,3,true)][j]=='.')
			return true;
	}
	if(j-2>=0 && j+3<boardSize){
		if(board[i][getIndex(j,2,false)]=='.' && board[i][getIndex(j,1,false)]==p && board[i][getIndex(j,1,true)]=='.' && board[i][getIndex(j,2,true)]==p && board[i][getIndex(j,3,true)]=='.')
			return true;
	}
	if(j-2>=0 && j+3<boardSize && i-2>=0 && i+3<boardSize){
		if(board[getIndex(i,2,false)][getIndex(j,2,false)]=='.' && board[getIndex(i,1,false)][getIndex(j,1,false)]==p && board[getIndex(i,1,true)][getIndex(j,1,true)]=='.' && board[getIndex(i,2,true)][getIndex(j,2,true)]==p && board[getIndex(i,3,true)][getIndex(j,3,true)]=='.')
			return true;
	}
	if(j-2>=0 && j+3<boardSize && i+3<boardSize && i-2>=0){
		if(board[getIndex(i,2,true)][getIndex(j,2,false)]=='.' && board[getIndex(i,1,true)][getIndex(j,1,false)]==p && board[getIndex(i,1,false)][getIndex(j,1,true)]=='.' && board[getIndex(i,2,false)][getIndex(j,2,true)]==p && board[getIndex(i,3,false)][getIndex(j,3,true)]=='.')
			return true;
	}



	return false;

}


bool OneMoveAway(string board[boardSize],int i,int j,string player){
	char p = player=="WHITE"?'w':'b';

	if(i-3>=0 && i+2<boardSize){
		if(board[getIndex(i,3,false)][j]=='.' && board[getIndex(i,2,false)][j]==p && board[getIndex(i,1,false)][j]==p && board[getIndex(i,1,true)][j]==p && board[getIndex(i,2,true)][j]=='.')
			return true;
	}
	if(j-3>=0 && j+2<boardSize){
		if(board[i][getIndex(j,3,false)]=='.' && board[i][getIndex(j,2,false)]==p && board[i][getIndex(j,1,false)]==p && board[i][getIndex(j,1,true)]==p && board[i][getIndex(j,2,true)]=='.')
			return true;
	}
	if(j-3>=0 && j+2<boardSize && i-3>=0 && i+2<boardSize){
		if(board[getIndex(i,3,false)][getIndex(j,3,false)]=='.' && board[getIndex(i,2,false)][getIndex(j,2,false)]==p && board[getIndex(i,1,false)][getIndex(j,1,false)]==p && board[getIndex(i,1,true)][getIndex(j,1,true)]==p && board[getIndex(i,2,true)][getIndex(j,2,true)]=='.')
			return true;
	}
	if(j-3>=0 && j+2<boardSize && i+3<boardSize && i-2>=0){
		if(board[getIndex(i,3,true)][getIndex(j,3,false)]=='.' && board[getIndex(i,2,true)][getIndex(j,2,false)]==p && board[getIndex(i,1,true)][getIndex(j,1,false)]==p && board[getIndex(i,1,false)][getIndex(j,1,true)]==p && board[getIndex(i,2,false)][getIndex(j,2,true)]=='.')
			return true;
	}


	/******************************************/

	if(i-2>=0 && i+3<boardSize){
		if(board[getIndex(i,2,false)][j]=='.' && board[getIndex(i,1,false)][j]==p && board[getIndex(i,1,true)][j]==p && board[getIndex(i,2,true)][j]==p && board[getIndex(i,3,true)][j]=='.')
			return true;
	}
	if(j-2>=0 && j+3<boardSize){
		if(board[i][getIndex(j,2,false)]=='.' && board[i][getIndex(j,1,false)]==p && board[i][getIndex(j,1,true)]==p && board[i][getIndex(j,2,true)]==p && board[i][getIndex(j,3,true)]=='.')
			return true;
	}
	if(j-2>=0 && j+3<boardSize && i-2>=0 && i+3<boardSize){
		if(board[getIndex(i,2,false)][getIndex(j,2,false)]=='.' && board[getIndex(i,1,false)][getIndex(j,1,false)]==p && board[getIndex(i,1,true)][getIndex(j,1,true)]==p && board[getIndex(i,2,true)][getIndex(j,2,true)]==p && board[getIndex(i,3,true)][getIndex(j,3,true)]=='.')
			return true;
	}
	if(j-2>=0 && j+3<boardSize && i+2<boardSize && i-3>=0){
		if(board[getIndex(i,2,true)][getIndex(j,2,false)]=='.' && board[getIndex(i,1,true)][getIndex(j,1,false)]==p && board[getIndex(i,2,true)][getIndex(j,2,false)]==p && board[getIndex(i,2,false)][getIndex(j,2,true)]==p && board[getIndex(i,3,false)][getIndex(j,3,true)]=='.')
			return true;
	}



	/***********************************/



	if(i+4<boardSize){
		if(board[getIndex(i,1,true)][j]==p && board[getIndex(i,2,true)][j]==p && board[getIndex(i,3,true)][j]==p && board[getIndex(i,4,true)][j]=='.')
			return true;
	}
	if(j+4<boardSize){
		if(board[i][getIndex(j,1,true)]==p && board[i][getIndex(j,2,true)]==p && board[i][getIndex(j,3,true)]==p && board[i][getIndex(j,4,true)]=='.')
			return true;
	}
	if(j+4<boardSize && i+4<boardSize){
		if(board[getIndex(i,1,true)][getIndex(j,1,true)]==p && board[getIndex(i,2,true)][getIndex(j,2,true)]==p && board[getIndex(i,3,true)][getIndex(j,3,true)]==p && board[getIndex(i,4,true)][getIndex(j,4,true)]=='.')
			return true;
	}
	if(j+4<boardSize && i-4>=0){
		if(board[getIndex(i,1,false)][getIndex(j,1,true)]==p && board[getIndex(i,2,false)][getIndex(j,2,true)]==p && board[getIndex(i,3,false)][getIndex(j,3,true)]==p && board[getIndex(i,4,false)][getIndex(j,4,true)]=='.')
			return true;
	}


	return false;	

}



pipii alphabeta(string board[boardSize], int depth, string playerString, int alpha, int beta,vpii moves,bool isMyTurn,int x,int y) {
    if (depth == 0) {
        return make_pair(evaluate(board,moves,playerString),make_pair(-1,-1)); 
        // return make_pair(0,make_pair(-1,-1));   
    }

    pipii bestMove = make_pair(INT_MIN,make_pair(-1,-1));

    char player = playerString=="WHITE"?'w':'b';
    string opponent = player=='w'?"BLACK":"WHITE";

    for(int i=isMyTurn?x*playerBoardSize:0;i<(isMyTurn?(x+1)*playerBoardSize:boardSize);i++){
    	for(int j=isMyTurn?y*playerBoardSize:0;j<(isMyTurn?(y+1)*playerBoardSize:boardSize);j++){
    	
    		
    		if(board[i][j]=='.'){
    			board[i][j]=player;
    			moves.push_back(make_pair(i,j));
    			pipii newMove= alphabeta(board, depth - 1, opponent, -beta, -alpha,moves,!isMyTurn,x,y);


				int score = -newMove.first;

				/*********************************/

				score = score + 10000 * canIMakeIT(board,i,j,playerString) + 1000 * OneMoveAway(board,i,j,playerString) + 90 * DoIHaveAdvantage(board,i,j,playerString);
				


				/*******************************/

    			
    			board[i][j]='.';
    			

    			

    			if(playerString=="WHITE")
    				score+=completeControlScore[i][j].first;
    			else
    				score+=completeControlScore[i][j].second;

				moves.pop_back();
		        if (score > bestMove.first) {
		        	bestMove = make_pair(score,make_pair(i,j));
		            alpha = max(alpha, score);
		            if (alpha >= beta) {
		                break;
		            }
		        }

    		}
    	}
    }

    return bestMove;
}



pipii minMax(string board[boardSize], int depth, string playerString, int alpha, int beta,vpii moves) {
    if (depth == 0) {   
        return make_pair(evaluate(board,moves,playerString),make_pair(-1,-1));    
    }

    pipii bestMove = make_pair(INT_MIN,make_pair(-1,-1));

    char player = playerString=="WHITE"?'w':'b';
    string opponent = player=='w'?"BLACK":"WHITE";

    for(int i=0;i<boardSize;i++){
    	for(int j=0;j<boardSize;j++){
    		
    		if(board[i][j]=='.'){
    			board[i][j]=player;
    			moves.push_back(make_pair(i,j));
    			pipii newMove= minMax(board, depth - 1, opponent, -beta, -alpha,moves);

    			int score = -newMove.first;
    			if(playerString=="WHITE"){
					score += getSpecialScore(board,moves,true,i,j);
				}else{
					score += getSpecialScore(board,moves,false,i,j);
				}

    			moves.pop_back();
    			board[i][j]='.';

    			

    			if(playerString=="WHITE")
    				score+=completeControlScore[i][j].first;
    			else
    				score+=completeControlScore[i][j].second;

		        if (score > bestMove.first) {
		        	bestMove = make_pair(score,make_pair(i,j));
		            alpha = max(alpha, score);
		            if (alpha >= beta) {
		                break;
		            }
		        }

    		}
    	}
    }

    return bestMove;
}


vpipii canCapture(string board[boardSize],string player){
	vector<pipii> res;

	char p = player=="WHITE"?'w':'b';
	char o = p=='w'?'b':'w';


	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			if(board[i][j]=='.'){
				int cnt=0;
				
				if(i+3<boardSize){
					if(board[getIndex(i,1,true)][j]==o && board[getIndex(i,2,true)][j]==o && board[getIndex(i,3,true)][j]==p)
						cnt++;
				}
				
				if(i-3>=0){
					if(board[getIndex(i,1,false)][j]==o && board[getIndex(i,2,false)][j]==o && board[getIndex(i,3,false)][j]==p)
						cnt++;
				}

				if(j+3<boardSize){
					if(board[i][getIndex(j,1,true)]==o && board[i][getIndex(j,2,true)]==o && board[i][getIndex(j,3,true)]==p)
						cnt++;	
				}

				if(j-3>=0){
					if(board[i][getIndex(j,1,false)]==o && board[i][getIndex(j,2,false)]==o && board[i][getIndex(j,3,false)]==p)
						cnt++;	
				}

				if(j+3<boardSize && i+3<boardSize){
					if(board[getIndex(i,1,true)][getIndex(j,1,true)]==o && board[getIndex(i,2,true)][getIndex(j,2,true)]==o && board[getIndex(i,3,true)][getIndex(j,3,true)]==p)
						cnt++;	
				}

				if(j-3>=0 && i-3>=0){
					if(board[getIndex(i,1,false)][getIndex(j,1,false)]==o && board[getIndex(i,2,false)][getIndex(j,2,false)]==o && board[getIndex(i,3,false)][getIndex(j,3,false)]==p)
						cnt++;	
				}

				if(j+3<boardSize && i-3>=0){
					if(board[getIndex(i,1,false)][getIndex(j,1,true)]==o && board[getIndex(i,2,false)][getIndex(j,2,true)]==o && board[getIndex(i,3,false)][getIndex(j,3,true)]==p)
						cnt++;	
				}

				if(j-3>=0 && i+3<boardSize){
					if(board[getIndex(i,1,true)][getIndex(j,1,false)]==o && board[getIndex(i,2,true)][getIndex(j,2,false)]==o && board[getIndex(i,3,true)][getIndex(j,3,false)]==p)
						cnt++;	
				}

				if(cnt){
					res.push_back(make_pair(cnt,make_pair(i,j)));
				}				

			}
		}
	}
	

	sort(res.begin(),res.end(), greater<pipii>());

	return res;

}




int main(){
	ifstream inputFile("input.txt");
	string line;

	getline(inputFile,line);
	string player = line;

	getline(inputFile,line);
	float timeLeft=stof(line);

	getline(inputFile,line);
	vector<int>captured = split(line);

	string board[19];

	for(int i=0;i<19;i++){
		getline(inputFile,line);
		board[18-i]=line;
	}

	inputFile.close();

	ifstream playDataFile("playdata.txt");
	// cout<<player;
	if(playDataFile){
		// Do something
	}
	if(player=="WHITE"){
		
		int count=0;
		int x,y;

		for(int i=0;i<19;i++){
			for(int j=0;j<19;j++){
				if(board[i][j]=='w')
					count++;
				else if(board[i][j]=='b')
					x=i,y=j;
			}
		}

		if(count==0){
			Output(10,10);
			return 0;
		}else if(count==1){
			if(x>10)
				x=7;
			else
				x=13;
			if(y>10)
				y=7;
			else
				y=13;

			Output(x,y);
			return 0;
		}
	}else{
		int count=0;
		int x,y;

		for(int i=0;i<19;i++){
			for(int j=0;j<19;j++){
				if(board[i][j]=='b')
					count++;
			}
		}
		if(count==0){
			Output(11,11);
			return 0;
		}
	}

	

	string opponent = player=="WHITE"?"BLACK":"WHITE";
	
	int rowC=-1,colC=-1,rowS=-1,colS=-1;

	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			if(board[i][j]=='.'){
				bool canI=false,shouldI=false;
				canI=canIMakeIT(board,i,j,player);
				shouldI = canIMakeIT(board,i,j,opponent);
				if(canI && shouldI){
					rowC=i,colC=j;
					rowS=-1;
					break;
				}else if(canI){
					rowC=i,colC=j;
					break;
				}
				else if(shouldI){
					rowS=i,colS=j;
					break;
				}
			}
		}
	}
	if(rowC!=-1){
		Output(rowC+1,colC+1);
		return 0;
	}else if(rowS!=-1){
		Output(rowS+1,colS+1);
		return 0;
	}
	

	// Write Function


	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			if(board[i][j]=='.'){
				if(OneMoveAway(board,i,j,player)){
					Output(i+1,j+1);
					return 0;
				}
			}
		}
	}
	

	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			if(board[i][j]=='.'){
				if(OneMoveAway(board,i,j,opponent)){
					Output(i+1,j+1);
					return 0;
				}
			}
		}
	}	


	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			if(board[i][j]=='.'){
				if(DoIHaveAdvantage(board,i,j,player)){
					Output(i+1,j+1);
					return 0;
				}
			}
		}
	}

	
	
	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			if(board[i][j]=='.'){
				if(DoIHaveAdvantage(board,i,j,opponent)){
					Output(i+1,j+1);
					return 0;
				}
			}
		}
	}

	

	


	vector<pipii>canICapture = canCapture(board,player);


	if(canICapture.size()>0){
		Output(canICapture[0].second.first+1,canICapture[0].second.second+1);
		return 0;
	}

	canICapture = canCapture(board,opponent);
	if(canICapture.size()>0){
		Output(canICapture[0].second.first+1,canICapture[0].second.second+1);
		return 0;
	}




	// vector<pipii>canICapture = canICaptureFunction(board,player);
	// vector<pipii>defend = canOpponentCapture(board,player);

	// if(canICapture.size()>0){
	// 	if(defend.size()>0){
			
	// 		if(canICapture[0].first>=defend[0].first){
	// 			cout<<"djhfghf1\n";
	// 			Output(canICapture[0].second.first+1,canICapture[0].second.second+1);
	// 		}else{
	// 			cout<<"djhfghf2\n";
	// 			Output(defend[0].second.first+1,defend[0].second.second+1);
	// 		}
	// 		return 0;
	// 	}
	// 	cout<<"djhfgh3\n";
	// 	Output(canICapture[0].second.first+1,canICapture[0].second.second+1);
	// 	return 0;
	// }else if(defend.size()>0){
	// 	cout<<"djhfghf4\n";
	// 	Output(defend[0].second.first+1,defend[0].second.second+1);
	// 	return 0;
	// }


	// cout<<"djh2335\n";
	


	


	// create AI agent

	completeRowScore = getRowScores(board);
	completeControlScore = getControlScores(board);
	completeThreatScore = getThreatScores(board);


	finalRowScore = getScore(completeRowScore);
	finalThreatScore = getScore(completeThreatScore);




	/***************************************************/
	if(timeLeft<15){
		vpii moves;
		pipii move = minMax(board, 2, player,INT_MIN,INT_MAX,moves);
		Output(move.second.first+1,move.second.second+1);
		return 0;
	}else if(timeLeft<1.5){
		vpii moves;
		pipii move = minMax(board, 1, player,INT_MIN,INT_MAX,moves);
		Output(move.second.first+1,move.second.second+1);
		return 0;
	}else if(timeLeft<0.3){
		for(int i=0;i<19;i++){
			for(int j=0;j<19;j++){
				if(board[i][j]=='.'){
					Output(i+1,j+1);
					return 0;	
				}					
			}
		}
	}

	/***************************************************/	

	vpipii allMoves;

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			vpii moves;
			pipii move = alphabeta(board, 3, player,INT_MIN,INT_MAX,moves,true,i,j);	
			allMoves.push_back(move);
		}
	}


	int row=-1,col=-1,score=INT_MIN;

	for(int i=0;i<allMoves.size();i++){
		
		if(allMoves[i].first>score){
			if(allMoves[i].second.first!=-1 && allMoves[i].second.second!=-1){
				row = allMoves[i].second.first;
				col = allMoves[i].second.second;
				
				score=allMoves[i].first;
			}
		}
	}
	
	if(row==-1 || col==-1){
		for(int i=0;i<19;i++){
			for(int j=0;j<19;j++){
				if(board[i][j]=='.'){
					row=i;
					col=j;
					break;
				}
			}
		}
	}


	Output(row+1,col+1);
		


	return 0;
}



