#include "lexer.hpp"
#include <cstring>
#include <cstdlib>
#include <iostream>

// EOF was chosen as 11 because it is a non printable character and most
// keyboards do not even provide an option for emitting this character
// Thus apart from maliciously designed programs, nothing should break the
// Lexer and CharStream methods

CharStream::CharStream(const char* file) : 
    line(1), col(1), eof(false), offset(0) {
    this->file.open(file);
    open = true;

    if (!this->file.is_open()) {
        open = false;
        return;
    }

    fname = static_cast<char*>(malloc(strlen(file) + 1));
    std::strcpy(fname, file);
    lines.push_back(LineAcct(offset, 0));
}

char CharStream::Next() {
    if (!open)
        return CST_EOF;

    char c = '\0';
    file.read(&c, 1);

    // If any failures occur, its time to bail immediately
    if (file.eof() || file.bad() || file.fail()) {
        eof = true;
        return CST_EOF;
    }

    if (c == '\n') {
        offset += 1;
        lines.push_back(LineAcct(offset, 0));

        line += 1;
        col = 1;
    }
    else {
        col += 1;
        lines[lines.size() - 1].len += 1;
        lines[lines.size() - 1].line += c;
        offset += 1;
    }

    return c;
}

void CharStream::PutBack() {
    if (!offset)
        return;
    
    file.unget();

    line -= 1;
    offset -= 1;
    if (col == 1) {
        lines.pop_back();
        col = lines[lines.size() - 1].len + 1;
    }
    else 
        col -= 1;
    
}

void CharStream::DumpLines() {
    for (auto it = lines.begin(); it != lines.end(); it++) {
        file.seekg(it->offset, std::ios_base::beg);
        std::cout << it->line << std::endl;
    }
}

CharStream::~CharStream() {
    std::free(fname);
    file.close();
    lines.clear();
}