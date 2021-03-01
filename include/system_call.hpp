#pragma once

#include <iostream>
#include <pstream.h>
#include <string>

/**
 * @WARNING It's behaviour is NOT same as std::system
 *          Say you cd using filesystem::current_path, even then pstream runs the command as if in the build's directory
*/
namespace _dontuse{
    // https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
    inline std::pair<std::string,bool> exec_command(const char* command) {
        // run a process and create a streambuf that reads its stdout and stderr
        redi::ipstream proc(command,
        redi::pstreams::pstdout | redi::pstreams::pstderr);
        std::string line;
        std::string output;
        // read child's stdout
        while (std::getline(proc.out(), line)) {
            output.append(line);
            output.push_back('\n');
        }
        // if reading stdout stopped at EOF then reset the state
        if (proc.eof() && proc.fail()) {
            output.clear();
            proc.clear();
        }
        // read child's stderr
        while (std::getline(proc.err(), line)) {
            output.append(line);
            output.push_back('\n');
        }

        return std::make_pair(output, ! proc.fail());
    }
}
