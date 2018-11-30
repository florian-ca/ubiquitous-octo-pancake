#!/usr/bin/python
import time;  # This is required to include time module.

ticks = time.time()

for i in range(0,10000):
	for j in range (0,10000):
		h=i
print "time: ", time.time()-ticks ," secondes"