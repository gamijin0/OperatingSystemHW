from enum import Enum
import time
import copy

class bcolors:
    #用于控制输出的颜色
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'

class CPU_Mode(Enum):
    SJF = 1 #短作业优先
    RR = 2 #时间片轮转
    PNS = 3 #优先级


class Task():

    name = "" #进程名称
    arrive_time = 0 #到达时间
    need_time =0 #完成所需时间
    priority = 0 #优先级
    finish_time = 0 #完成时刻
    progress = 0 #当前进度
    wait_time = 0 #执行前等待时间

    def __init__(self,task:list):
        self.name = str(task[0])
        self.arrive_time = int(task[1])
        self.need_time = int(task[2])
        self.priority = int(str(task[3]).replace('\n',''))
        self.finish_time = 0
        self.wait_time=0
        self.progress =0

    def __str__(self):
        return (self.name+":a"+str(self.arrive_time)+",n"+str(self.need_time)+",w"+str(self.wait_time)+",pro"+str(self.progress)+ ",pri" + str(self.priority))

class CPUManager():

    task_wait = list() #等待队列
    task_ready = list() #执行队列

    time_slice = 1 #时间片大小
    time_slice_used = 0

    task_in_service = None #当前正在执行的任务

    res = list() #用于记录结果

    debug = False

    time_now = 0  #当前时间

    mode = CPU_Mode(1)

    #模式:SJF_mode,
    SJF_mode = 1 #短作业优先


    def __init__(self, task_list:list, debug:bool = False):
        self.task_wait = task_list
        self.debug = debug
        cpu_pool = 0


    def execute(self,mode:CPU_Mode,time_slice:int = 1 ):

            self.mode = mode
            # if(self.debug):
            print("Using mode: %s "% self.mode)
            if(self.mode==CPU_Mode.RR):
                self.time_slice = time_slice
                print("Time slice: %d" % self.time_slice)


            while(True):
                self.cpu_run()

    def cpu_run(self):

        # time.sleep(0.2)
        if(self.debug):
            print(bcolors.ENDC+"============time: %d==============="% self.time_now)


        #检查是否有进程到达
        for t in self.task_wait[:]:
            if(self.time_now==t.arrive_time):
                if(self.debug):
                    print(bcolors.FAIL+"task arrive: %s" % t)
                self.task_ready.append(self.task_wait.pop(self.task_wait.index(t))) #若此任务已到达,则放入执行队列
                if(self.mode==CPU_Mode.SJF):
                    #最短作业优先则按照需求时间排序
                    self.task_ready.sort(key=lambda x:x.need_time)
                elif(self.mode==CPU_Mode.PNS):
                    self.task_ready.sort(key=lambda x:x.priority,reverse=True)
        # 若没有任务,则加载任务
        if(self.task_in_service==None):
            if(self.task_ready.__len__()>0):
                #开始执行最新的一个任务
                self.task_in_service = self.task_ready.pop(0)
                self.time_slice_used = 0
                if(self.debug):
                    print(bcolors.WARNING+"start task: %s" % self.task_in_service)
            else:
                if(self.task_wait.__len__()==0):
                    #全部任务执行完毕
                    self.print_res() #打印结果
                    exit(0) #退出

        #检查是否上一次有没做完的进程
        if (self.mode == CPU_Mode.RR and self.task_in_service is not None):

            if (self.time_slice_used == self.time_slice):
                #若当前进程已使用完时间片,则切换进程
                self.task_ready.append(self.task_in_service)
                self.task_in_service = self.task_ready.pop(0)
                if (self.debug == True):
                    print(bcolors.OKBLUE + "task changed to: %s" % self.task_in_service)

                self.time_slice_used = 0


        #打印这一时刻执行的任务
        if(self.debug):
            if(self.task_in_service==None):
                print(bcolors.HEADER + "run -> None")
            else:
                print(bcolors.HEADER+"run -> %s" % self.task_in_service)

        #执行任务
        self.task_in_service.progress += 1



        if(self.task_in_service.progress==self.task_in_service.need_time):
            # 若当前任务执行完毕
            self.task_in_service.finish_time = self.time_now #记录下完成时间
            self.res.append(self.task_in_service)

            if(self.debug):
                print(bcolors.OKGREEN+"task finish : %s" % self.task_in_service)

            self.task_in_service=None
            self.time_slice_used = 0
        else:
            #若当前任务未结束,则已使用时间片计数+1
            self.time_slice_used += 1




        for t in self.task_ready:
            t.wait_time+=1 #就绪队列中的任务等待时间+1



        self.time_now +=1



    def print_res(self):
        for i in self.res:
            nt = i.need_time
            print(bcolors.OKBLUE+"[",end='')
            for j in range(nt):
                print(bcolors.OKGREEN+"#",end='')
            print(bcolors.ENDC+str(i),end='')
            for j in range(nt):
                print(bcolors.OKGREEN+"#",end='')
            print(bcolors.OKBLUE + "]",end='')

        print("\n\n平均响应时间: %.1f" % (sum(i.wait_time for i in self.res)/len(self.res)))
        print("\n平均周转时间: %.1f" % (((sum(i.wait_time for i in self.res)+sum(i.need_time for i in self.res))/len(self.res))))
