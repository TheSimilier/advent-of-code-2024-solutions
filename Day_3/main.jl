#first and probably last time using julia lol lmao

file = open("./input.txt", "r")
inputStr = read(file, String)

accum = 0
validMulChars = ['m', 'u', 'l', '(', 'd', ',', 'n', ')']
wasValidMul = false
lastMulIndex = 0
num1 = -1
num2 = -1
numDigit1 = "-1"
numDigit2 = "-1"
numDigit3 = "-1"

#puzzle 2
mulAllowed = true
validDoChars = ['d', 'o', '(', ')']
validDontChars = ['d', 'o', 'n', ''', 't', '(', ')']
lastDoIndex = 0
lastDontIndex = 0
wasValidDo = false
wasValidDont = false

for currChar in inputStr
    #puzzle 1 global values
    global accum
    global lastMulIndex
    global num1
    global num2
    global numDigit1
    global numDigit2
    global numDigit3
    global wasValidMul
    #puzzle 2 global values
    global mulAllowed
    global lastDoIndex
    global lastDontIndex
    global wasValidDo
    global wasValidDont
    #who thought making local scope like this was a good idea

    #puzzle2 do/dont  instruction processing
    isValidDo = currChar == validDoChars[lastDoIndex+1]
    isValidDont = currChar == validDontChars[lastDontIndex+1]

    if isValidDo
        wasValidDo = true
        lastDoIndex += 1
        if lastDoIndex == length(validDoChars)
            mulAllowed = true
            lastDoIndex = 0
            wasValidDo = false
        end
    elseif wasValidDo
        lastDoIndex = 0
        wasValidDo = false
    end
    if isValidDont
        wasValidDont = true
        lastDontIndex += 1
        if lastDontIndex == length(validDontChars)
            mulAllowed = false
            lastDontIndex = 0
            wasValidDont = false
        end
    elseif wasValidDont
        lastDontIndex = 0
        wasValidDont = false
    end

    if isValidDo || isValidDont
        continue
    end

    #puzzle1 mul instruction processing
    isValidMul = currChar == validMulChars[lastMulIndex+1] #is valid if current character matches next character in validation list
    isValidMul = isValidMul || (validMulChars[lastMulIndex+1] == 'd' && isdigit(currChar)) #is valid if current character is a number and next valid index denotes number 1
    isValidMul = isValidMul || (validMulChars[lastMulIndex+1] == 'n' && isdigit(currChar)) #is valid if current character is a number and next valid index denotes number 2
    isValidMul = isValidMul || (validMulChars[lastMulIndex+1] == ',' && isdigit(currChar)) #obviously still valid if we are presently a number
    isValidMul = isValidMul || (validMulChars[lastMulIndex+1] == ')' && isdigit(currChar)) # .

    if isValidMul && mulAllowed
        wasValidMul = true
        #only iterate valid index if not exceeding index length (shouldnt happen) and if next index would be end of number but current char is number
        if lastMulIndex < length(validMulChars) && !((validMulChars[lastMulIndex+1] == ',' || validMulChars[lastMulIndex+1] == ')') && isdigit(currChar))
            lastMulIndex += 1
        end

        # if current character is digit, store digit
        if (validMulChars[lastMulIndex] == 'd' || validMulChars[lastMulIndex] == 'n') && isdigit(currChar)
            if numDigit1 == "-1"
                numDigit1 = currChar
            elseif numDigit2 == "-1"
                numDigit2 = currChar
            elseif numDigit3 == "-1"
                numDigit3 = currChar
            else
                isValidMul = false
            end
        end
            
        #if current character is end of number, store digits to number 1 or 2
        if currChar == ',' || currChar == ')'
            lastMulIndex += 1 #iterate valid index past number on number exit
            numStr = string(numDigit1)
            if numDigit2 != "-1"
                numStr *= string(numDigit2)
            end
            if numDigit3 != "-1"
                numStr *= string(numDigit3)
            end

            if currChar == ','
                num1 = parse(Int, numStr)
            else
                num2 = parse(Int, numStr)
            end

            #clear digit storage
            numDigit1 = "-1"
            numDigit2 = "-1"
            numDigit3 = "-1"
        end

        #if current char is end of instruction, execute
        if currChar == ')'
            accum += num1 * num2
            isValidMul = false #force reset after execution
        end
    end

    #if char not valid, reset storage
    if !isValidMul && wasValidMul
        wasValidMul = false
        lastMulIndex = 0
        num1 = -1
        num2 = -1
        numDigit1 = "-1"
        numDigit2 = "-1"
        numDigit3 = "-1"
    end
end
@show accum
