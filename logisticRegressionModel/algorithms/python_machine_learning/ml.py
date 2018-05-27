# -*- coding: utf-8 -*-

# importing libraries
import numpy as np
from sklearn import svm,neural_network,neighbors
from sklearn.model_selection import cross_val_score
import tests as ts

### Reading data file ###
filename="data_chunk.dat"
#filename="data_prefetch.dat"

targets=np.array([0.001,0.01,0.1,0.5])   #chunk size candidates
#targets=np.array([1,2,3,4,5,6])  #prefetching distance candidates


Xdata=[]
Execution_times=[]
Ydata=[]
with open(filename,"r") as file:
    n_experiments,n_features,n_targets=[int(j) for j in file.readline().split()]
    for i in range(n_experiments):
        line=file.readline().split()
        Xdata.append([float(j) for j in line[0:n_features]])
        Execution_times.append([float(j) for j in line[n_features:]])


### Generate data arrays ###
Xdata=np.array(Xdata)
Execution_times=np.array(Execution_times)
Ydata=targets[np.where(Execution_times==np.min(Execution_times,axis=1).reshape((-1,1)))[1]]

#%% Rescaling [0,1] for every feature
for i in range(Xdata.shape[1]):
    Xdata[:,i]=(Xdata[:,i]-np.min(Xdata[:,i]))/(np.max(Xdata[:,i])-np.min(Xdata[:,i]))

#%% OPTIONAL
# Log is applied to the targets to make sure they have the same scale
# This is just an experiment
#Ydata=np.log(Ydata)

#%% SMV REGRESSION
print("SVM Regression")

#Hyperparameters:
# gamma          #Kernel function coefficient | float | (Default is 1/n_features)
# kernel         #Kernel function | ‘linear’, ‘poly’, ‘rbf’, ‘sigmoid’ or ‘precomputed’ | (Default is "rbf")
# C              #Parameter of error function | float | (Default is 1)
# epsilon        #Epsilon in the SVMR model | float | (Default is 0.1)

svmr=svm.SVR(gamma=0.05,C=1,epsilon=0.1,kernel='rbf')

#mean absolute error cross validation
scores = cross_val_score(svmr, Xdata, Ydata, scoring='neg_mean_absolute_error', cv=3)
print("Cross validation with mean absolute error : %0.2f (+/- %0.2f)" % (scores.mean(), scores.std() * 2))

#relative error cross validation (my implementation)
print("Cross validation with mean relative error :"+str(np.mean(ts.cross_validation_relative(svmr,Xdata,Ydata,3)))+" %")
print("Cross validation with mean relative error on log(Ydata) :"+str(np.mean(ts.cross_validation_relative_log(svmr,Xdata,Ydata,3)))+" %")

#%% NEURAL NETWORK
print("Neural-Network Regression")

#Hyperparameters
#solver                #method used to minimize loss function | "lbfgs", "sgd", "adam" | (Default is "adam")
#activation            #activation function used in the hidden layers | "relu","tanh',"logistic","identity" | (Default is "relu")
#hidden_layer_sizes    # sizes of the hidden layers of the network

nnr=neural_network.MLPRegressor(hidden_layer_sizes=(10,10),solver="lbfgs",activation="relu")

#mean absolute error cross validation
scores = cross_val_score(nnr, Xdata, Ydata, scoring='neg_mean_absolute_error', cv=3)
print("Cross validation with mean absolute error : %0.2f (+/- %0.2f)" % (scores.mean(), scores.std() * 2))

#relative error cross validation (my implementation)
print("Cross validation with mean relative error :"+str(np.mean(ts.cross_validation_relative(nnr,Xdata,Ydata,3)))+" %")
print("Cross validation with mean relative error on log(Ydata) :"+str(np.mean(ts.cross_validation_relative_log(nnr,Xdata,Ydata,3)))+" %")


#%% k-NearestNeighbors
print("Nearest Neighbors Regression")

#Hyperparameters
#n_neighbors      #number of neighbors considered | int | (Default is 5)
#weights          #determines the weights associated with the neighbors when calculating the average | "uniform","distance" |
                  #(Default is "uniform')

knnr=neighbors.KNeighborsRegressor(n_neighbors=4,weights="uniform")
#mean absolute error cross validation

scores = cross_val_score(knnr, Xdata, Ydata, scoring='neg_mean_absolute_error', cv=3)
print("Cross validation with mean absolute error : %0.2f (+/- %0.2f)" % (scores.mean(), scores.std() * 2))

#relative error cross validation (my implementation)
print("Cross validation with mean relative error :"+str(np.mean(ts.cross_validation_relative(knnr,Xdata,Ydata,3)))+" %")
print("Cross validation with mean relative error on log(Ydata) :"+str(np.mean(ts.cross_validation_relative_log(knnr,Xdata,Ydata,3)))+" %")



