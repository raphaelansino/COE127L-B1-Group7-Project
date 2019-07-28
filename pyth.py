# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt
import csv

x = []
y = []
z = []

with open('pyth.csv','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        x.append(int(row[0]))
        y.append(float(row[1]))
        z.append(float(row[2]))
        
plt.plot(x,y, label='C++ Time', color='b')  
plt.plot(x,z, label='OpenMP Time', color='r')  



plt.xlabel('Cores')
plt.ylabel('Average Time (ms)')

plt.title('OpenMP vs C++Processing Time')
plt.legend()
plt.show()
