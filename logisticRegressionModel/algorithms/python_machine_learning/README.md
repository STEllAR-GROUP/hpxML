# Machine Learning Implementation with Scikit-Learn

This code was tested on Python3
To install the requirements use:
` ` `
python3 -m pip install -r requirement.txt
` ` `

This scripts reads the data files located at hpxML/logisticRegressionModel/algorithms/inputs/ and applies Machine Learning Regressions to fit the data using a continuous function.
The algorithms currently used are:

1. Support Vector Machine Regression (http://scikit-learn.org/stable/modules/generated/sklearn.svm.SVR.html#sklearn.svm.SVR)
2. Neural Network Regression (http://scikit-learn.org/stable/modules/generated/sklearn.neural_network.MLPRegressor.html#sklearn.neural_network.MLPRegressor)
3. K-Nearest-Neighbors Regression (http://scikit-learn.org/stable/modules/generated/sklearn.neighbors.KNeighborsRegressor.html#sklearn.neighbors.KNeighborsRegressor)

Note that the candidates for prefetching_distance are currently unknown so the code has only been tested on chuck_size,

One of my major problem right now is that there are too few candidates values for prefetching distance and chunk size and the values are on different scales {0.001,0.01,0.1,0.5}. This is problematic for fitting continuous regressions as points to be fitted are far appart. My temporary solution to this problem is to fit log(Y) instead of Y so the targets values are on the same scale. 
For example the subset for chunk_size becomes {-6.9,-4.6,-2.3,0.69} when applying log.

To evaluate the error on the of a regression current subset, the mean relative error must currently be used since the candidates are on different scales.

<a href="http://www.codecogs.com/eqnedit.php?latex=\Delta=\frac{1}{n_{exp}}\sum_{n=1}^{n_{exp}}\frac{|y_n-\hat{y}_n|}{|y_n|}&space;\times&space;100&space;\%" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\Delta=\frac{1}{n_{exp}}\sum_{n=1}^{n_{exp}}\frac{|y_n-\hat{y}_n|}{|y_n|}&space;\times&space;100&space;\%" title="\Delta=\frac{1}{n_{exp}}\sum_{n=1}^{n_{exp}}\frac{|y_n-\hat{y}_n|}{|y_n|} \times 100 \%" /></a>

However, the cross-validation algorithms used by scikit-learn don't support the mean relative error so my own algorithm for cross validation was implemented in tests.py as the function *cross_validation_relative()*. Another version of this function called *cross_validation_relative_log()* applies trains a regression with Y'=log(Y)  as data and outputs the mean relative error using this formula:

<a href="http://www.codecogs.com/eqnedit.php?latex=\Delta=\frac{1}{n_{exp}}\sum_{n=1}^{n_{exp}}\frac{|y_n-exp(y'_n)|}{|y_n|}&space;\times&space;100&space;\%" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\Delta=\frac{1}{n_{exp}}\sum_{n=1}^{n_{exp}}\frac{|y_n-exp(y'_n)|}{|y_n|}&space;\times&space;100&space;\%" title="\Delta=\frac{1}{n_{exp}}\sum_{n=1}^{n_{exp}}\frac{|y_n-exp(y'_n)|}{|y_n|} \times 100 \%" /></a>


IMPORTANT!!! These solutions are temporary. The best long-term solution would be to have way more canditates for chunk_size and prefetching_distance and more experiments to ensure maximum precision. A more fitting subset for chunk_size could be {0.001,0.005,0.01,0,025,0.05,0,075,0.1,0,25,0.5} for example. This will require a lot of testing.
