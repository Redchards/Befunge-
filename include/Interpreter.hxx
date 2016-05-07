#ifndef BEFUNGE_INTERPRETER_HXX
#define BEFUNGE_INTERPRETER_HXX

#include <algorithm>
#include <cctype>
#include <random>
#include <stack>
#include <string>

#include <Parser.hxx>
#include <ProgramPosition.hxx>

enum class Cardinality : uint8_t
{
	Right = 0,
	Left,
	Up,
	Down	
};

// Very simple wrapper for the stack, to meet the requirements of the Befunge program stack.
class ProgramStack : public std::stack<int64_t>
{
	using value_type = int64_t;
	using Base = std::stack<int64_t>;
	
	public:
	void pop() noexcept;
	value_type top() const noexcept;
	value_type pop_back() noexcept;	
};

class Interpreter
{
	public:
	Interpreter();	
	
	void interpret(std::string filePath);
	void step();
	void pause();
	
	private:
	
	void handleOperation(char op);
	void changeDirection(char op);
	void handleArithmetic(char op);
	void handleLogical(char op);
	void handleStackOperation(char op);
	int64_t askForInteger(const std::string& msg) const;
	char askForChar(const std::string& msg) const;
	
	void putCall();
	void getCall();
	
	ProgramPosition position_;
	Cardinality direction_;
	Parser parser_;
	ProgramStack programStack_;
	bool running_;
	
	bool parsingString_;
	
	constexpr static char stringDelimiter_ = '"';
	
	std::random_device rd_;
    std::mt19937 gen_;
	std::uniform_int_distribution<typename std::underlying_type<Cardinality>::type> rand_;
};

#endif // BEFUNGE_INTERPRETER_HXX