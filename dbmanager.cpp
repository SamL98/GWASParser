#include "dbmanager.hpp"

MySQLManager::MySQLManager()
{
    host = "localhost";
    if (const char* mysql_username = std::getenv("mysql_username")) {
        std::string str(mysql_username);
        username = str;
    }
    if (const char* mysql_pass = std::getenv("mysql_pass")) {
        std::string str(mysql_pass);
        password = str;
    }
    if (const char* mysql_db = std::getenv("mysql_db")) {
        std::string str(mysql_db);
        dbname = str;
    }
}

bool MySQLManager::idForEntry(std::string table, std::string col, std::string* str_val, uint32_t* int_val, short col_type, uint32_t* existingId)
{
    mysqlpp::Connection conn = mysqlpp::Connection();
    createConnection(&conn);

    std::ostringstream qStr;
    qStr << "select id from " << table << " where " << col << "=";
    if (col_type == 0) 
        qStr << mysqlpp::quote_only << *str_val;
    else 
        qStr << *int_val;
    qStr << " limit 1";

    mysqlpp::Query q = conn.query(qStr.str());
    try
    {
        mysqlpp::StoreQueryResult res = q.store();
        if (res && res.num_rows() > 0)
        {
            *existingId = Utility::stringToInt((std::string) res[0]["id"]);
            return true;
        }
        else 
            return false;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error fetching id from " << table << " " << e.what() << std::endl;
        return false;
    }
}

void MySQLManager::createConnection(mysqlpp::Connection* conn)
{
    *conn = mysqlpp::Connection(true);
    try
    {
        conn->connect(dbname.c_str(), host.c_str(), username.c_str(), password.c_str());
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

uint32_t MySQLManager::insertSNP(std::string& name, uint16_t& chr, uint32_t& pos)
{
    uint32_t existingId = 0;
    bool exists = idForEntry("SNPs", "name", &name, NULL, 0, &existingId);
    if (existingId >= 1 || exists)
    {
        //std::cout << "Entry for SNP " << name << " already exists it is: " << existingId << std::endl << std::endl;
        return existingId;
    }
    else
        std::cout << "SNP " << name << " does not exist in database." << std::endl << std::endl;

    mysqlpp::Connection conn = mysqlpp::Connection();
    createConnection(&conn);

    std::ostringstream iQStr;
    iQStr << "insert into SNPs (name, chr, pos) values (" << mysqlpp::quote_only << name << ", " << chr << ", " << pos << ")";
    //std::cout << "Query: " << iQStr.str() << std::endl;
    mysqlpp::Query insertQ = conn.query(iQStr.str());

    try
    {
        insertQ.execute();
    }
    catch (std::exception& e)
    {
        std::cout << "Error inserting into SNPs: " << insertQ.error() << std::endl;
        return 0;
    }

    uint32_t newId;
    idForEntry("SNPs", "name", &name, NULL, 0, &newId);
    return newId;
}

uint32_t MySQLManager::insertPaper(uint32_t& pubmed)
{
    uint32_t existingId = 0;
    bool exists = idForEntry("Papers", "pubmed_id", NULL, &pubmed, 1, &existingId);
    if (existingId >= 1 || exists)
    {
        //std::cout << "Entry for paper " << pubmed << " already exists it is: " << existingId << std::endl << std::endl;
        return existingId;
    }
    else
        std::cout << "Paper " << pubmed << " does not exist in database." << std::endl << std::endl;

    mysqlpp::Connection conn = mysqlpp::Connection();
    createConnection(&conn);

    std::ostringstream iQStr;
    iQStr << "insert into Papers (pubmed_id) values (" << pubmed << ")";
    //std::cout << "Query: " << iQStr.str() << std::endl;
    mysqlpp::Query insertQ = conn.query(iQStr.str());

    try
    {
        insertQ.execute();
    }
    catch (std::exception& e)
    {
        std::cerr << "Error inserting into Paper: " << insertQ.error() << std::endl;
        return 0;
    }

    uint32_t newId = 0;
    idForEntry("Papers", "pubmed_id", NULL, &pubmed, 1, &newId);
    return newId;
}

void MySQLManager::insertAssociation(std::string& name, uint32_t& size, std::string& cohort, double& pvalue, uint32_t& SNP, uint32_t& paper)
{
    mysqlpp::Connection conn = mysqlpp::Connection();
    createConnection(&conn);

    std::ostringstream iQStr;
    iQStr << "insert into Associations (name, size, cohort, pvalue, snp, paper) values (" 
        << mysqlpp::quote_only << name << ", " 
        << size << ", " 
        << mysqlpp::quote_only << cohort << ", " 
        << pvalue << ", " 
        << SNP << ", "
        << paper << ")";
    std::cout << "Association query: " << iQStr.str() << std::endl << std::endl;
    mysqlpp::Query insertQ = conn.query(iQStr.str());
    try
    {
        insertQ.execute();
    }
    catch (std::exception& e)
    {
        std::cerr << "Error inserting into Association: " << insertQ.error() << std::endl << std::endl;
    }
}