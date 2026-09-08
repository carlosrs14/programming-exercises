#include <stdio.h>

typedef enum {
    HTTP_OK = 200,
    HTTP_BAD_REQUEST = 400,
    HTTP_UNAUTHORIZED = 401,
    HTTP_FORBIDDEN = 403,
    HTTP_NOT_FOUND = 404,
    HTTP_INTERNAL_ERROR = 500
} HttpStatusCode;

const char* http_status_message(HttpStatusCode code) {
    switch (code) {
        case HTTP_OK:
            return "OK - Request succeeded";
        case HTTP_BAD_REQUEST:
            return "Bad Request - Malformed syntax";
        case HTTP_UNAUTHORIZED:
            return "Unauthorized - Authentication required";
        case HTTP_FORBIDDEN:
            return "Forbidden - Server refuses authorization";
        case HTTP_NOT_FOUND:
            return "Not Found - Resource not located";
        case HTTP_INTERNAL_ERROR:
            return "Internal Server Error - Unexpected condition";
        default:
            return "Unknown Status Code";
    }
}

int main() {
    int code_input;

    printf("enter http status code (200, 400, 401, 403, 404, 500): ");
    if (scanf("%d", &code_input) != 1) {
        perror("invalid input");
        return 1;
    }

    HttpStatusCode code = (HttpStatusCode)code_input;
    printf("Status %d: %s\n", code_input, http_status_message(code));

    return 0;
}