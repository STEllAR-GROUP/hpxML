#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jun 19 12:57:03 2018

@author: gabriel
"""

# importing libraries
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as colors

### Reading data file ###
#filename="./files/data_chunk.dat"
#filename="./files/train.dat"
#filename="./files/train_matrix.dat"
#filename="./files/train_matrix_100.dat"
#filename='./files/chunk-stability.dat'
#filename='.files/train_matrix_50_rep.dat'
filename="./files/train_matrix_big.dat"

Xdata=[]
Execution_times=[]
Ydata=[]
with open(filename,"r") as file:
    n_experiments,n_features,n_targets=[int(j) for j in file.readline().split()]
    targets=np.array([float(j) for j in file.readline().split()[n_features:n_features+n_targets]])
    for i in range(n_experiments):
        line=file.readline().split()
        Xdata.append([float(j) for j in line[0:n_features]])
        Execution_times.append([float(j) for j in line[n_features:]])


### Generate data arrays ###
Xdata=np.array(Xdata)
Execution_times=np.array(Execution_times)


for i in range(Xdata.shape[0]):
    for j in range(n_targets):
        if targets[j]*Xdata[i][4]<1:
            Execution_times[i][j]=100

Ydata=targets[np.where(Execution_times==np.min(Execution_times,axis=1).reshape((-1,1)))[1]]
plt.figure(1)


#%%
##relative variance of time executions
def rel_var(Execution_Times):
    var_list=[]
    for row in Execution_Times:
        elements=row[row != 100]
        var_list.append(np.var(elements)/np.mean(elements)**2)
    return np.array(var_list)

##variance
def var(Execution_Times):
    var_list=[]
    for row in Execution_Times:
        elements=row[row != 100]
        var_list.append(np.var(elements))
    return np.array(var_list)
variance=var(Execution_times) 
rel_variance=rel_var(Execution_times)       


 #%%
#plot variance with respect to 2 variables
plt.scatter(Xdata[:,5],Xdata[:,4], s=50, linewidths=4, c=rel_variance*100, cmap=plt.cm.jet,norm=colors.LogNorm(),)
plt.colorbar()
plt.xlabel("Number of threads")
plt.ylabel("Matrix size")


########2D plot #############################3
#%%
##plotting dependance of Y with respect to both ite and Nthreads
plt.scatter(Xdata[:,5],Xdata[:,4], s=200, linewidths=4, c=Ydata, cmap=plt.cm.jet,norm=colors.LogNorm())
plt.xlim([1.5,14.5])
#plt.yscale('log')
plt.colorbar()
plt.xlabel("Number of threads")
plt.ylabel("Matrix Size")
