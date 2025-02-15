// src/mime_types.c
#include "../include/mime_types.h"
#include <string.h>

static const MimeTypeMapping MIME_MAPPINGS[] = {
    {".txt", "text/plain"},
    {".html", "text/html"},
    {".css", "text/css"},
    {".js", "application/javascript"},
    {".json", "application/json"},
    {".png", "image/png"},
    {".jpg", "image/jpeg"},
    {".gif", "image/gif"},
    {".svg", "image/svg+xml"},
    {".ico", "image/x-icon"},
    {NULL, NULL}
};

const char* get_content_type(const char* filename) {
    const char* ext = strrchr(filename, '.');
    if (!ext) return "application/octet-stream";
    
    for (const MimeTypeMapping* mapping = MIME_MAPPINGS; mapping->extension; mapping++) {
        if (strcmp(ext, mapping->extension) == 0) {
            return mapping->mime_type;
        }
    }
    return "application/octet-stream";
}