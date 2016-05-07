#include <Interpreter.hxx>

void ProgramStack::pop() noexcept
{
	if(!empty())
	{
		Base::pop();
	}
}

auto ProgramStack::top() const noexcept
-> value_type
{
	if(!empty())
	{
		return Base::top();
	}
	return 0;
}

auto ProgramStack::pop_back() noexcept
-> value_type
{
	value_type tmp = 0;
	if(!empty())
	{
		tmp = Base::top();
		Base::pop();
	}
	return tmp;
}

Interpreter::Interpreter()
: position_{},
  direction_{Cardinality::Right},
  parser_{},
  programStack_{},
  running_{false},
  parsingString_{false},
  rd_{},
  gen_{rd_()},
  rand_{0, 3}
{}

void Interpreter::interpret(std::string filePath)
{
	parser_.parse(filePath);
	running_ = true;
	
	while(running_)
	{
		handleOperation(parser_[position_.line][position_.row]);
	}
}

void Interpreter::handleOperation(char op)
{
	if(parsingString_ && op != stringDelimiter_)
	{
		programStack_.push(op);
		step();
		return;
	}
	else if(std::isdigit(op))
	{
		programStack_.push(op - '0');
		step();
		return;
	}
	switch(op) 
	{
		case '<' :
		case '>' : 
		case 'v' : 
		case '^' :
		case '?' :
			changeDirection(op);
			break;
		
		case '+' :
		case '-' :
		case '*' :
		case '/' :
		case '%' :
			handleArithmetic(op);
			break;
			
		case '!' :
		case '`' :
			handleLogical(op);
			break;
			
		case '_' :
		case '|' :
		case ':' :
		case '\\' :	
		case '$' :
			handleStackOperation(op);
			break;
			
		case ',' :
			//std::cout << "Op is : " << (char)programStack_.top() << std::endl;
			//d = ;
			//std::cout << "Display : " << d << "\n";
			std::cout << static_cast<char>(programStack_.pop_back() % 127);
			break;
		case '.' :
			std::cout << programStack_.pop_back();
			break;
			
		case 'p' :
			putCall();
			break;
		case 'g' :
			getCall();
			break;
			
		case '#' :
			step();
			break;
		
		case '&' :
			programStack_.push(askForInteger("Enter an integer : "));
			break;
		case '~' :
			programStack_.push(askForChar("Enter a character : "));
			break;
		
		case stringDelimiter_ :
			parsingString_ = !parsingString_;
			break;
			
		case '@' :
			running_ = false;
			return;
	}
	
	step();
}

void Interpreter::step()
{
	switch(direction_)
	{
		case Cardinality::Right :
			++position_.row;
			if(position_.row == parser_.getGridWidth())
			{
				position_.row = 0;	
			}
			break;
		case Cardinality::Left :
			if(position_.row == 0)
			{
				position_.row = parser_.getGridWidth() - 1;
			}
			else
			{
				--position_.row;
			}
			break;
		case Cardinality::Up :
			if(position_.line == 0)
			{
				position_.line = parser_.getGridHeight() - 1;
			}
			else
			{
				--position_.line;
			}
			break;
		case Cardinality::Down :
			++position_.line;
			if(position_.line == parser_.getGridHeight())
			{
				position_.line = 0;
			}
			break;
	}
	
#	ifdef DEBUG
	parser_.displayGrid(position_);
#	endif
	
	/*std::cout << "Stack :" << std::endl;
	std::stack<int64_t> tmp{static_cast<std::stack<int64_t>>(programStack_)};
	while(!tmp.empty())
	{
		std::cout << tmp.top() << ", ";
		tmp.pop();
	}
	std::cout << "\n";
	std::cout << position_.line << " : " << position_.row << std::endl;*/
}

void Interpreter::changeDirection(char op)
{
	switch(op)
	{
		case '<' :
			direction_ = Cardinality::Left;
			break;
		case '>' :
			direction_ = Cardinality::Right;
			break;
		case 'v' :
			direction_ = Cardinality::Down;
			break;
		case '^' :
			direction_ = Cardinality::Up;
			break;
		case '?' :
			//std::cout << "Hello : " << rand_(gen_) << std::endl;
			direction_ = static_cast<Cardinality>(rand_(gen_));
			break;
	}
}

void Interpreter::handleArithmetic(char op)
{	
	int64_t rhs = programStack_.pop_back();
	int64_t lhs = programStack_.pop_back();
	
	switch(op)
	{
		case '+' :
			programStack_.push(lhs + rhs);
			break;
		case '-' :
			programStack_.push(lhs - rhs);
						//std::cout << lhs << " : " << rhs << "\n";
						//std::cout << programStack_.top() << '\n';
			break;
		case '*' :
			programStack_.push(lhs * rhs);
			break;
		case '/' :
			if(rhs == 0)
			{
				programStack_.push(0);
				break;
				//rhs = askForInteger(divisionByZeroMsg);
			}
			programStack_.push(static_cast<size_t>(lhs / rhs));
			break;
		case '%' :
			if(rhs == 0)
			{
				programStack_.push(0);
				break;
				//rhs = askForInteger(divisionByZeroMsg);
			}
			programStack_.push(lhs % rhs);
			break;
	}
}

void Interpreter::handleLogical(char op)
{
	//std::cout << "Logical" << std::endl;
	if(programStack_.empty())
	{
		programStack_.push(0);
		return;
	}
	
	int64_t rhs = programStack_.pop_back();
	int64_t lhs = 0;
	
	switch(op)
	{
		case '!' :
			programStack_.push((rhs == 0 ? 1 : 0));
			break;
		case '`' :
			lhs = programStack_.pop_back();
			programStack_.push(lhs > rhs);
			break;
	}
}

void Interpreter::handleStackOperation(char op)
{
	int64_t lhs = 0;
	int64_t rhs = 0;
		
	switch(op)
	{
		case '_' :
			lhs = programStack_.pop_back();
			if(lhs == 0)
			{
				changeDirection('>');
			}
			else
			{
				changeDirection('<');
			}
			break;
		case '|' :
			lhs = programStack_.pop_back();
			if(lhs == 0)
			{
				changeDirection('v');
			}
			else
			{
				changeDirection('^');
			}
			break;
		case ':' :
			programStack_.push(programStack_.top());
			break;
		case '\\' :	
			rhs = programStack_.pop_back();
			lhs = programStack_.pop_back();
			programStack_.push(rhs);
			programStack_.push(lhs);
			break;
		case '$' :
			programStack_.pop();
	}
}

int64_t Interpreter::askForInteger(const std::string& msg) const
{
	std::string tmpBuffer;
	std::cout << msg;
	
	bool isNumber = false;
	
	while(!isNumber)
	{
		std::cin >> tmpBuffer;
		
		isNumber = !tmpBuffer.empty()
		&& (std::find_if(tmpBuffer.begin(), tmpBuffer.end(),
						[](char c){ return !isdigit(c); }) == tmpBuffer.end());
	}
	/*do {
		std::cin >> tmpBuffer;
	} while((tmpBuffer.size() > 1 && !std::isdigit(tmpBuffer[0]))
		 || (tmpBuffer.size() > 2 && tmpBuffer[0] != '-' && !std::isdigit(tmpBuffer[1])));
	
	int64_t result = 0;
	if(tmpBuffer.size() == 2)
	{
		result = -(tmpBuffer[1] - '0');
	}
	else
	{
		result = tmpBuffer[0] - '0';
	}*/
	
	return std::stoi(tmpBuffer);
}

char Interpreter::askForChar(const std::string& msg) const
{
	std::string tmpBuffer;
	std::cout << msg;
	do {
		std::cin >> tmpBuffer;
	} while(tmpBuffer.size() > 1 || !std::isalpha(tmpBuffer[0]));
	
	return tmpBuffer[0];	
}

void Interpreter::putCall()
{
	int64_t sty = programStack_.pop_back();
	int64_t stx = programStack_.pop_back();
	
	uint64_t line = sty < 0 ? 0 : sty;
	uint64_t row = stx < 0 ? 0 : stx;
	
	char value = static_cast<char>(programStack_.pop_back() % 127);
	//std::cout << line << " : " << row << std::endl;
	if((stx < 0 || row > parser_.getGridWidth())
	|| (sty < 0 || line > parser_.getGridHeight()))
	{
		std::cout << "Out of bound !!!" << std::endl;
		return;
	}
	
	parser_[line][row] = value;
}

void Interpreter::getCall()
{
	int64_t sty = programStack_.pop_back();
	int64_t stx = programStack_.pop_back();
	
	uint64_t line = sty < 0 ? 0 : sty;
	uint64_t row = stx < 0 ? 0 : stx;
	
	if((stx < 0 || row > parser_.getGridWidth())
	|| (sty < 0 || line > parser_.getGridHeight()))
	{
		programStack_.push(0);
	}
	else
	{
		programStack_.push(parser_[line][row]);
	}
}