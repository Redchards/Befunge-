#ifndef BEFUNGE_PARSER_HXX
#define BEFUNGE_PARSER_HXX

#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <ProgramPosition.hxx>

class ParsingException : public std::exception
{
	public:
	ParsingException(const std::string& msg) : msg_{std::string{"Error during parsing : "} + msg}
	{}
	ParsingException(std::string&& msg) : msg_{std::string{"Error during parsing : "} + std::move(msg)}
	{}
	
	const char* what() const noexcept override
	{
		return msg_.c_str();
	}
	
	private:
	const std::string msg_;	
};

class Parser
{
	public:
	Parser() = default;
	
	void parse(std::string filePath);
	std::string& operator[](size_t index);
	void displayGrid() const noexcept;
	void displayGrid(ProgramPosition position) const noexcept;
	bool isEmpty() const noexcept;
	
	size_t getGridWidth() const noexcept;
	size_t getGridHeight() const noexcept;
	
	private:
	std::vector<std::string> grid_;	
};

#endif // BEFUNGE_PARSER_HXX