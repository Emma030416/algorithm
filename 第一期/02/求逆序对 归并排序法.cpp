// 归并排序分为两个部分，分和治，在治（合并）的过程中：
// 如果从右子序列中取出一个元素，那么左子序列中剩余的元素个数即为与该元素构成的逆序对数
#include<iostream>
#include<vector>
#define MAX 20
using namespace std;

// 治：合并两个子数组，统计逆序对 
int merge(vector<int>& arr, int l, int mid, int r, vector<int>& temp) {
	int i = l, j = mid + 1, t = 0, count = 0;
	while(i <= mid && j <= r) {
		if(arr[i] <= arr[j]) {
			temp[t++] = arr[i++];
		}
		else {
			temp[t++] = arr[j++];
			count += (mid - i + 1);
		}	
	}
	while(i <= mid) {
		temp[t++] = arr[i++];
	}
	while(j <= r) {
		temp[t++] = arr[j++];
	}
	for(int k = 0; k < t; k++) {
		arr[l + k] = temp[k];	
	}
	return count;
}

// 分：不断一分为二，总逆序对数 = 左半边的 + 右半边的 + 合并过程中的（递归） 
int cut(vector<int>& arr, int l, int r, vector<int>& temp) {
	if (l >= r) return 0;
	int mid = l + (r - l) / 2;
	int total_count = 0;
	total_count += cut(arr, l, mid, temp); // 左半部分
	total_count += cut(arr, mid + 1, r, temp); // 右半部分
	total_count += merge(arr, l, mid, r, temp); // 合并过程中的 
	return total_count;
}
	
int main() {
	int n;
	cin>>n;
	vector<int> arr(n);
	vector<int> temp(n);
	for(int k = 0; k < n; k++) {
		cin>>arr[k];
	} 
	int total_count = cut(arr, 0, n - 1, temp);
	cout<<total_count<<endl;
	return 0;
}



