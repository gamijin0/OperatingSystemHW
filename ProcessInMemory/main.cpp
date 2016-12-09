#include <iostream>
#include <windows.h>
#include <psapi.h>
#include <algorithm>

#define PRO_MAX 4096

using namespace std;

int main() {
    DWORD  processIds[PRO_MAX];
    DWORD len;

    //��һ��������ָ�򱣴�PID��һ�������׵�ַ
    // �ڶ�������Ϊ����Ĵ�С�����ֽ�Ϊ��λ��
    // �������������Ǵ���ֵ��ָ����ʵ����Ϊ�˱�����ЩPID��ʹ�õ��ֽ���
    if(!EnumProcesses(processIds,PRO_MAX,&len))
    {
        cout<<"��ȡPID����!"<<endl;
        ;
        exit(0);
    }

    cout<<"��������:"<<len<<endl;

    sort(processIds,processIds+len);
    for(int i=0;i<len;i++ )
    {
        if(processIds[i]!=0) //PID==0˵����ϵͳ���ý���,���账��
        {
            HANDLE  hOneProcess = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, false,processIds[i]);
            PROCESS_MEMORY_COUNTERS info;
            GetProcessMemoryInfo(hOneProcess,&info, sizeof(info));

            TCHAR* procName = new TCHAR[MAX_PATH];
            GetModuleFileNameEx(hOneProcess, NULL, procName, MAX_PATH);

            cout<<"PID:\t"<<processIds[i]<<"\t������:\t"<<procName
                <<"\n��ǰʹ�õ��ڴ�:\t"<<info.PeakWorkingSetSize/1024/1024<<"MB"
                <<"\tȱҳ�жϴ���:"<<info.PageFaultCount
                <<endl;
        }

    }

    system("pause");
    return 0;
}