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

int testST(SegmentTree &st, int s, int e) {
    printf("[%d]-[%d] = %d\n", s, e, st.sum(s, e));
}
int main() {
    vector<int> nums = {1,2,3,4,5,6,7,8,9};
    SegmentTree st(nums);
    testST(st, 0, 10);
    testST(st, -2, -1);
    testST(st, 10, 15);
    testST(st, -1, 2);
    testST(st, 1, 2);
    testST(st, 2, 9);
    testST(st, 3, 7);
    testST(st, 5, 8);
    st.update(2, 20);
    st.update(5, 30);
    testST(st, 0, 10);
    testST(st, -2, -1);
    testST(st, 10, 15);
    testST(st, -1, 2);
    testST(st, 1, 2);
    testST(st, 2, 9);
    testST(st, 3, 7);
    testST(st, 5, 8);

    return 0;
}