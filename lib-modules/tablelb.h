#ifndef TABLELB_H
#define TABLELB_H

std::string query_platform_table(){
	#if __linux__
		return "gnulinux";
	#elif _WIN32
		return "windows";
	#else
		return "NULL";
	#endif
}

std::string base_path_tablelb = "test/";

class main_table_clss{
	public:
	void create_table(std::string create_table_parameter_1, std::string create_table_parameter_2){
		if(query_platform_table() == "gnulinux"){
			std::string create_table_command = "mkdir " + base_path_tablelb + create_table_parameter_1 + "/" + create_table_parameter_2;
			system(create_table_command.c_str());
		}else if(query_platform_table() == "windows"){
		//WINDOWS
		}else{std::cout << "unsupported platform";}
	}
	void del_table(std::string del_table_parameter_1, std::string del_table_parameter_2){
		if(query_platform_table() == "gnulinux"){
			std::string del_table_command = "rm -rf " + base_path_tablelb + del_table_parameter_1 + "/" + del_table_parameter_2;
			system(del_table_command.c_str());
		}else if(query_platform_table() == "windows"){
		//WINDOWS
		}else{std::cout << "unsupported platform";}
	}
};

#endif
