#partition
def dupe(possible):
    temp = []
    for item in possible: 
        temp.append(item) 
        for i in range(1, 10, 1):
            if i == 1:
                if item.count(1) > 1: #removes lists with more than a single 1
                    temp.remove(item)
            else:
                if item.count(i) > 2:  #removes lists with more than 2 of a single number
                    temp.remove(item)
    return temp

def partition(value, bordering, freebies):
    value = value[0]
    bordering = bordering[0]
    possible = []
    if value <= 9: #1 digit 
        if freebies and bordering:
            possible.append([value, "2"])
        elif freebies:
            possible.append([value, "3"])
        else:
            possible.append([value, "0"])
    if 3 <= value <= 18: #2 digit
        for x in range(1, 10, 1):
            if 0 < value - x <= 9:
                if freebies and bordering:
                    possible.append(sorted([x, value-x]) + ["1"]) #sorts added list for easier filtering later
                elif freebies:
                    possible.append(sorted([x, value-x]) + ["2"])
                else:
                    possible.append(sorted([x, value-x]) + ["0"])
    if 5 <= value <= 26: #3 digit
        for x in range(1, 10, 1):
            sum1 = value - x
            if sum1 > 0:
                for y in range(1, 10, 1):
                    if 0 < sum1 - y <= 9:
                        if freebies and bordering:
                            possible.append(sorted([x, y, sum1-y]) + ["0"]) #sorts added list for easier filtering later
                        elif freebies:
                            possible.append(sorted([x, y, sum1-y]) + ["1"])
                        else:
                            possible.append(sorted([x, y, sum1-y]) + ["0"])
    if bordering == False:
        if 8 <= value <= 34: #4 digits
            for x in range(1, 10, 1):
                sum1 = value - x
                if sum1 > 0:
                    for y in range(1, 10, 1):
                        sum2 = sum1 - y
                        if sum2 > 0:
                            for z in range(1, 10, 1):
                                if 0 < (sum2 - z) <= 9:
                                    possible.append(sorted([x, y, z, sum2-z]) + ["0"]) #sorts added list for easier filtering later
    temp = []
    for item in possible: #filters duplicates
        if item not in temp:
            temp.append(item)
    possible = temp
    return dupe(possible)

print(partition([22], [True], True))