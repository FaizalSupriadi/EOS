#include <iostream>
using namespace std;
// Als je bijvoorbeeld: "cat text.txt | ./DezeCode.exe | sort | uniq" doet dan wordt de text in de txt file
// woord voor woord geprint in hoofletters, gesorteerd en alleen de unieke woorden blijven.
int main() {
    string text;
    while (cin >> text){
        for (unsigned int j = 0; j < text.size(); j++) {
        text[j] = toupper(text[j]);
        }
        if (cin.eof()) {
            return 0;
        }
        cout << text << '\n';
    }
}