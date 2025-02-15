## Overview

This project is a lightweight and efficient implementation of an HTTP server written in C. It demonstrates fundamental web server concepts while maintaining high performance and reliability. The server is designed to handle multiple file types and serve both static and dynamic content efficiently.

## Features

- **HTTP/1.1 Protocol Support**: Efficient request handling and robust error management.
- **File Handling**: Support for multiple file types including HTML, CSS, JavaScript, images, and videos.
- **Performance**: Optimized for speed and resource efficiency.
- **Error Handling**: Robust error handling implementation for various scenarios including 404 Not Found and 500 Internal Server Error responses.

## Project Structure

```
include/
    http_handler.h
    mime_types.h
    server.h
Makefile
src/
    http_handler.c
    main.c
    mime_types.c
    server.c
wwwroot/
    about.html
    error_pages/
        404.html
        500.html
        501.html
    img/
        sample.jpg
    index.html
    video/
        sample.mp4
```

## Getting Started

### Prerequisites

- GCC (GNU Compiler Collection)
- Windows with Winsock2 library

### Building the Project

1. Clone the repository:
    ```sh
    git clone <repository-url>
    cd <repository-directory>
    ```

2. Build the project using the provided Makefile:
    ```sh
    make
    ```

### Running the Server

1. Run the server executable:
    ```sh
    ./bin/webserver [port]
    ```
    If no port is specified, the server will default to port 9090.

2. Open a web browser and navigate to `http://localhost:<port>` to see the server in action.

### Cleaning the Build

1. To clean the build directory and remove all compiled files, run:

    ```sh
    make clean
    ```

### Project Files

- **Source Files**:
  - main.c: Entry point of the server application.
  - server.c: Server initialization, starting, and cleanup functions.
  - http_handler.c: HTTP request handling and response generation.
  - mime_types.c: MIME type detection based on file extensions.

- **Header Files**:
  - server.h: Server-related definitions and function declarations.
  - http_handler.h: HTTP handler-related definitions and function declarations.
  - mime_types.h: MIME type-related definitions and function declarations.

- **Web Root**:
  - index.html: Main page served by the server.
  - about.html: About page.
  - 404.html: Custom 404 error page.
  - 500.html: Custom 500 error page.
  - 501.html: Custom 501 error page.
  - sample.jpg: Sample image file.
  - sample.mp4: Sample video file.

## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgments

- This project uses the Winsock2 library for network communication on Windows.
- The HTML and CSS files in the wwwroot directory are used for demonstration purposes.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any improvements or bug fixes.