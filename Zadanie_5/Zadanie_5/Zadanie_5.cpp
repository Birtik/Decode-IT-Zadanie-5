#include <iostream>
#include <list>
#include <fstream>
#include <string>


using namespace std;


class Web
{
public:

    int* ip;

public:
    Web(int* ip)
    {
        this->ip = ip;
    }
};

class Task
{
private:

    ifstream s;
    string line;
    list<Web*> web;
    list<bool> tests;

public:

    Task()
    {
        s.open("file.txt");
    }

    int* getIp()
    {
        try
        {
            string number;
            int* ip = new int[8];

            int i = 1;
            int j = 0;

            if (line[1] != ' ') throw 1;

            do
            {
                i++;

                if (line[i] == '.' || line[i] == ' ')
                {
                    ip[j] = 0;

                    for (int s = number.length() - 1, p = 1; s >= 0; s--, p *= 10)
                        ip[j] += ((int)number[s] - 48) * p;



                    if (ip[j] < 0 || ip[j]>255) throw 1;

                    number = "";
                    j++;
                }
                else number += line[i];

            } while (line[i] != ' ');

            do
            {
                i++;

                if (line[i] == '.' || line[i] == '\0')
                {
                    ip[j] = 0;

                    for (int s = number.length() - 1, p = 1; s >= 0; s--, p *= 10)
                        ip[j] += ((int)number[s] - 48) * p;


                    if (ip[j] < 0 || ip[j]>255) throw 1;

                    number = "";
                    j++;
                }
                else number += line[i];

            } while (line[i] != '\0');

            return ip;
        }
        catch (int x)
        {
            cout << "Incorrect input data!";
            exit(0);
        }

    }

    void ReadFile()
    {
        while (getline(s, line))
        {
            try
            {
                if (line[0] == 'B') SetWeb();
                else if (line[0] == 'T') FindWeb();
                else throw 1;
            }
            catch (int x) {
                cout << "Incorrect input data!";
                exit(0);
            }
        }

        s.close();
    }

    void SetWeb()
    {
        try
        {
            web.push_back(new Web(getIp()));
        }
        catch (int x) {
            cout << "Incorrect input data!";
            exit(0);
        }
    }

    void FindWeb()
    {
        int* test_ip = getIp();
        bool exist = false;

        for (Web* w : web)
        {
            if (exist) break;

            for (int i = 0; i < 8; i++)
            {
                //cout << "Pobrany: " << test_ip[i] << endl;
                //cout << "Zapisany: " << w->ip[i] << endl;


                if (test_ip[i] != w->ip[i]) break;

                if (i == 7) exist = true;
            }
        }

        try
        {
            tests.push_back(exist);
        }
        catch (int x) {
            cout << "Incorrect input data!";
            exit(0);
        }
    }

    list<bool> getTests()
    {
        return tests;
    }

};

int main()
{
    Task* task = new Task();

    task->ReadFile();

    for (bool b : task->getTests())
    {
        if (b) cout << 'T' << endl;
        else cout << 'N' << endl;
    }

    delete task;
}

