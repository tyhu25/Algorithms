#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void PrintVector(const vector<int> &vec);
bool NextPermutation(vector<int> &vec);

int TwoWayPartition(vector<int> &vec, int low, int high);
pair<int, int> ThreeWayPartition(vector<int> &vec, int low, int high);

void TestTwoWayPartition();
pair<int, int> ThreeWayPartition(vector<int> &vec, int low, int high);

pair<int, int> DualPivotPartition(vector<int> &vec, int low, int high);
void TestDualPivotPartition();

bool NextPermutation(vector<int> &vec) {
    int size = vec.size();
    int index = size-2;
    while(index>=0) {
        if(vec[index]<vec[index+1]) break;
        index--;
    }
    if(index<0) return false;
    reverse(vec.begin()+index+1, vec.end());
    vector<int>::iterator it = upper_bound(vec.begin()+index+1, vec.end(), vec[index]);
    int upBound = it-vec.begin();
    swap(vec[index], vec[upBound]);
    return true;
}

void PrintVector(const vector<int> &vec) {
    for(int i=0; i<vec.size(); i++) {
        cout<<vec[i]<<" ";
    }
    cout<<endl;
}

int TwoWayPartition(vector<int> &vec, int low, int high) {
    int key = vec[low];
    int i = low+1;
    int j = high;
    while(i<=j) {
        if(vec[i]<key) {
            i++;
        } else if(vec[j]>key) {
            j--;
        } else {
            swap(vec[i],vec[j]);
        }
    }
    swap(vec[low], vec[j]);
    return j;
}

void TestTwoWayPartition() {
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = vec.size();
    while(true) {
        vector<int> tmp = vec;
        int pivot = TwoWayPartition(tmp, 0, size-1);
        bool err = false;
        for(int i=0; i<size; i++) {
            if(i<pivot && tmp[i]>tmp[pivot]) {
                err = true;
                break;
            }
            if(i>pivot && tmp[i]<tmp[pivot]) {
                err = true;
                break;
            }
        }
        if (err) {
            cout<<string(20, '=');
            cout<<"\nTEST FAILED\n";
            cout<<string(20, '=');
            cout<<"\nBefore Partition:\n";
            PrintVector(vec);
            cout<<"After Partition:\n";
            PrintVector(tmp);
            cout<<"\n";
        }
        if(!NextPermutation(vec)) break;
    }    
}

pair<int, int> ThreeWayPartition(vector<int> &vec, int low, int high) {
    int lt = low;
    int gt = high;
    int i = low;
    int key = vec[low];
    while(i<=gt) {
        if(vec[i]<key) {
            swap(vec[i], vec[lt]);
            i++;
            lt++;
        } else if(vec[i]>key) {
            swap(vec[i], vec[gt]);
            gt--;
        } else {
            i++;
        }
    }
    return make_pair(lt, gt);
}

void TestThreeWayPartition() {
    vector<int> vec = {1, 1, 1, 2, 2, 2, 3, 3, 4, 5};
    int size = vec.size();
    while(true) {
        vector<int> tmp = vec;
        pair<int, int> pivot = ThreeWayPartition(tmp, 0, size-1);
        bool err = false;
        if(tmp[pivot.first]!=tmp[pivot.second]) {
            err = true;
        }
        if(!err) {
            int key = tmp[pivot.first];
            for(int i=0; i<size; i++) {
                if(i<pivot.first && tmp[i]>key) {
                    err = true;
                    break;
                }
                if(i>pivot.second && tmp[i]<key) {
                    err = true;
                    break;
                }
                if(i>=pivot.first && i<=pivot.second && tmp[i]!=key) {
                    err = true;
                    break;
                }
            }
        }

        if (err) {
            cout<<string(20, '=');
            cout<<"\nTEST FAILED\n";
            cout<<string(20, '=');
            cout<<"\nBefore Partition:\n";
            PrintVector(vec);
            cout<<"After Partition:\n";
            PrintVector(tmp);
            cout<<"Pivot = ( " <<pivot.first<<", "<<pivot.second<<" )\n";
            cout<<"\n";
        }
        if(!NextPermutation(vec)) break;
    }    
}

pair<int, int> DualPivotPartition(vector<int> &vec, int low, int high) {
    if(vec[high]<vec[low]) {
        swap(vec[low], vec[high]);
    }
    int lKey = vec[low];
    int hKey = vec[high];
    int lt = low+1;
    int gt = high-1;
    int i = low+1;
    while(i<=gt) {
        if(vec[i]<lKey) {
            swap(vec[lt], vec[i]);
            lt++;
            i++;
        } else if(vec[i]>hKey) {
            swap(vec[i], vec[gt]);
            gt--;
        } else {
            i++;
        }
    }
    lt--;
    gt++;
    swap(vec[low], vec[lt]);
    swap(vec[high], vec[gt]);
    return make_pair(lt, gt);
}

void TestDualPivotPartition() {
    vector<int> vec = {1, 2, 3, 3, 3, 4, 5, 6, 7, 8};
    int size = vec.size();
    while(true) {
        vector<int> tmp = vec;
        pair<int, int> pivot = DualPivotPartition(tmp, 0, size-1);
        bool err = false;

        int key = tmp[pivot.first];
        for(int i=0; i<size; i++) {
            if(i<pivot.first && tmp[i]>tmp[pivot.first]) {
                err = true;
                break;
            }
            if(i>pivot.second && tmp[i]<tmp[pivot.second]) {
                err = true;
                break;
            }
            if(i>=pivot.first && i<=pivot.second && (tmp[i]<tmp[pivot.first] || tmp[i]>tmp[pivot.second])) {
                err = true;
                break;
            }
        }
        
        if (err) {
            cout<<string(20, '=');
            cout<<"\nTEST FAILED\n";
            cout<<string(20, '=');
            cout<<"\nBefore Partition:\n";
            PrintVector(vec);
            cout<<"After Partition:\n";
            PrintVector(tmp);
            cout<<"Pivot = ( " <<pivot.first<<", "<<pivot.second<<" )\n";
            cout<<"\n";
        }
        if(!NextPermutation(vec)) break;
    }    
}

int main() {
    TestTwoWayPartition();
    TestThreeWayPartition();
    TestDualPivotPartition();

    return 0;
}