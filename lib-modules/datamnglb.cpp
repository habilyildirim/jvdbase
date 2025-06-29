#ifndef DATAMNG_H
#define DATAMNG_H

const std::string base_path_datamng = BASE_PATH;
std::string command;

class main_datamng_clss {
	public:
	void insert_data(std::string insert_data_parameter_1_base_name,std::string insert_data_parameter_2_table_name,std::string insert_data_parameter_3_datastr_name,std::string insert_data_parameter_4_data_name) {
		std::string file_path = base_path_datamng + insert_data_parameter_1_base_name + "/" + insert_data_parameter_2_table_name + "/" + insert_data_parameter_3_datastr_name + ".jvd";
		std::ofstream insert_file(file_path, std::ios::app);
		if(insert_file.is_open()) {insert_file << insert_data_parameter_4_data_name << "\n";}
		else {std::cout << "ERROR/";}
	}
	
	void delete_data(std::string del_data_parameter_1_base_name,std::string del_data_parameter_2_table_name,std::string del_data_parameter_3_datastr_name,std::string del_data_parameter_4_condition,std::string del_data_parameter_5_parameter) {
		//TEMP FILE
		std::string status_temp_file = base_path_datamng + del_data_parameter_1_base_name + "/" + del_data_parameter_2_table_name + "/" + "temp.jtmp";
		std::ofstream tempfile(status_temp_file);
		if(tempfile.is_open()) {
			std::string main_file_path = base_path_datamng + del_data_parameter_1_base_name + "/" + del_data_parameter_2_table_name + "/" + del_data_parameter_3_datastr_name + ".jvd";
			std::ifstream main_file(main_file_path);
			//TEMP FILE
			std::string status_temp_file = base_path_datamng + del_data_parameter_1_base_name + "/" + del_data_parameter_2_table_name + "/" + "temp.jtmp";
			std::ofstream tempfile(status_temp_file);
			if(tempfile.is_open()) {
				std::string data_line_datamng;
				if(del_data_parameter_4_condition == "INDEX") {
					int line_counter_datamng = 1;
					int target = std::stoi(del_data_parameter_5_parameter) + 2;
					while(std::getline(main_file,data_line_datamng)) {
						if(line_counter_datamng != target) {tempfile << data_line_datamng << "\n";}
						line_counter_datamng++;
					}
					std::remove(main_file_path.c_str());
					std::rename(status_temp_file.c_str(), main_file_path.c_str());
				} else if(del_data_parameter_4_condition == "MATCH") {
					while(std::getline(main_file,data_line_datamng)) {if(del_data_parameter_5_parameter != data_line_datamng){tempfile << data_line_datamng << "\n";}}
					std::remove(main_file_path.c_str());
					std::rename(status_temp_file.c_str(), main_file_path.c_str());
				} else if(del_data_parameter_4_condition == "FIRST-MATCH") {
					bool controller = false;
					while(std::getline(main_file,data_line_datamng)) {
						if(controller == false && del_data_parameter_5_parameter == data_line_datamng) {
							controller = true;
							continue;
						} tempfile << data_line_datamng << "\n";
					}
					std::remove(main_file_path.c_str());
					std::rename(status_temp_file.c_str(), main_file_path.c_str());
				} else {(void)0;}
			}
		} else {std::cout << "ERROR/TEMP_FILE_NOT_CREATED";}
	} 
};

class selectprc_datamng_clss {
	public:
	std::string select_data(std::string select_data_parameter_1_base_name,std::string select_data_parameter_2_table_name,std::string select_data_parameter_3_datastr_name,std::string select_data_parameter_4_condition,std::string select_data_parameter_5_parameter) {
		std::string file_path = base_path_datamng + select_data_parameter_1_base_name + "/" + select_data_parameter_2_table_name + "/" + select_data_parameter_3_datastr_name + ".jvd";
		std::fstream file(file_path);
		std::string file_line;
		if(select_data_parameter_4_condition == "INDEX") {
			int counter = 1;
			int target = std::stoi(select_data_parameter_5_parameter) + 2;
			while(std::getline(file,file_line)){
				if(counter == target) {return file_line;}
				counter++;
			}
		} else if(select_data_parameter_4_condition == "MATCH") {
			int match_total = 0;
			int match_index = 1;
			std::string return_value;
			while(std::getline(file,file_line)) {
				if(select_data_parameter_5_parameter == file_line) {
					match_total++;
					match_index++;
					return_value = return_value + "I(" + std::to_string(match_index - 2) + ") ";
				}
			} return return_value + " " + "\n" + "TOTAL(" + std::to_string(match_total) + ")";
		} else if(select_data_parameter_4_condition == "FIRST-MATCH") {
			int index = 1;			
			while(std::getline(file,file_line)) {
				if(select_data_parameter_5_parameter == file_line) {return "I("  + std::to_string(index - 2) + ")" + "  " + file_line;}
				index++;	
			}
		} return "";
	}
};

#endif
