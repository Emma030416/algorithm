def sort(nums):
    n = len(nums)
    for i in range(1, n):
        target = nums[i]
        l, r = 0, i - 1
        while l <= r:
            mid = l + (r - l) // 2
            if target > nums[mid]:
                r = mid - 1
            else:
                l = mid + 1
        for j in range(i - 1, l - 1, -1):
            nums[j + 1] = nums[j]
        nums[l] = target
    return nums

def main():
    n = int(input())
    nums = []
    for x in range(n):
        nums.append(int(input(x)))
    sorted_nums = sort(nums)
    for x in sorted_nums:
        print(x, end=" ")