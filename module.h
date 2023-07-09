#ifndef MODULE_H
#define MODULE_H
typedef struct Record {
    int id;
    char state_car_num[9];
    char mark[21];
    int graduation_year;
    int car_mileage;
    char vin_code[21];
    int status;
    struct Record* next;

} Record;

int print_cars_by_year_and_mileage(const Record* head, int min_year, int max_year, int min_mileage, int max_mileage);
int print_cars_by_brand_and_region(const Record* head, const char* brand, const char* region);
int change_config_value(const char* param, const char* new_value);
int convert_records_to_csv();
int save_list_to_file(Record** head);
int check_record_exists(Record** head, int id);
int createConfigFile();
int checkLicenseKey();
int createDatabaseFile();
int view_records(Record** head);
int add_record(Record** head, int id, char* state_car_num, char* mark, int graduation_year, int car_mileage, char* vin_code, int status);
int del_record(Record** head, int id);
int changing_record(Record** head, int id, char* state_car_num, char* mark, int graduation_year, int car_mileage, char* vin_code, int status);

#endif /*MODULE_H*/
