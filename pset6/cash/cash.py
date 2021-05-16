# number of coins needed for change
from cs50 import get_float


change = -1.0
# input the amount of change required
while change < 0:
    change = int(get_float("Changed owed: ") * 100)
counter = 0
# list of coins available
coins = [25, 10, 5, 1]
# iterate through each coin and find out if the biggest coin can be used, and if so, how many
# continues in descending coin value
for coin in coins:
    if int(change // coin) > 0:
        counter += int(change // coin)
        change -= int(change // coin) * coin
print(counter)

