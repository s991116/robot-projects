#include <string>
#include <boost/regex.hpp>
 
int main() {
 
        std::string text("a fat cat sat on the mat");
        boost::regex re("\\w+");
 
        boost::sregex_token_iterator i(text.begin(), text.end(), re, 0);
        boost::sregex_token_iterator end;
 
        for( ; i != end ; ++i ) {
                std::cout << *i << ' ';
        }
 
        std::cout << std::endl;
 
        return 0;
}
