import random
word = list(random.choice(list(open('long-words.txt'))))
try:
  limit = sys.argv[1]
except:
  Exception
  limit=6
mistakes=0; found=False; finished=False; guessed = ['_'*len(word)]
while mistakes<limit and not finished:
  guess = str(raw_input('Guess a letter: '))
  for i in range(len(word)):
    if guess == word[i]:
      guessed[i] = guess
      found = True
  if not found:
    mistakes=mistakes+1
    print "Number of attempts left: ",limit-mistakes
  else:
    print guessed
    found = False