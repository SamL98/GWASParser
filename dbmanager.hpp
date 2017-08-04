#include <iostream>
#include <sstream>
#include <string>
#include "utility.hpp"

class MySQLManager
{
public:
    MySQLManager();
    void createConnection(mysqlpp::Connection* conn);
    bool idForEntry(std::string table, std::string col, std::string* str_val, uint32_t* int_val, short col_type, uint32_t* existingId);
    uint32_t insertSNP(std::string& name, uint16_t& chr, uint32_t& pos);
    uint32_t insertPaper(uint32_t& pubmed);
    void insertAssociation(std::string& name, uint32_t& size, std::string& cohort, double& pvalue, uint32_t& SNP, uint32_t& paper);
private:
    //mysqlpp::Connection conn;
    std::string dbname;
    std::string host;
    std::string username;
    std::string password;
};