#include<iostream>
#define MAX 20
using namespace std;
int main() {
	int n, arr[MAX] = {0};
	cin>>n;
	for(int i = 0; i < n; i++) {
		cin>>arr[i];
	} 
	int count = 0;
	for(int i = 0; i < n - 1; i++) {
		for(int j = i + 1; j < n; j++) {
			if(arr[i] > arr[j]) count++;
		}
	}
	cout<<count;
	return 0;
}

