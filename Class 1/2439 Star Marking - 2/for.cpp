#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;
    
    for (int i = 1; i <= N; i++) {
        // 공백 출력
        for (int j = 1; j <= N - i; j++) {
            cout << " ";
        }
        // 별 출력
        for (int j = 1; j <= i; j++) {
            cout << "*";
        }
        cout << "\n"; // 줄바꿈
    }
    
    return 0;
}