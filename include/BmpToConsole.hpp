#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <iomanip>

class BmpToConsole {
public:
    void initialized(const std::string& filepath);
    void printToConsole() const;

private:
    int width = 0;
    int height = 0;
    int bitsPerPixel = 0;
    std::vector<unsigned char> pixels;

    void loadBmp(const std::string& filepath);
    char getCharForBrightness(unsigned char brightness) const;
};