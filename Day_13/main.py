result = 0
costA = 3
costB = 1
with open('./input.txt', mode='rt', encoding='utf-8') as inputFile:
    line = inputFile.readline()
    a = 0
    b = 0
    c = 0
    d = 0
    e = 0
    f = 0
    while line != '':
        values = []
        if 'A:' in line:
            values = line.rstrip().split('+')
            a = int(values[1].split(',')[0])
            d = int(values[2])
        elif 'B:' in line:
            values = line.rstrip().split('+')
            b = int(values[1].split(',')[0])
            e = int(values[2])
        elif ':' in line:
            values = line.rstrip().split('=')
            c = int(values[1].split(',')[0]) + 10000000000000 #pzl2
            f = int(values[2]) + 10000000000000 #pzl2
            x = (e*c-b*f)/(a*e-b*d)
            y = (f-d*x)/e
            if x == int(x) and y == int(y):
                result += x * costA + y * costB

            a = 0
            b = 0
            c = 0
            d = 0
            e = 0
            f = 0

        line = inputFile.readline()



print("puzzle 1 result:", result)