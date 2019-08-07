
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;


typedef vector<pair<int, int>> PlayVt;
bool sortBestGenre(const pair<string,int> &a,  const pair<string,int> &b) 
{ 
    return (a.second > b.second); 
} 

bool sortPlay(const pair<int, int> &a, const pair<int, int> &b)
{ 
    return (a.first > b.first); 
} 

struct stGenre
{
    bool operator () (std::pair<std::string, int> const& value)
    {
        return (value.first == name);
    }
    string name;
};


vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    map<string, PlayVt> bestMap;
    vector<pair<string, int>> playMap;

    for (int ii = 0; ii < genres.size(); ii++)
    {
        auto iterF = bestMap.find(genres[ii]);
        if (iterF == bestMap.end())
        {
            PlayVt playVt;
            playVt.push_back(make_pair(plays[ii], ii));
            bestMap.insert(make_pair(genres[ii], playVt));
        }
        else
        {
            iterF->second.push_back(make_pair(plays[ii], ii));
        }

        stGenre genre;
        genre.name = genres[ii];
        auto iterF_play = find_if(playMap.begin(), playMap.end(), genre);

        if (iterF_play == playMap.end())
        {
            playMap.push_back(make_pair(genres[ii], plays[ii]));
        }
        else
        {
           iterF_play->second += plays[ii]; 
        }

    }

    sort(playMap.begin(), playMap.end(), sortBestGenre);

    for (auto iter = playMap.begin(); iter != playMap.end(); iter++)
    {
        auto iterF = bestMap.find(iter->first);
        if (iterF != bestMap.end())
        {
            sort(iterF->second.begin(), iterF->second.end(), sortPlay);
            int nCount = min(2, (int) iterF->second.size());

            for (int ii = 0; ii < nCount; ii++)
            {
                answer.push_back(iterF->second[ii].second);
            }
        }
    }

    return answer;
}
