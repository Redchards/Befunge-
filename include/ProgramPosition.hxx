#ifndef BEFUNGE_PROGRAM_POSITION_HXX
#define BEFUNGE_PROGRAM_POSITION_HXX
	
struct ProgramPosition
{
	ProgramPosition() : line{0}, row{0}
	{}
	
	size_t line;
	size_t row;
};

#endif // BEFUNGE_PROGRAM_POSITION_HXX