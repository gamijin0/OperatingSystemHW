//
// Created by 49738 on 2016/10/24.
//

#include <iostream>
#include <windows.h>
using namespace std;


int main(){
    OpenClipboard(NULL);
    EmptyClipboard(); //清空剪贴板
    HANDLE myHeap = GlobalAlloc(GMEM_FIXED,100); //分配固定的内存,返回一个指针.
    char* heapTop = (char*)GlobalLock(myHeap);  //锁定指定内存对象,返回内存指向对象第一个字节的指针

    while (TRUE){
        cout<<"InPut your text:";
        string InPutStr;
        cin>>InPutStr;
        strcpy(heapTop,InPutStr.c_str());
        SetClipboardData(CF_TEXT,myHeap) ;  //将指定内存对象的数据设置到剪切板
        GlobalUnlock(myHeap) ;//解锁内存对象 并且减少锁定计数
        CloseClipboard() ;  //关闭剪切板 在调用Open之后 必须有
        cout<<"Clipboard is updated."<<endl;
        if(strcmp(InPutStr.c_str(),"exit")==0){
            break;
        }
    }

}
