#include <iostream>
#include <QHash>

using namespace std;

class UseQHash
{
public:
    QHash<QString, QString>& getProps() const;
private:
    QHash<QString, QString> _data;
};

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
