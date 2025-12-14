# 王子钰Week-3

## 贪心

#### [561. 数组拆分](https://leetcode.cn/problems/array-partition/description/?envType=problem-list-v2&envId=greedy)

```c++
class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        // 从小到大排序，然后按顺序两两一组就是最优解
        sort(nums.begin(), nums.end());
        int sum = 0;
        for(int i = 0; i < nums.size(); i += 2){
            sum += nums[i];
        }
        return sum;
    }
};
```



#### [2078. 两栋颜色不同且距离最远的房子](https://leetcode.cn/problems/two-furthest-houses-with-different-colors/description/)

```c++
class Solution {
public:
    int maxDistance(vector<int>& colors) {
        // 双指针，从头尾看起
        int n = colors.size();
        int l = colors[0], r = colors[n-1];
        // 头尾颜色不同则距离最远
        if(l != r) return n-1;
        // 否则移动其中一个
        //移动尾指针，头指针不动
        int ans = 0;
        for(int i = n-1; i >= 0; i--) {
            if(colors[i] != l){
                ans = max(ans, i-0);
            }
        }
        //移动头指针，尾指针不动
        for(int i = 0; i <= n-1; i++){
            if(colors[i] != r){
                ans = max(ans, (n-1) - i);
            }
        }
        return ans;
    }
};
```



#### [1005. K 次取反后最大化的数组和](https://leetcode.cn/problems/maximize-sum-of-array-after-k-negations/description/)

```c++
class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        // 总体思路:全为正就把绝对值小的取反，有负数就把负数里绝对值大的变成正数
        // 先排序
        sort(nums.begin(), nums.end());
        // 从左往右将负数翻成正数
        for(auto &i : nums){
            if(i < 0 && k){
                i = -i;
                k--;
            } 
        } // 直到没有负数了 或 k = 0
        int sum = accumulate(nums.begin(), nums.end(), 0); // 初值为0，从数组开头到结尾依次加到0上，得到sum
        // 如果全部翻为正数了还有多的k，讨论k的奇偶性
        // 若k为奇数
        if(k % 2 == 1){ 
            sum -= 2 * (*min_element(nums.begin(),nums.end())); // 最小的正数翻成负数
        }
        // 若k为偶数，对某个数翻转偶数次就行，总和不变
        return sum;
    }
};
```



#### [881.救生艇](https://leetcode.cn/problems/boats-to-save-people/description/)

```c++
class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        // 排序，排在前的小的数为x，应该和小于 (limit-x) 的最后一个数匹配
        multiset<int> s; // 可重复且自动排序的容器
        for(auto i : people) s.insert(i);
        int ans = 0;
        while(!s.empty()){
            auto it = *s.begin();
            auto it2 = s.upper_bound(limit - it);
            if(it2 != s.begin()){
                it2--;
            }
            if(it2 != s.begin()){
                s.erase(it2);
            }
            s.erase(s.begin());
            ans++;
        }
        return ans;
    }
};
```



