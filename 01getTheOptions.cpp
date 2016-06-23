/*************************************************************************
	> File Name: 01getTheOptions.cpp
	> Author: Tony
	> Mail: 445241843@qq.com 
	> Created Time: Thu 23 Jun 2016 11:29:27 AM CST
 ************************************************************************/
#include<boost/program_options.hpp>				//libboost_program_options     library
#include<boost/program_options/errors.hpp>
#include<iostream>
namespace opt = boost::program_options;
int main(int argc, char* argv[])
{
	opt::options_description desc("All option:");
	desc.add_options()
		("apple, a", opt::value<int>()->default_value(10), "apples that you have")
		("orange, o", opt::value<int>(), "oranges that you have")
		("name", opt::value<int>(), "your name")
		("help", "produce your message");
	opt::variables_map vm;
	opt::store(opt::parse_command_line(argc, argv, desc), vm);
	opt::notify(vm);
	if(vm.count("help")){
		std::cout << desc << "\n";
		return 1;
	}
	try{
		opt::store(opt::parse_config_file<char>("apples_oranges.cfg", desc), vm);
	}catch(const opt::reading_file & e){
		std::cout << "Failed to open file 'apples_oranges.cfg':" << e.what();
	}
	opt::notify(vm);
	if(vm.count("name")){
		std::cout << "Hi,"  << vm["name"].as<std::string>() << "\n";
	}
	std::cout << "Fruits count: " << vm["apples"].as<int>() + vm["oranges"].as<int>() << std::endl;
	return 0;
}

