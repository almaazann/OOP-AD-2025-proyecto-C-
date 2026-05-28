#include <iostream>
#include <string>
using namespace std;

class GameObject{
    public:
    int ID;
    string name;
    
    GameObject(int id, string n){
        ID = id;
        name = n;
    }
    GameObject(){
        ID = 0;
        name = "Default";
    }
    void render(){
        cout << "Existing as: " << name << "\nAnd my ID is: " << ID << endl;
    }
    virtual ~GameObject(){
      cout << "Game Object has been destroyed" << endl;
    }
};

class Stats{
    public:
    int Health;
    int Mana;

    Stats(int h, int m){
        Health = h;
        Mana = m;
    }
    Stats(){
        Health = 100;
        Mana = 200;
    }

    void takeDamage(){
        Health -= 10;
        cout << "You've been attacked, your health now is: " << Health << endl;
    }
    void useMana(){
      Mana -= 20;
      cout << "You've used mana, your mana now is" << Mana << endl;
    }

    void gainHP(){
      Health += 10;
      cout << "You have healed, your healt now is" << Health << endl;
    }
    void gainMana(){
      Mana += 20;
      cout << "You've gained mana, your mana now is:" << Mana << endl;
    }  
};

class SoulMark{
    public:
    string SoulTatto;

    SoulMark(){
      SoulTatto = "There is no tatto";
    }
    SoulMark(string t){
      SoulTatto = t;
    }
    ~SoulMark(){
      cout << "You no longer posses a soul mark" << endl;
    }
};

class Weapon{
    public:
    int baseDamage;
    string name;

    Weapon(string n, int d){
        name = n;
        baseDamage = d;
    }
    Weapon(){
        name = "Weapon";
        baseDamage = 10;
    }
    virtual ~Weapon(){
      cout << "You no longer posses a weapon" << endl;
    }

    virtual void attack(){
        cout <<"You've attacked, you dealed " << baseDamage << " damage" << endl;
    }
};

class Sword: public Weapon {
    public:
    int sharpness;

    Sword(): Weapon(){
        sharpness = 10;
    }
    Sword(string n, int d, int s): Weapon(n, d){
        sharpness = s;
    }
    void attack() override{
        cout << "You've attacked with your sword, you dealed " << baseDamage + sharpness << " damage" << endl;
    }
    ~Sword(){
      cout << "You no longer posses a sword" << endl;
    }
};

class Potion{ 
    public:
    int healAmount;

    Potion(){
        healAmount = 10;
    }
    Potion(int h){
        healAmount = h;
    }
    ~Potion() {
        cout << "Potion has been consumed" << endl;
    }

    void use(){
      cout << "Potion has been used!\nYou've healed " << healAmount << "health points." << endl;
    }
};

class Guild{
    public:
    string name;
    int members;

    Guild(string n, int m){
        name = n;
        members = m;
    }

    Guild(){
        name = "Guild";
        members = 0;
    }
    void showInfo(){
        cout << "Guild name: " << name << "\nMembers: " << members << endl;
    }
    void addMember(){
        members++;
        cout << "You've joined the guild" << endl;
    }

    void removeMember(){
        members--;
        cout << "You've left the guild" << endl;
    }
    ~Guild() {
        cout << "Guild has been destroyed" << endl;
    }
};

class Hero: public GameObject{
    public:
    Stats stats;
    SoulMark soulMark;
    Guild* guild;
    Weapon* weaponPtr;        

    Hero(int id, string n, Stats s, SoulMark sm, Guild* g, Weapon* sw): GameObject(id, n){
        stats = s;
        soulMark = sm;
        guild = g;
        weaponPtr = sw;
    }

    Hero(): GameObject(){
        stats = Stats();
        soulMark = SoulMark();
        guild = nullptr;
        weaponPtr = nullptr;
        cout << "You have been created" << endl;
    }

    ~Hero(){
        cout << "You died lol!" << endl;
    }

    void usePotion(Potion* p){
        p->use();
        delete p;
        stats.useMana();
        stats.gainHP();
    }

    void attack(){
      if (weaponPtr == nullptr){
        cout << "You don't have a weapon" << endl;
      }
      else{
        weaponPtr->attack();
        cout << "You've attacked" << endl;
      }
    }

};
int main(){
    Guild* myGuild = new Guild("The Dark Knights", 0);
    Weapon* myWeapon = new Sword("Excalibur", 10, 10);  
    bool jugando = true;
    cout << " ===== JUEGO INICIADO ==== " << endl;
    cout << "HIII PLAYER, WHATS YOUR NAME?" << endl;
    string playerName;
    cin >> playerName;
    cout << "Can you give me an ID? you only need 4 numbers" << endl;
    int playerID;
    cin >> playerID;
    cout << "Would you like to join a guild? (y/n)" << endl;
    char answer;
    cin >> answer;
    if (answer == 'y'){
        myGuild->addMember();
        myGuild->showInfo();
        cout << "You've joined the guild" << endl;
    }
    else{
        cout << "You've decided to stay alone, you know what they say, 'Better alone than in bad company'"<<endl;
    }
    cout<<"Would you like to have a weapon? (y/n)"<<endl;
    char answer2;
    cin >> answer2;
    if (answer2 == 'y'){
        cout << "You've chosen to have a weapon, the all mighty excalibur" << endl;   
    }
    else{
        cout << "You cant attack folk" << endl;
        delete myWeapon;
        myWeapon = nullptr;
    }
    cout << "Whats yout biggest quality, say it as a soulmark" << endl;
    string soulMark;
    cin >> soulMark;
    Hero myHero(playerID, playerName, Stats(), SoulMark(soulMark), myGuild, myWeapon);
    while(jugando){
      cout << "What would you like to do?" << endl;
      cout << "1. Attack" << endl;
      cout << "2. Use Potion" << endl;
      cout << "3. Exit" << endl;
      int choice;
      cin >> choice;
      if (choice == 1){
        myHero.attack();
      }
      else if (choice == 2){
        myHero.usePotion(new Potion());
      }
      else if(choice == 3){
        jugando = false;
        cout << "You've decided to exit the game" << endl;
        cout << " ===== JUEGO TERMINADO ==== " << endl;
      }
      
    }
    delete myGuild;
    delete myWeapon;
    return 0;
}