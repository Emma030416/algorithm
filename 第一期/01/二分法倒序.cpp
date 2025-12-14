#include<iostream>
#include<vector>
using namespace std;
int main() {
    int i, n;
    cin>>n;
    cout<<endl;
    vector<int> nums(n);
    for(i = 0; i < n; i++) {
        cin>>nums[i];
    }
    for(i = 1; i < n; i++) {
        int target = nums[i];
        int l = 0, r = i - 1;
        while(l <= r) {
              int mid = l + (r - l) / 2;
              if(target > nums[mid]) r = mid - 1;
              else l = mid + 1;
        }
        for(int j = i - 1; j >= l; j--) {
            nums[j + 1] = nums[j];
        } 
        nums[l] = target;
    }
    for(int i = 0; i < n; i++) {
        cout<<nums[i]<<" ";
    }
    return 0;
}
