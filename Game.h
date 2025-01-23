 #ifndef _GAME_
#define _GAME_
#include "Player.h"
#include "Board.h"
#include <SFML/Audio.hpp>
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
        int window_x = 1024+384;
        int window_y = 1024;
        int captured_pos_x = 1100;
        int caputered_w_y = 100;
        int captured_b_y = 875;
        Texture t1,R,N,B,Q,K,P,r,n,b,q,k,p, b1, b2, b3, b4, b5W, b5B,bg,sb;
        Texture PlayT;
        Sprite Play;
        Sprite f[32];
        Sprite bc[16];
        Sprite wc[16];
        Sprite PlayW;
        Sprite PlayB;
        Sprite Background;
        Sprite Sidebar;
        SoundBuffer move_sound;
        SoundBuffer capture_sound;
        SoundBuffer check_sound;
        
        int w_capture{};
        int b_capture{};
        Sprite buttons[4];
        Sprite board;
        bool king_check = false;
        Game(std::string name1, std::string name2);
        ~Game();
        void switchTurn();
        void loadPromotions();
        void promoteMenu(bool& black, bool& white, std::pair<int,int> dest, int mp);
        void enPassantRemoval(int x, int y);
        void enPassantCapture(Vector2f newPos, float& add_x_w, float& add_x_b);
        void guiCapture(Vector2f newPos, float& add_x_w, float& add_x_b);
        void guiCastle(Vector2f newPos);
        void guiStalemate();
        void guiCheckmate();
        int count_select{};
        bool double_check{false};
        bool king_checkmate{false};
        int count_check{};
        void loadPosition();
        void start();
        void menu();

};

#endif

