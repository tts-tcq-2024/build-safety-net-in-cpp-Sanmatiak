#include "Soundex.h"
#include <cctype>
#include <unordered_map>
static const std::unordered_map<char, char> soundexCodes {
    {'B', '1'}, {'F', '1'}, {'P', '1'}, {'V', '1'},
    {'C', '2'}, {'G', '2'}, {'J', '2'}, {'K', '2'}, {'Q', '2'},
    {'S', '2'}, {'X', '2'}, {'Z', '2'},
    {'D', '3'}, {'T', '3'},
    {'L', '4'},
    {'M', '5'}, {'N', '5'},
    {'R', '6'}
};
char getSoundexCode(char c) {
    c = std::toupper(c);
    auto it = soundexCodes.find(c);
    return (it != soundexCodes.end()) ? it->second : '0';
}
void appendSoundexCode(std::string& soundex, char code, char& prevCode) {
    if (code != '0' && code != prevCode) {
        soundex += code;
        prevCode = code;
    }
}
std::string processInitialCharacter(const std::string& name) {
    std::string soundex;
    soundex += std::toupper(name[0]);
    return soundex;
}
void processRemainingCharacters(const std::string& name, std::string& soundex) {
    char prevCode = getSoundexCode(name[0]);
    for (size_t i = 1; i < name.length() && soundex.length() < 4; ++i) {
        char code = getSoundexCode(name[i]);
        appendSoundexCode(soundex, code, prevCode);
    }
}
std::string generateSoundex(const std::string& name) {
    if (name.empty()) return "";
    std::string soundex = processInitialCharacter(name);
    processRemainingCharacters(name, soundex);
    soundex.resize(4, '0');
    return soundex;
}
