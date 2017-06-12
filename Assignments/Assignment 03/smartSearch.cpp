#include <fstream>
#include "sorts.cpp"

using namespace std;

// prototype
bool binarySearch(vector<long> nums, long temp);
// A single pair is stored in a Vector<long>
// You have to return a vector of all pairs.
vector< vector<long> > smartSearch(vector<long> nums, long k)
{   

    vector<long> sorted = BucketSort(nums, 610);
	vector<long> sorted_r;
    
    for (int i = 0; sorted[i] < k; i++)
    {
    	sorted_r.push_back(sorted[i]);
	}
    
    vector< vector<long> > pairs;
    
    for (int i = 0; i < sorted_r.size(); i++)
    {
    	long first = sorted_r[i];
		long temp = k - first;
		if (binarySearch(sorted_r, temp))
		{
			vector<long> pair;
			pair.push_back(first);
			pair.push_back(temp);
			pairs.push_back(pair);
		}		
	}

	return pairs;
}

bool binarySearch(vector<long> nums, long temp)
{
	int left = 0, right = nums.size() - 1, mid;
	
	while (left < right)
	{
		mid = (left + right) / 2;
		if (temp > nums[mid])
		{
				left = mid + 1;
		}	
		else if (temp < nums[mid])
		{
			right = mid;
		}
		else
		{
			return true;
		}
	}
	return false;
}

int main()
{
    vector<long> nums;
    ifstream in("random.txt");
    long n;
    while(in >> n)
        nums.push_back(n);
    in.close();

    long k;
    cout << "Enter the value of K: ";
    cin >> k;

    vector< vector<long> > result = smartSearch(nums, k);

    for(int i = 0; i < result.size(); i++)
        cout << result[i][0] << ", " << result[i][1] << endl;

    return 0;
}
