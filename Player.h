#ifndef _PLAYER_
#define _PLAYER_
#include <string>
class Player{
    private:
        std::string name;
        char colour;
    public:
        
        Player() = default;
        Player(std::string name_param, char colour_param){
            name = name_param;
            colour = colour_param;
        }

        std::string getName() const{
            return name;
        }

        char getColour() const{
            return colour;
        }

        void setName(std::string name_param){
            name = name_param;
        }

        void setColour(char colour_param){
            colour = colour_param;
        }

};

#endif