result = 0
pzl2result = 0

rules = {}

with open('./input.txt', mode='rt', encoding='utf-8') as inputFile:
    line = inputFile.readline()
    while line != '':
        if '|' in line:
            numbers = line.split('|')
            rules.setdefault(numbers[0].rstrip(), []).append(numbers[1].rstrip())
        elif ',' in line:
            numbers = line.rstrip().split(',')

            isCorrect = True

            for index in range(len(numbers)):
                currNum = numbers[index].split('\\')[0]
                for jndex in range(index, len(numbers)):
                    nextNum = numbers[jndex].split('\\')[0]
                    if nextNum in rules.keys():
                        rulesForNum = rules[numbers[jndex]]
                        if currNum in rulesForNum:
                            isCorrect = False

            if isCorrect:
                middleIndex = int((len(numbers) + 1) / 2) -1
                result += int(numbers[middleIndex])
            else:
                while not isCorrect:
                    isCorrect = True
                    for index in range(len(numbers)):
                        currNum = numbers[index].split('\\')[0]
                        for jndex in range(index, len(numbers)):
                            nextNum = numbers[jndex].split('\\')[0]
                            if nextNum in rules.keys():
                                rulesForNum = rules[numbers[jndex]]
                                if currNum in rulesForNum:
                                    isCorrect = False
                                    numbers[index] = nextNum
                                    numbers[jndex] = currNum
                                    break

                middleIndex = int((len(numbers) + 1) / 2) -1
                pzl2result += int(numbers[middleIndex])

                
        line = inputFile.readline()



print("puzzle 1 result:", result)
print("puzzle 2 result:", pzl2result)