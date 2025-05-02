#ifndef DATASTRLB_H
#define DATASTRLB_H

std::string query_platform_datastr(){
	#if __linux__
		return "gnulinux";
	#elif _WIN32
		return "windows";
	#else
		return "NULL";
	#endif
}

std::string base_path_datastrlb = "test/";

class main_datastr_clss{
	public:
	void create_datastr(std::string create_datastr_parameter_1,std::string create_datastr_parameter_2,std::string create_datastr_parameter_3,std::string create_datastr_parameter_4){
		if(query_platform_datastr() == "gnulinux"){
			std::string create_datastr_command = "touch " + create_datastr_parameter_1 + "/" + create_datastr_parameter_2 + "/" + create_datastr_parameter_3 + ".jvd";
			system(create_datastr_command.c_str());
			
			std::ofstream create_datastr_file_ou(create_datastr_parameter_1 + "/" + create_datastr_parameter_2 + "/" + create_datastr_parameter_3 + ".jvd", std::ios::app);
			create_datastr_file_ou << "TYPE=" << create_datastr_parameter_4 << "\n";
		}else if(query_platform_datastr() == "windows"){
		//WINDOWS
		}else{std::cout << "unsupported platform";}
	}
	void del_datastr(std::string del_datastr_parameter_1,std::string del_datastr_parameter_2,std::string del_datastr_parameter_3){
		if(query_platform_datastr() == "gnulinux"){
			std::string del_datastr_command = "rm " + del_datastr_parameter_1 + "/" + del_datastr_parameter_2 + "/" + del_datastr_parameter_3 + ".jvd";
			system(del_datastr_command.c_str());
		}else if(query_platform_datastr() == "windows"){
		//WINDOWS
		}else{std::cout << "unsupported platform";}
	}	
};

#endif
