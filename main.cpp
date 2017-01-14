#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <list>
using namespace std;
int answer(char *T, char *S, int *A, int *B) ;
int guess(int A, int B);
int ABtrans(int A,int B);
int numIndex(int num);
void start(void);
char ansString[10*9*8*7*4], checkTable[5040][5040];
int finalTable[9], condition[15];
list <int> validlist;
list <int>::iterator it;
int main()
{
    start();
    int A, B, roundTotal = 0, ans, i, j, roundn, ansnum, bestnum;
    char ansRefer[4],refer[4];
    for(i=1;i<9;i++)finalTable[i]=0;
    while(printf("Please enter a number :")&&scanf("%d",&ansnum)!=EOF){
        ans = numIndex(ansnum);
        ansRefer[0]=ansString[ans*4],ansRefer[1]=ansString[ans*4+1],ansRefer[2]=ansString[ans*4+2],ansRefer[3]=ansString[ans*4+3];
        validlist.clear();
        roundn = bestnum = 0;
        for(i=0;i<5040;i++)validlist.push_back(i);

        while(1) {

            if(validlist.size() == 5040){
                bestnum = 0;
                validlist.pop_front();
            }
            else if(validlist.size() == 1){
                bestnum = validlist.front();
                validlist.pop_front();
            }
            else if(bestnum==0&&A==0&&B==0){
                bestnum = 2272;
            }
            else {
                bestnum = guess(A,B);
            }

            refer[0]=ansString[bestnum*4],refer[1]=ansString[bestnum*4+1],refer[2]=ansString[bestnum*4+2],refer[3]=ansString[bestnum*4+3];
            answer(refer, ansRefer, &A, &B);
            printf("Round-%d %d%d%d%d %dA%dB\n",++roundn,refer[3],refer[2],refer[1],refer[0],A,B);

            if(A == 4)break;

            for(it = validlist.begin(); it != validlist.end();++it)
                if( checkTable[*it][bestnum] != ABtrans(A,B))
                    *it = -1;
            validlist.remove(-1);
        }
        finalTable[roundn]++;
        roundTotal += roundn;
    }//for(i=1;i<9;i++)printf("|[%d-%d]|",i,finalTable[i]);//printf("\n[%f]", (float)roundTotal/5040);
    return(0);
}
void start(void) {
    int i, j, k, m,flag2=0,a,b;
    for(i = 0 ; i < 10 ; i++)
    for(j = 0 ; j < 10 ; j++)if (i != j)
    for(k = 0 ; k < 10 ; k++)if (k != j && k != i)
    for(m = 0 ; m < 10 ; m++)if (m != k && m != j && m != i) {
        ansString[flag2++]=m;
        ansString[flag2++]=k;
        ansString[flag2++]=j;
        ansString[flag2++]=i;
    }
    for(i = 0 ; i < 5040 ; i++)
        for(j = i ; j < 5040 ; j++){
            a=b=0;
            for(k = 0 ; k < 4 ; k++){
                if(ansString[i*4+k]==ansString[j*4+k])a++;
                for(m = 0 ; m < 4 ; m++){
                    if(ansString[i*4+k]==ansString[j*4+m])b++;
                    checkTable[i][j]=checkTable[j][i]=ABtrans(a,b-a);
                }
            }
        }
}
int answer(char *T, char *S, int *A, int *B) {
   	*A = *B = 0;
   	int i , j;
   	for ( i = 0 ; i < 4 ; i++ )	{
        if(T[i]==S[i])
            *A = *A + 1;
        for ( j = 0 ; j < 4 ; j++ )
            if(T[i]==S[j])*B = *B + 1;
    }
    *B = *B - *A;
    return ABtrans(*A,*B);
}
int guess(int A, int B) {
    int i, j, bestnum = 0;
    double best = 0.0;
    for( i=1; i<5040; i++ ) {
        for( j=0; j<15 ; j++ )condition[j]=0;
        for( it=validlist.begin(); it!=validlist.end(); ++it )
            condition[checkTable[i][*it]]++;
        double temp = 0.0;
        for( j=0; j<15; j++ )
            if(condition[j]!=0)
                temp += log2((double)condition[j]/validlist.size())*condition[j];
        if(temp < best) {
            best = temp;
            bestnum = i;
        }
    }
    return bestnum;
}
int ABtrans(int A,int B) {
    return (A==0)?B:((A==1)?B+5:(A==2)?B+9:(A==3)?B+12:14);
}
int numIndex(int num) {
    int i;
    char temp[4];
    temp[3]=num/1000,temp[2]=(num/100)%10,temp[1]=(num/10)%10,temp[0]=num%10;
    for(i = 0 ; i <5040 ; i++)
        if(temp[3]==ansString[i*4+3]&&temp[2]==ansString[i*4+2]&&temp[1]==ansString[i*4+1]&&temp[0]==ansString[i*4])
            return i;
}