#include<stdio.h>
int main(){

    printf("\n==charging Graph ==\n");
    for (int i = 0; i <= 20; i++) {
        int pos = (int)((2.33/ 5) * 50); // scale voltage to width
        for (int j = 0; j < pos; j++) {
             printf(" "); // spaces before the star
        }
    printf("*\n"); }


    return 0;
}