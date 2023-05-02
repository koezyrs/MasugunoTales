#include "Register.h"

Register::Register()
{
    registPanelTexture = TextureManager::GetTexture("Register");
    username_input = new InputBox(450,233, 122, 10, 20);
    password_input = new InputBox(450,266, 122, 10, 32, true);
    retype_password_input = new InputBox(450,302, 122, 10, 20, true);
    email_input = new InputBox(450,334, 122, 10, 50);
    button_regist = new Button("RegistButtonOut","RegistButtonOver",446,355,56,21, [this]{RegistButon();});
    button_back = new Button("BackButtonOut","BackButtonOver",523,356,56,21, [this]{BackButton();});
    systemMessageText = new Label(GAME_FONT, " ", 12, 420, 150, Black, 300);
    username_input->setActive();
}

Register::~Register()
{
    delete username_input;
    delete password_input;
    delete retype_password_input;
    delete email_input;
    delete button_regist;
    delete button_back;
}

void Register::HandleEvent()
{
    SDL_PollEvent(&Game::event);
    switch(Game::event.type){
        case SDL_QUIT:
            Game::session = CLEAR;
            break;
        case SDL_KEYDOWN:
            if(Game::event.key.keysym.sym == SDLK_RETURN) RegistButon();
            if(Game::event.key.keysym.sym == SDLK_TAB)
                {
                    if(username_input->isActive()) {username_input->deActive(); password_input->setActive();}
                    else if(password_input->isActive()) {password_input->deActive(); retype_password_input->setActive();}
                    else if(retype_password_input->isActive()) {retype_password_input->deActive(); email_input->setActive();}
                    else if(email_input->isActive()) {email_input->deActive(); username_input->setActive();}
                }
            break;
        default:
            break;
        }

    username_input->handleEvent(&Game::event);
    password_input->handleEvent(&Game::event);
    retype_password_input->handleEvent(&Game::event);
    email_input->handleEvent(&Game::event);
    button_regist->handleEvent(&Game::event);
    button_back->handleEvent(&Game::event);
}

void Register::Update()
{

}

void Register::Render()
{
    // Clear front buffer
    SDL_SetRenderDrawColor(Game::gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(Game::gRenderer);

    SDL_RenderCopy(Game::gRenderer, registPanelTexture, NULL, NULL);
    username_input->Render();
    password_input->Render();
    retype_password_input->Render();
    email_input->Render();
    button_regist->Render();
    button_back->Render();
    systemMessageText->Render();

     // Update screen
    SDL_RenderPresent(Game::gRenderer);
}

void Register::RegistButon()
{
    Game::conn = mysql_init(0);
    Game::conn = mysql_real_connect(Game::conn, HOST, DBUSERNAME, DBPASSWORD, DATABASE, HOSTPORT, NULL, 0);
    if(!Game::conn)
    {
        setMessage("Can't connect to database! ");
        std::cerr << "Can not connect to database! " << std::endl;
        return;
    }

    MYSQL_ROW row;
    MYSQL_RES* res;
    std::string qstr;
    int qstate;

    // Check if username and password has special symbol or NULL
    if(username_input->inputValue.empty())
    {
        setMessage("Username is empty!");
        return;
    }

    if(password_input->inputValue.empty())
    {
        setMessage("Password is empty!");
        return;
    }

    if(checkSpecialSymbol(username_input->inputValue))
    {
        setMessage("Username contains special symbol!");
        return;
    }

    if(password_input->inputValue != retype_password_input->inputValue)
    {
        setMessage("Password does not match!");
        return;
    }

    // Check if username exist
    qstr = "SELECT username FROM accounts WHERE username = '" + username_input->inputValue + "'";
    qstate = mysql_query(Game::conn, qstr.c_str());
    if(!qstate)
    {
        res = mysql_store_result(Game::conn);
        row = mysql_fetch_row(res);
        if(row)
        {
            setMessage("Username exists!");
            return;
        }
        mysql_free_result(res);
    }else
    {
        std::cout << "Can not make query! (Can not register!)" << std::endl;
        return;
    }

    // Them du lieu moi vao database
    qstr = "INSERT INTO accounts(username, password, email) VALUES('" + username_input->inputValue +
            "','" + password_input->inputValue + "','" + email_input->inputValue + "')";

    qstate = mysql_query(Game::conn, qstr.c_str());
    if(qstate)
    {
        setMessage("Can not query database! ");
        std::cout << "Error#1: Can not insert new account" << std::endl;
        return;
    }

    // Lay account id
    std::string account_id;
    qstr = "SELECT id FROM accounts WHERE username = '" + username_input->inputValue + "' AND password = '" + password_input->inputValue + "'";
    qstate = mysql_query(Game::conn, qstr.c_str());
    if(!qstate)
    {
        res = mysql_store_result(Game::conn);
        row = mysql_fetch_row(res);
        if(row) {std::string _account_id(row[0]); account_id = _account_id;}
        else{
            std::cerr << "Error#2: Can not find account id!" << std::endl;
            return;
        }
        mysql_free_result(res);
    }


    // Them actor moi
    qstr = "INSERT INTO actors(account_id,character_name,level,experience,experience_to_next_level,strength,dexterity,intelligence,vitality,agility,stats_used,stats_available,map_id,x,y,gold,skin) VALUES(" + account_id + ",'" + username_input->inputValue + "',1,0,100,3,6,10,20,15,0,0,1,192,128,0,'Player')";

    qstate = mysql_query(Game::conn, qstr.c_str());
    if(qstate)
    {
        setMessage("Can not query database! ");
        std::cout << "Error#3: Can not create new character!" << std::endl;
        return;
    }

    // Lay actor_id
    std::string actor_id;
    qstr = "SELECT id FROM actors WHERE account_id = " + account_id;
    qstate = mysql_query(Game::conn, qstr.c_str());
    if(!qstate)
    {
        res = mysql_store_result(Game::conn);
        row = mysql_fetch_row(res);
        if(row) {std::string _actor_id(row[0]); actor_id = _actor_id;}
        else{
            std::cerr << "Error#4: Can not find actor id!" << std::endl;
            return;
        }
        mysql_free_result(res);
    }

    // Them equip vao character information
    for(int i = 0; i < MAX_EQUIPMENT_SLOTS; i++)
    {
        qstr = "INSERT INTO actor_character_information(actor_id, slot_id, equipment_id) VALUES(" + actor_id + "," + to_string(i) + ",0)";
        qstate = mysql_query(Game::conn, qstr.c_str());
        if(qstate)
        {
            setMessage("Can not query database! ");
            std::cout << "Error#5: Can not insert data into Character information!" << std::endl;
            return;
        }
    }

    // Them item vao inventory
    for(int i = 0; i < MAX_INVENTORY_SLOTS; i++)
    {
        qstr = "INSERT INTO actor_inventory(actor_id, slot_id, equipment_id, item_id, item_amount) VALUES(" + actor_id + "," + to_string(i) + ",0,0,0)";
        qstate = mysql_query(Game::conn, qstr.c_str());
        if(qstate)
        {
            setMessage("Can not query database! ");
            std::cout << "Error#6: Can not insert data into Inventory!" << std::endl;
            return;
        }
    }

    // Them vao bang xep hang
    qstr = "INSERT INTO actor_ranking(actor_id, character_name, actor_power, actor_gold, actor_level) VALUES(" + actor_id + ",'" + username_input->inputValue + "',0,0,1)";
    qstate = mysql_query(Game::conn, qstr.c_str());
    if(qstate)
    {
        setMessage("Can not query database! ");
        std::cout << "Error#7: Can not insert data into Ranking!" << std::endl;
        return;
    }

    // Success
    setMessage("Create account successfully!");
}

void Register::BackButton()
{
    username_input->Reset();
    password_input->Reset();
    retype_password_input->Reset();
    email_input->Reset();
    systemMessageText->Reset();
    Game::session = LOGIN;
}

void Register::setMessage(std::string text)
{
    systemMessageText->Reset();
    systemMessageText = new Label(GAME_FONT, text.c_str(), 12, 420, 150, Black, 204);
}

bool Register::checkSpecialSymbol(std::string text)
{
    bool success = false;
    int n = text.length();
    for(int i = 0; i < n; i++)
    {
        if(((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z') || (text[i] >= '0' && text[i] <= '9'))) continue;
        success = true;
        break;
    }
    return success;
}
