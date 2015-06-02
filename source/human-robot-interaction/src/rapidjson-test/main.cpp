#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>

using namespace rapidjson;

//int main() {
//    // 1. Parse a JSON string into DOM.
//    const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
//    Document d;
//    d.Parse(json);
//
//
//    // 2. Modify it by DOM.
//    Value& s = d["stars"];
//    s.SetInt(s.GetInt() + 1);
//
//    Value array(kArrayType);
//    array.PushBack("A", d.GetAllocator()).PushBack(1, d.GetAllocator());
//    d.AddMember("ALPHA", array, d.GetAllocator());
//
//
//    // 3. Stringify the DOM
//    StringBuffer buffer;
//    Writer<StringBuffer> writer(buffer);
//    d.Accept(writer);
//
//    // Output {"project":"rapidjson","stars":11}
//    std::cout << buffer.GetString() << std::endl;
//    return 0;
//}


int main() {
    // 1. Parse a JSON string into DOM.
    const char* json = "{\"RIGHT\":[\"26.09979\",\"107.4933\",\"1000.195\"],\"LEFT\":[\"-380.2425\",\"185.61\",\"1038.522\"]}";
    Document d;
    d.Parse(json);
    
    std::cout << d.HasMember("LEFT") << std::endl;
    
    if(d.HasMember("RIGHT")){
        std::cout <<  d["RIGHT"][1u].GetString() << std::endl;
    }
    
    
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
    
    
    std::cout << buffer.GetString() << std::endl;
    return 0;
}