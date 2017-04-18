import sys,getopt


"""
get input from stdin
return : list of strings
"""
def getInput():
    res = list()
    while(True):
        try:
            s = raw_input()
            res.append(s)
        except EOFError,e:
            # print e
            break
    # print res
    return res


"""
divide a list of input strings into  partitions to handle
return : list of partition
"""
def divideIntoPart(lines):
    partition_list = list()
    partition = list()
    for line in lines:
        if(line[0]=='\\' or line[0]=='-'):
            continue
        if(line[0] not in ['<','-','>'] and len(partition)!=0):
            partition_list.append(partition)
            partition = list()
            partition.append(line)
        else:
            if(line[0] in ['<','-','>']):
                partition.append(line[2:])
            else:
                partition.append(line)
    if(len(partition)!=0):
        partition_list.append(partition)
    return partition_list

"""
get one operator(str) and two operator list from an operator string
return (operator,left,right)
"""
def getOperatorList(operatorStr):
    operator = ''
    if('a' in operatorStr):
        operator = 'a'
    elif ('d' in operatorStr):
        operator = 'd'
    elif ('c' in operatorStr):
        operator = 'c'
    left = operatorStr.split(operator)[0].split(',')
    right = operatorStr.split(operator)[1].split(',')

    return (operator,left,right)
"""
use a partition(list of str) and the new_file(str) to generate the old content
return : list of contents
"""
def patchPartition(partition,contents):

    lines = contents

    operator,left,right = getOperatorList(partition[0])


    if (operator == 'a'):
        right_index = map(lambda s:int(s),right)
        for r in range(right_index[0],right_index[-1]+1):
            lines[r-1] = ""
    if (operator == 'd'):
        left_index = map(lambda s: int(s), left)
        right_index = int(right[0])
        for l_index,l in enumerate(range(left_index[0],left_index[-1]+1)):
            lines[right_index-1] += "%s\n" % (partition[1+l_index])
    if (operator == 'c'):
        left_index = map(lambda s: int(s), left)
        right_index = map(lambda s: int(s), right)

        # new_content_list = partition[1 + len(left_index):]

        previous_content = ""
        for l_index,l in enumerate(range(left_index[0],left_index[-1]+1)):
            previous_content += partition[1+l_index] + "\n"

        for r_index,r in enumerate(range(right_index[0],right_index[-1]+1)):
            lines[r-1] = ""

        lines[right_index[0]-1] = previous_content

    return lines

"""
get lines from a file
return the list of lines of a file
"""
def getLinesFromFile(filename):

    with open(filename,mode='r') as f:
        lines = f.readlines()

    return lines


def patch(new_filename):
    lines = getInput()
    partition_list = divideIntoPart(lines)
    content = getLinesFromFile(new_filename)

    for index,partition in enumerate(partition_list):
        print "Patch ==> [%d%%]" % (index*100/len(partition_list))
        content = patchPartition(partition,content)

    return content


def main(argv):

    inputfile = ''
    outputfile = ''
    hint = 'diff <old_file> <new_file> | patch.py -i <inputfile> -o <outputfile>'
    try:

        opts, args = getopt.getopt(argv,"hi:o:",["ifile=","ofile="])
    except getopt.GetoptError:
        print hint
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print hint
            sys.exit()
        elif opt in ("-i", "--ifile"):
            inputfile = arg
        elif opt in ("-o", "--ofile"):
            outputfile = arg

    content = patch(inputfile)
    with open(outputfile,'w')  as outf:
        for line in content:
            if(len(line)!=0):
                outf.write(line)

    print "Patch successfully."




if(__name__=="__main__"):
    main(sys.argv[1:])