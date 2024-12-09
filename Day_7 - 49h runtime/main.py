import math

finalSum = 0

with open('./input.txt', mode='rt', encoding='utf-8') as inputFile:
    line = inputFile.readline()
    while line != '':
        uncleanedNumbers = line.rstrip().split(':')
        result = int(uncleanedNumbers[0])
        cleanedNumbers = uncleanedNumbers[1].split(' ')
        finalNumbers = [int(x) for x in cleanedNumbers if x]

        for i in range(0, math.factorial(len(finalNumbers))):
            testSum = 0
            for j in range(0, len(finalNumbers)):
                if j == 0:
                    testSum = finalNumbers[j]
                    continue
                if i % math.exp2(j) >= math.exp2(j) / 2:
                    testSum += finalNumbers[j]
                else:
                    testSum *= finalNumbers[j] 

            if testSum == result:
                finalSum += testSum
                break

        line = inputFile.readline()



print("puzzle 1 result:", finalSum)