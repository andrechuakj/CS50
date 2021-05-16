# program to determine whether a dna belongs to
# someone in the list of people

# things to do:
# 1. create dictionary for all the individuals from data.csv
# 2. process the sequence given, counting the repeats of each STR
# 3. match the number of repeats for respective STR to that in the dictionary of individuals
# printing out the name of the individual if match, no match otherwise
import csv
import sys


def main():

    data = []
    numbersofrepeat = []

    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")
    datafile = sys.argv[1]
    sequencefile = sys.argv[2]

    with open(sequencefile) as sfile:
        sequence = sfile.read()

    with open(datafile) as dfile:

        reader = csv.reader(dfile)
        headers = next(reader)
        numSRT = len(headers)

    with open(datafile) as dfile:
        dreader = csv.DictReader(dfile)
        for name in dreader:
            for i in range(1, numSRT):
                name[headers[i]] = int(name[headers[i]])
            data.append(name)
    for i in range(1, len(headers)):
        number = count(headers[i], sequence)
        numbersofrepeat.append(number)
    check(numbersofrepeat, data, numSRT, headers)


def count(STR, sequence):
    counter = 0
    i = 0
    while i < len(sequence) - len(STR):
        countset = [0, i]
        num = counting(sequence, STR, countset)
        i = num[1]
        if num[0] > counter:
            counter = num[0]
    return counter


# "counting" function that takes in list "countset" which acts like a global variable where countset[0] is the 
# number of times the counting function managed to count a specific STR consecutively, and countset[1] is the character
# that the sequence has been read to currently
# function also returns an updated countset
def counting(sqnc, STR, countset):
    if STR == sqnc[countset[1]:countset[1] + len(STR)]:
        countset[1] = countset[1] + len(STR)
        countset[0] += 1
        countset = counting(sqnc, STR, countset)
    elif countset[0] > 0:
        return countset
    elif countset[0] == 0:
        countset[1] += 1
    return countset


def check(setofnum, data, numSRT, headers):
    for row in data:
        counter = 0
        for i in range(numSRT - 1):
            if row[headers[i + 1]] == setofnum[i]:
                counter += 1
        if counter == numSRT - 1:
            print(row[headers[0]])
            return

    print("No match")
    return       


if __name__ == "__main__":
    main()