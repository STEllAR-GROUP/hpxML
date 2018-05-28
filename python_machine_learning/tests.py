#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu May 24 21:02:46 2018

@author: gabriel
"""

import numpy as np
import math

def cluster_maker(Xdata,Ydata,k):
    delta=int(math.floor(Xdata.shape[0]/k))
    cluster=[[Xdata[i*delta:(i+1)*delta+int(i==(k-1))*Xdata.shape[0],:],Ydata[i*delta:(i+1)*delta+int(i==(k-1))*Xdata.shape[0]]] for i in range(k)]
    return cluster
    
def merge(cluster,index):
    X=cluster[int(index==0)][0]
    Y=cluster[int(index==0)][1]
    for i in range(int(index==0)+1,len(cluster)):
        if i==index:
            pass
        else:
            X=np.vstack((X,cluster[i][0]))
            Y=np.append(Y,cluster[i][1])
            
    return X,Y
       
def cross_validation_relative(model,Xdata,Ydata,k):
    error=0
    cluster=cluster_maker(Xdata,Ydata,k)
    for i in range(k):
        X,Y=merge(cluster,i)
        model.fit(X,Y)
        error+=np.abs((model.predict(cluster[i][0])-cluster[i][1])/(cluster[i][1]))*100
    error/=k
    return error

def cross_validation_relative_log(model,Xdata,Ydata,k):
    error=0
    cluster=cluster_maker(Xdata,np.log(Ydata),k)
    for i in range(k):
        X,Y=merge(cluster,i)
        model.fit(X,Y)
        error+=np.abs((np.exp(model.predict(cluster[i][0]))-np.exp(cluster[i][1]))/np.exp(cluster[i][1]))*100
    error/=k
    return error

    