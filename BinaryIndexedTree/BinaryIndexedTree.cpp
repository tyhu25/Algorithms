#include <iostream>
#include <vector>

using namespace std;


class BinaryIndexedTree {
public:
    BinaryIndexedTree(const vector<int> &nums) {
        int size = nums.size();
        mNums = nums;
        mTree = vector<int> (size+1, 0);
        for(int i=0; i<size; i++) {
            int idx = i+1;
            int start = idx-lowBit(idx)+1;
            for(int j=start; j<=idx; j++) {
                mTree[idx]+=nums[j-1];
            }
        }
    }
    
    int sum(int idx) {
        idx = idx+1;
        int res = 0;
        while(idx>0) {
            res+=mTree[idx];
            idx-=lowBit(idx);
        }
        return res;
    }
    
    void update(int idx, int val) {
        int diff = val-mNums[idx];
        mNums[idx] = val;
        idx = idx+1;
        while(idx<mTree.size()) {
            mTree[idx]+=diff;
            idx+=lowBit(idx);
        }
    }
    
    int read(int idx) {
        idx = idx+1;
        int res = mTree[idx];
        int stop = idx-lowBit(idx);
        int it = idx-1;
        while(it!=stop) {
            res -= mTree[it];
            it-=lowBit(it);
        }
        return res;
    }
    
private:
    int lowBit(int num) {
        return num & (-num);
    }
    vector<int> mTree;
    vector<int> mNums;
};

void testBITSum(vector<int> &nums, BinaryIndexedTree &BIT) {
    printf("testBITSum\n");
    int failureCnt = 0;
    for(int i=0; i<nums.size(); i++){
        int sum = 0;
        for(int j=0; j<=i; j++) {
            sum+=nums[j];
        }
        int bitSum = BIT.sum(i);
        if(sum!=bitSum) {
            printf("Unexpected sum at index %d. Got: %d, Expected: %d\n", i, bitSum, sum);
            failureCnt++;
        }
    }
    printf("Test Done, %d failed\n", failureCnt);
}

void testBitRead(vector<int> &nums, BinaryIndexedTree &BIT) {
    printf("testBitRead\n");
    int failureCnt = 0;
    for(int i=0; i<nums.size(); i++) {
        int val = BIT.read(i);
        if(val!=nums[i]) {
            printf("Unexpected read value at index %d. Got: %d, Expected: %d\n", i, val, nums[i]);
            failureCnt++;
        }
    }
    printf("Test Done, %d failed\n", failureCnt);
}

void testBIT(vector<int> &nums) {
    BinaryIndexedTree BIT(nums);
    testBITSum(nums, BIT);
    testBitRead(nums, BIT);
    nums[2] = 20;
    nums[5] = 30;
    nums[8] = 40;
    BIT.update(2, 20);
    BIT.update(5, 30);
    BIT.update(8, 40);
    testBITSum(nums, BIT);
}

int main() {
    vector<int> nums={1,2,3,4,5,6,7,8,9,10};
    testBIT(nums);
    return 0;
}