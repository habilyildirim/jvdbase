#ifndef TABLELB_H
#define TABLELB_H

const std::string base_path_tablelb = BASE_PATH;

class main_table_clss {
	public:
	void create_table(std::string create_table_parameter_1, std::string create_table_parameter_2) {
		std::string create_table_path = base_path_tablelb + create_table_parameter_1 + "/" + create_table_parameter_2;
		if(!std::filesystem::create_directory(create_table_path)) {std::cout << "ERROR/TABLE_NOT_CREATE";}
	}
	
	void del_table(std::string del_table_parameter_1, std::string del_table_parameter_2) {
		std::string del_table_path = base_path_tablelb + del_table_parameter_1 + "/" + del_table_parameter_2;
		if(!std::filesystem::remove_all(del_table_path)) {std::cout << "ERROR/TABLE_NOT_REMOVE";}
	}
};

#endif
