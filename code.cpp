#include<bits/stdc++.h>
#define Rating first
#define Id second

using namespace std;

vector <pair<int,int>> v1, v2;
int teamNumber = 1, TOTAL_SKILLS, TOTAL_MEMBERS, teamSize;
vector <int> normalizedData;

struct attributes {
	int id;
	vector <int> skills;
};

vector <attributes> dataset;
vector <int> skillsWeight;

/**
 * This function fetchs the data from the file
 * the format of file will be:
 * first line contains 3 integers: TOTAL_SKILLS, TOTAL_MEMBERS, TeamSize
 * First TOTAL_MEMBERS number of lines are number of members and the rate of their respective skills (there are total 4 skills).
 * Next TOTAL_SKILLS lines will be weights assigned to each skill. (user's choice)
 */
void getData()
{
	cin >> TOTAL_MEMBERS >> TOTAL_SKILLS >> teamSize; // processing first line
	cout << teamSize;
	vector <attributes> tempDataset(TOTAL_MEMBERS);
	vector <int> tempSkillsWeight(TOTAL_SKILLS);
	for(int i = 0; i < TOTAL_MEMBERS; i++)   // proccessinf the members rating with their respective Ids.
	{
		attributes data;
		cin >> data.id;
		for(int j = 0; j < TOTAL_SKILLS; j++)
		{
			int skill;
			cin >> skill;
			data.skills.push_back(skill);
		}
		tempDataset[data.id - 1] = data;
	}
	for(int i = 0; i < TOTAL_SKILLS; i++)   // processing the skill's weight with their respective Ids.
	{
		int id, weight;
		cin >> id >> weight;
		tempSkillsWeight[id - 1] = weight;
	}
	dataset = tempDataset;
	skillsWeight = tempSkillsWeight;
}

/**
 * Here the weighted mean is calculated in the skills.
 * We are provided with the weights so do summation of all w_i * s_i where w_i is weight and s_i is skill so we get the total "effective" skill rate
 * then we simply divide it the sum of all weights so we get the weighted mean.
 */
void computeFinalRating()
{
	for(int i = 0; i < TOTAL_MEMBERS; i++) // iterate over all members and for each calculate the effective skill rate
	{
		int finalRating = 0, totalWeight = 0;
		for(int j = 0; j < TOTAL_SKILLS; j++)
		{
			finalRating += skillsWeight[j] * dataset[i].skills[j];  // w_i * s_i = "effective skill rate"
			totalWeight += skillsWeight[j];
		}
		normalizedData.push_back(finalRating / totalWeight);   // divide by sum of all weights
	}
}

/**
 * This is actual heart of the entire code here the grouping is done in the following manner:
 * if there are persons in the gourp then it is divided into 2 "stable" groups of equal number of people 
 * here the we are more focused on the wprd "stable" because ultimate target is to achieve more similarities among all the groups/
 */
void createTeams(vector <pair<int,int>> v)
{
	
	int n = v.size();
	assert(n % teamSize == 0);
	int REQUIRED_SIZE = n / 2;
	int GLOBAL_MINIMUM = INT_MAX;
	for(int i = 0; i < (1 << n); i++)  // just iterated to all the possible combinations
	{
		int sum1 = 0, sum2 = 0;
		int CURRENT_SIZE = __builtin_popcount(i);  // i am only interested in dividing equally (i.e size = n / 2)
		vector <pair<int,int>> res1, res2;
		if(CURRENT_SIZE == REQUIRED_SIZE)
		{
			for(int j = 0; j < n; j++)
			{
				if(i & (1 << j)) res1.push_back(v[j]);  // separates out the two groups
				else res2.push_back(v[j]);
			}
			for(auto j : res1) sum1 += j.Rating;  // compute the respective effective group ratings
			for(auto j : res2) sum2 += j.Rating;
			
			// if the get difference smaller than then current minimum then yes we are interesteed in such formation
			// else we continue with next possible combination
			if(GLOBAL_MINIMUM > abs(sum1 - sum2))   
			{
				GLOBAL_MINIMUM = abs(sum1 - sum2);
				v1 = res1;
				v2 = res2;
			}
		}
	}
	if(v1.size() == teamSize) // here if we finally achieve our required team size then we print the teams
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

