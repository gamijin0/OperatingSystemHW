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

            cout<<"PID:\t"<<processIds[i]<<"\n\t������:\t"<<procName
                <<"\n\t��ǰʹ�õ��ڴ�:\t"<<info.WorkingSetSize/1024/1024<<"MB"
                <<"\n\tʹ���ڴ�߷�:"<<info.PeakWorkingSetSize/1024/1024<<"MB"
                <<"\n\tȱҳ�жϴ���:"<<info.PageFaultCount
                <<"\n\tʹ��ҳ�滺��ظ߷�:"<<info.QuotaPeakPagedPoolUsage
                <<"\n\tʹ��ҳ�滺���:"<<info.QuotaPagedPoolUsage
                <<"\n\tʹ�÷Ƿ�ҳ����ظ߷�:"<<info.QuotaPeakNonPagedPoolUsage
                <<"\n\tʹ�÷Ƿ�ҳ�����:"<<info.QuotaNonPagedPoolUsage
                <<"\n\tʹ�÷�ҳ�ļ�:"<<info.PagefileUsage
                <<"\n\tʹ�÷�ҳ�ļ��߷�:"<<info.PeakPagefileUsage
                <<endl;
        }

    }

    system("pause");
    return 0;
}