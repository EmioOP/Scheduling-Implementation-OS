#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>

int main(){
    int four_ac;
    int fd[2];
    int a,b,c;
    int b_sqr;
    double result;

    printf("Enter a,b and c\n");
    scanf("%d%d%d",&a,&b,&c);
    printf("%d %d %d\n",a,b,c);

    if(pipe(fd) == -1){
        printf("Error");
        return 1;
    }

    if(fork() == 0){
        close(fd[0]);
        four_ac = 4 * a * c;
        write(fd[1],&four_ac,sizeof(four_ac));
        close(fd[1]);
    }else{
        close(fd[1]);
        b_sqr = b * b;
        read(fd[0],&four_ac,sizeof(four_ac));
        close(fd[0]);
        result = sqrt(b_sqr - four_ac);
        printf("Result: %.2f",result);
    }
    
    return 0;
}