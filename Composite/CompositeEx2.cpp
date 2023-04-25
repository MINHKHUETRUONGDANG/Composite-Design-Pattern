#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

class MenuComponent{
    protected: 
        MenuComponent *mc;
    public:
	    virtual ~MenuComponent(){};
	    
	    void setMenu(MenuComponent *mc){ this->mc = mc; }
	    MenuComponent *getMenu(){ return mc; }
	    
	    virtual void addMenu(MenuComponent *mc){}
	    virtual void removeMenu(MenuComponent *mc){}
	    
	    virtual string getName() const = 0;
	    virtual string getDescription() const = 0;
	    virtual double getPrice() const = 0;
	    virtual bool isVegetarian() const = 0;
	    
	    virtual bool isComposite() const { return false; };
	    virtual string print() const = 0;
};

//leaf
class MenuItem: public MenuComponent{
    private: string name; string description; double price; bool vegetarian;
    public: 
        virtual ~MenuItem(){};
        MenuItem(string name, string description, double price, bool vegetarian)
                : name(name), description(description), price(price), vegetarian(vegetarian){};
                
        virtual string getName() const { return name; };
	    virtual string getDescription() const { return description; };
	    virtual double getPrice() const { return price; };
	    virtual bool isVegetarian() const { return vegetarian; };
	    
	    virtual string print() const {
	        return "Menu Item: " + getName();
	    }
};

//composite
class Menu: public MenuComponent{
    private: string name; string description; double price; bool vegetarian; list<MenuComponent*> children;
    public: 
        virtual ~Menu(){};
        Menu(string name, string description, double price, bool vegetarian)
                : name(name), description(description), price(price), vegetarian(vegetarian){};
                
        virtual string getName() const { return name; };
	    virtual string getDescription() const { return description; };
	    virtual double getPrice() const { return price; };
	    virtual bool isVegetarian() const { return vegetarian; };
	    
	    void addMenu(MenuComponent *mc){ children.push_back(mc); mc->setMenu(this); }
	    void removeMenu(MenuComponent *mc){ children.remove(mc); mc->setMenu(nullptr); }
	    bool isComposite() const{ return true; }
	    
	    
	    virtual string print() const {
	        string result;
	        
	        for(const MenuComponent *component: children){
	            if(component == children.back()) result += component->print();
	            else result += component->print() + " + ";
	        }
	        
	        return result;
	    }
};

class Waitress{
    public:
        virtual ~Waitress(){};
        
        void ClientCode(MenuComponent *mc){
            cout << "\nRESULT: " << mc->print();
        }
        
        void ClientCode2(MenuComponent *mc1, MenuComponent *mc2){
            if(mc1->isComposite())
                mc1->addMenu(mc2);
                
            cout << "\nRESULT: " << mc1->print();
        }
};

int main()
{
	Waitress waitress;
	
	MenuComponent *fish = new MenuItem("fish", "This is fish", 1, false);
	MenuComponent *doAnChay = new MenuItem("Do An Chay", "Traditional Vietamese vegetarian food", 2, true);
	MenuComponent *pho = new MenuItem("Pho", "This is Pho", 1.5, false);

    MenuComponent *menu = new Menu("Menu", "Menu creator", 0, false);
    
    menu->addMenu(fish);
    waitress.ClientCode(menu);
    
    menu->addMenu(doAnChay);
    waitress.ClientCode(menu);
    
    waitress.ClientCode2(menu, pho);
    
    delete menu, waitress;
    delete fish, doAnChay, pho;
	return 0;
}
