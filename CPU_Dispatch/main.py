from CPU_Dispatch.CPUManager import CPUManager,CPU_Mode,Task

task_list = list()

with open("data.txt",encoding='utf-8') as f:
    lines = f.readlines()
    for line in lines[1:]:
        line = line.split(',')
        task_list.append(Task(line))
        # print(Task(line))


one = CPUManager(task_list,debug=False)
one.execute(mode=CPU_Mode.RR,time_slice=2)


