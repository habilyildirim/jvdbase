#ifndef MAINBASELB_H
#define MAINBASELB_H

const std::string base_path_mainbaselb = BASE_PATH;

class main_base_clss{
	public:
	void create_base(std::string create_base_parameter_1){
		std::string create_folder_path = base_path_mainbaselb + create_base_parameter_1;
		std::string create_file_path = base_path_mainbaselb + create_base_parameter_1 + "/" + create_base_parameter_1 + ".jvb";
		if(std::filesystem::create_directory(create_folder_path)){
			std::ofstream base_main_file_add_key(create_file_path, std::ios::app);
			if(base_main_file_add_key.is_open()){
				base_main_file_add_key << "BASE-NAME=" << create_base_parameter_1 << "\n";
				base_main_file_add_key.close();
			}else{std::cout << "ERROR/BASE_FILE_NOT_CREATED";}				
		}else{std::cout << "ERROR/BASE_NOT_CREATED";}
	}	
	void del_base(std::string del_base_parameter_1){
		std::string remove_folder_path = base_path_mainbaselb + del_base_parameter_1;
		if(!std::filesystem::remove_all(remove_folder_path)){std::cout << "BASE_NOT_REMOVE";}
	}
};

class backup_clss{
	public:
	void backup_base(std::string backup_base_parameter_1){
		if(ssystem_control() == 1){
			std::string backup_base_path_and_command = "cp -r " + base_path_mainbaselb + backup_base_parameter_1 + " /opt/";
			system(backup_base_path_and_command.c_str());
		}else if(ssystem_control() == 0){
			std::string backup_base_path_and_command = "xcopy /E /I /Y \"" + base_path_mainbaselb + backup_base_parameter_1 + "\" \"C:\\\"";
			system(backup_base_path_and_command.c_str());
		}else{std::cout << "ERROR/SUPPORT ONLY LINUX & WINDOWS";}
	}
	void backup_load(std::string backup_load_parameter_1){
		if(ssystem_control() == 1){
			std::string backup_load_command = "cp -r /opt/" + backup_load_parameter_1 + " " + base_path_mainbaselb;
			system(backup_load_command.c_str());
		}else if(ssystem_control() == 0){
			std::string backup_load_command = "xcopy /E /I /Y \"C:\\" + backup_load_parameter_1 + "\" \"" + base_path_mainbaselb + "\\\"";
			system(backup_load_command.c_str());
		}else{std::cout << "ERROR/SUPPORT ONLY LINUX & WINDOWS";}
	}
};

#endif
