#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <cmath>
#include <utility>
#include <stack>
#include <cassert>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

#define UP 0
#define UP_RIGHT 1
#define RIGHT 2
#define DOWN_RIGHT 3
#define DOWN 4
#define DOWN_LEFT 5
#define LEFT 6
#define UP_LEFT 7
int dep1;
int dep2;
int val_puz[6][6];
pair<int , int > memo_white[30] , memo_dark[30];
pair<int , int > best ,best2,best3;
char puz [6][6];
char fak [6][6];
void con(string ap){
	int i , j ; 
	for (i = 0 ; i < 6 ;i++){
		for (j = 0 ; j < 6 ; j ++ ){
			puz[i][j] = ap[i * 6 + j] ; 
		}
	}
}
pair<int,int> findplace(string ap){
	int x , y;
	pair<int , int > p1 ;
	switch(ap[0]){
   		case 'A' :
      		x = 0;
      		break;
      	case 'B' :
      		x = 1;
      		break;
      	case 'C' :
      		x = 2;
      		break;
		case 'D' :
      		x = 3;
			break;	
		case 'E' :
			x = 4;
			break;
		case 'F' :
      		x = 5;
      		break;
  }
  switch(ap[1]){
   		case 'a' :
      		y = 0;
      		break;
      	case 'b' :
      		y = 1;
      		break;
      	case 'c' :
      		y = 2;
      		break;
		case 'd' :
      		y = 3;
			break;	
		case 'e' :
			y = 4;
			break;
		case 'f' :
      		y = 5;
      		break;
  }
  p1.first = x ;
  p1.second = y ;
  return p1;
}
string decon(int f){
	int i , j ; 
	string ap;
	for (i = 0 ; i < 6 ;i++){
		for (j = 0 ; j < 6 ; j ++ ){
			if (f == 1)
				ap += puz[i][j]; 
			else 
				ap += fak[i][j];
		}
	}
	return ap;
}

int find_valid(int color , int dir , pair<int , int > p1 ){
	int count = 0;
	char de ;
	if (color == 1)
		de = 'X';
	else 
		de = 'O';
	if (puz[p1.first][p1.second] == 'X' || puz[p1.first][p1.second] == 'O')
		return count;
	else {
		if (dir == UP){
			while(1){
				if (p1.first-1 < 0){
					count = 0 ; 
					break;
				}
				if (puz[p1.first-1][p1.second] == de){
					break;
				}
				else if((puz[p1.first-1][p1.second] == '+')) {
					count = 0 ;
					break;
				}
				else{
					count ++; 
					p1.first--;
				}
			}
		}
		else if (dir == UP_RIGHT){
			while(1){
				if (p1.first-1 < 0 || p1.second+1 >= 6 ){
					count = 0 ; 
					break;
				}
				if (puz[p1.first-1][p1.second+1] == de){
					break;
				}
				else if((puz[p1.first-1][p1.second+1] == '+')) {
					count = 0 ;
					break;
				}
				else{
					count ++; 
					p1.first--;
					p1.second++;
				}
			}
		}
		else if (dir == RIGHT){
			while(1){
				if (p1.second+1 >= 6 ){
					count = 0 ; 
					break;
				}
				if (puz[p1.first][p1.second+1] == de){
					break;
				}
				else if((puz[p1.first][p1.second+1] == '+')) {
					count = 0 ;
					break;
				}
				else{
					count ++; 
					p1.second++;
				}
			}
		}
		else if (dir == DOWN_RIGHT){
			while(1){
				if (p1.first+1 >= 6 || p1.second+1 >= 6 ){
					count = 0 ; 
					break;
				}
				if (puz[p1.first+1][p1.second+1] == de){
					break;
				}
				else if((puz[p1.first+1][p1.second+1] == '+')) {
					count = 0 ;
					break;
				}
				else{
					count ++; 
					p1.first++;
					p1.second++;
				}
			}
		}
		else if (dir == DOWN){
			while(1){
				if (p1.first+1 >= 6){
					count = 0 ; 
					break;
				}
				if (puz[p1.first+1][p1.second] == de){
					break;
				}
				else if((puz[p1.first+1][p1.second] == '+')) {
					count = 0 ;
					break;
				}
				else{
					count ++; 
					p1.first++;
				}
			}
		}
		else if (dir == DOWN_LEFT){
			while(1){
				if (p1.first+1 >= 6 || p1.second-1 < 0 ){
					count = 0 ; 
					break;
				}
				if (puz[p1.first+1][p1.second-1] == de){
					break;
				}
				else if((puz[p1.first+1][p1.second-1] == '+')) {
					count = 0 ;
					break;
				}
				else{
					count ++; 
					p1.first++;
					p1.second--;
				}
			}
		}
		else if (dir == LEFT){
			while(1){
				if ( p1.second-1 < 0 ){
					count = 0 ; 
					break;
				}
				if (puz[p1.first][p1.second-1] == de){
					
					break;
				}
				else if((puz[p1.first][p1.second-1] == '+')) {
					count = 0 ;
					break;
				}
				else{
					
					count ++; 
					p1.second--;
				}
			}
		}
		else if (dir == UP_LEFT){
			while(1){
				if (p1.first-1 < 0 || p1.second-1 < 0 ){
					count = 0 ; 
					break;
				}
				if (puz[p1.first-1][p1.second-1] == de){
					break;
				}
				else if((puz[p1.first-1][p1.second-1] == '+')) {
					count = 0 ;
					break;
				}
				else{
					count ++; 
					p1.first--;
					p1.second--;
				}
			}
		}
	}	
	return count;	
}

void flip(int color , int dir , pair<int , int > p1){
	char de ;
	if (color == 1)
		de = 'X';
	else 
		de = 'O';
	if (dir == UP){
		while(1){
			if (p1.first-1 < 0){
				break;
			}
			if (puz[p1.first-1][p1.second] == de){
				break;
			}
			else if((puz[p1.first-1][p1.second] == '+')) {
			
				break;
			}
			else{
				puz[p1.first-1][p1.second] = de;
				p1.first--;
			}
		}
	}
	else if (dir == UP_RIGHT){
		while(1){
			if (p1.first-1 < 0 || p1.second+1 >= 6 ){
			 
				break;
			}
			if (puz[p1.first-1][p1.second+1] == de){
				break;
			}
			else if((puz[p1.first-1][p1.second+1] == '+')) {
				
				break;
			}
			else{
				puz[p1.first-1][p1.second+1] = de; 
				p1.first--;
				p1.second++;
			}
		}
	}
	else if (dir == RIGHT){
		while(1){
			if (p1.second+1 >= 6 ){
			
				break;
			}
			if (puz[p1.first][p1.second+1] == de){
				break;
			}
			else if((puz[p1.first][p1.second+1] == '+')) {
			
				break;
			}
			else{
				puz[p1.first][p1.second+1] = de; 
				p1.second++;
			}
		}
	}
	else if (dir == DOWN_RIGHT){
		while(1){
			if (p1.first+1 >= 6 || p1.second+1 >= 6 ){
				
				break;
			}
			if (puz[p1.first+1][p1.second+1] == de){
				break;
			}
			else if((puz[p1.first+1][p1.second+1] == '+')) {
				
				break;
			}
			else{
				puz[p1.first+1][p1.second+1] = de; 
				p1.first++;
				p1.second++;
			}
		}
	}
	else if (dir == DOWN){
		while(1){
			if (p1.first+1 >= 6){
				
				break;
			}
			if (puz[p1.first+1][p1.second] == de){
				break;
			}
			else if((puz[p1.first+1][p1.second] == '+')) {
			
				break;
			}
			else{
				puz[p1.first+1][p1.second] = de; 
				p1.first++;
			}
		}
	}
	else if (dir == DOWN_LEFT){
		while(1){
			if (p1.first+1 >= 6 || p1.second-1 < 0 ){
			
				break;
			}
			if (puz[p1.first+1][p1.second-1] == de){
				break;
			}
			else if((puz[p1.first+1][p1.second-1] == '+')) {
			
				break;
			}
			else{
				puz[p1.first+1][p1.second-1] = de; 
				p1.first++;
				p1.second--;
			}
		}
	}
	else if (dir == LEFT){
		while(1){
			if ( p1.second-1 < 0 ){
			 
				break;
			}
			if (puz[p1.first][p1.second-1] == de){
				
				break;
			}
			else if((puz[p1.first][p1.second-1] == '+')) {
			
				break;
			}
			else{
				puz[p1.first][p1.second-1] = de;
				p1.second--;
			}
		}
	}
	else if (dir == UP_LEFT){
		while(1){
			if (p1.first-1 < 0 || p1.second-1 < 0 ){
			
				break;
			}
			if (puz[p1.first-1][p1.second-1] == de){
				break;
			}
			else if((puz[p1.first-1][p1.second-1] == '+')) {
			
				break;
			}
			else{
				puz[p1.first-1][p1.second-1] = de; 
				p1.first--;
				p1.second--;
			}
		}
	}
}
void ini_move(){
	int i ;
	for (i = 0 ; i <30 ; i ++){
		memo_white[i].first = 99;memo_white[i].second = 99;
		memo_dark[i].first = 99 ;memo_dark[i].second  = 99;
	}
}
int board_wei[6][6] = {{4,-3,2,2,-3,4},{-3,-4,-1,-1,-4,-3},{2,-1,1,1,-1,2},{2,-1,1,1,-1,2},{-3,-4,-1,-1,-4,-3},{4,-3,2,2,-3,4}};
int place_score(int color){
//1 = dark 2 = white
//+ (for empty grid), X (for dark pieces) O (for light pieces)
 	int i , j ,o=0,x=0;
 	for (i = 0 ; i < 6 ; i++){
 		for (j = 0 ; j < 6 ; j++){
 			if (puz[i][j]=='O')
				o+= board_wei[i][j];
		 	if (puz[i][j]=='X')
				x+= board_wei[i][j];
		}
	}
	if (color == 1)
		return x;
	else
		return o;
}
int can_move(int color){
	int i , j , k;
	int count = 0;
	int moba = 0;
	pair<int , int> p1 ;
	for (i = 0 ; i < 6 ; i ++){
		for(j = 0 ; j < 6 ; j ++){
			if(puz[i][j] =='+'){
				p1.first = i ;
				p1.second = j;
				for (k = 0 ; k < 8 ; k ++){
					count = 0;
					count = find_valid(color,k,p1);
					if (count > 0 ){
						if(color == 1){
							memo_dark[moba].first = i ;
							memo_dark[moba++].second= j ;
						}
						else{
							memo_white[moba].first = i ;
							memo_white[moba++].second= j ;
						}
					}
				}
			}
		}
	}
//	printf("can_move :");
//	for (i =0 ; i < moba ; i ++){
//		printf("%d + %d\n",memo_dark[i].first,memo_dark[i].second);
//	}
//	printf("\n");	
	return moba;
}
int moba(int color){
	return can_move(color);
}
int count_color(string ap , int color){
	int i , o=0 , x=0;
	for (i = 0 ;i < 36 ; i++){
		if (ap[i]=='O'){
			o++;
		}
		else if (ap[i]=='X'){
			x++;
		}	
	}
	if (color == 1 )
		return x;
	else
		return o;
}
int count_pz( int color){
	int i , j , o=0 , x=0;
	for (i = 0 ; i < 6 ; i++){
		for (j = 0; j <6 ; j ++){
			if (puz[i][j]=='O')
				o++;
			else if (puz[i][j]=='X')
				x++;	
		}
	}
	if (color == 1 )
		return x;
	else
		return o;
}
bool gameover(string ap){
	int i , count = 0; 
	for (i=0 ; i < 36 ; i ++){
		if (ap[i]== '+'){
			return false;
		}
	}
	return true;
}
int max1(int a , int b){
	if (a > b )
		return a;
	else 
		return b;	
}
int min1(int a , int b){
	if (a < b )
		return a;
	else 
		return b;	
}

void show1(){
	int i , j ;
	char* a = "ABCDEF";
	printf("  a b c d e f\n");
	for (i = 0 ; i < 6 ; i ++){
		printf("%c ",a[i]);
		for ( j = 0 ; j < 6 ; j ++){
			printf("%c ",puz[i][j]);
		}
		printf("\n");
	}	
}

void copy_puz(char target[][6] , char source[][6]){
	int i,j;
	for(i = 0 ; i < 6 ; i ++){
		for(j = 0 ; j < 6 ; j++){
			target[i][j] = source[i][j];
		}
	}
}
int valid_step(int);
float monte(string ap , int color ){
	//+ (for empty grid), X (for dark pieces) O (for light pieces).
	//1 = dark 2 = white
	int i , j , k , n , rn , bwin=0 , wwin=0,q,count,v,pre=0;
	srand(time(0));
	pair<int , int > p1 ;
	for (k = 0 ; k < 1000 ; k++){
//		printf(" k=%d\n",k);
		con(ap);
		pre=0;
		while(!(count_pz(1)<=0 || count_pz(2)<=0)){
			if(gameover(decon(1)))
				break;	
//			printf("%d - %d",valid_step(1),valid_step(2));
			if (valid_step(1)==0&&valid_step(2)==0){
				break; 
			}
			ini_move();			
			n = can_move(color);
//			printf("n = %d",n);	
			if (n == 0){
				if (pre==1)
					break;
				if (color == 1 )
					color = 2;
				else
					color = 1;
				pre=1;
				continue;
			}
			rn = rand() % n;
			if (color == 1){
				v=0;
				p1.first = memo_dark[rn].first;
				p1.second = memo_dark[rn].second;
				for (q = 0 ; q < 8 ; q ++){			
					count = 0;
					count = find_valid(color,q,p1);
					if (count > 0 ){
						flip(color, q ,p1);
						v=1;	
					}	
				}
				if (v == 1)
					puz[memo_dark[rn].first][memo_dark[rn].second]='X';	
			}
			else{
				v=0;
				p1.first = memo_white[rn].first;
				p1.second = memo_white[rn].second;
				for (q = 0 ; q < 8 ; q ++){			
					count = 0;
					count = find_valid(color,q,p1);
					if (count > 0 ){
						flip(color, q ,p1);
						v=1;	
					}	
				}
				if (v == 1)
					puz[memo_white[rn].first][memo_white[rn].second]='O';
			}
			if (color == 1 )
				color = 2;
			else
				color = 1;
			
//			printf("------------------------------------------\n");
//			printf(" k=%d\n",k);
//			show1();
//			printf("------------------------------------------\n");
		}
		if (count_color(decon(1),1)>count_color(decon(1),2))
			bwin ++;
		else
			wwin ++;
	}
//	printf("b win = %d  w win =%d\n",bwin,wwin);
	if (color == 1)
		return (bwin / 1000);
	else 	
		return (wwin / 1000);
}	
float max_search_monte(string , int ,int,float ,float );
float min_search_monte(string ap , int depth , int color , float alpha , float beta){
	int i , j , count = 0 , k = 0, v = 0 , p = 0,tag = 0;
	float m , t_score =999999.0 , score = 0.0;
	pair<int , int > p1 ;
	m = beta;
	con(ap);
	if (depth == 0 || gameover(ap)){
		if (color == 1){
			score += monte(ap , color);
			return score;
		}	
		else{
			score += monte(ap , color);

			return score;
		} 		
	}
	for (i = 0 ; i < 6 ; i ++){
		for (j = 0 ; j < 6 ; j ++){
			if(puz[i][j] =='+'){
				v=0;
				p1.first = i ;
				p1.second = j;
				for (k = 0 ; k < 8 ; k ++){
					count = 0;
					count = find_valid(color,k,p1);
					if (count > 0 ){
						flip(color, k ,p1);
						tag = 1;
						v=1;	
					}
				}
				if (v == 1){
					if (color == 1){
						puz[i][j] = 'X';
						t_score = max_search_monte(decon(1),depth-1,2,alpha, m);
					}
					else{
						puz[i][j] = 'O';
						t_score = max_search_monte(decon(1),depth-1,1,alpha, m);
					}
					if (t_score < m){
						m = t_score;
					}
					if (m == -36 || m <= alpha)
						return (alpha);
				}
			}
			
			con(ap);	
		}
	}
	if (tag == 0 ){
		if (color == 1)
			t_score = max_search_monte(decon(1),depth-1,2,alpha, m);
		else 	
			t_score = max_search_monte(decon(1),depth-1,1,alpha, m);
		if (t_score < m){
			m = t_score;
		}
		if (m == -36 || m <= alpha){
			return (alpha);
		}
	}
	return m;
}
float max_search_monte(string ap , int depth ,int color , float alpha , float beta ){
	int i , j , count = 0 , k = 0, v = 0 , p = 0,tag = 0;
	float m , t_score =999999.0 , score = 0.0;
	pair<int , int > p1 ;
	m = alpha;
	con(ap);
	if (depth == 0 || gameover(ap)){
		if (color == 1){
//			printf("run into monte\n");
			score += monte(ap , color);
//			printf("hi\n");
			return score;
		}	
		else{
//			printf("run into monte\n");
			score += monte(ap , color);
//			printf("hi\n");
			return score;
		} 		
	}
//	printf("depth = %d\n",depth);
	for (i = 0 ; i < 6 ; i ++){
		for (j = 0 ; j < 6 ; j ++){
			if(puz[i][j] =='+'){
				v=0;
				p1.first = i ;
				p1.second = j;
				for (k = 0 ; k < 8 ; k ++){
					count = 0;
					count = find_valid(color,k,p1);
					if (count > 0 ){
						flip(color, k ,p1);
						v=1;
						tag = 1;	
					}
				}
				if (v == 1){
					if (color == 1){
						puz[i][j] = 'X';
//						show1();
						t_score = min_search_monte(decon(1),depth-1,2,m,beta);
//						if (depth == 4)
//							printf("t score = %d\n",t_score);
					}
					else{
						puz[i][j] = 'O';
//						show1();
						t_score = min_search_monte(decon(1),depth-1,1,m,beta);
//						if (depth == 4)
//							printf("t score = %d\n",t_score);
					}
					if (t_score > m){
						m = t_score;
						if (depth == dep1){
							best.first = i;
							best.second = j;
						}
						if (depth == dep2){
							best2.first = i;
							best2.second = j;
						}
						if (depth == 4){
							best3.first = i;
							best3.second = j;
						}
						if (m == 36 || m >= beta)
							return (beta);
					}
				}
			}
			con(ap);
		}
	}
	if (tag == 0 ){
		if (color == 1)
			t_score = min_search_monte(decon(1),depth-1,2,m,beta);
		else 	
			t_score = min_search_monte(decon(1),depth-1,1,m,beta);
		if (t_score > m){
			m = t_score;
		if (m == 36 || m >= beta)
			return (beta);
		}
	}
//	printf("end\n");
	return m;
}
int max_search_com(string , int ,int,int ,int );
int min_search_com(string ap , int depth , int color , int alpha , int beta){
	int i , j , count = 0 , k = 0 , m = 0 , t_score =999999, v = 0 , p = 0,tag = 0,score = 0;
	pair<int , int > p1 ;
	m = beta;
	con(ap);
	if (depth == 0 || gameover(ap)){
		if (color == 1){
			score += (count_color(ap,1) - count_color(ap,2));
			score += moba(1) -moba(2);
			score += place_score(1) - place_score(2);
			return score;
		}	
		else{
			score += (count_color(ap,2) - count_color(ap,1));
			score += moba(2) - moba(1);
			score += place_score(2) - place_score(1);
			return score;
		} 	
			
	}
	for (i = 0 ; i < 6 ; i ++){
		for (j = 0 ; j < 6 ; j ++){
			if(puz[i][j] =='+'){
				
				v=0;
				p1.first = i ;
				p1.second = j;
				for (k = 0 ; k < 8 ; k ++){
					count = 0;
					count = find_valid(color,k,p1);
					if (count > 0 ){
						flip(color, k ,p1);
						tag = 1;
						v=1;	
					}
				}
				if (v == 1){
					if (color == 1){
						puz[i][j] = 'X';
						t_score = max_search_com(decon(1),depth-1,2,alpha, m);
					}
					else{
						puz[i][j] = 'O';
						t_score = max_search_com(decon(1),depth-1,1,alpha, m);
					}
					if (t_score < m){
						m = t_score;
					}
					if (m == -36 || m <= alpha)
						return (alpha);
				}
			}
			
			con(ap);	
		}
	}
	if (tag == 0 ){
		if (color == 1)
			t_score = max_search_com(decon(1),depth-1,2,alpha, m);
		else 	
			t_score = max_search_com(decon(1),depth-1,1,alpha, m);
		if (t_score < m){
			m = t_score;
		}
		if (m == -36 || m <= alpha){
			return (alpha);
		}
	}
	return m;
}
int max_search_com(string ap , int depth ,int color , int alpha , int beta ){
	int i , j , count = 0 , k = 0 , m = 0 , t_score = -999999 , v = 0 , p = 0 , tag = 0,score= 0;
	pair<int , int > p1 ;
	m = alpha;
	con(ap);
	if (depth == 0 || gameover(ap)){
		if (color == 1){
			score += (count_color(ap,1) - count_color(ap,2));
			score += moba(1) -moba(2);
			score += (place_score(1) - place_score(2)) * 1;
			return score;
		}	
		else{
			score += (count_color(ap,2) - count_color(ap,1));
			score += moba(2) - moba(1);
			score += place_score(2) - place_score(1);
			return score;
		} 	
	}
//	printf("depth = %d\n",depth);
	for (i = 0 ; i < 6 ; i ++){
		for (j = 0 ; j < 6 ; j ++){
			if(puz[i][j] =='+'){
				v=0;
				p1.first = i ;
				p1.second = j;
				for (k = 0 ; k < 8 ; k ++){
					count = 0;
					count = find_valid(color,k,p1);
					if (count > 0 ){
						flip(color, k ,p1);
						v=1;
						tag = 1;	
					}
				}
				if (v == 1){
					if (color == 1){
						puz[i][j] = 'X';
//						show1();
						t_score = min_search_com(decon(1),depth-1,2,m,beta);
//						if (depth == 4)
//							printf("t score = %d\n",t_score);
					}
					else{
						puz[i][j] = 'O';
//						show1();
						t_score = min_search_com(decon(1),depth-1,1,m,beta);
//						if (depth == 4)
//							printf("t score = %d\n",t_score);
					}
					if (t_score > m){
						m = t_score;
						if (depth == dep1){
							best.first = i;
							best.second = j;
						}
						if (depth == dep2){
							best2.first = i;
							best2.second = j;
						}
						if (m == 36 || m >= beta)
							return (beta);
					}
				}
			}
			con(ap);
		}
	}
	if (tag == 0 ){
		if (color == 1)
			t_score = min_search_com(decon(1),depth-1,2,m,beta);
		else 	
			t_score = min_search_com(decon(1),depth-1,1,m,beta);
		if (t_score > m){
			m = t_score;
		if (m == 36 || m >= beta)
			return (beta);
		}
	}
//	printf("end\n");
	return m;
}
int max_search(string , int ,int,int ,int );
int min_search(string ap , int depth , int color , int alpha , int beta){
	int i , j , count = 0 , k = 0 , m = 0 , t_score =999999, v = 0 , p = 0,tag = 0;
	pair<int , int > p1 ;
	m = beta;
	con(ap);
	if (depth == 0 || gameover(ap)){
		if (color == 1)
			return (count_color(ap,1) - count_color(ap,2));
		else 	
			return (count_color(ap,2) - count_color(ap,1));
	}
	for (i = 0 ; i < 6 ; i ++){
		for (j = 0 ; j < 6 ; j ++){
			if(puz[i][j] =='+'){
				
				v=0;
				p1.first = i ;
				p1.second = j;
				for (k = 0 ; k < 8 ; k ++){
					count = 0;
					count = find_valid(color,k,p1);
					if (count > 0 ){
						flip(color, k ,p1);
						tag = 1;
						v=1;	
					}
				}
				if (v == 1){
					if (color == 1){
						puz[i][j] = 'X';
						t_score = max_search(decon(1),depth-1,2,alpha, m);
					}
					else{
						puz[i][j] = 'O';
						t_score = max_search(decon(1),depth-1,1,alpha, m);
					}
					if (t_score < m){
						m = t_score;
					}
					if (m == -36 || m <= alpha)
						return (alpha);
				}
			}
			
			con(ap);	
		}
	}
	if (tag == 0 ){
		if (color == 1)
			t_score = max_search(decon(1),depth-1,2,alpha, m);
		else 	
			t_score = max_search(decon(1),depth-1,1,alpha, m);
		if (t_score < m){
			m = t_score;
		}
		if (m == -36 || m <= alpha){
			return (alpha);
		}
	}
	return m;
}

int max_search(string ap , int depth ,int color , int alpha , int beta ){
	int i , j , count = 0 , k = 0 , m = 0 , t_score = -999999 , v = 0 , p = 0 , tag = 0;
	pair<int , int > p1 ;
	m = alpha;
	con(ap);
	if (depth == 0 || gameover(ap)){
//		printf("game\n");
		if (color == 1){	
			return (count_color(ap,1) - count_color(ap,2));
		}
		else {
			return (count_color(ap,2) - count_color(ap,1));
		}
			
	}
//	printf("depth = %d\n",depth);
	for (i = 0 ; i < 6 ; i ++){
		for (j = 0 ; j < 6 ; j ++){
			if(puz[i][j] =='+'){
				v=0;
				p1.first = i ;
				p1.second = j;
				for (k = 0 ; k < 8 ; k ++){
					count = 0;
					count = find_valid(color,k,p1);
					if (count > 0 ){
						flip(color, k ,p1);
						v=1;
						tag = 1;	
					}
				}
				if (v == 1){
					if (color == 1){
						puz[i][j] = 'X';
//						show1();
						t_score = min_search(decon(1),depth-1,2,m,beta);
//						if (depth == 4)
//							printf("t score = %d\n",t_score);
					}
					else{
						puz[i][j] = 'O';
//						show1();
						t_score = min_search(decon(1),depth-1,1,m,beta);
//						if (depth == 4)
//							printf("t score = %d\n",t_score);
					}
					if (t_score > m){
						m = t_score;
						if (depth == dep1){
							best.first = i;
							best.second = j;
						}
						if (depth == dep2){
							best2.first = i;
							best2.second = j;
						}
						if (m == 36 || m >= beta)
							return (beta);
					}
				}
			}
			con(ap);
		}
	}
	if (tag == 0 ){
		if (color == 1)
			t_score = min_search(decon(1),depth-1,2,m,beta);
		else 	
			t_score = min_search(decon(1),depth-1,1,m,beta);
		if (t_score > m){
			m = t_score;
		if (m == 36 || m >= beta)
			return (beta);
		}
	}
//	printf("end\n");
	return m;
}

int valid_step(int color){
	int i , j , k , count ,tag;
	pair<int , int> p1 ;
	for (i = 0 ; i < 6 ; i ++){
		for (j = 0 ; j < 6 ; j ++){
			if(puz[i][j] =='+'){
				p1.first = i ;
				p1.second = j;
				for (k = 0 ; k < 8 ; k ++){
					count = 0;
					count = find_valid(color,k,p1);
					if (count > 0 ){
						tag=1;	
						break;
					}
				}
			}
		}
	}
	if (tag == 1 )
		return 1;
	else 
		return 0;
}

int main(){
	string ap , place , move;
	pair <int , int > p1;
	const char* row = "ABCDEF";
	const char* col = "abcdef";
	string ini = "++++++++++++++OX++++XO++++++++++++++";
	int sec_c=0,pla1=0,pla2=0,hehe,n , i , j , color , dir , ans = -1 , depth = 10 , max = -999999,tmpi=0,tmpj=0,l,alpha=-999999,beta = 999999,count;
	float alpha1 = -999999.0 ,  beta1 = 999999.0;
	double total_sec=0.0;
	//+ (for empty grid), X (for dark pieces) O (for light pieces).
	//1 = dark 2 = white
	for (hehe = 0 ; hehe < 1 ; hehe ++){
		ap = ini ;
		con(ap);
		
		dep1 = 4;
		dep2 = 10;
		while (!gameover(ap)){
	//		printf("------------------------------------------\n");
	//		show1();
	//		printf("------------------------------------------\n");
			if (count_color(ap,1)<=0 || count_color(ap,2)<=0||(valid_step(1)==0&&valid_step(2)==0))
				break;
			if (valid_step(1)){
				auto startTime = std::chrono::high_resolution_clock::now();
	//			cout<<"player Dark move : "<<endl;
	//			cin>>move;
	//			p1 = findplace(move);
	//			ap = decon(1);	
				ans = max_search_monte(ap , dep1, 1 ,alpha1,beta1);
				printf("AI 1 move = %c%c\n", row[best.first] , col[best.second]);
				for (i = 0 ; i < 8 ; i++){
					count = 0;
					count = find_valid(1,i,best);
					if (count > 0)
						flip(1 , i , best);
				}
				puz[best.first][best.second] = 'X';
				ap = decon(1);
	//			printf("AI 1 move = %c%c\n", row[best.first] , col[best.second]);
				con(ap);
				auto endTime = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double> duration = endTime - startTime;
	    		double seconds = duration.count();
	    		total_sec+=seconds;
	    		sec_c++;
	    		std::cout << "mini Execution time: " << seconds << " seconds" << std::endl;
			}	
			if (valid_step(2)){
				ans = max_search_com(ap , dep2, 2 ,alpha,beta);
				con(ap);
				for (i = 0 ; i < 8 ; i++){
					count = 0;
					count = find_valid(2,i,best2);
					if (count > 0)
						flip(2 , i , best2);
				}
				puz[best2.first][best2.second] = 'O';
				ap = decon(1);
				printf("AI2 move = %c%c\n", row[best2.first] , col[best2.second]);
			}
		}
		ap = decon(1);
		if (count_color(ap , 1) > count_color(ap , 2)){
			pla1++;
			printf("player 1 win !!\n");
		}
		else{
			pla2++;
			printf("player 2 win !!\n");
		}	
	}
	printf("avg_sec = %lf\n",total_sec/sec_c);
	printf("player 1 win = %d  player 2 win = %d !!\n",pla1,pla2);
	return 0;
}
