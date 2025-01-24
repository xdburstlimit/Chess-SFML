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
        Vector2u window_res = {1024,1024};
        unsigned int side_bar = 384;    //where pieces get stored
        int size = 128;     //height/width of squares
        int offset = 32;    //to put pieces in center of squares
        int captured_pos_x = 1100;  //x position of black and white pieces
        int caputered_w_y = 100;    //y position of black pieces
        int captured_b_y = 875;     //y position of white pieces
                int k_x{};
        int k_y{};
        int count_select{};
        int count_check{};
        int w_capture{};
        int b_capture{};
        int attack_x{};
        int attack_y{};
        int mp{};
        int piece_x = 0, piece_y = 0;
        float dx = 0, dy = 0;
        float add_x_w = 0; 
        float add_x_b = 0;
        bool double_check{false};
        bool king_checkmate{false};
        bool king_check{false};
        bool stale_mate{false};
        bool king_safety{false};
        bool enemy{false};
        bool block_check{false};
        bool correct_colour{false};
        bool valid_piece{false};
        bool list_piece{false};
        bool isMove{false};
        bool list_move{false};
        bool isValid_M{false};
        bool not_nullptr{false};
        bool isValid_P{false};
        bool piece_selected{false};
        bool promote_white{false};
        bool promote_black{false};

        Texture t1,R,N,B,Q,K,P,r,n,b,q,k,p, b1, b2, b3, b4 ,bg,sb;
        Texture PlayT;
        Sprite Play;
        Sprite f[32];
        Sprite bc[16];
        Sprite wc[16];
        Sprite Background;
        Sprite Sidebar;
        Sprite buttons[4];
        Sprite board;
        RectangleShape king_red;
        SoundBuffer move_sound;
        SoundBuffer capture_sound;
        SoundBuffer check_sound;

        std::pair<int,int> chosen_pieces[128]; 
        std::pair<int,int> moves[128];
        std::pair<int,int> selected_pair;

    public:
        /*
        int k_x{};
        int k_y{};
        int count_select{};
        int count_check{};
        int w_capture{};
        int b_capture{};
        int attack_x{};
        int attack_y{};
        int mp{};
        int piece_x = 0, piece_y = 0;
        float dx = 0, dy = 0;
        float add_x_w = 0; 
        float add_x_b = 0;
        bool double_check{false};
        bool king_checkmate{false};
        bool king_check{false};
        bool stale_mate{false};
        bool king_safety{false};
        bool enemy{false};
        bool block_check{false};
        bool correct_colour{false};
        bool valid_piece{false};
        bool list_piece{false};
        bool isMove{false};
        bool list_move{false};
        bool isValid_M{false};
        bool not_nullptr{false};
        bool isValid_P{false};
        bool piece_selected{false};
        bool promote_white{false};
        bool promote_black{false};
        

        Texture t1,R,N,B,Q,K,P,r,n,b,q,k,p, b1, b2, b3, b4 ,bg,sb;
        Texture PlayT;
        Sprite Play;
        Sprite f[32];
        Sprite bc[16];
        Sprite wc[16];
        Sprite Background;
        Sprite Sidebar;
        Sprite buttons[4];
        Sprite board;
        RectangleShape king_red;
        SoundBuffer move_sound;
        SoundBuffer capture_sound;
        SoundBuffer check_sound;

        std::pair<int,int> chosen_pieces[128]; 
        std::pair<int,int> moves[128];
        std::pair<int,int> selected_pair;
        */


        //Constructors/Functions
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
        void loadPosition();
        void start();
        void menu();

};

#endif

