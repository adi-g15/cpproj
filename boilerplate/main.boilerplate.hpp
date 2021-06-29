#pragma once

constexpr auto MAIN_CPP_BOILERPLATE = 
                    "/*\n"
                    "    ${{CPPROJ_PROJECT_NAME}}\n"
                    "    ${{CPPROJ_PROJECT_DESC}}\n"
                    "*/\n"
                    "\n"
                    "#include <iostream>\n"
                    "\n"
                    "int main() {\n"
                    "    std::cout << \"Namaste!\\n\";\n"
                    "}\n"
                    "\n";

