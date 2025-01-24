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
    bg.loadFromFile("assets/menu/bg.jpg");
    sb.loadFromFile("assets/menu/sidebar.jpg");
    PlayT.loadFromFile("assets/buttons/buttons.png");

    buttons[0].setTexture(b1);
    buttons[1].setTexture(b2);
    buttons[2].setTexture(b3);
    buttons[3].setTexture(b4);
    Play.setTexture(PlayT);
    Play.setTextureRect(IntRect(0,0,325,130));
    Play.setPosition(500,475);

    
    king_red.setSize(Vector2f(size,size));
    king_red.setFillColor(sf::Color::Red);
    king_red.setPosition(-128,-128);

    Background.setTexture(bg);
    Sidebar.setTexture(sb);
    Sidebar.setPosition(window_res.y,0);

    
    board.setTexture(t1);
/*  stalemate
    f[0].setTexture(K);
    f[1].setTexture(k);
    f[2].setTexture(Q);
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
    for(int i{}; i < 8; ++i){
        for(int j{}; j < 8; ++j){
            if(play_board.getSquare(i,j) != nullptr){
                delete play_board.getSquare(i, j);
            }
        }
    }
}

void Game::loadPosition(){
   
/*  stalemate
    f[0].setPosition(size*4+offset,size*7+offset);
    f[1].setPosition(offset,offset);
    f[2].setPosition(size*5+offset,size*1+offset);
*/
    //white pieces
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
                f[i].setPosition(Vector2f(1100 + add_x_w, 100));
                add_x_w = add_x_w + 10;        
            }
        }    
    }else if(currentPlayer->getColour()=='B'){
        for(int i{}; i < 32; ++i){
            if(f[i].getPosition().x == newPos.x && f[i].getPosition().y == newPos.y - size){
                f[i].setPosition(Vector2f(1100 + add_x_w, captured_b_y));
                add_x_w = add_x_w + 10;        
            }
        }

    }
}

void Game::guiCapture(Vector2f newPos, float& add_x_w, float& add_x_b){
    for(int i{}; i < 32; ++i){// code to check if there is a sprite at the newPos
        if(f[i].getPosition().x == newPos.x && f[i].getPosition().y == newPos.y){
            if(currentPlayer->getColour()=='W'){
                wc[w_capture] = f[i];
                f[i].setPosition(Vector2f(captured_pos_x + add_x_w,caputered_w_y));
                add_x_w = add_x_w + 20;
                ++w_capture;
            }
            else if(currentPlayer->getColour()=='B'){
                bc[b_capture] = f[i];
                f[i].setPosition(Vector2f(captured_pos_x + add_x_b, captured_b_y));
                add_x_b = add_x_b + 20;
                ++b_capture;
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

void Game::guiCheckmate(){
    sf::RenderWindow checkmate(sf::VideoMode({400,200}),"Result", Style::Titlebar|sf::Style::Close);// promotion window
    sf::Text cm;
    sf::Font undertable;
    
    undertable.loadFromFile("./assets/font/sans.ttf");
    cm.setFont(undertable);
    
    std::string colour = currentPlayer->getColour() == 'W'? "White ":"Black ";
    std::string winner = colour + "wins";
    cm.setString(winner);
    cm.setCharacterSize(70);
    cm.setFillColor(sf::Color::Black);
    cm.setPosition(40,50);
    while(checkmate.isOpen()){
        Event eS;
        while(checkmate.pollEvent(eS)){
            if(eS.type == Event::Closed)
                checkmate.close();                        
        }
        
        checkmate.clear(sf::Color::White);
        checkmate.draw(cm);
        checkmate.display();

    }

}

void Game::guiStalemate(){
    sf::RenderWindow stalemate(sf::VideoMode({400,200}),"Result", Style::Titlebar|sf::Style::Close);// promotion window
    sf::Text sm;
    sf::Font undertable;
    
    undertable.loadFromFile("./assets/font/sans.ttf");
    sm.setFont(undertable);
    
    
    sm.setString("Stalemate");
    sm.setCharacterSize(70);
    sm.setFillColor(sf::Color::Black);
    sm.setPosition(50,50);
    while(stalemate.isOpen()){
        Event eS;
        while(stalemate.pollEvent(eS)){
            if(eS.type == Event::Closed)
                stalemate.close();                                   
        }
        
        stalemate.clear(sf::Color::White);
        stalemate.draw(sm);
        stalemate.display();

    }
}

void Game::promoteMenu(bool& black, bool& white, std::pair<int,int> dest, int mp){
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

void Game::menu(){
    sf::RenderWindow menu(sf::VideoMode({window_res.x + side_bar, window_res.y}), "Chess", Style::Titlebar|sf::Style::Close);
    float px{};
    float py{};
    while(menu.isOpen()){
        Vector2i pos = Mouse::getPosition(menu);
        Event e;
        while(menu.pollEvent(e)){
            if(e.type == Event::Closed)
                menu.close();
            if(Play.getGlobalBounds().contains(pos.x,pos.y)){
                Play.setTextureRect(IntRect(330,0,318,130));
            }else{
                Play.setTextureRect(IntRect(0,0,325,130));
            }
            if(e.type == Event::MouseButtonPressed){
                if(e.key.code == Mouse::Left){
                    if(Play.getGlobalBounds().contains(pos.x,pos.y)){
                        menu.close();
                        start();
                    }
                }
            }                         
        }
        //draw
        menu.clear(sf::Color::White);
        menu.setVerticalSyncEnabled(true);
        menu.draw(Background);
        menu.draw(Play);
        menu.display();
    }
    

}

void Game::start(){
    //initialising window and pieces
    sf::RenderWindow window(sf::VideoMode({window_res.x + side_bar, window_res.y}), "Chess",Style::Titlebar|sf::Style::Close);
    loadPosition();

    //sound effects
    move_sound.loadFromFile("./assets/sound/move-self.mp3");
    Sound move_piece(move_sound);

    capture_sound.loadFromFile("./assets/sound/capture.mp3");
    Sound capture_piece(capture_sound);

    check_sound.loadFromFile("./assets/sound/notify.mp3");
    Sound checked(check_sound);

    /*
        IMPORTANT:
            x_engine = y_sfml    (board[i][j] = sfml[y][x])
            y_engine = x_sfml
    */

    /*
        TODO:
        *Try to use one window, instead of calling another one for the game.
        *clean up code, remove debugging prints see where you can make the code simpler.
        
        
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
        *make a menu                    //done
        *add sounds for moving pieces   //done
        *add sound when king is in check, highlight king if in check.//done

        BUGS:
        *Really rare case where a piece will snap back to incorrect position.
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


                            if(not_nullptr){
                                correct_colour = play_board.getColourB(k_x,k_y) != currentPlayer->getColour();
                            }
                            valid_piece = not_nullptr;
                            
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
                            if(not_nullptr){
                                correct_colour = play_board.getColourB(temp_y,temp_x) == currentPlayer->getColour();
                            }
                        
                            selected_pair = std::make_pair(temp_y, temp_x);

                            for(int i{}; i < count_select;++i){
                                if(selected_pair == chosen_pieces[i]){
                                    list_piece = true;
                                    break;
                                }
                            }
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
                                    if(play_board.getSquare(dest.second,dest.first) == nullptr)
                                        move_piece.play();
                                    else
                                        capture_piece.play();
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

                                    king_check = play_board.isCheck(currentPlayer->getColour(), attack_x, attack_y, k_x, k_y, double_check);
                                    
                                    if(!king_check){
                                        king_red.setPosition(-size, -size);
                                        stale_mate = play_board.isStalemate(currentPlayer->getColour(), k_x, k_y);
                                        if(stale_mate == true){
                                            guiStalemate();
                                            window.close();

                                        }
                                    }else{
                                        std::string k_colour = (currentPlayer->getColour() != 'W')? "White " : "Black ";
                                        king_red.setPosition(k_y*size, k_x*size);
                                        checked.play();
                                        block_check = play_board.blockCheckPossible(currentPlayer->getColour(), count_select,chosen_pieces,moves,attack_x,attack_y,k_x,k_y);
                                    }

                                    king_checkmate = play_board.isCheckmate(currentPlayer->getColour());
                                    if(!block_check || double_check){
                                        if(king_check){
                                            if((king_checkmate == true)){
                                                guiCheckmate();
                                                window.close();

                                            }
                                        }
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
                        }else{
                            /*
                                this block of code is for when king is in check
                                either by blocking the attacking piece
                                taking the attacking piece
                                moving king to safety(if double checked or not)
                            */
                            
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

                            for(int i{}; i < count_select; ++i){
                                    if(selected_pair == chosen_pieces[i] && std::pair {dest.second,dest.first} == moves[i]){
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
                                if(isValid_M && (enemy || play_board.getSquare(dest.second,dest.first)== nullptr)){// if move is valid
                                    if(play_board.getSquare(dest.second,dest.first) == nullptr)
                                        move_piece.play();
                                    else
                                        capture_piece.play();
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

                                    //promotion
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
                                    
                                    //check
                                    king_check = play_board.isCheck(currentPlayer->getColour(), attack_x, attack_y, k_x, k_y, double_check);
                                    //stalemate and check statement
                                    if(!king_check){
                                        king_red.setPosition(-size, -size);
                                        stale_mate = play_board.isStalemate(currentPlayer->getColour(), k_x, k_y);
                                        if(stale_mate == true){
                                            guiStalemate();
                                            window.close();

                                        }
                                    }else{
                                        std::string k_colour = (currentPlayer->getColour() != 'W')? "White " : "Black ";
                                        king_red.setPosition(k_y*size, k_x*size);
                                        checked.play();
                                        block_check = play_board.blockCheckPossible(currentPlayer->getColour(), count_select,chosen_pieces,moves,attack_x,attack_y,k_x,k_y);
                                    }
                                    
                                    //checkmate
                                    king_checkmate = play_board.isCheckmate(currentPlayer->getColour());
                                    if(!block_check || double_check){
                                        if(king_check){
                                            if(king_checkmate == true){
                                                guiCheckmate();
                                                window.close();
                                            }
                                        }
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
        window.draw(Sidebar);
        window.draw(king_red);
        for(int i{0}; i < 32; ++i) window.draw(f[i]);//draws pieces
        
        window.display();
    }



}

