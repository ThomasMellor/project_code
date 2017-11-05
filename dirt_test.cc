#include <sys/stat.h>
#include <iostream>

int main() {
struct stat sb;
        std::string path; 
        std::cin >> path;
        std::cout << path; 
if (stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))
{
        std::cout << "is directory" << std::endl;
};
};
