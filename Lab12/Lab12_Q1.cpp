class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int x=0,y=0;
	int a[m+n];
	if(n!=0){
        for(int i=0;i<m+n;i++){
        if(y==n){
            a[i]=nums1[x];
            x++;
        }
        else if(nums1[x]<nums2[y]&&x<m){
            a[i]=nums1[x];
            x++;
        }
        else{
            a[i]=nums2[y];
            y++;
        }
    }
    for(int i=0;i<m+n;i++)
		nums1[i]=a[i]; 
    }
    }
};
