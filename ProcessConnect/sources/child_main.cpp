//
// Created by 49738 on 2016/10/10.
//
#include <iostream>
#include <windows.h>

#define dwMemoryFileSize 1024
#define FILE_MAPPING_NAME "MyFileMapping"

int main(int argc, char *argv[]){

    //创建一个内存文件映射对象
    HANDLE  hMap=OpenFileMapping(
            PAGE_READWRITE,//保护模式
            TRUE,//如这个函数返回的句柄能由当前进程启动的新进程继承，则这个参数为TRUE
            FILE_MAPPING_NAME
    );

    //检查句柄有效性
    if(hMap==NULL){
        std::cout<<"Open FileMap object failed:"<<GetLastError()<<"\nPlease check the mainProcess."<<std::endl;
        system("pause");
        exit(0);
    } else{
        std::cout<<"Open FileMap object ["<<FILE_MAPPING_NAME<<"]  succeed."<<std::endl;
    }


    //内存映射文件映射到进程的虚拟地址中
    PVOID my_viewOfFile= MapViewOfFile(
            hMap,//CreateFileMapping()返回的句柄
            PAGE_READWRITE,//与CreateFileMapping()函数所设置的保护属性相匹配
            0, //文件映射起始偏移的高32位
            0, //文件映射起始偏移的低32位
            0 //文件中要映射的字节数。为0表示映射整个文件映射对象
    );

    char tmp[dwMemoryFileSize];
    if(my_viewOfFile){
        while (TRUE){
            char s[dwMemoryFileSize]="";
            strcpy(s,(char*)my_viewOfFile);
            if(strlen(s)>0&&strcmp(tmp,s)!=0){
                //若内存文件有变化，则输出
                std::cout<<"What you just input is:"<<s<<std::endl;
                strcpy(tmp,s);
            }
            if(strcmp(s,"exit")==0){
                break;
            }
        }
    } else{
        std::cout<<"Get view of file object failed:"<<GetLastError()<<std::endl;
        system("pause");
        exit(0);
    }

    UnmapViewOfFile(my_viewOfFile);
    CloseHandle(hMap);
    return 0;

}