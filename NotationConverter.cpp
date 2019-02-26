#include "NotationConverter.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

//Constructor to create first and last node
NotationConverter::NotationConverter()
{
    header = new DNode;             
    trailer = new DNode;            
    header->next = trailer;         
    trailer->prev = header;
}

//function to check if the list is empty
bool NotationConverter::empty() const
{
    return (header == nullptr);
}

//function to get the first item of the list
const Elem& NotationConverter::front() const
{
    return header->next->element;
}

//function to get the last item of the list
const Elem& NotationConverter::back() const
{
    return trailer->prev->element;
}

//funtion to insert items at the front of the list
void NotationConverter::insertFront(const Elem& e)
{
    if(empty())                 //check whether the list is empty and create new node
    {
        DNode* u = new DNode;
        u-> element = e;
        u->prev = nullptr;
        u->next = nullptr;
        header = u;
        trailer = u;
    }
        
    else                       //create new node if the list is not empty
    {
        DNode* u = new DNode;
        u->element = e;
        u->next = header;
        u->prev = nullptr;
        header->prev = u;
        header = u;
    }    
    n++;          //increase size of the list
}

//function to remove items at the front of the list
void NotationConverter::removeFront()
{
    DNode* u = header;
    if(u->next == nullptr && u->prev == nullptr)  //check whether the list is empty and remove item
    {
        header = nullptr;
        trailer = nullptr;
        delete u;
    }
        
    else                            //remove item if the list is not empty
    {
        header = u->next;
        header->prev = nullptr;
        delete u;
    }
    n--;                           //decrease size of the list
}

//destructor to deallocate memory
NotationConverter::~NotationConverter()
{
    while(!empty())
        removeFront();
    delete header;
    delete trailer;
}

//function to check whether the input string is valid
void NotationConverter::valid_input(const Elem& e)
{ 
    for(unsigned i = 0; i < e.size(); i++)          //loop to read the string
    {
        if(e[i] < 'A' || (e[i] > 'Z' && e[i] < 'a') || e[i] > 'z')      //check for non letter characters
        {
            if(e[i] !='*' && e[i] != '/' && e[i] != '+' && e[i] != '-' && e[i] != '(' && e[i] != ')' && e[i] != ' ') //check for non operations, parenthesis, and space characters
                throw std::runtime_error("Invalid input"); 
        }    
    }
}

//function to convert a string from infix to postfix
std::string NotationConverter::infixToPostfix(std::string inStr)
{
    valid_input(inStr);                 //check for valid input string
    std:: string outpost;               //variable to store final string
    std::string sTemp;                  //variable to convert characters to string
    
    for(unsigned i = 0; i < inStr.size(); i++)          //loop to read the input string
    {
        sTemp = inStr[i];
        
        if(inStr[i] == '(' || inStr[i] == '*' || inStr[i] == '/')       //check for precedence operand and add to the list
        {
            insertFront(sTemp);
        }

        else if(inStr[i] == '+' || inStr[i] == '-')                 //check for operands and add to the list
        {
            if((header->element)[0] == '*' || (header->element)[0] == '/')      //check for precedent operands and remove them from the list
            {
                outpost = outpost + header->element + " ";
                removeFront();
            }
            insertFront(sTemp);             
        }

        else if(inStr[i] == ')')        //check for closing parethesis
        {
            while((header->element)[0] != '(' && !empty())  //loop to find opened parenthesis, store data on the final string, and remove from the list 
            {
                outpost = outpost + header->element + " ";
                removeFront(); 
            }
            if(!empty())                //check if the list is not empty and remove item from the list
            {
                removeFront();
            }
        }
            
        else if((inStr[i] >= 'A' && inStr[i]<= 'Z') || (inStr[i]>= 'a' && inStr[i]<= 'z'))    //check for letter character and strore on the final string
        {
            outpost = outpost + inStr[i] + " ";
        }

        else if((i == inStr.size()-1) && !empty())      //check for remaining characters, store them on the final string, and remove items from the list
        {
            while(!empty())
            {
                outpost = outpost + header->element + " ";
                removeFront();
            }
        }

         else if(inStr[i] != ' ')           //look for errors
        {
            throw std::runtime_error("Empty string");
        }
    }
    return outpost;           //return the final string
}

//function to convert a string from infix to prefix
std::string NotationConverter::infixToPrefix(std::string inStr)
{
    valid_input(inStr);             //check for valid input string
    std:: string outpref;           //variable to store the string
    std::string sTemp;              //variable to convert characters to string

    for(unsigned i = 0; i < inStr.size(); i++)  //loop to read each character of the input string and add to the list
    {
        sTemp = inStr[i];
        insertFront(sTemp);
    }

    while(!empty())         //look fot parenthesis, strore data on the string, and remove from the list
    {
        if(header->element[0] == '(')
        {
           outpref = outpref + ") ";
            removeFront(); 
        }

        else if(header->element[0] == ')')
        {
           outpref = outpref + "( ";
            removeFront();
        }

        else
        {
            outpref = outpref + header->element + " " ;
            removeFront(); 
        }
    }

    std::string temp;               //variable to store the string backwards
    temp = infixToPostfix(outpref);     //convert the string to postfix
    std::string fOutprefix;             //variable to store the final string

    for(unsigned i = 0; i < temp.size(); i++)   //loop to read the converted string and add to the list
    {
        sTemp = temp[i];
        insertFront(sTemp);
    }

    while(!empty())         //loop to store data to the final string and remove from the list
    {
        fOutprefix = fOutprefix + header->element;
        removeFront();
    }

    return fOutprefix;          //return the final string
}

//function to convert a string from prefix to infix
std::string NotationConverter::prefixToInfix(std::string inStr)
{
    valid_input(inStr);                     //check for valid input string
    std:: string outInfix;                  //variable to store the string backward
    std::string sTemp;                      //variable to convert characters to string

    for(unsigned i = 0; i < inStr.size(); i++)      //loop to read each character of the input string and add to the list
    {
        sTemp = inStr[i];
        insertFront(sTemp);
    }

    while(!empty())                                 //loop to copy the list backward to the string
    {
        outInfix = outInfix + header->element;
        removeFront();
    }

    std::string temp1, temp2, fOutInfix;            //variables to store the final string and add/remove front the list
    
    for(unsigned i = 0; i < outInfix.size(); i++)       //loop to read each character of the string
    {
        if((outInfix[i] >= 'A' && outInfix[i] <= 'Z') || (outInfix[i] >= 'a' && outInfix[i] <= 'z'))    //check for letters character and add to the list
        {
            fOutInfix = outInfix[i];
            insertFront(fOutInfix);            
        }

        else if(outInfix[i] == '*' || outInfix[i] == '/' || outInfix[i] == '-' || outInfix[i] == '+')   //check for operation, remove from the list, and add new items
        {
            temp1 =header->element + " ";
            removeFront();
            temp2 = header->element;
            removeFront();
            sTemp = "(" + temp1 + outInfix[i] + " " + temp2 + ")";
            insertFront(sTemp);
        }
    }

    fOutInfix = header->element;            //store item at the front of the list on the final sting
    removeFront();                          //remove item on the front of the list
    return fOutInfix;                       //return the final string
}

//function to convert a string from prefix to postfix
std::string NotationConverter::postfixToInfix(std::string inStr)
{
    valid_input(inStr);                                 //check for valid input string
    std:: string postInfix, fPostInfix;                 //variables to store the final string
    std::string sTemp, temp1, temp2;                    //variables to store characters and add/remove front the list

    for(unsigned i = 0; i < inStr.size(); i++)          //loop to read each character of the string
    {
        if((inStr[i] >= 'A' && inStr[i] <= 'Z') || (inStr[i] >= 'a' && inStr[i] <= 'z'))     //check for letters character and add to the list
        {
            sTemp = inStr[i];               
            insertFront(sTemp);             
        }

        else if(inStr[i] == '/' || inStr[i] == '*' || inStr[i] == '+' || inStr[i] == '-')   //check for operation, remove from the list, and add new items
        {
            temp1 = header->element;
            removeFront();
            temp2 = header->element + " ";
            removeFront();
            postInfix = "(" + temp2 + inStr[i] + " " + temp1 + ")";
            insertFront(postInfix); 
        }
    }

    fPostInfix = header->element;           //store item at the front of the list on the final sting 
    removeFront();                          //remove item on the front of the list
    return fPostInfix;                      //return the final string
}

//function to convert a string from prefix to postfix
std::string NotationConverter::prefixToPostfix(std::string inStr)
{
    valid_input(inStr);                             //check for valid input string
    return infixToPostfix(prefixToInfix(inStr));    //convert prefix to infix and then infix to postfix

}

//function to convert a string from postfix to prefix
std::string NotationConverter::postfixToPrefix(std::string inStr)
{
    valid_input(inStr);                                 //check for valid input string
    return infixToPrefix(postfixToInfix(inStr));        //convert postfix to infix and then infix to prefix

}