#include "Game.h"


Game::Game(std::string name1, std::string name2){
    
    player1.setName(name1); 
    player1.setColour('W');

    player2.setName(name2);
    player2.setColour('B');

    currentPlayer = &player1;

    t1.loadFromFile("assets/board.png");

    //white pieces
    R.loadFromFile("assets/wr.png");
    N.loadFromFile("assets/wn.png");
    B.loadFromFile("assets/wb.png");
    Q.loadFromFile("assets/wq.png");
    K.loadFromFile("assets/wk.png");
    P.loadFromFile("assets/wp.png");

    //black pieces
    r.loadFromFile("assets/br.png");
    n.loadFromFile("assets/bn.png");
    b.loadFromFile("assets/bb.png");
    q.loadFromFile("assets/bq.png");
    k.loadFromFile("assets/bk.png");
    p.loadFromFile("assets/bp.png");

    //buttons
    b1.loadFromFile("assets/buttons/queen.png");
    b2.loadFromFile("assets/buttons/bishop.png");
    b3.loadFromFile("assets/buttons/knight.png");
    b4.loadFromFile("assets/buttons/rook.png");

    buttons[0].setTexture(b1);
    buttons[1].setTexture(b2);
    buttons[2].setTexture(b3);
    buttons[3].setTexture(b4);

    board.setTexture(t1);
/*
    f[0].setTexture(K);
    f[1].setTexture(Q);
    f[2].setTexture(k);
*/
    //special white

    f[0].setTexture(R);
    f[1].setTexture(N);
    f[2].setTexture(B);
    f[3].setTexture(Q);
    f[4].setTexture(K);
    f[5].setTexture(B);
    f[6].setTexture(N);
    f[7].setTexture(R);
    //pawns
    for(int i{8}; i < 16; ++i){
        f[i].setTexture(P);
    }


    //special black
    f[16].setTexture(r);
    f[17].setTexture(n);
    f[18].setTexture(b);
    f[19].setTexture(q);
    f[20].setTexture(k);
    f[21].setTexture(b);
    f[22].setTexture(n);
    f[23].setTexture(r);
    //pawns
    
    for(int i{24}; i < 32; ++i){
        f[i].setTexture(p);
    }

    board.setScale(0.5,0.5);
}

Game::~Game(){ // deletes remaining pieces on board that is dynamically allocated 
    std::cout << "Game destructor called " << '\n';
    for(int i{}; i < 8; ++i){
        for(int j{}; j < 8; ++j){
            if(play_board.getSquare(i,j) != nullptr){
                delete play_board.getSquare(i, j);
            }
        }
    }
}

void Game::loadPosition(){
    //white pieces
    /*
    f[0].setPosition(size*4 +offset, size*7 +offset);
    f[1].setPosition(size*5 +offset, size*1 +offset);
    f[2].setPosition(offset,offset);
    */
    
   
    for(int i{}; i < 8; ++i){
        f[i].setPosition(size*i + offset,size*7 + offset);
    }
    for(int i{0}; i < 8; ++i){
        f[i+8].setPosition(size*i + offset,size*6 +offset);
    }
    //black pieces
    
    for(int i{0}; i < 8; ++i){
        f[i+16].setPosition(size*i+offset,size*0+offset);
    }

    for(int i{0}; i < 8; ++i){
        f[i+24].setPosition(size*i+offset,size*1+offset);
    }
    
    
     
}

void Game::loadPromotions(){
    for(int i{}; i < 4; ++i){
        buttons[i].setPosition(0,100*i);
    }
}

void Game::switchTurn(){
    if(currentPlayer == &player1){
        currentPlayer = &player2;
    }else{
        currentPlayer = &player1;
    }


}

void Game::enPassantRemoval(int x, int y){// removes enPassant bool after turn switch
    for(int i{}; i < 8; ++i){
        for(int j{}; j < 8; ++j){
            if(i == x && j == y){
                continue;
            }
            if(play_board.getSquare(i, j) != nullptr){
                if(play_board.getSymbolB(i,j) == 'P' && play_board.getSquare(i,j)->getisMoved()== true && play_board.getSquare(i,j)->getenPassant() == true){
                    play_board.getSquare(i,j)->setenPassant(false);
                }else if(play_board.getSymbolB(i,j) == 'p'&& play_board.getSquare(i,j)->getisMoved()== true && play_board.getSquare(i,j)->getenPassant() == true){
                    play_board.getSquare(i,j)->setenPassant(false);
                }
            }
            
        }
    }
}

void Game::enPassantCapture(Vector2f newPos, float& add_x_w, float& add_x_b){
    float temp_x{};
    float temp_y{};
    if(currentPlayer->getColour() == 'W'){
        for(int i{}; i < 32; ++i){
            temp_x = f[i].getPosition().x;
            temp_y = f[i].getPosition().y;
            if(temp_x == newPos.x && temp_y == newPos.y + size){
                std::cout << int(temp_y/size) << ", " << int(temp_x/size) << '\n';
                f[i].setPosition(Vector2f(1100 + add_x_w, 100));
                add_x_w = add_x_w + 10;        
            }
        }    
    }else if(currentPlayer->getColour()=='B'){
        for(int i{}; i < 32; ++i){
            if(f[i].getPosition().x == newPos.x && f[i].getPosition().y == newPos.y - size){
                f[i].setPosition(Vector2f(1100 + add_x_w, 924-50));
                add_x_w = add_x_w + 10;        
            }
        }

    }
}

void Game::guiCapture(Vector2f newPos, float& add_x_w, float& add_x_b){
    for(int i{}; i < 32; ++i){// code to check if there is a sprite at the newPos
        if(f[i].getPosition().x == newPos.x && f[i].getPosition().y == newPos.y){
            if(currentPlayer->getColour()=='W'){
                f[i].setPosition(Vector2f(1100 + add_x_w, 100));
                add_x_w = add_x_w + 10;
            }
            else if(currentPlayer->getColour()=='B'){
                f[i].setPosition(Vector2f(1100 + add_x_b, 924-50));
                add_x_b = add_x_b + 10;
            }
        }
    }

}

void Game::guiCastle(Vector2f newPos){
    for(int i{}; i < 32; ++i){
        if(f[i].getPosition().x == newPos.x + size && f[i].getPosition().y == newPos.y){
            f[i].setPosition(newPos.x-size, newPos.y);
        }else if(f[i].getPosition().x == newPos.x - 2*size && f[i].getPosition().y == newPos.y){
            f[i].setPosition(newPos.x+size, newPos.y);
        }
    }
}

void Game::promoteMenu(bool& black, bool& white, std::pair<int,int> dest, int mp){
    std::cout << "inside promote menu\n";
    float px{};
    float py{};
    sf::RenderWindow promotion(sf::VideoMode({200,400}),"Choose a Piece");// promotion window
    loadPromotions();
    while(promotion.isOpen()){
        Vector2i posP = Mouse::getPosition(promotion);
        Event eP;
        while(promotion.pollEvent(eP)){
            if(eP.type == Event::MouseButtonPressed){
                if(eP.key.code == Mouse::Left){
                    for(int i{}; i < 4; ++i){
                        if(buttons[i].getGlobalBounds().contains(posP.x,posP.y)){
                            px = posP.x;
                            py = posP.y;
                            if(px >= 0 && px <= 200){
                                if(py >= 0 && py <= 100){
                                    play_board.pawnPromotion(dest.second, dest.first,"queen",currentPlayer->getColour());
                                    if(currentPlayer->getColour()=='W'){
                                        f[mp].setTexture(Q,true);
                                    }else if(currentPlayer->getColour()=='B'){
                                        f[mp].setTexture(q,true);
                                    }
                                }else if(py > 100 && py <= 200){
                                    play_board.pawnPromotion(dest.second, dest.first,"bishop",currentPlayer->getColour());
                                    if(currentPlayer->getColour()=='W'){
                                        f[mp].setTexture(B,true);
                                    }else if(currentPlayer->getColour()=='B'){
                                        f[mp].setTexture(b,true);
                                    }
                                }else if(py > 200 && py <= 300){
                                    play_board.pawnPromotion(dest.second, dest.first,"knight",currentPlayer->getColour());
                                    if(currentPlayer->getColour()=='W'){
                                        f[mp].setTexture(N,true);
                                    }else if(currentPlayer->getColour()=='B'){
                                        f[mp].setTexture(n,true);
                                    }
                                }else if(py > 300 && py <= 400){
                                    play_board.pawnPromotion(dest.second, dest.first,"rook",currentPlayer->getColour());
                                    if(currentPlayer->getColour()=='W'){
                                        f[mp].setTexture(R,true);
                                    }else if(currentPlayer->getColour()=='B'){
                                        f[mp].setTexture(r,true);
                                    }
                                }
                            }
                            black = false;
                            white = false;
                            promotion.close();    
                        }
                    }
                }
            }
            for(int i{}; i < 4; ++i) promotion.draw(buttons[i]);
            promotion.display();                                 
        }

    }
    
}

void Game::start(){
    //initialising window and pieces
    Vector2u window_res = {1024,1024};
    unsigned int side_bar = 384;
    sf::RenderWindow window(sf::VideoMode({window_res.x + side_bar, window_res.y}), "Chess",Style::Titlebar|sf::Style::Close);


    //buttons for promotion window

    loadPosition();
    bool block_check{false};
    std::pair<int,int> chosen_pieces[128]; 
    std::pair<int,int> moves[128];
    std::pair<int,int> selected_pair;
    int attack_x{};
    int attack_y{};

    bool correct_colour = false;
    bool valid_piece = false;
    bool list_piece = false;
    int k_x{};
    int k_y{};
    bool isMove = false;
    bool list_move = false;
    bool isValid_M = false;
    bool not_nullptr = false;
    bool isValid_P = false;
    bool piece_selected = false;
    bool promote_white = false;
    bool promote_black = false;
    int piece_x = 0, piece_y = 0;
    float dx = 0, dy = 0;
    int mp{};
    float add_x_w = 0; // for when pieces get captured
    float add_x_b = 0;
    bool stale_mate = false;
    bool king_safety{false};
    bool enemy{false};
    //play_board.printBoard();

    /*
        IMPORTANT:
            x_engine = y_sfml and
            y_engine = x_sfml

            in the gui code we will be following the sfml style ig
    */

    /*
        OPTIONAL:
        *add sounds for moving pieces
        *add sound when king is in check, highlight king if in check.
        *add gui popups for stalemate, checkmate
        *make a menu
    


        ORDER IS IN LISTED IMPORTANCE
        
        Finished:
        *implement ValidPiece detection(reason why program is segfaulting when pressing empty blocks, too quickly after moving)
            -need to add a nullptr check/// done
            -add a valid piece check which checks the colour of the piece ig/// done
        *Alternate between players
            -uncomment switch turn/// done
        *need to add bounds checking if sprite is inside board area. // done
        *need to takeaway sprite when the piece gets taken idk
            -maybe do a check to see if there is a sprite at the newPos and if so then delete in valid Move block //done
        *implement GUI code for enPassant Capture   //done
        *implement GUI code for castling //done
        *implement GUI code for pawn promotion //done
        *implement Check Logic(highlight king square with red if in check) //done
        *implement stalemate           //done
        *implement Checkmate Logic()    //done

        BUGS:
        *some cases where a pawn takes a piece before promotion segfaults the game //done
    */
    while(window.isOpen()){
        Vector2i pos = Mouse::getPosition(window);          //mouse position relative to the window
        Event e;
        while(window.pollEvent(e)){         //while loop to detect event types
            if(e.type == Event::Closed)
                window.close();

            if(e.type == Event::MouseButtonPressed)
                if(e.key.code == Mouse::Left){
                    //if !king_check else 
                    if(!king_check){
                        if(pos.x < float(window_res.x) && pos.y < float(window_res.y)){
                            for(int i{}; i < 32; ++i){
                                if(f[i].getGlobalBounds().contains(pos.x, pos.y))
                                {
                                    int temp_x = int(pos.x/size);
                                    int temp_y = int(pos.y/size);
                                    if(play_board.getSquare(temp_y,temp_x)!=nullptr && play_board.getColourB(temp_y,temp_x) == currentPlayer->getColour()){
                                        isMove = true; mp= i;
                                        dx = pos.x - f[i].getPosition().x;
                                        dy = pos.y - f[i].getPosition().y;
                                        piece_x = temp_x;          //in the  x_board=y_sfml and y_board=x_sfml
                                        piece_y = temp_y;
                                        piece_selected = true;
                                    }
                                }
                            }
                        }
                    }else{//logic for when king is in check
                        if(double_check){
                            not_nullptr = play_board.getSquare(k_x,k_y) != nullptr;
                            std::cout << k_x << ", " << k_y << '\n';

                            if(not_nullptr){
                                correct_colour = play_board.getColourB(k_x,k_y) != currentPlayer->getColour();
                            }
                            valid_piece = not_nullptr;
                            
                            std::cout << "k_y*size+offset,k_x*size +offset" << k_y*size+offset <<", " << k_x*size +offset << '\n';
                            //&& f[i].getPosition()== Vector2f(k_y*size+offset,k_x*size +offset)
                            if(valid_piece&& correct_colour){
                                for(int i{}; i < 32; ++i){
                                    if(f[i].getPosition()== Vector2f(k_y*size+offset,k_x*size +offset) && f[i].getGlobalBounds().contains(pos.x, pos.y)){
                                        mp = i;
                                        dx = pos.x - f[i].getPosition().x;
                                        dy = pos.y - f[i].getPosition().y;
                                        break;
                                    }
                                }
                                isMove = true;
                                piece_x = k_y;
                                piece_y = k_x;
                                piece_selected = true;
                            }
                            double_check = false;
                            
                        }else{
                            int temp_x = int(pos.x/size);
                            int temp_y = int(pos.y/size);
                            not_nullptr = play_board.getSquare(temp_y,temp_x) != nullptr;
                            std::cout << "not nullptr : " << not_nullptr << '\n';
                            if(not_nullptr){
                                correct_colour = play_board.getColourB(temp_y,temp_x) == currentPlayer->getColour();
                                std::cout << "correct colour: " << correct_colour << '\n';
                            }
                        
                            selected_pair = std::make_pair(temp_y, temp_x);
                            std::cout << count_check << '\n';
                            for(int i{}; i < count_select;++i){
                                //std::cout << chosen_pieces[i].second << ", " << chosen_pieces[i].first << '\n';
                                //std::cout << "searching for pair...\n";
                                if(selected_pair == chosen_pieces[i]){
                                    list_piece = true;
                                    break;
                                }
                            }
                            //f[i].getPosition()== Vector2f(selected_pair.second*size+offset,selected_pair.first*size +offset) && 
                            valid_piece = not_nullptr && correct_colour && list_piece;
                            if(valid_piece){
                                for(int i{}; i < 32; ++i){
                                    if(f[i].getGlobalBounds().contains(pos.x, pos.y) ){
                                        mp = i;
                                        dx = pos.x - f[i].getPosition().x;
                                        dy = pos.y - f[i].getPosition().y;
                                        break;
                                    }
                                }
                                isMove = true;
                                piece_x = selected_pair.second;
                                piece_y = selected_pair.first;
                                
                                piece_selected = true;
                            }
                            
                        }
                        

                    }
                }
            if(piece_selected == true){
                if(e.type == Event::MouseButtonReleased){
                    if(e.key.code == Mouse::Left){
                        //if !king_check else
                        if(!king_check){
                            isMove = false;
                            Vector2f p = f[mp].getPosition() + Vector2f(size/2,size/2);           //selected sprite's position
                            Vector2f newPos = Vector2f(size*int(p.x/size)+offset,size*int(p.y/size)+offset);        //new position of sprite
                            std::pair<int,int> dest(int(p.x/size),int(p.y/size));
                            if(newPos.x < float(window_res.x) && newPos.y < float(window_res.y)){
                                isValid_M = play_board.isValidMoveB(piece_y, piece_x, dest.second, dest.first, currentPlayer->getColour());
                                if(currentPlayer->getColour()== 'W'){
                                    king_safety = play_board.pieceBlockingCheck(piece_y, piece_x, dest.second, dest.first,  'B');
                                }else if(currentPlayer->getColour() =='B'){
                                    king_safety = play_board.pieceBlockingCheck(piece_y, piece_x, dest.second, dest.first,  'W');
                                }
                                
                                if(!king_safety){
                                    isValid_M = false;
                                }
                                if(play_board.getSquare(dest.second,dest.first) != nullptr){
                                    enemy= play_board.getColourB(piece_y, piece_x) != play_board.getColourB(dest.second,dest.first);
                                }
                
                                
                                if(isValid_M && (play_board.getSquare(dest.second,dest.first)==nullptr ||enemy)){// if move is valid
                                    guiCapture(newPos,add_x_w,add_x_b);  
                                    if(piece_x+1 < 8 && piece_x-1 > 0){        
                                        bool black_pawn_ep_r = play_board.getSquare(piece_y,piece_x+1)!=nullptr &&play_board.getSymbolB(piece_y,piece_x+1)=='p' && play_board.getSquare(piece_y,piece_x+1)->getenPassant() == true;
                                        bool black_pawn_ep_l = play_board.getSquare(piece_y,piece_x-1)!=nullptr &&play_board.getSymbolB(piece_y,piece_x-1)=='p' && play_board.getSquare(piece_y,piece_x-1)->getenPassant() == true;
                                        bool black_pawn_ep = black_pawn_ep_l || black_pawn_ep_r;
                                        
                                        bool white_pawn_ep_r = play_board.getSquare(piece_y,piece_x+1)!=nullptr &&play_board.getSymbolB(piece_y,piece_x+1)=='P'&& play_board.getSquare(piece_y,piece_x+1)->getenPassant() == true;
                                        bool white_pawn_ep_l = play_board.getSquare(piece_y,piece_x-1)!=nullptr &&play_board.getSymbolB(piece_y,piece_x-1)=='P'&& play_board.getSquare(piece_y,piece_x-1)->getenPassant() == true;
                                        bool white_pawn_ep = white_pawn_ep_l || white_pawn_ep_r;
                                        if(play_board.getSymbolB(piece_y,piece_x)== 'P' && currentPlayer->getColour()=='W' && black_pawn_ep){
                                            enPassantCapture(newPos,add_x_w,add_x_b);
                                        }else if( play_board.getSymbolB(piece_y,piece_x) == 'p' && currentPlayer->getColour()=='B' && white_pawn_ep){
                                            std::cout << "inside else if\n";
                                            enPassantCapture(newPos,add_x_w,add_x_b);
                                        }
                                    }


                                    bool isKing = play_board.getSymbolB(piece_y,piece_x)== 'K' || play_board.getSymbolB(piece_y,piece_x) == 'k';
                                    bool diff2 = piece_y == dest.second && abs(piece_x - dest.first) == 2;
                                    
                                    if(isKing && diff2){
                                        guiCastle(newPos);
                                    }
                                    play_board.movePiece(piece_y,piece_x,dest.second, dest.first);
                                    play_board.printBoard();
                                    f[mp].setPosition(newPos);
                                    king_check = play_board.isCheck(currentPlayer->getColour(), attack_x, attack_y, k_x, k_y, double_check);
                                    std::cout << "king_check : " << king_check << '\n';
                                    
                                    if(!king_check){
                                        stale_mate = play_board.isStalemate(currentPlayer->getColour(), k_x, k_y);
                                        std::cout << "stale_mate:" << stale_mate << '\n';
                                        if(stale_mate == true){
                                            std::cout << "its a draw\n";
                                            window.close();

                                        }
                                    }else{
                                        std::string k_colour = (currentPlayer->getColour() != 'W')? "White " : "Black ";
                                        block_check = play_board.blockCheckPossible(currentPlayer->getColour(), count_select,chosen_pieces,moves,attack_x,attack_y,k_x,k_y);
                                        std::cout << k_colour+"is in check\n";
                                    }

                                    king_checkmate = play_board.isCheckmate(currentPlayer->getColour());
                                    std::cout << king_checkmate << '\n';
                                    if(king_check || double_check){
                                        std::cout << "before king_checkmate?\n";
                                        if((king_checkmate == true) && !block_check){
                                            std::cout << "inside checkmate\n";
                                            std::string winner{" "};
                                            std::string x_wins = " wins.";
                                            if(currentPlayer->getColour() == 'W'){
                                                winner = "White";
                                            }else if(currentPlayer->getColour() == 'B'){
                                                winner = "Black";
                                            }
                                            std::string message = winner + x_wins;
                                            std::cout << message << '\n';
                                            window.close();

                                        }
                                    }
                                    
                                    for(int i=0; i < 8; ++i){
                                        if(play_board.getSquare(0,i)!= nullptr && play_board.getSymbolB(0,i)=='P'){
                                            promote_white = true;
                                            break;
                                        }
                                        if(play_board.getSquare(7,i)!= nullptr && play_board.getSymbolB(7,i)=='p'){
                                            promote_black = true;
                                            break;
                                        }      
                                    }
                                    
                                    if(promote_white||promote_black){
                                        promoteMenu(promote_black,promote_white,dest,mp);
                                    }
                                    
                                    piece_selected = false;
                                    switchTurn();
                                    enPassantRemoval(dest.second, dest.first);


                                }else if(!isValid_M){// this block of code makes the piece snap back to position if invalid move
                                    f[mp].setPosition(Vector2f(piece_x*size +offset, piece_y*size+offset) );
                                }
                            }else{
                                f[mp].setPosition(Vector2f(piece_x*size +offset, piece_y*size+offset) );
                            }
                            //play_board.printBoard();
                        }else{
                            /*
                                THIS IS FOR WHEN KING IS IN CHECK AND A MOVE NEEDS TO BE MADE TO GET IT OUT OF CHECK.
                                EITHER BY BLOCKING THE ATTACKING PIECE
                                KILLING THE ATTAKCING PIECE
                                MOVING KING TO SAFETY.
                            */
                            isMove = false;
                            Vector2f p = f[mp].getPosition() + Vector2f(size/2,size/2);           //selected sprite's position
                            Vector2f newPos = Vector2f(size*int(p.x/size)+offset,size*int(p.y/size)+offset);        //new position of sprite
                            std::pair<int,int> dest(int(p.x/size),int(p.y/size));
                            if(newPos.x < float(window_res.x) && newPos.y < float(window_res.y)){
                                isValid_M = play_board.isValidMoveB(piece_y, piece_x, dest.second, dest.first, currentPlayer->getColour());
                                if(currentPlayer->getColour()== 'W'){
                                    king_safety = play_board.pieceBlockingCheck(piece_y, piece_x, dest.second, dest.first,  'B');
                                    std::cout << king_check << '\n';
                                }else if(currentPlayer->getColour() =='B'){
                                    king_safety = play_board.pieceBlockingCheck(piece_y, piece_x, dest.second, dest.first,  'W');
                                }

                            for(int i{}; i < count_select; ++i){
                                    if(selected_pair == chosen_pieces[i] && std::pair {dest.second,dest.first} == moves[i]){
                                        std::cout << "move in list selected\n";
                                        list_move = true;
                                        break;
                                    }
                                }

                                if(play_board.getSquare(dest.second,dest.first) != nullptr){
                                    enemy= play_board.getColourB(piece_y, piece_x) != play_board.getColourB(dest.second,dest.first);
                                }
                
                                
                                if(!king_safety){
                                    isValid_M = false;
                                }
                                std::cout << "before isValid_M block \n";
                                if(isValid_M && (enemy || play_board.getSquare(dest.second,dest.first)== nullptr)){// if move is valid
                                    std::cout << "inside isValid_M block \n";
                                    guiCapture(newPos,add_x_w,add_x_b);    
                                    //enpassant code start      
                                    if(piece_x+1 < 8 && piece_x-1 > 0){
                                        bool black_pawn_ep_r = play_board.getSquare(piece_y,piece_x+1)!=nullptr &&play_board.getSymbolB(piece_y,piece_x+1)=='p' && play_board.getSquare(piece_y,piece_x+1)->getenPassant() == true;
                                        
                                        bool black_pawn_ep_l = play_board.getSquare(piece_y,piece_x-1)!=nullptr &&play_board.getSymbolB(piece_y,piece_x-1)=='p' && play_board.getSquare(piece_y,piece_x-1)->getenPassant() == true;
                                        bool black_pawn_ep = black_pawn_ep_l || black_pawn_ep_r;
                                        
                                        bool white_pawn_ep_r = play_board.getSquare(piece_y,piece_x+1)!=nullptr &&play_board.getSymbolB(piece_y,piece_x+1)=='P'&& play_board.getSquare(piece_y,piece_x+1)->getenPassant() == true;
                                        bool white_pawn_ep_l = play_board.getSquare(piece_y,piece_x-1)!=nullptr &&play_board.getSymbolB(piece_y,piece_x-1)=='P'&& play_board.getSquare(piece_y,piece_x-1)->getenPassant() == true;
                                        bool white_pawn_ep = white_pawn_ep_l || white_pawn_ep_r;
                                        
                                        if(play_board.getSymbolB(piece_y,piece_x)== 'P' && currentPlayer->getColour()=='W' && black_pawn_ep){
                                            enPassantCapture(newPos,add_x_w,add_x_b);
                                        }else if( play_board.getSymbolB(piece_y,piece_x) == 'p' && currentPlayer->getColour()=='B' && white_pawn_ep){
                                            std::cout << "inside else if\n";
                                            enPassantCapture(newPos,add_x_w,add_x_b);
                                        }
                                    }
                                    //enpassant code end
                                    
                                    //castling code start
                                    bool isKing = play_board.getSymbolB(piece_y,piece_x)== 'K' || play_board.getSymbolB(piece_y,piece_x) == 'k';
                                    bool diff2 = piece_y == dest.second && abs(piece_x - dest.first) == 2;
                                    
                                    if(isKing && diff2){
                                        guiCastle(newPos);
                                    }
                                    //castling code end

                                    play_board.movePiece(piece_y,piece_x,dest.second, dest.first);
                                    play_board.printBoard();
                                    f[mp].setPosition(newPos);
                                    
                                    //check
                                    
                                    
                                    king_check = play_board.isCheck(currentPlayer->getColour(), attack_x, attack_y, k_x, k_y, double_check);
                                    std::cout << "when king is checked\n";
                                    std::cout << king_check << '\n';
                                    //stalemate and check statement
                                    if(!king_check){
                                        stale_mate = play_board.isStalemate(currentPlayer->getColour(), k_x, k_y);
                                        std::cout << "stale_mate:" << stale_mate << '\n';
                                        if(stale_mate == true){
                                            std::cout << "its a draw\n";
                                            window.close();

                                        }
                                    }else{
                                        std::string k_colour = (currentPlayer->getColour() != 'W')? "White " : "Black ";
                                        block_check = play_board.blockCheckPossible(currentPlayer->getColour(), count_select,chosen_pieces,moves,attack_x,attack_y,k_x,k_y);
                                        std::cout << k_colour+"is in check\n";
                                        
                                    }
                                    
                                    //checkmate
                                    king_checkmate = play_board.isCheckmate(currentPlayer->getColour());
                                    std::cout << "king check : " << king_check << '\n';
                                    std::cout << "king_checkmate : " << king_checkmate << '\n';
                                    if(king_check || double_check){
                                        std::cout << king_checkmate && !block_check << '\n'; 
                                        if(king_checkmate == true && !block_check){
                                            std::cout << "inside king_checkmate block\n";
                                            std::string winner{" "};
                                            std::string x_wins = " wins.";
                                            if(currentPlayer->getColour() == 'W'){
                                                winner = "White";
                                            }else if(currentPlayer->getColour() == 'B'){
                                                winner = "Black";
                                            }
                                            std::string message = winner + x_wins;
                                            std::cout << message << '\n';
                                            window.close();

                                        }
                                    }
                                    
                                    for(int i=0; i < 8; ++i){
                                        if(play_board.getSquare(0,i)!= nullptr && play_board.getSymbolB(0,i)=='P'){
                                            promote_white = true;
                                            break;
                                        }
                                        if(play_board.getSquare(7,i)!= nullptr && play_board.getSymbolB(7,i)=='p'){
                                            promote_black = true;
                                            break;
                                        }      
                                    }
                                    
                                    if(promote_white||promote_black){
                                        promoteMenu(promote_black,promote_white,dest,mp);
                                    }
                                    
                                    piece_selected = false;
                                    valid_piece = false;
                                    isValid_M = false;
                                    switchTurn();
                                    enPassantRemoval(dest.second, dest.first);
                                }else if(!isValid_M){// this block of code makes the piece snap back to position if invalid move
                                    f[mp].setPosition(Vector2f(piece_x*size +offset, piece_y*size+offset) );
                                }
                            }else{
                                f[mp].setPosition(Vector2f(piece_x*size +offset, piece_y*size+offset) );
                            }
                            //maybe put check/stalemate/checkmate here(?)
       
                            //play_board.printBoard();

                        }
                    
                    }
                }
            }
        }
        if(isMove) f[mp].setPosition(pos.x-dx, pos.y-dy);//allows to move sprite around when mouse is pressed on it




        //////draw////
        window.clear(sf::Color::White);
        window.setVerticalSyncEnabled(true);
        window.draw(board);//draws board
        for(int i{0}; i < 32; ++i) window.draw(f[i]);//draws pieces
        
        window.display();
    }



}

