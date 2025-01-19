#include "Game.h"


Game::Game(std::string name1, std::string name2){
    
    player1.setName(name1); 
    player1.setColour('W');

    player2.setName(name2);
    player2.setColour('B');

    currentPlayer = &player1;

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

void Game::start(){
    //initialising window and pieces
    Vector2u window_res = {1024,1024};
    sf::RenderWindow window(sf::VideoMode({window_res.x + 384, window_res.y}), "Chess");
    Texture t1,R,N,B,Q,K,P,r,n,b,q,k,p;
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
    
    Sprite board(t1);
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
    f[8].setTexture(P);
    f[9].setTexture(P);
    f[10].setTexture(P);
    f[11].setTexture(P);
    f[12].setTexture(P);
    f[13].setTexture(P);
    f[14].setTexture(P);
    f[15].setTexture(P);

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
    f[24].setTexture(p);
    f[25].setTexture(p);
    f[26].setTexture(p);
    f[27].setTexture(p);
    f[28].setTexture(p);
    f[29].setTexture(p);
    f[30].setTexture(p);
    f[31].setTexture(p);

    loadPosition();

    board.setScale(0.5,0.5);
    

    bool isMove = false;
    bool isValid_M = false;
    bool not_nullptr = false;
    bool isValid_P = false;
    bool piece_selected = false;
    int piece_x = 0, piece_y = 0;
    float dx = 0, dy = 0;
    int mp{};
    float add_x_w = 0; // for when pieces get captured
    float add_x_b = 0;
    play_board.printBoard();

    /*
        TODO:
        *implement GUI code for enPassant Capture
        *implement GUI code for castling
        *implement GUI code for pawn promotion
        *implement Check Logic(highlight king square with red if in check)
        *implement Checkmate Logic()

        Finished:
        *implement ValidPiece detection(reason why program is segfaulting when pressing empty blocks, too quickly after moving)
            -need to add a nullptr check/// done
            -add a valid piece check which checks the colour of the piece ig/// done
        *Alternate between players
            -uncomment switch turn/// done
        *need to add bounds checking if sprite is inside board area. // done
        *need to takeaway sprite when the piece gets taken idk
            -maybe do a check to see if there is a sprite at the newPos and if so then delete in valid Move block //done
        ORDER IS IN LISTED IMPORTANCE
    
    
    
    */
    while(window.isOpen()){
        Vector2i pos = Mouse::getPosition(window);          //mouse position relative to the window
        Event e;
        while(window.pollEvent(e)){         //while loop to detect event types
            if(e.type == Event::Closed)
                window.close();

        
            if(e.type == Event::MouseButtonPressed)
                if(e.key.code == Mouse::Left){
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
                                    piece_x = int(pos.x/size);          //in the  x_board=y_sfml and y_board=x_sfml
                                    piece_y = int(pos.y/size);
                                    piece_selected = true;
                                }
                            }
                        }
                    }
                }
            if(piece_selected == true){
                if(e.type == Event::MouseButtonReleased){
                    if(e.key.code == Mouse::Left){
                        isMove = false;
                        Vector2f p = f[mp].getPosition() + Vector2f(size/2,size/2);           //selected sprite's position
                        Vector2f newPos = Vector2f(size*int(p.x/size)+offset,size*int(p.y/size)+offset);        //new position of sprite
                       
                        
                        if(newPos.x < float(window_res.x) && newPos.y < float(window_res.y)){
                        
                            isValid_M = play_board.isValidMoveB(piece_y, piece_x, int(p.y/size), int(p.x/size), currentPlayer->getColour());
                            if(isValid_M){// if move is valid
                                for(int i{}; i < 32; ++i){// code to check if there is a sprite at the newPos
                                    if(f[i].getPosition().x == newPos.x && f[i].getPosition().y == newPos.y){
                                        if(currentPlayer->getColour()=='W'){
                                            f[i].setPosition(Vector2f(1100 + add_x_w, 100));
                                            add_x_w = add_x_w + 10;
                                        }
                                        else if(currentPlayer->getColour()=='B'){
                                            f[i].setPosition(Vector2f(1100 + add_x_b, 924));
                                            add_x_b = add_x_b + 10;
                                        }
                                    }
                                }
                                play_board.movePiece(piece_y,piece_x,int(p.y/size), int(p.x/size));
                                f[mp].setPosition(newPos);
                                piece_selected = false;
                                switchTurn();
                                enPassantRemoval(int(p.y/size), int(p.x/size));
                            }else if(!isValid_M){// this block of code makes the piece snap back to position if invalid move
                                f[mp].setPosition(Vector2f(piece_x*size +offset, piece_y*size+offset) );
                                /*
                                if(play_board.getSquare(7,0)!=nullptr && play_board.getisMovedB(7,0)== false){//hack solution so that the white rook in corner doesnt instant transmission into oblivion in beginning of game
                                    f[0].setPosition(Vector2f(offset, 7*size+offset));
                                }
                                */
                            }
                        }else{
                            f[mp].setPosition(Vector2f(piece_x*size +offset, piece_y*size+offset) );
                        }
                        play_board.printBoard();
                    
                    }
                }
            }
        }
        if(isMove) f[mp].setPosition(pos.x-dx, pos.y-dy);//allows to move sprite around when mouse is pressed on it



        //////draw////
        window.clear(sf::Color::White);
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
