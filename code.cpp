#include<bits/stdc++.h>
#define TOTAL_SIZE 17
#define TOTAL_SKILLS 4
#define TOTAL_PERSONS 12
#define Rating first
#define Id second

using namespace std;

vector <pair<int,int>> v1, v2;
vector <int> normalizedData;

struct attributes {
	int id;
	int skills[TOTAL_SKILLS];
};

vector <attributes> dataset;
vector <int> skillsWeight;
int teamSize, teamNumber = 1;

void getData()
{
	for(int i = 0; i < TOTAL_SIZE; i++)
	{
		if(i < TOTAL_PERSONS)
		{
			attributes data;
			cin >> data.id;
			for(int j = 0; j < TOTAL_SKILLS; j++)
			{
				cin >> data.skills[j];
			}
			dataset.push_back(data);
		}
		else if(i < TOTAL_SKILLS + TOTAL_PERSONS)
		{
			int id, weight;
			cin >> id >> weight;
			skillsWeight.push_back(weight);
		}
		else
		{
			cin >> teamSize;
		}
	}
}

void computeFinalRating()
{
	for(int i = 0; i < TOTAL_PERSONS; i++)
	{
		int finalRating = 0, totalWeight = 0;
		for(int j = 0; j < TOTAL_SKILLS; j++)
		{
			finalRating += skillsWeight[j] * dataset[i].skills[j];
			totalWeight += skillsWeight[j];
		}
		normalizedData.push_back(finalRating / totalWeight);
	}
}

void createTeams(vector <pair<int,int>> v)
{
	int n = v.size();
	assert(n % teamSize == 0);
	int REQUIRED_SIZE = n / 2;
	
	int GLOBAL_MINIMUM = INT_MAX;
	for(int i = 0; i < (1 << n); i++)
	{
		int sum1 = 0, sum2 = 0;
		int CURRENT_SIZE = __builtin_popcount(i);
		vector <pair<int,int>> res1, res2;
		if(CURRENT_SIZE == REQUIRED_SIZE)
		{
			for(int j = 0; j < n; j++)
			{
				if(i & (1 << j)) res1.push_back(v[j]);
				else res2.push_back(v[j]);
			}
			for(auto j : res1) sum1 += j.Rating;
			for(auto j : res2) sum2 += j.Rating;
			if(GLOBAL_MINIMUM > abs(sum1 - sum2))
			{
				GLOBAL_MINIMUM = abs(sum1 - sum2);
				v1 = res1;
				v2 = res2;
			}
		}
	}
	if(v1.size() == teamSize)
	{
		cout << "Team - " << teamNumber << ": ";
		for(auto i : v1) cout << i.Id << " ";
		cout << "\n";
		teamNumber++;
		cout << "Team - " << teamNumber << ": ";
		for(auto i : v2) cout << i.Id << " ";
		cout << "\n";
		teamNumber++;	
	}
}

void getTeams()
{ 
	vector <pair<int,int>> v;
	for(int i = 0; i < normalizedData.size(); i++)
	{
		v.push_back({normalizedData[i], i + 1});
	}
	sort(v.begin(),v.end());
	createTeams(v);
	vector <pair<int,int>> ans1 = v1, ans2 = v2;
	createTeams(ans1);
	createTeams(ans2);
}

int main()
{
	freopen("sample_data.txt","r",stdin);
	freopen("teams_formed.txt","w",stdout);
	getData();
	computeFinalRating();
	getTeams();
	return 0;
}

