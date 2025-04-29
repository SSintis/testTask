#include "../include/BmpEditor.hpp"

void BmpEditor::run(std::string inputPath, std::string outputPath) {
    loadBmp(inputPath);
    drawCenteredDiagonalCross();
    saveBmp(outputPath);
}

void BmpEditor::loadBmp(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open file");
    }

    fileHeader.resize(14);
    file.read(reinterpret_cast<char*>(fileHeader.data()), 14);

    if (fileHeader[0] != 'B' || fileHeader[1] != 'M') {
        throw std::runtime_error("Not a BMP file");
    }

    infoHeader.resize(40);
    file.read(reinterpret_cast<char*>(infoHeader.data()), 40);

    width = *(int*)&infoHeader[4];
    height = *(int*)&infoHeader[8];
    bitsPerPixel = *(short*)&infoHeader[14];

    if (bitsPerPixel != 24 && bitsPerPixel != 32) {
        throw std::runtime_error("Unsupported BMP format (only 8, 24, 32-bit supported)");
    }

    int headerSize = *(int*)&infoHeader[0];
    if (headerSize > 40) {
        file.ignore(headerSize - 40);
    }

    int rowSize = ((bitsPerPixel * width + 31) / 32) * 4;
    pixels.resize(height * rowSize);
    
    for (int y = 0; y < height; ++y) {
        file.read(reinterpret_cast<char*>(&pixels[y * rowSize]), rowSize);
    }
}

void BmpEditor::drawCenteredDiagonalCross() {
    int rowSize = ((bitsPerPixel * width + 31) / 32) * 4;
    int bytesPerPixel = bitsPerPixel / 8;
    
    float centerX = width / 2.0f;
    float centerY = height / 2.0f;
    
    float maxRadius = std::sqrt(centerX * centerX + centerY * centerY);
    
    for (float r = -maxRadius; r <= maxRadius; r += 0.5f) {
        int x1 = static_cast<int>(centerX + r);
        int y1 = static_cast<int>(centerY + r);
        
        if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height) {
            int offset1 = y1 * rowSize + x1 * bytesPerPixel;
            setPixelColor(offset1, 255, 0, 0);
        }

        int x2 = static_cast<int>(centerX + r);
        int y2 = static_cast<int>(centerY - r);
        
        if (x2 >= 0 && x2 < width && y2 >= 0 && y2 < height) {
            int offset2 = y2 * rowSize + x2 * bytesPerPixel;
            setPixelColor(offset2, 255, 0, 0);
        }
    }
}

void BmpEditor::setPixelColor(int offset, unsigned char r, unsigned char g, unsigned char b) {
    if (bitsPerPixel == 24 || bitsPerPixel == 32) {
        pixels[offset] = b;
        pixels[offset+1] = g;
        pixels[offset+2] = r;
    }
}

void BmpEditor::saveBmp(const std::string& filepath) {
    std::ofstream file(filepath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not create output file");
    }

    file.write(reinterpret_cast<char*>(fileHeader.data()), fileHeader.size());
    file.write(reinterpret_cast<char*>(infoHeader.data()), infoHeader.size());
    
    if (bitsPerPixel == 8) {
        file.write(reinterpret_cast<char*>(palette.data()), palette.size());
    }

    int rowSize = ((bitsPerPixel * width + 31) / 32) * 4;
    for (int y = 0; y < height; ++y) {
        file.write(reinterpret_cast<char*>(&pixels[y * rowSize]), rowSize);
    }
}