#!/usr/bin/python
import random,sys
word = (random.choice(list(open('long-words.txt'))))
try: #attempt to get max nomber of tries from cli argument, default to 6
  limit = int(sys.argv[1])
except:
  Exception
  limit=6
length=len(word)-1
mistakes=0; matches=0; match=False; finished=False; guessed = ["_ "]*length; letters=[]
while mistakes<limit and not finished:
  guess = str(raw_input('Guess a letter: '))
  if len(guess)>1:
    if guess == 'quit':
      break
    else:
      print "Uh oh: You can only guess a single letter at a time"
  else:
    for i in range(length):
      if guess == word[i]:
	guessed[i] = guess
	match = True
	matches = matches+1
    if guess not in letters:
	letters.append(guess)
    if not match:
      mistakes = mistakes+1
      print "Steps from gallows: ",limit-mistakes, "  Word so far: ",''.join(guessed)
      print "Guessed: ",letters
    else:
      print ''.join(guessed) #change the list to string to look pretty
      print "Guessed: ",letters
      match = False
    if matches == (length):
      finished = True
if mistakes == limit:
  print "** Uh oh: you've run out of steps. You're on the platform.. and <SNAP!>"
  print "** The word you were trying to guess was ",word
if finished:
  print "** You've been pardoned!! Well done!  The word was ",word