import sys

dict = {}
f = open(sys.argv[1])
f.next()
for line in f:
  list = line.split(',')
  grade = list[-1]
  id = list[0]
  if grade not in dict:
    dict[grade] = [id]
  else:
    dict[grade].append(id)
for key in dict.viewkeys():
  print "grade: ",key.strip(),'  Count: ',len(dict[key])
  print "Students IDs: ",dict[key]