//
// Created by fconde on 4/10/23.
//

#include <iostream>

#include "FigvAuxiliaryFunctions.h"

void FigvLog(std::string className, int line, std::string message) {
    std::cout << "FIGV: " << className << "(" << line << "): " << message << std::endl;
}
