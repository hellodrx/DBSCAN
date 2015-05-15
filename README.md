# DBSCAN
This is an implementation of DBSCAN algorithm[1]. DBSCAN is an unsupervised density-based cluster algorithm. It's simple yet useful. DBSCAN has two parameters --- MinPts and distance. MinPts is the quantity of neighbour points; distance is Euclidean distance between one and its neighbour.
The whole framework  followed Wikipedia's[2] instruction. For simplicity, I only use one-dimensional integer data. But one can easily modify the data structure to satisfy your application. The implementation is very simple that one can easily understand DBSCAN's underlying idea.

The test data is 33, 36, 37, 38, 42, 43, 46, 133, 134, 137, 11400, 11478, 11755

In this program, MinPts = 3, and distance = 15;

The result 
clusters
0th cluster
33 34 36 37 38 42 43 46

1st cluster
133 134 137

outlier
11400 11478 11755
 
 /*****************************************************************/
 本算法是按照WIKIPEDIA[2]的指导实现的DBSCAN[1]算法。 DBSCAN是一种基于密度的非监督分类算法。你可以通过[2]的地址详细了解其算法原理，[1]是其论文。本实现只是简单的应用了一维的整型数据说明DBSCAN的原理，你可以
 轻易的修改数据类型来符合你的应用
 
 在本实现中，邻域最小数目为3，欧式距离为15
 
 测试数据33, 36, 37, 38, 42, 43, 46, 133, 134, 137, 11400, 11478, 11755
 
 结果
 clusters
0th cluster
33 34 36 37 38 42 43 46

1st cluster
133 134 137

outlier
11400 11478 11755
 




1. Ester M, Kriegel H P, Sander J, et al. A density-based algorithm for discovering clusters in large spatial databases with noise[C]//Kdd. 1996, 96(34): 226-231.
2. http://en.wikipedia.org/wiki/DBSCAN
