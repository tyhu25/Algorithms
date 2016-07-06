#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> permuteUnique(vector<int>& nums);
int getMin(vector<int> &vec, int l, int h);
void printArray(vector<int> &vec);

//Sparse Table(ST) algorithm
class RMQ {
public:
    RMQ(const vector<int> &Array) {
        A = Array;
        int N = A.size();
        int LogN=(int)(log2(N));
        M = vector<vector<int>>(N, vector<int>(LogN, 0));

        for(int i=0; i<N; i++) M[i][0] = i;
        
        for(int j=1; (1<<j)<=N; j++) {
            for(int i=0; i+(1<<j)-1<N; i++) {
                if(A[M[i][j-1]]<A[M[i+(1<<(j-1))][j-1]]) {
                    M[i][j] = M[i][j-1];
                } else {
                    M[i][j] = M[i+(1<<(j-1))][j-1];
                }
            }
        }
    }
    int query(int i, int j) {
        int k = (int)(log2(j-i+1));
        if(A[M[i][k]]<=A[M[j-(1<<k)+1][k]]) {
            return M[i][k];
        } else {
            return M[j-(1<<k)+1][k];
        }
    }

    vector<vector<int>> M;
    vector<int> A;
};

void testRMQ(vector<int> &nums) {
    vector<vector<int>> permutations = permuteUnique(nums);
    for(auto vec:permutations) {
        RMQ rmq(vec);
        for(int i=0; i<vec.size(); i++) {
            for(int j=i; j<vec.size(); j++) {
                int rangeMinInx = rmq.query(i, j);
                int vecMin = getMin(vec, i, j);
                if(vec[rangeMinInx]!=vecMin) {
                    cout<<"==========\n";
                    printArray(vec);
                    printf("Test on range [%d]-[%d] failed. Get: %d, Expected: %d\n", i, j, vec[rangeMinInx], vecMin);
                    cout<<"==========\n";
                }
            }
        }
    }
    printf("Test done\n");
}

void dfs(vector<int>& nums, vector<vector<int>> &res, vector<int>& vec, vector<bool> &m) {
    if(vec.size()==nums.size()) {
        res.push_back(vec);
        return;
    }
    for(int i=0; i<nums.size(); i++) {
        if(m[i] || (i!=0 && nums[i]==nums[i-1] && !m[i-1])) {
            continue;
        }
        m[i] = true;
        vec.push_back(nums[i]);
        dfs(nums, res, vec, m);
        vec.pop_back();
        m[i] = false;
    }
}

vector<vector<int>> permuteUnique(vector<int>& nums) 
{
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    vector<int> vec;
    vector<bool> m(nums.size(), false);
    dfs(nums, res, vec, m);
    return res;
}

int getMin(vector<int> &vec, int l, int h) {
    int res = vec[l];
    for(int i=l+1; i<=h; i++) {
        res=min(res, vec[i]);
    }
    return res;
}

void printArray(vector<int> &vec) {
    for(int i=0; i<vec.size(); i++) {
        cout<<vec[i]<<" ";
    }
    cout<<endl;
}


int main() {
    vector<int> nums = {1,2,3,4,5,6,7,8,9};

    testRMQ(nums);
    return 0;
}