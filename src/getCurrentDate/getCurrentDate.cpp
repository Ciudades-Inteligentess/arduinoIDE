#include <iostream>
#include <ctime>
#include <iomanip>

class GetCurrentDate{
    public:
        std::string getCurrentDate()
        {
            std::time_t now = std::time(0);
            std::tm *localTime = std::localtime(&now);

            std::ostringstream oss;
            oss << std::put_time(localTime, "%Y-%m-%dT%H:%M:%S.000Z");

            return oss.str();
        }
};