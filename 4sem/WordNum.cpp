#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>

struct st {

    int count;
    std::string word;

};

bool comp(struct st a, struct st b) {

    return a.count > b.count;

}

std::string prepare(std::string& s) {

    std::transform(s.begin(), s.end() - 1, s.begin(), std::tolower);
    const std::string del = ".,/\\?-=+)(*&^%$#@!";

    if (s.find_first_of(del, 0) != std::string::npos)
        s.pop_back();

    return s;
}

int main() {

    std::ifstream file("file.txt");
    std::map < std::string, int > freq;

    if (file.is_open()) {

        std::string word;
        while (!file.eof()) {

            file >> word;
            word = prepare(word);
            freq[word]++;

        }

        std::map < std::string, int >::iterator it = freq.begin();
        std::vector < struct st > s;

        struct st b = { 0, "" };
        for (int i = 0; it != freq.end(); it++, i++) {

            s.push_back(b);
            s[i].count = it->second;
            s[i].word = it->first;

        }

        std::sort(s.begin(), s.end(), comp);

        for (const auto& st : s)
            std::cout << st.word << " " << st.count << std::endl;

        file.close();
    }
    return 0;
}
