/** Author: Nicholas Lipovetsky **/

#include "SpellingBee.h"

void read_files();
void read_data(std::string &);
void welcome();
void sleep_func(int );
void clear_screen();
void menu(const std::string &, int &);
void how_to_play(int &);
void play(int &, GameClass &);

int main()
{
    std::string name;
    int menu_choice;
    bool game = true;

    read_files();
    welcome();
    read_data(name);
    GameClass player(name);
    clear_screen();
    menu(name,menu_choice);
    clear_screen();

    do
    {
        if(menu_choice==1)
        {
            play(menu_choice,player);
        }
        else if(menu_choice==2)
        {
            how_to_play(menu_choice);
        }
        else if(menu_choice==3 || menu_choice==4)
        {
            game = false;
        }
        else
        {
            game = false;
        }
    }   while(game);

    return 0;
}

void play(int &menuC, GameClass &player)
{
    std::string word;
    bool status1, status2, status3, status4, status5;
    int attempts = 10;
    int turns = 1;
    int element = GameClass::randomize();

    GameClass::print_letters(element);
    while(attempts>0)
    {
        std::cout << "\n***********************" << std::endl;
        std::cout << "Turn " << turns <<  std::endl;
        std::cout << "***********************" << std::endl;
        std::cout << "Enter Word(Type Q To Exit): ";
        std::cin >> word;
        std::transform(word.begin(), word.end(), word.begin(), tolower);
        if(word == "q")
        {
            attempts = -1;
            menuC = 3;
            std::cout << "\nThanks For Playing....Exiting...." << std::endl;
            sleep_func(2000);
            clear_screen();
        }
        else
        {
            player.set_user_word(word);
            player.check_if_valid_length(word,status1);
            if(status1)
            {
                std::cout << "\nVALID LENGTH!";
                player.check_if_valid_letters(word,status2,element);
                if(status2)
                {
                    std::cout << "\nVALID LETTERS!" << std::endl;
                    player.check_if_valid_word(word,status3);
                    if(status3)
                    {
                        std::cout << "VALID WORD!\n" << std::endl;
                        player.check_for_duplicate(word,status4);
                        if(status4)
                        {
                            player.set_valid_user_word(word);
                            player.point_system(word.size());
                            player.check_if_win(menuC,status5,element);
                            if(status5 && menuC==1)
                            {
                                clear_screen();
                                player.reset_data();
                                status5 = false;
                                attempts = -1;
                            }
                            else if(status5 && menuC==2)
                            {
                                clear_screen();
                                menuC = 3;
                                std::cout << "\nThanks For Playing....Exiting...." << std::endl;
                                sleep_func(2000);
                                clear_screen();
                                attempts = -1;
                            }
                        }
                        else
                        {
                            attempts--;
                            std::cout << "You Have " << attempts << " Attempts Remaining." << std::endl;
                            std::cout << std::endl << std::endl;
                        }
                     }
                     else
                     {
                        attempts--;
                        std::cout << "You Have " << attempts << " Attempts Remaining." << std::endl;
                        std::cout << std::endl << std::endl;
                     }
                }
                else
                {
                   attempts--;
                   std::cout << "You Have " << attempts << " Attempts Remaining." << std::endl;
                   std::cout << std::endl << std::endl;
                }
            }
            else
            {
               attempts--;
               std::cout << "You Have " << attempts << " Attempts Remaining." << std::endl;
               std::cout << std::endl << std::endl;
            }
            turns++;
        }
    }
    if(attempts==0)
    {
        clear_screen();
        std::cout << "You Are Out Of Attempts....Exiting...." << std::endl;
        sleep_func(2000);
        menuC = 3;
    }
}

void welcome()
{
    clear_screen();

    std::string temp, artStr;
    std::vector<std::string> vec;
    std::ifstream art;
    art.open("Art.txt");
    if(!art)
        std::cout << "Error Opening Art File!";

    while(!art.fail())
    {
        getline(art,artStr);
        vec.push_back(artStr);
    }

    for(unsigned int i = 0; i < vec.size()-1; i++)
        std::cout << vec.at(i) << std::endl;

    std::cout << "                            Press Enter Key To Continue....";
    getline(std::cin,temp);

    clear_screen();

    return;
}

// Function Opens Database Files Containing Words And Sets Of Letters
// Then Fills Their Respective Vectors With The Data.
void read_files()
{
    std::ifstream Words_File;
    Words_File.open("Words.txt");
    if(!Words_File)
        std::cout << "Error Opening Words File!";

    std::ifstream Letters_File;
    Letters_File.open("Letters.txt");
    if(!Letters_File)
        std::cout << "Error Opening Letters File!";

    std::ifstream Amount_Of_Words_File;
    Amount_Of_Words_File.open("AmountOfWordsPerSet.txt");
    if(!Amount_Of_Words_File)
        std::cout << "Error Opening Amount Of Words Pet Set File!";

    GameClass::fill_words(Words_File);
    GameClass::fill_letter_sets(Letters_File);
    GameClass::fill_sets_word_size(Amount_Of_Words_File);

    Words_File.close();
    Letters_File.close();
}
// Function Outputs The Game Menu, Offering The User The Ability
// To Either Play/Launch The Game, To Read How The Instructions,
// Or To Quit The Game Entirely.
void menu(const std::string &name, int &menuC)
{
    int key;

    std::cout << "*********************************************************************************************" << std::endl;
    std::cout << "- Welcome User: '" << name << "' -" << std::endl;
    std::cout << "*********************************************************************************************" << std::endl;
    std::cout << "Menu\n------\n(1)Play\n(2)How To Play\n(3)Quit\n";
    std::cout << ">";
    std::cin >> key;
    if(key==1)
        menuC = 1;
    else if(key==2)
        menuC = 2;
    else if(key==3)
    {
        std::cout << "\nThanks For Playing....Exiting...." << std::endl;
        sleep_func(2000);
        menuC = 3;
    }
    else
    {
        std::cout << "\nInvalid Input....Exiting...." << std::endl;
        sleep_func(2000);
        menuC = 4;
    }
}
// Function Outputs The Instructions To The Game. Offers The User The
// Ability To Play/Launch The Game, Or To Quit The Game Entirely.
void how_to_play(int &menuC)
{
    int key;

    std::cout << "There Will Appear A Random Set Of 7 Letters." << std::endl;
    std::cout << "You Must Type A Word That Exists In The English Dictionary Using Those Letters." << std::endl;
    std::cout << "\nRules:" << std::endl;
    std::cout << "1) The Word You Type In Has To Be At The Least 5 Letters Long." << std::endl;
    std::cout << "2) You Must Use The Center Letter At Least Once." << std::endl;
    std::cout << "3) You May Use The Same Letter More Than Once." << std::endl;
    std::cout << "4) Proper Names, Hyphenated Words, Prefixes, And Suffixes Are Not Allowed." << std::endl;
    std::cout << "5) You Have Ten Attempts To Come Up With Valid Words." << std::endl;
    std::cout << "6) You Will Win If You Enter All The Words That Are Made Up By Those Letters." << std::endl;
    std::cout << "\nScoring:" << std::endl;
    std::cout << "-Each Correct Word Is Worth One Point. However, A Word That Uses All Seven Letters Is Worth Three Points." << std::endl;
    std::cout << "-At 10 Points You Gain The Title Of 'Good'." << std::endl;
    std::cout << "-At 15 Points You Gain The Title Of 'Excellent'." << std::endl;
    std::cout << "-At 20 Points You Gain The Title Of 'Genius'." << std::endl;
    std::cout << "-If You Enter All The Words That Are Made Up By Those Letters You Will Gain The Title Of 'Divine'." << std::endl;
    std::cout << "\nReady To Play?" << std::endl;
    std::cout << "(1)Play\n(3)Quit" << std::endl;
    std::cout << ">";
    std::cin >> key;
    if(key==1)
        menuC = 1;
    else if(key==3)
    {
        menuC = 3;
        std::cout << "\nThanks For Playing....Exiting...." << std::endl;
        sleep_func(2000);
    }
    else
    {
        std::cout << "\nInvalid Input....Exiting...." << std::endl;
        sleep_func(2000);
        menuC = 4;
    }
    clear_screen();
}
// Function Outputs The Post Welcome Animation Welcome Screen.
// Asks User For Their Name And Returns via Reference.
void read_data(std::string &name)
{
    std::cout << "- Welcome To Team 1's Group Project Spelling Bee Game -" << std::endl << std::endl;
    std::cout << "Please Enter Your Name: ";
    getline(std::cin,name);
}

// Function Uses Operating System Specific Commands To Sleep/Delay
// The Program For The Given Amount Of Milliseconds.
// As Of Now Supports Windows 32+64, And Unix/Linux. Can be
// Extended To Supports Various Other Operating Systems.
void sleep_func(int ms)
{
    #ifdef _WIN32
      Sleep(ms);
    #elif __linux__ || _linux || __unix__
      usleep(ms * 1000);
    #else
        usleep(ms * 1000);
    #endif
}
// Function Uses Operating System Specific Commands To Nicely
// Clear The Screen And Buffer In Windows. Also Uses ANSI
// Escape Codes To Clear The Screen In Unix And Linux Consoles
// That Supports/Uses Bash.
void clear_screen()
{
    #ifdef _WIN32
      HANDLE                     hStdOut;
      CONSOLE_SCREEN_BUFFER_INFO csbi;
      DWORD                      count;
      DWORD                      cellCount;
      COORD                      homeCoords = { 0, 0 };

      hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
      if (hStdOut == INVALID_HANDLE_VALUE) return;

      /* Get the number of cells in the current buffer */
      if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
      cellCount = csbi.dwSize.X *csbi.dwSize.Y;

      /* Fill the entire buffer with spaces */
      if (!FillConsoleOutputCharacter(
                hStdOut,
                (TCHAR) ' ',
                cellCount,
                homeCoords,
                &count
            )) return;

      /* Fill the entire buffer with the current colors and attributes */
      if (!FillConsoleOutputAttribute(
                hStdOut,
                csbi.wAttributes,
                cellCount,
                homeCoords,
                &count
            )) return;

      /* Move the cursor home */
      SetConsoleCursorPosition( hStdOut, homeCoords );
    #else
      std::cout << "\033[2J\033[1;1H";
    #endif
}
