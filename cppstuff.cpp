#include<iostream>
#include <memory>
#include <string>
#include <unordered_map>

class aclass
{
    public: 
        int a;
        aclass(int inint){
            a = inint;
        };
};

class constructordestructor
{
    public:
        int value;
        constructordestructor(int inint){
            value = inint;
            std::cout << "CONSTRUCTOR " << inint << "\n";
        }
        // copy constructor
        // make this private to prevent copies of this class
        constructordestructor(constructordestructor &t){    
            value = t.value;
            std::cout << "COPY CONSTRUCTOR " << value << "\n";
        }
        ~constructordestructor(){
            std::cout << "DESTRUCTOR " << value << "\n";
        }

};

void section_break(const std::string instring)
{
    std::cout << "\n---------------------\n" << instring << "\n---------------------\n";
}

void printvalue_copy(const constructordestructor inObject)
{
    std::cout << "printvalue_copy " << inObject.value << "\n";
}
void printvalue_ref(const constructordestructor* inObject)
{
    std::cout << "printvalue_ref " << inObject->value << "\n";
}

void printvalue_smart(const std::shared_ptr<constructordestructor> inObject)
{
    std::cout << "printvalue_smart " << inObject->value << "\n";
}

void printvalue_unique(const std::unique_ptr<constructordestructor> inObject)
{
    std::cout << "printvalue_unique " << inObject->value << "\n";
}


int main(){
    std::cout << "AAA\n";
    int x = 2;
    aclass test(x);
    std::cout << test.a << "\n";


    section_break("UNORDERED MAP");    
    std::unordered_map<std::string, aclass> amap;
    amap.insert(std::make_pair("one", aclass(1)));
    amap.insert(std::make_pair("two", test));

    if(amap.find("one") != amap.end())
    {
        auto result = amap.find("one");
        std::cout << "FOUND " << result->second.a << "\n";

    }
    else
    {
        std::cout<< "NOT FOUND\n";
    }

    // END: unordered mnap
    //-----------------------------------------------------
    // AUTO keyword
    section_break("AUTO");
    std::cout << "Iterating across map of " << amap.size() << " elements...\n";
    for(auto it = amap.begin(); it != amap.end(); it++)
        std::cout << it->first << " " << it->second.a  << "\n";

    auto autoexample = amap.begin()->second.a;
    std:: cout << "First element = " << autoexample << "\n";
    // END: AUTO keyword
    //-----------------------------------------------------
    // Constructor/destructor/copy constructor

    section_break("CONSTRUCTOR/DESTRUCTOR");
    constructordestructor a_thing(5);
    printvalue_copy(a_thing);
    printvalue_ref(&a_thing);

    section_break("SMART POINTER");

    std::shared_ptr<constructordestructor> pshared = std::make_shared<constructordestructor>(6);
    //std::shared_ptr<constructordestructor> pshared = std::make_shared<constructordestructor>(a_thing);
    std::unique_ptr<constructordestructor> punique = std::make_unique<constructordestructor>(7);
    printvalue_smart(pshared);
    printvalue_unique(std::move(punique)); // this is how you need to pass a reference to unique_ptr...by moving it
    // punique destructor has now been called, because we moved it. it is now deleted, we can't print its value anymore
    // it didn't call another constructor. maybe it called a copy constructor? not sure how to confirm this
    if(punique)
        std::cout << punique->value << "\n";
    else
        std::cout << "This pointer has been deleted!\n";    

    
    return 0;
}