#include <iostream>
#include <string>
std::string fill(std::string s, int ln){
    while (s.length()<ln){
        s = '0'+s;
    }
    if (s.length()>ln){
        std::string t = "";
        for (int i = 0; i < ln; i ++){
            t += s[i];
        }
        return t;
    }
    return s;
}
struct zachNum{
    std::string num;
    int intnum;
    zachNum(int fsprt, char tlr, int scndprt){
        num = fill(std::to_string(fsprt%100), 2)+tlr+fill(std::to_string(scndprt%10000), 4);
        intnum = std::stoi(fill(std::to_string(fsprt%100), 2)+std::to_string(int(tlr))+fill(std::to_string(scndprt%10000), 4));
    }
};
struct grNum{
    std::string num;
    grNum(std::string name, int nm, int yr){
        num = fill(name, 4)+'-'+fill(std::to_string(nm%100), 2)+'-'+fill(std::to_string(yr%100), 2);
    }
};
struct zachotka{
    zachNum* znum;
    grNum* gnum;
    int mrk;
    zachotka(zachNum* z, grNum* g, int m):
    znum(z), gnum(g){
        if (m > 5){
            mrk = 5;
        } else if (m < 2){
            mrk = 2;
        }  else{
           mrk = m;
        }
    }
    std::string printLine(){
        return znum->num+' '+gnum->num+' '+std::to_string(mrk)+"     "+std::to_string(znum->intnum);
    }
    ~zachotka(){
        delete znum;
        delete gnum;
    }
};
struct dobllist {
private:
    struct item{
        zachotka* val;
        int id;
        item *prev;
        item *next;
        item(zachotka* zch):
                val(zch), id(0), prev(nullptr), next(nullptr){
        };
        void chngId(int frid, int val){
            for (item* p = this; p; p = p->next){
                if (p->id >= frid){
                    p->id += val;
                }
            }
        }
        void delSelf(int frid){
            if (prev){
                prev->next = next;
            }
            if (next){
                next->prev = prev;
                next->chngId(frid, -1);
            }
            delete this;
        }
        ~item(){
            delete val;
        }
    };
    int len = 0;
    item *fst = nullptr;
    item* getVal(int fid) {
        item *p = fst;
        for (; p->id != fid; p = p->next);
        return p;
    }
public:
    int getLen(){
        return len;
    }
    zachotka* getNode(int i){
        return getVal(i)->val;
    }
    void insert(zachotka* nval){
        if (!fst){
            fst = new item(nval);
        }else{
            int tid = 0;
            bool fnd = false;
            for (item* p = fst; p; p = p->next){
                tid = p->id;
                if ((nval->znum->intnum)<=(p->val->znum->intnum)){
                    fnd = true;
                    break;
                }
            }
            item* ins = new item(nval);
            if (fnd){
                item* temp = getVal(tid);
                ins->next = temp;
                ins->prev = temp->prev;
                ins->id = tid;
                temp->prev = ins;
                temp->chngId(tid, 1);
                if (!tid){
                    fst = ins;
                }else{
                    ins->prev->next = ins;
                }
            }else{
                item* temp = getVal(len-1);
                temp->next = ins;
                ins->prev = temp;
                ins->id = len;
            }
        }
        len += 1;
    }
    void printList(bool dir){
        if (dir){
            for (item* p = fst; p; p = p->next){
                std::cout << p->id << "   " << p->val->printLine() << std::endl;
            }
        }else{
            item* p = fst;
            for (; p->next; p = p->next);
            for (item* pp = p; pp; pp = pp->prev){
                std::cout << pp->id << "   " << pp->val->printLine() << std::endl;
            }
        }
    }
    void del(int frid){
        if (((frid+1) <= len) and frid >= 0){
            len -= 1;
            item* p = getVal(frid);
            if (!frid){
                fst = p->next;
            }
            p->delSelf(frid);
        }
    }
    ~dobllist(){
        item *temp;
        len = 0;
        while (fst){
            temp = fst;
            fst = fst->next;
            delete temp;
        }
    }
};

int main() {
    dobllist* a = new dobllist();
    a->insert(new zachotka(new zachNum(12, 'L', 1234), new grNum("IKBO", 25, 22), 5));
    //a->insert(new zachotka(new zachNum(12, 'L', 1234), new grNum("IKBO", 25, 22), 4));
    //a->insert(new zachotka(new zachNum(12, 'L', 1234), new grNum("IKBO", 25, 22), 3));
    //a->insert(new zachotka(new zachNum(12, 'L', 1234), new grNum("IKBO", 25, 22), 2));
    //a->insert(new zachotka(new zachNum(12, 'X', 1234), new grNum("I:BO", 25, 22), 5));
    //a->insert(new zachotka(new zachNum(12, 'Z', 1234), new grNum("IHBO", 25, 22), 5));
    //a->insert(new zachotka(new zachNum(12, 'X', 1234), new grNum("I:BO", 25, 22), 2));
    //a->insert(new zachotka(new zachNum(12, 'X', 1234), new grNum("I:BO", 25, 22), 4));
    //a->insert(new zachotka(new zachNum(12, 'L', 1234), new grNum("IKBO", 25, 22), 3));
    //a->insert(new zachotka(new zachNum(12, 'A', 1234), new grNum("IHBO", 25, 22), 3));
    //a->insert(new zachotka(new zachNum(12, 'A', 1234), new grNum("IHBO", 25, 22), 2));
    a->printList(true);
    std::cout << std::endl;
    a->del(0);
    a->printList(true);
    a->insert(new zachotka(new zachNum(12, 'L', 1234), new grNum("IKBO", 25, 22), 4));
    a->printList(true);
    a->del(0);
    a->printList(true);
    std::cout << std::endl;
    delete a;
    return 0;
}
