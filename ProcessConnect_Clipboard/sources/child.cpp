//
// Created by 49738 on 2016/10/24.
//
#include <iostream>
#include <windows.h>
#define MAX_LENGTH 1024
using namespace std;

int main(){

    char tmpStr[MAX_LENGTH]="";
    while (TRUE){

        Sleep(200);//睡眠以防止同步错误

        OpenClipboard(NULL);
        if (IsClipboardFormatAvailable(CF_TEXT))    //如果剪切板中有文本类型的数据
        {
            HANDLE h=GetClipboardData(CF_TEXT); // 获得剪切板数据 所在的内存对象
            char * p=(char*)GlobalLock(h) ;  //通过锁定内存对象 获得剪切板缓冲区的指针
            GlobalUnlock(h) ;            //解锁内存对象 减少 内存对象的锁定技术

            if(strcmp(tmpStr,p)!=0){ //如果剪贴板内容有变化则输出
                cout<<"What in the ClipBoard is :"<<p<<endl;
                strcpy(tmpStr,p);
            }
            if(strcmp(tmpStr,"exit")==0){
                break;
            }
        }
        CloseClipboard();
    }

}