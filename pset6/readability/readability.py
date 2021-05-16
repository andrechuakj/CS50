# program to determine readability of text
from cs50 import get_string


text = get_string("Text: ")
length = len(text)
letters = 0.0
words = 1.0
sentences = 0.0

# going through each character 1 by 1
# to determine if its letter, word, sentence
for i in range(length):
    if text[i].isalpha():
        letters += 1
    elif text[i] == " ":
        words += 1
    elif text[i] in [".", "!", "?"]:
        sentences += 1
        
L = letters / words * 100
S = sentences / words * 100
x = round(0.0588 * L - 0.296 * S - 15.8)
    
if x < 1:
    print("Before Grade 1")
elif x > 15:
    print("Grade 16+")
else:
    print("Grade " + str(x))