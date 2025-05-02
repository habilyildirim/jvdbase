#ifndef DATAMNG_H
#define DATAMNG_H

std::string query_platform_datamng(){
	#if __linux__
		return "gnulinux";
	#elif _WIN32
		return "windows";
	#else
		return "NULL";
	#endif
}

std::string base_path_datamng = "test/";

class main_datamng_clss{
	public:
	void insert_data(std::string insert_data_parameter_1_base_name,std::string insert_data_parameter_2_table_name,std::string insert_data_parameter_3_datastr_name,std::string insert_data_parameter_4_data_name){
		if(query_platform_datamng() == "gnulinux"){
			std::string file_path = base_path_datamng + insert_data_parameter_1_base_name + "/" + insert_data_parameter_2_table_name + "/" + insert_data_parameter_3_datastr_name + ".jvd";
			std::ofstream ofile(file_path, std::ios::app);
			ofile << insert_data_parameter_4_data_name << "\n";
		}else if(query_platform_datamng() == "windows"){
		//WINDOWS	
		}else{}
	}
	void delete_data(std::string del_data_parameter_1_base_name,std::string del_data_parameter_2_table_name,std::string del_data_parameter_3_datastr_name,std::string del_data_parameter_4_condition,std::string del_data_parameter_5_parameter){
		if(query_platform_datamng() == "gnulinux"){
			std::string file_path = base_path_datamng + del_data_parameter_1_base_name + "/" + del_data_parameter_2_table_name + "/" + del_data_parameter_3_datastr_name + ".jvd";
		    std::ifstream ifile(file_path);
		    //TEMP FILE
		    std::string status_temp_file = base_path_datamng + del_data_parameter_1_base_name + "/" + del_data_parameter_2_table_name + "/" + "temp.jtmp";
		    std::string command = "touch " + base_path_datamng + del_data_parameter_1_base_name + "/" + del_data_parameter_2_table_name + "/" + "temp.jtmp";
		    system(command.c_str());
		    std::ofstream tempfile(status_temp_file);

			std::string data_line_datamng;
			if(del_data_parameter_4_condition == "INDEX"){
				int line_counter_datamng = 1;
				int target = std::stoi(del_data_parameter_5_parameter) + 2;
				while(std::getline(ifile,data_line_datamng)){
					if(line_counter_datamng != target){
						tempfile << data_line_datamng << "\n";
					}
					line_counter_datamng++;
				}
				command = "rm " + file_path;
				system(command.c_str());
				command = "mv " + status_temp_file + " " + file_path;
				system(command.c_str());
			}else if(del_data_parameter_4_condition == "MATCH"){
				while(std::getline(ifile,data_line_datamng)){
					if(del_data_parameter_5_parameter != data_line_datamng){
						tempfile << data_line_datamng << "\n";
					}
				}
				command = "rm " + file_path;
				system(command.c_str());
				command = "mv " + status_temp_file + " " + file_path;
				system(command.c_str());
			}else if(del_data_parameter_4_condition == "FIRST-MATCH"){
				bool controller = false;
				while(std::getline(ifile,data_line_datamng)){
					if(controller == false && del_data_parameter_5_parameter == data_line_datamng){
						controller = true;
						continue;
					}
					tempfile << data_line_datamng << "\n";
				}
				command = "rm " + file_path;
				system(command.c_str());
				command = "mv " + status_temp_file + " " + file_path;
				system(command.c_str());				
			}else{}
		}else if(query_platform_datamng() == "windows"){
		//WINDOWS	
		}else{}		
	} 
};

class selectprc_datamng_clss{
	public:
	std::string select_data(std::string select_data_parameter_1_base_name,std::string select_data_parameter_2_table_name,std::string select_data_parameter_3_datastr_name,std::string select_data_parameter_4_condition,std::string select_data_parameter_5_parameter){
		std::string file_path = base_path_datamng + select_data_parameter_1_base_name + "/" + select_data_parameter_2_table_name + "/" + select_data_parameter_3_datastr_name + ".jvd";
		std::fstream file(file_path);
		std::string file_line;
		
		if(select_data_parameter_4_condition == "INDEX"){
			int counter = 1;
			int target = std::stoi(select_data_parameter_5_parameter) + 2;
			
			while(std::getline(file,file_line)){
				if(counter == target){return file_line;}
				counter++;
			}
		}else if(select_data_parameter_4_condition == "MATCH"){
			int match_total = 0;
			int match_index = 1;
			std::string return_value;
			while(std::getline(file,file_line)){
				if(select_data_parameter_5_parameter == file_line){
					match_total++;
					match_index++;
					return_value = return_value + "I(" + std::to_string(match_index - 2) + ") ";
				}
			}return return_value + " " + "\n" + "TOTAL(" + std::to_string(match_total) + ")";
		}else if(select_data_parameter_4_condition == "FIRST-MATCH"){
			int index = 1;
			
			while(std::getline(file,file_line)){
				if(select_data_parameter_5_parameter == file_line){return "I("  + std::to_string(index - 2) + ")" + "  " + file_line;}
				index++;	
			}
		}
		return "";
	}
};

#endif
