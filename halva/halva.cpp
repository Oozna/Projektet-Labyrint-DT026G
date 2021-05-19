// halva.cpp : This file contains the 'main' function. Program execution begins
// and ends there.
//

#include "Maze.h"

int main() {
  srand(time(NULL));
  bool running = true;

  while (running) { // loop som ser till att programmet inte avslutas innan
                    // användaren vill det

    int answer;
    bool check = true;
    while (check) { // felkontroll på inmatningen
      std::cout << "Welcome to Eric's Maze generator, write one of the numbers "
                   "below to continue"
                << std::endl;
      std::cout << "1. Create a maze" << std::endl;
      std::cout << "2. Create a custom sized maze" << std::endl;
      std::cout << "3. Exit the program." << std::endl;
      std::cin >> answer;
      if (answer > 3 || answer < 1 || std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Please enter one of the shown Intergers" << std::endl;

      } else {
        check = false;
      }
    }
    switch (answer) { // Om de väljer en standard maze, kallar
                      // defaultkonstruktorn 11x11
    case 1: {
      int case1answer;
      Maze g;
      g.generate();
      g.print();
      bool check = true;
      while (check) {
        std::cout << "Do you want to solve the maze?"
                  << std::endl // frågar om de vill skriva ut lösningen på
                               // skärmen med felkontroll
                  << "1. Yes" << std::endl
                  << "2. No" << std::endl;

        std::cin >> case1answer;
        if (case1answer < 1 || case1answer > 2 || std::cin.fail()) {
          std::cin.clear();
          std::cin.ignore(1000, '\n');
          std::cout << "Please enter one of the shown Intergers" << std::endl;

        } else {
          check = false;
        }
      }
      if (case1answer == 1) {
        g.solve();
        g.print();
      }
      break;
    }
    case 2: {
      int rows, columns;
      check = true;

      while (check) { //Felkontroll antal rader
        std::cout << "How many rows do you want the maze to have. (Odd "
                     "numbers 3 or higher only)"
                  << std::endl;
        std::cin >> rows;
        if (rows < 3 || !(rows % 2) || std::cin.fail()) {
          std::cin.clear();
          std::cin.ignore(1000, '\n');
          std::cout << "Please enter a valid Interger" << std::endl;

        } else {
          check = false;
        }
      }
      check = true;
      while (check) {  //Felkontroll antal kolumner
        std::cout << "How many columns do you want the maze to have. (Odd "
                     "numbers 3 or higher only)"
                  << std::endl;
        std::cin >> columns;
        if (columns < 3 || !(columns % 2) || std::cin.fail()) {
          std::cin.clear();
          std::cin.ignore(1000, '\n');
          std::cout << "Please enter a valid Interger" << std::endl;

        } else {
          check = false;
        }
      }
      Maze g(rows, columns); //skapa labyrinten med antalet rader och kolumner som specifierat
      g.generate();
      g.print();
      int case2answer;
      bool check = true;

      while (check) {
        std::cout << "Do you want to solve the maze?"
                  << std::endl // frågar om de vill skriva ut lösningen på
                               // skärmen med felkontroll
                  << "1. Yes" << std::endl
                  << "2. No" << std::endl;

        std::cin >> case2answer;
        if (case2answer < 1 || case2answer > 2 || std::cin.fail()) {
          std::cin.clear();
          std::cin.ignore(1000, '\n');
          std::cout << "Please enter one of the shown Intergers" << std::endl;

        } else {
          check = false;
        }
      }
     
      if (case2answer == 1) { // om svaret 1 skriver ut annars endast break
        g.solve();
        g.print();
        std::cout << std::endl;
      }
      break;
    }
    case 3: {
      std::cout << "Alright have a good day!" << std::endl;
      running = false;
      break;
    }
    default:
      break;
    }
  }
  return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add
//   Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project
//   and select the .sln file
