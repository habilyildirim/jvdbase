#include "inc.h"
#include "mainbaselb.h"
#include "tablelb.h"
#include "datastrlb.h"
#include "datamnglb.h"

const std::string base_path_interpreter = BASE_PATH;
uint8_t ssystem_control();
color_codes_strc color_codes;

std::string join(const std::vector<std::string> & v, const std::string & delimiter = ", ") {
    std::string result;
    for(size_t i = 0; i < v.size(); ++i){
        result += (i ? delimiter : "") + v[i];
    }
    return result;
}

std::string exists_control_fn(std::string exists_control_fn_parameter_1_base_name, std::string exists_control_fn_parameter_2_table_file, std::string custom = "NULL"){
	std::string control_table = base_path_interpreter + exists_control_fn_parameter_1_base_name + "/" + exists_control_fn_parameter_2_table_file;
	std::ifstream control_file(control_table);

	if(custom == "LINUX" && std::filesystem::exists("/opt/" + exists_control_fn_parameter_1_base_name)){return "EXISTS";}
	else if(custom == "WINDOWS" && std::filesystem::exists("C:/" + exists_control_fn_parameter_1_base_name)){return "EXISTS";}
					
	if(!std::filesystem::exists(base_path_interpreter + exists_control_fn_parameter_1_base_name)){return "BASE_NOT_EXISTS";}
	else if(!std::filesystem::exists(control_table)){return "DATA_NOT_EXISTS";}
	else{return "DATA_EXISTS";}
}

std::string exists_control2_fn(std::string exists_datastr_parameter_1_file_path, std::string exists_datastr_parameter_1_data, std::string exists_datastr_parameter_1_table_name){
	std::ifstream base_exists_file(exists_datastr_parameter_1_file_path);
	std::string data = exists_datastr_parameter_1_file_path + "/" + exists_datastr_parameter_1_table_name + "/" + exists_datastr_parameter_1_data;

	if(!std::filesystem::exists(exists_datastr_parameter_1_file_path)){return "BASE_NOT_EXISTS";}
	else if(!base_exists_file.is_open()){return "MAIN_FILE_IS_NOT_OPEN";}
	else if (!std::filesystem::exists(exists_datastr_parameter_1_file_path + "/" + exists_datastr_parameter_1_table_name)){return "TABLE_NOT_EXISTS";}
	else if(std::filesystem::exists(data)){return "DATASTR_EXISTS";}
	else if(!std::filesystem::exists(data)){return "DATASTR_NOT_EXISTS";}
	else{return "TRUE_FN";}
}

std::string condition_control_fn(std::string condition_fn_parameter){
	if(condition_fn_parameter.substr(0,6) == "INDEX#"){return "INDEX#";}
	else if(condition_fn_parameter.substr(0,6) == "MATCH#"){return "MATCH#";}
	else if(condition_fn_parameter.substr(0,12) == "FIRST-MATCH#"){return "FIRST-MATCH#";}
	else{return "WRONG";}
}

std::string data_type_control_fn(std::string parameter_data,std::string parameter_type){
	std::istringstream control(parameter_data.substr(2,parameter_data.length() - 2));
	int int_control;
	char chr_control;
	
	if(parameter_type == "BOOL" && parameter_data.substr(3,parameter_data.length() - 3) == "true" || parameter_data.substr(3,parameter_data.length() - 3) == "false"){return "BOOL";}
	else if(parameter_type == "INT" && control >> int_control && !(control >> chr_control)){return "INT";}
	else if(parameter_type == "CHAR" && parameter_type.substr(2,parameter_data.length() - 2).length() == 1){return "CHAR";}
	else{return "WRONG";}
}

std::string datastr_data_type_control_fn(std::string parameter_data_type_path){
	std::ifstream datastr_type_control_fn_file(parameter_data_type_path);
	std::string datastr_type_control_fn_file_data_type;
	
	while(std::getline(datastr_type_control_fn_file, datastr_type_control_fn_file_data_type)){break;}
	return datastr_type_control_fn_file_data_type.substr(5,datastr_type_control_fn_file_data_type.length() - 5);
}

std::string data_type_parameter_control_fn(std::string parameter_data_type){
	if(parameter_data_type == "INT"){return "INT";}
	else if(parameter_data_type == "CHAR"){return "CHAR";}
	else if(parameter_data_type == "STRING"){return "STRING";}
	else if(parameter_data_type == "BOOL"){return "BOOL";}
	else{return "WRONG";}
}

std::string find_parameter_fn(std::string find_parameter_parameter_1_file_line, int find_parameter_parameter_2_counter, bool last_parameter = false){
	int find_parameter_counter_1 = find_parameter_parameter_2_counter;
	bool find_parameter_error = false;
	int length_add = 0;
	char query_char = ',';
	std::vector<std::string> find_parameter_indep_vector;
	
	if(last_parameter == true){
		length_add++;
		query_char = ']';
	}
	while(find_parameter_parameter_1_file_line[find_parameter_counter_1] != query_char){
		std::string convert_char_base_name(1,find_parameter_parameter_1_file_line[find_parameter_counter_1]);
		find_parameter_indep_vector.push_back(convert_char_base_name);
		find_parameter_counter_1++;
		if(find_parameter_counter_1 > find_parameter_parameter_1_file_line.length()){
			find_parameter_error = true;
			break;
		}
	}if(find_parameter_error == true){return "FIND_PARAMETER_LINE_ERROR";}
	else{return join(find_parameter_indep_vector,"");}
}

void info_msg_fn(std::string info_msg_parameter_1, std::string info_msg_parameter_2, int info_msg_parameter_3_query_num){std::cout << "Q(" << info_msg_parameter_3_query_num << ")" << " " << color_codes.color_information_s << info_msg_parameter_1 << " = " << info_msg_parameter_2  << color_codes.color_information_f << "\n";}

void error_msg_fn(std::string error_msg_parameter_1, int error_msg_parameter_2, std::string error_msg_parameter_3){
	error_msg_parameter_2++;
	
	if(error_msg_parameter_1 == "ERROR SYNTAX"){std::cout << color_codes.color_error_s << "LINE " << error_msg_parameter_2 << "; " << error_msg_parameter_1 << " = " << "'" << error_msg_parameter_3 << "'" << color_codes.color_error_f << "\n";}
	else{std::cout << color_codes.color_error_s << "LINE " << error_msg_parameter_2 << "; " << error_msg_parameter_1 << " = " << error_msg_parameter_3 << color_codes.color_error_f << "\n";}
}

int main(int argc, char* argv[]){
	std::string input_file_data = argv[1];
	std::string input_file_line;
	std::ifstream input_file(input_file_data);
	
	std::string base_name;
	std::string info_msg_content;

	main_base_clss main_base_obj;
	main_table_clss main_table_obj;
	main_datastr_clss main_datastr_obj;
	main_datamng_clss main_datamng_obj;
	selectprc_datamng_clss selectprc_datamng_obj;
	backup_clss backup_obj;
		
	bool inter_success = true;
	int line_counter = 0;
	int query_counter = 0;
	int output_counter = 0;

	std::vector<std::string> select_vector;

	if(input_file_data.substr(input_file_data.length() - 4, 4) != ".jnq"){
		error_msg_fn("ERROR FORMAT", 0, "WRONG FILE FORMAT");
		inter_success = false;
	}else if(input_file.is_open()){
		while(std::getline(input_file, input_file_line)){
			if(input_file_line.substr(0,13) == "CREATE-BASE->"){
			//CREATE_BASE_OP_START
				base_name = input_file_line.substr(13, input_file_line.length() - 13);
				
				if(std::filesystem::exists(base_path_interpreter + base_name) && std::filesystem::is_directory(base_path_interpreter + base_name)){
					base_exists_label:
					error_msg_fn("ERROR CREATE BASE", line_counter, "BASE EXISTS");
					inter_success = false;
					break;
				}else{
					query_counter++;
					main_base_obj.create_base(base_name);
					info_msg_fn("CREATE BASE",base_name,query_counter);	
				}
			//CREATE_BASE_OP_END
			}else if(input_file_line.substr(0,10) == "DEL-BASE->"){
			//DEL_BASE_OP_START
				base_name = input_file_line.substr(10, input_file_line.length() - 10);
				
				if(!std::filesystem::exists(base_path_interpreter + base_name)){
					error_msg_fn("ERROR DELETE BASE", line_counter, "BASE NOT EXISTS");
					inter_success = false;
					break;
				}else{
					query_counter++;
					main_base_obj.del_base(base_name);
					info_msg_fn("DEL BASE",base_name,query_counter);
				}
			//DEL_BASE_OP_END
			}else if(input_file_line.substr(0,14) == "CREATE-TABLE->"){
			//CREATE_TABLE_OP_START
				std::string create_table_line_data;
				std::getline(input_file, create_table_line_data);
				if(create_table_line_data != "["){
					error_msg_fn("ERROR SYNTAX", line_counter, "TRUE USAGE = CREATE-TABLE->\n[\nBASE-NAME->BASE_NAME\nTABLE-NAME->TABLE_NAME\n]");
					inter_success = false;
					break;
				}else{
					bool first_work_create_table = true;
					int control_counter = 1;
					std::string create_table_base_name;
					std::string create_table_table_name;
				
					while(std::getline(input_file, create_table_line_data)){
						line_counter++;
						if(create_table_line_data.substr(0,11) != "BASE-NAME->" && first_work_create_table == true){							
							error_msg_fn("ERROR CREATE TABLE", line_counter, "MISSING PARAMETER-BASE NAME MUST BE SPECIFIED FIRST");
							inter_success = false;
							break;
						}else if(first_work_create_table == true){
							create_table_base_name = create_table_line_data.substr(11, create_table_line_data.length() - 11);
						}else if(create_table_line_data.substr(0,12) != "TABLE-NAME->" && control_counter == 2){							
							error_msg_fn("ERROR CREATE TABLE", line_counter, "MISSING PARAMETER-TABLE NAME MUST BE SPECIFIED SECOND");
							inter_success = false;
							break;
						}else if(control_counter == 2){
							create_table_table_name = create_table_line_data.substr(12, create_table_line_data.length() - 12);
							if(create_table_table_name.substr(0,1) == ""){
								error_msg_fn("ERROR CREATE TABLE", line_counter, "TABLE NAME PARAMETER IS NULL");
								inter_success = false;
								break;
							}else if(create_table_table_name.substr(0,1) == " "){
								error_msg_fn("ERROR CREATE TABLE", line_counter, "TABLE NAME PARAMETER FIRST CHAR IS SPACE");
								inter_success = false;
								break;
							}else{
								std::string create_table_base_file_path = base_path_interpreter + create_table_base_name + "/" + create_table_base_name + ".jvb";
								if(exists_control_fn(create_table_base_name, create_table_table_name) == "BASE_NOT_EXISTS"){
									error_msg_fn("ERROR CREATE TABLE", line_counter, "BASE NOT EXISTS");
									inter_success = false;
									break;
								}else if(exists_control_fn(create_table_base_name, create_table_table_name) == "DATA_EXISTS"){
									error_msg_fn("ERROR CREATE TABLE", line_counter, "TABLE EXISTS");
									inter_success = false;
									break;
								}else{
									query_counter++;
									info_msg_content = create_table_base_name + "~>" + create_table_table_name;			
									info_msg_fn("CREATE TABLE",info_msg_content,query_counter);
									main_table_obj.create_table(create_table_base_name, create_table_table_name);
								}
							}
						}else if(create_table_line_data.substr(0,16) == "CREATE-DATASTR->"){
							std::string create_table_datastr_name = create_table_line_data.substr(16, create_table_datastr_name.length() - 16);
							if(create_table_datastr_name.substr(0,1) == ""){
								error_msg_fn("ERROR CREATE TABLE", line_counter, "DATASTR PARAMETER IS NULL");
								inter_success = false;
								break;
							}else if(create_table_datastr_name.substr(0,1) == " "){
								error_msg_fn("ERROR CREATE TABLE", line_counter, "DATASTR PARAMETER FIRST CHAR IS SPACE");
								inter_success = false;
								break;
							}else{
								std::string create_table_base_file_path = base_path_interpreter + create_table_base_name;
								if(exists_control_fn(create_table_base_name, create_table_table_name) == "DATA_EXISTS"){
									if(exists_control_fn(create_table_base_name, create_table_table_name + "/" + create_table_table_name + create_table_datastr_name + ".jvd") == "BASE_NOT_EXISTS"){
										error_msg_fn("ERROR CREATE TABLE", line_counter, "CREATED TABLE BUT NOT BE CREATE DATASTR BECOUSE BASE IS NOT EXISTS");
										inter_success = false;
										break;
									}else if(exists_control_fn(create_table_base_name, create_table_table_name + "/" + create_table_datastr_name + ".jvd") == "DATA_EXISTS"){
										error_msg_fn("ERROR CREATE TABLE", line_counter, "CREATED TABLE BUT NOT BE CREATE DATASTR BECOUSE DATASTR IS EXISTS");
										inter_success = false;
										break;
									}else if(exists_control_fn(create_table_base_name, create_table_table_name + "/" + create_table_datastr_name + ".jvd") == "DATA_NOT_EXISTS"){
										query_counter++;
										main_datastr_obj.create_datastr(create_table_base_file_path, create_table_table_name, create_table_datastr_name,"STRING");
										info_msg_content = create_table_base_name + "~>" + create_table_table_name + "~>" + create_table_datastr_name;
										info_msg_fn("CREATE DATASTR",info_msg_content,query_counter);
									}
								}
							}
						}else if(create_table_line_data == "]"){break;}
						if(control_counter < 3){control_counter++;}
						first_work_create_table = false;
					}
				}if(inter_success == false){break;}
			//CREATE_TABLE_OP_END
			}else if(input_file_line.substr(0,12) == "DEL-TABLE->["){
			//DEL_TABLE_OP_START
				std::string del_table_base_name;
				std::string del_table_table_name;
				
				if(find_parameter_fn(input_file_line,12) == "FIND_PARAMETER_LINE_ERROR"){
					error_msg_fn("ERROR DEL TABLE", line_counter, "TRUE USAGE 'DEL-TABLE->[BASE NAME,TABLE NAME]'");
					inter_success = false;
					break;
				}else{del_table_base_name = find_parameter_fn(input_file_line,12);}
				if(find_parameter_fn(input_file_line,del_table_base_name.length(),true) == "FIND_PARAMETER_LINE_ERROR"){
					error_msg_fn("ERROR DEL TABLE", line_counter, "TRUE USAGE 'DEL-TABLE->[BASE NAME,TABLE NAME]'");
					inter_success = false;
					break;
				}else{del_table_table_name = find_parameter_fn(input_file_line,13 + del_table_base_name.length(),true);}
				
				if(exists_control_fn(del_table_base_name,del_table_table_name) == "BASE_NOT_EXISTS"){
					error_msg_fn("ERROR DEL TABLE", line_counter, "BASE NOT EXISTS");
					inter_success = false;
					break;
				}else if(exists_control_fn(del_table_base_name,del_table_table_name) == "DATA_NOT_EXISTS"){
					error_msg_fn("ERROR DEL TABLE", line_counter, "TABLE NOT EXISTS");
					inter_success = false;
					break;					
				}else{
					query_counter++;
					main_table_obj.del_table(del_table_base_name,del_table_table_name);
					info_msg_content = del_table_base_name + "~>" + del_table_table_name;
					info_msg_fn("DEL TABLE",info_msg_content,query_counter);
				}
			//DEL_TABLE_OP_END
			}else if(input_file_line.substr(0,17) == "CREATE-DATASTR->["){
			//CREATE_DATASTR_OP_START
				std::string create_datastr_line_base_name;
				std::string create_datastr_line_table_name;
				std::string create_datastr_line_new_datastr_name;
				std::string create_datastr_data_type;
				
				if(find_parameter_fn(input_file_line,17) == "FIND_PARAMETER_LINE_ERROR"){
					error_msg_fn("ERROR CREATE DATA STORAGE", line_counter, "TRUE USAGE 'CREATE-DATASTR->[BASE NAME,TABLE NAME,NEW DATA STORAGE NAME,DATA TYPE: INT,STRING,BOOL]'");
					inter_success = false;
					break;
				}else{create_datastr_line_base_name = find_parameter_fn(input_file_line,17);}
				if(find_parameter_fn(input_file_line,18 + create_datastr_line_base_name.length()) == "FIND_PARAMETER_LINE_ERROR"){
					error_msg_fn("ERROR CREATE DATA STORAGE", line_counter, "TRUE USAGE 'CREATE-DATASTR->[BASE NAME,TABLE NAME,NEW DATA STORAGE NAME,DATA TYPE: INT,STRING,BOOL]'");
					inter_success = false;
					break;
				}else{create_datastr_line_table_name = find_parameter_fn(input_file_line,18 + create_datastr_line_base_name.length());}
				if(find_parameter_fn(input_file_line,19 + create_datastr_line_base_name.length() + create_datastr_line_table_name.length()) == "FIND_PARAMETER_LINE_ERROR"){
					error_msg_fn("ERROR CREATE DATA STORAGE", line_counter, "TRUE USAGE 'CREATE-DATASTR->[BASE NAME,TABLE NAME,NEW DATA STORAGE NAME,DATA TYPE: INT,STRING,BOOL]'");
					inter_success = false;
					break;
				}else{create_datastr_line_new_datastr_name = find_parameter_fn(input_file_line,19 + create_datastr_line_base_name.length() + create_datastr_line_table_name.length());}
				if(data_type_parameter_control_fn(find_parameter_fn(input_file_line,20 + create_datastr_line_base_name.length() + create_datastr_line_table_name.length() + create_datastr_line_new_datastr_name.length(),true)) == "WRONG" || find_parameter_fn(input_file_line,20 + create_datastr_line_base_name.length() + create_datastr_line_table_name.length() + create_datastr_line_new_datastr_name.length(),true) == "FIND_PARAMETER_LINE_ERROR"){
					error_msg_fn("ERROR CREATE DATA STORAGE", line_counter, "TRUE USAGE 'CREATE-DATASTR->[BASE NAME,TABLE NAME,NEW DATA STORAGE NAME,DATA TYPE: INT,STRING,BOOL]'");
					inter_success = false;
					break;
				}else{create_datastr_data_type = find_parameter_fn(input_file_line,20 + create_datastr_line_base_name.length() + create_datastr_line_table_name.length() + create_datastr_line_new_datastr_name.length(),true);}
				
				if(exists_control2_fn(base_path_interpreter + create_datastr_line_base_name,create_datastr_line_new_datastr_name + ".jvd",create_datastr_line_table_name) == "BASE_NOT_EXISTS"){
					error_msg_fn("ERROR CREATE DATA STORAGE", line_counter, "BASE NOT EXISTS");
					inter_success = false;
					break;
				}else if(exists_control2_fn(base_path_interpreter + create_datastr_line_base_name,create_datastr_line_new_datastr_name + ".jvd",create_datastr_line_table_name) == "TABLE_NOT_EXISTS"){
					error_msg_fn("ERROR CREATE DATA STORAGE", line_counter, "TABLE NOT EXISTS");
					inter_success = false;
					break;
				}else if(exists_control2_fn(base_path_interpreter + create_datastr_line_base_name,create_datastr_line_new_datastr_name + ".jvd",create_datastr_line_table_name) == "DATASTR_EXISTS"){
					error_msg_fn("ERROR CREATE DATA STORAGE", line_counter, "DATA STORAGE EXISTS");
					inter_success = false;
					break;
				}else{
					query_counter++;
					main_datastr_obj.create_datastr(base_path_interpreter + create_datastr_line_base_name, create_datastr_line_table_name, create_datastr_line_new_datastr_name,create_datastr_data_type);
					info_msg_content = create_datastr_line_base_name + "~>" + create_datastr_line_table_name + "~>" + create_datastr_line_new_datastr_name;
					info_msg_fn("CREATE DATASTR",info_msg_content,query_counter);
				}
			//CREATE_DATASTR_OP_END
			}else if(input_file_line.substr(0,14) == "DEL-DATASTR->["){
			//DEL_DATASTR_OP_START
				std::string del_datastr_line_base_name;
				std::string del_datastr_line_table_name;
				std::string del_datastr_line_deleted_datastr_name;
				
				if(find_parameter_fn(input_file_line,14) == "FIND_PARAMETER_LINE_ERROR"){
					error_msg_fn("ERROR DEL DATA STORAGE", line_counter, "TRUE USAGE 'DEL-DATASTR->[BASE NAME,TABLE NAME,DEL DATA STORAGE NAME]'");
					inter_success = false;
					break;
				}else{del_datastr_line_base_name = find_parameter_fn(input_file_line,14);}
				if(find_parameter_fn(input_file_line,14 + del_datastr_line_base_name.length()) == "FIND_PARAMETER_LINE_ERROR"){
					error_msg_fn("ERROR DEL DATA STORAGE", line_counter, "TRUE USAGE 'DEL-DATASTR->[BASE NAME,TABLE NAME,DEL DATA STORAGE NAME]'");
					inter_success = false;
					break;
				}else{del_datastr_line_table_name = find_parameter_fn(input_file_line,15 + del_datastr_line_base_name.length());}
				if(find_parameter_fn(input_file_line,16 + del_datastr_line_base_name.length() + del_datastr_line_table_name.length(),true) == "FIND_PARAMETER_LINE_ERROR"){
					error_msg_fn("ERROR DEL DATA STORAGE", line_counter, "TRUE USAGE 'DEL-DATASTR->[BASE NAME,TABLE NAME,DEL DATA STORAGE NAME]'");
					inter_success = false;
					break;
				}else{del_datastr_line_deleted_datastr_name = find_parameter_fn(input_file_line,16 + del_datastr_line_base_name.length() + del_datastr_line_table_name.length(),true);}
				
				if(exists_control2_fn(base_path_interpreter + del_datastr_line_base_name, del_datastr_line_deleted_datastr_name + ".jvd",del_datastr_line_table_name) == "BASE_NOT_EXISTS"){
					error_msg_fn("ERROR DEL DATA STORAGE", line_counter, "BASE NOT EXISTS");
					inter_success = false;
					break;
				}else if(exists_control2_fn(base_path_interpreter + del_datastr_line_base_name, del_datastr_line_deleted_datastr_name + ".jvd", del_datastr_line_table_name) == "TABLE_NOT_EXISTS"){
					error_msg_fn("ERROR DEL DATA STORAGE", line_counter, "TABLE NOT EXISTS");
					inter_success = false;
					break;
				}else if(exists_control2_fn(base_path_interpreter + del_datastr_line_base_name, del_datastr_line_deleted_datastr_name + ".jvd", del_datastr_line_table_name) == "DATASTR_NOT_EXISTS"){
					error_msg_fn("ERROR DEL DATA STORAGE", line_counter, "DATA STORAGE NOT EXISTS");
					inter_success = false;
					break;
				}else{
					query_counter++;
					main_datastr_obj.del_datastr(base_path_interpreter + del_datastr_line_base_name, del_datastr_line_table_name, del_datastr_line_deleted_datastr_name);
					info_msg_content = del_datastr_line_base_name + "~>" + del_datastr_line_table_name + "~>" + del_datastr_line_deleted_datastr_name;
					info_msg_fn("DEL DATASTR",info_msg_content,query_counter);
				}
			//DEL_DATASTR_OP_END
			}else if(input_file_line.substr(0,14) == "INSERT-DATA->["){
			//INSERT_DATA_OP_START
				std::string insert_data_base_name;
				std::string insert_data_table_name;
				std::string insert_data_datastr_name;
				std::string insert_data_data_name;
				
				if(find_parameter_fn(input_file_line,14) == "FIND_PARAMETER_LINE_ERROR"){
					error_msg_fn("ERROR INSERT DATA", line_counter, "TRUE USAGE 'INSERT-DATA->[BASE NAME,TABLE NAME,DATASTR NAME,DATA NAME]'");
					inter_success = false;
					break;
				}else{insert_data_base_name = find_parameter_fn(input_file_line,14);}
				if(find_parameter_fn(input_file_line,14 + insert_data_base_name.length()) == "FIND_PARAMETER_LINE_ERROR"){
					error_msg_fn("ERROR INSERT DATA", line_counter, "TRUE USAGE 'INSERT-DATA->[BASE NAME,TABLE NAME,DATASTR NAME,DATA NAME]'");
					inter_success = false;
					break;
				}else{insert_data_table_name = find_parameter_fn(input_file_line,15 + insert_data_base_name.length());}
				if(find_parameter_fn(input_file_line,16 + insert_data_base_name.length() + insert_data_table_name.length()) == "FIND_PARAMETER_LINE_ERROR"){
					error_msg_fn("ERROR INSERT DATA", line_counter, "TRUE USAGE 'INSERT-DATA->[BASE NAME,TABLE NAME,DATASTR NAME,DATA NAME]'");
					inter_success = false;
					break;
				}else{insert_data_datastr_name = find_parameter_fn(input_file_line,16 + insert_data_base_name.length() + insert_data_table_name.length());}
				if(find_parameter_fn(input_file_line,17 + insert_data_base_name.length() + insert_data_table_name.length() + insert_data_datastr_name.length(),true) == "FIND_PARAMETER_LINE_ERROR"){
					error_msg_fn("ERROR INSERT DATA", line_counter, "TRUE USAGE 'INSERT-DATA->[BASE NAME,TABLE NAME,DATASTR NAME,DATA NAME]'");
					inter_success = false;
					break;
				}else{insert_data_data_name = find_parameter_fn(input_file_line,17 + insert_data_base_name.length() + insert_data_table_name.length() + insert_data_datastr_name.length(),true);}				
				
				if(exists_control2_fn(base_path_interpreter + insert_data_base_name,insert_data_datastr_name + ".jvd",insert_data_table_name) == "BASE_NOT_EXISTS"){
					error_msg_fn("ERROR INSERT DATA", line_counter, "BASE NOT EXISTS");
					inter_success = false;
					break;
				}else if(exists_control2_fn(base_path_interpreter + insert_data_base_name,insert_data_datastr_name + ".jvd",insert_data_table_name) == "TABLE_NOT_EXISTS"){
					error_msg_fn("ERROR INSERT DATA", line_counter, "TABLE NOT EXISTS");
					inter_success = false;
					break;
				}else if(exists_control2_fn(base_path_interpreter + insert_data_base_name,insert_data_datastr_name + ".jvd",insert_data_table_name) == "DATASTR_NOT_EXISTS"){
					error_msg_fn("ERROR INSERT DATA", line_counter, "DATA STORAGE NOT EXISTS");
					inter_success = false;
					break;
				}else{
					//BOOL TYPE INSERT
					if(insert_data_data_name.substr(0,3) == "10*" && data_type_control_fn(insert_data_data_name,"BOOL") == "BOOL" && datastr_data_type_control_fn(base_path_interpreter + insert_data_base_name + "/" + insert_data_table_name + "/" + insert_data_datastr_name + ".jvd") == "BOOL"){
						query_counter++;													
						main_datamng_obj.insert_data(insert_data_base_name,insert_data_table_name,insert_data_datastr_name,insert_data_data_name.substr(3,insert_data_data_name.length() - 3));
						info_msg_content = insert_data_base_name + "~>" + insert_data_table_name + "~>" + insert_data_datastr_name + "~>" + insert_data_data_name.substr(3,insert_data_data_name.length() - 3);
						info_msg_fn("INSERT DATA",info_msg_content,query_counter);
					}else if(insert_data_data_name.substr(0,3) == "10*" && datastr_data_type_control_fn(base_path_interpreter + insert_data_base_name + "/" + insert_data_table_name + "/" + insert_data_datastr_name + ".jvd") != "BOOL"){
						error_msg_fn("ERROR INSERT DATA", line_counter,insert_data_base_name + "~>" + insert_data_table_name + "~>" + insert_data_datastr_name + " DATASTR IS NOT BOOL");
						inter_success = false;
						break;
					}else if(insert_data_data_name.substr(0,3) == "10*" && data_type_control_fn(insert_data_data_name,"BOOL") != "BOOL"){
						error_msg_fn("ERROR INSERT DATA",line_counter,insert_data_data_name.substr(3,insert_data_data_name.length() - 3) + " DATA IS NOT BOOL " + insert_data_base_name + "~>" + insert_data_table_name + "~>" + insert_data_datastr_name + " DATASTR IS BOOL");
						inter_success = false;
						break;
					}
					//INT TYPE INSERT
					else if(insert_data_data_name.substr(0,2) == "I*" && data_type_control_fn(insert_data_data_name,"INT") == "INT" && datastr_data_type_control_fn(base_path_interpreter + insert_data_base_name + "/" + insert_data_table_name + "/" + insert_data_datastr_name + ".jvd") == "INT"){
						query_counter++;													
						main_datamng_obj.insert_data(insert_data_base_name,insert_data_table_name,insert_data_datastr_name,insert_data_data_name.substr(2,insert_data_data_name.length() - 2));
						info_msg_content = insert_data_base_name + "~>" + insert_data_table_name + "~>" + insert_data_datastr_name + "~>" + insert_data_data_name.substr(2,insert_data_data_name.length() - 2);
						info_msg_fn("INSERT DATA",info_msg_content,query_counter);
					}else if(insert_data_data_name.substr(0,2) == "I*" && datastr_data_type_control_fn(base_path_interpreter + insert_data_base_name + "/" + insert_data_table_name + "/" + insert_data_datastr_name + ".jvd") != "INT"){
						error_msg_fn("ERROR INSERT DATA",line_counter,insert_data_base_name + "~>" + insert_data_table_name + "~>" + insert_data_datastr_name + " DATASTR IS NOT INT");
						inter_success = false;
						break;
					}else if(insert_data_data_name.substr(0,2) == "I*" && data_type_control_fn(insert_data_data_name,"INT") != "INT"){
						error_msg_fn("ERROR INSERT DATA",line_counter,insert_data_data_name.substr(2,insert_data_data_name.length() - 2) + " DATA IS NOT INT " + insert_data_base_name + "~>" + insert_data_table_name + "~>" + insert_data_datastr_name + " DATASTR IS INT");
						inter_success = false;
						break;
					}
					//CHAR TYPE INSERT
					else if(insert_data_data_name.substr(0,2) == "'*" && data_type_control_fn(insert_data_data_name,"CHAR") == "CHAR" && datastr_data_type_control_fn(base_path_interpreter + insert_data_base_name + "/" + insert_data_table_name + "/" + insert_data_datastr_name + ".jvd") == "CHAR"){
						query_counter++;													
						main_datamng_obj.insert_data(insert_data_base_name,insert_data_table_name,insert_data_datastr_name,insert_data_data_name.substr(2,insert_data_data_name.length() - 2));
						info_msg_content = insert_data_base_name + "~>" + insert_data_table_name + "~>" + insert_data_datastr_name + "~>" + insert_data_data_name.substr(2,insert_data_data_name.length() - 2);
						info_msg_fn("INSERT DATA",info_msg_content,query_counter);
					}else if(insert_data_data_name.substr(0,2) == "'*" && datastr_data_type_control_fn(base_path_interpreter + insert_data_base_name + "/" + insert_data_table_name + "/" + insert_data_datastr_name + ".jvd") != "CHAR"){
						error_msg_fn("ERROR INSERT DATA",line_counter,insert_data_base_name + "~>" + insert_data_table_name + "~>" + insert_data_datastr_name + " DATASTR IS NOT CHAR");
						inter_success = false;
						break;
					}else if(insert_data_data_name.substr(0,2) == "'*" && data_type_control_fn(insert_data_data_name,"CHAR") != "CHAR"){
						error_msg_fn("ERROR INSERT DATA",line_counter,insert_data_data_name.substr(2,insert_data_data_name.length() - 2) + " DATA IS NOT CHAR " + insert_data_base_name + "~>" + insert_data_table_name + "~>" + insert_data_datastr_name + " DATASTR IS CHAR");
						inter_success = false;
						break;
					}
					//STRING TYPE INSERT
					else if(insert_data_data_name.substr(0,2) == "~*" && datastr_data_type_control_fn(base_path_interpreter + insert_data_base_name + "/" + insert_data_table_name + "/" + insert_data_datastr_name + ".jvd") == "STRING"){
						query_counter++;													
						main_datamng_obj.insert_data(insert_data_base_name,insert_data_table_name,insert_data_datastr_name,insert_data_data_name.substr(2,insert_data_data_name.length() - 2));
						info_msg_content = insert_data_base_name + "~>" + insert_data_table_name + "~>" + insert_data_datastr_name + "~>" + insert_data_data_name.substr(2,insert_data_data_name.length() - 2);
						info_msg_fn("INSERT DATA",info_msg_content,query_counter);
					}else if(insert_data_data_name.substr(0,2) == "~*" && datastr_data_type_control_fn(base_path_interpreter + insert_data_base_name + "/" + insert_data_table_name + "/" + insert_data_datastr_name + ".jvd") != "STRING"){
						error_msg_fn("ERROR INSERT DATA",line_counter,insert_data_base_name + "~>" + insert_data_table_name + "~>" + insert_data_datastr_name + " DATASTR IS NOT STRING");
						inter_success = false;
						break;
					}else{
						error_msg_fn("ERROR INSERT DATA", line_counter, "WRONG DATA TYPE");
						inter_success = false;
						break;
					}
				}
			//INSERT_DATA_OP_END
			}else if(input_file_line.substr(0,11) == "DEL-DATA->["){			
			//DEL_DATA_OP_START
				std::string del_data_base_name;
				std::string del_data_table_name;
				std::string del_data_datastr_name;
				std::string del_data_condition;
				
				if(find_parameter_fn(input_file_line,11) == "FIND_PARAMETER_LINE_ERROR"){
					error_msg_fn("ERROR DEL DATA", line_counter, "TRUE USAGE 'DEL-DATA->[BASE NAME,TABLE NAME,DATASTR NAME,CONDITION]'");
					inter_success = false;
					break;
				}else{del_data_base_name = find_parameter_fn(input_file_line,11);}
				if(find_parameter_fn(input_file_line,11 + del_data_base_name.length()) == "FIND_PARAMETER_LINE_ERROR"){
					error_msg_fn("ERROR DEL DATA", line_counter, "TRUE USAGE 'DEL-DATA->[BASE NAME,TABLE NAME,DATASTR NAME,CONDITION]'");
					inter_success = false;
					break;
				}else{del_data_table_name = find_parameter_fn(input_file_line,12 + del_data_base_name.length());}
				if(find_parameter_fn(input_file_line,13 + del_data_base_name.length() + del_data_table_name.length()) == "FIND_PARAMETER_LINE_ERROR"){
					error_msg_fn("ERROR DEL DATA", line_counter, "TRUE USAGE 'DEL-DATA->[BASE NAME,TABLE NAME,DATASTR NAME,CONDITION]'");
					inter_success = false;
					break;
				}else{del_data_datastr_name = find_parameter_fn(input_file_line,13 + del_data_base_name.length() + del_data_table_name.length());}
				if(find_parameter_fn(input_file_line,14 + del_data_base_name.length() + del_data_table_name.length() + del_data_datastr_name.length(),true) == "FIND_PARAMETER_LINE_ERROR"){
					error_msg_fn("ERROR DEL DATA", line_counter, "TRUE USAGE 'INSERT-DATA->[BASE NAME,TABLE NAME,DATASTR NAME,CONDITION]'");
					inter_success = false;
					break;
				}else{del_data_condition = find_parameter_fn(input_file_line,14 + del_data_base_name.length() + del_data_table_name.length() + del_data_datastr_name.length(),true);}

				if(exists_control2_fn(base_path_interpreter + del_data_base_name,del_data_datastr_name + ".jvd",del_data_table_name) == "BASE_NOT_EXISTS"){
					error_msg_fn("ERROR DEL DATA", line_counter, "BASE NOT EXISTS");
					inter_success = false;
					break;
				}else if(exists_control2_fn(base_path_interpreter + del_data_base_name,del_data_datastr_name + ".jvd",del_data_table_name) == "TABLE_NOT_EXISTS"){
					error_msg_fn("ERROR DEL DATA", line_counter, "TABLE NOT EXISTS");
					inter_success = false;
					break;
				}else if(exists_control2_fn(base_path_interpreter + del_data_base_name,del_data_datastr_name + ".jvd",del_data_table_name) == "DATASTR_NOT_EXISTS"){
					error_msg_fn("ERROR DEL DATA", line_counter, "DATA STORAGE NOT EXISTS");
					inter_success = false;
					break;
				}else{
					if(condition_control_fn(del_data_condition.substr(0,6)) == "INDEX#"){
						main_datamng_obj.delete_data(del_data_base_name,del_data_table_name,del_data_datastr_name,"INDEX",del_data_condition.substr(6,del_data_condition.length() - 6));
						query_counter++;
						info_msg_content = del_data_base_name + "~>" + del_data_table_name + "~>" + del_data_datastr_name + "~>" + del_data_condition;
						info_msg_fn("DEL DATA",info_msg_content,query_counter);
					}else if(condition_control_fn(del_data_condition.substr(0,6)) == "MATCH#"){
						main_datamng_obj.delete_data(del_data_base_name,del_data_table_name,del_data_datastr_name,"MATCH",del_data_condition.substr(6,del_data_condition.length() - 6));
						query_counter++;
						info_msg_content = del_data_base_name + "~>" + del_data_table_name + "~>" + del_data_datastr_name + "~>" + del_data_condition;
						info_msg_fn("DEL DATA",info_msg_content,query_counter);
					}else if(condition_control_fn(del_data_condition.substr(0,12)) == "FIRST-MATCH#"){
						main_datamng_obj.delete_data(del_data_base_name,del_data_table_name,del_data_datastr_name,"FIRST-MATCH",del_data_condition.substr(12,del_data_condition.length() - 12));
						query_counter++;
						info_msg_content = del_data_base_name + "~>" + del_data_table_name + "~>" + del_data_datastr_name + "~>" + del_data_condition;
						info_msg_fn("DEL DATA",info_msg_content,query_counter);						
					}else{
						error_msg_fn("ERROR DEL DATA", line_counter, "TRUE USAGE 'INSERT-DATA->[BASE NAME,TABLE NAME,DATASTR NAME,CONDITION]'");
						inter_success = false;
						break;
					}
				}
			//DEL_DATA_OP_END
			}else if(input_file_line.substr(0,14) == "SELECT-DATA->["){
			//SELECT_DATA_OP_START
				std::string select_data_base_name;
				std::string select_data_table_name;
				std::string select_data_datastr_name;
				std::string select_data_condition;
			
				if(find_parameter_fn(input_file_line,14) == "FIND_PARAMETER_LINE_ERROR"){
					error_msg_fn("ERROR SELECT DATA", line_counter, "TRUE USAGE 'SELECT-DATA->[BASE NAME,TABLE NAME,DATASTR NAME,CONDITION]'");
					inter_success = false;
					break;
				}else{select_data_base_name = find_parameter_fn(input_file_line,14);}
				if(find_parameter_fn(input_file_line,14 + select_data_base_name.length()) == "FIND_PARAMETER_LINE_ERROR"){
					error_msg_fn("ERROR SELECT DATA", line_counter, "TRUE USAGE 'SELECT-DATA->[BASE NAME,TABLE NAME,DATASTR NAME,CONDITION]'");
					inter_success = false;
					break;
				}else{select_data_table_name = find_parameter_fn(input_file_line,15 + select_data_base_name.length());}
				if(find_parameter_fn(input_file_line,16 + select_data_base_name.length() + select_data_table_name.length()) == "FIND_PARAMETER_LINE_ERROR"){
					error_msg_fn("ERROR SELECT DATA", line_counter, "TRUE USAGE 'SELECT-DATA->[BASE NAME,TABLE NAME,DATASTR NAME,CONDITION]'");
					inter_success = false;
					break;
				}else{select_data_datastr_name = find_parameter_fn(input_file_line,16 + select_data_base_name.length() + select_data_table_name.length());}
				if(find_parameter_fn(input_file_line,17 + select_data_base_name.length() + select_data_table_name.length() + select_data_datastr_name.length(),true) == "FIND_PARAMETER_LINE_ERROR"){
					error_msg_fn("ERROR SELECT DATA", line_counter, "TRUE USAGE 'SELECT-DATA->[BASE NAME,TABLE NAME,DATASTR NAME,CONDITION]'");
					inter_success = false;
					break;
				}else{select_data_condition = find_parameter_fn(input_file_line,17 + select_data_base_name.length() + select_data_table_name.length() + select_data_datastr_name.length(),true);}				

				if(exists_control2_fn(base_path_interpreter + select_data_base_name,select_data_datastr_name + ".jvd",select_data_table_name) == "BASE_NOT_EXISTS"){
					error_msg_fn("ERROR SELECT DATA", line_counter, "BASE NOT EXISTS");
					inter_success = false;
					break;
				}else if(exists_control2_fn(base_path_interpreter + select_data_base_name,select_data_datastr_name + ".jvd",select_data_table_name) == "TABLE_NOT_EXISTS"){
					error_msg_fn("ERROR SELECT DATA", line_counter, "TABLE NOT EXISTS");
					inter_success = false;
					break;
				}else if(exists_control2_fn(base_path_interpreter + select_data_base_name,select_data_datastr_name + ".jvd",select_data_table_name) == "DATASTR_NOT_EXISTS"){
					error_msg_fn("ERROR SELECT DATA", line_counter, "DATA STORAGE NOT EXISTS");
					inter_success = false;
					break;
				}else{
					if(select_data_condition.substr(0,6) == "INDEX#"){
						query_counter++;
						info_msg_content = "SELECT DATA";
						info_msg_fn("SELECT DATA",info_msg_content,query_counter);
						select_vector.push_back("{" + select_data_base_name + "}" + "-" + "{" + select_data_table_name  + "}" + "-" + "{" + select_data_datastr_name + "}" + "CON" + "(" + select_data_condition + ")" + " " + selectprc_datamng_obj.select_data(select_data_base_name,select_data_table_name,select_data_datastr_name,"INDEX",select_data_condition.substr(6,select_data_condition.length() - 6)));
					}else if(select_data_condition.substr(0,6) == "MATCH#"){
						query_counter++;
						info_msg_content = "SELECT DATA";
						info_msg_fn("SELECT DATA",info_msg_content,query_counter);
						select_vector.push_back("{" + select_data_base_name + "}" + "-" + "{" + select_data_table_name  + "}" + "-" + "{" + select_data_datastr_name + "}" + "CON" + "(" + select_data_condition + ")" + " " + selectprc_datamng_obj.select_data(select_data_base_name,select_data_table_name,select_data_datastr_name,"MATCH",select_data_condition.substr(6,select_data_condition.length() - 6)));
					}else if(select_data_condition.substr(0,12) == "FIRST-MATCH#"){
						query_counter++;
						info_msg_content = "SELECT DATA";
						info_msg_fn("SELECT DATA",info_msg_content,query_counter);
						select_vector.push_back("{" + select_data_base_name + "}" + "-" + "{" + select_data_table_name  + "}" + "-" + "{" + select_data_datastr_name + "}" + "CON" + "(" + select_data_condition + ")" + " " + selectprc_datamng_obj.select_data(select_data_base_name,select_data_table_name,select_data_datastr_name,"FIRST-MATCH",select_data_condition.substr(12,select_data_condition.length() - 12)));
					}
				}
			//SELECT_DATA_OP_END	
			}else if(input_file_line.substr(0,14) == "BACKUP-BASE->["){
			//BACKUP_BASE_OP_START
				std::string backup_base_backup_base_name;
				if(find_parameter_fn(input_file_line,14,true) == "FIND_PARAMETER_LINE_ERROR"){
					error_msg_fn("ERROR BACKUP BASE", line_counter, "TRUE USAGE 'BACKUP-BASE->[BASE_NAME]'");
					inter_success = false;
					break;
				}else{backup_base_backup_base_name = find_parameter_fn(input_file_line,14,true);}

				if(exists_control_fn(backup_base_backup_base_name,"NULL") == "BASE_NOT_EXISTS"){
					error_msg_fn("ERROR BACKUP BASE", line_counter, "BASE NOT EXISTS");
					inter_success = false;
					break;
				}else{
					backup_obj.backup_base(backup_base_backup_base_name);
					if(ssystem_control() == 1){
						query_counter++;
						info_msg_content = "BACKUP BASE /opt/" + backup_base_backup_base_name;
						info_msg_fn("BACKUP",info_msg_content,query_counter);
					}else if(ssystem_control() == 0){
						query_counter++;
						info_msg_content = "BACKUP BASE C:/" + backup_base_backup_base_name;
						info_msg_fn("BACKUP",info_msg_content,query_counter);
					}else{
						error_msg_fn("ERROR BACKUP", line_counter, "support only linux & windows");
						inter_success = false;
						break;
					}
				}
			//BACKUP_BASE_OP_END
			}else if(input_file_line.substr(0,14) == "BACKUP-LOAD->["){
			//BACKUP_LOAD_OP_START
				std::string backup_load_base_name;
				if(find_parameter_fn(input_file_line,14,true) == "FIND_PARAMETER_LINE_ERROR"){
					error_msg_fn("ERROR BACKUP LOAD", line_counter, "TRUE USAGE 'BACKUP-LOAD->[BASE_NAME]'");
					inter_success = false;
					break;
				}else{backup_load_base_name = find_parameter_fn(input_file_line,14,true);}
				if(ssystem_control() == 1){
					if(exists_control_fn(backup_load_base_name,"NULL","LINUX") != "EXISTS"){
						error_msg_fn("ERROR BACKUP LOAD", line_counter, "BACKUP NOT EXISTS");
						inter_success = false;
						break;
					}else if(exists_control_fn(backup_load_base_name,"NULL") != "BASE_NOT_EXISTS"){
						error_msg_fn("ERROR BACKUP LOAD", line_counter, "BASE EXISTS");
						inter_success = false;
						break;
					}else{
						backup_obj.backup_load(backup_load_base_name);
						query_counter++;
						info_msg_content = "BACKUP LOAD ~>" + backup_load_base_name;
						info_msg_fn("BACKUP",info_msg_content,query_counter);	
					}
				}else if(ssystem_control() == 0){
					if(exists_control_fn(backup_load_base_name,"NULL","WINDOWS") != "EXISTS"){
						error_msg_fn("ERROR BACKUP LOAD", line_counter, "BACKUP NOT EXISTS");
						inter_success = false;
						break;
					}else if(exists_control_fn(backup_load_base_name,"NULL") != "BASE_NOT_EXISTS"){
						error_msg_fn("ERROR BACKUP LOAD", line_counter, "BASE EXISTS");
						inter_success = false;
						break;
					}else{
						backup_obj.backup_load(backup_load_base_name);
						query_counter++;
						info_msg_content = "BACKUP LOAD ~>" + backup_load_base_name;
						info_msg_fn("BACKUP",info_msg_content,query_counter);	
					}
				}else{
					error_msg_fn("ERROR BACKUP", line_counter, "support only linux & windows");
					inter_success = false;
					break;
				}
			//BACKUP_LOAD_OP_END
			}else if(input_file_line.substr(0,2) == "C{" || input_file_line.substr(0,2) == "c{"){
				//COMMENT LINES
				int comment_counter;
				std::string commend_data;
				while(std::getline(input_file,commend_data)){
					line_counter++;
					if(commend_data == "}"){break;}
				}
			}else if(input_file_line.substr(0,1) == ""){//NULL LINE
			}else if(input_file_line.substr(0,1) == " "){//COMMENT LINE
			}else if(input_file_line.substr(0,1) == "	"){//COMMENT LINE
			}else{
				error_msg_fn("ERROR SYNTAX",line_counter,input_file_line);
				inter_success = false;
				break;
			}
			line_counter++;
		}
		if(inter_success == true){
			std::cout << color_codes.color_success_inter_s << "\n" << "SUCCESS QUERY / " << query_counter << " QUERY" << " RAN" << color_codes.color_success_inter_f << "\n";
			std::cout << "\n" << "[OUTPUT]" << "\n\n";
			std::cout << "";
			std::cout << "";
			while(output_counter != select_vector.size()){
				std::cout << color_codes.color_output_s << "S[ "  << select_vector[output_counter] << " ]"  << color_codes.color_output_f << "\n";
				output_counter++;
			}return 1;
		}else{
			std::cout << color_codes.color_error_s << "FAIL QUERY / " << query_counter << " QUERY" << " RAN" << color_codes.color_error_f << "\n"; 
			return 0;
		}
	}else{
		error_msg_fn("ERROR FILE",0,"INPUT FILE COULD NOT BE OPENED");
		std::cout << color_codes.color_error_s << "FAIL QUERY / " << query_counter << " QUERY" << " RAN" << color_codes.color_error_f << "\n";
		return 0;
	}
}
