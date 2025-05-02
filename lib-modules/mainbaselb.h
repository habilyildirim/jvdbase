#ifndef MAINBASELB_H
#define MAINBASELB_H

std::string query_platform_main_base(){
	#ifdef __linux__
		return "gnulinux";
	#elif _WIN32
		return "windows";
	#else
		return "NULL";
	#endif
}

std::string base_path_mainbaselb = "test/";

class main_base_clss{
	public:
	void create_base(std::string create_base_parameter_1){
		if(query_platform_main_base() == "gnulinux"){
			std::string command_linux_make_dir = "mkdir " + base_path_mainbaselb + create_base_parameter_1;
			system(command_linux_make_dir.c_str());

			std::string base_main_file = base_path_mainbaselb + create_base_parameter_1 + "/" + create_base_parameter_1 + ".jvb";
			std::string command_linux_touch_main_file = "touch " + base_main_file;

			system(command_linux_touch_main_file.c_str());
			
			std::ofstream base_main_file_add_key(base_main_file, std::ios::app);
			base_main_file_add_key << "BASE-NAME=" << create_base_parameter_1 << "\n";
		}else if(query_platform_main_base() == "windows"){
		//WINDOWS
		}else{std::cout << "unsupported platform";}
	}	
	void del_base(std::string del_base_parameter_1){
		if(query_platform_main_base() == "gnulinux"){
			std::string command_linux_rm_base = "rm -rf " + base_path_mainbaselb + del_base_parameter_1;
			system(command_linux_rm_base.c_str());
		}else if(query_platform_main_base() == "windows"){
		//WINDOWS
		}else{std::cout << "unsupported platform";}
	}
};

#endif
