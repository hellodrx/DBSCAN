#include <iostream>
#include <vector>
#include <assert.h>


using namespace std;

struct data
{
	int a;
	bool isvisited;
};

class  DBSCAN
{
private:
	int                   minPts;//最小
	float                 dis;
	vector<data>          dataset;//整个数据集
	vector<int>           outliers;//离群点
	vector< vector<int> > clusters;//已分好的类

public:
	DBSCAN();
	DBSCAN(vector<int> , float distance, int minPts);
    void expandCluster( int p, vector<int> neighbour, int classNUM );
	vector<int> regionQuery( data p);//将该点邻域内的其它点的编号返回
	void operator()( vector<int> _data);
	void init( vector<int> _data);//将数据转变成带有bool标记的数据集
	void displayClusters();
};


DBSCAN::DBSCAN()
{
	dis = 15;
	minPts = 3;
}

DBSCAN::DBSCAN(vector<int> _data, float distance, int _minPts)
{
	init(_data);

	minPts = _minPts;
	dis = distance;
	
}

void DBSCAN::expandCluster( int p, vector<int> neighbour, int classNUM)
{
	clusters[classNUM].push_back(p);
	
	int size = neighbour.size();

	for ( int i = 0; i < size; i++)
	{
		if ( dataset[neighbour[i]].isvisited)//如果该点已经被访问过
		{
			continue;
		}
		else
		{
			dataset[neighbour[i]].isvisited = true;

			vector<int> _neighbour= regionQuery( dataset[neighbour[i]]);


			if ( _neighbour.size() > minPts)
			{
				//合并_neighbour和neighbour
				neighbour.insert(neighbour.end(), _neighbour.begin(),_neighbour.end());
			}

			clusters[classNUM].push_back(dataset[neighbour[i]].a);//因为当前点之前没有访问，所以也没有分类，直接被分类进当前类

		}
	}
}

vector<int> DBSCAN::regionQuery( data p)
{
	int size = dataset.size();
	vector<int> nums;//it stores the order numbers in dataset of p's neighgbours

	for( int i = 0; i < size; i++)
	{
		if ( abs( dataset[i].a - p.a) < dis)
		{
			nums.push_back(i);
		}
	}

	return nums;
}

void DBSCAN::operator()(vector<int> _data)
{
	assert( _data.size() != 0);
	if ( dataset.size() == 0)
	{
		init( _data);
	}

	int C = -1;//类别编号
	int size = _data.size();

	for ( int i = 0; i < size; i++)
	{
		if ( dataset[i].isvisited == true)//如果该点已被访问过
		{
			continue;
		}
		else//如果没被访问
		{
			dataset[i].isvisited = true;
			vector<int> neighbour = regionQuery( dataset[i]);
			if ( neighbour.size() < minPts)//如果是离群点
			{
				outliers.push_back(dataset[i].a);
			}
			else//如果是核心点
			{
				C++;
				clusters.push_back( vector<int>());//初始化每一个类别
				expandCluster(dataset[i].a, neighbour, C);//neighbour里只存储数据的编号
			}
		}
	}
}

void DBSCAN::init(vector<int> _data)
{
	assert( _data.size() != 0);//保证不是空集

	int size = _data.size();

	for ( int i = 0; i < size; i++)
	{
		data temp;
		temp.a = _data[i];
		temp.isvisited = false;

		dataset.push_back(temp);
	}
}

void DBSCAN::displayClusters()//display clusters' members and outliers'
{
	int m_clusters = clusters.size();

	cout<<"CLUSTERS"<<endl;
	for ( int i = 0; i < m_clusters; i++)
	{
		int temp = clusters[i].size();
		cout<<" /******************This is the "<<i<<"th cluster.***************************/"<<endl;
	    
		for ( int j = 0; j < temp; j++)
		{
			cout<<clusters[i][j]<<" ";
		}
		
		cout<<endl;
	}

	int m_outliers =outliers.size();

	cout<<endl<<endl<<" OUTLIERS"<<endl;
	for ( int ii = 0; ii < m_outliers; ii++)
	{
		cout<<outliers[ii]<<" ";
	}
}



int main()
{
	vector <int> data;

	data.push_back(33);
	data.push_back(36);
	data.push_back(37);
	data.push_back(38);
	data.push_back(42);
	data.push_back(43);
	data.push_back(46);
	data.push_back(133);
	data.push_back(134);
	data.push_back(137);
	data.push_back(11400);
	data.push_back(11478);
	data.push_back(11755);

	DBSCAN dbscan;
	dbscan(data);

	dbscan.displayClusters();

	getchar();

	return 0;


}