#include "cipherthread.h"

CipherThread::CipherThread(QObject *parent, std::string &s, int pos, int k)
    : QThread(parent), m_s(s), m_pos(pos), m_k(k)
{
}

void CipherThread::run()
{
    //radi samo za basic slucajeve, nisam obradjivoa ostalo
    char c = m_s[m_pos];
    c += (m_k % 26);
    m_s[m_pos] = c;
}
