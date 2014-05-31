#ifndef HGEXCEPTION_H
#define HGEXCEPTION_H
#include <string>
#include <exception>

class HGException : public std::exception {
    private:
        std::string msg;
    public:
        explicit HGException (const std::string & msg) : msg ("[Mesh Exception]" + msg) {}
        explicit HGException(const char* message): msg(message) {}
        virtual ~HGException () throw (){}
        inline const std::string & getMessage () const { return msg; }
        virtual const char* what() const throw() {
            return msg.c_str();
        }
};

#endif
