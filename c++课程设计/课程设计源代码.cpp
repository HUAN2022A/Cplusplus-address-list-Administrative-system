#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const int MAX = 1000;
class Contact {
private:
    string name;
    string phoneNumber;

public:
    Contact() {}
    Contact(const string& _name, const string& _phoneNumber) : name(_name), phoneNumber(_phoneNumber) {}
    friend class contactmanagerment;
    virtual void display() const;
    //虚函数返回常量只读引用，防止修改
    const string& getName() const;
    const string& getPhoneNumber() const;
    //修改成员
    void revisename(string newname);
    void revisephoneNumber(string newphonenumber);
};
void Contact::display() const {
    cout << "姓名：" << getName() << " " << "联系方式:" << getPhoneNumber() << endl;
}
const string& Contact::getName() const {
        return name;
    }
const string& Contact::getPhoneNumber() const {
    return phoneNumber;
}
void Contact::revisename(string newname) {
    this->name = newname;
}
void Contact::revisephoneNumber(string newphonenumber) {
    this->phoneNumber = newphonenumber;
}
class PhoneContact : public Contact {
public:

    PhoneContact() {}
    PhoneContact(const string& name, const string& phoneNumber) : Contact(name, phoneNumber) {}
    friend istream& operator>>(istream& input, const PhoneContact& a);
};
istream& operator>>(istream& input, PhoneContact& a)
{
    string name, phone;
    cout << "请依次输入新姓名和新手机号码" << endl;
    input >> name >> phone;
    PhoneContact b(name, phone);
     a =  b;
     return input;
}
class SimCardContact : public Contact {
private:
    string hometown;
    string qqNumber;

public:
    SimCardContact() {}
    SimCardContact(const string& name, const string& phoneNumber, const string& hometown, const string& qqNumber)
        : Contact(name, phoneNumber), hometown(hometown), qqNumber(qqNumber) {}
    const string& gethometown() const;
    const string& getqqNumber() const;
    void revisehometown(string newhometown);
    void reviseqqNumber(string newqqNumber);
    void display() const override;
    SimCardContact& operator=(PhoneContact& b);
    friend class contactmanagerment;
    friend istream& operator>>(istream& input, SimCardContact& a);
    
};
SimCardContact& SimCardContact::operator=(PhoneContact& b) {
    revisename(b.getName());
    revisephoneNumber(b.getPhoneNumber());
    return *this;
}
istream& operator>>(istream& input, SimCardContact& a)
{
    string name, phone,hometown,qqnumber;
    cout << "请输入新姓名" << endl;
    input>>name;
    cout << "请输入新手机号码" << endl;
    input >> phone;
    cout << "请输入新籍贯" << endl;
    input >> hometown;
    cout << "请输入新QQ号码" << endl;
    input >> qqnumber;
    SimCardContact b(name, phone,hometown,qqnumber);
    a = b;
    return input;
}
void SimCardContact::revisehometown(string newhometown) {
    this->hometown = newhometown;
}
void SimCardContact::reviseqqNumber(string newqqNumber) {
    this->qqNumber = newqqNumber;
}
const string& SimCardContact::getqqNumber() const
{
    return qqNumber;
}
const string& SimCardContact::gethometown() const
{
    return hometown;
}
void SimCardContact::display() const {
    cout << "姓名：" << getName() <<" " << "联系方式:" << getPhoneNumber() <<"  "<<"籍贯: " << hometown <<" " << "QQ号码 : " << qqNumber << endl;

}
class contactmanagerment {
private:
    PhoneContact pc[MAX];
    SimCardContact sc[MAX];
    int pcnumber;
    int scnumber;
public:
    
    contactmanagerment() : pcnumber(0),scnumber(0){}
    //加载手机通讯录
    void loadPhoneContact();
    //加载手机卡通讯录
    void loadPhonecardContact();
    // 添加联系人
    void addContact();
    //删除联系人
    void deleteContact(); 
    //显示联系人
    void displayContacts();
    //修改联系人
    void reviseContact();
    //查询联系人
    void searchContact();
    //转存手机联系人至手机卡
    void save_to_sim_card();
    //转存手机卡联系人至手机
    void save_to_phone();

    //保存手机联系人
    void savePhoneContact();
    //保存手机卡联系人
    void savePhoneCardContact();
};
void contactmanagerment::loadPhoneContact() {
    fstream ifs1;
    ifs1.open("D:\\phone_contacts.txt");
    if (ifs1.is_open()) {
        cout << "手机通讯录加载成功" << endl; 
        while (ifs1 >> pc[pcnumber].name >> pc[pcnumber].phoneNumber)
        {
            pcnumber++;
        }
        ifs1.close();
    }
    else {
        cout << "文件打开失败" << endl;
    }
  
}
void contactmanagerment::loadPhonecardContact() {
    string temp2;
    ifstream ifs2;
    ifs2.open("D:\\sim_contacts.txt");
    if (ifs2.is_open()) {
        cout << "手机卡通讯录加载成功" << endl;
        getline(ifs2, temp2);
        while (ifs2 >> sc[scnumber].name >> sc[scnumber].phoneNumber >> sc[scnumber].hometown >> sc[scnumber].qqNumber)
        {
            scnumber++;
        }
      
        ifs2.close();
    }
    else {
        cout << "文件打开失败" << endl;
    }
}
void contactmanagerment::addContact() {
    cout << "请选择你要添加联系人的位置" << endl;
    cout << "1.手机" << endl;
    cout << "2.手机卡" << endl;
    int choice;
    cin >> choice;
    if (choice == 1) {
        if (pcnumber == MAX)
        {
            cout << "联系人已满，请重试" << endl;
            return;
        }
        else {
            string name, phoneNumber;
            cout << "请输入联系人姓名" << endl;
            cin >> name;
            cout << "请输入联系人号码" << endl;
            cin >> phoneNumber;
            bool exist = false;
            for (int i = 0; i < pcnumber; i++) {
                if (pc[i].getPhoneNumber() == phoneNumber) {
                    exist = true;
                    cout << "此联系人在手机中已经存在！" << endl;
                    break;
                }
            }
            if (!exist) {

                PhoneContact contact(name, phoneNumber);
                pc[pcnumber++] = contact;
                cout << "联系人添加成功！" << endl;
            }

        }
    }
    if (choice == 2)
    {
        if (scnumber == MAX)
        {
            cout << "联系人已满，请重试" << endl;
            return;
        }
            bool exist = false;
            string name, phoneNumber, hometown, qqNumber;
            cout << "请输入联系人姓名：" << endl;
            cin >> name;
            cout << "请输入联系人号码：" << endl;
            cin >> phoneNumber;
            cout << "请输入联系人籍贯：" << endl;
            cin >> hometown;
            cout << "请输入联系人QQ号码；" << endl;
            cin >> qqNumber;
                for (int i = 0; i < scnumber; i++) {
                    if (sc[i].getPhoneNumber() == phoneNumber || sc[i].getqqNumber() == qqNumber) {
                        cout << "此联系人在手机卡中已经存在！" << endl;
                        exist = true;
                        break;
                    }
                }
                if (!exist) {
                    SimCardContact contact(name, phoneNumber,hometown,qqNumber);
                    sc[scnumber++] = contact;
                    cout << "联系人添加成功！" << endl;
                }
        }
    if(choice!=1&&choice!=2)
    {
        cout << "未知操作，请重试" << endl;
    }
    }
void contactmanagerment::deleteContact() {
    bool deleted = false;
    string key;
    int choice;
    cout << "请输入你要删除联系人的位置" << endl;
    cout << "1.手机" << endl;
    cout << "2.手机卡" << endl;
    cin >> choice;
    if (choice == 1) {
        cout << "请输入你要删除联系人的联系方式" << endl;
        cin >> key;
        for (int i = 0; i < pcnumber; i++) {
            if (pc[i].getPhoneNumber() == key )
            {
                for (int j = i; j < pcnumber - 1; j++) {
                    pc[j] = pc[j + 1];
                }
                pcnumber--;
                deleted = true;
                break;
            }
        }
        if (deleted) {
            cout << "成功删除" << std::endl;
        }
        else {
            cout << "联系人未找到" << std::endl;
        }

    }
    if (choice == 2) {
        cout << "请输入你要删除联系人的联系方式或QQ号码" << endl;
        cin >> key;
        for (int i = 0; i < scnumber; i++) {
            if (sc[i].getPhoneNumber() == key||sc[i].getqqNumber() == key)
            {
                for (int j = i; j < scnumber - 1; j++) {
                    sc[j] = sc[j + 1];
                }
                scnumber--;
                deleted = true;
                break;
            }
        }
        if (deleted) {
            cout << "成功删除." << std::endl;
        }
        else {
            cout << "联系人未找到" << std::endl;
        }  
    }
    if(choice!=1&&choice!=2)
    {
        cout << "未知操作，请重试" << endl;
    }
}
void contactmanagerment::displayContacts() {
    cout << "按1显示所有手机联系人；" << endl;
    cout << "按2显示所有手机卡联系人；" << endl;
    int key;
    cin >> key;
    if (key == 1) {
        if (pcnumber != 0)
        {
            cout << "以下为所有手机联系人" << endl;
            for (int i = 0; i < pcnumber; i++) {
                pc[i].display();
            }
        }
        else if (pcnumber == 0)
        {
            cout << "手机当前暂无联系人，请添加后重试" << endl;
        }
    }
    if (key == 2) {
        if (scnumber != 0)
        {
            cout << "以下为所有手机卡联系人" << endl;
            for (int i = 0; i < scnumber; i++) {
                sc[i].display();
            }
        }
        else if (scnumber == 0)
        {
            cout << "手机卡当前暂无联系人，请添加后重试" << endl;
        }
    }
    if(key!=1&&key!=2)
    {
cout << "未知操作，请重试" << endl;
    }
}
void contactmanagerment::reviseContact() {
    bool revise = false;
    cout << "请输入你要修改联系人的位置" << endl;
    cout << "1.手机" << endl;
    cout << "2.手机卡" << endl;
    int choice;
    cin >> choice;
    if (choice == 1) {
        cout << "请输入你要修改联系人的姓名或电话号码：" << endl;
        string key;
        cin >> key;
        for (int i = 0; i <= pcnumber; i++) {
            if (pc[i].getName() == key || pc[i].getPhoneNumber() == key)
            {
                cout << "已找到相关联系人信息:" << endl;
                pc[i].display();
                cout << "按1修改姓名" << endl << "按2修改电话号码" << endl << "按3修改姓名和电话号码" << endl;
                int choice;
                string name;
                string phonenumber;
                cin >> choice;
                if (choice == 1)
                {
                    cout << "请输入新姓名" << endl;
                    cin >> name;
                    pc[i].revisename(name);
                }
                else if (choice == 2)
                {
                    cout << "请输入新手机号码" << endl;
                    cin >> phonenumber;
                    pc[i].revisephoneNumber(phonenumber);
                }
                else if (choice == 3)
                {
                    cin >> pc[i];

                }
                cout << "联系人修改成功！" << endl << endl << endl;
                revise = true;
            }

        }
        if (!revise) {
            cout << "未找到该联系人，请重试" << endl;
            return;
        }
    }
    if (choice == 2) {
        cout << "请输入你要修改联系人的姓名或电话号码：" << endl;
        string key;
        cin >> key;
        for (int i = 0; i <= scnumber; i++) {
            if (sc[i].getName() == key || sc[i].getPhoneNumber() == key)
            {
                cout << "已找到相关联系人信息:" << endl;
                sc[i].display();
                cout << "按1修改姓名" << endl << "按2修改电话号码" << endl << "按3修改籍贯" << endl << "按4修改QQ号码" <<endl<< "按5全部修改" << endl;
                int choice;
                string name;
                string phonenumber;
                string hometown;
                string QQnumber;
                cin >> choice;
                if (choice == 1)
                {
                    cout << "请输入新姓名" << endl;
                    cin >> name;
                    sc[i].revisename(name);
                    revise = true;
                }
                else if (choice == 2)
                {
                    cout << "请输入新手机号码" << endl;
                    cin >> phonenumber;
                    sc[i].revisephoneNumber(phonenumber);
                    revise = true;
                }
                else if (choice == 3)
                {
                    cout << "请输入新籍贯" << endl;
                    cin >> hometown;
                    sc[i].revisehometown(hometown);
                    revise = true;
                }
                else if (choice == 4)
                {
                    cout << "请输入新QQ号码" << endl;
                    cin >> QQnumber;
                    sc[i].reviseqqNumber(QQnumber);
                    revise = true;
                }
                else if (choice == 5)
                {
                    cin >> sc[i];
                    revise = true;
                }
            }
            if (!revise) {
                cout << "未找到该联系人，请重试" << endl;
                return;
            }
            else {
                cout << "联系人信息修改成功！" << endl << endl << endl;
                return;
            }
        }
    }
    if (choice != 1 && choice != 2)
    {
        cout << "未知操作，请重试" << endl;
    }

}
void contactmanagerment::searchContact() {
    bool search = false;
    string key;
    cout << "请输入你要查询联系人的姓名或手机号码" << endl;
    cin >> key;
    cout << "请输入你要查询联系人的位置" << endl;
    cout << "1.手机" << endl;
    cout << "2.手机卡" << endl;
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        for (int i = 0; i < pcnumber; i++)
        {
            //可能出现重名联系人
            if (pc[i].getName() == key || pc[i].getPhoneNumber() == key)
            {
                pc[i].display();
                search = true;
            }
        }
        if (!search)
        {
            cout << "未找到该联系人，请重试！" << endl;
        }
    }
    if (choice == 2)
    {
        for (int i = 0; i < pcnumber; i++)
        {
            //可能出现重名联系人
            if (sc[i].getName() == key || sc[i].getPhoneNumber() == key)
            {
                pc[i].display();
                search = true;
            }
        }
        if (!search)
        {
            cout << "未找到该联系人，请重试！" << endl;
        }
    }
}
void contactmanagerment::save_to_sim_card() { 
    bool none=true;
    for (int i = 0; i <pcnumber;i++) {
        bool same = false;
        for (int j = 0; j < scnumber; j++) {
            if (sc[j].getPhoneNumber() == pc[i].getPhoneNumber())
            {
                same = true;
                break;
            }
        }
            if (!same) {
                sc[scnumber++] = pc[i];
                none = false;
            }
        }
    if (!none) { cout << "转存成功！" << endl; }
    else { cout << "无可转存联系人！" << endl; }
}
void contactmanagerment::save_to_phone() {
    bool none = true;
    for (int i =0; i <scnumber; i++) {
        bool same = false;
        for (int j = 0; j<pcnumber; j++) {
            if (pc[j].getPhoneNumber() == sc[i].getPhoneNumber())
            {
                same = true;
                break;
            }
        }
        if (!same) {
            PhoneContact a(sc[i].getName(), sc[i].getPhoneNumber());
                pc[pcnumber++] = a;
                none = false;
        }

    }
    if (!none) { cout << "转存成功！" << endl; }
    else { cout << "无可转存联系人！" << endl; }
}
void contactmanagerment::savePhoneContact() {
    //保存手机联系人
    ofstream ofs1;
    ofs1.open("D:\\phone_contacts.txt");
    if (ofs1.is_open())
    {
        ofs1 << endl;
        for (int i = 0; i < pcnumber; i++)
        {
            ofs1 << pc[i].name << " " << pc[i].phoneNumber << endl;
        }
        ofs1.close();
        cout << "手机联系人保存成功" << endl;
    }
    else {
        cout << "手机联系人保存失败" << endl;
    }
 
}
void contactmanagerment::savePhoneCardContact() {
    //保存手机卡联系人
    ofstream ofs2;
    ofs2.open("D:\\sim_contacts.txt");
    if (ofs2.is_open())
    {
        ofs2 << endl;
        for (int i = 0; i < scnumber; i++)
        {
            ofs2 << sc[i].name << " " << sc[i].phoneNumber << " " <<
                sc[i].hometown << " " << sc[i].qqNumber << endl;
        }
        ofs2.close();
        cout << "手机卡联系人保存成功" << endl;
    }
    else {
        cout << "手机卡联系人保存失败" << endl;
    }
}
void  displaymenu() {

  
    cout << "                                                       SDAU_QZH            " << endl;
    cout << "                                            ==============================" << endl;
    cout << "                                            |     尊敬的客户您好！       |" << endl;
    cout << "                                            |  欢迎登录通讯录管理系统    |" << endl;
    cout << "                                            |  请按选择你要执行的操作    |" << endl;
    cout << "                                            |   1.添加新的联系人.        |" << endl;
    cout << "                                            |   2.删除联系人信息.        |" << endl;
    cout << "                                            |   3.修改联系人信息.        |" << endl;
    cout << "                                            |   4.查询联系人信息.        |" << endl;
    cout << "                                            |   5.显示联系人信息.        |" << endl;
    cout << "                                            |   6.转存手机联系人至手机卡.|" << endl;
    cout << "                                            |   7.转存手机卡联系人至手机.|" << endl;
    cout << "                                            |   0.退出通讯录系统.        |" << endl;
    cout << "                                            ==============================" << endl;
    cout << "                                  为了您的用户体验，请在操作后正常按0退出，以免数据丢失" << endl;
    cout << endl;
    cout << "           * * * * * * *       * * * * * * * * * * *            * * * * *           * * *                 * * *  " << endl;
    cout << "          * * * * * * * * *    * * *            * * *          * * * * * *          * *                     * *" << endl;
    cout << "        * * * * *               * *                * *        * * * * * * *         * *                     * *" << endl;
    cout << "        * * *                   * *                 * *      * *       * * *        * *                     * *" << endl;
    cout << "          * * * * * * * *       * *                  * *    * *         * * *       * *                     * *" << endl;
    cout << "                      * * *     * *                  * *   * *         * * * *      * *                     * *" << endl;
    cout << "                        * *     * *                 * *   * * * * * * * * * * *     * *                     * * " << endl;
    cout << "                        * *     * *                * *   * *                 * *    * *                     * *" << endl;
    cout << "      * *               * *     * *               * *   * *                   * *   * * *               * * * *" << endl;
    cout << "      * * * * * * * * * * *  * * * * * * * * * * * *   * * * * *             * * *    * * * * * * * * * * * * * " << endl;
    cout << endl;
}
 int main() {
    contactmanagerment on;
    on.loadPhoneContact();
    on.loadPhonecardContact();
    displaymenu();
    while (true) {
      
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            system("cls");
            on.addContact();

        }
        else if (choice == 2)
        {
            system("cls");
            on.deleteContact();
        }
        else if (choice == 3)
        {
            system("cls");
            on.reviseContact();

        }
        else if (choice == 4)
        {
            system("cls");
            on.searchContact();
        }
        else if (choice == 5)
        {
            system("cls");
            on.displayContacts();
        }
        else if (choice == 6)
        {
            system("cls");
            on.save_to_sim_card();
        }
        else if (choice == 7)
        {
            system("cls");
            on.save_to_phone();
        }
        else if (choice == 0)
        {
            system("cls");
            //保存文件
            on.savePhoneContact();
            on.savePhoneCardContact();
            cout << "期待您的下次使用！" << endl;
            return 0;
        }
        if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7 && choice != 0 )
        {
            system("cls");
            cout << "未知操作，请重试" << endl;
        }
        cout << endl << endl;
        cout << "*按1返回主菜单" << endl;
        cout << "*按0退出" << endl;
        int num;
        cin >> num;
        if (num == 0)
        {
            system("cls");
            //保存文件
            on.savePhoneContact();
            on.savePhoneCardContact();
            cout << "期待您的下次使用！" << endl;
            return 0;
            
        }
        else if (num == 1)
        {
            displaymenu();
        }
        else if (num != 1 && num != 0)
        {
            cout << "未知操作，请重试" << endl;
        }
    }
}
  