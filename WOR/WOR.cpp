
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <cstdio>
#include <conio.h>
#include "windows.h" 


std::string NowToString()
{
    std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
    time_t t = std::chrono::system_clock::to_time_t(p);
    char str[26];
    ctime_s(str, sizeof str, &t);
    return str;
}


class Paper
{
    std::string data;
    std::string timestamp;

public:
    Paper(std::string poem) : data(poem) {
      
        timestamp = NowToString();
        
    }

    std::string getData() const
    {
        return data;
    }

    std::string getTimeStamp() const
    {
        return timestamp;
    }


};


class Robot
{
    std::string currentPoem = "";
    uint8_t poemSize;

public:

    Robot(uint8_t size = 100) : poemSize(size)
    {
       srand(std::time(NULL));
    }

    void createPoem()
    {
        currentPoem = "";
        for (int i = 0; i < poemSize; i++)
        {
            currentPoem.push_back((char)(rand() % 75 + 48));
        }
               
    }

    void readPaper(std::unique_ptr<Paper> poem)
    {
        currentPoem = poem->getData();
    }

    std::unique_ptr<Paper> printPaper()
    {
        if (currentPoem.empty())
            return nullptr;
        return std::make_unique<Paper>(currentPoem);
    }

    std::string recitePoem()
    {
        std::cout << "Here is my poem: \n" << currentPoem << std::endl;
        return currentPoem;
    }


};

class Mechanic {
public:
    std::vector<std::unique_ptr<Paper>> book;
    Robot* robot;

    Mechanic(Robot* _robot) : robot(_robot) {}

    void getPaper()
    {
        book.push_back(robot->printPaper());
    }

    void insertPaper()
    {
        robot->readPaper(std::move(book.back()));

        book.pop_back();
    }

    void printLog()
    {
        for (auto& poem : book)
        {

            std::cout << "LOG : " << (*poem).getData().substr(0, 4) << " on " << (*poem).getTimeStamp() << std::endl;
        }





    }

};


int main()
{
    Robot* robot_ptr = new Robot;
    Robot* robot_ptr2 = new Robot(25);
    Mechanic mechanic(robot_ptr);
    Mechanic mechanic2(robot_ptr2);
    int i = 0;

    bool stop = false;
    while (stop == false)
    {

       
        stop = _kbhit();
        std::cout << " We start loop number " << i<< std::endl;
        robot_ptr->createPoem();
        
        robot_ptr2->createPoem();
        
        if (i % 2 == 1)
        {
            mechanic.getPaper();
            if (i % 5 == 1) { 
                std::cout << " I am first robot "<<std::endl;
                mechanic.insertPaper(); 
                robot_ptr->recitePoem(); }
            
        }
        else
        {
           
            mechanic2.getPaper();
            if (i % 5 == 1) { std::cout << " I am second robot " << std::endl; mechanic2.insertPaper(); robot_ptr2->recitePoem(); }
        }
        if (i % 10 == 1)
        {
            std::cout << " Logs I mechanic " << std::endl;
            mechanic.printLog();
            std::cout << " Logs II mechanic " << std::endl;

            mechanic2.printLog();

        }

        Sleep(1500);

        i++;
    }


    delete robot_ptr;
    delete robot_ptr2;
    return 0;
}