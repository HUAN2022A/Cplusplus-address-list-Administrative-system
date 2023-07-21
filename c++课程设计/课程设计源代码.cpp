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
    //�麯�����س���ֻ�����ã���ֹ�޸�
    const string& getName() const;
    const string& getPhoneNumber() const;
    //�޸ĳ�Ա
    void revisename(string newname);
    void revisephoneNumber(string newphonenumber);
};
void Contact::display() const {
    cout << "������" << getName() << " " << "��ϵ��ʽ:" << getPhoneNumber() << endl;
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
    cout << "���������������������ֻ�����" << endl;
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
    cout << "������������" << endl;
    input>>name;
    cout << "���������ֻ�����" << endl;
    input >> phone;
    cout << "�������¼���" << endl;
    input >> hometown;
    cout << "��������QQ����" << endl;
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
    cout << "������" << getName() <<" " << "��ϵ��ʽ:" << getPhoneNumber() <<"  "<<"����: " << hometown <<" " << "QQ���� : " << qqNumber << endl;

}
class contactmanagerment {
private:
    PhoneContact pc[MAX];
    SimCardContact sc[MAX];
    int pcnumber;
    int scnumber;
public:
    
    contactmanagerment() : pcnumber(0),scnumber(0){}
    //�����ֻ�ͨѶ¼
    void loadPhoneContact();
    //�����ֻ���ͨѶ¼
    void loadPhonecardContact();
    // �����ϵ��
    void addContact();
    //ɾ����ϵ��
    void deleteContact(); 
    //��ʾ��ϵ��
    void displayContacts();
    //�޸���ϵ��
    void reviseContact();
    //��ѯ��ϵ��
    void searchContact();
    //ת���ֻ���ϵ�����ֻ���
    void save_to_sim_card();
    //ת���ֻ�����ϵ�����ֻ�
    void save_to_phone();

    //�����ֻ���ϵ��
    void savePhoneContact();
    //�����ֻ�����ϵ��
    void savePhoneCardContact();
};
void contactmanagerment::loadPhoneContact() {
    fstream ifs1;
    ifs1.open("D:\\phone_contacts.txt");
    if (ifs1.is_open()) {
        cout << "�ֻ�ͨѶ¼���سɹ�" << endl; 
        while (ifs1 >> pc[pcnumber].name >> pc[pcnumber].phoneNumber)
        {
            pcnumber++;
        }
        ifs1.close();
    }
    else {
        cout << "�ļ���ʧ��" << endl;
    }
  
}
void contactmanagerment::loadPhonecardContact() {
    string temp2;
    ifstream ifs2;
    ifs2.open("D:\\sim_contacts.txt");
    if (ifs2.is_open()) {
        cout << "�ֻ���ͨѶ¼���سɹ�" << endl;
        getline(ifs2, temp2);
        while (ifs2 >> sc[scnumber].name >> sc[scnumber].phoneNumber >> sc[scnumber].hometown >> sc[scnumber].qqNumber)
        {
            scnumber++;
        }
      
        ifs2.close();
    }
    else {
        cout << "�ļ���ʧ��" << endl;
    }
}
void contactmanagerment::addContact() {
    cout << "��ѡ����Ҫ�����ϵ�˵�λ��" << endl;
    cout << "1.�ֻ�" << endl;
    cout << "2.�ֻ���" << endl;
    int choice;
    cin >> choice;
    if (choice == 1) {
        if (pcnumber == MAX)
        {
            cout << "��ϵ��������������" << endl;
            return;
        }
        else {
            string name, phoneNumber;
            cout << "��������ϵ������" << endl;
            cin >> name;
            cout << "��������ϵ�˺���" << endl;
            cin >> phoneNumber;
            bool exist = false;
            for (int i = 0; i < pcnumber; i++) {
                if (pc[i].getPhoneNumber() == phoneNumber) {
                    exist = true;
                    cout << "����ϵ�����ֻ����Ѿ����ڣ�" << endl;
                    break;
                }
            }
            if (!exist) {

                PhoneContact contact(name, phoneNumber);
                pc[pcnumber++] = contact;
                cout << "��ϵ����ӳɹ���" << endl;
            }

        }
    }
    if (choice == 2)
    {
        if (scnumber == MAX)
        {
            cout << "��ϵ��������������" << endl;
            return;
        }
            bool exist = false;
            string name, phoneNumber, hometown, qqNumber;
            cout << "��������ϵ��������" << endl;
            cin >> name;
            cout << "��������ϵ�˺��룺" << endl;
            cin >> phoneNumber;
            cout << "��������ϵ�˼��᣺" << endl;
            cin >> hometown;
            cout << "��������ϵ��QQ���룻" << endl;
            cin >> qqNumber;
                for (int i = 0; i < scnumber; i++) {
                    if (sc[i].getPhoneNumber() == phoneNumber || sc[i].getqqNumber() == qqNumber) {
                        cout << "����ϵ�����ֻ������Ѿ����ڣ�" << endl;
                        exist = true;
                        break;
                    }
                }
                if (!exist) {
                    SimCardContact contact(name, phoneNumber,hometown,qqNumber);
                    sc[scnumber++] = contact;
                    cout << "��ϵ����ӳɹ���" << endl;
                }
        }
    if(choice!=1&&choice!=2)
    {
        cout << "δ֪������������" << endl;
    }
    }
void contactmanagerment::deleteContact() {
    bool deleted = false;
    string key;
    int choice;
    cout << "��������Ҫɾ����ϵ�˵�λ��" << endl;
    cout << "1.�ֻ�" << endl;
    cout << "2.�ֻ���" << endl;
    cin >> choice;
    if (choice == 1) {
        cout << "��������Ҫɾ����ϵ�˵���ϵ��ʽ" << endl;
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
            cout << "�ɹ�ɾ��" << std::endl;
        }
        else {
            cout << "��ϵ��δ�ҵ�" << std::endl;
        }

    }
    if (choice == 2) {
        cout << "��������Ҫɾ����ϵ�˵���ϵ��ʽ��QQ����" << endl;
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
            cout << "�ɹ�ɾ��." << std::endl;
        }
        else {
            cout << "��ϵ��δ�ҵ�" << std::endl;
        }  
    }
    if(choice!=1&&choice!=2)
    {
        cout << "δ֪������������" << endl;
    }
}
void contactmanagerment::displayContacts() {
    cout << "��1��ʾ�����ֻ���ϵ�ˣ�" << endl;
    cout << "��2��ʾ�����ֻ�����ϵ�ˣ�" << endl;
    int key;
    cin >> key;
    if (key == 1) {
        if (pcnumber != 0)
        {
            cout << "����Ϊ�����ֻ���ϵ��" << endl;
            for (int i = 0; i < pcnumber; i++) {
                pc[i].display();
            }
        }
        else if (pcnumber == 0)
        {
            cout << "�ֻ���ǰ������ϵ�ˣ�����Ӻ�����" << endl;
        }
    }
    if (key == 2) {
        if (scnumber != 0)
        {
            cout << "����Ϊ�����ֻ�����ϵ��" << endl;
            for (int i = 0; i < scnumber; i++) {
                sc[i].display();
            }
        }
        else if (scnumber == 0)
        {
            cout << "�ֻ�����ǰ������ϵ�ˣ�����Ӻ�����" << endl;
        }
    }
    if(key!=1&&key!=2)
    {
cout << "δ֪������������" << endl;
    }
}
void contactmanagerment::reviseContact() {
    bool revise = false;
    cout << "��������Ҫ�޸���ϵ�˵�λ��" << endl;
    cout << "1.�ֻ�" << endl;
    cout << "2.�ֻ���" << endl;
    int choice;
    cin >> choice;
    if (choice == 1) {
        cout << "��������Ҫ�޸���ϵ�˵�������绰���룺" << endl;
        string key;
        cin >> key;
        for (int i = 0; i <= pcnumber; i++) {
            if (pc[i].getName() == key || pc[i].getPhoneNumber() == key)
            {
                cout << "���ҵ������ϵ����Ϣ:" << endl;
                pc[i].display();
                cout << "��1�޸�����" << endl << "��2�޸ĵ绰����" << endl << "��3�޸������͵绰����" << endl;
                int choice;
                string name;
                string phonenumber;
                cin >> choice;
                if (choice == 1)
                {
                    cout << "������������" << endl;
                    cin >> name;
                    pc[i].revisename(name);
                }
                else if (choice == 2)
                {
                    cout << "���������ֻ�����" << endl;
                    cin >> phonenumber;
                    pc[i].revisephoneNumber(phonenumber);
                }
                else if (choice == 3)
                {
                    cin >> pc[i];

                }
                cout << "��ϵ���޸ĳɹ���" << endl << endl << endl;
                revise = true;
            }

        }
        if (!revise) {
            cout << "δ�ҵ�����ϵ�ˣ�������" << endl;
            return;
        }
    }
    if (choice == 2) {
        cout << "��������Ҫ�޸���ϵ�˵�������绰���룺" << endl;
        string key;
        cin >> key;
        for (int i = 0; i <= scnumber; i++) {
            if (sc[i].getName() == key || sc[i].getPhoneNumber() == key)
            {
                cout << "���ҵ������ϵ����Ϣ:" << endl;
                sc[i].display();
                cout << "��1�޸�����" << endl << "��2�޸ĵ绰����" << endl << "��3�޸ļ���" << endl << "��4�޸�QQ����" <<endl<< "��5ȫ���޸�" << endl;
                int choice;
                string name;
                string phonenumber;
                string hometown;
                string QQnumber;
                cin >> choice;
                if (choice == 1)
                {
                    cout << "������������" << endl;
                    cin >> name;
                    sc[i].revisename(name);
                    revise = true;
                }
                else if (choice == 2)
                {
                    cout << "���������ֻ�����" << endl;
                    cin >> phonenumber;
                    sc[i].revisephoneNumber(phonenumber);
                    revise = true;
                }
                else if (choice == 3)
                {
                    cout << "�������¼���" << endl;
                    cin >> hometown;
                    sc[i].revisehometown(hometown);
                    revise = true;
                }
                else if (choice == 4)
                {
                    cout << "��������QQ����" << endl;
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
                cout << "δ�ҵ�����ϵ�ˣ�������" << endl;
                return;
            }
            else {
                cout << "��ϵ����Ϣ�޸ĳɹ���" << endl << endl << endl;
                return;
            }
        }
    }
    if (choice != 1 && choice != 2)
    {
        cout << "δ֪������������" << endl;
    }

}
void contactmanagerment::searchContact() {
    bool search = false;
    string key;
    cout << "��������Ҫ��ѯ��ϵ�˵��������ֻ�����" << endl;
    cin >> key;
    cout << "��������Ҫ��ѯ��ϵ�˵�λ��" << endl;
    cout << "1.�ֻ�" << endl;
    cout << "2.�ֻ���" << endl;
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        for (int i = 0; i < pcnumber; i++)
        {
            //���ܳ���������ϵ��
            if (pc[i].getName() == key || pc[i].getPhoneNumber() == key)
            {
                pc[i].display();
                search = true;
            }
        }
        if (!search)
        {
            cout << "δ�ҵ�����ϵ�ˣ������ԣ�" << endl;
        }
    }
    if (choice == 2)
    {
        for (int i = 0; i < pcnumber; i++)
        {
            //���ܳ���������ϵ��
            if (sc[i].getName() == key || sc[i].getPhoneNumber() == key)
            {
                pc[i].display();
                search = true;
            }
        }
        if (!search)
        {
            cout << "δ�ҵ�����ϵ�ˣ������ԣ�" << endl;
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
    if (!none) { cout << "ת��ɹ���" << endl; }
    else { cout << "�޿�ת����ϵ�ˣ�" << endl; }
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
    if (!none) { cout << "ת��ɹ���" << endl; }
    else { cout << "�޿�ת����ϵ�ˣ�" << endl; }
}
void contactmanagerment::savePhoneContact() {
    //�����ֻ���ϵ��
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
        cout << "�ֻ���ϵ�˱���ɹ�" << endl;
    }
    else {
        cout << "�ֻ���ϵ�˱���ʧ��" << endl;
    }
 
}
void contactmanagerment::savePhoneCardContact() {
    //�����ֻ�����ϵ��
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
        cout << "�ֻ�����ϵ�˱���ɹ�" << endl;
    }
    else {
        cout << "�ֻ�����ϵ�˱���ʧ��" << endl;
    }
}
void  displaymenu() {

  
    cout << "                                                       SDAU_QZH            " << endl;
    cout << "                                            ==============================" << endl;
    cout << "                                            |     �𾴵Ŀͻ����ã�       |" << endl;
    cout << "                                            |  ��ӭ��¼ͨѶ¼����ϵͳ    |" << endl;
    cout << "                                            |  �밴ѡ����Ҫִ�еĲ���    |" << endl;
    cout << "                                            |   1.����µ���ϵ��.        |" << endl;
    cout << "                                            |   2.ɾ����ϵ����Ϣ.        |" << endl;
    cout << "                                            |   3.�޸���ϵ����Ϣ.        |" << endl;
    cout << "                                            |   4.��ѯ��ϵ����Ϣ.        |" << endl;
    cout << "                                            |   5.��ʾ��ϵ����Ϣ.        |" << endl;
    cout << "                                            |   6.ת���ֻ���ϵ�����ֻ���.|" << endl;
    cout << "                                            |   7.ת���ֻ�����ϵ�����ֻ�.|" << endl;
    cout << "                                            |   0.�˳�ͨѶ¼ϵͳ.        |" << endl;
    cout << "                                            ==============================" << endl;
    cout << "                                  Ϊ�������û����飬���ڲ�����������0�˳����������ݶ�ʧ" << endl;
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
            //�����ļ�
            on.savePhoneContact();
            on.savePhoneCardContact();
            cout << "�ڴ������´�ʹ�ã�" << endl;
            return 0;
        }
        if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7 && choice != 0 )
        {
            system("cls");
            cout << "δ֪������������" << endl;
        }
        cout << endl << endl;
        cout << "*��1�������˵�" << endl;
        cout << "*��0�˳�" << endl;
        int num;
        cin >> num;
        if (num == 0)
        {
            system("cls");
            //�����ļ�
            on.savePhoneContact();
            on.savePhoneCardContact();
            cout << "�ڴ������´�ʹ�ã�" << endl;
            return 0;
            
        }
        else if (num == 1)
        {
            displaymenu();
        }
        else if (num != 1 && num != 0)
        {
            cout << "δ֪������������" << endl;
        }
    }
}
  