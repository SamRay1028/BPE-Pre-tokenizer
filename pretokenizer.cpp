#include <iostream>
#include <string_view>
#include <string.h>
#include <string>
#include <fstream>
#include <unicode/utypes.h>
#include <unicode/ustring.h>
#include <vector>
#include <mach/mach.h>
#include <memory>
#include <string_view>
#include "robin_hood.h"

typedef struct token2{
    uint8_t split_index = 0;
    int frequency = 0;
    int size = 0;
    int* words;
}token2;

void pretokenizer(){
    int iterations = 32000;
    std::ifstream corpusText("/Users/samraya/Desktop/The complete works of William Shakespeare.txt");
    robin_hood::unordered_map<std::string_view, token2> token_data;
    robin_hood::unordered_set<std::string> token_record;
    robin_hood::unordered_map<std::string, int> word_frequencies;
    robin_hood::unordered_map<std::string, int> newFrequencies;
    std::priority_queue<std::pair<int, std::string_view>> pq;
    std::string line;
    std::string str;
    std::string temp_token;
    int pos1 = 0;
    int pos2 = 0;
    token_record.insert(std::string(1, '$'));
    while(getline(corpusText, line)){
        line.insert(0, 1, '@');
        line.push_back('$');
        if(line.length() > 0){
            for(int i = 0; i < line.length() - 1; ++i){
                token_record.insert(std::string(1, line[i]));
                if(line[i] == ' '){
                    // || line[i] == '$'
                    ++pos2;
                    ++word_frequencies[line.substr(pos1, pos2 - pos1)];
                    --pos2;
                    pos1 = pos2;
                }
                ++pos2;
                 
            }
            pos1 = 0;
            pos2 = 0;
        }
    }
    std::string_view sv;
    for(auto& pair : word_frequencies){
        for(int i = 0; i < pair.first.length() - 1; ++i){
            sv = std::string_view(pair.first).substr(i, 2);
            token_data[sv].frequency += pair.second;
            ++token_data[sv].size;
        }
    }
    for(auto& pair : word_frequencies){
        for(int i = 0; i < pair.first.length() - 1; ++i){
            sv = std::string_view(pair.first).substr(i, 2);
            token_data[sv].words = (int*)malloc(token_data[sv].size * sizeof(int));
            token_data[sv].size = 0;
        }
    }
    std::cout << "break" << std::endl;
    int count = 0;
    for(auto& pair : word_frequencies){
        for(int i = 0; i < pair.first.length() - 1; ++i){
            sv = std::string_view(pair.first).substr(i, 2);
            token_data[sv].words[token_data[sv].size] = count;
            ++token_data[sv].size;
        }
        ++count;
    }
    for(auto& pair : token_data){
        pair.second.split_index = 1;
    }
    for(auto t : token_data){
        pq.push({t.second.frequency, t.first});
    }
}
