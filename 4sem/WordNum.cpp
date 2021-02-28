#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>

// FIXIT: очень много лишний пустых строк. давайте запустим автоформатирование, чтобы убрать их

unsigned char low(unsigned char c) {

    return std::tolower(c);

}

// FIXIT: числа на конце названий обычно не несут никакой полезной информации. давайте переименуем
struct stat1 {

    int count;
    std::string word;

};

// FIXIT: название компаратора
bool comp1(struct stat1 a, struct stat1 b) {

    return a.count > b.count;

}

std::string prepare(std::string& s) {

    // FIXIT: тут можно просто писать std::transform(...., std::tolower);
    std::transform(s.begin(), s.end() - 1, s.begin(), low);

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

        std::vector < struct stat1 > s;

        struct stat1 b = { 0, "" };
        for (int i = 0; it != freq.end(); it++, i++) {

            s.push_back(b);
            s[i].count = it->second;
            s[i].word = it->first;

        }

        std::sort(s.begin(), s.end(), comp1);

        std::vector < struct stat1 >::iterator it1 = s.begin();

        for (int i = 0; it1 != s.end(); it1++, i++)

            std::cout << s[i].word << " " << s[i].count << std::endl;
        
        /*
        Еще можно писать либо вот так:
        for (size_t i = 0; i < s.size(); ++i)
            std::cout << s[i].word << " " << s[i].count << std::endl;
        
        Либо вот так:
        for (const auto& stat : s)
            std::cout << stat.word << " " << stat.count << std::endl;
            
        Оба варианта выглядят проще.
        */

        file.close();
    }
    return 0;
}
