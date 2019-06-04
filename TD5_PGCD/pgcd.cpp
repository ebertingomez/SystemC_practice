#include <stdio.h>
int pgdc(unsigned int a,unsigned int b){
    int bigger = (a>b) ? a : b;
    int smaller = (a<b) ? a : b;
    int diff;
    do {
        diff = bigger - smaller;
        bigger = (diff>smaller) ? diff : smaller;
        smaller = (diff<smaller) ? diff : smaller;
    }
    while (diff >0);
    return bigger;
}

int main(){
    printf("The result is %d \n",pgdc(360,81));
    return 0;
}