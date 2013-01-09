import random
word = (random.choice(list(open('long-words.txt'))))
try: #attempt to get max nomber of tries from cli argument, default to 6
  limit = sys.argv[1]
except:
  Exception
  limit=6
length=len(word)-1
mistakes=0; matches=0; match=False; finished=False; guessed = ["_ "]*length; miss=[]
while mistakes<limit and not finished:
  guess = str(raw_input('Guess a letter: '))
  if guess == 'quit':
    break
  for i in range(length):
    if guess == word[i]:
      guessed[i] = guess
      match = True
      matches = matches+1
  if not match:
    miss.append(guess)
    mistakes = mistakes+1
    print "Steps from gallows: ",limit-mistakes, "Word so far: ",''.join(guessed)
    print "Missed: ",miss
  else:
    print ''.join(guessed)
    match = False
  if matches == (length):
    finished = True
if mistakes == limit:
  print "** Uh oh: you've run out of steps. You're on the platform.. and <SNAP!>"
  print "** The word you were trying to guess was ",word
if finished:
  print "** You've been pardoned!! Well done!  The word was ",word