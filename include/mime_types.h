// include/mime_types.h
#ifndef MIME_TYPES_H
#define MIME_TYPES_H

typedef struct {
    const char* extension;
    const char* mime_type;
} MimeTypeMapping;

const char* get_content_type(const char* filename);

#endif