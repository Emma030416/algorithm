dfs模板小总结：

```cpp
// 如果每次只判断当前这一个位置/当前这一个数
void dfs(int x) {
	if(...) {
		输出结果
		return ;
	}
    
	一种情况
    状态变化
    dfs(x + 1); 
        
	另一种情况
    状态回溯
    dfs(x + 1);     
}
```

```cpp
// 内部有for循环遍历
void dfs(int x) {
    if(...) {
        输出结果
		return ;
    }
    for(int i = ...; i <= n; i++) {
        if(st[i]) { 
			一种情况
            状态变化
            dfs(x + 1);
            
            另一种情况
            状态回溯 // 不用再dfs(x + 1)了
        }
    }  
}
```

**顺序：**

1. **按位置枚举：每个位置放哪个数**
2. **按数枚举：每个数放哪个位置**

写 dfs 函数前一定要先确定顺序



# P1255 数楼梯

https://www.luogu.com.cn/problem/P1255

### 解析

结论：**斐波那契数列**，即 1 1 2 3 5 8 13...

思考过程：（递推/动态规划）

1. 可以枚举找规律：
   台阶数：0，走法：1（这是为了后面递推设置的）
   台阶数：1，走法：1
   台阶数：2，走法：2（最后一步是从0阶到2阶，到0阶有几种方法？1种；最后一步是从1阶到2阶，到1阶有几种方法？1种 -> 一共1+1=2种）
   台阶数：3，走法：3（最后一步是从1阶到3阶，到1阶有几种方法？1种；最后一步是从2阶到3阶，到2阶有几种方法？2种 -> 一共1+2=3种）
   台阶数：4，走法：5（最后一步是从2阶到4阶，到2阶有几种方法？2种；最后一步是从3阶到4阶，到3阶有几种方法？3种 -> 一共2+3=5种）
   ...

2. 不枚举，直接找递推公式
   **一步可以走 1 阶 / 2 阶，也就是要达到第 i 阶的话，只能从 i - 1 / i - 2 这两阶跨上去**
   **所以达到第 i 阶的方法 = 到达第 i - 1 阶的方法 + 到达第 i - 2 阶的方法** 
   **dp[i] = dp[i - 1] + dp[1 - 2]**
   从总结的递推公式不难看出，重点就是要初始化前两个值（dp[1] = 1 和 dp[2] = 2，直接初始化可以避免dp[0]意义不明的争议）

------

递归就是函数自己调用自己。
我们可以很容易的写出这样的代码：

```cpp
#include<iostream>

using namespace std;

int fab(int x) {
    if(x == 1) return 1;
    if(x == 2) return 2;
    return fab(x - 1) + fab(x - 2);
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", fab(n));
    return 0;
}
```

> 细节：
> 建议平时都用 scanf 和 printf。
> 当数据范围比较小时，scanf、printf 和 cin、cout 速度差不多；但是当数据量很大（>1e5）时，scanf、printf 会快1倍甚至更多。 

结果50。部分测试点超时了。  

------

为什么超时了？
有一种分析方法，叫画递归搜索树。
树的层数为n时，递归的时间复杂度为**O(2ⁿ)**。所以**递归的层数不能太大**。

题目时间限制为1s，即10^9(ns)，不能比它大。
所以1s最多能递归多少层呢？我们可以计算一下上限。
对于走楼梯这道题，根据递归搜索树分析（假设最后到dp[1]和dp[2]），那么深度 = 楼梯数 - 1，近似相等。
**所以从理论上分析，深度（楼梯数）到达30就会超时。**
当然不同机器性能可能有所差别，性能好的到40也行。这道题N的范围最大到5000...所以超时是必然的。

下面是要记的一些数值：
$$
2^{10} = 1024
$$

$$
2^{20} ≈ 10^6
$$

$$
2^{31} ≈ 2 × 10^9
$$

$$
2^{64} ≈ 10^{18}
$$

------

我们试一下**记忆化搜索**呢？就是用数组把已经递推出来的数记录下来，省去重复递推的过程。

```cpp
#include<iostream>

using namespace std;

long long num[5000];

long long fab(int x) {
    if(num[x]) return num[x];  
    if(x == 1) return num[x] = 1;
    if(x == 2) return num[x] = 2;
    return num[x] = fab(x - 1) + fab(x - 2); 
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%lld\n", fab(n)); 
    return 0;
}
```

结果60。时间ok，但longlong溢出了，WA。
我试了一下，输入4054，输出就是负数了，-5089030755722794639，显然是溢出了。

------

怎么解决longlong溢出呢？
需要用**高精度**，转成字符串...（看不懂，有点超出了，比赛我直接得60分算了）
再见。本题止步于此，未成功解决。



# 92. 递归实现指数型枚举（AWCing）

https://www.acwing.com/problem/content/94/

### 解析

每种数字都有选 / 不选两种可能，一共 2ⁿ 种，属于指数型（每个数之间没有关系）

一样的，我们可以画递归树，树的两支分别是该数 选 和 不选

深度优先搜索的重点就是**回溯**，一个分支结束（假设是选），不能直接到不选的平行分支，而是要**重置为待定**（回到父节点），再到不选

我们用一个数组 st 记录每个数的状态，0表示待定，1表示选，2表示不选

```
举个例子，假设有三个数，递归树就应该长这样：
												? - -
					√ ? -							 						 × ? -
		√ √ ?					 √ × ?					        × √ ?					  × × ?
√ √ √		   √ √ ×	 √ × √		    √ × ×		    × √ √  		   × √ ×	  × × √	         × × ×
```

我们来分析一下整个过程：（结合上面的树看）
dfs(1) -> st[1] = 2 -> dfs(2) -> st[2] = 2 -> dfs(3) -> st[3] = 2 -> dfs(4) -> 增加一个判断条件，x > n 时，输出 × × × ，return，因为是 dfs(3) 这一层调用了 dfs(4)，所以 return 是返回到了 dfs(3) 的这一层，这样实现的回溯。

-> st[3] = 0 -> st[3] = 1 -> dfs(4) -> 同上，输出 × × √ ，return 回 dfs(3) 这一层，st[3] = 0，dfs(3) 这一层结束了，因为是 dfs(2) 这一层调用了 dfs(3)，所以 dfs(3) 结束后返回到 dfs(2) 继续。

-> st[2] = 0 -> st[2] = 1 -> dfs(3) -> st[3] = 2 -> dfs(4) -> 输出 × √ × ，return -> st[3] = 0 -> st[3] = 1 -> dfs(4) -> 输出 × √ √  ，return ，dfs(2) 这一层结束了，返回到 dfs(1)。

-> st[1] = 0 -> st[1] = 1 -> dfs(2)...到左边分支了，和上面右边分支的整个过程一样。

彻底清楚了，写代码。

### 解答

```cpp
#include<iostream>

using namespace std;

const int N = 20;

int n; 
int st[N]; 

void dfs(int x) { // x 表示当前枚举到了哪个位置
    // 这一条线枚举完了到底了，输出一种结果
    if(x > n) { 
        for(int i = 1; i <= n; i++) {
            if(st[i] == 1) {
                printf("%d ", i);
            }
        }
        printf("\n");
        return ;
    }
    st[x] = 2;  // 不选
    dfs(x + 1);	// 到下一层。一直往下，直到最后一层，x > n，输出这一条线的结果，返回
    st[x] = 0;  // 回溯，重置为待定状态
    
    st[x] = 1;  // 选
    dfs(x + 1);
    st[x] = 0;
}

int main() {
    scanf("%d", &n);
    dfs(1);
    return 0;
}
```



# P1706 全排列问题

https://www.luogu.com.cn/problem/P1706

### 解析

strcmp 方法比较两个字符串，按照字典序比较

**顺序：**

1. **按位置枚举：每个位置放哪个数**
2. **按数枚举：每个数放哪个位置**

我们以第一种为例，依次枚举每个位置放哪个数。

用一个 bool 数组来记录每个数的状态（false 表示已经选了，不可选；true 表示还没被选，可选），再用一个数组来记录每个位置的数。

在当前位置遍历所有数，如果该数可选，则当前位置有：选 / 不选两种方案，和上一题非常类似，这部分代码如下：

```cpp
if(st[i]) {
    num[x] = i;
    st[i] = false; // 选
    dfs(x + 1);
    num[x] = 0;
    st[i] = true; // 不选
}
```

有个问题，**数组不初始化的话默认全为 0**，而 0 在 bool 数组里就是 false，所以如果不初始化就没有数可选了，全部不可选。

解决方法：状态换一下，或者全部初始化为 true 。我已经习惯这个状态的定义了，就用初始化了。

初始化的话也别直接一个 for 循环，纯粹浪费时间，用 fill 填充。因为是从 i = 1 开始的，所以下标 0 的位置不用管，直接用 st + 1 开始，给 st[1] 到 st[n] 填 true。

```cpp
fill(st + 1, st + n + 1, true); 
```

多说一句，其实比赛的话初始化肯定会浪费时间，建议还是直接换状态。可以写完再整个换，这样也不会影响到思路。

### 解答

```cpp
#include<iostream>

using namespace std;

const int N = 10;

int n;
bool st[N]; // 每个数的状态
int num[N]; // 每个位置的数

void dfs(int x) { // 用来记录当前枚举到了哪个位置
    if(x > n) {
        for(int i = 1; i <= n; i++) {
            printf("%5d", num[i]); // 宽度不足5的直接用空格填充
        }
        printf("\n");
        return ;
    }
    for(int i = 1; i <= n; i++) {
        if(st[i]) { // 如果该数可选
            num[x] = i; // 选
            st[i] = false; // 更新状态
            dfs(x + 1);
            num[x] = 0; // 不选，重置
            st[i] = true; // 更新状态
        }
    }  
}

int main() {
    scanf("%d", &n);
    fill(st + 1, st + n + 1, true); 
    dfs(1);
    return 0;
}
```

细节：这道题写成"    %d"也行，手动输入4个空格填充，这是因为这道题限制了n <= 9。但如果有10以上的两位数就应该填充3个空格了，就会错位。所以这种写法是不具备普遍性的。



# P1157 组合的输出

https://www.luogu.com.cn/problem/P1157

还是有两种枚举顺序。

第一种，**按位置枚举**，枚举每个位置放哪个数。

和上一题差不多，主要区别在于输出的数列要从小到大，也就是每个位置上不能选比他小的数。

如果画递归树的话，就是有的情况可以直接剪枝，不用继续往下递归了。比如第一个位置就放最大数，或者后面没有那么多个比第一个数大的数，就直接不考虑了。

具体代码实现上，我们可以用 start 控制，表示可选数的下限，start = 前一个数 + 1，可选数控制在 [start + 1, n] 之间。

```cpp
#include<iostream>

using namespace std;

const int N = 21;

int n, r;
int num[N];

void dfs(int x, int start) {  // x记录当前位置
    if(x > r) {
        for(int i = 1; i <= r; i++) {
            printf("%3d", num[i]);
        }
        printf("\n");
        return ;
    }
    for(int i = start; i <= n; i++) { // 判断每个数是选还是不选（不能选比他小的数，用start控制）
        num[x] = i; // 选
        dfs(x + 1, i + 1);
        num[x] = 0; // 不选，重置
    }   
}

int main() {
    scanf("%d %d", &n, &r);
    dfs(1, 1);
    return 0;
}
```

------

第二种，**按数枚举**，枚举每个数是选还是不选。

一样地，用st数组记录每个数的状态，true表示选了，false表示没选。

```cpp
#include<iostream>

using namespace std;

const int N = 21;

int n, r, cnt = 0;
bool st[N]; // 每个数字的状态：true表示选了，false表示没选

void dfs(int x) { // x记录当前枚举到哪个数字了
    if(cnt == r) {
        for(int i = 1; i <= n; i++) {
            if(st[i]) printf("%3d", i);
        }
        printf("\n");
        return ;
    }
    for(int i = x; i <= n; i++) {
        if(!st[i]) {
            st[i] = true; // 选
            cnt++;
            dfs(i + 1);
            st[i] = false; // 不选
            cnt--; // 重置！
        }
    } 
}

int main() {
    scanf("%d %d", &n, &r);
    dfs(1);
    return 0;
}
```

感觉第一种 按位置枚举 更好理解。



# P1036 [NOIP 2002 普及组] 选数

https://www.luogu.com.cn/problem/P1036

第一种，**按位置枚举**，每个位置放哪个数。

**选数本质是组合，不能再回头选，否则可能会重复，比如 (3, 7) 和 (7, 3)，因此每次可选的数只能是从 start 开始往后！**

```cpp
#include<iostream>
#include<cmath>

using namespace std;

const int N = 21;

int n, k;
int q[N]; // 存输入的n个数
int num[N]; // 存最后选择的k个数
int ans = 0;

bool isPrime(int sum) {
    if(sum == 1) return false;
    if(sum == 2) return true;
    if(sum % 2 == 0) return false;
    for(int i = 3; i <= sqrt(sum); i += 2) {
        if(sum % i == 0) return false;
    }
    return true;
}

void dfs(int x, int start) {
    // 剪枝
    if(x + n - start < k) return ;   
    
    if(x > k) { // 这里x表示当前选到哪个位置了，x = k 表示正准备选第k个数，但还没有选，所以是x > k
        int sum = 0;
        for(int i = 1; i <= k; i++) sum += num[i];
        if(isPrime(sum)) ans++;
        return ;
    }   
    
    for(int i = start; i <= n; i++) { // 从start开始，不能再回头选
        num[x] = q[i]; // 选
        dfs(x + 1, i + 1);
        num[x] = 0;
    }
}

int main() {
    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &q[i]);
    }
    dfs(1, 1);
    printf("%d", ans); 
    return 0;
}
```

注意：这题加了**剪枝**！

什么情况可以直接剪掉？前面已经大致解释过了，**已选数的个数 + 可选数的个数  < 总共要选的数的个数**，也就是数不够了。

当正在考虑 x 这个位置时，已选数的个数为 x - 1，可选数的个数为 n - start + 1。

**剪枝用时会更短**，在时间复杂度本身就很大的情况下更明显。前面的题都是加剪枝更好。

------

第二种，**按数枚举**，每个数选不选。

一个 isPrime 函数，判断结果是否为素数。

一个 dfs 函数：桉数枚举，每次只判断当前这个数选还是不选，然后下一个数直接 dfs(x + 1) 递归。

如果选的话 sum += q[i]，已选数的个数 cnt++，如果不选的话两个变量回溯！

**再次强调，不选的话，所有选的时候变化了的变量都要回溯，恢复为原状态！**

条件就是如果 cnt == k ，且 sum 为素数，则 ans++。

然后如果 x > n，但没有选够 k 个数，直接 return ；

```cpp
#include<iostream>
#include<cmath>

using namespace std;

const int N = 21;

int n, k;
int q[N]; // 存储所有的数
int sum = 0, cnt = 0, ans = 0; // sum记录和，cnt记录已选的数有多少个，ans记录最后有多少种组合满足要求（输出）

bool isPrime(int num) {
    if(num == 1) return false;
    if(num == 2) return true;
    if(num % 2 == 0) return false;
    for(int i = 3; i <= sqrt(num); i += 2) {
        if(num % i == 0) return false;
    }
    return true;
}

void dfs(int x) { // 记录枚举到哪个数了
    if(cnt == k) {
        if(isPrime(sum)) {
            ans++;
        }
        return ;
    }
    if(x > n) {
        return ;
    }
    sum += q[x]; cnt++;// 选
    dfs(x + 1);
    sum -= q[x]; cnt--; // 不选
    dfs(x + 1);
}

int main() {
    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &q[i]);
    }
    dfs(1);
    printf("%d", ans);
    return 0;
}
```



# P2089 烤鸡

https://www.luogu.com.cn/problem/P2089

简单，稍微注意一下细节就行。

每种调料都是 1~3 克，所以范围是 10~30，先把不符合范围的叉出去。这个写在 main 里面，输入完就判断。

然后就是输出顺序的问题，如果在 dfs 里输出方案，那么每枚举完一种就会输出，最后才会回到 main 里输出总方案数 ans。

但题目要求先输出 ans，所以方案也要在 main 里输出，也就是要先用一个数组把所有方案都记录下来。

已经有一个数组 arr 用来记录当前方案每个位置的数了，我们可以再用一个**二维数组 mem [第几个方案] [当前方案]** 来记录所有方案。

------

第一种，按位置枚举，每种调料放多少克（1~3）。

```cpp
#include<iostream>

using namespace std;

const int N = 11;
    
int n;
int arr[N]; // 当前方案
int ans = 0; // 方案数
int mem[59049][N]; // 所有方案

void dfs(int x, int sum) { // sum表示当前美味程度
    if(sum > n) return ; // 剪枝
    
    if(x > 10) {
        if(sum == n) {
            ans++;
            for(int i = 1; i <= 10; i++) {
                mem[ans][i] = arr[i];
            }
        }
        return ;
    }
    
    for(int i = 1; i <= 3; i++) { // 三种可选
        arr[x] = i; // 选
        dfs(x + 1, sum + i);
        arr[x] = 0; // 不选
    }  
}

int main() {
    scanf("%d", &n);
    if(n < 10 || n > 30) { // 放main函数里直接return 0，不要放dfs里每次都来一遍
        printf("0"); 
        return 0;
    }
    dfs(1, 0);
    printf("%d\n", ans);
    for(int i = 1; i <= ans; i++) {
        for(int j = 1; j <= 10; j++) {
            printf("%d", mem[i][j]);
            if(j != 10) printf(" ");
        }
        printf("\n");
    }
    return 0;
}
```

------

第二种，枚举每种克数放哪几种调料。



# P1088 [NOIP 2004 普及组] 火星人

https://www.luogu.com.cn/problem/P1088

这题也简单，关键是题意理解。我们到底要干啥：

1. 先找到初始排列（输入的 mars）
2. 然后继续往后生成排列，找到它后面的第 m 个排列

我们按位置枚举，每个位置选哪个数。

```cpp
#include<iostream>

using namespace std;

const int N = 10010;

int n, m;
int arr[N]; // 记录方案
int mars[N]; // 记录火星人的初始排列（输入）
bool st[N]; // true表示被选了，false表示没被选
int add = 0; // 记录这是初始排列加几后的方案

void dfs(int x) {
    if(x > n) {
        add++;
        if(add == m + 1) { 
            for(int i = 1; i <= n; i++) {
                printf("%d", arr[i]);
                if(i != n) printf(" ");
            }
            exit(0);
        }
        return ;
    }
    
    for(int i = 1; i <= n; i++) {
        // add = 0，先找到初始序列（输入的）
        if(!add) {
            i = mars[x];
        } 
        if(!st[i]) {
            arr[x] = i; st[i] = true; // 选
            dfs(x + 1);
            arr[x] = 0; st[i] = false; // 不选  
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &mars[i]);
    }
    dfs(1);
    return 0;
}
```

细节：**加 exit(0)**，找到了输出完了就立即退出程序，否则会超时。



没懂，我觉得是add == m？明天看。

