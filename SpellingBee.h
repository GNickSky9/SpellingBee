#ifndef SPELLINGBEE_H_INCLUDED
#define SPELLINGBEE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <time.h>

#ifdef _WIN32
   #include <windows.h>
#elif __linux__ || _linux || __unix__
   #include <unistd.h>
#else
    #include <unistd.h>
   //std::cout << "Invalid Operating System!" << std::endl;
#endif

enum Titles {Good,Excellent,Genius,NoTitle};
const std::string TitleName[] = {"Good","Excellent","Genius","No Title Earned Yet"};

class GameClass
{
      private:
            std::string user_name;
            Titles title;
            int points;
            std::vector<std::string> user_words;
            std::vector<std::string> valid_user_words;
            static std::vector<std::string> words;
            static std::vector<std::string> letter_sets;
            static std::vector<int> sets_word_size;
            void len_error();
            void invalid_letter();
            void center_error();
            void invalid_word();
            void duplicate_word();
      public:
            GameClass();
            GameClass(std::string );

            void set_name(std::string );
            void set_title(Titles );
            void set_points(int );
            void set_user_word(std::string );
            void set_valid_user_word(std::string );

            Titles get_title(){return title;}
            std::string get_name(){return user_name;}
            int get_points(){return points;}
            int get_valid_user_words(){return valid_user_words.size();}

            void check_if_valid_length(const std::string &, bool &);
            void check_if_valid_letters(const std::string &, bool &, int);
            void check_if_valid_word(const std::string &, bool &);
            void check_for_duplicate(const std::string &, bool &);
            void check_if_win(int &,bool &,int element);

            void point_system(int);
            void reset_data();

            static void fill_words(std::ifstream &);
            static void fill_letter_sets(std::ifstream &);
            static void fill_sets_word_size(std::ifstream &);
            static int randomize();
            static void print_letters(int );
};

#endif // SPELLINGBEE_H_INCLUDED
