#include <iostream>
#include <sstream>
#include <sha256.h>
#include <conio.h>
#include <ctime>
#include <cstdio>
using namespace std;

string getstr(int c){
    stringstream ss;
    string s;
    ss << (char)c;
    ss >> s;
    return s;
}

string balloonHash(string content, string NaCl){
    int s_cost = 100, t_cost = 100;
    SHA256 hash;
    string buf[s_cost+1];
    string prev;
    string salt = hash(NaCl);

    for(int s = 0; s < s_cost; s++){
        buf[s] = hash(content + salt);
    }

    for(int t = 1; t < t_cost + 1; t++){
        for(int m = 0; m < s_cost; m++){
            prev = buf[(t-1) % s_cost];
            buf[t] = hash(prev + salt);

            for(int i = 0; i < 20; i++){
                string other = hash(getstr(m + t) + getstr(i + m) + getstr(t + i) + salt);
                buf[m] = hash(buf[i] + other);
            }
        }
        //cout << t << ". " << buf[t] << "\n";
    }

    string total;
    for(int i = 0; i < s_cost + 1; i++){
        total += buf[i];
    }
    return hash(total);
}

int main()
{
    string content, salt;
    SHA256 h;
    cout << "<text> <salt>:\n";
    cin >> content >> salt;
    clock_t start = clock();
    string result = balloonHash(content, salt);
    cout << "\nResult: " << result;
    cout << "\nTook " << double(clock() - start)/1000 << " seconds\n\n";
    cout << "press any key to continue...\n";
    getch();
    return 0;
}
