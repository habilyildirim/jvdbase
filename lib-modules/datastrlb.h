#ifndef DATASTRLB_H
#define DATASTRLB_H

const std::string base_path_datastrlb = BASE_PATH;

class main_datastr_clss{
	public:
	void create_datastr(std::string create_datastr_parameter_1,std::string create_datastr_parameter_2,std::string create_datastr_parameter_3,std::string create_datastr_parameter_4){
		std::string create_datastr_path = create_datastr_parameter_1 + "/" + create_datastr_parameter_2 + "/" + create_datastr_parameter_3 + ".jvd";
		std::ofstream datastr_file(create_datastr_path, std::ios::app);
		if(datastr_file.is_open()){datastr_file << "TYPE=" << create_datastr_parameter_4 << "\n";}
		else{std::cout << "ERROR/DATASTR_FILE_NOT_CREATED";}
	}
	void del_datastr(std::string del_datastr_parameter_1,std::string del_datastr_parameter_2,std::string del_datastr_parameter_3){
		std::string del_datastr_path_cbefore = del_datastr_parameter_1 + "/" + del_datastr_parameter_2 + "/" + del_datastr_parameter_3 + ".jvd";
		const char* del_datastr_path = del_datastr_path_cbefore.c_str();
		if(remove(del_datastr_path) == 0){}
		else{std::cout << "ERROR/DATASTR_FILE_NOT_REMOVED";}
	}	
};

#endif
