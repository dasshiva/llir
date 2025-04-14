#include "libcmdline/libcmdline.h"
#include <iostream>
#include "lexer.hpp"
#include <stdlib.h>

// First declare the command line options accepted by the application
Option file = { "f", "file", "Specify the input file", "s", 
    nullptr, nullptr, 1, OPTION_REQUIRED | OPTION_DEFAULT};
// More options as necessary ...

// Now add all the options to this array by reference (pointers)
Option* options[] = {
    &file,
// Add more above here as more options are added but do not remove this NULL
    NULL
};

Program desc = { "LLVM IR Parser", "0.0.1", "Copyright(C) Shivashish Das 2025" };

int main(int argc, const char** argv) {
    ProgramDetails(&desc);

	int s = ParseOptions((Option**)&options, argc, argv);

	if (s != CMDLINE_SUCCESS) {
        std::cout << std::endl;
        GenerateHelp(argv[0], options, 1);
		return 1;
	}

    CharStream cst(file.Args->String);
    if (!cst.IsOpen()) {
        std::cout << "Failed to open " << file.Args->String << std::endl;
        return 1;
    }

    while (1) {
        char c = cst.Next();
        if (c == CST_EOF) break;
        //std::cout << c;
    }

    //std::cout << std::endl;
    cst.DumpLines();
	FreeOptionArgs((Option**)&options);
	return 0;
}

