# Machine Learning Implementation with Scikit-Learn

This code was tested on Python3
To install the requirements use:
` ` `
python3 -m pip install -r requirement.txt
` ` `

This scripts reads the data files located in the files/ folder and applies Machine Learning Regressions to fit the data using a regression algorithms
The algorithms currently used are:

1. Support Vector Machine Regression (http://scikit-learn.org/stable/modules/generated/sklearn.svm.SVR.html#sklearn.svm.SVR)
2. Neural Network Regression (http://scikit-learn.org/stable/modules/generated/sklearn.neural_network.MLPRegressor.html#sklearn.neural_network.MLPRegressor)
3. K-Nearest-Neighbors Regression (http://scikit-learn.org/stable/modules/generated/sklearn.neighbors.KNeighborsRegressor.html#sklearn.neighbors.KNeighborsRegressor)
4. Random Forest regression (http://scikit-learn.org/stable/modules/generated/sklearn.ensemble.RandomForestRegressor.html)


To evaluate the regressoin, the k-fild cross validation method is used. However, since the target values are on different scales, I must fit the log(Chunk-size) to have target values on the same scale. The chunk-size can be predicted by taking the exponential of the prediction of the regressions. Since scikit's cross validation doesn't support this method, I had to implement my own cross validation technique which outputs the error. The *function cross_validation_squared_log()* in the file tests.py does the following:

<a href="http://www.codecogs.com/eqnedit.php?latex=\Delta=\frac{1}{n_{exp}}\sum_{n=1}^{n_{exp}}\frac{|y_n-exp(y'_n)|}{|y_n|}&space;\times&space;100&space;\%" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\Delta=\frac{1}{n_{exp}}\sum_{n=1}^{n_{exp}}(y_n-exp(f(x_n)))^2&space;\times&space;100&space;\%" title="bob" /></a>


