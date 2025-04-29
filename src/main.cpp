/*
Готовое тестовое задание для компании 'Effective Mobile'

Тестовое задание было реализовано с помощью двух классов
BmpToConsole.hpp и BmpEditor.hpp, в первом реализована логика
вывода в консоль изображения формата BMP(24 и 32 бита), а во втором реализована
логика добавления на изображение X(креста)

Как запустить:
    ->cd build/
    ->cmake ..
    ->make
    ->cd bin/
    ->./main

    -Enter input BMP file path: ../../assets/13.bmp
    -Enter output BMP file path: ../../assets/result.bmp

*/
#include "../include/BmpToConsole.hpp"
#include "../include/BmpEditor.hpp"

int main() {
    BmpEditor imageEditor;
    BmpToConsole drawImage;

    std::string inputPath, outputPath;
    
    std::cout << "Enter input BMP file path: ";
    std::cin >> inputPath;
    std::cout << "Enter output BMP file path: ";
    std::cin >> outputPath;

    imageEditor.run(inputPath, outputPath);

    drawImage.initialized(inputPath);
    drawImage.printToConsole();

    drawImage.initialized(outputPath);
    drawImage.printToConsole();
    
    std::cout << "Image processed and saved successfully!\n";

    return 0;
}