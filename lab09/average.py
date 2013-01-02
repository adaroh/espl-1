import sys

f = open(sys.argv[1])
sum = 0.
count = 0.
f.next()
for line in f:
  print line,
  list = line.split(',')
  sum=sum+float(list[-1])
  count=count+1
print "The average grade is: ",sum/count