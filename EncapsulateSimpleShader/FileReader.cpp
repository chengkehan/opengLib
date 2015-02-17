//
//  FileReader.cpp
//  Base_on_cg
//
//  Created by jimCheng on 15/2/14.
//  Copyright (c) 2015年 JimCheng. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "FileReader.h"
#include "cgUtil.h"

/* PUBLIC */

FileReader::FileReader() :
    m_content(nullptr)
{
    // Do nothing
}

FileReader::~FileReader()
{
    releaseMemory();
}

bool FileReader::read(const char *path)
{
    if (path == nullptr)
    {
        cgPrintThenExit("FileReader::read input parameter is null");
        return false;
    }
    
    FILE* file = fopen(path, "r");
    if (file == nullptr)
    {
        cgPrintThenExit("File is not exists. %s.\n", path);
        return false;
    }
    
    int seekResult = fseek(file, 0, SEEK_END);
    if (seekResult != 0)
    {
        cgPrintThenExit("Seek to end of file error. %s\n", path);
        return false;
    }
    
    long fileSize = ftell(file);
    if (fileSize == -1L)
    {
        cgPrintThenExit("Get size of file fail. %s\n", path);
        return false;
    }
    
    rewind(file);
    
    releaseMemory();
    m_content = (char*)malloc(sizeof(char) * fileSize);
    if (m_content == nullptr)
    {
        cgPrintThenExit("Allocate memory fail for reading file. %s\n", path);
        return false;
    }
    
    size_t readFileResult = fread(m_content, 1, fileSize, file);
    if (readFileResult != fileSize)
    {
        releaseMemory();
        cgPrintThenExit("Read file fail. %s\n", path);
        return false;
    }
    
    fclose(file);
    
    return true;
}

const char* FileReader::content()
{
    return m_content;
}

/* PRIVATE */

void FileReader::releaseMemory()
{
    delete m_content;
    m_content = nullptr;
}