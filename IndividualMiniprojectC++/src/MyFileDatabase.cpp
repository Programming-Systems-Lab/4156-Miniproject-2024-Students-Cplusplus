/** 
MIT License

Copyright (c) 2024 Programming Systems Lab @ Columbia University

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "MyFileDatabase.h"
#include <iostream>
#include <fstream>

/**
 * Constructs a MyFileDatabase object and loads up the data structure with
 * the contents of the file.
 *
 * @param flag     used to distinguish mode of database
 * @param filePath the path to the file containing the entries of the database
 */
MyFileDatabase::MyFileDatabase(int flag, const std::string& filePath) : filePath(filePath) {
    if (flag == 0) {
        deSerializeObjectFromFile();
    }
}

/**
 * Sets the department mapping of the database.
 *
 * @param mapping the mapping of department names to Department objects
 */
void MyFileDatabase::setMapping(const std::map<std::string, Department>& mapping) {
    departmentMapping = mapping;
}

/**
 * Gets the department mapping of the database.
 *
 * @return the department mapping
 */
std::map<std::string, Department> MyFileDatabase::getDepartmentMapping() const {
    return departmentMapping;
}

/**
 * Saves the contents of the internal data structure to the file. Contents of the file are
 * overwritten with this operation.
 */
void MyFileDatabase::saveContentsToFile() const {
    std::ofstream outFile(filePath, std::ios::binary);
    size_t mapSize = departmentMapping.size();
    outFile.write(reinterpret_cast<const char*>(&mapSize), sizeof(mapSize));
    for (const auto& it : departmentMapping) {
        size_t keyLen = it.first.length();
        outFile.write(reinterpret_cast<const char*>(&keyLen), sizeof(keyLen));
        outFile.write(it.first.c_str(), keyLen);
        it.second.serialize(outFile);
    }
    outFile.close();
}

/**
 * Deserializes the object from the file and returns the department mapping.
 *
 * @return the deserialized department mapping
 */
void MyFileDatabase::deSerializeObjectFromFile() {
    std::ifstream inFile(filePath, std::ios::binary);
    size_t mapSize;
    inFile.read(reinterpret_cast<char*>(&mapSize), sizeof(mapSize));
    for (size_t i = 0; i < mapSize; ++i) {
        size_t keyLen;
        inFile.read(reinterpret_cast<char*>(&keyLen), sizeof(keyLen));
        std::string key(keyLen, ' ');
        inFile.read(&key[0], keyLen);
        Department dept; 
        dept.deserialize(inFile);
        departmentMapping[key] = dept;
    }
    inFile.close();
}

/**
 * Returns a string representation of the database.
 *
 * @return a string representation of the database
 */
std::string MyFileDatabase::display() const {
    std::string result;
    for (const auto& it : departmentMapping) {
        result += "For the " + it.first + " department:\n" + it.second.display() + "\n";
    }
    return result;
}
