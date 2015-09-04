#ifndef _GAMEERROR_H
#define _GAMEERROR_H
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <exception>

namespace gameErrorNS
{
	const int FATAL_ERROR = -1;
	const int WARNING = 1;
}

class GameError : public std::exception
{
private:
	int m_errorCode;
	std::string m_message;

public:
	GameError() throw() : m_errorCode(gameErrorNS::FATAL_ERROR),
		m_message("Undefined Error in game.") {}

	//copy constructor
	GameError(const GameError& e) throw() : std::exception(e), m_errorCode(e.m_errorCode),
		m_message(e.m_message) {}

	GameError(int code, const std::string &s) throw() : m_errorCode(code), m_message(s) {}

	GameError& operator= (const GameError& rhs) throw()
	{
		std::exception::operator=(rhs);
		this->m_errorCode = rhs.m_errorCode;
		this->m_message = rhs.m_message;
	}

	virtual ~GameError() throw() {};
	virtual const char* what() const throw() { return this->getMessage(); }
	const char* getMessage() const throw() { return m_message.c_str(); }
	int getErrorCode() const throw() { return m_errorCode; }
};
#endif