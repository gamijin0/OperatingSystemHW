#include <iostream>
#include <windows.h>
#include <psapi.h>
#include <algorithm>

#define PRO_MAX 4096

using namespace std;

int main() {
    DWORD  processIds[PRO_MAX];
    DWORD len;

    //第一个参数是指向保存PID的一个数组首地址
    // 第二个参数为数组的大小（以字节为单位）
    // 第三个参数则是传出值，指明了实际上为了保存这些PID所使用的字节数
    if(!EnumProcesses(processIds,PRO_MAX,&len))
    {
        cout<<"获取PID错误!"<<endl;
        ;
        exit(0);
    }

    cout<<"进程数量:"<<len<<endl;

    sort(processIds,processIds+len);
    for(int i=0;i<len;i++ )
    {
        if(processIds[i]!=0) //PID==0说明是系统闲置进程,无需处理
        {
            HANDLE  hOneProcess = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, false,processIds[i]);
            PROCESS_MEMORY_COUNTERS info;
            GetProcessMemoryInfo(hOneProcess,&info, sizeof(info));

            TCHAR* procName = new TCHAR[MAX_PATH];
            GetModuleFileNameEx(hOneProcess, NULL, procName, MAX_PATH);

            cout<<"PID:\t"<<processIds[i]<<"\n\t进程名:\t"<<procName
                <<"\n\t当前使用的内存:\t"<<info.WorkingSetSize/1024/1024<<"MB"
                <<"\n\t使用内存高峰:"<<info.PeakWorkingSetSize/1024/1024<<"MB"
                <<"\n\t缺页中断次数:"<<info.PageFaultCount
                <<"\n\t使用页面缓存池高峰:"<<info.QuotaPeakPagedPoolUsage
                <<"\n\t使用页面缓存池:"<<info.QuotaPagedPoolUsage
                <<"\n\t使用非分页缓存池高峰:"<<info.QuotaPeakNonPagedPoolUsage
                <<"\n\t使用非分页缓存池:"<<info.QuotaNonPagedPoolUsage
                <<"\n\t使用分页文件:"<<info.PagefileUsage
                <<"\n\t使用分页文件高峰:"<<info.PeakPagefileUsage
                <<endl;
        }

    }

    system("pause");
    return 0;
}