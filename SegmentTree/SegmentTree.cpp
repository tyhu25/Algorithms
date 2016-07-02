#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct SegmentTreeNode {
    int l, r, sum;
    SegmentTreeNode *left;
    SegmentTreeNode *right;
    SegmentTreeNode (int L, int R) 
        :l(L), r(R), sum(0), left(0), right(0) {}    
};

class SegmentTree {
public:
    SegmentTree(const vector<int> &nums) {
        root = buildST(nums, 0, nums.size()-1);
    }
    int sum(int start, int end) {
        return sum(root, start, end);
    }
    
    void update(int i, int val) {
        update(root, i, val);
    }
    
private:
    SegmentTreeNode* buildST(const vector<int> &nums, int start, int end) {
        if(start>end) return 0;
        SegmentTreeNode *r = new SegmentTreeNode(start, end);
        if(start==end) {
            r->sum = nums[start];
        } else {
            int m = (start+end)/2;
            r->left = buildST(nums, start, m);
            r->right = buildST(nums, m+1, end);
            r->sum = r->left->sum+r->right->sum;
        }
        return r;
    }
    
    int sum(SegmentTreeNode* node, int start, int end) {
        if(start>node->r || end<node->l) return 0;
        if(start<=node->l && end>=node->r) return node->sum;
        //int mid = (node->r+node->l)/2;
        //if(end<=mid) return sum(node->left, start, end);
        //if(start>mid) return sum(node->right, start, end);
        return sum(node->left, start, end) + sum(node->right, start, end);
    }
    
    void update(SegmentTreeNode* node, int i, int val) {
        if(i<node->l || i>node->r) return;
        if(node->l==node->r) {
            node->sum = val;
            return;
        }
        int mid = (node->l+node->r)/2;
        if(i<=mid) {
            update(node->left, i, val);
        } else {
            update(node->right, i, val);
        }
        node->sum = node->left->sum+node->right->sum;
    }

    SegmentTreeNode *root; 
};

int testST(vector<int> &nums, SegmentTree &st) {
    int size = nums.size();
    for(int i=-2; i<size+1; i++) {
        for(int j=i+1; j<size+2; j++) {
            int rangeSum = st.sum(i, j);
            int expectedSum = 0;
            for(int k=max(0,i); k<=min(size-1,j); k++) {
                expectedSum+=nums[k];
            }
            if(rangeSum!=expectedSum) {
                printf("Test on range [%d]-[%d] failed. Get: %d, Expected: %d\n", i, j, rangeSum, expectedSum);
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


int main() {
    vector<int> nums = {1,2,3,4,5,6,7,8,9};
#if 0
    SegmentTree st(nums);
    testST(nums, st);
    st.update(2, 20);
    st.update(5, 30);
    nums[2] = 20;
    nums[5] = 30;
    testST(nums, st);
#endif

    testRMQ(nums);
    return 0;
}