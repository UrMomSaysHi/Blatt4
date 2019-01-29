#include "mnist.h"


/*!
 * @brief constructor
 *
 * @param path: path that contains data files
 *
 * @return result
 */
MNIST::MNIST(const std::string& path) : trainingData(getMNISTdata(path + "images.bin", path + "images.labels")){
    if(!this->trainingData.size()) { std::cout <<"ERROR: parsing training data" <<std::endl; }
}



/*!
 * @brief data loader
 *
 * @copyright 2016 Peter Baumann
 *
 * @param imgpath: path to training images
 * @param labelpath: path to traininglabels
 *
 * @return vector of  MNISTchar
 */
std::vector<MNISTchar> MNIST::getMNISTdata(const std::string& imagepath, const std::string& labelpath) {
    std::vector<MNISTchar> tmpdata = std::vector<MNISTchar>();
    std::fstream file (imagepath, std::ifstream::in | std::ifstream::binary);
    int magicNum_images = 0, magicNum_labels = 0;
    int itemCount_images = 0, itemCount_labels = 0;
    // READ THE IMAGE FILE DATA
    if(file.is_open()) {
        int row_count = 0, col_count = 0;
        // FILE HEADER INFO is stored as 4 Byte Integers
        file.read((char*)&magicNum_images, 4);
        file.read((char*)&itemCount_images, 4);
        file.read((char*)&row_count, 4);
        file.read((char*)&col_count, 4);
        // Transform Byte values from big to little endian
        magicNum_images = swap32(magicNum_images);
        itemCount_images = swap32(itemCount_images);
        row_count = swap32(row_count);
        col_count= swap32(col_count);
        // Loop throug all the items and store every pixel of every row
        for (int i = 0; i < itemCount_images; i++) {
            MNISTchar tmpchar = MNISTchar();
            for(int r = 0; r < (row_count * col_count); r++) {
                byte pixel = 0;
                // read one byte (0-255 color value of the pixel)
                file.read((char*)&pixel, 1);
                tmpchar.pixelData.push_back((float)pixel / 255);
            }
            tmpdata.push_back(tmpchar);
        }
    }
    file.close();
    // READ THE LABEL FILE DATA
    file.open(labelpath, std::ifstream::in | std::ifstream::binary);
    if (file.is_open()) {
        file.read((char*)&magicNum_labels, 4);
        file.read((char*)&itemCount_labels, 4);
        magicNum_labels = swap32(magicNum_labels);
        itemCount_labels = swap32(itemCount_labels);
        if(itemCount_images == itemCount_labels) {
            // read all the labels and store them in theire MNISTchars
            for(MNISTchar& m : tmpdata) {
                file.read((char*)&m.label, 1);
                m.output[m.label] = 1.0f;
            }
        }
    }
    file.close();
    return tmpdata;
}


/*!
 * @brief print sample of data to application output
 *
 * @copyright 2016 Peter Baumann
 *
 * @param startChar: id of image to start at
 * @param endChar: id of image to stop at
 *
 */
void MNIST::testPrintout(int startChar, int endChar) const {
    for(int i = startChar; i < endChar; i++) {
        std::cout <<"------------------------------" <<std::endl;
        int count = 0;
        for (auto r : trainingData[i].pixelData) {
            if(count < 27) {
                if(r < 0.25) std::cout <<" ";
                else if(r < 0.5) std::cout <<"-";
                else if(r < 0.75) std::cout <<"+";
                else if(r <= 1.0) std::cout <<"#";
                ++count;
            } else {
                std::cout <<std::endl;
                count = 0;
            }
        }
        std::cout <<" Expected Output: ";
        for(const short& x : trainingData[i].output) { std::cout <<x; }
        std::cout <<std::endl;
        std::cout <<"\t\tThis is a: " << trainingData[i].label  <<std::endl;
        std::cout <<"------------------------------" <<std::endl;
    }
}


/*!
 * @brief convert image to matrix for displaying on widget
 *
 * @param idx index of image in trainingData
 *
 * @return image as matrix
 *
 */
std::vector<std::vector<float>> MNIST::to_matrix(size_t idx) {
    std::vector<float> img = trainingData[idx].pixelData;
    size_t n = static_cast<size_t>(sqrt(img.size()));
    std::vector<std::vector<float>> result(n, std::vector<float>(n));
    for (size_t i=0; i<n; i++){
        for (size_t j=0; j<n; j++) {
            result[i][j] = img[n*i+j];
        }
    }
    return result;
}
