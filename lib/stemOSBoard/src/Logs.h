#ifndef Logs_h
#define Logs_h
#include "LittleFS.h"
#include "FS.h"
#include "esp_log.h"
#include "esp_err.h"

#define FORMAT_LITTLEFS_IF_FAILED true

class Logs {
    private:
        static fs::FS fs;
        static File root;
    public:
        Logs(void);
        void listDir(const char * dirname, uint8_t levels);
        void createDir(const char * path);
        void removeDir(const char * path);
        void readFile(const char * path);
        void writeToFile(const char * path, const char * message);
        void appendToFile(const char * path, const char * message);
        void renameFile(const char * path1, const char * path2);
        void deleteFile(const char * path);
        void findFile(const char * PathFile, uint8_t level=0);
        bool findDir(const char * path);
        // void timeReadFile();
        esp_err_t startFileSystem();
};

#endif