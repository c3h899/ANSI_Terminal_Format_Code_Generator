#ifndef _ARGS_PARSER_H
#define _ARGS_PARSER_H

#include<map>
#include<string>
#include<vector>

template<typename T>
struct key_entry{
	unsigned int num_args = 0;
	void (*fp)(T&, std::vector<std::string>::iterator begin,
		std::vector<std::string>::iterator end) = NULL;
	std::string key = "";
	std::string usage = "";
};

template<typename T>
class args_parser {
	public:
		constexpr args_parser(int argc, char *argv[]);
		constexpr void add_key(unsigned int nargs,void (*fp)(T&, 
			std::vector<std::string>::iterator begin,
			std::vector<std::string>::iterator end),
			std::string key, std::string usage = "");
		constexpr void auto_man();
		void evaluate();
	private:
		unsigned int arg_count = 0;
		T parsed_data;
		std::map< std::string, key_entry<T> > arg_eval;
		std::vector<std::string> in_args;
	protected:
};
#endif