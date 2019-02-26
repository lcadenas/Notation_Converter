#ifndef NOTATIONCONVERTER_H
#define NOTATIONCONVERTER_H

//#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;
#include "NotationConverterInterface.hpp"

typedef std::string Elem;
class DNode
{
    private:
        Elem element;                                               //variable to store the value
        DNode* next;                                                //next item in the list
        DNode* prev;                                                //previous item in the list  
    public:
        DNode(){element = " "; next = NULL; prev = NULL;}          //constructor 
    friend class NotationConverter;
};

class NotationConverter : public NotationConverterInterface
{
    friend class DNode;
    private:
        DNode* header;                                              //pointer to the first item in the list
        DNode* trailer;                                             //pointer to the last element in the list
        int n;                                                      //size of the list
    public:
        NotationConverter();                                        //constructor
        ~NotationConverter();                                       //destructor
        void valid_input(const Elem& e);                            //function to check whether the input string is valid     
        bool empty() const;                                         //function to check if the list is empty
        const Elem& front() const;                                  //function to get the first item of the list
        const Elem& back() const;                                   //function to get the last item of the list
        void insertFront(const Elem& e);                            //funtion to insert items at the front of the list
        void removeFront();                                         //function to remove items at the front of the list
        virtual std::string postfixToInfix(std::string inStr);      //function to convert a string from postfix to infix
        virtual std::string postfixToPrefix(std::string inStr);     //function to convert a string from postfix to prefix
        virtual std::string infixToPostfix(std::string inStr);      //function to convert a string from infix to postfix     
        virtual std::string infixToPrefix(std::string inStr);       //function to convert a string from infix to prefix
        virtual std::string prefixToInfix(std::string inStr);       //function to convert a string from prefix to infix
        virtual std::string prefixToPostfix(std::string inStr);     //function to convert a string from prefix to postfix
};

#endif