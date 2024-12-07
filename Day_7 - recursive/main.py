from enum import Enum
class Operator(Enum):
    Addition = 1
    Multiplication = 2
    Concatenation = 3

def recursiveCheck(goingResult, expectedResult, numbers, operator: Operator) -> bool:
    if len(numbers) == 0:
        return goingResult == expectedResult
    nextNumber = numbers.pop()
    if operator == Operator.Addition:
        nextResult = goingResult + nextNumber
    elif operator == Operator.Multiplication:
        nextResult = goingResult * nextNumber
    else:
        nextResult = int(str(goingResult) + str(nextNumber))
    if (nextResult > expectedResult):
        return False
    if (nextResult == expectedResult):
        return True
    if not recursiveCheck(nextResult, expectedResult, numbers[:], Operator.Addition):
        if not recursiveCheck(nextResult, expectedResult, numbers[:], Operator.Multiplication):
            return recursiveCheck(nextResult, expectedResult, numbers[:], Operator.Concatenation)
    return True


finalSum = 0

with open('./input.txt', mode='rt', encoding='utf-8') as inputFile:
    line = inputFile.readline()
    while line != '':
        uncleanedNumbers = line.rstrip().split(':')
        result = int(uncleanedNumbers[0])
        cleanedNumbers = uncleanedNumbers[1].split(' ')
        finalNumbers = list(reversed([int(x) for x in cleanedNumbers if x]))

        firstNumber = finalNumbers.pop()
        if recursiveCheck(firstNumber, result, finalNumbers[:], Operator.Addition) or recursiveCheck(firstNumber, result, finalNumbers[:], Operator.Multiplication) or recursiveCheck(firstNumber, result, finalNumbers[:], Operator.Concatenation):
            finalSum += result

        line = inputFile.readline()



print("puzzle result:", finalSum)