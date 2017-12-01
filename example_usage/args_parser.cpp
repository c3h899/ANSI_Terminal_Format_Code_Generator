#include<iostream>
#include "args_parser.hpp"

//#define DEBUG_CONSTRUCTOR
//#define DEBUG_ADD_KEY
//#define DEBUG_EVALUATE

template<typename T>
constexpr args_parser<T>::args_parser(int argc, char *argv[]){
	arg_count = argc;
#ifdef DEBUG_CONSTRUCTOR
	std::cout << "Input Arguement Count: " << arg_count << std::endl;
#endif
	//in_args.reserve(argc);
	for(int ii = 0; ii < argc; ++ii){
		in_args.push_back(argv[ii]);
		//in_args[ii] = argv[ii];
#ifdef DEBUG_CONSTRUCTOR
	std::cout << "Argument (" << ii << "): " << argv[ii] << std::endl;
#endif
	}
#ifdef DEBUG_CONSTRUCTOR
	std::cout << "" << std::endl;
#endif
}

template<typename T>
constexpr void args_parser<T>::add_key(unsigned int nargs, void (*fp)(T&, std::vector<std::string>::iterator begin,
		std::vector<std::string>::iterator end), std::string key, std::string usage){
	if(fp != NULL){
		key_entry<T> value;
		value.num_args = nargs;
		value.fp = fp;
		value.usage = usage;
		arg_eval.insert( std::pair<std::string, key_entry<T> >(key,value));
#ifdef DEBUG_ADD_KEY
	std::cout << "Adding Function to Table. Accessible as '" << key << "'" << std::endl;
	std::cout << "" << std::endl;
#endif
	} else {
		std::cerr << "ERROR: Invalid Menu Function (null pointer)" << std::endl;
	}
}

template<typename T>
constexpr void args_parser<T>::auto_man(){
	std::cout << "The following arguements are supported:" << std::endl;
	for(auto ii = arg_eval.begin(); ii != arg_eval.end(); ii++){
		std::cout << "" << std::endl;
		std::cout << ii->first << " : " << ii->second.usage << std::endl;
	}
}

template<typename T>
void args_parser<T>::evaluate(){
#ifdef DEBUG_EVALUATE
	std::cout << "Number of supported commands: " << arg_eval.size() << "; number of arguments: " << arg_count << std::endl;
	std::cout << "" << std::endl;
#endif
	if( (arg_eval.size() > 0) && (arg_count > 1) ){
		for(unsigned int ii = 1; ii < arg_count; ++ii){
#ifdef DEBUG_EVALUATE
	std::cout << "Argument (" << ii << "): " << in_args[ii] << std::endl;
#endif
			auto item = arg_eval.find(in_args[ii]);
			if(item != arg_eval.cend()){ // std::map returns out of bound result if no match
#ifdef DEBUG_EVALUATE
	std::cout << "Command Identified: '" << in_args[ii] << "'" << std::endl;
	std::cout << "Present argument (" << ii << "); Number of expected arguments: " << (item->second.num_args) << std::endl;
#endif
				if((item->second.num_args + ii) < arg_count){
#ifdef DEBUG_EVALUATE
	std::cout << "\tFunction shall be evaluated." << std::endl;
#endif
					auto begin = in_args.begin() + ii + 1;
					auto end = in_args.begin() + ii + item->second.num_args;
					item->second.fp(parsed_data, begin, end);
					ii += item->second.num_args; // Increment over expected argument parameters
				} else {
#ifdef DEBUG_EVALUATE
	std::cout << "Function shall NOT be evaluated." << std::endl;
#endif
					std::cerr << "ERROR: Insufficient arguments provided to: " << in_args[ii] << std::endl;
					if(item->second.usage != ""){
						std::cout << "Usage of '" << in_args[ii] << "': " << item->second.usage << std::endl;
					}
				}
			} else {
				std::cerr << "ERROR: Invalid Argument '" << in_args[ii] << "'." << std::endl;
			}
#ifdef DEBUG_EVALUATE
	std::cout << "" << std::endl;
#endif		
		}
	} else {
		std::cerr << "WARNING: Nothing to be done." << std::endl;
	}
}

template class args_parser<int>;