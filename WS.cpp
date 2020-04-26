#include <iostream>
#include <ctime>
#include <string>
#include <algorithm>
#include <random>
#include <fstream>

class Number {
protected:
    std::vector<int> data;
public:
    Number operator+(const Number &number) {
        Number numb(number);
        Number res;
        int v_ume = 0;
        int len1 = numb.size();
        int len2 = this->size();
        int min = std::min(len1, len2);
        for (unsigned int i = 0; i != min; i++) {
            int x = numb.data[numb.data.size() - 1 - i] + this->data[data.size() - 1 - i] + v_ume;
            if (x > 9) {
                v_ume = x / 10;
                res.data.push_back(x % 10);
            } else {
                v_ume = 0;
                res.data.push_back(x);
            }
        }
        if (len1 < len2){
            for (int i = len1; i != len2; i++){
                int y = this->data[data.size() - 1 - i] + v_ume;
                if (y > 9) {
                    v_ume = y / 10;
                    res.data.push_back(y % 10);
                } else {
                    v_ume = 0;
                    res.data.push_back(y);
                }
            }
        }
        if (len1 > len2){
            for (int i = len2; i != len1; i++){
                int z = numb.data[numb.data.size() - 1 - i] + v_ume;
                if (z > 9) {
                    v_ume = z / 10;
                    res.data.push_back(z % 10);
                } else {
                    v_ume = 0;
                    res.data.push_back(z);
                }
            }
        }
        if (v_ume)
            res.data.push_back(v_ume);

        std::reverse(res.data.begin(), res.data.end());
        return res;
    }
    const int& operator[](size_t i) const {
        return data[i];
    }
    int& operator[](size_t i) {
        return data[i];
    }
    Number& operator -(const Number& _num) {
        Number num(_num);

        if (this->size() > num.size()) {
            int len1 = num.size();
            for (int i = 0; i < this->size() - len1; i++)
                num.push_front(0);
        }

        int v_ume = 0;

        for (int i = this->size() - 1; i > -1; i--) {
            if ((this->data[i] - num[i] - v_ume)  >= 0) {
                this->data[i] = this->data[i] - num[i] - v_ume;
                v_ume = 0;
            }
            else {
                this->data[i] = this->data[i] - num[i] - v_ume + 10;
                v_ume = 1;
            }
        }

        std::reverse(this->data.begin(), this->data.end());
        this->Zero_Check();

        if (num.data.empty())
            this->push_back(0);
        std::reverse(this->data.begin(), this->data.end());

        return *this;
    }
public:
    void push_back(const int num){
        this->data.push_back(num);
    }
    void pop_back(){
        this->data.pop_back();
    }
    int size() const{
        return this->data.size();
    }
    void reverse(){
        std::reverse(this->data.begin(), this->data.end());
    }
    void push_front(const int x){
        this->reverse();
        this->push_back(x);
        this->reverse();
    }
    void Index(int i, int j, int val){
        //needed for Advanced GradeSchool
        this->data[i + j] = val;
    }
    void Zero_Check(){
        //checks for zeroes in the beggining of the number and gets rid of them
        for (int i = this->size() - 1; i != 1; i--) {
            if (this->data[i] != 0)
                break;
            this->pop_back();
        }
    }
    void Zero_Check2() {
        int check = 1;
        Number a;
        int i = 0;
        while (i != data.size()){
            if (data[i] == 0 && check == 0 )
                a.push_back(data[i]);
            else if (data[i] != 0){
                a.push_back(data[i]);
                check = 0;
                }
            i++;
        }
        data = a.data;
    }
public:
    static std::pair<Number, Number> Split(const Number &number) {
        //splitting Number into 2 Numbers
        int len = number.data.size();
        std::pair<Number, Number> res;

        if (len % 2 == 1){
            for (int i = 0; i != (len+1) / 2; i++)
                res.first.data.push_back(number.data[i]);
            for ( int i = (len+1) / 2; i != len; i++)
                res.second.data.push_back(number.data[i]);
        }

        else if (len % 2 != 1){
            for (int i = 0; i != (len ) / 2; i++)
                res.first.data.push_back(number.data[i]);
            for ( int i = (len) / 2; i != len; i++)
                res.second.data.push_back(number.data[i]);
        }
        return res;
    }
    Number ten_pow(int sz){
        // Adding 0 sz times
       for (int i = sz; i != 0; i--) {
           data.push_back(0);
       }
       return *this;
   }
};

class Multiplicator{
public:
    static Number Randomizer(const int k) {
        //std::srand(std::time(nullptr));
        Number res;
        //std::random_device rd;
        std::mt19937 gen(clock());
        std::uniform_int_distribution<> dis(1, 9);
        res.push_back(dis(gen));

        for (int i = 0; i < k - 1; i++) {
            std::uniform_int_distribution<> dis2(0, 9);
            res.push_back(dis2(gen));
            }
        return res;
        }
public:
    static Number Grade_School_Multiplication (const Number& num1, const Number& num2) {
        //Simple grade school multiplication
        Number res;
        res.ten_pow(num1.size() + num2.size());

        for (int i = 0; i < num1.size(); i++) {
            for (int j = 0; j < num2.size(); ++j) {
                Number a;
                int temp = num1[i] * num2[j];
                a.push_back(temp / 10);
                a.push_back(temp % 10);
                res = a.ten_pow(num1.size() + num2.size() - i - j) + res;
            }
        }
        res.pop_back();
        res.pop_back();
        return res;
    }
    /*static Number Grade_School_Multiplication(const Number &num1, const Number &num2) {  // "Advanced grade school multiplication"
        Number res;

        for (int k = 0; k != num1.size() + num2.size(); k++)
            res.push_back(0);

        int pr1 = 0;
        int pr2 = 0;

        for (int i = num2.size() - 1; i > -1; i--) {
            int v_ume = 0;
            int first_mult = num2[i];
            pr2 = 0;
            for (int j = num1.size() - 1; j > -1; j--) {
                int second_mult = num1[j];
                int other_el = res[pr1 + pr2];
                int sum = (first_mult * second_mult) + v_ume + other_el;
                v_ume = 0;

                while (sum >= 10) {
                    v_ume += 1;
                    sum -= 10;
                }
                res.Index(pr1, pr2, sum);
                pr2 = num1.size() - j;
            }
            res.Index(pr1, pr2, res[pr1 + pr2] + v_ume);
            pr1++;
        }
        res.Zero_Check();

        Number fin;
        for (int i = res.size() - 1; i != -1; i--) {
            fin.push_back(res[i]);
        }

        return fin;
    }*/
public:
    static Number DAC(const Number &num1, const Number &num2) {
        //base case 1 / 64
        if (num1.size() == 1 || num2.size() == 1)
            return Grade_School_Multiplication(num1, num2);
//        if (num1.size() <= 64 || num2.size() <= 64)
//            return Grade_School_Multiplication(num1, num2);

        std::pair<Number, Number> num1_half = Number::Split(num1);
        std::pair<Number, Number> num2_half = Number::Split(num2);

        int len1 = num1.size() / 2; //2 different lenghts for the case when num1.size != num.size
        int len2 = num2.size() / 2;

        return DAC(num1_half.first, num2_half.first).ten_pow(len1 + len2) +
               DAC(num1_half.first, num2_half.second).ten_pow(len1) + DAC(num1_half.second, num2_half.first).ten_pow(len2) +
               DAC(num1_half.second, num2_half.second);

    }
public:
    static Number Karatsuba (const Number &_num1, const Number &_num2) {
        Number num1(_num1); // copied numbers
        Number num2(_num2);

        //base case
        if (num1.size() == 1 || num2.size() == 1)
            return Multiplicator::Grade_School_Multiplication(num1, num2);
//        if (num1.size() <= 64 || num2.size() <= 64)
//            return Multiplicator::Grade_School_Multiplication(num1, num2);

        if (num1.size() % 2 == 1) //Check whether the sizes are odd / even
            num1.push_front(0);
        if (num2.size() % 2 == 1)
            num2.push_front(0);

        int len = num1.size();
        std::pair<Number, Number> num1_half = Number::Split(num1);
        std::pair<Number, Number> num2_half = Number::Split(num2);

        Number x1 = Karatsuba(num1_half.first, num2_half.first);
        Number x2 = Karatsuba(num1_half.second, num2_half.second);
        Number x3 = Karatsuba(num1_half.first + num1_half.second, num2_half.first + num2_half.second);
        Number sum = Number(x1.ten_pow(len) + (x3 - x2 - x1).ten_pow(len / 2) + x2);
        sum.Zero_Check2();
        return sum;
    }
};

    std::ostream& operator<<(std::ostream &out, const Number &number) {
        for (int i = 0; i != number.size(); i++)
            out << number[i];
        return out;
    } //operator of output

    int main() {
            //opening csv file
            std::ofstream out1;
            out1.open(R"(C:\Users\kukar\Desktop\finalresult.csv)");

            for (int i = 0; i <= 1000; i += 50) {
                float res_grade = 0;
                float res_karat = 0;
                float res_dac = 0;
                for (int j = 0; j <= 4; j++) {
                    Number first = Multiplicator::Randomizer(i);
                    Number second = Multiplicator::Randomizer(i);

                    float start_grade = clock();
                    Multiplicator::Grade_School_Multiplication(first, second);
                    float end_grade = clock();
                    float search_grade = end_grade - start_grade;
                    res_grade += search_grade;

                    float start_karat = clock();
                    Multiplicator::Karatsuba(first, second);
                    float end_karat = clock();
                    float search_karat = end_karat - start_karat;
                    res_karat += search_karat;

                    float start_dac = clock();
                    Multiplicator::DAC(first, second);
                    float end_dac = clock();
                    float search_dac = end_dac - start_dac;
                    res_dac += search_dac;
                }

                //mean value calculation
            float divconq = res_dac / 5;
            float grade_school = res_grade / 5;
            float karatsuba = res_karat / 5;

            //putting results into the csv file
            out1 << i << ',' << divconq / CLOCKS_PER_SEC << ',' << grade_school / CLOCKS_PER_SEC << ','
                 << karatsuba / CLOCKS_PER_SEC << '\n';
            }
    }
