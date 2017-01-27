#ifndef DOODSONNUMBERS_H
#define DOODSONNUMBERS_H


class DoodsonNumbers
{
public:
    explicit DoodsonNumbers():m_d1(0),m_d2(0),m_d3(0),m_d4(0),m_d5(0),m_d6(0),m_extended(0){}
    explicit DoodsonNumbers(int d1, int d2, int d3, int d4, int d5, int d6, int extended):
        m_d1(d1),m_d2(d2),m_d3(d3),m_d4(d4),m_d5(d5),m_d6(d6),m_extended(extended){}

    int D1() const{return m_d1;}
    int D2() const{return m_d2;}
    int D3() const{return m_d3;}
    int D4() const{return m_d4;}
    int D5() const{return m_d5;}
    int D6() const{return m_d6;}
    int Extended() const{return m_extended;}

    void setD1(const int &d1){m_d1 = d1;}
    void setD2(const int &d2){m_d2 = d2;}
    void setD3(const int &d3){m_d3 = d3;}
    void setD4(const int &d4){m_d4 = d4;}
    void setD5(const int &d5){m_d5 = d5;}
    void setD6(const int &d6){m_d6 = d6;}
    void setExtended(const int &ext){m_extended = ext;}

private:
    int m_d1;
    int m_d2;
    int m_d3;
    int m_d4;
    int m_d5;
    int m_d6;
    int m_extended;
};
inline bool operator ==(const DoodsonNumbers &doodson1, const DoodsonNumbers &doodson2){
    return (doodson1.D1() == doodson2.D1() && doodson1.D2() == doodson2.D2() && doodson1.D3() == doodson2.D3()
            && doodson1.D4() == doodson2.D4() && doodson1.D5() == doodson2.D5() && doodson1.D6() == doodson2.D6()
            && doodson1.Extended() == doodson2.Extended());
}
inline bool operator !=(const DoodsonNumbers &doodson1, const DoodsonNumbers &doodson2){
    return !(doodson1 == doodson2);
}

#endif // DOODSONNUMBERS_H
