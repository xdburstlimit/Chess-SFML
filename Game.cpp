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
                std::cout << '(' << x << ", " << y << ") skipped\n";
                continue;
            }
            if(play_board.getSquare(i, j) != nullptr){
                if(play_board.getSymbolB(i,j) == 'P' && play_board.getSquare(i,j)->getisMoved()== true && play_board.getSquare(i,j)->getenPassant() == true){
                    std::cout << "enpassant removed at " << i << ", " << j << '\n';
                    play_board.getSquare(i,j)->setenPassant(false);
                }else if(play_board.getSymbolB(i,j) == 'p'&& play_board.getSquare(i,j)->getisMoved()== true && play_board.getSquare(i,j)->getenPassant() == true){
                    std::cout << "enpassant removed at " << i << ", " << j << '\n';
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
                f[i].setPosition(Vector2f(1100 + add_x_w, 100));
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
    //I should make this a function, but the goddamn textures are tripping me up
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

    bool isMove = false;

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
    play_board.printBoard();

    /*
        TODO:
        *implement Check Logic(highlight king square with red if in check)
        *implement stalemate
        *implement Checkmate Logic()

        OPTIONAL:
        *add sounds for moving pieces
        *add sound when king is in check.


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
                }
            if(piece_selected == true){
                if(e.type == Event::MouseButtonReleased){
                    if(e.key.code == Mouse::Left){
                        //if !king_check else
                        isMove = false;
                        Vector2f p = f[mp].getPosition() + Vector2f(size/2,size/2);           //selected sprite's position
                        Vector2f newPos = Vector2f(size*int(p.x/size)+offset,size*int(p.y/size)+offset);        //new position of sprite
                        std::pair<int,int> dest(int(p.x/size),int(p.y/size));
                        if(newPos.x < float(window_res.x) && newPos.y < float(window_res.y)){
                            isValid_M = play_board.isValidMoveB(piece_y, piece_x, dest.second, dest.first, currentPlayer->getColour());
                            
                            if(isValid_M){// if move is valid
                                guiCapture(newPos,add_x_w,add_x_b);          
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


                                bool isKing = play_board.getSymbolB(piece_y,piece_x)== 'K' || play_board.getSymbolB(piece_y,piece_x) == 'k';
                                bool diff2 = piece_y == dest.second && abs(piece_x - dest.first) == 2;
                                
                                if(isKing && diff2){
                                    guiCastle(newPos);
                                }
                                std::cout << " before movepiece\n";
                                play_board.movePiece(piece_y,piece_x,dest.second, dest.first);
                                std::cout << "after move piece\n";
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
                                
                                piece_selected = false;
                                switchTurn();
                                enPassantRemoval(dest.second, dest.first);
                            }else if(!isValid_M){// this block of code makes the piece snap back to position if invalid move
                                f[mp].setPosition(Vector2f(piece_x*size +offset, piece_y*size+offset) );
                            }
                        }else{
                            f[mp].setPosition(Vector2f(piece_x*size +offset, piece_y*size+offset) );
                        }
                        std::cout << "outside else block\n";
                        play_board.printBoard();
                    
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
/*
void Game::start(){
    bool king_checkmate = false;
    bool valid_move = false;
    bool king_check = false;
    bool block_possible = false;
    int king_x_check{};
    int king_y_check{};
    std::pair<int,int> pieceXY;
    std::pair<int,int> posXY;
    bool list_piece{false};
    bool valid_piece{false};
    char choice{'y'};
    bool stale_mate = false;
    bool not_nullptr = false;
    bool current_colour = false;
    bool double_check = false;
    int attack_x;
    int attack_y;
    std::pair<int,int> piece_list[128];
    std::pair<int,int> chosen_pieces[128];
    std::pair<int,int> moves[128];

    while(king_checkmate != true && stale_mate != true){
        board.printBoard();
        if(currentPlayer){      
            if(king_check == false){
                while(valid_piece == false){
                    std::cout << "Choose piece " << currentPlayer->getName() << ":" << '\n';
                    pieceXY = board.inputCoords();
                    not_nullptr = (board.getSquare(pieceXY.first,pieceXY.second)!= nullptr);
                    if(not_nullptr){//avoids segfaulting
                        current_colour = (board.getColourB(pieceXY.first,pieceXY.second) == currentPlayer->getColour());
                    }
                    valid_piece = not_nullptr && current_colour;
                    if(valid_piece == true){
                        std::cout << "Valid Piece selected" << '\n';
                        std::cout << "Change piece? y/n" << '\n';
                        std::cin >> choice;
                        if(choice == 'y'){
                            valid_piece = false;
                        }else if(choice == 'n'){
                            break;
                        }
                    }else{
                        std::cout << "Invalid piece selected" << '\n';
                    } 
                } 
            
            }else{
                if(double_check == true){
                    std::cout << "King has been double checked, move to safety." << '\n';
                    pieceXY = std::make_pair(king_x_check, king_y_check);
                }else{
                    while(valid_piece == false){
                        std::cout << "Choose piece to lift check or move king : " << currentPlayer->getName() << '\n';
                        block_possible = board.blockCheckPossible(currentPlayer->getColour(),piece_list,chosen_pieces, moves ,attack_x, attack_y, king_x_check, king_y_check);
                        pieceXY = board.inputCoords();

                        not_nullptr = (board.getSquare(pieceXY.first,pieceXY.second)!= nullptr);
                        if(not_nullptr){//avoids segfaulting
                            current_colour = (board.getColourB(pieceXY.first,pieceXY.second) == currentPlayer->getColour());
                        }

                        for(int i{}; i < 128; ++i){
                            if( pieceXY == chosen_pieces[i]){
                                list_piece = true;
                                break;
                            }
                        }
                        valid_piece = not_nullptr && current_colour && list_piece;
                        if(valid_piece == true){
                            std::cout << "Valid Piece selected" << '\n';
                            std::cout << "Change piece? y/n" << '\n';
                            std::cin >> choice;
                            if(choice == 'y'){
                                valid_piece = false;
                            }else if( choice == 'n'){
                                break;
                            }
                        }else{
                            std::cout << "Invalid piece selected " << '\n';
                        }
                    }
                }
            }
            //making move logic
            if(king_check == false){
                std::cout << "Make move: " << '\n';
                posXY = board.inputCoords();//need to add an if else statement here as well for if king is in check or not and forcing the player to choose moves from that set which it will always be correct or choosing the king to move out of hte fucking way 
                valid_move = board.getSquare(pieceXY.first,pieceXY.second)->isValidMove(pieceXY.first,pieceXY.second,posXY.first,posXY.second,board,currentPlayer->getColour());
                if(valid_move == true){
                    board.movePiece(pieceXY.first,pieceXY.second, posXY.first, posXY.second);
                    king_check = board.isCheck(currentPlayer->getColour(), attack_x, attack_y, king_x_check, king_y_check, double_check);
                    if(king_check == false){
                        stale_mate = board.isStalemate(currentPlayer->getColour(),king_x_check,king_y_check);
                        if(stale_mate == true){
                            break;
                        }
                    }
                    
                    king_checkmate = board.isCheckmate(currentPlayer->getColour());
                    if(king_checkmate == true){
                        std::cout << "Player " << currentPlayer->getColour() << " wins" <<'\n';
                        break;
                    }

                    board.pawnPromotion(currentPlayer->getColour());
                }else{
                    valid_move = false;
                    while(valid_move == false){
                        std::cout << "Invalid move, select again.  " << '\n';
                        posXY = board.inputCoords();
                        valid_move = board.getSquare(pieceXY.first,pieceXY.second)->isValidMove(pieceXY.first,pieceXY.second,posXY.first,posXY.second,board,currentPlayer->getColour());
                    }
                    std::cout << "Valid move made." << '\n';
                    board.movePiece(pieceXY.first,pieceXY.second, posXY.first, posXY.second);
                    king_check = board.isCheck(currentPlayer->getColour(),attack_x, attack_y, king_x_check, king_y_check, double_check);
                    if(king_check == false){
                        stale_mate = board.isStalemate(currentPlayer->getColour(),king_x_check,king_y_check);
                        if(stale_mate == true){
                            break;
                        }
                    }
                    king_checkmate = board.isCheckmate(currentPlayer->getColour());
                    if(king_checkmate == true){
                        std::cout << "Player " << currentPlayer->getColour() << " wins" <<'\n';
                        break;
                    }
                    board.pawnPromotion(currentPlayer->getColour());
                }
            }else{
                std::cout << "Make move: " << '\n';
                if(pieceXY.first == king_x_check && pieceXY.second == king_y_check){
                    posXY = board.inputCoords();
                    valid_move = board.getSquare(pieceXY.first,pieceXY.second)->isValidMove(pieceXY.first,pieceXY.second,posXY.first,posXY.second,board,currentPlayer->getColour());
                }else{
                    posXY = board.inputCoords();
                    for(int i{}; i < 128; ++i){
                        if(posXY == moves[i]){
                            valid_move = true;
                            break;
                        }
                    }
                }
                if(valid_move == true){
                    board.movePiece(pieceXY.first,pieceXY.second, posXY.first, posXY.second);
                    king_check = board.isCheck(currentPlayer->getColour(), attack_x, attack_y, king_x_check, king_y_check, double_check);
                    if(king_check == false){
                        stale_mate = board.isStalemate(currentPlayer->getColour(),king_x_check,king_y_check);
                        if(stale_mate == true){
                            break;
                        }
                    }
                    
                    king_checkmate = board.isCheckmate(currentPlayer->getColour());
                    if(king_checkmate == true){
                        std::cout << "Player " << currentPlayer->getColour() << " wins" <<'\n';
                        break;
                    }

                    board.pawnPromotion(currentPlayer->getColour());
                }else{
                    valid_move = false;
                    while(valid_move == false){
                        if(pieceXY.first == king_x_check && pieceXY.second == king_y_check){
                            posXY = board.inputCoords();
                            valid_move = board.getSquare(pieceXY.first,pieceXY.second)->isValidMove(pieceXY.first,pieceXY.second,posXY.first,posXY.second,board,currentPlayer->getColour());
                        }else{
                            posXY = board.inputCoords();
                            for(int i{}; i < 128; ++i){
                                if(posXY == moves[i]){
                                    valid_move = true;
                                    break;
                                }
                            }
                        }
                    }
                    std::cout << "Valid move made." << '\n';
                    board.movePiece(pieceXY.first,pieceXY.second, posXY.first, posXY.second);
                    king_check = board.isCheck(currentPlayer->getColour(),attack_x, attack_y, king_x_check, king_y_check, double_check);
                    if(king_check == false){
                        stale_mate = board.isStalemate(currentPlayer->getColour(),king_x_check,king_y_check);
                        if(stale_mate == true){
                            break;
                        }
                    }
                    king_checkmate = board.isCheckmate(currentPlayer->getColour());
                    if(king_checkmate == true){
                        std::cout << "Player " << currentPlayer->getColour() << " wins" <<'\n';
                        break;
                    }
                    board.pawnPromotion(currentPlayer->getColour());
                }

            }
        }
        switchTurn();
        pieceXY = {};
        posXY = {};
        for(int i{}; i < 128; ++i){
            piece_list[i] = {};
            chosen_pieces[i] = {};
            moves[i] = {};
        }
        valid_piece = false;
    }
    board.printBoard();
}
*/
