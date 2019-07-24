#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int main(int argc, char const *argv[])
{
    char in[10],out[10];
    cin>>in>>out;
    int inlen=(int)strlen(in),outlen=(int)strlen(out);
    int in47=1,out47=1;
    for (int i = 0; i < inlen; ++i){
        in47*=(in[i]-0x40);
    }
    for (int i = 0; i < outlen; ++i){
        out47*=(out[i]-0x40);
    }
    if (out47%47==in47%47){
        printf("GO\n");
        return 0;
    }
    printf("STAY\n");
    return 0;
}