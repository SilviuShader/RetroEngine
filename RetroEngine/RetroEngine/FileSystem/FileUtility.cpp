#include "FileUtility.h"

#include <iostream>
#include <fstream>

#include <filesystem>

using namespace std;
using namespace filesystem;

namespace RetroEngine::FileSystem
{
    string FileUtility::ReadFile(const string& filename)
    {
        if (!exists(filename))
        {
            cout << "Can't open file " << filename << endl;
            return "";
        }

        try
        {
            ifstream inputFileStream(filename);
            string str((istreambuf_iterator<char>(inputFileStream)),
                istreambuf_iterator<char>());

            inputFileStream.close();

            return str;
        }
        catch (ifstream::failure e)
        {
            cout << "Can't read file " << filename << endl;
            return "";
        }

        return "";
    }
}