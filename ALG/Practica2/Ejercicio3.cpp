#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string subsecuenciaComunMasLarga(const string& s1, const string& s2) {
    int n = s1.size();
    int m = s2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Rellenamos la tabla de programación dinámica
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Reconstruimos la subsecuencia común más larga
    string resultado;
    int i = n; /* largo de s1 */
    int j = m; /* largo de s2 */

    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            resultado.push_back(s1[i - 1]);
            i--;
            j--;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    reverse(resultado.begin(), resultado.end());

    return resultado;
}

int main() {
    string s1 = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
    string s2 = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";

    string lcs = subsecuenciaComunMasLarga(s1, s2);

    cout << "Subsecuencia comun mas larga: " << lcs << endl;
    cout << "Longitud: " << lcs.size() << endl;

    return 0;
}