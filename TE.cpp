/**
******************************************************************************
* @author         : oswin
* @brief          : 模板元编程条件编译的简单例子
******************************************************************************
*/

struct NodeInfo
{
    int mRow;
    int mCol;

    NodeInfo(int r = 0, int c = 0):mRow(r),mCol(c){}
};

template<typename T>
typename std::enable_if<(sizeof(T) == 8)>::type checkParams(T t){
    cout<< typeid(t).name()<<endl;
}

template<typename T>
typename std::enable_if<(sizeof(T) == 24)>::type checkParams(T t){
    cout<< typeid(t).name()<<endl;
}

template<typename T, int flag = sizeof(T) / 8>
struct CheckParams {

    template<size_t n>
    struct bool_trait {};

    void check(T t) {
        Check(bool_trait<flag>(), t);
    }

    void Check(bool_trait<1>, T t) //二分法查找
    {
        cout << "use binary" << endl;
    };

    void Check(bool_trait<3>, T t) //顺序查找
    {
        cout << "use seq" << endl;
    };
};

template<typename R, typename... Args>
R getRetArgs(R(Args...));

template<typename R, typename... Args>
constexpr size_t getNumArgs(R(*)(Args...)) {
    return sizeof ...(Args);
}

int main1(){

    NodeInfo node;
    vector<NodeInfo>nodes;

    //example 1: enable_if
    checkParams<NodeInfo>(node);
    checkParams<vector<NodeInfo>>(nodes);

    //example 2: int flag = sizeof(T);bool_trait<flag>
    CheckParams<NodeInfo> cnode;
    CheckParams<vector<NodeInfo>> cnodes;
    cnode.check(node);
    cnodes.check(nodes);
}





/**
  ******************************************************************************
  * @author         : oswin
  * @brief          : tuple在模版元编程中的一个应用场景是将可变模板参数保存起来，因为可变模板
  * 参数不能直接作为变量保存起来，需要借助tuple保存起来，保存后再在需要的时候通过一些手段将tuple
  * 又转换为可变模板参数
  * @date           :
  ******************************************************************************
  */

//定义整形序列
template<int...>
struct IndexSeq{};

//生成整形序列
template<int N, int... Indexes>
struct MakeIndexes : MakeIndexes<N - 1, N - 1, Indexes...>{//递归生成MakeIndexes<0,0,1,2,3...N-1>
    MakeIndexes(){
        cout<<"N: "<<N<<endl;
    }
};

template<int... indexes>
struct MakeIndexes<0, indexes...>{
    MakeIndexes(){
        cout<<"KK"<<endl;
    }
    typedef IndexSeq<indexes...> type;
};

template<typename... Args>
void printargs(Args... args){
    //先将可变模板参数保存到tuple中
    print_helper(typename MakeIndexes<sizeof... (Args)>::type(), std::make_tuple(args...));
}

template<typename T>
void print(T t)
{
    cout << t << endl;
}

template<typename T, typename... Args>
void print(T t, Args... args)
{
    print(t);
    print(args...);
}

template<int... Indexes, typename... Args>
void print_helper(IndexSeq<Indexes...>, std::tuple<Args...>&& tup){
    //再将tuple转换为可变模板参数，将参数还原回来，再调用print
    print(std::get<Indexes>(tup)...);
}

//递归的简单例子
void recursiveFunc(deque<int> &vec) {
    int front = vec.front();
    if (front == 0) {
        return;
    }

    front = front - 1;
    vec.push_front(front);
    recursiveFunc(vec);
}

int main(){
    printargs(1, 2.5, "test");
    
    //test recursive function
    deque<int> vec{6};
    recursiveFunc(vec);

    while (!vec.empty()) {
        int p = vec.back();
        vec.pop_back();
        cout << p << endl;
    }
}
