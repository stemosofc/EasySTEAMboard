#ifndef Logs_h
#define Logs_h
#include "LittleFS.h"
#include "FS.h"
#include "esp_log.h"
#include "esp_err.h"

#define FORMAT_LITTLEFS_IF_FAILED true

class Logs {
    private:
        fs::FS fs = LittleFS;
    public:
        Logs(void);
        void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
        void createDir(fs::FS &fs, const char * path);
        void removeDir(fs::FS &fs, const char * path);
        void readFile(fs::FS &fs, const char * path);
        void writeToFile(fs::FS &fs, const char * path, const char * message);
        void appendToFile(fs::FS &fs, const char * path, const char * message);
        void renameFile(fs::FS &fs, const char * path1, const char * path2);
        void deleteFile(fs::FS &fs, const char * path);
        void findFile(const char * path);
        void findDir(const char * path);
        // void timeReadFile();
        esp_err_t startFileSystem();
};

#endif