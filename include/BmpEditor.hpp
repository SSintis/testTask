#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <cmath>

class BmpEditor {
public:
    void run(std::string inputPath, std::string outputPath);

private:
    int width = 0;
    int height = 0;
    int bitsPerPixel = 0;
    std::vector<unsigned char> pixels;
    std::vector<unsigned char> palette;
    std::vector<unsigned char> fileHeader;
    std::vector<unsigned char> infoHeader;

    void loadBmp(const std::string& filepath);
    void drawCenteredDiagonalCross();
    void setPixelColor(int offset, unsigned char r, unsigned char g, unsigned char b);

    void saveBmp(const std::string& filepath);
};