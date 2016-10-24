//
// Created by 49738 on 2016/10/10.
//
#include <iostream>
#include <windows.h>
#define FILE_MAPPING_NAME "MyFileMapping"
#define MEMORY_SIZE 1024*1024
int main(){

    //创建一个内存文件映射对象
    HANDLE hMap=CreateFileMapping(
            INVALID_HANDLE_VALUE,  ///映射文件的句柄，若设为0xFFFFFFFF(即：INVALID_HANDLE_VALUE)则创建一个进程间共享的对象
            NULL, //安全属性
            PAGE_READWRITE, //保护方式,PAGE_READONLY 以只读方式打开映射；PAGE_READWRITE 以可读、可写方式打开映射；PAGE_WRITECOPY 为写操作留下备份
            0,//文件映射的最大长度的高32位
            MEMORY_SIZE,//文件映射的最大长度的低32位。如这个参数和dwMaximumSizeHigh都是零，就用磁盘文件的实际长度(第一个参数则能不能为空)
            FILE_MAPPING_NAME
    );

    //检查句柄有效性
    if(hMap==NULL){
        std::cout<<"Create FileMap object failed:"<<GetLastError()<<std::endl;
        exit(0);
    } else{
        std::cout<<"Create FileMap object ["<<FILE_MAPPING_NAME<<"]  succeed."<<std::endl;
    }

    //内存映射文件映射到进程的虚拟地址中
    PVOID my_viewOfFile= MapViewOfFile(
            hMap,//CreateFileMapping()返回的句柄
            FILE_MAP_ALL_ACCESS,//与CreateFileMapping()函数所设置的保护属性相匹配
            0, //文件映射起始偏移的高32位
            0, //文件映射起始偏移的低32位
            0 //文件中要映射的字节数。为0表示映射整个文件映射对象
    );

    //创建子进程
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));

    CreateProcess(
            "ProcessConnect_child.exe",   //  指向一个NULL结尾的、用来指定可执行模块的宽字节字符串
            NULL, // 命令行字符串
            NULL, //    指向一个SECURITY_ATTRIBUTES结构体，这个结构体决定是否返回的句柄可以被子进程继承。
            NULL, //    如果lpProcessAttributes参数为空（NULL），那么句柄不能被继承。<同上>
            false,//    指示新进程是否从调用进程处继承了句柄。
            CREATE_NEW_CONSOLE,//  CREATE_NEW_CONSOLE  新控制台打开子进程
            //  CREATE_SUSPENDED    子进程创建后挂起，直到调用ResumeThread函数
            NULL, //    指向一个新进程的环境块。如果此参数为空，新进程使用调用进程的环境
            NULL, //    指定子进程的工作路径
            &si, // 决定新进程的主窗体如何显示的STARTUPINFO结构体
            &pi  // 接收新进程的识别信息的PROCESS_INFORMATION结构体
    );



    if(my_viewOfFile){
        //将输入写入内存文件
            while (TRUE){
                std::cout<<"InPut your text:";
                std::string InPutStr;
                std::cin>>InPutStr;
                lstrcpy((LPTSTR)my_viewOfFile,InPutStr.c_str());
                if(strcmp(InPutStr.c_str(),"exit")==0){
                    break;
                }
            }

    } else{
        std::cout<<"Get view of file object failed:"<<GetLastError()<<std::endl;
        exit(0);
    }
    UnmapViewOfFile(my_viewOfFile);
    CloseHandle(hMap);
    return 0;

}
