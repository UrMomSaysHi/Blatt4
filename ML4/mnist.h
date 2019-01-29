//  MNIST.h

#pragma once
#ifndef MNIST_h
#define MNIST_h

#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

// BIG-Endian to LITTLE-Endian byte swap
#define swap16(n) (((n&0xFF00)>>8)|((n&0x00FF)<<8))
#define swap32(n) ((swap16((n&0xFFFF0000)>>16))|((swap16(n&0x0000FFFF))<<16))

typedef unsigned char byte;


struct MNISTchar {
    std::vector<float> pixelData;          // Store the 784 (28x28) pixel color values (0-255) of the digit-image
    std::vector<float> output;             // Store the expected output (e.g: label 5 / output 0,0,0,0,0,1,0,0,0,0)
    int label;                             // Store the handwritten digit in number form
    MNISTchar() : pixelData(std::vector<float>()), output(std::vector<float>(10)), label(0) {}
};


class MNIST {
public:
    const std::vector<MNISTchar> trainingData;  // Set of 60.000 handwritten digits to train the net

    MNIST(const std::string& path);

private:
    std::vector<MNISTchar> getMNISTdata(const std::string& imagepath, const std::string& labelpath);

public:
    void testPrintout(int startChar, int endChar) const;
    std::vector<std::vector<float>> to_matrix(size_t idx);
};

#endif
