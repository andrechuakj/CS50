import csv
import sys

if len(sys.argv) != 3:
    sys.exit("Usage: python dna.py data.csv sequence.txt")
datafile = sys.argv[1]
sequencefile = sys.argv[2]

with open(sequencefile) as sfile:
    sequence = sfile.read()


with open(datafile) as dfile:
    reader = csv.reader(dfile)
    headers = next(reader)
#    nNumSRT = len(headers) + 1
    dreader = csv.DictReader(dfile)
    
print(headers)
print(len(headers))
# print(length)
# print(headers[1] + "\n" + numSRT)