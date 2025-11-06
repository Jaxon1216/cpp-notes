#include<stdio.h>
#include<math.h>
int main(){
    int  m, n;

    while(scanf("%d %d", &m, &n) == 2){
        for(int i = m; i <= n; i++){
            if(i == pow(i%10,3) + pow((i/10)%10,3) + pow((i/100),3))
                printf("%d ",i);
            else printf("no ");
        }
        printf("\n");
    }
    return 0;
}