class Solution {
public:
    bool isMonotonic(vector<int>& nums) {
        bool m=true,n=true;
        for(int i=0;i<nums.size()-1;i++){
            if(nums[i]>nums[i+1])
                m=false;
        }
        for(int i=0;i<nums.size()-1;i++){
            if(nums[i]<nums[i+1])
                n=false;
        }
        if(m==true||n==true)
            return true;
        else
            return false;
    }
};
