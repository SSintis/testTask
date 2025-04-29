#include "../include/BmpToConsole.hpp"

void BmpToConsole::initialized(const std::string& filepath) {
    loadBmp(filepath);
}
    
void BmpToConsole::printToConsole() const {
    if (pixels.empty()) {
        throw std::runtime_error("No image loaded");
    }
    
    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            unsigned char brightness = pixels[y * width + x];
            char c = getCharForBrightness(brightness);
            std::cout << c;
        }
        std::cout << '\n';
    }
}
    
void BmpToConsole::loadBmp(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open file");
    }
    
    unsigned char fileHeader[14];
    file.read(reinterpret_cast<char*>(fileHeader), 14);
    
    if (fileHeader[0] != 'B' || fileHeader[1] != 'M') {
        throw std::runtime_error("Not a BMP file");
    }
    
    unsigned char infoHeader[40];
    file.read(reinterpret_cast<char*>(infoHeader), 40);
    
    width = *(int*)&infoHeader[4];
    height = *(int*)&infoHeader[8];
    bitsPerPixel = *(short*)&infoHeader[14];
    
    if (bitsPerPixel != 24 && bitsPerPixel != 32) {
        std::cerr << "Image has " << bitsPerPixel << " bits per pixel (only 24 or 32 supported)\n";
        throw std::runtime_error("Unsupported BMP format");
    }
    
    int headerSize = *(int*)&infoHeader[0];
    if (headerSize > 40) {
        file.ignore(headerSize - 40);
    }
    
    int rowSize = ((bitsPerPixel * width + 31) / 32) * 4;
    int pixelRowSize = (bitsPerPixel / 8) * width;
    std::vector<unsigned char> row(rowSize);
    
    pixels.resize(width * height);
    bool isGrayscale = true;
    
    for (int y = 0; y < height; ++y) {
        file.read(reinterpret_cast<char*>(row.data()), rowSize);
                
        for (int x = 0; x < width; ++x) {
            int offset = x * (bitsPerPixel / 8);
            unsigned char b = row[offset];
            unsigned char g = row[offset + 1];
            unsigned char r = row[offset + 2];
                    
            if (r != g || g != b) {
                isGrayscale = false;
            }

            pixels[y * width + x] = (r + g + b) / 3;
        }
    }
    
    if (!isGrayscale) {
        std::cerr << "Warning: Image is not grayscale (R, G, B channels differ)\n";
        std::cerr << "Bits per pixel: " << bitsPerPixel << " (" << (bitsPerPixel/8) << " bytes per pixel)\n";
        std::cerr << "Continuing with grayscale conversion...\n";
    }
}
    
char BmpToConsole::getCharForBrightness(unsigned char brightness) const {
    const std::string chars = " .:-=+*#%@";
    int index = static_cast<int>(brightness / 255.0f * (chars.size() - 1));
    return chars[index];
}