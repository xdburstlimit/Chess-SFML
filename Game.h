 #ifndef _GAME_
#define _GAME_
#include "Player.h"
#include "Board.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <time.h>
using namespace sf;

class Game{
    private:
        Player player1,player2;
        Board play_board;
        Player* currentPlayer;
    public:
        int size = 128;
        int offset = 32;
        Sprite f[32];
        Sprite buttons[4];
        Game(std::string name1, std::string name2);
        ~Game();
        void switchTurn();
        void loadPromotions();
        void enPassantRemoval(int x, int y);
        void enPassantCapture(Vector2f newPos, float& add_x_w, float& add_x_b);
        void guiCapture(Vector2f newPos, float& add_x_w, float& add_x_b);
        void guiCastle(Vector2f newPos);
        void loadPosition();
        void start();

};

#endif

