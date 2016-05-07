#include <Parser.hxx>

void Parser::parse(std::string filePath)
{
	size_t maxLineLength = 0;
	std::ifstream ifs{filePath};

	if(!ifs.is_open())
	{
		throw ParsingException("unable to open the file '" + filePath + "' !");
	}
	
	std::string buffer;
	while(std::getline(ifs, buffer))
	{
		if(buffer.size() < maxLineLength) {
			for(size_t i = buffer.size(); i < maxLineLength; ++i)
			{
				buffer.push_back(' ');
			}
		}
				else
		{
			maxLineLength = buffer.size();
		}
		grid_.push_back(std::move(buffer));
	}
}

std::string& Parser::operator[](size_t index)
{
	return grid_[index];
}

void Parser::displayGrid() const noexcept
{
	for(std::string line : grid_) {
		for(auto op : line) {
			std::cout << op;
		}
		std::cout << '\n';
	}
}

void Parser::displayGrid(ProgramPosition position) const noexcept
{
	uint64_t line_count = 0;
	uint64_t row_count = 0;
	for(std::string line : grid_) {
		for(auto op : line) {
			if(line_count == position.line && row_count == position.row)
			{
				std::cout << "\033[31m" << op << "\033[0m";
			}
			else
			{
				std::cout << op;
			}
			++row_count;
		}
		row_count = 0;
		++line_count;
		std::cout << '\n';
	}
	
	std::cout << "\n\n";
}

bool Parser::isEmpty() const noexcept
{
	return grid_.size() == 0;
}

size_t Parser::getGridWidth() const noexcept
{
	return !isEmpty() ? grid_.back().size() : 0;
}

size_t Parser::getGridHeight() const noexcept
{
	return !isEmpty() ? grid_.size() : 0;
}