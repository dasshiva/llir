#ifndef __LEXER_HPP__
#define __LEXER_HPP__

#include <cstdint>
#include <fstream>
#include <vector>

#define CST_EOF ((char)11) 
struct LineAcct {
    uint32_t offset;
    uint32_t len;
    std::string line;

    LineAcct (uint32_t off, uint32_t len) : offset(off), len(len) {}
};

class Lexer;
class CharStream {
public:
    CharStream() = delete;
    CharStream(const char* file);
    char Next();
    uint32_t Line() { return line; }
    uint32_t Column() { return col; }
    void  PutBack();
    ~CharStream();
    bool IsOpen() { return open; }
    void DumpLines();

private:
    std::ifstream file;
    uint32_t line;
    bool open, eof;
    uint32_t col;
    std::vector<LineAcct> lines;
    char* fname;
    uint32_t offset;

    friend class Lexer;
};

enum TokenKind {
    TOKEN_EOF,
    TOKEN_NUMBER,
    TOKEN_IDENT
};

struct Token {
    TokenKind   tk;
    uint32_t    line;
    uint32_t    col;
    std::string str;
    int64_t     number;
};

class Lexer {
public:
    Lexer() = delete;
    Lexer(CharStream* cst);
    Token Next();
    Token Peek();
    void  Error(Token tk, const char* fmt, ...);
private:
    CharStream* cst;
    Token buffer;
    uint32_t flags;

};

#endif