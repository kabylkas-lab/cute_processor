## A simple interface to translate Assembly commands into 
import os
import sys

def txt_translator():
    txt = input('Type in the name of the file: ')
    f2 = open(os.path.join(sys.path[0],'instructions.txt'), 'a')
    with open(os.path.join(sys.path[0],'%s.txt' % txt), 'r') as f1: 
        for line in f1:
            com = line.split()
            com[1] = com[1].split(',')[0]
            f2.write(COMMANDS_DICT[com[0]])
            for i in range(1,3):
                f2.write(ADDRESS_DICT[com[i]])
            f2.write('\n')

    f1.close()
    f2.close()
    print('Translation successfull!\n')
    

def input_translator():
    num_func = int(input('How many commands do you want to execute: '))
    print('Example: JMP R1, R2 \n')
    print('Available cmd: MV, ADD, SUB, MVI, JMP \n')
    print('Enter Assembly commands:\n')
    f = open(os.path.join(sys.path[0],'instructions.txt'), 'a')
    for i in range(0,num_func):
        user_input = input()
        com = user_input.split(' ', 3)
        com[1] = com[1].split(',')[0]
        f.write(COMMANDS_DICT[com[0]])
        for i in range(1,3):
            f.write(ADDRESS_DICT[com[i]])
        f.write('\n')

    f.close()
    print('Translation successfull!\n')

COMMANDS_DICT = {'ADD': '000', 'SUB': '001', 'MV': '010', 'MVI': '011', 'JMP': '100'}

ADDRESS_DICT = {'R1': '000', 'R2': '001', 'R3': '010','R4': '011', 
                'R5': '100', 'R6': '101', 'R7': '110', 'R8': '111'}

print('This program translates Assembly commands into instruction for cute-processor model\n')

## Translation of the input commands
mode = int(input('Type 0 if you want to translate file or 1 if you want to type them in: '))

(txt_translator() if mode == 0 else input_translator())

