#include "DynamicProgramming.h"

int DynamicProgramming::multiplyMatrixChain(vector<int> p, vector< vector<int> > &s)
{
	int n = p.size()-1;
	vector< vector<int> > m(n, vector<int>(n, 0));
	
	for(int l=2; l<n+1; l++)
	{
		for(int i=0; i<n-l+1; i++)
		{
			int j = i+l-1;
			m[i][j]=INT_MAX;
			for(int k=i; k<j; k++)
			{
				int q = m[i][k]+m[k+1][j]+p[i]*p[k+1]*p[j+1];
				if(q<m[i][j])
				{
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
	
	return m[0][5];
}

void DynamicProgramming::printMatrixSolution(const vector< vector<int> > &s, int start, int end)
{
	if(start==end)
	{
		cout<<"S"<<start;
	}
	else
	{
		cout<<"(";
		printMatrixSolution(s, start, s[start][end]);
		printMatrixSolution(s, s[start][end]+1, end);
		cout<<")";
	}
}