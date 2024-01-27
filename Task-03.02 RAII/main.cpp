//
//  main.cpp
//  Task-03.02 RAII
//
//  Created by Маргарет  on 27.01.2024.
//

#include <iostream>

class WrongIndex : public std::exception {
public:
const char* what() const noexcept override { return "Вы ввели несуществующий индекс";}
};
    


class SmartArray {
private:
    int*arr_ = NULL;
    int size_;
    int capacity_;
public:
    SmartArray() {
        capacity_ = 1;
        size_ = 0;
        arr_ = new int[capacity_];
    }
    
    SmartArray(int capacity) {
        this->capacity_ = capacity;
        arr_ = new int[capacity_];
        size_ = 0;
    }
    
    void growArray() {
        
        int* temp = new int[capacity_ * 2];
        capacity_ = capacity_ * 2;
        for (int i = 0; i < size_; i++) {
            temp[i] = arr_[i];
        }
        delete[] arr_;
        arr_ = temp;
    }
    
    void add_element(int value) {
        if (size_ == capacity_) {
            growArray();
        }
        arr_[size_] = value;
        size_++;
            
    }
    
    int get_element(int index) {
        if (index < size_ && index >= 0)  {
            return arr_[index];
        } else {
            throw WrongIndex();
        }
    }
    
    SmartArray& operator = (const SmartArray& right) {
        
        delete[] arr_;
        
        capacity_ = right.capacity_;
        size_ = right.size_;
        
        arr_ = new int[capacity_];
        
        for (int i = 0; i < size_; i++) {
            arr_[i] = right.arr_[i];
        }
        return *this;
    }
    
    void print_array() {
        
        std::cout << "Элементы массива : ";
        
        for (int i = 0; i < size_; i++) {
            std::cout << arr_[i] << " ";
        }
        std::cout << "\n";
        
        std::cout << "Размер массива: " << size_;
    }
    
    
    ~SmartArray() {
        delete[] arr_;
    }
        
    
};

int main(int argc, const char * argv[]) {
    try {
        SmartArray arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);
        
        arr.print_array();
        std::cout << "\n";

        SmartArray new_array(2);
        new_array.add_element(44);
        new_array.add_element(34);
        
        
        
        new_array.print_array();
        std::cout << "\n";
        
        arr = new_array;
        
        arr.print_array();
        

    }
    catch (const WrongIndex& e) {
        std::cout << e.what() << "\n";
    }
   
    return 0;
}
