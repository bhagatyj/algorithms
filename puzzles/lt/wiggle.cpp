#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	void wiggleSort(vector<int>& nums);
};

void
Solution::wiggleSort(std::vector<int> &nums) {
	std::sort(nums.begin(), nums.end());
	int midpoint = (nums.size()-1)/2;
	int end = nums.size()-1;
	vector<int> mynums;


	while (midpoint>0) {
		mynums.push_back(nums[midpoint]);
		mynums.push_back(nums[end]);
		midpoint--;
		end--;
	}
	if (nums.size()%2) {
		mynums.push_back(nums[midpoint]);
	} else {
		cout << "End is" << end << endl;
		mynums.push_back(nums[midpoint]);
		mynums.push_back(nums[end]);	}

	int i=0;
	for (int &x : mynums) {
		nums[i] = x;
		i++;
	}
}
