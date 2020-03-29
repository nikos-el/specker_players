#include <iostream>  
#include <stdexcept>  
#include <string>  
  
class Player {  
  public:  
    Player(const std::string &n): name(n) {}  
      
    virtual ~Player(){  
      name.clear();  
    }  
  
    virtual const std::string & getType() const = 0;  
    virtual Move play(const State &s) = 0;  
  
    friend std::ostream & operator << (std::ostream &out, const Player &player){  
      out<<player.getType()<<" player "<<player.name;  
      return out;  
    }  
  
  protected:  
    std::string name;  
};  
  
class GreedyPlayer: public Player {  
  public:  
    GreedyPlayer(const std::string &n): Player(n), type("Greedy") {}  
    ~GreedyPlayer(){  
      name.clear();  
      type.clear();  
    }  
  
    const std::string & getType() const {  
      return type;  
    }  
    Move play(const State &s) {  
      int i_max=0, max_coins=0;   
      for (int i=0; i<s.getHeaps(); i++){  
        int x=s.getCoins(i);  
        if (x>max_coins){  
          i_max=i;  
          max_coins=x;  
        }  
      }  
      return Move(i_max, max_coins, 0, 0);  
    }  
  private:  
    std::string type;  
};  
  
class SpartanPlayer: public Player {  
  public:  
    SpartanPlayer(const std::string &n): Player(n), type("Spartan") {}  
    ~SpartanPlayer(){  
      name.clear();  
      type.clear();  
    }  
   
    const std::string & getType() const {  
      return type;  
    }  
    Move play(const State &s) {  
      int i_max=0, max_coins=0;   
      for (int i=0; i<s.getHeaps(); i++){  
        int x=s.getCoins(i);  
        if (x>max_coins){  
          i_max=i;  
          max_coins=x;  
        }  
      }  
      return Move(i_max, 1, 0, 0);  
    }  
  private:  
    std::string type;  
};  
  
class SneakyPlayer: public Player {  
  public:  
    SneakyPlayer(const std::string &n): Player(n), type("Sneaky") {}  
    ~SneakyPlayer(){  
      name.clear();  
      type.clear();  
    }  
   
    const std::string & getType() const {  
      return type;  
    }  
    Move play(const State &s) {  
      int i_min=0, min_coins=0, i=0;  
      while (min_coins==0) min_coins=s.getCoins(i++);  
      i_min=i-1;   
      for (i=0; i<s.getHeaps(); i++){  
        int x=s.getCoins(i);  
        if (x>0 && x<min_coins){  
          i_min=i;  
          min_coins=x;  
        }  
      }  
      return Move(i_min, min_coins, 0, 0);  
    }  
  private:  
    std::string type;  
};  
  
class RighteousPlayer: public Player {  
  public:  
    RighteousPlayer(const std::string &n): Player(n), type("Righteous") {}  
    ~RighteousPlayer(){  
      name.clear();  
      type.clear();  
    }  
    
    const std::string & getType() const {  
      return type;  
    }  
    Move play(const State &s) {  
      int i_min=0, i_max=0, min_coins=0, max_coins=0, i=0;   
      while (min_coins==0) min_coins=s.getCoins(i++);  
      i_min=i-1;   
      for (i=0; i<s.getHeaps(); i++){  
        int x=s.getCoins(i);  
        if (x>max_coins){  
          i_max=i;  
          max_coins=x;  
        }  
        if (x<min_coins){  
          i_min=i;  
          min_coins=x;  
        }  
      }  
      int k=(max_coins+1)/2;  
      return Move(i_max, k, i_min, k-1);  
    }  
  private:  
    std::string type;  
};  
