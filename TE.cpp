/**
******************************************************************************
* @author         : oswin
* @brief          : 模板元编程条件编译的简单例子
******************************************************************************
*/

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

int main(){

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
