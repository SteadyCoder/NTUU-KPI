#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

string new_s(string w) {
    string result = "no answer";
    int n = w.length()
    int i;
    for (i = 1; i < n; ++i)
        if (w[i - 1] > w[i]) break;
    i--;
    
    int j = i + 1;
    while (j < n) {
        if (w[j] > a[i])
            break;
        j++;
    }
    
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
    
    i++;
    while (i < n) {
        
    }

    return result;
}

int main() {
    int n;
    cin >> n;

    vector<string> a(n);

    for (int i = 0; i < n; ++i) 
        cin >> a[i];
    
    
    
    
    return 0;

}
