/////////////////////////////////////////////////////////////////////////////
// Copyright 2004 NVIDIA Corporation.  All Rights Reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
// 
// * Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the distribution.
// * Neither the name of NVIDIA nor the names of its contributors
//   may be used to endorse or promote products derived from this software
//   without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// (This is the Modified BSD License)
/////////////////////////////////////////////////////////////////////////////

// Argument Parsing
//
// The parse function takes a list of options and variables or functions
// for storing option values and return <0 on failure:
//
//    ArgParse ap(argc, argv);
//
//    if (ap.parse (
//            "", parse_objects,
//            "-camera %f %f %f", &camera[0], &camera[1], &camera[2],
//            "-lookat %f %f %f", &lx, &ly, &lz,
//            "-oversampling %d", &oversampling,
//            "-passes %d", &passes,
//            "-lens %f %f %f", &aperture, &focalDistance, &focalLength,
//            "-motion %f %f", &frameopen, &frameclose,
//            "-motion_camera %f %f %f", &vcx, &vcy, &vcz,
//            "-motion_lookat %f %f %f", &vlx, &vly, &vlz,
//            "-format %d %d %f", &width, &height, &aspect,
//            "-flag", &flag,
//            NULL) < 0) {
// 
//        usage ();
//        return EXIT_FAILURE;
//    }
//
// The available argument types are:
//     %d - 32bit integer
//     %f - 32bit float
//     %F - 64bit float (double)
//     %s - char* (assumed allocated before calling ArgParse::parse())
//     %S - char* (allocated automatically in ArgParse::parse())
//     %! - bool flag
//     %* - (argc,argv) sublist with callback
//
// Notes:
//   - If an option doesn't have any arguments, a flag argument is assumed.
//   - Flags are initialized to false.  No other variables are initialized.
//   - The empty string, "", is used as a global sublist (ie. "%*").
//   - Sublist functions are all of the form "int func(int argc, char **argv)".
//   - If a sublist function returns -1, parse() will terminate early.
//


#ifndef ARGPARSE_H
#define ARGPARSE_H

#include <vector>


class ArgOption;

class ArgParse {

 public:
    
    ArgParse(int argc, char **argv);
    ~ArgParse();
    
    int parse(const char *format, ...); // parse the command line  <0 on error
    int found(char *option);            // number of times option was parsed

    char *error_message() { return message; };

 private:

    int argc;                           // a copy of the command line argc
    char **argv;                        // a copy of the command line argv
    char message[4096];                 // error message
    ArgOption *global;                  // option for extra cmd line arguments
    
    std::vector<ArgOption *> option;

    ArgOption *find_option(const char *name);
    int invoke_all_sublist_callbacks();
    int parse_command_line();
    void report_error(const char *format, ...);
    
};


#endif // ARGPARSE_H
