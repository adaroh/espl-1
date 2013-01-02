import random
word = list(random.choice(list(open('long-words.txt'))))
try: #attempt to get max nomber of tries from cli argument, default to 6
  limit = sys.argv[1]
except:
  Exception
  limit=6
mistakes=0; matches=0; match=False; finished=False; guessed = ['_'*len(word)]
while mistakes<limit and not finished:
  guess = str(raw_input('Guess a letter: '))
  if guess == 'quit':
    exit
  for i in range(len(word)-1):
    if guess == word[i]:
      guessed[i] = guess
      match = True
      matches = matches+1
  if not match:
    mistakes = mistakes+1
    print "guessed: ",guessed
    print "Steps from gallows: ",limit-mistakes, "Word so far: ",guessed
  else:
    print guessed
    match = False
  if matches == len(word):
    finished = True
if mistakes == limit:
  print "** Uh oh: you've run out of steps. You're on the platform.. and <SNAP!>"
  print "** The word you were trying to guess was ",word
if finished:
  print "** You've been pardoned!! Well done!  The word was ",word