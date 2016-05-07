#include <iostream>

#include <Interpreter.hxx>
#include <Parser.hxx>

int main(int argc, char* argv[]) try
{
	
	if(argc == 2)
	{	
		Interpreter nice;
		nice.interpret(argv[1]);
	}
	return 0;
}
catch(ParsingException& e)
{
	std::cout << e.what() << std::endl;
}