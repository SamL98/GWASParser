#include "csv.hpp"
#include "dbmanager.hpp"
#include <iterator>
#include <fstream>

std::istream& operator>>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}

int main()
{
    MySQLManager manager;
    //manager.createConnection();

    std::ifstream file("sample_gwas.csv");
    CSVRow row;
    while (file >> row)
    {
        std::string name = row[0];
        uint16_t chr = Utility::stringToInt(row[1]);
        uint32_t pos = Utility::stringToInt(row[2]);
//        std::cout << "Name: " << name << ", Chr: " << chr << ", Pos: " << pos << std::endl;
        uint32_t snp_id = manager.insertSNP(name, chr, pos);

        //std::cout << "Pubmed string is: " << row[3] << std::endl;
        uint32_t pubmed = Utility::stringToInt(row[3]);
        //std::cout << "Pubmed id: " << pubmed << std::endl;
        uint32_t paper_id = manager.insertPaper(pubmed);

        std::string trait = row[4];
        std::string cohort = row[6];
        uint32_t size = Utility::stringToInt(row[5]);
        double pval = Utility::stringToDouble(row[7]);
        
        manager.insertAssociation(trait, size, cohort, pval, snp_id, paper_id);
    }
    return 0;
}