#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define SEGMENT_TREE_ARRAY_IMPL

#ifdef SEGMENT_TREE_NODE_IMPL
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
#endif

#ifdef SEGMENT_TREE_ARRAY_IMPL
class SegmentTree {
public:
    SegmentTree(const vector<int> &nums) {
        mNums = nums;
        int n = nums.size();
        int size = 2*(int)pow(2,(ceil(log2(n))))-1;
        mST = vector<int>(size, 0);
        mLazy = vector<int>(size, 0);
        buildST(0, n-1, 0);
    }

    int sum(int start, int end) {
        return sum(start, end, 0, mNums.size()-1, 0);
    }

    int queryLazy(int l, int r) {
        return queryLazy(l, r, 0, mNums.size()-1, 0);
    }

    void update(int i, int val) {
        int diff = val - mNums[i];
        mNums[i] = val;
        update(i, diff, 0, mNums.size()-1, 0);
    }

    void updateRange(int l, int r, int val) {
        for(int i=l; i<=r; i++) {
            mNums[i] += val;
        }
        upadteRange(0, mNums.size()-1, l, r, 0, val);
    }

    void updateRangeLazy(int l, int r, int val) {
        for(int i=l; i<=r; i++) {
            mNums[i] += val;
        }
        upadteRangeLazy(0, mNums.size()-1, l, r, 0, val);
    }

private:
    int buildST(int start, int end, int index) {
        if(start==end) {
            mST[index] = mNums[start];
            return mST[index];
        }
        int mid = start + (end-start)/2;
        mST[index] = buildST(start, mid, 2*index+1) + buildST(mid+1, end, 2*index+2);
        return mST[index];
    }

    int sum(int qs, int qe, int ss, int se, int index) {
        if(qs>se || qe<ss) {
            return 0;
        }
        if(qs<=ss && qe>=se) {
            return mST[index];
        }
        int mid = ss + (se-ss)/2;
        return sum(qs, qe, ss, mid, 2*index+1) + sum(qs, qe, mid+1, se, 2*index+2);
    }

    int queryLazy(int l, int r, int start, int end, int index) {
        if(start>end || l>end || r<start) {
            return 0;
        }

        if(mLazy[index]!=0) {
            mST[index] += (end-start+1)*mLazy[index];
            if(start!=end) {
                mLazy[index*2+1]+=mLazy[index];
                mLazy[index*2+2]+=mLazy[index];
            }
            mLazy[index]=0;
        }

        if(l<=start && r>=end) {
            return mST[index];
        }
        int mid = (start+end)/2;
        return queryLazy(l, r, start, mid, 2*index+1) + queryLazy(l, r, mid+1, end, 2*index+2);
    }

    void update(int idx, int diff, int start, int end, int stIdx) {
        if(idx<start || idx>end) return;
        mST[stIdx]+=diff;
        if(start!=end) {
            int mid = start + (end-start)/2;
            update(idx, diff, start, mid, stIdx*2+1);
            update(idx, diff, mid+1, end, stIdx*2+2);
        }
    }

    void upadteRange(int start, int end, int l, int r, int stIdx, int val) {
        if(start>end || l>end || r<start) return;
        if(start==end) {
            mST[stIdx] += val;
            return;
        }
        int mid=(start+end)/2;
        upadteRange(start, mid, l, r, stIdx*2+1, val);
        upadteRange(mid+1, end, l, r, stIdx*2+2, val);
        mST[stIdx] = mST[stIdx*2+1] + mST[stIdx*2+2];
    }

    void upadteRangeLazy(int start, int end, int l, int r, int stIdx, int val) {
        if(start>end || l>end || r<start) return;
        if(mLazy[stIdx]!=0) {
            mST[stIdx] += (end-start+1)*mLazy[stIdx];
            if(start!=end) {
                mLazy[stIdx*2+1]+=mLazy[stIdx];
                mLazy[stIdx*2+2]+=mLazy[stIdx];
            }
            mLazy[stIdx]=0;
        }

        if(l<=start && r>=end) {
            mST[stIdx] += (end-start+1)*val;
            if(start!=end) {
                mLazy[stIdx*2+1]+=val;
                mLazy[stIdx*2+2]+=val;
            }
            return;
        }
        int mid = (start+end)/2;
        upadteRangeLazy(start, mid, l, r, stIdx*2+1, val);
        upadteRangeLazy(mid+1, end, l, r, stIdx*2+2, val);
        mST[stIdx] = mST[stIdx*2+1] + mST[stIdx*2+2];
    }

    vector<int> mNums;
    vector<int> mST;
    vector<int> mLazy;
};
#endif

typedef int (SegmentTree::*pQueryFunc)(int,int);

int testST(vector<int> &nums, SegmentTree &st, pQueryFunc pfun) {
    int size = nums.size();
    for(int i=-2; i<size+1; i++) {
        for(int j=i+1; j<size+2; j++) {
            int rangeSum = (st.*pfun)(i, j);
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

int main() {
    vector<int> nums = {1,2,3,4,5,6,7,8,9};

    SegmentTree st(nums);
    testST(nums, st, &SegmentTree::queryLazy);

    st.update(2, 20);
    st.update(5, 30);
    nums[2] = 20;
    nums[5] = 30;
    testST(nums, st, &SegmentTree::sum);

#ifdef SEGMENT_TREE_ARRAY_IMPL
    int l = 2;
    int r = 6;
    int val = 5;
    st.updateRange(l,r,val);
    //Update orginal array for testing purpose
    for(int i=l; i<=r; i++) {
        nums[i]+=val;
    }
    testST(nums, st, &SegmentTree::queryLazy);

    l = 3;
    r = 6;
    val=-2;
    st.updateRangeLazy(l,r,val);
    for(int i=l; i<=r; i++) {
        nums[i]+=val;
    }
    testST(nums, st, &SegmentTree::queryLazy);
#endif

    return 0;
}