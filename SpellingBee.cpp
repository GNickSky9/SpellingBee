#include "SpellingBee.h"

/** Initialize Static Class Vectors - Start **/
std::vector<std::string> GameClass::words;
std::vector<std::string> GameClass::letter_sets;
std::vector<int> GameClass::sets_word_size;
/** Initialize Static Class Vectors - End **/



/** Private Error Checking Functions - Start **/
void GameClass::len_error()
{
    std::cout << "\nInvalid! You Entered A Word With A Length Of Less Than 5." << std::endl;
}

void GameClass::center_error()
{
    std::cout << "\nInvalid! You Did Not Enter The Required Center Letter." << std::endl;
}

void GameClass::invalid_letter()
{
    std::cout << "\nInvalid! You Entered A Letter That Does Not Exist." << std::endl;
}

void GameClass::invalid_word()
{
    std::cout << "\nInvalid! You Entered A Word That Does Not Exist." << std::endl;
}

void GameClass::duplicate_word()
{
    std::cout << "Invalid! You Entered A Word You Already Previously Entered." << std::endl;
}
/** Private Error Checking Functions - End **/



/** Constructors - Start **/
GameClass::GameClass() : user_name(""), points(0)
{
}

GameClass::GameClass(std::string name) : user_name(name), points(0)
{
}
/** Constructors - End **/



/** Mutator Functions - Start **/
void GameClass::set_name(std::string N)
{
    user_name = N;
}

void GameClass::set_title(Titles T)
{
    title = T;
}

void GameClass::set_points(int P)
{
    points = points + P;

    if(points<10)
        set_title(NoTitle);
    else if(points>=10 && points <15)
        set_title(Good);
    else if(points>=15 && points <20)
        set_title(Excellent);
    else if(points>=20)
        set_title(Genius);
}

void GameClass::set_user_word(std::string word)
{
    user_words.push_back(word);
}

void GameClass::set_valid_user_word(std::string word)
{
    valid_user_words.push_back(word);
}
/** Mutator Functions - End **/



/** Class Functions To Check For Validity Of Data - Start **/
void GameClass::check_if_valid_length(const std::string &word, bool &status)
{
    std::string temp_word = word;
    std::transform(temp_word.begin(), temp_word.end(), temp_word.begin(), toupper);

    if(temp_word.size()<5)
    {
        len_error();
        status = false;
    }
    else
        status = true;
}

void GameClass::check_if_valid_letters(const std::string &word, bool &status, int element)
{
    std::string temp_word = word;
    std::transform(temp_word.begin(), temp_word.end(), temp_word.begin(), toupper);
    std::string letters = letter_sets.at(element);
    std::transform(letters.begin(), letters.end(), letters.begin(), toupper);
    std::string temp, temp2, cen_let;
    unsigned int valid_count = 0;
    int valid_cen_use = 0;
    cen_let = letters[3];

    for(unsigned int i = 0; i < word.size(); i++)
    {
        temp = temp_word[i];
        for(unsigned int i = 0; i < letters.size(); i++)
        {
            temp2 = letters[i];
            if(temp==temp2)
            {
                valid_count++;
            }
            if(temp==cen_let)
            {
                valid_cen_use++;
            }

        }
    }

    if(valid_count==word.size() && valid_cen_use > 0)
        status = true;
    else if(valid_cen_use<=0)
    {
        center_error();
        status = false;
    }
    else
    {
        invalid_letter();
        status = false;
    }
}

void GameClass::check_if_valid_word(const std::string &word, bool &status)
{
    std::string temp_word = word;
    std::transform(temp_word.begin(), temp_word.end(), temp_word.begin(), tolower);
    std::string valid_word;
    int cnt = 0;
    for(unsigned int i = 0; i < words.size() - 1; i++)
    {
        valid_word = words.at(i);
        if(temp_word==valid_word)
            cnt++;
    }
    if(cnt>0)
        status = true;
    else
    {
        invalid_word();
        status = false;
    }
}

void GameClass::check_for_duplicate(const std::string &word, bool &status)
{
    std::string temp_word = word;
    std::transform(temp_word.begin(), temp_word.end(), temp_word.begin(), tolower);
    int dup_cnt = 0;
    for(unsigned int i = 0; i < user_words.size() - 1; i++)
    {
        if(temp_word==user_words[i])
            dup_cnt++;
    }
    if(dup_cnt>0)
    {
        duplicate_word();
        status = false;
    }
    else
        status = true;
}

void GameClass::check_if_win(int &choice, bool &status,int element)
{
    //status = false;
    int temp = sets_word_size.at(element);
    if(get_valid_user_words()==temp)
    {
        std::cout << "Congratulations! You Have Successfully Typed In Every Possible Word For This Set!" << std::endl;
        std::cout << "Would You Like To Play Again?" << std::endl;
        std::cout << "(1) Yes" << std::endl;
        std::cout << "(2) No" << std::endl;
        std::cout << "> ";
        std::cin >> choice;
        status = true;
    }
}
/** Class Functions To Check For Validity Of Data - End **/



/** Class Functions To Reset Data And For The Game Point System - Start **/
void GameClass::reset_data()
{
    user_words.clear();
    valid_user_words.clear();
    points = 0;
    title = NoTitle;
}

void GameClass::point_system(int size)
{
    if(size>=7)
    {
        this->set_points(3);
        std::cout << "Congratulations! You Earned 3 Points For A Total Points Of: " << this->get_points() << std::endl;
        if(this->get_points()>=10 && this->get_points()<15)
            std::cout << "Congratulations! You Now Have The Title Of: '" << TitleName[this->get_title()] << "'." << std::endl;
        else if(this->get_points()>=15 && this->get_points()<20)
            std::cout << "Congratulations! You Now Have The Title Of: '" << TitleName[this->get_title()] << "'." << std::endl;
        else if(this->get_points()>=20)
            std::cout << "Congratulations! You Now Have The Title Of: '" << TitleName[this->get_title()] << "'." << std::endl;
        std::cout << std::endl << std::endl;
    }
    else
    {
        this->set_points(1);
        std::cout << "Congratulations! You Earned 1 Point For A Total Points Of: " << this->get_points() << std::endl;
        if(this->get_points()>=10 && this->get_points()<15)
            std::cout << "Congratulations! You Now Have The Title Of: '" << TitleName[this->get_title()] << "'." << std::endl;
        else if(this->get_points()>=15 && this->get_points()<20)
            std::cout << "Congratulations! You Now Have The Title Of: '" << TitleName[this->get_title()] << "'." << std::endl;
        else if(this->get_points()>=20)
            std::cout << "Congratulations! You Now Have The Title Of: '" << TitleName[this->get_title()] << "'." << std::endl;
        std::cout << std::endl << std::endl;
    }
}
/** Class Functions To Reset Data And For The Game Point System - End **/



/** Static Class Functions To Read Data From Files, To Print Set Of Letters, And To Randomize Which Set To Play - Start **/
void GameClass::fill_words(std::ifstream &file)
{
    std::string temp;
    while(!file.fail())
    {
        file >> temp;
        words.push_back(temp);
    }
}

void GameClass::fill_letter_sets(std::ifstream &file)
{
    std::string temp;
    while(!file.fail())
    {
        file >> temp;
        letter_sets.push_back(temp);
    }
}

void GameClass::fill_sets_word_size(std::ifstream &file)
{
    int temp;
    while(!file.fail())
    {
        file >> temp;
        sets_word_size.push_back(temp);
    }
}

void GameClass::print_letters(int element)
{
    std::string temp = letter_sets.at(element);
    std::cout << "**************************" << std::endl;
    std::cout << "*   --Set Of Letters--   *" << std::endl;
    std::cout << "**************************" << std::endl;
    std::cout << "*          " << temp[0] << "             *" << std::endl;
    std::cout << "*     " << temp[1] << "          " << temp[2] << "       *" << std::endl;
    std::cout << "*          " << temp[3] << "             *" << std::endl;
    std::cout << "*     " << temp[4] << "          " << temp[5] << "       *" << std::endl;
    std::cout << "*          " << temp[6] << "             *" << std::endl;
    std::cout << "**************************" << std::endl;
}

int GameClass::randomize()
{
    srand(time(NULL));
    int lucky_set;
    lucky_set = rand() % letter_sets.size();
    return lucky_set;
}
/** Static Class Functions To Read Data From Files, To Print Set Of Letters, And To Randomize Which Set To Play - End **/
