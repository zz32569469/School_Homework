#include<iostream>

using namespace std;

class int_array_cell{
    public:
        int_array_cell(){};

        int_array_cell(int *m){
            this->_counter=1;
            this->_memory=m;

            cout<<"int_array_cell is allocated\n";
        }

        ~int_array_cell(){};

        int get_counter(){
            return _counter;
        }

        bool sub_counter(){
            --this->_counter;
            if(this->_counter==0) return true;
            cout<<"int_array_cell counter is decreased: counter "<<this->_counter<<'\n';
            return false;
        }

        void add_counter(){
            ++this->_counter;
            cout<<"int_array_cell counter is increased: counter "<<this->_counter<<'\n';
        }

    private:
        int _counter;
        int *_memory;
};

class counter_ptr{
    public:
        counter_ptr(){};

        counter_ptr(char *x){
            this->_name=new char[1000]();
            *(this->_name)=*x;
            this->_cell_ptr=nullptr;
            cout<<"coutner_ptr "<<this->_name<<" is not assigned to an int_array_cell\n";
        }

        counter_ptr(char *x, int *a){
            this->_name=new char[1000]();
            *(this->_name)=*x;
            this->_cell_ptr=new int_array_cell(a);
            cout<<"counter_ptr "<<this->_name<<" is assigned to an int_array_cell: "<<"counter "<<_cell_ptr->get_counter()<<'\n';;
        }

        ~counter_ptr(){
            cout<<"counter_ptr "<<this->_name<<" is deleted\n";
            if(this->_cell_ptr!=nullptr && this->_cell_ptr->sub_counter()){
                cout<<"int_array_cell counter "<<this->_cell_ptr->get_counter()<<": deleted\n";
                delete this->_cell_ptr;
            }
            delete this->_name;
        };

        counter_ptr& operator=(int *x){
            if(this->_cell_ptr!=nullptr && this->_cell_ptr->sub_counter()){
                cout<<"int_array_cell counter "<<this->_cell_ptr->get_counter()<<": deleted\n";
                delete[] this->_cell_ptr;
            }

            this->_cell_ptr=new int_array_cell(x);
            cout<<"counter_ptr "<<this->_name<<" is assigned to an int_array_cell: "<<"counter "<<_cell_ptr->get_counter()<<'\n';;
        }

        counter_ptr& operator=(counter_ptr &x){
            if(this->_cell_ptr!=nullptr && this->_cell_ptr->sub_counter()){
                cout<<"int_array_cell counter "<<this->_cell_ptr->get_counter()<<": deleted\n";
                delete[] this->_cell_ptr;
            }

            if(this->_cell_ptr==nullptr){
                this->_cell_ptr=x._cell_ptr;
                this->_cell_ptr->add_counter();

                cout<<"counter_ptr a is assigned to an int_array_cell: counter "<<this->_cell_ptr->get_counter()<<'\n';
            }
        }

    private:
        char *_name;
        int_array_cell *_cell_ptr;
};

counter_ptr b("b", new int[10]);

int main(){

    b=new int[100];

    counter_ptr a("a");

    a=b;

}