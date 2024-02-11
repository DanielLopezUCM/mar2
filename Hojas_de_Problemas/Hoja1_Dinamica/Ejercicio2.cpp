
#include <vector>
#include <math.h>
#include <limits.h>

#define INF INT_MAX

using namespace std;

/*



*/

vector<int> resolver(vector<int> const &monedas, int objetivo)
{
    vector<vector<pair<int, int>>> dp(monedas.size() + 1, vector<pair<int, int>>(objetivo + 1, {INF, INF}));

    dp[0][0] = {0, 0};
    for (int i = 1; i, i <= monedas.size(); i++)
    {
        dp[i][0] = {0, 0};
        for (int j = monedas[i - 1]; j < objetivo; j++)
        {
            if (dp[i - 1][j - monedas[i - 1]].first != INF)
            {
                dp[i][j] = {dp[i - 1][j - monedas[i - 1]].first + 1, i};
                if (dp[i - 1][j].first != INF && dp[i - 1][j].first > dp[i][j].first)
                {
                    dp[i][j] = dp[i - 1][j];
                }
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    vector<int> sol;

    if (dp[monedas.size()][objetivo].first != INF)
    {
        int k = objetivo, ant = monedas.size();
        while (dp[ant][objetivo].second != 0)
        {
            sol.push_back(dp[ant][objetivo].second);
            ant = dp[ant][objetivo].second;
            objetivo -= monedas[ant - 1];
        }
    }

    return sol;
}