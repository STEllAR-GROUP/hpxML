# -*- coding: utf-8 -*-

# importing libraries
import numpy as np
from sklearn import svm,neural_network,neighbors
from sklearn.model_selection import cross_val_score
from sklearn.ensemble import RandomForestRegressor
import tests as ts

### Reading data file ###
#filename='files/train_matrix_big.dat'
filename='files/train_matrix.dat'
#filename='files/Zahra/data_chunk.dat'
#filename='files/train.dat'

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

for i in range(n_experiments):
    for j in range(n_targets):
        if targets[j]*Xdata[i][4]<1:
            Execution_times[i][j]=100

#remove feature (optional)
Xdata=Xdata[:,[4,5]]

#remove candidates (optinal)
Execution_times=Execution_times[:,[0,2,4,6]]
targets=targets[[0,2,4,6]]

Ydata=targets[np.where(Execution_times==np.min(Execution_times,axis=1).reshape((-1,1)))[1]]

#%% Rescaling [0,1] for every feature
for i in range(Xdata.shape[1]):
    Xdata[:,i]=(Xdata[:,i]-np.min(Xdata[:,i]))/(np.max(Xdata[:,i])-np.min(Xdata[:,i]))

#%% SMV REGRESSION
print("SVM Regression")

#Hyperparameters:
# gamma          #Kernel function coefficient | float | (Default is 1/n_features)
# kernel         #Kernel function | ‘linear’, ‘poly’, ‘rbf’, ‘sigmoid’ or ‘precomputed’ | (Default is "rbf")
# C              #Parameter of error function | float | (Default is 1)
# epsilon        #Epsilon in the SVMR model | float | (Default is 0.1)

svmr=svm.SVR(gamma=1,C=1,epsilon=0.05,kernel='rbf')

#mean absolute error cross validation
scores = cross_val_score(svmr, Xdata, Ydata,scoring='neg_mean_squared_error', cv=5)
print("Cross validation with mean squared error : %0.4f (+/- %0.4f)" % (scores.mean(), scores.std() * 2))
print("Cross validation with mean relative error on log(Ydata) :"+str(np.mean(ts.cross_validation_squared_log(svmr,Xdata,Ydata,4)))+"+/-"+str(2*np.std(ts.cross_validation_squared_log(svmr,Xdata,Ydata,4))))


#%% NEURAL NETWORK
print("Neural-Network Regression")

#Hyperparameters
#solver                #method used to minimize loss function | "lbfgs", "sgd", "adam" | (Default is "adam")
#activation            #activation function used in the hidden layers | "relu","tanh',"logistic","identity" | (Default is "relu")
#hidden_layer_sizes    # sizes of the hidden layers of the network

nnr=neural_network.MLPRegressor(hidden_layer_sizes=(10,10),solver="lbfgs",activation="relu",random_state=0)

#mean absolute error cross validation
scores = cross_val_score(nnr, Xdata, Ydata, scoring='neg_mean_squared_error', cv=6)
print("Cross validation with mean absolute error : %0.4f (+/- %0.4f)" % (scores.mean(), scores.std() * 2))
print("Cross validation with mean relative error on log(Ydata) :"+str(np.mean(ts.cross_validation_squared_log(nnr,Xdata,Ydata,4)))+"+/-"+str(2*np.std(ts.cross_validation_squared_log(nnr,Xdata,Ydata,4))))


#%% k-NearestNeighbors
print("Nearest Neighbors Regression")

#Hyperparameters
#n_neighbors      #number of neighbors considered | int | (Default is 5)
#weights          #determines the weights associated with the neighbors when calculating the average | "uniform","distance" |
                  #(Default is "uniform')

knnr=neighbors.KNeighborsRegressor(n_neighbors=3,weights="uniform")
#mean absolute error cross validation

scores = cross_val_score(knnr, Xdata, Ydata, scoring='neg_mean_squared_error', cv=4)
print("Cross validation with mean absolute error : %0.4f (+/- %0.4f)" % (scores.mean(), scores.std() * 2))
print("Cross validation with mean relative error on log(Ydata) :"+str(np.mean(ts.cross_validation_squared_log(knnr,Xdata,Ydata,6)))+"+/-"+str(2*np.std(ts.cross_validation_squared_log(knnr,Xdata,Ydata,6))))


#%% Random Forest regression
print("Random Forest Regression")
rfr=RandomForestRegressor(random_state=0)
#mean absolute error cross validation

scores = cross_val_score(rfr, Xdata, Ydata, scoring='neg_mean_squared_error', cv=6)
print("Cross validation with mean absolute error : %0.5f (+/- %0.4f)" % (scores.mean(), scores.std() * 2))
print("Cross validation with mean relative error on log(Ydata) :"+str(np.mean(ts.cross_validation_squared_log(rfr,Xdata,Ydata,6)))+"+/-"+str(2*np.std(ts.cross_validation_squared_log(rfr,Xdata,Ydata,5))))











#%% Results visualisation
import matplotlib.pyplot as plt
import matplotlib.colors as colors
import random as rnd

plt.figure(1)
def jitter(Ydata_copy,Ypred_copy):
    for i in range(Ydata_copy.shape[0]):
        Ydata_copy[i]*= rnd.uniform(0.89, 1.11)
        Ypred_copy[i]*=rnd.uniform(0.92, 1.08)
rfr.fit(Xdata,np.log(Ydata))
Ypred=np.exp(rfr.predict(Xdata))
Ydata_copy=np.copy(Ydata)
Ypred_copy=np.copy(Ypred)
jitter(Ydata_copy,Ypred_copy)
plt.scatter(Ydata_copy,Ypred_copy,edgecolor='k')
plt.plot(np.logspace(-3,0,10),np.logspace(-3,0,10),'k--')
plt.xscale('log')
plt.yscale('log')
plt.xlabel("Optimal Chunk Size")
plt.ylabel("Prediction")

