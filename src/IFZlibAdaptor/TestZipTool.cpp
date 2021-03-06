//
//   File name      : TestZipTool.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : IFZlibAdaptor
//
//   Create datetime: 2013-01-09 10:28:21
//

#ifdef _GTEST_

// Tested or implemented header
#include "IFZlibAdaptor/ZipTool.h"

// C system headers
#include <windows.h>

// C++ system headers
// ...

// Headers from other projects
#include <gtest/gtest.h>
#include "IFDataType/Tstring.h"
#include "IFMacros/BasicOperateMacro.h"
#include "IFOperator/PathHandler.h"
#include "IFDataType/DirectoryHolder.h"

// Headers of current project
// ...

static unsigned char s_kZipFileContent[] = {
    0x50, 0x4B, 0x03, 0x04, 0x14, 0x00, 0x00, 0x00, 0x08, 0x00, 0xBD, 0xBA, 0x29, 0x42, 0xD0, 0x82,
    0xA0, 0x4C, 0xB2, 0x00, 0x00, 0x00, 0x09, 0x01, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x74, 0x65,
    0x73, 0x74, 0x31, 0x2E, 0x74, 0x78, 0x74, 0x55, 0x8E, 0x4B, 0x6A, 0xC4, 0x30, 0x10, 0x44, 0xF7,
    0x81, 0xDC, 0xA1, 0x0E, 0x20, 0x72, 0x88, 0x10, 0x98, 0xE5, 0x9C, 0x41, 0x96, 0xDA, 0x56, 0x0F,
    0x76, 0xCB, 0xF4, 0xC7, 0xC6, 0xB7, 0x1F, 0x39, 0x64, 0x93, 0x6D, 0xF1, 0xAA, 0xEA, 0x7D, 0x87,
    0xE3, 0x6C, 0x24, 0xC8, 0x58, 0xBB, 0x2C, 0x70, 0xCD, 0x2C, 0xE8, 0x33, 0xF2, 0x14, 0x46, 0x86,
    0x2C, 0x15, 0x61, 0xA1, 0x7B, 0x76, 0xEE, 0x62, 0x09, 0x7B, 0xA8, 0x05, 0x0F, 0x92, 0xE5, 0xC8,
    0xCA, 0x79, 0x5A, 0x2F, 0x78, 0x23, 0x58, 0xDE, 0x08, 0xCF, 0xE9, 0x45, 0xC5, 0x13, 0xE8, 0x60,
    0x29, 0x77, 0x1B, 0x95, 0x8C, 0x17, 0x81, 0x77, 0x28, 0xD5, 0x28, 0x74, 0xB3, 0x1B, 0x42, 0x2A,
    0xE9, 0xB8, 0xB0, 0xBE, 0x86, 0x13, 0x7E, 0xC8, 0xF6, 0xEE, 0x6C, 0x5B, 0x02, 0x3B, 0xD8, 0x6E,
    0x88, 0x15, 0xCA, 0x4B, 0xF3, 0xFF, 0x51, 0x0D, 0xBF, 0xD2, 0xBD, 0xE6, 0x4D, 0xFB, 0x39, 0x3C,
    0x67, 0x58, 0x94, 0x86, 0x47, 0x3F, 0x48, 0x65, 0x23, 0xF1, 0xF4, 0xAB, 0x3C, 0x88, 0x5D, 0xFB,
    0xC1, 0x95, 0x20, 0x74, 0xE2, 0x11, 0x59, 0xAB, 0x61, 0xEE, 0xFA, 0xB7, 0x33, 0x87, 0x87, 0x0E,
    0x69, 0x2A, 0xA1, 0xEC, 0xD7, 0xD7, 0xE7, 0xC7, 0x1B, 0x50, 0x4B, 0x03, 0x04, 0x0A, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x4F, 0xBB, 0x29, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x53, 0x74, 0x61, 0x74, 0x75, 0x65, 0x20, 0x6F, 0x66,
    0x20, 0x4C, 0x69, 0x62, 0x65, 0x72, 0x74, 0x79, 0x2F, 0x50, 0x4B, 0x03, 0x04, 0x14, 0x00, 0x00,
    0x00, 0x08, 0x00, 0x29, 0xBB, 0x29, 0x42, 0xA9, 0x87, 0x61, 0xFC, 0x94, 0x00, 0x00, 0x00, 0xD3,
    0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x53, 0x74, 0x61, 0x74, 0x75, 0x65, 0x20, 0x6F, 0x66,
    0x20, 0x4C, 0x69, 0x62, 0x65, 0x72, 0x74, 0x79, 0x2F, 0x74, 0x65, 0x73, 0x74, 0x32, 0x2E, 0x74,
    0x78, 0x74, 0x2D, 0x8E, 0x3D, 0x0E, 0xC2, 0x30, 0x0C, 0x85, 0xF7, 0x4A, 0xBD, 0x83, 0xD9, 0x0B,
    0xD7, 0x40, 0xCC, 0xB0, 0x30, 0xA6, 0xE4, 0x95, 0x44, 0x8A, 0xE3, 0xCA, 0x4E, 0x41, 0xBD, 0x3D,
    0x0E, 0x30, 0xF9, 0xB3, 0xFC, 0x7E, 0x7C, 0xCE, 0x2F, 0x10, 0x83, 0x76, 0xD9, 0x94, 0x5A, 0x56,
    0xC4, 0x1F, 0xAE, 0x22, 0x3A, 0x8D, 0xC3, 0xBD, 0x73, 0xDA, 0x62, 0x2C, 0x7E, 0xE0, 0x60, 0x06,
    0xA3, 0x1D, 0x41, 0x6B, 0xAE, 0x4F, 0x6A, 0x42, 0xB3, 0x22, 0xB4, 0x04, 0x5A, 0x14, 0x70, 0xF9,
    0xCD, 0xF1, 0xAD, 0x68, 0x8F, 0xE4, 0x72, 0xC5, 0xB2, 0x19, 0x48, 0x96, 0x7F, 0x38, 0xC0, 0xDD,
    0x65, 0x49, 0x14, 0xA7, 0x71, 0xB8, 0xA2, 0x46, 0x72, 0xAF, 0x61, 0xEA, 0x83, 0x92, 0x30, 0x0A,
    0xCC, 0x7C, 0x03, 0xAF, 0xB0, 0x76, 0x6C, 0xE2, 0x7D, 0xB1, 0xD7, 0x70, 0x0F, 0xBF, 0x50, 0xC9,
    0x4B, 0x23, 0xDE, 0xA9, 0x04, 0x5E, 0x69, 0x86, 0xE5, 0x88, 0xAF, 0xF5, 0x29, 0x25, 0xA2, 0x52,
    0xF4, 0x9F, 0x0F, 0xE3, 0xF0, 0x01, 0x50, 0x4B, 0x01, 0x02, 0x1F, 0x00, 0x14, 0x00, 0x00, 0x00,
    0x08, 0x00, 0xBD, 0xBA, 0x29, 0x42, 0xD0, 0x82, 0xA0, 0x4C, 0xB2, 0x00, 0x00, 0x00, 0x09, 0x01,
    0x00, 0x00, 0x09, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x74, 0x65, 0x73, 0x74, 0x31, 0x2E, 0x74, 0x78, 0x74, 0x0A, 0x00, 0x20,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0xA9, 0x6D, 0xCE, 0x10, 0x7D, 0xEE, 0xCD,
    0x01, 0xA9, 0x6D, 0xCE, 0x10, 0x7D, 0xEE, 0xCD, 0x01, 0x6A, 0x01, 0x66, 0xBB, 0x7C, 0xEE, 0xCD,
    0x01, 0x50, 0x4B, 0x01, 0x02, 0x1F, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4F, 0xBB, 0x29,
    0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x00, 0x24,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xD9, 0x00, 0x00, 0x00, 0x53,
    0x74, 0x61, 0x74, 0x75, 0x65, 0x20, 0x6F, 0x66, 0x20, 0x4C, 0x69, 0x62, 0x65, 0x72, 0x74, 0x79,
    0x2F, 0x0A, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x21, 0x59, 0x08,
    0xB3, 0x7D, 0xEE, 0xCD, 0x01, 0x21, 0x59, 0x08, 0xB3, 0x7D, 0xEE, 0xCD, 0x01, 0x36, 0x3D, 0x39,
    0x8D, 0x7D, 0xEE, 0xCD, 0x01, 0x50, 0x4B, 0x01, 0x02, 0x1F, 0x00, 0x14, 0x00, 0x00, 0x00, 0x08,
    0x00, 0x29, 0xBB, 0x29, 0x42, 0xA9, 0x87, 0x61, 0xFC, 0x94, 0x00, 0x00, 0x00, 0xD3, 0x00, 0x00,
    0x00, 0x1B, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x09,
    0x01, 0x00, 0x00, 0x53, 0x74, 0x61, 0x74, 0x75, 0x65, 0x20, 0x6F, 0x66, 0x20, 0x4C, 0x69, 0x62,
    0x65, 0x72, 0x74, 0x79, 0x2F, 0x74, 0x65, 0x73, 0x74, 0x32, 0x2E, 0x74, 0x78, 0x74, 0x0A, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x16, 0x70, 0x6F, 0x88, 0x7D, 0xEE,
    0xCD, 0x01, 0x05, 0x49, 0x6F, 0x88, 0x7D, 0xEE, 0xCD, 0x01, 0x4B, 0x52, 0x34, 0xC1, 0x7C, 0xEE,
    0xCD, 0x01, 0x50, 0x4B, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x2C, 0x01,
    0x00, 0x00, 0xD6, 0x01, 0x00, 0x00, 0x00, 0x00
};

static const char s_kFile1[] = "But when a long train of abuses and usurpations, pursuing invariably the same Object, evinces a design to reduce them under absolute Despotism, it is their right, it is their duty, to throw off such Government, and to provide new Guards for their future security.\r\n";
static const char s_kFile2[] = "Give me your tired your poor,\r\nYour huddled masses yearning to breathe free,\r\nThe wretched refuse of your teeming shore.\r\nSend these, the homeless, tempest-tossed to me,\r\nI lift my lamp beside the golden door!\r\nand to provide new Guards for their future security.\r\n";

TEST(ZipTool, Unzip)
{
    int ret_code = 0;

    Tstring test_path(TEXT(".\\testtemp\\") );
    DirectoryHolder directory_holder(test_path);
    Tstring zip_file_path_name = test_path + (TEXT("testzip.zip") );
    Tstring target_path        = test_path + (TEXT("") );

    ASSERT_TRUE(PathHandler::CreatePathRecursive(test_path) );

    FILE *fzip = _tfopen(zip_file_path_name.c_str(), TEXT("wb") );
    ASSERT_TRUE(fzip != NULL);

    ret_code = fwrite(s_kZipFileContent, 1, sizeof(s_kZipFileContent), fzip);
    ASSERT_EQ(ret_code, sizeof(s_kZipFileContent) );

    MY_FCLOSE(fzip);

    int nRetCode = ZipTool::Unzip(zip_file_path_name, target_path);
    ASSERT_TRUE(nRetCode);

    char read_buffer[4096];
    FILE *fresult = _tfopen((test_path + TEXT("test1.txt") ).c_str(), TEXT("rb") );
    ASSERT_TRUE(fresult != NULL);

    ret_code = fread(read_buffer, 1, sizeof(read_buffer), fresult);
    ASSERT_EQ(ret_code, 265);

    MY_FCLOSE(fresult);

    ASSERT_EQ(0, memcmp(s_kFile1, read_buffer, ret_code) );


    fresult = _tfopen((test_path + TEXT("Statue_of_Liberty\\test2.txt") ).c_str(), TEXT("rb") );
    ASSERT_TRUE(fresult != NULL);

    ret_code = fread(read_buffer, 1, sizeof(read_buffer), fresult);
    ASSERT_EQ(ret_code, 211);

    MY_FCLOSE(fresult);

    ASSERT_EQ(0, memcmp(s_kFile2, read_buffer, ret_code) );
}

#endif
