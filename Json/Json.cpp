#include <iostream>
#include "json/json.h"
#include <fstream>
#include <map>

//g++ Json.cpp -o Json -ljson

using namespace std;

void parseStrToJson()
{
    const char *str = \
        "{\"Teacher\":\"Timi\", \"Student\":\"Lucy\", \"Age\":18}";
    Json::Value value;
    Json::Reader reader;

    if(reader.parse(str, value)){
        string Teacher = value["Teacher"].asString();
        string Student = value["Student"].asString();
        int Age = value["Age"].asInt();

        cout << "My teacher name is \"" + Teacher + "\" I am a \"" + Student + \
            "\" " + "My age is \"" <<  Age <<  "\"" << endl;
    }
}

void parseJsonFromFileToStr()
{
    Json::Reader reader;
    Json::Value root;
    char filename[] = "./test.txt";

    std::ifstream is;
    is.open( filename, std::ios::in );
    cout << "file info is : " << is << endl;
    if( reader.parse(is, root) ) {
        std::string uploadid;
        if( !root["files"].isNull() )
            uploadid = root["uploadid"].asString();
        uploadid = root.get("uploadid", "null").asString();
        cout << "uploadid -- = " << uploadid << endl;
        string code = root["code"].asString();
        string msg = root["msg"].asString();

        cout << "first code is \"" + code + "\" first msg is \"" + msg + "\""<< endl;

        int file_size = root["files"].size();
        cout << "file_size is = " << file_size << endl;

        for(int i = 0; i < file_size; ++i) {
            string filename = root["files"][i]["filename"].asString();
            cout << "file name is = " + filename << endl;
            Json::Value val_image = root["files"][i]["images"];
            int image_size = val_image.size();
            cout << "image_size is = " << image_size << endl;
            for( int j = 0; j < image_size; ++j ) {
                std::string type = val_image[j]["type"].asString();
                std::string url = val_image[j]["url"].asString();
            }
        }
    }
    is.close();
}

void vecMapToJson()
{
    vector< map<string, string> > tempVec;
    map<string, string> tempMap1;
    map<string, string> tempMap2;
    tempMap1.insert(make_pair("Name", "Xiaoming"));
    tempMap1.insert(make_pair("Age", "18"));
    tempMap1.insert(make_pair("Nation", "Chinese"));
    tempMap2.insert(make_pair("Name", "Tom"));
    tempMap2.insert(make_pair("Age", "19"));
    tempMap2.insert(make_pair("Nation", "American"));
    tempVec.push_back(tempMap1);
    tempVec.push_back(tempMap2);
    
    Json::Value root;
    vector< map<string, string> >::const_iterator itVec = tempVec.begin();
    map<string, string>::const_iterator itMap;

    for(; itVec != tempVec.end(); itVec++) {
        Json::Value value1;
        itMap = itVec->begin();
        for(; itMap != itVec->end(); itMap++) {
            value1[itMap->first] = itMap->second;
        }
        root["xxxx"].append(value1);
    }

    Json::FastWriter fast_writer;
    cout << "Fast Writer = " << fast_writer.write(root) << endl;

}

void vecMapToJson_1()
{
    //root["key_array"].append("array_string");  新建一个 Key（名为：key_array），类型为数组，对第一个元素赋值为字符串："array_string"。
    //root["key_array"].append(1234);           为数组 key_array 赋值，对第二个元素赋值为：1234。
    map< string, vector< map<string, string> > > tempMap;
    vector< map<string, string> > tempVec1;
    vector< map<string, string> > tempVec2;
    map<string, string> tempMap1;
    map<string, string> tempMap2;
    map<string, string> tempMap3;
    tempMap1.insert(make_pair("Name", "Xiaoming"));
    tempMap1.insert(make_pair("Age", "18"));
    tempMap1.insert(make_pair("Nation", "Chinese"));
    tempMap2.insert(make_pair("Name", "Tom"));
    tempMap2.insert(make_pair("Age", "19"));
    tempMap2.insert(make_pair("Nation", "American"));
    tempMap3.insert(make_pair("Name", "SanBen"));
    tempMap3.insert(make_pair("Age", "20"));
    tempMap3.insert(make_pair("Nation", "Japan"));
    tempVec1.push_back(tempMap1);
    tempVec1.push_back(tempMap2);
    tempVec2.push_back(tempMap3);

    tempMap.insert(make_pair("first", tempVec1));
    tempMap.insert(make_pair("second", tempVec2));
    
    Json::Value root;

    map< string, vector< map<string, string> > >::const_iterator itMap;
    map<string, string>::const_iterator itMap1;
    //第一层map
    for(itMap = tempMap.begin(); itMap != tempMap.end(); itMap++) {
        Json::Value value1;
        vector< map<string, string> >::const_iterator itVec1;
        //第二次vector
        for(itVec1 = itMap->second.begin(); itVec1 != itMap->second.end(); itVec1++){
            Json::Value value2;
            map<string, string>::const_iterator itMap1 = itVec1->begin();
            //第三层map
            for(; itMap1 != itVec1->end(); itMap1++) {
                value2[itMap1->first] = itMap1->second;
            }
            value1.append(value2);
        }
        root["fhxx"].append(value1);
    }


    Json::FastWriter fast_writer;
    cout << "Fast Writer = " << fast_writer.write(root) << endl;

}

void jsonToVecMap()
{
    string strJson = "{\"name\":\"tom\",\"sex\":\"男\",\"age\":\"24\",\"friends\":[{\"name\":\"chen\",\"sex\":\"男\"},{\"name\":\"li\",\"sex\":\"女\"}]}";
    Json::Value value;
    Json::Reader reader;
    bool error = reader.parse(strJson, value);
    if( value.isArray() ) {
        cout << "---value is array ----" << endl;

    } else if (value.isObject()){
        cout << "---value is object ----" << endl;
        cout << "name is = " + value["name"].asString() << endl;
        cout << "sex is = " + value["sex"].asString() << endl;
        cout << "age is = " + value["age"].asString() << endl;

        if(value["friends"].isNull()) { 
            cout << "friends is Null Array" << endl;
        }

        Json::Value value1 = value["friends"];
        if( value1.isArray() ) {
            cout << "--- value 1 --- is array " << endl;
            for(int i = 0; i < (int)value1.size(); i++) {
                Json::Value objVal = value1[i];
                Json::Value::Members members = objVal.getMemberNames();
                for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it) {
                    cout << "*it = " << *it << "  objVal[*it]  = " << objVal[*it].asString() << endl;
                }//end for loop members
                
            }//end for loop value1.size()

        }//end for value1.isArray

    }
}
int main()
{
    parseStrToJson();
    parseJsonFromFileToStr();
    vecMapToJson();
    vecMapToJson_1();
    jsonToVecMap();
    const char* str =
        "{\"praenomen\":\"Gaius\",\"nomen\":\"Julius\",\"cognomen\":\"Caezar\","
                "\"born\":-100,\"died\":-44}";

    Json::Value root;
    Json::Reader reader;

    if(reader.parse(str, root))
    {
        string praenomen = root["praenomen"].asString();
        string nomen = root["nomen"].asString();
        string cognomen = root["cognomen"].asString();
        int born = root["born"].asInt();
        int died = root["died"].asInt();

        cout << praenomen + " " + nomen + " " + cognomen \
                 << " was born in year " << born \
                 << ", died in year " << died << endl;
    }
    return 0;
}
