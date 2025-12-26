#ifndef ARABRZYMEXCEPTION_HPP
#define ARABRZYMEXCEPTION_HPP

#include <exception>
#include <string>

class ArabRzymException : public std::exception {
  std::string msg_;

  public:
    ArabRzymException(const std::string &msg);
    ~ArabRzymException();
    const char *what() const noexcept;
};

#endif // ARABRZYMEXCEPTION_HPP