/*
Author: JOYCE VIEIRA FERREIRA DOS SANTOS
Course: CSCI-135
Instructor: Tong Yi
Assignment: Project 2, Task D

Description: TASK D
*/

#include "Game.hpp"
#include <iostream>
using namespace std;

//TODO: define default constructor of Game class.
Game:: Game(): area(7,2) {
}

//TODO: define non-default constructor of Game class.
Game:: Game(int size, int num_mines): area(size, num_mines){
}

//TODO: Ensure users to enter a cell index in [0, size).
//      return the input number.
//ensure to enter a valid index num whose cell is not checked yet, return num.
//Hint: which method of area to call to find out whether a cell in it is checked or not?
//Here are the steps.
//First, print "Please choose a cell (the first starts from 0): "
//and input an int for num from console.
//Keep asking for input num as long as num is 
//not in (0, size] or the corresponding cell is
//checked, where size is the capacity of data member area.
//begin
//    If num is out of range, that is, not in [0, size), 
//    prompt "Enter an integer in [0, size-1]: ",
//    replace size-1 by the actual value of 
//    given parameter size in this method.
//    Otherwise, the cell must be checked (why??), prompt 
//    "Cell … is already chosen. Please re-enter: ", 
//    where … is the value of num
//
//    Re-enter num
//end
//return num
int Game::input() const {
    int num;
    cout << "Please choose a cell (the first starts from 0): ";
    cin >> num;
    // for loop 
    while (true) { 
        if (!(num >= 0 && num <= this->area.get_size() - 1)) { 
            cout << "Enter an integer in [0, " << area.get_size()-1 << "]: "; // re-enter
            cin >> num;
            continue; // checks once again
        }

        if(this->area.is_checked(num)) { // if cell is already marked
            cout << "Cell " << num << "is already chosen. Please re-enter: "; // re-enter num
            cin >> num;
            continue; // checks once again
        }
      
        break;
    }
    return num;
}
//TODO: code to show how to play a game. 
//Star with an empty layout of field,
//keep choosing a valid index for an unchecked cell 
//until one of the following happens.
//(a) A cell with a mine is chosen, 
//    in that case, print "Mine explodes! Game ends."
//(b) All cells without mines are found out, 
//    in that case, print 
//    "Congratulations! Find out all the cells without mines."
//(c) After the game, print the layout of fields 
//    where mines are marked as * 
//    and nonmines are marked by its number of neighbor(s).
// playing minesweeper
void Game::play() {
  int round = 1;
  int check = 0; 

  while(true) {
    // prints the field
    cout << area.to_string() << endl; 
    cout << "Round " << round << ": ";
    //ask user to input cell
    int num = input(); 
    area.mark_checked(num); 
    // cout << area.to_string() << endl; // prints current field
    check++; 
    // if cell chosen has a mine
    if(area.has_mine(num)) { 
      cout << "Mine explodes! Game ends." << endl;
      break;
    }
    //after all cells are marked off
    else if(check == area.get_size() - area.get_num_mines()) { 
      cout << area.to_string() << endl;
      cout << "Congratulations! Find out all the cells without mines." << endl;
      break;
    }

    area.mark_checked(num); 
    round++;
  }
  cout <<"\nThe answer is " << endl;
  // prints the answer
  cout << area.answer_string(); 

}