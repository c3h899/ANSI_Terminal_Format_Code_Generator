#include<iostream>
#include "args_parser.hpp"
#include "ansi_term.hpp"

using namespace std;

struct menu_data{
	// Nothing of interest here.
};

void menu_function_0(int&, std::vector<std::string>::iterator begin,
		std::vector<std::string>::iterator end){
	int jj = 0;
	std::cout << "Hello from Menu Function 0" << std::endl;
	for(auto ii = begin; ii != end; ++ii){
		std::cout << "\t Arg (" << jj << "): " << *ii << std::endl;
		++jj;
	}
}

void menu_function_color_echo(int&, std::vector<std::string>::iterator begin,
		std::vector<std::string>::iterator end){
	std::cout << ctrm::tformat(*begin) << *end << ctrm::reset() << std::endl;
}

int main(int argc, char *argv[]){
	args_parser<int> main_menu(argc,argv);
	
	// Evaluate Success Case
	main_menu.add_key(0,menu_function_0,"-p");
	main_menu.add_key(2,menu_function_color_echo,"-c","Takes in a two arguments: a format code and the string to format.");
	
	if(argc > 1){
		main_menu.evaluate();
	} else {
		main_menu.auto_man();
	}

	return 0;
}