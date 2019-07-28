# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt
import csv

x = []
y = []
z = []

with open('cppout.csv','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        x.append(int(row[0]))
        y.append(float(row[1]))
        
plt.plot(x,y, label='Time')  


plt.xlabel('Cores')
plt.ylabel('Average Time (ms)')

plt.title('C++ Program Processing Time')
plt.legend()
plt.show()
