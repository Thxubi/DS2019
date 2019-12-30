#include <iostream> 
#include <random>
using std::cout; using std::endl;      
using std::default_random_engine;
int main()      
{       
    default_random_engine e;       
    for (size_t i = 0; i < 10; ++i) //生成十个随机数       
       cout << e() << endl;       
    cout << "Min random:" << e.min() << endl; //输出该随机数引擎序列的范围       
    cout << "Max random:" << e.max() << endl;       
    return 0;       
}