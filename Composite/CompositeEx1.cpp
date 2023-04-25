#include <iostream>
#include <vector>

using namespace std;

class Department{
    public:
        virtual ~Department(){};
        
        virtual void printDepartmentName() const = 0;
        virtual string getName() const = 0;
};

//Composites
class HeadDepertment: public Department{ private: string name; int id; vector<Department*> childrenDepartments;
    public: HeadDepertment(int id, string name):name(name), id(id){};
    
    void printDepartmentName() const { 
        cout << "\nHEAD DEPARTMENT\n";  
        for(int i = 0; i < childrenDepartments.size(); i++){
            childrenDepartments[i]->printDepartmentName();
        }
    }
    string getName() const { return name; }
    
    void add(Department *d){ childrenDepartments.push_back(d); }
    void removeDepartment(int id){ childrenDepartments.erase(childrenDepartments.begin() + id); }
};
class SoftwareDepartment: public Department{ private: string name; int id; vector<Department*> childrenDepartments;
    public: SoftwareDepartment(int id, string name):name(name), id(id){};
    
    void printDepartmentName() const { 
        cout << "HEAD " << getName() << endl; 
        for(int i = 0; i < childrenDepartments.size(); i++){
            childrenDepartments[i]->printDepartmentName();
        }
    }
    string getName() const { return name; }
    
    void add(Department *d){ childrenDepartments.push_back(d); }
    void removeDepartment(int id){ childrenDepartments.erase(childrenDepartments.begin() + id); }
};

//Leaves
class TesterDepartment: public Department{ private: string name; int id;
    public: TesterDepartment(int id, string name):name(name), id(id){};
    
    void printDepartmentName() const { cout << getName() << endl; }
    string getName() const { return name; }
};
class SalesDepartment: public Department{ private: string name; int id;
    public: SalesDepartment(int id, string name):name(name), id(id){};
    
    void printDepartmentName() const { cout << getName() << endl; }
    string getName() const { return name; }
};
class FinancialDepartment: public Department{ private: string name; int id;
    public: FinancialDepartment(int id, string name):name(name), id(id){};
    
    void printDepartmentName() const { cout << getName() << endl; }
    string getName() const { return name; }
};

int main()
{
        Department *salesDepartment = new SalesDepartment(1, "Sales Department");
		Department *financialDepartment = new FinancialDepartment(2, "Financial Department");
		Department *testerDepartment = new TesterDepartment(4, "tester Department");
		
		//creating composites
		SoftwareDepartment *softwareDepartment = new SoftwareDepartment(3, "software Department");
		HeadDepertment *headDepartment = new HeadDepertment(0, "Head Department");
		
		softwareDepartment->add(testerDepartment);
		
		headDepartment->add(salesDepartment);
		headDepartment->add(financialDepartment);
		headDepartment->add(softwareDepartment);
		
		//Print Data
		softwareDepartment->printDepartmentName();
		headDepartment->printDepartmentName();

    return 0;
}
