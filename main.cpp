#include "xmlreader.h"
#include <ctime>
#include <iostream>
#include <dirent.h>
#include <vector>
#include <string>

int main()
{
    int st = clock();
    std::vector<std::string> listFileNameIn;
    std::vector<std::string> listFileNameTemp;
    DIR *dirIn;
    DIR *dirTemp;
    struct dirent *ent;
    if ((dirIn = opendir ("./in/")) != NULL)
    {
        while ((ent = readdir (dirIn)) != NULL)
        {
            if((ent->d_name[0] == '.' && ent->d_name[1] == 0) || (ent->d_name[0] == '.' && ent->d_name[1] == '.'))
                continue;
            listFileNameIn.push_back("./in/" + static_cast<std::string>(ent->d_name));
        }
        closedir (dirIn);
    }
    else
    {
        perror ("");
        return 1;
    }
    if((dirTemp = opendir ("./templates/")) != NULL)
    {
        while ((ent = readdir (dirTemp)) != NULL)
        {
            if((ent->d_name[0] == '.' && ent->d_name[1] == 0) || (ent->d_name[0] == '.' && ent->d_name[1] == '.'))
                continue;
            listFileNameTemp.push_back("./templates/" + static_cast<std::string>(ent->d_name));
        }
        closedir (dirTemp);
    }
    else
    {
        perror ("");
        return 1;
    }

    std::string header = "";
    int cntOtch = 0;
    for(const std::string &fileName : listFileNameIn)
    {
        XmlReader *xmlIn = new XmlReader(fileName.c_str());
        bool templ = false;
        if(xmlIn->getListNodes()[0]->getName() != "?xml")
        {
            std::cout << "Это не XML проверьте структуру файла "  << fileName << std::endl;
            delete xmlIn;
            continue;
        }
        else if(xmlIn->getListNodes()[1]->getName() != "report")
        {
            std::cout << "Это не отчет проверьте структуру файла "  << fileName << std::endl;
            delete xmlIn;
            continue;
        }
        for(const std::string &tempName : listFileNameTemp)
        {
            XmlReader *xmlTemp = new XmlReader(tempName.c_str());
            if(xmlTemp->getListNodes()[0]->getName() != "?xml")
            {
                std::cout << "Это не XML проверьте структуру файла "  << tempName << std::endl;
                templ = false;
                delete xmlTemp;
                continue;
            }
            else if(xmlTemp->getListNodes()[1]->getName() != "metaForm")
            {
                std::cout << "Это не шаблон проверьте структуру файла "  << tempName << std::endl;
                templ = false;
                delete  xmlTemp;
                continue;
            }
            else if(xmlTemp->getNodeByName("metaForm")[0]->getValueByAtributeName("code") == xmlIn->getNodeByName("report")[0]->getValueByAtributeName("code")
                    && xmlTemp->getNodeByName("metaForm")[0]->getValueByAtributeName("shifr") == xmlIn->getNodeByName("report")[0]->getValueByAtributeName("shifr")
                    && xmlTemp->getNodeByName("metaForm")[0]->getValueByAtributeName("idf") == xmlIn->getNodeByName("report")[0]->getValueByAtributeName("form"))
            {
                if(xmlTemp->getNodeByName("metaForm")[0]->getValueByAtributeName("version") != xmlIn->getNodeByName("report")[0]->getValueByAtributeName("version")
                                    && xmlTemp->getNodeByName("metaForm")[0]->getValueByAtributeName("format-version") != xmlIn->getNodeByName("report")[0]->getValueByAtributeName("format-version"))
                {
                    std::cout << "Версии шаблонов не совпадают обновите шаблон в отчете или шаблон в папке teplates.("  << fileName << ")" << std::endl;
                    templ = true;
                    delete xmlTemp;
                    continue;
                }
                else
                {
                    //// тут работаем с данными для конвертации
                    ++cntOtch;
                    if(header.empty())
                    {
                        //// нужно посчитать период временно сейчас
                        std::string periodStart = "0101";
                        std::string periodEnd = "1231";
                        header += xmlIn->getNodeByName("report")[0]->getValueByAtributeName("year")
                            + periodStart
                            + xmlIn->getNodeByName("report")[0]->getValueByAtributeName("year")
                            + periodEnd
                            + "0000(())),==10000000000000\n";
                    }
                    std::string writeRow;
                    for(const Node *sectIn : xmlIn->getNodeByName("section"))
                    {
                        //create rows in MKT
                    }
                    std::cout << writeRow << std::endl;
                    ////////////////////////////////////////
                    templ = true;
                    delete xmlTemp;
                    break;
                }
            }
            templ = false;
            delete xmlTemp;
        }
        if(!templ)
            std::cout << "Не нашлось подходящего шаблона для обработки отчета в папке template.(" << fileName << ")" << std::endl;


        //clear memory

        delete xmlIn;
    }

    //std::cout << std::endl << "~~~" << header << "~~~" << std::endl;


    int ed = clock();
    std::cout << "Elapsed time: " << double(ed-st)/CLOCKS_PER_SEC << std::endl;
    return 0;
}
