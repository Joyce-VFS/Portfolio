/*
Author: Joyce V. F. Dos Santos
Course: CSCI-136
Instructor: Tong Yi
Assignment: Project 2

*/


#include "Field.hpp"
#include <iostream>
#include <cstdlib> //rand, srand
#include <ctime>

using namespace std;


Field::Field() {
    Field (7,2);
}

// for constructor
  

Field::Field(int size, int num_mines) {
    if (size <= 3) {  
        size = 7;
    }
    if (num_mines < 2) {  
        num_mines = 2;
    }
    if (num_mines >= size) { 
        num_mines = size / 3;
    }

    this->size = size;
    this->num_mines = num_mines;  

    cells = new int[size];    
    checked = new bool[size];
    
    for(int i = 0; i < size; i++) {
        cells[i] = 0;
        checked[i] = false;
    }

    int count = 0;
    srand(time(0));

    while(count < num_mines) { 
        int index = rand() % size;
        if(cells[index] == 0) {
            cells[index] = 1;
            count++;
        }
    }
}//destructor

Field:: ~Field() {
    delete[] cells;
    cells = nullptr;

    delete[] checked;
    checked = nullptr;
}

//Return a string of labels
string get_labels(int size) {
    string str;
    for (int i = 0; i < size; i++) { 
        str += "  ";
        if (i < 10)
           str += " " + std::to_string(i);
        else str += to_string(i);
        str += "  ";
    }
    str += "\n";
    return str;
}


string get_separate_line(int size) {
    string str = "+";
    for (int i = 0; i < size; i++)
        str += "-----+";
    str += "\n";
    return str;
}

 
string Field::to_string() const {
    string str = get_labels(size);
    str += get_separate_line(size);

    str += "|";
    for (int i = 0; i < size; i++) {
       if (cells[i] == 0) 
        {
           if (checked[i] == true)
               str += "  " + std::to_string(neighbor_mines(i)) +
                      "  |";
           else str += "     |";
        }
        else //needs ti have mine 
            str += "     |";

        
    }

    str += "\n";

    str += get_separate_line(size);

    return str;
}


string Field::answer_string() const {
    string str = get_labels(size); 
    str += get_separate_line(size);
    str += "|";
    for(int i = 0; i < size; i++) {// If cell has mine show asterisk
        if(cells[i] == 1) {
            str += "  *  |"; 
        }
        else {// cell does not have mine 
            str += "  " + std::to_string(neighbor_mines(i)) + "  |"; 
        }
    }
    str += "\n";
    str += get_separate_line(size);
    return str;

}


string Field::empty_layout_string() const {
  string str = get_labels(size);
  str += get_separate_line(size);

  str += "|";
  for (int i = 0; i < size; i++) {

      if (cells[i] == 0 && 
         checked[i] == true)
        str += "     |";
      else str += "     |";
  }

  str += "\n";

  str += get_separate_line(size);

  return str;
}


int Field::get_size() const {

    return size;

}


int Field::get_num_mines() const {

    return num_mines;

}

// return number of mines 
int Field:: neighbor_mines(int index) const {
    if(cells[index] == 1) { 
        return -1;
    }

    int count = 0;
    if(index > 0 && cells[index - 1] == 1) { 
        count++;
    }
    if(index + 1 < size && cells[index + 1] == 1) { 
        count++;
    }

    return count;
}



void Field::mark_checked(int index) {
    if (index >= 0 && index < size) {
        checked[index] = true;
    }

}


bool Field::is_checked(int index) const {
    if (index >= 0 && index < size) {
        return checked[index];
    }
    return false;
}


bool Field::has_mine(int index) const {
    if (index >= 0 && index < size) {
        return cells[index] == 1;
    }
    return false;
}

