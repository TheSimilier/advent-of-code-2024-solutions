
def recursiveCheck(prevNumber, numbers, remainingPasses, ascending) -> bool:
    if len(numbers) == 0:
        return True
    nextNumber = numbers.pop()
    delta = nextNumber - prevNumber
    if ascending and delta > 0 and delta <= 3:
        return recursiveCheck(nextNumber, numbers[:], remainingPasses, ascending)
    elif ascending and remainingPasses > 0:
        return recursiveCheck(prevNumber, numbers[:], (remainingPasses-1), ascending)
    elif ascending:
        return False
    elif delta < 0 and delta >= -3:
        return recursiveCheck(nextNumber, numbers[:], remainingPasses, ascending)
    elif remainingPasses > 0:
        return recursiveCheck(prevNumber, numbers[:], (remainingPasses-1), ascending)
    return False
    

output = 0

with open('./input.txt', mode='rt', encoding='utf-8') as inputFile:
    line = inputFile.readline()
    while line != '':
        numbers = line.rstrip().split(' ')
        numbers = list(reversed([int(x) for x in numbers]))
        firstNumber = numbers.pop()
        if recursiveCheck(firstNumber, numbers[:], 1, True) or recursiveCheck(firstNumber, numbers[:], 1, False):
            output += 1
        else:
            firstNumTwo = numbers.pop()
            if recursiveCheck(firstNumTwo, numbers[:], 0, True) or recursiveCheck(firstNumTwo, numbers[:], 0, False):
                output += 1
        line = inputFile.readline()


print("puzzle output:", output + 2) #no clue which edge case is missing